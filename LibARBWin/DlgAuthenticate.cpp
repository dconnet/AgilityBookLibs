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
 * 2014-12-30 Changed pixels to dialog units.
 * 2012-02-16 Fix initial focus.
 * 2009-01-06 Ported to wxWidgets.
 * 2007-08-03 Created
 */

#include "stdafx.h"
#include "LibARBWin/DlgAuthenticate.h"

#include "LibARBWin/DlgPadding.h"
#include "LibARBWin/Widgets.h"
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/valgen.h>

#if defined(__WXMSW__)
#include <wx/msw/msvcrt.h>
#endif

namespace dconSoft
{
namespace ARBWin
{

CDlgAuthenticate::CDlgAuthenticate(wxString const& userName, wxWindow* parent, wxString caption, wxString message)
	: wxDialog()
	, m_Name(userName.c_str())
{
	if (caption.empty())
		caption = _("Authentication");
	Create(parent, wxID_ANY, caption.c_str(), wxDefaultPosition, wxDefaultSize);
	// Controls (these are done first to control tab order)

	wxStaticText* textMsg = nullptr;
	if (!message.empty())
	{
		textMsg = new wxStaticText(this, wxID_ANY, message.c_str(), wxDefaultPosition, wxDefaultSize, 0);
		textMsg->Wrap(-1);
	}

	wxStaticText* textUserName = new wxStaticText(this, wxID_ANY, _("User Name"), wxDefaultPosition, wxDefaultSize, 0);
	textUserName->Wrap(-1);

	CTextCtrl* ctrlUsername = new CTextCtrl(
		this,
		wxID_ANY,
		wxEmptyString,
		wxDefaultPosition,
		wxDLG_UNIT(this, wxSize(100, -1)),
		0,
		wxGenericValidator(&m_Name));

	wxStaticText* textPassword = new wxStaticText(this, wxID_ANY, _("Password"), wxDefaultPosition, wxDefaultSize, 0);
	textPassword->Wrap(-1);

	CTextCtrl* ctrlPassword = new CTextCtrl(
		this,
		wxID_ANY,
		wxEmptyString,
		wxDefaultPosition,
		wxDLG_UNIT(this, wxSize(100, -1)),
		wxTE_PASSWORD,
		wxGenericValidator(&m_Password));

	// Sizers
	const ARBWin::CDlgPadding padding(this);

	wxBoxSizer* bSizer = new wxBoxSizer(wxVERTICAL);

	if (textMsg)
		bSizer->Add(textMsg, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, padding.Controls());

	wxFlexGridSizer* sizerItems = new wxFlexGridSizer(2, 2, padding.Inner(), padding.Inner());
	sizerItems->SetFlexibleDirection(wxBOTH);
	sizerItems->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	sizerItems->Add(textUserName, 0, wxALIGN_CENTER_VERTICAL);
	sizerItems->Add(ctrlUsername, 1, wxALIGN_CENTER_VERTICAL);
	sizerItems->Add(textPassword, 0, wxALIGN_CENTER_VERTICAL);
	sizerItems->Add(ctrlPassword, 1, wxALIGN_CENTER_VERTICAL);

	bSizer->Add(sizerItems, 1, wxEXPAND | wxALL, padding.Controls());

	wxSizer* sdbSizer = CreateSeparatedButtonSizer(wxOK | wxCANCEL);
	bSizer->Add(sdbSizer, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, padding.ButtonSizer());

	SetSizer(bSizer);
	Layout();
	GetSizer()->Fit(this);
	wxSize sz = GetSize();
	SetSizeHints(sz, wxSize(-1, sz.y));
	CenterOnParent();

	if (userName.empty())
		IMPLEMENT_ON_INIT(CDlgAuthenticate, ctrlUsername)
	else
		IMPLEMENT_ON_INIT(CDlgAuthenticate, ctrlPassword)
}


wxString CDlgAuthenticate::GetUserName() const
{
	return m_Name;
}


wxString CDlgAuthenticate::GetPassword() const
{
	return m_Password;
}

} // namespace ARBWin
} // namespace dconSoft
