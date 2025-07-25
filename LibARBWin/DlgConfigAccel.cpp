/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Data-driven helper to create menus and toolbar items.
 * @author David Connet
 *
 * Revision History
 * 2019-03-05 Moved out of MenuHelper.cpp
 */

#include "stdafx.h"
#include "DlgConfigAccel.h"

#include "LibARBWin/DlgPadding.h"
#include "LibARBWin/ListData.h"
#include "LibARBWin/MenuHelper.h"
#include "LibARBWin/ReportListCtrl.h"
#include "LibARBWin/Validators.h"
#include <wx/utils.h>
#include <set>

#if defined(__WXMSW__)
#include <wx/msw/msvcrt.h>
#endif


namespace dconSoft
{
using namespace ARBCommon;
namespace ARBWin
{

namespace
{

wxString GetKeyCode(std::unordered_map<int, KeyCodeMapping> const& keyMap, int code)
{
	wxString text;
	auto key = keyMap.find(code);

	if (key != keyMap.end())
		text = wxGetTranslation(key->second.special);
	else if (isascii(code))
		text << static_cast<wxChar>(code);

	return text;
}


wxString TrimDots(wxString const& str)
{
	wxString s(str);
	if (s.length() > 3)
	{
		if (s.substr(s.length() - 3) == L"...")
			s = s.substr(0, s.length() - 3);
	}
	return s;
}

} // namespace


class CDlgEditAccel : public wxDialog
{
public:
	CDlgEditAccel(
		std::vector<CMenuHelper::ItemAccel> const& accelData,
		CMenuHelper::ItemAccel const& item,
		std::unordered_map<int, KeyCodeMapping> const& keyMap,
		wxString const& action,
		bool bAllowDups,
		wxWindow* pParent);

	bool GetData(CMenuHelper::ItemAccel& item);

private:
	void OnKeyDown(wxKeyEvent& evt);
	void OnClear(wxCommandEvent& evt);
	void OnOk(wxCommandEvent& evt);

	std::vector<CMenuHelper::ItemAccel> const& m_accelData;
	CMenuHelper::ItemAccel m_item;
	std::unordered_map<int, KeyCodeMapping> const& m_keyMap;
	bool m_bAllowDups;
	wxTextCtrl* m_ctrlKey;
};

/////////////////////////////////////////////////////////////////////////////

CDlgEditAccel::CDlgEditAccel(
	std::vector<CMenuHelper::ItemAccel> const& accelData,
	CMenuHelper::ItemAccel const& item,
	std::unordered_map<int, KeyCodeMapping> const& keyMap,
	wxString const& action,
	bool bAllowDups,
	wxWindow* pParent)
	: m_accelData(accelData)
	, m_item(item)
	, m_keyMap(keyMap)
	, m_bAllowDups(bAllowDups)
	, m_ctrlKey(nullptr)
{
	wxString caption = wxString::Format(L"%s : %s", _("Assign Key"), action);
	Create(pParent, wxID_ANY, caption, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE);

	wxStaticText* textKey = new wxStaticText(this, wxID_ANY, _("Key:"), wxDefaultPosition, wxDefaultSize, 0);

	m_ctrlKey = new wxTextCtrl(
		this,
		wxID_ANY,
		GetKeyCode(m_keyMap, m_item.keyCode),
		wxDefaultPosition,
		wxDLG_UNIT(this, wxSize(30, -1)),
		0);
	m_ctrlKey->Bind(wxEVT_KEY_DOWN, &CDlgEditAccel::OnKeyDown, this);

	wxStaticText* textMod = new wxStaticText(this, wxID_ANY, _("Modifiers:"), wxDefaultPosition, wxDefaultSize, 0);

	wxCheckBox* ctrlCtrl = new wxCheckBox(
		this,
		wxID_ANY,
		_("Ctrl"),
		wxDefaultPosition,
		wxDefaultSize,
		0,
		wxGenericValidator(&m_item.bCtrl));

	wxCheckBox* ctrlAlt = new wxCheckBox(
		this,
		wxID_ANY,
		_("Alt"),
		wxDefaultPosition,
		wxDefaultSize,
		0,
		wxGenericValidator(&m_item.bAlt));

	wxCheckBox* ctrlShift = new wxCheckBox(
		this,
		wxID_ANY,
		_("Shift"),
		wxDefaultPosition,
		wxDefaultSize,
		0,
		wxGenericValidator(&m_item.bShift));

	wxButton* ctrlClear = new wxButton(this, wxID_ANY, _("Clear"), wxDefaultPosition, wxDefaultSize, 0);
	ctrlClear->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &CDlgEditAccel::OnClear, this);

	// Sizers
	const ARBWin::CDlgPadding padding(this);

	wxBoxSizer* bSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* sizerModifiers = new wxBoxSizer(wxHORIZONTAL);
	sizerModifiers->Add(ctrlCtrl, 0, wxRIGHT, padding.Inner());
	sizerModifiers->Add(ctrlAlt, 0, wxRIGHT, padding.Inner());
	sizerModifiers->Add(ctrlShift);

	wxFlexGridSizer* sizerCtrls = new wxFlexGridSizer(2, 2, padding.Inner(), padding.Inner());
	sizerCtrls->AddGrowableCol(1);
	sizerCtrls->SetFlexibleDirection(wxBOTH);
	sizerCtrls->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
	sizerCtrls->Add(textKey, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 0);
	sizerCtrls->Add(m_ctrlKey, 0, wxALIGN_CENTER_VERTICAL | wxEXPAND, 0);
	sizerCtrls->Add(textMod, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 0);
	sizerCtrls->Add(sizerModifiers, 0, wxALIGN_CENTER_VERTICAL, 0);

	bSizer->Add(sizerCtrls, 0, wxLEFT | wxRIGHT | wxTOP, padding.Controls());
	bSizer->Add(ctrlClear, 0, wxALIGN_RIGHT | wxALL, padding.Controls());

	wxSizer* sdbSizer = CreateSeparatedButtonSizer(wxOK | wxCANCEL);
	bSizer->Add(sdbSizer, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, padding.ButtonSizer());

	Bind(wxEVT_COMMAND_BUTTON_CLICKED, &CDlgEditAccel::OnOk, this, wxID_OK);

	SetSizer(bSizer);
	Layout();
	GetSizer()->Fit(this);
	SetSizeHints(GetSize(), wxDefaultSize);
	CenterOnParent();

	IMPLEMENT_ON_INIT(m_ctrlKey)
}


bool CDlgEditAccel::GetData(CMenuHelper::ItemAccel& item)
{
	item = m_item;
	return true;
}


void CDlgEditAccel::OnKeyDown(wxKeyEvent& evt)
{
	wxString text = GetKeyCode(m_keyMap, evt.GetKeyCode());
	if (!text.IsEmpty())
	{
		m_item.keyCode = evt.GetKeyCode();
		m_ctrlKey->ChangeValue(text);
	}
}


void CDlgEditAccel::OnClear(wxCommandEvent& evt)
{
	m_item.Clear();
	m_ctrlKey->Clear();
	TransferDataToWindow();
}


void CDlgEditAccel::OnOk(wxCommandEvent& evt)
{
	if (!Validate() || !TransferDataFromWindow())
		return;
	if (!m_bAllowDups)
	{
		std::set<std::pair<int, long>> accels;

		long mask = CMenuHelper::ToBitmask(m_item);
		accels.insert(std::make_pair(m_item.keyCode, mask));

		for (auto iter = m_accelData.begin(); iter != m_accelData.end(); ++iter)
		{
			if (iter->keyCode != 0 && *iter != m_item)
			{
				mask = CMenuHelper::ToBitmask(*iter);
				auto accel = std::make_pair(iter->keyCode, mask);
				if (accels.find(accel) != accels.end())
				{
					wxMessageBox(
						_("ERROR: This accelerator is already in use."),
						_("Assign Key"),
						wxOK | wxCENTRE | wxICON_STOP);
					return;
				}
			}
		}
	}

	EndDialog(wxID_OK);
}

/////////////////////////////////////////////////////////////////////////////

ARB_TYPEDEF(CMenuData)
class CMenuData : public CListData
{
public:
	CMenuData(
		std::unordered_map<int, KeyCodeMapping> const& keyMap,
		std::vector<CMenuHelper::ItemAccel> const& accels,
		wxString const& path,
		wxString const& item,
		wxString const& location,
		int order)
		: m_keyMap(keyMap)
		, m_accels(accels)
		, m_path(path)
		, m_item(item)
		, m_location(location)
		, m_order(order)
	{
	}

	int OnCompare(CListDataPtr const& item, long iCol) const override
	{
		CMenuDataPtr pRow2 = std::dynamic_pointer_cast<CMenuData, CListData>(item);
		if (!pRow2)
			return 0;

		int o1 = GetSortOrder(iCol);
		int o2 = pRow2->GetSortOrder(iCol);
		int nRet = 0;
		if (o1 < o2)
			nRet = -1;
		else if (o1 > o2)
			nRet = 1;
		return nRet;
	}

	wxString OnNeedText(long iCol) const override
	{
		wxString str;
		switch (iCol)
		{
		case 0:
			if (0 < m_accels.size())
			{
				for (size_t i = 0; i < m_accels.size(); ++i)
				{
					if (0 < i)
						str << L", ";
					if (m_accels[i].bCtrl)
						str << _("Ctrl+");
					if (m_accels[i].bAlt)
						str << _("Alt+");
					if (m_accels[i].bShift)
						str << _("Shift+");
					str << GetKeyCode(m_keyMap, m_accels[i].keyCode);
				}
			}
			break;
		case 1:
			str = m_path;
			break;
		case 2:
			str = m_location;
			break;
		default:
			assert(0);
		}
		return str;
	}

	std::vector<CMenuHelper::ItemAccel> const& Accels() const
	{
		return m_accels;
	}

	void ClearAccels()
	{
		for (CMenuHelper::ItemAccel& item : m_accels)
			item.Clear();
	}

	int GetSortOrder(int inCol) const
	{
		int order = 0;
		switch (inCol)
		{
		default:
			break;
		case 0:
			order = m_accels.empty() ? 0 : m_accels[0].keyCode;
			break;
		case 1:
			order = m_order;
			break;
		}
		return order;
	}

	bool Configure(std::vector<CMenuHelper::ItemAccel> const& accelData, bool bAdd, bool bAllowDups, wxWindow* pParent)
	{
		assert(m_accels.size() > 0);

		bool bUpdated = false;
		CMenuHelper::ItemAccel item;
		if (bAdd)
		{
			bool bFoundEmpty = false;
			for (CMenuHelper::ItemAccel const& i : m_accels)
			{
				if (!i.keyCode)
				{
					item = i;
					bFoundEmpty = true;
					break;
				}
			}
			if (!bFoundEmpty)
				return bUpdated;
		}
		else
		{
#pragma PRAGMA_TODO(handle selecting from multiple items)
			item = m_accels[0];
		}

		CDlgEditAccel dlg(accelData, item, m_keyMap, m_item, bAllowDups, pParent);
		if (wxID_OK == dlg.ShowModal())
		{
			dlg.GetData(item);
			for (CMenuHelper::ItemAccel& i : m_accels)
			{
				if (i.key == item.key)
					i = item;
			}
			bUpdated = true;
		}
		return bUpdated;
	}

	int Id() const
	{
		if (m_accels.size() == 0)
			return 0;
		return m_accels[0].id;
	}

	void CopyFrom(CMenuDataPtr pItem)
	{
		m_accels = pItem->m_accels;
	}

private:
	std::unordered_map<int, KeyCodeMapping> const& m_keyMap;
	std::vector<CMenuHelper::ItemAccel> m_accels;
	wxString m_path;
	wxString m_item;
	wxString m_location;
	int m_order;
};

/////////////////////////////////////////////////////////////////////////////

CDlgConfigAccel::CDlgConfigAccel(
	std::unordered_map<int, wxString> const& menuIds,
	std::vector<CMenuHelper::ItemAccel> const& accelData,
	std::vector<CMenuHelper::ItemAccel> const& accelDataDefaults,
	bool bAllowDups,
	std::vector<CMenuHelper::ItemData> const& menuItems,
	std::unordered_map<int, KeyCodeMapping> const& keyMap,
	wxWindow* pParent,
	wxString caption)
	: m_menuIds(menuIds)
	, m_accelDataDefaults(accelDataDefaults)
	, m_bAllowDups(bAllowDups)
	, m_menuItems()
	, m_accelData(accelData)
	, m_keyMap(keyMap)
	, m_reportColumn()
	, m_ctrlItems(nullptr)
	, m_ctrlNew(nullptr)
	, m_ctrlEdit(nullptr)
	, m_ctrlClear(nullptr)
{
	{
		std::vector<wxString> path;
		path.push_back(TrimDots(wxStripMenuCodes(wxGetTranslation(menuItems[0].menu))));

		for (size_t i = 1; i < menuItems.size(); ++i)
		{
			while (path.size() > menuItems[i].menuLevel)
				path.pop_back();

			wxString menuItem = TrimDots(wxStripMenuCodes(wxGetTranslation(menuItems[i].menu)));
			path.push_back(menuItem);

			wxString data;
			for (size_t n = 0; n < path.size(); ++n)
			{
				if (0 == n)
					data << path[n];
				else
					data << L" | " << path[n];
			}

			MenuData menudata;
			menudata.m_data = &menuItems[i];
			menudata.m_path = data;
			menudata.m_item = menuItem;
			m_menuItems.push_back(menudata);
		}
	}

	if (caption.empty())
		caption = _("Configure Keyboard Shortcuts");
	Create(pParent, wxID_ANY, caption, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER);

	// Controls (these are done first to control tab order)

	m_ctrlItems = new CReportListCtrl(
		this,
		wxDefaultPosition,
		wxDLG_UNIT(this, wxSize(250, 150)),
		true,
		CReportListCtrl::SortHeader::Sort,
		true,
		false);
	m_ctrlItems->Bind(wxEVT_COMMAND_LIST_ITEM_SELECTED, &CDlgConfigAccel::OnItemSelected, this);
	m_ctrlItems->Bind(wxEVT_COMMAND_LIST_ITEM_ACTIVATED, &CDlgConfigAccel::OnItemActivated, this);
	m_ctrlItems->Bind(wxEVT_KEY_DOWN, &CDlgConfigAccel::OnKeyDown, this);

	std::vector<CReportListHeader::ColumnInfo> columns;
	columns.push_back(CReportListHeader::ColumnInfo{0, wxLIST_FORMAT_LEFT, arbT("Keyboard Shortcut")});
	columns.push_back(CReportListHeader::ColumnInfo{1, wxLIST_FORMAT_LEFT, arbT("Description")});
	if (!menuIds.empty())
		columns.push_back(CReportListHeader::ColumnInfo{2, wxLIST_FORMAT_LEFT, arbT("Location")});
	m_reportColumn.Initialize(this, m_ctrlItems);
	m_reportColumn.CreateColumns(columns);
	LoadData();

	m_ctrlNew = new wxButton(this, wxID_ANY, _("New..."), wxDefaultPosition, wxDefaultSize, 0);
	m_ctrlNew->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &CDlgConfigAccel::OnAddItem, this);

	m_ctrlEdit = new wxButton(this, wxID_ANY, _("Edit..."), wxDefaultPosition, wxDefaultSize, 0);
	m_ctrlEdit->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &CDlgConfigAccel::OnEditItem, this);

	m_ctrlClear = new wxButton(this, wxID_ANY, _("Clear"), wxDefaultPosition, wxDefaultSize, 0);
	m_ctrlClear->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &CDlgConfigAccel::OnClearItem, this);

	wxButton* ctrlDefaults = new wxButton(this, wxID_ANY, _("Set Defaults"), wxDefaultPosition, wxDefaultSize, 0);
	ctrlDefaults->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &CDlgConfigAccel::OnSetDefaults, this);

	// Sizers
	const ARBWin::CDlgPadding padding(this);

	wxBoxSizer* bSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* sizerItems = new wxBoxSizer(wxHORIZONTAL);
	sizerItems->Add(m_ctrlItems, 1, wxEXPAND | wxRIGHT, padding.Controls());

	wxBoxSizer* sizerBtns = new wxBoxSizer(wxVERTICAL);
	sizerBtns->Add(m_ctrlNew, 0, wxEXPAND | wxBOTTOM, padding.Inner());
	sizerBtns->Add(m_ctrlEdit, 0, wxEXPAND | wxBOTTOM, padding.Inner());
	sizerBtns->Add(m_ctrlClear, 0, wxEXPAND | wxBOTTOM, padding.Inner());
	sizerBtns->Add(ctrlDefaults, 0, wxEXPAND);

	sizerItems->Add(sizerBtns, 0, wxEXPAND);

	bSizer->Add(sizerItems, 1, wxEXPAND | wxALL, padding.Controls());

	wxSizer* sdbSizer = CreateSeparatedButtonSizer(wxOK | wxCANCEL);
	bSizer->Add(sdbSizer, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, padding.ButtonSizer());

	Bind(wxEVT_COMMAND_BUTTON_CLICKED, &CDlgConfigAccel::OnOk, this, wxID_OK);

	SetSizer(bSizer);
	Layout();
	GetSizer()->Fit(this);
	SetSizeHints(GetSize(), wxDefaultSize);
	CenterOnParent();

	UpdateControls();
}


bool CDlgConfigAccel::GetAccelData(std::vector<CMenuHelper::ItemAccel>& accelData)
{
	if (accelData.size() == m_accelData.size())
	{
		std::vector<CMenuHelper::ItemAccel> v1(m_accelData);
		std::vector<CMenuHelper::ItemAccel> v2(accelData);
		std::sort(v1.begin(), v1.end(), [](CMenuHelper::ItemAccel const& one, CMenuHelper::ItemAccel const& two) {
			return one.key < two.key;
		});
		std::sort(v2.begin(), v2.end(), [](CMenuHelper::ItemAccel const& one, CMenuHelper::ItemAccel const& two) {
			return one.key < two.key;
		});
		bool bModified = false;
		for (size_t i = 0; !bModified && i < v1.size(); ++i)
		{
			if (v1[i] != v2[i])
				bModified = true;
		}
		if (!bModified)
			return false;
	}
	accelData = m_accelData;
	return true;
}


void CDlgConfigAccel::LoadData()
{
	m_ctrlItems->Freeze();

	m_ctrlItems->DeleteAllItems();
	int lastMenuId = -1;
#if defined(_DEBUG) || defined(__WXDEBUG__)
	std::set<int> inUseId;
	std::set<int> inUseMenuId;
#endif
	int count = 0;
	for (size_t i = 0; i < m_menuItems.size(); ++i)
	{
		if (m_menuItems[i].m_data->id && !(m_menuItems[i].m_data->flags & MENU_MRU))
		{
			std::vector<CMenuHelper::ItemAccel> accels;

			// Add a blank line between menus.
			if (lastMenuId != m_menuItems[i].m_data->menuId)
			{
				lastMenuId = m_menuItems[i].m_data->menuId;
				if (m_ctrlItems->GetItemCount() > 0)
					m_ctrlItems->InsertItem(
						std::make_shared<CMenuData>(m_keyMap, accels, wxString(), wxString(), wxString(), -1));
			}

#if defined(_DEBUG) || defined(__WXDEBUG__)
			inUseId.insert(m_menuItems[i].m_data->id);
			auto iterMenuId = inUseMenuId.find(m_menuItems[i].m_data->menuId);
			// Make sure we have a description for each menu.
			if (iterMenuId == inUseMenuId.end())
			{
				inUseMenuId.insert(m_menuItems[i].m_data->menuId);
				if (m_menuIds.size() == 0)
					assert(inUseMenuId.size() == 1);
				else
					assert(m_menuIds.find(m_menuItems[i].m_data->menuId) != m_menuIds.end());
			}
#endif

			// Support for multiple accelerators for an id (like copy: Ctrl+C/Ctrl+Ins)
			for (size_t n = 0; n < m_accelData.size(); ++n)
			{
				if (m_accelData[n].id == m_menuItems[i].m_data->id)
				{
					accels.push_back(m_accelData[n]);
				}
			}
			// This means you forgot to add the ItemData to the ItemAccel array.
			// (all menu items must be represented in the accel array)
			assert(accels.size() > 0);

			auto menuStr = m_menuIds.find(m_menuItems[i].m_data->menuId);
			wxString location;
			if (menuStr != m_menuIds.end())
				location = menuStr->second;
			m_ctrlItems->InsertItem(
				std::make_shared<
					CMenuData>(m_keyMap, accels, m_menuItems[i].m_path, m_menuItems[i].m_item, location, count++));
		}
	}
#if defined(_DEBUG) || defined(__WXDEBUG__)
	// Sanity checking
	// All the accelerators must be in a menu (can't get the text otherwise)
	for (CMenuHelper::ItemAccel const& item : m_accelData)
	{
		if (inUseId.find(item.id) == inUseId.end())
		{
			assert(0); // For now, we don't support independent accel items
			inUseId.insert(item.id);
		}
	}
#endif

	m_reportColumn.SizeColumns();
	m_reportColumn.Sort();

	m_ctrlItems->Thaw();
}


void CDlgConfigAccel::UpdateControls()
{
	long idx = m_ctrlItems->GetSelection(true);
	bool bEnableNew = false;
	bool bEnableEdit = (0 <= idx);
	bool bHasAccel = false;
	if (0 <= idx)
	{
		CMenuDataPtr pData = std::dynamic_pointer_cast<CMenuData, CListData>(m_ctrlItems->GetData(idx));
		size_t nConfigured = 0;
		for (CMenuHelper::ItemAccel const& item : pData->Accels())
		{
			if (item.keyCode)
			{
				++nConfigured;
			}
		}
		bEnableNew = (nConfigured < pData->Accels().size());
		bHasAccel = (nConfigured > 0);
	}

	m_ctrlNew->Enable(bEnableNew);
	m_ctrlEdit->Enable(bEnableEdit);
	m_ctrlClear->Enable(bHasAccel);
}


void CDlgConfigAccel::DoEdit(bool bAdd)
{
	long idx = m_ctrlItems->GetSelection(true);
	if (0 > idx)
		return;
	CMenuDataPtr pData = std::dynamic_pointer_cast<CMenuData, CListData>(m_ctrlItems->GetData(idx));
	if (pData->Configure(m_accelData, bAdd, m_bAllowDups, this))
	{
		std::vector<long> sameItemsIdx;
		for (long item = 0; item < m_ctrlItems->GetItemCount(); ++item)
		{
			CMenuDataPtr pItem = std::dynamic_pointer_cast<CMenuData, CListData>(m_ctrlItems->GetData(item));
			if (pItem->Id() == pData->Id())
			{
				if (item != idx)
					pItem->CopyFrom(pData);
				sameItemsIdx.push_back(item);
			}
		}

		for (long item : sameItemsIdx)
			m_ctrlItems->RefreshItem(item);
		UpdateControls();
	}
}


void CDlgConfigAccel::OnItemSelected(wxListEvent& evt)
{
	UpdateControls();
}


void CDlgConfigAccel::OnItemActivated(wxListEvent& evt)
{
	DoEdit(false);
}


void CDlgConfigAccel::OnKeyDown(wxKeyEvent& evt)
{
	switch (evt.GetKeyCode())
	{
	default:
		evt.Skip();
		break;
	case WXK_SPACE:
	case WXK_NUMPAD_SPACE:
		DoEdit(false);
		break;
	}
}


void CDlgConfigAccel::OnAddItem(wxCommandEvent& evt)
{
	DoEdit(true);
}


void CDlgConfigAccel::OnEditItem(wxCommandEvent& evt)
{
	DoEdit(false);
}


void CDlgConfigAccel::OnClearItem(wxCommandEvent& evt)
{
	long idx = m_ctrlItems->GetSelection(true);
	if (0 > idx)
		return;
	CMenuDataPtr pData = std::dynamic_pointer_cast<CMenuData, CListData>(m_ctrlItems->GetData(idx));

	pData->ClearAccels();
	m_ctrlItems->RefreshItem(idx);
	UpdateControls();
	m_ctrlItems->SetFocus();
}


void CDlgConfigAccel::OnSetDefaults(wxCommandEvent& evt)
{
	m_accelData = m_accelDataDefaults;
	LoadData();
	UpdateControls();
}


void CDlgConfigAccel::OnOk(wxCommandEvent& evt)
{
	m_accelData.clear();
	for (long idx = 0; idx < m_ctrlItems->GetItemCount(); ++idx)
	{
		CMenuDataPtr pData = std::dynamic_pointer_cast<CMenuData, CListData>(m_ctrlItems->GetData(idx));
		for (CMenuHelper::ItemAccel const& item : pData->Accels())
		{
			if (std::find(m_accelData.begin(), m_accelData.end(), item) == m_accelData.end())
				m_accelData.push_back(item);
		}
	}
	EndDialog(wxID_OK);
}

} // namespace ARBWin
} // namespace dconSoft
