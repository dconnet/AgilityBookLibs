/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Test ARBVersion class
 * @author David Connet
 *
 * Revision History
 * 2018-08-15 Changed VERSION_NUMBER to std::array, added more CVersionNum tests.
 * 2017-11-09 Convert from UnitTest++ to Catch
 * 2012-07-30 Add CVersionNum tests.
 * 2011-08-22 ARBVersion was only using 16 instead of 32bits.
 * 2008-01-12 Created
 */

#include "stdafx.h"
#include "TestARBLib.h"

#include "ARBCommon/ARBTypes.h"
#include "ARBCommon/VersionNum.h"

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>
#endif


namespace dconSoft
{
using namespace ARBCommon;


TEST_CASE("ARBVersion")
{
	SECTION("ctor")
	{
		unsigned short maj = 0, minor = 0;
		ARBVersion v;
		REQUIRE(maj == v.Major());
		REQUIRE(minor == v.Minor());

		maj = 1;
		minor = 2;
		ARBVersion v2(maj, minor);
		REQUIRE(maj == v2.Major());
		REQUIRE(minor == v2.Minor());
	}


	SECTION("str")
	{
		ARBVersion v(1, 2);
		REQUIRE(L"1.2" == v.str());
	}


	SECTION("str2")
	{
		ARBVersion v(L"1.2");
		REQUIRE(v.Major() == 1);
		REQUIRE(v.Minor() == 2);
		REQUIRE(L"1.2" == v.str());
	}


	SECTION("Comparison")
	{
		ARBVersion v1(1, 2);
		ARBVersion v2(2, 1);
		REQUIRE(v1 < v2);
	}


	SECTION("Bounds")
	{
		unsigned short maj = 0xefff;
		unsigned short min = 0xeffe;
		ARBVersion v1(maj, min);
		REQUIRE(v1.Major() == maj);
		REQUIRE(v1.Minor() == min);
	}
}


TEST_CASE("VersionNum")
{
	SECTION("VerParse")
	{
		CVersionNum v;
		REQUIRE(v.Parse(L"1.2.3.4"));
		CVersionNum::VERSION_NUMBER ver;
		v.GetVersion(ver);
		REQUIRE(ver[0] == 1);
		REQUIRE(ver[1] == 2);
		REQUIRE(ver[2] == 3);
		REQUIRE(ver[3] == 4);

		REQUIRE_FALSE(v.Parse(L"2.3.4"));
		REQUIRE(ver[0] == 1);
		REQUIRE(ver[1] == 2);
		REQUIRE(ver[2] == 3);
		REQUIRE(ver[3] == 4);
	}


	SECTION("VerCtor")
	{
		CVersionNum v(L"1.2.3.4");
		CVersionNum::VERSION_NUMBER ver;
		v.GetVersion(ver);
		REQUIRE(ver[0] == 1);
		REQUIRE(ver[1] == 2);
		REQUIRE(ver[2] == 3);
		REQUIRE(ver[3] == 4);
	}


	SECTION("VerCtor2")
	{
		CVersionNum v(L"1.2.3");
		REQUIRE_FALSE(v.Valid());
	}


	SECTION("VerEq")
	{
		CVersionNum v1, v2;
		v1.Assign(1, 2, 3, 4);
		v2.Assign(1, 2, 3, 4);
		REQUIRE(v1 == v2);
	}


	SECTION("VerComp")
	{
		CVersionNum v1, v2;
		v1.Assign(1, 2, 3, 4);
		v2.Assign(2, 1, 3, 4);
		REQUIRE(v1 < v2);
		REQUIRE(v2 > v1);

		v2.Assign(1, 2, 3, 5);
		REQUIRE(v1 < v2);
		REQUIRE(v2 > v1);
	}


	SECTION("VerAssign")
	{
		CVersionNum v(L"1.2.3.4");
		REQUIRE(v.Valid());
		v.Assign(0, 0, 0, 0);
		REQUIRE_FALSE(v.Valid());
		v.Assign(0, 0, 0, 1);
		REQUIRE(v.Valid());
	}


	SECTION("Parse0")
	{
		CVersionNum v(L"0.0.0.0");
		REQUIRE_FALSE(v.Valid());

		v.Parse(L"1.2.3.4");
		REQUIRE(v.Valid());
		CVersionNum::VERSION_NUMBER ver;
		v.GetVersion(ver);
		REQUIRE(ver[0] == 1);
		REQUIRE(ver[1] == 2);
		REQUIRE(ver[2] == 3);
		REQUIRE(ver[3] == 4);

		v.Parse(L"0.0.0.0");
		REQUIRE_FALSE(v.Valid());
		v.GetVersion(ver);
		REQUIRE(ver[0] == 0);
		REQUIRE(ver[1] == 0);
		REQUIRE(ver[2] == 0);
		REQUIRE(ver[3] == 0);
	}


	SECTION("str")
	{
		CVersionNum v(1, 2, 3, 4);
		REQUIRE(v.GetVersionString(0) == L"1.2.3.4");
		REQUIRE(v.GetVersionString(1) == L"1");
		REQUIRE(v.GetVersionString(2) == L"1.2");
		REQUIRE(v.GetVersionString(3) == L"1.2.3");
		REQUIRE(v.GetVersionString(4) == L"1.2.3.4");
		REQUIRE(v.GetVersionString(5) == L"1.2.3.4");
	}
}

} // namespace dconSoft
