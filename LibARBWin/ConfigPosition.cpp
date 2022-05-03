/*
 * Copyright (c) David Connet. All Rights Reserved.
 */

/**
 * @file
 * @brief Save window position
 * @author David Connet
 *
 * Note: When transitioning from "dpiAware:True" to "dpiAware:True/PM",
 * the x/y position may be off initially if you have more than 1 monitor
 * and they're at different scaling factors.
 *
 * Note2: This code is slightly incompatible with the previous version.
 * That stored the x/y in 100% numbers. We don't do that anymore. Those
 * are stored in raw form (so we can put the window back and scale properly
 * on a multi-monitor setup). (Hence the Last[XY]old apis)
 *
 * Revision History
 * 2022-05-03 Add back-compatibility for X/Y changes.
 * 2022-04-15 Fix sizing so it works per-monitor.
 * 2022-04-15 Use wx DPI support.
 * 2021-09-23 Fix reading of last state.
 * 2021-09-19 Changed default config paths.
 * 2021-03-06 Moved into LibARBWin.
 * 2017-12-22 Add support for saving dialogs.
 * 2015-08-11 Add HiDPI support.
 * 2013-12-14 2.0.0 Standardized History
 * 2012-08-13       Moved ConfigPosition out of Globals.cpp
 */

#include "stdafx.h"
#include "LibARBWin/ConfigPosition.h"

#include <wx/config.h>
#include <wx/display.h>

#if defined(__WXMSW__)
#include <wx/msw/msvcrt.h>
#endif


namespace
{
enum class EntryStatus
{
	NoChange,
	ValueSet,
	OldValueSet,
};

EntryStatus GetEntry(wxString entry, wxString oldEntry, int& value, bool preserve)
{
	EntryStatus status = EntryStatus::NoChange;
	if (entry.empty())
		return status;
	if (wxConfig::Get()->HasEntry(entry))
	{
		if (wxConfig::Get()->Read(entry, &value, value))
			status = EntryStatus::ValueSet;
		if (!preserve && !oldEntry.empty() && wxConfig::Get()->HasEntry(oldEntry))
			wxConfig::Get()->DeleteEntry(oldEntry);
	}
	else if (!oldEntry.empty() && wxConfig::Get()->HasEntry(oldEntry))
	{
		if (wxConfig::Get()->Read(oldEntry, &value, value))
			status = EntryStatus::OldValueSet;
	}
	return status;
}
} // namespace


CConfigPosition::CConfigPosition(uint8_t flags)
	: CConfigPosition(wxString(), flags)
{
}


CConfigPosition::CConfigPosition(wxString const& name, uint8_t flags)
	: m_name(name)
	, m_flags(flags)
{
}


CConfigPosition::~CConfigPosition()
{
}


bool CConfigPosition::Set(wxWindow* wnd, bool bUseExisting, bool* pPosSet)
{
	if (!wnd || !wxConfig::Get())
		return false;

	int x = wxDefaultCoord, y = wxDefaultCoord, width = 0, height = 0;
	wnd->GetSize(&width, &height);
	int defWidth = width;
	int defHeight = height;

	if (bUseExisting)
	{
		wxRect r = wnd->GetScreenRect();
		x = r.GetLeft();
		y = r.GetTop();
	}

	EntryStatus statusX = GetEntry(LastX(), LastXold(), x, PreserveOldValue());
	EntryStatus statusY = GetEntry(LastY(), LastYold(), y, PreserveOldValue());
	bool setPos = (statusX != EntryStatus::NoChange || statusY != EntryStatus::NoChange);
	if (pPosSet)
		*pPosSet = setPos;

	double scale = 1.0;
#if !defined(wxHAS_DPI_INDEPENDENT_PIXELS)
	if (setPos)
	{
		int display = wxDisplay::GetFromPoint(wxPoint(x, y));
		// If the display can't be found, use the primary.
		// Position will be adjusted below.
		if (wxNOT_FOUND == display)
			display = 0;
		wxDisplay monitor(display);
		scale = monitor.GetScaleFactor();

		if (scale > 1.0)
		{
			if (statusX == EntryStatus::OldValueSet)
				x = static_cast<int>(x * scale);
			if (statusY == EntryStatus::OldValueSet)
				y = static_cast<int>(y * scale);
		}
	}
#endif

	if (!LastCX().empty())
	{
		// Note: Don't use FromDIP because the display 'wnd' is currently on
		// may have a different scaling than where we're going.
		if (wxConfig::Get()->Read(LastCX(), &width, width))
			width = static_cast<int>(width * scale);
	}
	if (!LastCY().empty())
	{
		if (wxConfig::Get()->Read(LastCY(), &height, height))
			height = static_cast<int>(height * scale);
	}

	long state = 0;
	if (!LastState().empty())
		wxConfig::Get()->Read(LastState(), &state, state);

	bool bCompute = false;
	wxMouseState mouseState = ::wxGetMouseState();
	if (wxDefaultCoord != x)
	{
		bCompute = true;
		mouseState.SetX(x);
	}
	if (wxDefaultCoord != y)
	{
		bCompute = true;
		mouseState.SetY(y);
	}
	wxSize curSize(defWidth, defHeight);
	if (defWidth != width)
	{
		bCompute = true;
		curSize.SetWidth(width);
	}
	if (defHeight != height)
	{
		bCompute = true;
		curSize.SetHeight(height);
	}
	if (bCompute)
	{
		wxPoint curPt(mouseState.GetX(), mouseState.GetY());
		int display = wxDisplay::GetFromPoint(curPt);
		if (wxNOT_FOUND == display)
			display = 0; // If the display can't be found, use the primary.
		wxDisplay monitor(display);
		wxRect rWorkSpace = monitor.GetClientArea();
		wxRect rect(curPt, curSize);
		// Make sure window is not bigger.
		if (rect.GetWidth() > rWorkSpace.GetWidth())
			rect.SetRight(rect.GetLeft() + rWorkSpace.GetWidth());
		if (rect.GetHeight() > rWorkSpace.GetHeight())
			rect.SetBottom(rect.GetTop() + rWorkSpace.GetHeight());
		// Make sure the window is fully visible in the screen.
		if (!rWorkSpace.Contains(rect.GetTopLeft()))
		{
			if (rect.GetLeft() < rWorkSpace.GetLeft())
				rect.Offset(rWorkSpace.GetLeft() - rect.GetLeft(), 0);
			if (rect.GetTop() < rWorkSpace.GetTop())
				rect.Offset(0, rWorkSpace.GetTop() - rect.GetTop());
		}
		// Only check the bottom-right if the rect has size.
		if (!rect.IsEmpty() && !rWorkSpace.Contains(rect.GetBottomRight()))
		{
			if (rect.GetRight() > rWorkSpace.GetRight())
				rect.Offset(rWorkSpace.GetRight() - rect.GetRight(), 0);
			if (rect.GetBottom() > rWorkSpace.GetBottom())
				rect.Offset(0, rWorkSpace.GetBottom() - rect.GetBottom());
		}
		if (wxDefaultCoord != x)
			x = rect.GetLeft();
		if (wxDefaultCoord != y)
			y = rect.GetTop();
		if (defWidth != width)
			width = rect.GetWidth();
		if (defHeight != height)
			height = rect.GetHeight();
	}
	wnd->SetSize(x, y, width, height);

	return 0 < state;
}


void CConfigPosition::Save(wxTopLevelWindow* wnd)
{
	if (!wnd || !wxConfig::Get())
		return;

	long state = 0;
	if (wnd->IsMaximized() || wnd->IsFullScreen())
	{
		state = 1;
	}
	else if (wnd->IsIconized())
	{
		state = -1;
	}
	else
	{
		SaveWindow(wnd);
	}
	if (!LastState().empty())
		wxConfig::Get()->Write(LastState(), state);
}


void CConfigPosition::SaveWindow(wxWindow* wnd)
{
	wxRect r = wnd->GetScreenRect();
	// Save x/y in native pixels.
	if (!LastX().empty())
		wxConfig::Get()->Write(LastX(), r.x);
	if (!LastY().empty())
		wxConfig::Get()->Write(LastY(), r.y);
	// Save w/h in 100% factor pixels.
	if (!LastCX().empty())
		wxConfig::Get()->Write(LastCX(), wnd->ToDIP(r.width));
	if (!LastCY().empty())
		wxConfig::Get()->Write(LastCY(), wnd->ToDIP(r.height));
}
