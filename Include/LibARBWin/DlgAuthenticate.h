#pragma once

/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Web authentication
 * @author David Connet
 *
 * Revision History
 * 2018-10-11 Moved to Win LibARBWin
 * 2009-01-06 Ported to wxWidgets.
 * 2007-08-03 Created
 */

#include "LibwxARBWin.h"


namespace dconSoft
{
namespace ARBWin
{

class ARBWIN_API CDlgAuthenticate : public wxDialog
{
public:
	CDlgAuthenticate(
		wxString const& userName,
		wxWindow* parent,
		wxString caption = wxString(),
		wxString message = wxString());

	wxString GetUserName() const;
	wxString GetPassword() const;

private:
	wxString m_Name;
	wxString m_Password;
};

} // namespace ARBWin
} // namespace dconSoft
