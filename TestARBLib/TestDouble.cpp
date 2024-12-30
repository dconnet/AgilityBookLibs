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
 * 2017-11-09 Convert from UnitTest++ to Catch
 * 2015-12-22 Added tests for changed ARBDouble parameter.
 * 2009-09-13 Add support for wxWidgets 2.9, deprecate tstring.
 * 2008-01-12 Created
 */

#include "stdafx.h"
#include "TestARBLib.h"

#include "ARBCommon/StringUtil.h"
#include <wx/numformatter.h>

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>
#endif


namespace dconSoft
{
using namespace ARBCommon;

namespace
{

wxString FormNumber(wxString const& d1, wxChar const& dec, wxString const& d2)
{
	return wxString::Format(L"%s%lc%s", d1, dec, d2);
}


void RunDblTests(bool bUseLocale)
{
	wxChar decimalPt = L'.';
	if (bUseLocale)
		decimalPt = wxNumberFormatter::GetDecimalSeparator();

	// ARBDouble always strips 0s unless prec ==2, unless =".00"
	double p = 3.14159265358979323846;
	wxString s = ARBDouble::ToString(p, 2, bUseLocale);
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
	REQUIRE(wxString(L"42") == s);
	s = ARBDouble::ToString(p, 1, bUseLocale);
	REQUIRE(wxString(L"42") == s);
	s = ARBDouble::ToString(p, 2, bUseLocale);
	REQUIRE(wxString(L"42") == s);

	p = 2002; // ARB alpha 1 release year!
	s = ARBDouble::ToString(p, 0, bUseLocale);
	REQUIRE(wxString(L"2002") == s);
	s = ARBDouble::ToString(p, 1, bUseLocale);
	REQUIRE(wxString(L"2002") == s);
	s = ARBDouble::ToString(p, 2, bUseLocale);
	REQUIRE(wxString(L"2002") == s);

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
}

} // namespace


TEST_CASE("Double")
{
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

} // namespace dconSoft
