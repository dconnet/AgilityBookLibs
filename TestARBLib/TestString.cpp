/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Test string util functions
 * @author David Connet
 *
 * Revision History
 * 2018-12-16 Convert to fmt.
 * 2017-11-09 Convert from UnitTest++ to Catch
 * 2015-11-27 Remove WIN32 ifdef from tests.
 * 2008-06-29 Created
 */

#include "stdafx.h"
#include "TestARBLib.h"

#include "ARBCommon/ARBMisc.h"
#include "ARBCommon/StringUtil.h"
#include "fmt/printf.h"
#include "fmt/xchar.h"
#include <algorithm>
#include <locale>

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>
#endif


namespace dconSoft
{
using namespace ARBCommon;


TEST_CASE("String")
{
	SECTION("Convert_ToWide")
	{
		std::string s("narrow");
		std::wstring s1 = StringUtil::stringW(s);
		REQUIRE(L"narrow" == s1);
#if defined(__WXWINDOWS__)
		wxString s2 = StringUtil::stringWX(s);
		REQUIRE(L"narrow" == s2);
#endif
	}


	SECTION("Convert_ToNarrow")
	{
		std::wstring s(L"wide");
		std::string s1 = StringUtil::stringA(s);
		REQUIRE("wide" == s1);
#if defined(__WXWINDOWS__)
		wxString s2 = StringUtil::stringWX(s);
		REQUIRE(L"wide" == s2);
#endif
	}


	// We know this will fail using wcstombs.
	SECTION("Convert_Multi")
	{
		// http://www.ftrain.com/unicode/#65275
		wchar_t w = 0xFEFB; // In courier new, Arabic Ligature Lam With Alef Isolated Form (see 'Character Map' program)
		std::wstring s(1, w);
		std::string s2 = StringUtil::stringA(s);
		REQUIRE(s.length() == 1u);
		// MBCS: 0, UTF8: 3
		REQUIRE(s2.length() == 3u);
	}


	SECTION("Convert_Multi2")
	{
		// http://www.ftrain.com/unicode/#247
		wchar_t w = 0x00f7; // Division sign
		std::wstring s(1, w);
		std::string s2 = StringUtil::stringA(s);
		REQUIRE(s.length() == 1u);
		// MBCS: 1, UTF8: 2
		REQUIRE(s2.length() > 0u);
	}


	SECTION("AtolGoodData")
	{
		std::wstring s1(L"123");
		long a1 = StringUtil::ToCLong(s1);
		REQUIRE(a1 == 123);
		REQUIRE(StringUtil::ToCLong(s1, a1));
	}


	SECTION("AtolBadData")
	{
		std::wstring s2(L"12-3");
		long a2 = StringUtil::ToCLong(s2);
		REQUIRE(a2 == 12);
		REQUIRE(!StringUtil::ToCLong(s2, a2));
		REQUIRE(a2 == 12);
		REQUIRE(!StringUtil::ToCLong(s2, a2, true));
		REQUIRE(a2 == 12);
	}


	SECTION("AtodGoodData")
	{
		std::wstring s1(L"12.3");
		double a1 = StringUtil::ToCDouble(s1);
		REQUIRE(a1 == 12.3);
		REQUIRE(StringUtil::ToCDouble(s1, a1));
	}


	SECTION("AtodBadData")
	{
		std::wstring s2(L"1.3-12");
		double a2;
		REQUIRE(!StringUtil::ToCDouble(s2, a2));
		REQUIRE(a2 == 1.3);
	}


	SECTION("AtodUS")
	{
		wxLocale locale(wxLANGUAGE_ENGLISH_US, wxLOCALE_DONT_LOAD_DEFAULT);
		std::wstring s1(L"12.3");
		double a1 = StringUtil::ToDouble(s1);
		REQUIRE(a1 == 12.3);
		std::wstring s2(L"1.3-12");
		double a2;
		bool bParsed = StringUtil::ToDouble(s2, a2);
		REQUIRE(a2 == 1.3);
		REQUIRE(!bParsed);
	}


	SECTION("AtodFR")
	{
		wxLocale locale(wxLANGUAGE_FRENCH, wxLOCALE_DONT_LOAD_DEFAULT);
		std::wstring s1(L"12,3");
		double a1 = StringUtil::ToDouble(s1);
		REQUIRE(a1 == 12.3);
		std::wstring s2(L"1,3-12");
		double a2;
		bool bParsed = StringUtil::ToDouble(s2, a2);
		REQUIRE(a2 == 1.3);
		REQUIRE(!bParsed);
	}


	SECTION("AtodFR2")
	{
		// Even in French, I want to have "." separators parse properly.
		wxLocale locale(wxLANGUAGE_FRENCH, wxLOCALE_DONT_LOAD_DEFAULT);
		std::wstring s1(L"12.3");
		double a1 = StringUtil::ToDouble(s1);
		REQUIRE(a1 == 12.3);
	}


	SECTION("ReplaceA")
	{
		std::string s("This is a test");
		std::string s2 = StringUtil::Replace(s, "is a", "");
		REQUIRE("This  test" == s2);
		s2 = StringUtil::Replace(s2, " test", "good");
		REQUIRE("This good" == s2);
	}


	SECTION("ReplaceW")
	{
		std::wstring s(L"This is a test");
		std::wstring s2 = StringUtil::Replace(s, L"is a", L"");
		REQUIRE(L"This  test" == s2);
		s2 = StringUtil::Replace(s2, L" test", L"good");
		REQUIRE(L"This good" == s2);
	}


	SECTION("ToLowerA")
	{
		std::string s("This is a TEST");
		std::string s2 = StringUtil::ToLower(s);
		REQUIRE("this is a test" == s2);
	}


	SECTION("ToLowerW")
	{
		std::wstring s(L"This is a TEST");
		std::wstring s2 = StringUtil::ToLower(s);
		REQUIRE(L"this is a test" == s2);
	}


	SECTION("ToUpperA")
	{
		std::string s("This is a TEST");
		std::string s2 = StringUtil::ToUpper(s);
		REQUIRE("THIS IS A TEST" == s2);
	}


	SECTION("ToUpperW")
	{
		std::wstring s(L"This is a TEST");
		std::wstring s2 = StringUtil::ToUpper(s);
		REQUIRE(L"THIS IS A TEST" == s2);
	}


	SECTION("Formatting")
	{
		REQUIRE(L"two one" == fmt::sprintf(L"%2$s %1$s", L"one", L"two"));
		REQUIRE(L"two one" == fmt::format(L"{1} {0}", L"one", L"two"));
		REQUIRE(L"    " == fmt::format(L"{:{}}", L" ", 4));
		REQUIRE(L"000 " == fmt::format(L"{:0>{}}", L" ", 4));
	}


	SECTION("Trim")
	{
		std::wstring str(L"  xyx  ");
		REQUIRE(StringUtil::Trim(str) == L"xyx");
		REQUIRE(StringUtil::TrimLeft(str) == L"xyx  ");
		REQUIRE(StringUtil::TrimRight(str) == L"  xyx");
	}


	SECTION("TrimChar")
	{
		std::wstring str(L"\"xyx\"");
		REQUIRE(StringUtil::Trim(str, '"') == L"xyx");
		REQUIRE(StringUtil::TrimLeft(str, '"') == L"xyx\"");
		REQUIRE(StringUtil::TrimRight(str, '"') == L"\"xyx");
	}


	SECTION("Sort")
	{
		if (StringUtil::CanCompareDigits())
		{

			std::vector<std::wstring> items;
			items.push_back(L"1a");
			items.push_back(L"10a");
			items.push_back(L"2a");

			std::stable_sort(items.begin(), items.end(), [](std::wstring const& one, std::wstring const& two) {
				return StringUtil::CompareNoCase(one, two) < 0;
			});

			REQUIRE(items[0] == L"1a");
			REQUIRE(items[1] == L"2a");
			REQUIRE(items[2] == L"10a");
		}
	}


	SECTION("Sort2")
	{
		if (StringUtil::CanCompareDigits())
		{
			std::vector<std::wstring> items;
			items.push_back(L"bob");
			items.push_back(L"Bob");
			items.push_back(L"Aa");
			items.push_back(L"2a");
			items.push_back(L"a");

			std::stable_sort(items.begin(), items.end(), [](std::wstring const& one, std::wstring const& two) {
				return StringUtil::CompareNoCase(one, two) < 0;
			});

			REQUIRE(items[0] == L"2a");
			REQUIRE(items[1] == L"a");
			REQUIRE(items[2] == L"Aa");
			// Case insensitive - so these should be same order as inserted
			REQUIRE(items[3] == L"bob");
			REQUIRE(items[4] == L"Bob");
		}
	}


	SECTION("Sort3")
	{
		if (StringUtil::CanCompareDigits())
		{
			std::vector<std::wstring> items;
			items.push_back(L"Bob");
			items.push_back(L"bob");
			items.push_back(L"Aa");
			items.push_back(L"2a");
			items.push_back(L"a");

			// Note: Ignore case simply means "bob" == "Bob".
			// It does not mean that lower case sorts before (or after) upper case.
			std::stable_sort(items.begin(), items.end(), [](std::wstring const& one, std::wstring const& two) {
				return StringUtil::CompareNoCase(one, two) < 0;
			});

			REQUIRE(items[0] == L"2a");
			REQUIRE(items[1] == L"a");
			REQUIRE(items[2] == L"Aa");
			// Case insensitive - so these should be same order as inserted
			REQUIRE(items[3] == L"Bob");
			REQUIRE(items[4] == L"bob");
		}
	}
}

} // namespace dconSoft
