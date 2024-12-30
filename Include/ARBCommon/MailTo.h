#pragma once

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

#include "LibwxARBCommon.h"

#include "ARBTypes.h"

#include <string>
#include <vector>


namespace dconSoft
{
namespace ARBCommon
{

class ARBCOMMON_API CMailTo
{
public:
	CMailTo();

	bool AddTo(wxString const& addr);
	void ClearTo();

	bool AddCC(wxString const& addr);
	void ClearCC();

	bool AddBCC(wxString const& addr);
	void ClearBCC();

	void SetSubject(wxString const& subject);
	void SetBody(wxString const& body);

	// clearText is to a user friendly version can be presented to user
	wxString Uri(bool clearText = false) const;

private:
	std::string Encode(wxString const& str, bool clearText) const;

	std::vector<wxString> m_to;
	std::vector<wxString> m_cc;
	std::vector<wxString> m_bcc;
	wxString m_subject;
	wxString m_body;
};

} // namespace ARBCommon
} // namespace dconSoft
