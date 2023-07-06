#pragma once

/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Helper for dialog layouts
 *
 * Revision History
 */

#include "LibwxARBWin.h"


namespace dconSoft
{
namespace ARBWin
{

class ARBWIN_API CDlgPadding
{
public:
	CDlgPadding(wxWindow* parent)
		: m_paddingCtrl(wxDLG_UNIT_X(parent, 5))
		, m_paddingInner(wxDLG_UNIT_X(parent, 3))
		, m_paddingButtonSizer(wxDLG_UNIT_X(parent, 3))
		, m_paddingControls(wxDLG_UNIT_X(parent, 2))
		, m_paddingTight(wxDLG_UNIT_X(parent, 1))
		, m_paddingOffset(wxDLG_UNIT_X(parent, 10))
	{
	}

	// Spacing between controls
	int Controls() const
	{
		return m_paddingCtrl;
	}

	// Spacing between related controls (text+ctrl)
	int Inner() const
	{
		return m_paddingInner;
	}

	// Spacing for button sizer
	// Also used when adding a notebook directly to a dialog
	int ButtonSizer() const
	{
		return m_paddingButtonSizer;
	}

	// Tight grouping of controls
	int TightControls() const
	{
		return m_paddingControls;
	}

	// Tight alignment for a companion control
	int Tight() const
	{
		return m_paddingTight;
	}

	// Offset when lining up something under a checkbox
	int CheckboxOffset() const
	{
		return m_paddingOffset;
	}

private:
	int m_paddingCtrl;
	int m_paddingInner;
	int m_paddingButtonSizer;
	int m_paddingControls;
	int m_paddingTight;
	int m_paddingOffset;
};

} // namespace ARBWin
} // namespace dconSoft
