/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief BreakLine and CSV handling.
 * @author David Connet
 *
 * Revision History
 * 2012-07-25 Fix a CSV read problem with multiline continuation data.
 * 2012-04-10 Based on wx-group thread, use std::string for internal use
 * 2010-10-30 Moved BreakLine from Globals.cpp, added CSV routines.
 */

#include "stdafx.h"
#include "ARBCommon/BreakLine.h"

#if defined(__WXMSW__)
#include <wx/msw/msvcrt.h>
#endif


namespace dconSoft
{
namespace ARBCommon
{

size_t BreakLine(wchar_t inSep, wxString const& inStr, std::vector<wxString>& outFields, bool inRemoveEmpties)
{
	outFields.clear();

	if (inStr.empty())
		return 0;

	size_t fld = 0;
	wchar_t const* pos = inStr.wc_str();
	wchar_t const* npos = wcschr(pos, inSep);
	while (npos)
	{
		wxString str(pos, npos - pos);
		if (!(inRemoveEmpties && str.empty()))
			outFields.push_back(str);
		++fld;
		pos = npos + 1;
		npos = wcschr(pos, inSep);
	}
	if (pos)
	{
		wxString str(pos);
		if (!(inRemoveEmpties && str.empty()))
			outFields.push_back(str);
	}
	++fld;
	return fld;
}


/* Grammar copied from RFC4180
 *
 * The ABNF grammar [2] appears as follows:
 *
 * file = [header CRLF] record *(CRLF record) [CRLF]
 * header = name *(COMMA name)
 * record = field *(COMMA field)
 * name = field
 * field = (escaped / non-escaped)
 * escaped = DQUOTE *(TEXTDATA / COMMA / CR / LF / 2DQUOTE) DQUOTE
 * non-escaped = *TEXTDATA
 * COMMA = %x2C
 * CR = %x0D ;as per section 6.1 of RFC 2234 [2]
 * DQUOTE =  %x22 ;as per section 6.1 of RFC 2234 [2]
 * LF = %x0A ;as per section 6.1 of RFC 2234 [2]
 * CRLF = CR LF ;as per section 6.1 of RFC 2234 [2]
 * TEXTDATA =  %x20-21 / %x23-2B / %x2D-7E
 */

ReadStatus ReadCSV(
	wchar_t inSep,
	wxString inRecord,
	std::vector<wxString>& ioFields,
	bool bContinuation,
	wxString newLine)
{
	if (!bContinuation)
		ioFields.clear();
	ReadStatus status = ReadStatus::Ok;
	if (bContinuation && inRecord.empty())
	{
		ioFields[ioFields.size() - 1] += newLine;
		status = ReadStatus::NeedMore;
	}
	bool bAddEmpty = false;
	while (!inRecord.empty())
	{
		wxString str;
		wxString ::size_type posSep = inRecord.find(inSep);
		if (bContinuation || L'"' == inRecord[0])
		{
			wxString ::size_type posQuote = inRecord.find(L'"', bContinuation ? 0 : 1);
			if (wxString ::npos == posQuote)
			{
				if (bContinuation)
					str = inRecord;
				else
					str = inRecord.substr(1);
				inRecord.clear();
				status = ReadStatus::NeedMore;
			}
			else
			{
				wxString data;
				wxString::iterator iStr = inRecord.begin();
				if (!bContinuation)
					++iStr;
				bool bInQuote = true;
				for (; iStr != inRecord.end(); ++iStr)
				{
					if (!bInQuote && *iStr == inSep)
					{
						++iStr;
						break;
					}
					else if (*iStr == L'"')
					{
						// This is the last char.
						if (iStr + 1 == inRecord.end())
						{
							if (!bInQuote)
								return ReadStatus::Error;
							else
								bInQuote = false;
						}
						else
						{
							if (*(iStr + 1) == L'"')
							{
								data += *iStr;
								++iStr;
							}
							else if (*(iStr + 1) == inSep)
								bInQuote = false;
							else
							{
								if (bInQuote)
									return ReadStatus::Error;
								data += *iStr;
							}
						}
					}
					else
						data += *iStr;
				}
				str = data;
				if (iStr == inRecord.end())
					inRecord.clear();
				else
					inRecord = wxString(iStr, inRecord.end());
			}
		}
		else
		{
			if (wxString ::npos == posSep)
			{
				str = inRecord;
				inRecord.clear();
			}
			else
			{
				str = inRecord.substr(0, posSep);
				inRecord = inRecord.substr(posSep + 1);
				if (inRecord.empty())
					bAddEmpty = true;
			}
			// If there is a quote in the string,
			// the field itself must be quoted.
			if (wxString ::npos != str.find(L'"'))
				return ReadStatus::Error;
		}
		if (bContinuation && 0 < ioFields.size())
			ioFields[ioFields.size() - 1] += newLine + str;
		else
			ioFields.push_back(str);
		bContinuation = false;
	}
	if (bAddEmpty)
		ioFields.push_back(wxString());
	return status;
}


wxString WriteCSV(wchar_t inSep, std::vector<wxString> const& inFields, bool includeQuote)
{
	size_t fld = 0;
	wxString val;
	for (std::vector<wxString>::const_iterator i = inFields.begin(); i != inFields.end(); ++i, ++fld)
	{
		if (0 < fld)
			val << inSep;
		val << WriteCSVField(inSep, *i, includeQuote);
	}
	return val;
}


wxString WriteCSVField(wchar_t inSep, wxString const& inField, bool includeQuote)
{
	wxString val;
	if (wxString ::npos != inField.find(L'"') || wxString ::npos != inField.find(L'\n')
		|| wxString ::npos != inField.find(inSep))
	{
		wxString str(inField);
		val << L"\"";
		while (!str.empty())
		{
			wxString ::size_type pos = str.find(L'"');
			if (wxString ::npos == pos)
			{
				val << str;
				str.clear();
			}
			else
			{
				val << str.substr(0, pos) << L"\"\"";
				str = str.substr(pos + 1);
			}
		}
		val << L"\"";
	}
	else if (includeQuote)
	{
		val << L"\"" << inField << L"\"";
	}
	else
	{
		val << inField;
	}
	return val;
}

} // namespace ARBCommon
} // namespace dconSoft
