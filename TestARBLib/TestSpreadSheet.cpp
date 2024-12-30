/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Test Spreadsheet column translations
 * @author David Connet
 *
 * Revision History
 * 2022-09-20 Created
 */

#include "stdafx.h"
#include "TestARBLib.h"

#include "LibARBWin/SpreadSheet.h"

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>
#endif


namespace dconSoft
{
using namespace ARBCommon;
using namespace ARBWin;

namespace
{
constexpr struct
{
	long row; // If -1, only testing column
	long col;
	wchar_t const* cell;
} k_cells[] = {
	// clang-format off
	{-1, 1, L"B"},
	{-1, 26, L"AA"},
	{0, 0, L"A1"},
	{1, 1, L"B2"},
	{1, 27, L"AB2"},
	// clang-format on
};
} // namespace


TEST_CASE("SpreadSheet")
{
	SECTION("Columns2Int")
	{
		for (auto const& data : k_cells)
		{
			if (0 > data.row)
			{
				long col = -1;
				REQUIRE(ISpreadSheet::GetCol(data.cell, col));
				REQUIRE(col == data.col);
			}
		}
	}


	SECTION("Columns2Str")
	{
		for (auto const& data : k_cells)
		{
			if (0 > data.row)
			{
				wxString col;
				REQUIRE(ISpreadSheet::GetCol(data.col, col));
				REQUIRE(col == data.cell);
			}
		}
	}


	SECTION("Cells2Int")
	{
		for (auto const& data : k_cells)
		{
			if (0 <= data.row)
			{
				long row = -1, col = -1;
				REQUIRE(ISpreadSheet::GetRowCol(data.cell, row, col));
				REQUIRE(row == data.row);
				REQUIRE(col == data.col);
			}
		}
	}


	SECTION("Cells2Str")
	{
		for (auto const& data : k_cells)
		{
			if (0 <= data.row)
			{
				wxString cell;
				REQUIRE(ISpreadSheet::GetRowCol(data.row, data.col, cell));
				REQUIRE(cell == data.cell);
			}
		}
	}
}

} // namespace dconSoft
