/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief implementation of the CDlgFind class
 * @author David Connet
 *
 * Revision History
 * 2024-02-19 Added more options, made more configurable, moved to ARBWin
 * 2014-12-31 Changed pixels to dialog units.
 * 2012-02-16 Fix initial focus.
 * 2011-12-22 Switch to using Bind on wx2.9+.
 * 2009-01-26 Ported to wxWidgets.
 * 2003-12-27 Created
 */

#include "stdafx.h"
#include "LibARBWin/DlgFind.h"

#include "ARBCommon/StringUtil.h"
#include "LibARBWin/DlgPadding.h"
#include "LibARBWin/ReportListCtrl.h"
#include "LibARBWin/Widgets.h"
#include "fmt/xchar.h"
#include <wx/grid.h>

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>
#endif


namespace dconSoft
{
using namespace ARBCommon;
namespace ARBWin
{

void CFindCallback::AddSearchTerm(wxString const& value)
{
	auto found = std::find(m_previousSearch.begin(), m_previousSearch.end(), value);
	if (found == m_previousSearch.begin())
		return;
	if (found != m_previousSearch.end())
		m_previousSearch.erase(found);
	m_previousSearch.push_front(value);
}


bool CFindCallback::Compare(wxString const& value) const
{
	wxString search = MatchCase() ? Text() : Text().Lower();
	wxString name = MatchCase() ? value : value.Lower();

#pragma PRAGMA_TODO(Implement whole word search and regex)

	return wxNOT_FOUND != name.Find(search);
}

/////////////////////////////////////////////////////////////////////////////

CFindDataBase::CFindDataBase()
{
	// m_enableSearchAll = CFindCallback::Feature::Hidden;
}


int CFindDataBase::GetCurrent() const
{
	auto count = GetCount();
	if (0 == count)
		return wxNOT_FOUND;
	auto sel = GetSelection();
	if (wxNOT_FOUND == sel)
	{
		if (SearchDown())
			sel = 0;
		else
			sel = count - 1;
	}
	return sel;
}


int CFindDataBase::GetNext(int sel) const
{
	auto count = GetCount();
	if (0 == count)
		return wxNOT_FOUND;
	if (SearchDown())
		++sel;
	else
		--sel;
	if (0 > sel || sel >= count)
	{
		if (Wrap())
		{
#pragma PRAGMA_TODO(handle wrapping)
		}
		sel = wxNOT_FOUND;
	}
	return sel;
}


void CFindDataBase::NotFound() const
{
	auto msg = fmt::format(_("Cannot find '{}'").wc_str(), m_search.wc_str());
	wxMessageBox(msg, _("Find"), wxOK | wxCENTRE | wxICON_INFORMATION);
}

/////////////////////////////////////////////////////////////////////////////

int CFindDataList::GetCount() const
{
	return m_list ? m_list->GetItemCount() : 0;
}


int CFindDataList::GetSelection() const
{
	return m_list ? m_list->GetSelection(true) : wxNOT_FOUND;
}

/////////////////////////////////////////////////////////////////////////////

int CFindDataGrid::GetCount() const
{
	return m_count;
}


int CFindDataGrid::GetSelection() const
{
	if (!m_grid || 0 >= m_count)
		return wxNOT_FOUND;
	auto cell = m_grid->GetGridCursorCoords();
	auto sel = cell.GetRow();
	return 0 > sel ? wxNOT_FOUND : sel;
}

/////////////////////////////////////////////////////////////////////////////

CDlgFind::CDlgFind(CFindCallback& callback, wxWindow* pParent)
	: wxDialog()
	, m_Callback(callback)
	, m_trace("CDlgFind")
{
	wxString caption = m_Callback.GetCaption();
	if (caption.empty())
		caption = _("Find");
	wxString text = m_Callback.Text();

	Create(pParent, wxID_ANY, caption, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE);

	// Controls (these are done first to control tab order)

	wxStaticText* staticText = new wxStaticText(this, wxID_ANY, _("Find &what:"), wxDefaultPosition, wxDefaultSize, 0);
	staticText->Wrap(-1);

#pragma PRAGMA_TODO(change this to a combobox and load with m_previousSearch)
	m_textCtrl = new CTextCtrl(this, wxID_ANY, text, wxDefaultPosition, wxSize(wxDLG_UNIT_X(this, 150), -1), 0);
	m_textCtrl->Bind(wxEVT_COMMAND_TEXT_UPDATED, [this](wxCommandEvent& evt) {
		m_btnFind->Enable(0 < m_textCtrl->GetValue().length());
	});

	m_ctrlMatchCase = new wxCheckBox(this, wxID_ANY, _("Match &case"), wxDefaultPosition, wxDefaultSize, 0);
	m_ctrlMatchCase->SetValue(m_Callback.MatchCase());

	if (CFindCallback::Feature::Hidden != m_Callback.IsMatchWordEnabled())
	{
		m_ctrlMatchWord = new wxCheckBox(this, wxID_ANY, _("&Match whole word"), wxDefaultPosition, wxDefaultSize, 0);
		m_ctrlMatchWord->SetValue(m_Callback.MatchWord());
	}

	if (CFindCallback::Feature::Hidden != m_Callback.IsMatchWordEnabled())
	{
		m_ctrlRegex
			= new wxCheckBox(this, wxID_ANY, _("Use regular &expressions"), wxDefaultPosition, wxDefaultSize, 0);
		m_ctrlRegex->SetValue(m_Callback.Regex());
	}

	if (CFindCallback::Feature::Hidden != m_Callback.IsWrapEnabled())
	{
		m_ctrlWrap = new wxCheckBox(this, wxID_ANY, _("&Wrap around"), wxDefaultPosition, wxDefaultSize, 0);
		m_ctrlWrap->SetValue(m_Callback.Wrap());
	}

	if (CFindCallback::Feature::Hidden != m_Callback.IsSearchAllEnabled())
	{
		wxString radioSearchFields[] = {_("&All"), _("&Visible")};
		int radioSearchCount = sizeof(radioSearchFields) / sizeof(radioSearchFields[0]);
		m_radioBoxSearch = new wxRadioBox(
			this,
			wxID_ANY,
			_("Fields to search"),
			wxDefaultPosition,
			wxDefaultSize,
			radioSearchCount,
			radioSearchFields,
			1,
			wxRA_SPECIFY_COLS);
		m_radioBoxSearch->SetSelection(m_Callback.SearchAll() ? 0 : 1);
		if (CFindCallback::Feature::Normal != m_Callback.IsSearchAllEnabled())
			m_radioBoxSearch->Enable(false);
	}

	if (CFindCallback::Feature::Hidden != m_Callback.IsDirectionEnabled())
	{
		wxString radioDirectionFields[] = {_("&Up"), _("&Down")};
		int radioDirectionCount = sizeof(radioDirectionFields) / sizeof(radioDirectionFields[0]);
		m_radioBoxDir = new wxRadioBox(
			this,
			wxID_ANY,
			_("Direction"),
			wxDefaultPosition,
			wxDefaultSize,
			radioDirectionCount,
			radioDirectionFields,
			1,
			wxRA_SPECIFY_COLS);
		m_radioBoxDir->SetSelection(m_Callback.SearchDown() ? 1 : 0);
		if (CFindCallback::Feature::Normal != m_Callback.IsDirectionEnabled())
			m_radioBoxDir->Enable(false);
	}

	m_btnFind = new wxButton(this, wxID_ANY, _("&Find"), wxDefaultPosition, wxDefaultSize, 0);
	m_btnFind->SetDefault();
	m_btnFind->Enable(0 < text.length());
	m_btnFind->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this](wxCommandEvent& evt) {
		m_Callback.Text(m_textCtrl->GetValue());
		m_Callback.MatchCase(m_ctrlMatchCase->GetValue());
		if (m_ctrlMatchWord)
			m_Callback.MatchWord(m_ctrlMatchWord->GetValue());
		if (m_ctrlRegex)
			m_Callback.Regex(m_ctrlRegex->GetValue());
		if (m_ctrlWrap)
			m_Callback.Wrap(m_ctrlWrap->GetValue());
		if (m_radioBoxSearch)
			m_Callback.SearchAll(m_radioBoxSearch->GetSelection() == 0);
		if (m_radioBoxDir)
			m_Callback.SearchDown(m_radioBoxDir->GetSelection() == 1);
		if (m_Callback.Search(this))
			m_Callback.AddSearchTerm(m_Callback.Text());
		m_btnFind->SetLabel(_("&Find Next"));
	});

	// There's no cancel button, so specifically enable Esc.
	Bind(wxEVT_CHAR_HOOK, [this](wxKeyEvent& evt) {
		if (evt.GetKeyCode() == WXK_ESCAPE)
			EndModal(0);
		else
			evt.Skip();
	});

	// Sizers
	const CDlgPadding padding(this);

	wxBoxSizer* bSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* sizerWhat = new wxBoxSizer(wxHORIZONTAL);
	sizerWhat->Add(staticText, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, padding.Inner());
	sizerWhat->Add(m_textCtrl, 1, wxALIGN_CENTER_VERTICAL);

	bSizer->Add(sizerWhat, 0, wxEXPAND | wxALL, padding.Controls());

	wxBoxSizer* sizerOptions = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* sizerChecks = new wxBoxSizer(wxVERTICAL);
	sizerChecks->Add(m_ctrlMatchCase);
	if (m_ctrlMatchWord)
		sizerChecks->Add(m_ctrlMatchWord, 0, wxTOP, padding.Controls());
	if (m_ctrlRegex)
		sizerChecks->Add(m_ctrlRegex, 0, wxTOP, padding.Controls());
	if (m_ctrlWrap)
		sizerChecks->Add(m_ctrlWrap, 0, wxTOP, padding.Controls());

	sizerOptions->Add(sizerChecks, 0, wxLEFT | wxBOTTOM | wxRIGHT, padding.Controls());
	if (m_radioBoxSearch)
		sizerOptions->Add(m_radioBoxSearch, 0, wxRIGHT | wxBOTTOM, padding.Controls());
	if (m_radioBoxDir)
		sizerOptions->Add(m_radioBoxDir, 0, wxRIGHT | wxBOTTOM, padding.Controls());
	bSizer->Add(sizerOptions);

	wxBoxSizer* bSizerBtns = new wxBoxSizer(wxHORIZONTAL);
	bSizerBtns->AddStretchSpacer();
	bSizerBtns->Add(m_btnFind);

	bSizer->Add(bSizerBtns, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, padding.Controls());

	SetSizer(bSizer);
	Layout();
	GetSizer()->Fit(this);
	CenterOnParent();

	IMPLEMENT_ON_INIT(CDlgFind, m_textCtrl)
}

} // namespace ARBWin
} // namespace dconSoft
