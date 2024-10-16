/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief implementation of the CStatusBarHelper class
 * @author David Connet
 *
 * Revision History
 * 2023-09-27 Fix sizing on linux/mac.
 * 2022-04-15 Use wx DPI support.
 * 2021-05-25 Changed initialization
 * 2021-01-20 Removed sizing kludge on linux/mac
 * 2019-01-27 Created
 */

#include "stdafx.h"
#include "LibARBWin/StatusBarHelper.h"

#include "LibARBWin/MenuHelper.h"

#if defined(__WXMSW__)
#include <wx/msw/msvcrt.h>
#endif


namespace dconSoft
{
namespace ARBWin
{

CStatusBarHelper::CStatusBarHelper(wxFrame* frame, size_t nColumns)
	: m_frame(frame)
	, m_Widths(nColumns, -1)
{
}


wxStatusBar* CStatusBarHelper::Initialize()
{
	if (!m_frame || m_Widths.size() == 0)
		return nullptr;

	wxStatusBar* statusbar = m_frame->CreateStatusBar(static_cast<int>(m_Widths.size()));
	if (!statusbar)
		return nullptr;

#if wxCHECK_VERSION(3, 3, 0)
	wxInfoDC dc(statusbar);
#else
	wxClientDC dc(statusbar);
#endif
	dc.SetFont(statusbar->GetFont());

	std::vector<int> style(m_Widths.size(), 0);

	m_Widths[0] = -1; // First column is variable width
	style[0] = wxSB_FLAT;
	for (size_t i = 1; i < m_Widths.size(); ++i)
	{
		m_Widths[i] = statusbar->FromDIP(50);
		style[i] = wxSB_NORMAL;
	}
	statusbar->SetStatusStyles(static_cast<int>(m_Widths.size()), style.data());
	SetStatusBarWidths(statusbar, -1);

	return statusbar;
}


bool CStatusBarHelper::Update(int nCol, wxString const& text)
{
	if (!m_frame || m_Widths.size() == 0)
		return false;

	wxStatusBar* statusbar = m_frame->GetStatusBar();
	if (!statusbar)
		return false;

	assert(nCol > 0 && nCol < static_cast<int>(m_Widths.size()));

	m_frame->SetStatusText(text, nCol);

#if wxCHECK_VERSION(3, 3, 0)
	wxInfoDC dc(statusbar);
#else
	wxClientDC dc(statusbar);
#endif
	dc.SetFont(statusbar->GetFont());
	m_Widths[nCol] = dc.GetTextExtent(text).x;

	SetStatusBarWidths(statusbar, nCol);

	return true;
}


bool CStatusBarHelper::Update(std::vector<wxString> const& text)
{
	if (!m_frame || m_Widths.size() == 0)
		return false;

	wxStatusBar* statusbar = m_frame->GetStatusBar();
	if (!statusbar)
		return false;

	assert(text.size() + 1 == m_Widths.size());

	for (int i = 0; i < static_cast<int>(text.size()); ++i)
		m_frame->SetStatusText(text[i], i + 1);

#if wxCHECK_VERSION(3, 3, 0)
	wxInfoDC dc(statusbar);
#else
	wxClientDC dc(statusbar);
#endif
	dc.SetFont(statusbar->GetFont());
	for (size_t i = 0; i < text.size(); ++i)
	{
		m_Widths[i + 1] = dc.GetTextExtent(text[i]).x;
	}

	SetStatusBarWidths(statusbar, -1);

	return true;
}


int CStatusBarHelper::GetContextMenuFieldId(wxContextMenuEvent const& evt, wxStatusBar*& statusbar, wxPoint& point)
	const
{
	statusbar = m_frame->GetStatusBar();
	if (!statusbar)
		return -1;
	wxRect rect;
	if (!CMenuHelper::GetMenuPosition(point, statusbar, evt))
		return -1;
	for (int id = 1; id < static_cast<int>(m_Widths.size()); ++id)
	{
		if (statusbar->GetFieldRect(id, rect) && rect.Contains(point))
			return id;
	}
	return -1;
}


int CStatusBarHelper::GetDoubleClickFieldId(wxMouseEvent const& evt) const
{
	wxStatusBar* statusbar = m_frame->GetStatusBar();
	if (!statusbar)
		return -1;
	wxRect rect;
	wxPoint point = evt.GetPosition();
	if (wxDefaultPosition == point)
	{
		rect = statusbar->GetScreenRect();
		point = ::wxGetMousePosition();
		if (!rect.Contains(point))
			return -1;
		point = statusbar->ScreenToClient(point);
	}
	for (int id = 1; id < static_cast<int>(m_Widths.size()); ++id)
	{
		if (statusbar->GetFieldRect(id, rect) && rect.Contains(point))
			return id;
	}
	return -1;
}


void CStatusBarHelper::SetStatusBarWidths(wxStatusBar* statusbar, int nColumn)
{
	bool bAddKludge
		= (statusbar->HasFlag(wxSTB_SIZEGRIP) && (0 > nColumn || nColumn == static_cast<int>(m_Widths.size()) - 1));
	// The gripper isn't right on hidpi. Add a fudge factor.
	if (bAddKludge)
	{
		if (statusbar->GetDPIScaleFactor() > 1.0)
			m_Widths[m_Widths.size() - 1] += statusbar->FromDIP(10);
#if defined(__WXGTK__)
		// The last column is cut off because of the gripper on linux.
		m_Widths[m_Widths.size() - 1] += statusbar->FromDIP(20);
#endif
	}

	wxSize borders = statusbar->GetBorders();
	if (0 < borders.x)
	{
		// A column is only updated if we've just computed the extent.
		// So cache the fixed value. (Or when we update a different column,
		// the previous one loses it's border adjustment.)
		for (int i = 0; i < static_cast<int>(m_Widths.size()); ++i)
		{
			if ((0 > nColumn || i == nColumn) && 0 < m_Widths[i])
			{
				// On Mac/Linux, I need (4 * borders.x) - not 2 as expected.
				// Sizing it exactly causes "..." in the text (or cut off on mac)
				// Note: On windows, borders.x is 0. Mac/Linux it is 2.
				m_Widths[i] += borders.x * 4;
			}
		}
	}

	statusbar->SetStatusWidths(static_cast<int>(m_Widths.size()), m_Widths.data());
}

} // namespace ARBWin
} // namespace dconSoft
