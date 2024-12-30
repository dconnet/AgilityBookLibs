#pragma once

/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Definitions of configuration (registry) entries.
 * @author David Connet
 *
 * wxConfig must be set up first before using these.
 *
 * Revision History
 * 2022-08-16 ColumnOrder is gone.
 * 2020-01-07 ColumnOrder and ReportListHeader settings are incompatible - separate.
 * 2018-10-11 Separated from RegItems.h.
 */

namespace dconSoft
{
namespace ARBWin
{

// Sorting:
#define CFG_KEY_SORTING L"Sorting"
#if 0
// These are gone. Leave in code as reminder not to reuse (or recreate!)
// these keys in the future.
//	ST [key]Order (ColumnOrder.cpp)
inline wxString CFG_SORTING_ORDER(wxString const& item)
{
	return wxString::Format(L"%s/%sOrder", CFG_KEY_SORTING, item);
}
//	ST [key]Sort (ColumnOrder.cpp)
inline wxString CFG_SORTING_SORT(wxString const& item)
{
	return wxString::Format(L"%s/%sSort", CFG_KEY_SORTING, item);
}
#endif
//	ST [key]Order2 (ReportListHeader.cpp)
inline wxString CFG_SORTING_ORDER2(wxString const& item)
{
	return wxString::Format(L"%s/%sOrder2", CFG_KEY_SORTING, item);
}
//	ST [key]Vis (ReportListHeader.cpp)
inline wxString CFG_SORTING_VISIBLE(wxString const& item)
{
	return wxString::Format(L"%s/%sVis", CFG_KEY_SORTING, item);
}
inline wxString CFG_COLUMN_WIDTHS(wxString const& item)
{
	return wxString::Format(L"%s/%sWidth", CFG_KEY_SORTING, item);
}
inline wxString CFG_SORT_COLUMN(wxString const& item)
{
	return wxString::Format(L"%s/%sColumn", CFG_KEY_SORTING, item);
}

#define CFG_KEY_ACCELERATORS L"Accelerators"
// ST
#define CFG_ACCEL_KEYCODE L"KeyCode"
// ST
#define CFG_ACCEL_ID L"id"
// DW (bitmask for alt/ctrl/shift modifiers)
#define CFG_ACCEL_MOD L"mod"

#define CFG_KEY_RECENT_FILES L"Recent File List" // Named this way for compatibility with existing MFC app

} // namespace ARBWin
} // namespace dconSoft
