/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Test ARBDate class
 * @author David Connet
 *
 * Revision History
 * 2017-11-09 Convert from UnitTest++ to Catch
 * 2013-10-07 Added leap year tests.
 * 2012-10-26 Changed ARBDate::GetTime to avoid time_t when possible.
 * 2009-10-30 Add support for localized dates.
 * 2009-09-13 Add support for wxWidgets 2.9, deprecate tstring.
 * 2008-01-11 Created
 */

#include "stdafx.h"
#include "TestARBLib.h"

#include "ARBCommon/ARBDate.h"

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>
#endif


namespace dconSoft
{
using namespace ARBCommon;


TEST_CASE("Date")
{
	SECTION("New")
	{
		ARBDate d;
		REQUIRE(!d.IsValid());
	}


#if defined(__WXWINDOWS__)
	SECTION("wxDate")
	{
		ARBDate d(1999, 3, 27);
		wxDateTime wxD;
		d.GetDate(wxD);
		REQUIRE(1999 == wxD.GetYear());
		REQUIRE(3 == wxD.GetMonth() + 1); // 'Month' is an enum, starting at 0
		REQUIRE(27 == wxD.GetDay());
	}
#endif


	SECTION("Valid")
	{
		ARBDate d(1999, 3, 27);
		REQUIRE(1999 == d.GetYear());
		REQUIRE(3 == d.GetMonth());
		REQUIRE(27 == d.GetDay());
	}


	SECTION("Bad")
	{
		ARBDate d(1999, 3, 42);
		REQUIRE(!d.IsValid());
	}


	SECTION("Equality")
	{
		ARBDate d1(1999, 3, 27);
		ARBDate d2(1999, 3, 27);
		REQUIRE(d1 == d2);
	}


	SECTION("Less")
	{
		ARBDate d1(1999, 3, 27);
		ARBDate d2(1999, 4, 27);
		REQUIRE(d1 < d2);
	}


	SECTION("Between")
	{
		ARBDate d1(1999, 3, 27);
		ARBDate d2(1999, 4, 27);
		ARBDate d3(1999, 5, 27);
		REQUIRE(d2.isBetween(d1, d3));
		REQUIRE(d2.isBetween(d3, d1));
		REQUIRE(!d1.isBetween(d2, d3));
		REQUIRE(!d1.isBetween(d3, d2));
	}


	SECTION("String")
	{
		ARBDate d(1999, 3, 2);
#if !defined(__WXWINDOWS__)
#pragma PRAGMA_TODO(need non - wx support in libarb - currently it asserts)
#else
		{
			wxLocale locale(wxLANGUAGE_ENGLISH_UK);
#if defined(WIN32) || defined(__WXMAC__)
			REQUIRE(L"02/03/1999" == d.GetString(ARBDateFormat::Locale));
#else
			REQUIRE(L"02/03/99" == d.GetString(ARBDateFormat::Locale));
#endif
		}
		{
			wxLocale locale(wxLANGUAGE_ENGLISH_US);
#ifdef __WXMAC__
			REQUIRE(L"03/02/1999" == d.GetString(ARBDateFormat::Locale));
#else
#if defined(WIN32) || defined(__WXMAC__)
			REQUIRE(L"3/2/1999" == d.GetString(ARBDateFormat::Locale));
#else
			REQUIRE(L"03/02/1999" == d.GetString(ARBDateFormat::Locale));
#endif
#endif
		}
#endif
		REQUIRE(L"03-02-1999" == d.GetString(ARBDateFormat::DashMMDDYYYY));
		REQUIRE(L"03/02/1999" == d.GetString(ARBDateFormat::SlashMMDDYYYY));
		REQUIRE(L"1999-03-02" == d.GetString(ARBDateFormat::DashYYYYMMDD));
		REQUIRE(L"1999/03/02" == d.GetString(ARBDateFormat::SlashYYYYMMDD));
		REQUIRE(L"02-03-1999" == d.GetString(ARBDateFormat::DashDDMMYYYY));
		REQUIRE(L"02/03/1999" == d.GetString(ARBDateFormat::SlashDDMMYYYY));
		REQUIRE(L"3-2-1999" == d.GetString(ARBDateFormat::DashMDY));
		REQUIRE(L"3/2/1999" == d.GetString(ARBDateFormat::SlashMDY));
		REQUIRE(L"1999-3-2" == d.GetString(ARBDateFormat::DashYMD));
		REQUIRE(L"1999/3/2" == d.GetString(ARBDateFormat::SlashYMD));
		REQUIRE(L"2-3-1999" == d.GetString(ARBDateFormat::DashDMY));
		REQUIRE(L"2/3/1999" == d.GetString(ARBDateFormat::SlashDMY));
		REQUIRE(L"19990302" == d.GetString(ARBDateFormat::YYYYMMDD));
	}


	SECTION("Add")
	{
		ARBDate d1(1999, 3, 27);
		ARBDate d2(1999, 3, 30);
		long days = 3;
		ARBDate dt1 = d1 + days;
		REQUIRE(dt1 == d2);
		ARBDate dt2 = d1;
		dt2 += days;
		REQUIRE(dt2 == d2);
		REQUIRE(dt1 == dt2);
	}


	SECTION("Subtract")
	{
		ARBDate d1(1999, 3, 30);
		ARBDate d2(1999, 3, 27);
		long days = 3;
		ARBDate dt1 = d1 - days;
		REQUIRE(dt1 == d2);
		ARBDate dt2 = d1;
		dt2 -= days;
		REQUIRE(dt2 == d2);
		REQUIRE(dt1 == dt2);
	}


	SECTION("FromString")
	{
		ARBDate d = ARBDate::FromString(L"1999-3-27", ARBDateFormat::DashYYYYMMDD);
		REQUIRE(d.IsValid());
		ARBDate d2(1999, 3, 27);
		REQUIRE(d == d2);
		d = ARBDate::FromString(L"1999-3-27", ARBDateFormat::SlashYYYYMMDD); // Reading does not enforce 0-padding
		REQUIRE(!d.IsValid());
		// TODO: Add more complete tests (test each format, bad formats, etc)
	}


#if !defined(__WXWINDOWS__)
#pragma PRAGMA_TODO(need non - wx support in libarb - currently it asserts)
#else
	SECTION("FromStringUK")
	{
		ARBDate d2(1999, 3, 27);
		wxLocale locale(wxLANGUAGE_ENGLISH_UK);
		ARBDate d = ARBDate::FromString(L"27/3/1999", ARBDateFormat::Locale);
		REQUIRE(d.IsValid());
		REQUIRE(d == d2);
	}
#endif


#if !defined(__WXWINDOWS__)
#pragma PRAGMA_TODO(need non - wx support in libarb - currently it asserts)
#else
	SECTION("FromStringUS")
	{
		ARBDate d2(1999, 3, 27);
		wxLocale locale(wxLANGUAGE_ENGLISH_US);
		ARBDate d = ARBDate::FromString(L"3/27/1999", ARBDateFormat::Locale);
		REQUIRE(d.IsValid());
		REQUIRE(d == d2);
	}
#endif


	SECTION("ValidDateString")
	{
		ARBDate d1(1999, 3, 30);
		ARBDate d2(1999, 3, 27);
		wxString s = ARBDate::GetValidDateString(d1, d2);
		REQUIRE(L"[1999-3-30-1999-3-27]" == s);
		d1.clear();
		s = ARBDate::GetValidDateString(d1, d2);
		REQUIRE(L"[*-1999-3-27]" == s);
		s = ARBDate::GetValidDateString(d2, d1);
		REQUIRE(L"[1999-3-27-*]" == s);
	}


	SECTION("ARBDayOfWeek")
	{
		ARBDate dSun(2009, 4, 12);
		ARBDate dMon(2009, 4, 13);
		REQUIRE(0 == dSun.GetDayOfWeek(ARBDayOfWeek::Sunday));
		REQUIRE(1 == dMon.GetDayOfWeek(ARBDayOfWeek::Sunday));
		REQUIRE(0 == dMon.GetDayOfWeek(ARBDayOfWeek::Monday));
	}


	SECTION("DayOfYear")
	{
		ARBDate d1(2009, 1, 1);
		ARBDate d2(2009, 2, 1);
		ARBDate d3(2009, 12, 31);
		ARBDate d4(2004, 12, 31);
		REQUIRE(1 == d1.GetDayOfYear());
		REQUIRE(32 == d2.GetDayOfYear());
		REQUIRE(365 == d3.GetDayOfYear());
		REQUIRE(366 == d4.GetDayOfYear());
	}


	SECTION("DSTDate")
	{
		ARBDate d1(2010, 6, 1);  // A date in DST
		ARBDate d2(2010, 12, 1); // A date not.
		time_t t1;
		d1.GetDate(t1);
		time_t t2;
		d2.GetDate(t2);
		REQUIRE(d1 == ARBDate(t1));
		REQUIRE(d2 == ARBDate(t2));
	}


	SECTION("LeapYear")
	{
		constexpr struct
		{
			int yr;
			bool isLeep;
		} sDates[] = {
			{1900, false},
			{2000, true},
			{2001, false},
			{2004, true},
		};
		for (size_t i = 0; i < _countof(sDates); ++i)
		{
			ARBDate d1(sDates[i].yr, 1, 1);
			REQUIRE(d1.isLeap() == sDates[i].isLeep);
		}
	}
}

} // namespace dconSoft
