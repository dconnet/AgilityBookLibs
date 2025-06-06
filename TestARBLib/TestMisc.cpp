/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Test misc functions
 * @author David Connet
 *
 * Revision History
 * 2019-10-13 Move config test to TestARB
 * 2019-08-15 Fix tests on unix.
 * 2019-06-28 Moved ConfigPath to TestUtils
 * 2018-04-26 Added roman numeral tests.
 * 2017-11-09 Convert from UnitTest++ to Catch
 * 2015-11-01 Added ARBConfig/ARBBook version test.
 * 2015-04-04 Add C99 printf test.
 * 2014-11-17 Added "true" units (nonIEC) to FormatBytes.
 * 2014-08-28 Enhanced FormatBytes
 * 2012-04-03 Added ARBVersion test.
 * 2011-11-17 Add localization test.
 * 2009-09-13 Add support for wxWidgets 2.9, deprecate tstring.
 * 2008-01-12 Created
 */

#include "stdafx.h"
#include "TestARBLib.h"

#include "ARBCommon/ARBMisc.h"
#include "ARBCommon/ARBTypes.h"
#include "ARBCommon/StringUtil.h"
#include "LibARBWin/CheckLink.h"

#include <stdarg.h>

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>
#endif


namespace dconSoft
{
using namespace ARBCommon;
using namespace ARBWin;

namespace
{
constexpr size_t NUM_PREC = 2;
constexpr struct
{
	double val;
	int prec[NUM_PREC];
	wchar_t const* unitSI[NUM_PREC];
	wchar_t const* unitBinary[NUM_PREC];
	wchar_t const* unitTrue[NUM_PREC];
} sc_FormatUnits[] = {
	// clang-format off
	{0.0,             {1, 2}, {L"0 B", L"0 B"},            {L"0 B", L"0 B"},            {L"0 B", L"0 B"}},
	{27.0,            {1, 2}, {L"27 B", L"27 B"},          {L"27 B", L"27 B"},          {L"27 B", L"27 B"}},
	{999.0,           {1, 2}, {L"999 B", L"999 B"},        {L"999 B", L"999 B"},        {L"999 B", L"999 B"}},
	{1000.0,          {1, 2}, {L"1 kB", L"1 kB"},          {L"1000 B", L"1000 B"},      {L"1000 B", L"1000 B"}},
	{1023.0,          {1, 2}, {L"1 kB", L"1.02 kB"},       {L"1023 B", L"1023 B"},      {L"1023 B", L"1023 B"}},
	{1024.0,          {1, 2}, {L"1 kB", L"1.02 kB"},       {L"1 KiB", L"1 KiB"},        {L"1 KB", L"1 KB"}},
	{1536.0,          {1, 2}, {L"1.5 kB", L"1.54 kB"},     {L"1.5 KiB", L"1.5 KiB"},    {L"1.5 KB", L"1.5 KB"}},
	{1600.0,          {1, 2}, {L"1.6 kB", L"1.6 kB"},      {L"1.6 KiB", L"1.56 KiB"},   {L"1.6 KB", L"1.56 KB"}},
	{1728.0,          {1, 2}, {L"1.7 kB", L"1.73 kB"},     {L"1.7 KiB", L"1.69 KiB"},   {L"1.7 KB", L"1.69 KB"}},
	// Note: On Mac/Unix, 15.625 is rounding differently than Windows.
	// Oh. And ReleaseDLL rounds the same way unix does.
	// And VC16.9 (v1928) rounds the same way unix does.
#if defined(WIN32) && defined(_MSC_VER) && _MSC_VER < 1928 && !(defined(_DLL) && !defined(_DEBUG))
	{16000.0,         {1, 2}, {L"16 kB", L"16 kB"},        {L"15.6 KiB", L"15.63 KiB"}, {L"15.6 KB", L"15.63 KB"}},
#else
	{16000.0,         {1, 2}, {L"16 kB", L"16 kB"},        {L"15.6 KiB", L"15.62 KiB"}, {L"15.6 KB", L"15.62 KB"}},
#endif
	{110592.0,        {1, 2}, {L"110.6 kB", L"110.59 kB"}, {L"108 KiB", L"108 KiB"},    {L"108 KB", L"108 KB"}},
	{7077888.0,       {1, 2}, {L"7.1 MB", L"7.08 MB"},     {L"6.8 MiB", L"6.75 MiB"},   {L"6.8 MB", L"6.75 MB"}},
	{452984832.0,     {1, 2}, {L"453 MB", L"452.98 MB"},   {L"432 MiB", L"432 MiB"},    {L"432 MB", L"432 MB"}},
	{28991029248.0,	  {1, 2}, {L"29 GB", L"28.99 GB"},     {L"27 GiB", L"27 GiB"},      {L"27 GB", L"27 GB"}},
	{1855425871872.0, {1, 2}, {L"1.9 TB", L"1.86 TB"},     {L"1.7 TiB", L"1.69 TiB"},   {L"1.7 TB", L"1.69 TB"}}
	// clang-format on
};
} // namespace


TEST_CASE("Misc")
{
	SECTION("Html_Sanitize")
	{
		wxString s(L"<&amp>");
		wxString s2 = SanitizeStringForHTML(s);
		REQUIRE(L"&lt;&amp;amp&gt;" == s2);
		s = L"1\r\n2\n3";
		s2 = SanitizeStringForHTML(s, true);
		REQUIRE(L"1<br/>2<br/>3" == s2);
		s2 = SanitizeStringForHTML(s, false);
		REQUIRE(L"1\r\n2\n3" == s2);
	}


	SECTION("CheckHttpFile")
	{
		// Note: This test no longer hits the internet. It validates a local file existence, or a valid URL.
		REQUIRE(CheckLink(L"http://www.agilityrecordbook.com/version2.xml"));
		REQUIRE(CheckLink(L"https://www.agilityrecordbook.com/version2.xml"));
		REQUIRE(!CheckLink(L"httpx://www.agilityrecordbook.com/versionXX.xml"));
	}


	SECTION("Version")
	{
		ARBVersion ver(0xf3f3, 0xff44);
		REQUIRE(ver.Major() == 0xf3f3);
		REQUIRE(ver.Minor() == 0xff44);
	}


	SECTION("FormatBytes")
	{
		wxLocale locale(wxLANGUAGE_ENGLISH_US);
		for (size_t i = 0; i < _countof(sc_FormatUnits); ++i)
		{
			for (size_t iPrec = 0; iPrec < NUM_PREC; ++iPrec)
			{
				REQUIRE(
					StringUtil::FormatBytes(
						sc_FormatUnits[i].val,
						sc_FormatUnits[i].prec[iPrec],
						StringUtil::ByteSizeStyle::Binary)
					== sc_FormatUnits[i].unitBinary[iPrec]);
				REQUIRE(
					StringUtil::FormatBytes(
						sc_FormatUnits[i].val,
						sc_FormatUnits[i].prec[iPrec],
						StringUtil::ByteSizeStyle::SI)
					== sc_FormatUnits[i].unitSI[iPrec]);
				REQUIRE(
					StringUtil::FormatBytes(
						sc_FormatUnits[i].val,
						sc_FormatUnits[i].prec[iPrec],
						StringUtil::ByteSizeStyle::True)
					== sc_FormatUnits[i].unitTrue[iPrec]);
			}
		}
	}


	SECTION("VerifyColor")
	{
#ifdef __WXMSW__
		REQUIRE(wxSYS_COLOUR_SCROLLBAR == COLOR_SCROLLBAR);
		REQUIRE(wxSYS_COLOUR_DESKTOP == COLOR_BACKGROUND);
		REQUIRE(wxSYS_COLOUR_ACTIVECAPTION == COLOR_ACTIVECAPTION);
		REQUIRE(wxSYS_COLOUR_INACTIVECAPTION == COLOR_INACTIVECAPTION);
		REQUIRE(wxSYS_COLOUR_MENU == COLOR_MENU);
		REQUIRE(wxSYS_COLOUR_WINDOW == COLOR_WINDOW);
		REQUIRE(wxSYS_COLOUR_WINDOWFRAME == COLOR_WINDOWFRAME);
		REQUIRE(wxSYS_COLOUR_MENUTEXT == COLOR_MENUTEXT);
		REQUIRE(wxSYS_COLOUR_WINDOWTEXT == COLOR_WINDOWTEXT);
		REQUIRE(wxSYS_COLOUR_CAPTIONTEXT == COLOR_CAPTIONTEXT);
		REQUIRE(wxSYS_COLOUR_ACTIVEBORDER == COLOR_ACTIVEBORDER);
		REQUIRE(wxSYS_COLOUR_INACTIVEBORDER == COLOR_INACTIVEBORDER);
		REQUIRE(wxSYS_COLOUR_APPWORKSPACE == COLOR_APPWORKSPACE);
		REQUIRE(wxSYS_COLOUR_HIGHLIGHT == COLOR_HIGHLIGHT);
		REQUIRE(wxSYS_COLOUR_HIGHLIGHTTEXT == COLOR_HIGHLIGHTTEXT);
		REQUIRE(wxSYS_COLOUR_BTNFACE == COLOR_BTNFACE);
		REQUIRE(wxSYS_COLOUR_BTNSHADOW == COLOR_BTNSHADOW);
		REQUIRE(wxSYS_COLOUR_GRAYTEXT == COLOR_GRAYTEXT);
		REQUIRE(wxSYS_COLOUR_BTNTEXT == COLOR_BTNTEXT);
		REQUIRE(wxSYS_COLOUR_INACTIVECAPTIONTEXT == COLOR_INACTIVECAPTIONTEXT);
		REQUIRE(wxSYS_COLOUR_BTNHIGHLIGHT == COLOR_BTNHIGHLIGHT);
		REQUIRE(wxSYS_COLOUR_3DDKSHADOW == COLOR_3DDKSHADOW);
		REQUIRE(wxSYS_COLOUR_3DLIGHT == COLOR_3DLIGHT);
		REQUIRE(wxSYS_COLOUR_INFOTEXT == COLOR_INFOTEXT);
		REQUIRE(wxSYS_COLOUR_INFOBK == COLOR_INFOBK);
		// REQUIRE(wxSYS_COLOUR_LISTBOX == );
		REQUIRE(wxSYS_COLOUR_HOTLIGHT == COLOR_HOTLIGHT);
		REQUIRE(wxSYS_COLOUR_GRADIENTACTIVECAPTION == COLOR_GRADIENTACTIVECAPTION);
		REQUIRE(wxSYS_COLOUR_GRADIENTINACTIVECAPTION == COLOR_GRADIENTINACTIVECAPTION);
		// REQUIRE(wxSYS_COLOUR_MENUHILIGHT == );
		// REQUIRE(wxSYS_COLOUR_MENUBAR == );
		// REQUIRE(wxSYS_COLOUR_LISTBOXTEXT == );
#endif
	}


	SECTION("RomanNumerals")
	{
		constexpr struct
		{
			short val;
			wchar_t const* roman;
		} testValues[] = {
			// clang-format off
			{ -42, L"" },
			{ 0, L""},
			{ 1, L"I"},
			{ 2, L"II" },
			{ 3, L"III" },
			{ 5, L"V" },
			{ 6, L"VI" },
			{ 7, L"VII" },
			{ 8, L"VIII" },
			{ 4, L"IV" },
			{ 9, L"IX" },
			{ 10, L"X" },
			{ 11, L"XI" },
			{ 13, L"XIII" },
			{ 14, L"XIV" },
			{ 18, L"XVIII" },
			{ 19, L"XIX" },
			{ 20, L"XX" },
			{ 28, L"XXVIII" },
			{ 29, L"XXIX" },
			{ 39, L"XXXIX" },
			{ 40, L"XL" },
			{ 49, L"XLIX" },
			{ 50, L"L" },
			{ 53, L"LIII" },
			{ 57, L"LVII" },
			{ 59, L"LIX" },
			{ 79, L"LXXIX" },
			{ 90, L"XC" },
			{ 99, L"XCIX" },
			{ 100, L"C" },
			{ 200, L"CC" },
			{ 499, L"CDXCIX" },
			{ 500, L"D" },
			{ 999, L"CMXCIX" },
			{ 2999, L"MMCMXCIX" },
			{ 3999, L"MMMCMXCIX" },
			// clang-format on
		};
		for (size_t i = 0; i < _countof(testValues); ++i)
		{
			REQUIRE(ShortToRoman(testValues[i].val) == testValues[i].roman);
		}
	}
}

} // namespace dconSoft
