/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Mailto uri generator
 * @author David Connet
 *
 * Revision History
 * 2021-03-16 Created
 */

#include "stdafx.h"
#include "ARBCommon/MailTo.h"

#include "ARBCommon/StringUtil.h"

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>
#endif


namespace dconSoft
{
namespace ARBCommon
{

CMailTo::CMailTo()
	: m_to()
	, m_cc()
	, m_bcc()
	, m_subject()
	, m_body()
{
}


bool CMailTo::AddTo(wxString const& addr)
{
	if (std::find(m_to.begin(), m_to.end(), addr) != m_to.end())
		return false;
	m_to.push_back(addr);
	return true;
}


void CMailTo::ClearTo()
{
	m_to.clear();
}


bool CMailTo::AddCC(wxString const& addr)
{
	if (std::find(m_cc.begin(), m_cc.end(), addr) != m_cc.end())
		return false;
	m_cc.push_back(addr);
	return true;
}


void CMailTo::ClearCC()
{
	m_cc.clear();
}


bool CMailTo::AddBCC(wxString const& addr)
{
	if (std::find(m_bcc.begin(), m_bcc.end(), addr) != m_bcc.end())
		return false;
	m_bcc.push_back(addr);
	return true;
}


void CMailTo::ClearBCC()
{
	m_bcc.clear();
}


void CMailTo::SetSubject(wxString const& subject)
{
	m_subject = subject;
}


void CMailTo::SetBody(wxString const& body)
{
	m_body = body;
}


wxString CMailTo::Uri(bool clearText) const
{
	wxString buffer;
	buffer << L"mailto:";

	for (size_t i = 0; i < m_to.size(); ++i)
	{
		if (0 < i)
			buffer << L",";
		buffer << Encode(m_to[i], clearText);
	}

	if (m_cc.empty() && m_bcc.empty() && m_subject.empty() && m_body.empty())
		return buffer;

	buffer << L"?";
	bool needAmp = false;

	for (size_t i = 0; i < m_cc.size(); ++i)
	{
		if (0 == i)
		{
			if (needAmp)
				buffer << L"&";
			buffer << L"cc=";
		}
		else
			buffer << L",";
		buffer << Encode(m_cc[i], clearText);
		needAmp = true;
	}

	for (size_t i = 0; i < m_bcc.size(); ++i)
	{
		if (0 == i)
		{
			if (needAmp)
				buffer << L"&";
			buffer << L"bcc=";
		}
		else
			buffer << L",";
		buffer << Encode(m_bcc[i], clearText);
		needAmp = true;
	}

	if (!m_subject.empty())
	{
		if (needAmp)
			buffer << L"&";
		buffer << L"subject=" << Encode(m_subject, clearText);
		needAmp = true;
	}

	if (!m_body.empty())
	{
		if (needAmp)
			buffer << L"&";
		buffer << L"body=" << Encode(m_body, clearText);
		needAmp = true;
	}

	return buffer;
}


std::string CMailTo::Encode(wxString const& str, bool clearText) const
{
	// This may not be completely correct. Reading RFCs isn't fun.
	// But it seems close enough.
	// Must convert to UTF8 for encoding purposes.
	std::string s = str.utf8_string();

	if (clearText)
		return s;

	wxString buffer;
	for (auto const& c : s)
	{
		if (
			// Unreserved (rfc6068)
			(c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '-' || c == '.'
			|| c == '_'
			|| c == '~'
			// SomeDelims
			|| c == '!' || c == '%' || c == '\'' || c == '(' || c == ')' || c == '*' || c == '+' || c == ',' || c == ';'
			|| c == ':' || c == '@')
		{
			buffer << c;
		}
		else
		{
			// Must cast or things like 'a3' print as '-5d'
			buffer << L"%" << wxString::Format("%02x", static_cast<unsigned char>(c));
		}
	}
	return buffer.utf8_string();
}

} // namespace ARBCommon
} // namespace dconSoft
