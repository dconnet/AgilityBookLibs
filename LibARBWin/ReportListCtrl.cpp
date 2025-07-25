/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Make selection in a listctrl easier.
 * @author David Connet
 *
 * Revision History
 * 2022-04-15 Use wx DPI support.
 * 2021-09-09 Add support for EnableCheckBoxes.
 * 2020-12-11 Moved to ReportListCtrl.cpp
 * 2020-12-07 Add a generic way to handle sorting/moving columns.
 * 2020-12-05 In SetColumnSort, always set the icon.
 * 2020-01-27 Add option for row coloring.
 * 2019-05-17 Enable alternate row coloring.
 * 2018-10-11 Moved to Win LibARBWin
 * 2011-12-22 Switch to using Bind on wx2.9+.
 * 2010-03-28 Moved SetColumnWidth override to CListCtrl.
 * 2009-09-13 Add support for wxWidgets 2.9, deprecate tstring.
 * 2009-01-06 Ported to wxWidgets.
 * 2008-02-20 Added subitem editing to lists.
 * 2007-02-26 Fix a problem redrawing list columns.
 * 2006-02-16 Cleaned up memory usage with smart pointers.
 * 2005-06-30 Allow restricted selection in multi-select lists.
 * 2004-10-04 Added div-by-0 tests.
 * 2004-09-16 Override SetColumnWidth to auto-fix tooltip rectangles.
 * 2004-09-09 Added tooltips to header control.
 * 2004-09-03 Using the sort icon forced alignment to left.
 * 2004-08-26 Added GetPrintLine to CListCtrl2.
 * 2003-11-22 When copying, only create a header if more than 1 line
 *            is selected (or if only one line exists).
 * 2003-11-21 Added multi-select and copy/selectall support.
 */

#include "stdafx.h"
#include "LibARBWin/ReportListCtrl.h"

#include "LibARBWin/ARBWinUtilities.h"
#include "LibARBWin/ImageHelperBase.h"
#include "LibARBWin/ListData.h"
#include "LibARBWin/ResourceManager.h"

#if defined(__WXMSW__)
#include <wx/msw/msvcrt.h>
#endif


namespace dconSoft
{
namespace ARBWin
{

namespace
{
void PushData(wxString& data, CReportListCtrl const* ctrl, int item, bool bBold)
{
	data << L"<tr>";
	std::vector<wxString> line;
	ctrl->GetPrintLine(item, line);
	for (auto const& i : line)
	{
		if (bBold)
			data << L"<td><strong>" << i << L"</strong></td>\n";
		else
			data << L"<td>" << i << L"</td>\n";
	}
	data << L"</tr>\n";
}
} // namespace


bool CReportListCtrl::m_enableRowColors = true;

// Note to self: If this is immediately after includes, doxygen throws a hissy fit.
wxIMPLEMENT_CLASS(CReportListCtrl, CListCtrl)


void CReportListCtrl::EnableRowColors(bool bEnable)
{
	m_enableRowColors = bEnable;
}


CReportListCtrl::CReportListCtrl(
	wxWindow* parent,
	bool bSingleSel,
	SortHeader sortHeader,
	bool bHasBorder,
	bool bHasImageList)
	: CListCtrl()
	, m_ImageList()
	, m_imgEmpty(-1)
{
	Create(
		parent,
		wxDefaultPosition,
		wxDefaultSize,
		bSingleSel,
		sortHeader,
		bHasBorder,
		bHasImageList,
		m_enableRowColors);
}


CReportListCtrl::CReportListCtrl(
	wxWindow* parent,
	const wxPoint& pos,
	const wxSize& size,
	bool bSingleSel,
	SortHeader sortHeader,
	bool bHasBorder,
	bool bHasImageList)
	: CListCtrl()
	, m_ImageList()
	, m_imgEmpty(-1)
{
	Create(parent, pos, size, bSingleSel, sortHeader, bHasBorder, bHasImageList, m_enableRowColors);
}


void CReportListCtrl::UpdateAlternateRowColor(bool enable)
{
	// Note EnableAlternateRowColours(bool) currently (as of 3.3.0) uses a value of '150'
	// in dark mode. This is quite jarring.
	if (enable)
	{
		// So for now, directly set the row color.
		const wxColour bgColour = GetBackgroundColour();
		// The only difference on this line is s/150/110/ .
		int alpha = bgColour.GetRGB() > 0x808080 ? 97 : 110;
		SetAlternateRowColour(bgColour.ChangeLightness(alpha));
	}
	else
		EnableAlternateRowColours(enable);
}


bool CReportListCtrl::Create(
	wxWindow* parent,
	const wxPoint& pos,
	const wxSize& size,
	bool bSingleSel,
	SortHeader sortHeader,
	bool bHasBorder,
	bool bHasImageList,
	bool bEnableRowColors)
{
	long style = wxLC_REPORT | wxLC_VIRTUAL | (bSingleSel ? wxLC_SINGLE_SEL : 0)
				 | ((sortHeader == SortHeader::Sort)     ? 0
					: (sortHeader == SortHeader::NoSort) ? wxLC_NO_SORT_HEADER
														 : wxLC_NO_HEADER)
				 | (bHasBorder ? wxBORDER : wxNO_BORDER);

	if (!CListCtrl::Create(parent, wxID_ANY, pos, size, style))
	{
		return false;
	}

	UpdateAlternateRowColor(bEnableRowColors);

	Bind(wxEVT_COMMAND_LIST_DELETE_ALL_ITEMS, &CReportListCtrl::OnDeleteAllItems, this);
	Bind(wxEVT_COMMAND_LIST_DELETE_ITEM, &CReportListCtrl::OnDeleteItem, this);

	// Make the blank one the 1st icon so if an icon isn't set in a list
	// it will use this by default
	if (bHasImageList)
	{
		m_ImageList.Create(FromDIP(16), FromDIP(16));
		m_imgEmpty = m_ImageList.Add(CResourceManager::Get()->GetIcon(ImageMgrBlank));
		CListCtrl::SetImageList(&m_ImageList, wxIMAGE_LIST_SMALL);
	}
	return true;
}

wxItemAttr* CReportListCtrl::OnGetItemAttr(long item) const
{
	return CListCtrl::OnGetItemAttr(item);
}


wxItemAttr* CReportListCtrl::OnGetItemColumnAttr(long item, long column) const
{
#if defined(__WXMSW__)
	// Only defined in the MSW and QT ports
	return CListCtrl::OnGetItemColumnAttr(item, column);
#else
	return nullptr;
#endif
}


int CReportListCtrl::OnGetItemColumnImage(long item, long column) const
{
	int index = -1;
	if (0 <= item && item < static_cast<long>(m_items.size()))
	{
		wxListItem info;
		m_items[item]->OnNeedListItem(column, info);
		if (info.GetMask() & wxLIST_MASK_IMAGE)
			index = info.GetImage();
	}
	return index;
}


int CReportListCtrl::OnGetItemImage(long item) const
{
	return OnGetItemColumnImage(item, 0);
}


wxString CReportListCtrl::OnGetItemText(long item, long column) const
{
	wxString text;
	if (0 <= item && item < static_cast<long>(m_items.size()))
	{
		wxListItem info;
		m_items[item]->OnNeedListItem(column, info);
		if (info.GetMask() & wxLIST_MASK_TEXT)
			text = info.GetText();
	}
	return text;
}


bool CReportListCtrl::OnGetItemIsChecked(long item) const
{
	return 0 <= item && item < static_cast<long>(m_items.size()) && m_items[item]->OnNeedCheck();
}


void CReportListCtrl::SetColumnSort(long column, int iconDirection)
{
	if (iconDirection > 0)
		ShowSortIndicator(column, true);
	else if (iconDirection < 0)
		ShowSortIndicator(column, false);
	else if (iconDirection == 0)
		ShowSortIndicator(-1);
}


bool CReportListCtrl::SortItems(CListCtrlCompare fnSortCallBack, SortInfo const* pSortInfo)
{
	// Since the underlaying control doesn't know that we changed item order,
	// we need to specifically get the selection and reset it after the sort.

	// Get old selection, clear it.
	long itemFocus = GetFocusedItem();
	std::vector<long> items;
	GetSelection(items);
	ClearSelection();

	// Translate selection indices to data pointers.
	std::vector<CListDataPtr> realItems;
	for (auto const& item : items)
		realItems.push_back(GetData(item));
	CListDataPtr pFocusItem = itemFocus >= 0 ? GetData(itemFocus) : nullptr;

	std::stable_sort(
		m_items.begin(),
		m_items.end(),
		[fnSortCallBack, pSortInfo](CListDataPtr const& one, CListDataPtr const& two) {
			return fnSortCallBack(one, two, pSortInfo) < 0;
		});

	// Now, restore selection/focus.
	items.clear();
	for (long index = 0; index < GetItemCount(); ++index)
	{
		CListDataPtr data = GetData(index);
		if (pFocusItem && pFocusItem == data)
			Focus(index);
		for (auto const& item : realItems)
		{
			if (item == data)
			{
				items.push_back(index);
				break;
			}
		}
	}
	SetSelection(items);

	Refresh();
	return true;
}


long CReportListCtrl::InsertItem(CListDataPtr const& inData)
{
	return InsertItem(GetItemCount(), inData);
}


long CReportListCtrl::InsertItem(long index, CListDataPtr const& inData)
{
	long item = -1;

	if (inData)
	{
		if (static_cast<long>(m_items.size()) <= index)
		{
			item = static_cast<long>(m_items.size());
			m_items.push_back(inData);
		}
		else
		{
			if (index < 0)
				index = 0;
			item = index;
			m_items.insert(m_items.begin() + index, inData);
		}
		SetItemCount(static_cast<long>(m_items.size()));
		Refresh();
	}

	return item;
}


bool CReportListCtrl::CanSelectAll() const
{
	return !HasFlag(wxLC_SINGLE_SEL);
}


void CReportListCtrl::SelectAll()
{
	if (!HasFlag(wxLC_SINGLE_SEL))
	{
		long count = GetItemCount();
		for (long item = 0; item < count; ++item)
		{
			Select(item, true);
		}
	}
}


void CReportListCtrl::SetSelection(long index, bool bEnsureVisible, bool bSetFocus)
{
	std::vector<long> indices;
	indices.push_back(index);
	SetSelection(indices);
	if (bEnsureVisible)
		EnsureVisible(index);
	if (bSetFocus)
		Focus(index);
}


void CReportListCtrl::SetSelection(std::vector<long>& indices)
{
	// Clear everything.
	long item = GetNextSelected(-1);
	while (0 <= item)
	{
		Select(item, false);
		item = GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	}
	// Set it.
	for (std::vector<long>::iterator iter = indices.begin(); iter != indices.end(); ++iter)
	{
		long index = *iter;
		if (index >= 0 && index < GetItemCount())
		{
			Select(index);
		}
	}
}


void CReportListCtrl::ClearSelection()
{
	std::vector<long> indices;
	SetSelection(indices);
}


CListDataPtr CReportListCtrl::GetData(long item) const
{
	CListDataPtr ptr;
	if (0 <= item && item < GetItemCount())
	{
		ptr = m_items[item];
	}
	return ptr;
}


wxString CReportListCtrl::GetPrintDataAsHtmlTable(bool bFirstLineIsHeader) const
{
	wxString data;
	data << L"<table border=\"0\">";
	if (!bFirstLineIsHeader)
		PushData(data, this, -1, true);
	for (long item = 0; item < GetItemCount(); ++item)
	{
		PushData(data, this, item, bFirstLineIsHeader && item == 0);
	}
	data << L"</table>\n";
	return data;
}


// This allows a derived class to print a subset of columns if it wants.
void CReportListCtrl::GetPrintLine(long item, std::vector<wxString>& line) const
{
	line.clear();
	CListDataPtr data = GetData(item);
	if (0 > item || data)
	{
		long nCols = GetColumnCount();
		for (long iCol = 0; iCol < nCols; ++iCol)
		{
			if (0 > item)
				line.push_back(GetListColumnText(this, item, iCol));
			else
				line.push_back(data->OnNeedText(iCol));
		}
	}
}


void CReportListCtrl::RefreshItem(long item)
{
	CListDataPtr data = GetData(item);
	if (data)
	{
		int nColumns = GetColumnCount();
		for (int iCol = 0; iCol < nColumns; ++iCol)
		{
			wxListItem info;
			info.SetId(item);
			info.SetColumn(iCol);
			data->OnNeedListItem(iCol, info);
			SetItem(info);
		}
		CListCtrl::RefreshItem(item);
	}
}


void CReportListCtrl::OnDeleteAllItems(wxListEvent& evt)
{
	m_items.clear();
	SetItemCount(0);
	evt.Skip();
}


void CReportListCtrl::OnDeleteItem(wxListEvent& evt)
{
	long index = evt.GetIndex();
	if (0 <= index && index < static_cast<long>(m_items.size()))
	{
		auto iter = m_items.begin() + index;
		m_items.erase(iter);
	}
	evt.Skip();
}

} // namespace ARBWin
} // namespace dconSoft
