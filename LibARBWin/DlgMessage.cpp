/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Generic multiline edit dialog
 * @author David Connet
 *
 * Revision History
 * 2022-03-11 Moved from Win to LibARBWin, tweaked arguments
 * 2014-12-31 Changed pixels to dialog units.
 * 2009-02-09 Ported to wxWidgets.
 */

#include "stdafx.h"
#include "LibARBWin/DlgMessage.h"

#include "LibARBWin/DlgPadding.h"
#include "LibARBWin/Widgets.h"

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>
#endif


namespace dconSoft
{
namespace ARBWin
{

CDlgMessage::CDlgMessage(wxString const& msg, wxString caption, wxWindow* pParent, wxSize szDlgUnits)
	: wxDialog()
	, m_textCtrl(nullptr)
{
	if (caption.empty())
		caption = _("IDD_MESSAGE");
	Create(pParent, wxID_ANY, caption, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER);

	// Controls (these are done first to control tab order)

	m_textCtrl = new CTextCtrl(
		this,
		wxID_ANY,
		msg,
		wxDefaultPosition,
		wxDLG_UNIT(this, szDlgUnits),
		wxTE_MULTILINE | wxTE_READONLY | wxTE_WORDWRAP);

	wxButton* btnClose = new wxButton(this, wxID_OK, _("IDC_MESSAGE_CLOSE"));
	btnClose->SetDefault();

	// Sizers
	const ARBWin::CDlgPadding padding(this);

	wxBoxSizer* bSizer = new wxBoxSizer(wxVERTICAL);
	bSizer->Add(m_textCtrl, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, padding.Controls());
	bSizer->Add(btnClose, 0, wxALIGN_RIGHT | wxALL, padding.Controls());

	SetSizer(bSizer);
	Layout();
	GetSizer()->Fit(this);
	SetSizeHints(GetSize(), wxDefaultSize);
	CenterOnParent();

	btnClose->SetFocus();
}


void CDlgMessage::SetMessage(wxString const& msg)
{
	m_textCtrl->SetLabel(msg);
}


bool CDlgMessage::LoadFile(wxString const& filename)
{
	if (!wxFileName::Exists(filename))
		return false;

	return m_textCtrl->LoadFile(filename);
}

} // namespace ARBWin
} // namespace dconSoft
