/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Test ARBDouble functions
 * @author David Connet
 *
 * Revision History
 * 2020-04-10 Update to fmt 6.2.
 * 2019-12-08 Add fmt number formatting tests.
 * 2018-12-16 Convert to fmt.
 * 2017-11-09 Convert from UnitTest++ to Catch
 * 2015-12-22 Added tests for changed ARBDouble parameter.
 * 2009-09-13 Add support for wxWidgets 2.9, deprecate tstring.
 * 2008-01-12 Created
 */

#include "stdafx.h"
#include "TestARBLib.h"

#include "ARBCommon/StringUtil.h"
#include "fmt/xchar.h"
#include <wx/numformatter.h>
#if FMT_VERSION < 80000
#include "fmt/locale.h"
#endif

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>
#endif

using namespace dconSoft::ARBCommon;


namespace
{

std::wstring FormNumber(std::wstring const& d1, wxChar const& dec, std::wstring const& d2)
{
	return fmt::format(L"{}{}{}", d1, dec, d2);
}


void RunDblTests(bool bUseLocale)
{
	wxChar decimalPt = L'.';
	if (bUseLocale)
		decimalPt = wxNumberFormatter::GetDecimalSeparator();

	// ARBDouble always strips 0s unless prec ==2, unless =".00"
	double p = 3.14159265358979323846;
	std::wstring s = ARBDouble::ToString(p, 2, bUseLocale);
	REQUIRE(FormNumber(L"3", decimalPt, L"14") == s);
	s = ARBDouble::ToString(p, 4, bUseLocale);
	REQUIRE(FormNumber(L"3", decimalPt, L"1416") == s);

	// eCompatible

	p = 2.1;
	s = ARBDouble::ToString(p, 0, bUseLocale);
	REQUIRE(FormNumber(L"2", decimalPt, L"1") == s);
	s = ARBDouble::ToString(p, 2, bUseLocale);
	REQUIRE(FormNumber(L"2", decimalPt, L"10") == s);
	s = ARBDouble::ToString(p, 3, bUseLocale);
	REQUIRE(FormNumber(L"2", decimalPt, L"1") == s);

	p = 2;
	s = ARBDouble::ToString(p, 0, bUseLocale);
	REQUIRE(L"2" == s);
	s = ARBDouble::ToString(p, 1, bUseLocale);
	REQUIRE(L"2" == s);
	s = ARBDouble::ToString(p, 2, bUseLocale);
	REQUIRE(L"2" == s);

	p = 42;
	s = ARBDouble::ToString(p, 0, bUseLocale);
	REQUIRE(std::wstring(L"42") == s);
	s = ARBDouble::ToString(p, 1, bUseLocale);
	REQUIRE(std::wstring(L"42") == s);
	s = ARBDouble::ToString(p, 2, bUseLocale);
	REQUIRE(std::wstring(L"42") == s);

	p = 2002; // ARB alpha 1 release year!
	s = ARBDouble::ToString(p, 0, bUseLocale);
	REQUIRE(std::wstring(L"2002") == s);
	s = ARBDouble::ToString(p, 1, bUseLocale);
	REQUIRE(std::wstring(L"2002") == s);
	s = ARBDouble::ToString(p, 2, bUseLocale);
	REQUIRE(std::wstring(L"2002") == s);

	// eStrip

	p = 2.1;
	s = ARBDouble::ToString(p, 0, bUseLocale, ARBDouble::ZeroStrip::Strip);
	REQUIRE(FormNumber(L"2", decimalPt, L"1") == s);
	s = ARBDouble::ToString(p, 2, bUseLocale, ARBDouble::ZeroStrip::Strip);
	REQUIRE(FormNumber(L"2", decimalPt, L"1") == s);
	s = ARBDouble::ToString(p, 3, bUseLocale, ARBDouble::ZeroStrip::Strip);
	REQUIRE(FormNumber(L"2", decimalPt, L"1") == s);

	p = 2;
	s = ARBDouble::ToString(p, 0, bUseLocale, ARBDouble::ZeroStrip::Strip);
	REQUIRE(L"2" == s);
	s = ARBDouble::ToString(p, 1, bUseLocale, ARBDouble::ZeroStrip::Strip);
	REQUIRE(L"2" == s);
	s = ARBDouble::ToString(p, 2, bUseLocale, ARBDouble::ZeroStrip::Strip);
	REQUIRE(L"2" == s);

	// eAsIs

	p = 2.1;
	s = ARBDouble::ToString(p, 0, bUseLocale, ARBDouble::ZeroStrip::AsIs);
	REQUIRE(FormNumber(L"2", decimalPt, L"1") == s);
	s = ARBDouble::ToString(p, 2, bUseLocale, ARBDouble::ZeroStrip::AsIs);
	REQUIRE(FormNumber(L"2", decimalPt, L"10") == s);
	s = ARBDouble::ToString(p, 3, bUseLocale, ARBDouble::ZeroStrip::AsIs);
	REQUIRE(FormNumber(L"2", decimalPt, L"100") == s);

	p = 2;
	s = ARBDouble::ToString(p, 0, bUseLocale, ARBDouble::ZeroStrip::AsIs);
	REQUIRE(L"2" == s);
	s = ARBDouble::ToString(p, 1, bUseLocale, ARBDouble::ZeroStrip::AsIs);
	REQUIRE(FormNumber(L"2", decimalPt, L"0") == s);
	s = ARBDouble::ToString(p, 2, bUseLocale, ARBDouble::ZeroStrip::AsIs);
	REQUIRE(FormNumber(L"2", decimalPt, L"00") == s);

	// Check assumptions about libfmt
	// Things changed from v5 to v6, see comments about fmt in ARBTypes.cpp
	// (v6: Formatting changed to locale-independent)
#if (FMT_VERSION >= 60000)
	static const struct
	{
		double val;
		int prec;
		wchar_t const* expected; // No matter the locale, these should always be the same.
		wchar_t const* format;
	} tests[] = {
		// clang-format off
		{42.34, 0, L"42.34", L"{:g}"},
		{42.0,  0, L"42",    L"{:g}"},
		{42.34, 1, L"42.3",  L"{:.{}f}"},
		{42.0,  1, L"42.0",  L"{:.{}f}"},
		// clang-format on
	};

	for (auto& test : tests)
	{
		if (test.prec > 0)
			s = fmt::format(test.format, test.val, test.prec);
		else
			s = fmt::format(test.format, test.val);
		REQUIRE(s == test.expected);
	}
#endif
}

} // namespace


TEST_CASE("Double")
{
	SECTION("fmtCheck")
	{
		// [v6.0/6.1] 'n' is used to tell it to use locales. But that
		// assumes 'g' and [v6.2] needs the std::locale passed.
		// (precision in 'g' works differently than 'f', it's the total
		// number of digits.
#ifdef WIN32
		// On Mac, de_DE has no dots.
		// On unix, I get 'name not valid' for locale.
		// Screw it. Only run these tests on Windows
#if (FMT_VERSION >= 60200)
		// Some general tests on assumptions ('L' appeared in v6.2, 'n' will be removed later)
		REQUIRE(L"1,234,567,890" == fmt::format(std::locale("en_US"), L"{:L}", 1234567890));
		REQUIRE(L"1.234.567.890" == fmt::format(std::locale("de_DE"), L"{:L}", 1234567890));
		REQUIRE(L"1234567890" == fmt::format(L"{}", 1234567890));
#if (FMT_VERSION > 60201)
		// This causes an 'invalid type specifier' exception in v6.2 and 6.2.1
		double d = 1.2;
		REQUIRE(L"1.2" == fmt::format(std::locale("en_US"), L"{:L}", d));
#endif
#endif
#endif
	}


	SECTION("strPrecUS")
	{
		wxLocale locale(wxLANGUAGE_ENGLISH_US);
		RunDblTests(true);
		RunDblTests(false);
	}


	SECTION("strPrecFR")
	{
		// Using French since the default decimal separator is a comma.
		wxLocale locale(wxLANGUAGE_FRENCH);
		RunDblTests(true);
		RunDblTests(false);
	}


	SECTION("equal")
	{
		double p1 = 3.14159265;
		double p2 = 3.141592;
		double p3 = 3.141592657;
		REQUIRE(ARBDouble::equal(p1, p2, 0.00001));
		REQUIRE(!ARBDouble::equal(p1, p2, 0.00000001));
		REQUIRE(ARBDouble::equal(p1, p3, 0.00000001));
	}
}
