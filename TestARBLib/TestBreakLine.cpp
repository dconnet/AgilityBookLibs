/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Test line parsing routines
 * @author David Connet
 *
 * Revision History
 * 2017-11-09 Convert from UnitTest++ to Catch
 * 2012-07-25 Add 2 multiline CSV tests.
 * 2010-10-17 Created
 */

#include "stdafx.h"
#include "TestARBLib.h"

#include "ARBCommon/BreakLine.h"

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>
#endif


namespace dconSoft
{
using namespace ARBCommon;

namespace
{

void GetFields(std::vector<wxString>& fields)
{
	fields.clear();
	// This is the same as field5 and fieldMore[12]
	fields.push_back(L"fld");
	fields.push_back(L"line\n;line");
	fields.push_back(L"\"quote\" here");
	fields.push_back(wxString());
	fields.push_back(L"");
}


bool VerifyFields(std::vector<wxString> const& fields1, std::vector<wxString> const& fields2)
{
	if (fields1.size() != fields2.size())
		return false;
	std::vector<wxString>::const_iterator i1 = fields1.begin();
	std::vector<wxString>::const_iterator i2 = fields2.begin();
	for (; i1 != fields1.end(); ++i1, ++i2)
	{
		if (*i1 != *i2)
			return false;
	}
	return true;
}

} // namespace


TEST_CASE("BreakLine")
{
	// String
	constexpr wchar_t record4[] = L"fld;fld;;fld";
	constexpr wchar_t record7[] = L"fld;fld;;fld;f\"f;f6;f7";
	constexpr wchar_t record5[] = L"fld;\"line\n;line\";\"\"\"quote\"\" here\";;";
	constexpr wchar_t recordMore1a[] = L"fld;\"line";
	constexpr wchar_t recordMore2a[] = L";line\";\"\"\"quote\"\" here\";;";
	constexpr wchar_t recordMore1b[] = L"2010-10-30;Name;\"Subname\";\"Line 1";
	constexpr wchar_t recordMore2b[] = L"Line 2\"";
	constexpr wchar_t recordMore1c[] = L"field1;\"Line1";
	constexpr wchar_t recordMore2c[] = L"Line2";
	constexpr wchar_t recordMore2cb[] = L"";
	constexpr wchar_t recordMore3c[] = L"Line3\";field3";


	SECTION("BreakLine")
	{
		std::vector<wxString> fields;
		REQUIRE(4u == BreakLine(';', record4, fields));
		REQUIRE(4u == fields.size());
		REQUIRE(4u == BreakLine(';', record4, fields, true));
		REQUIRE(3u == fields.size());
		REQUIRE(7u == BreakLine(';', record7, fields));
		REQUIRE(7u == fields.size());
		REQUIRE(7u == BreakLine(';', record7, fields, true));
		REQUIRE(6u == fields.size());
	}


	SECTION("ReadCSV")
	{
		std::vector<wxString> fields;
		REQUIRE(ReadStatus::Error == ReadCSV(';', L"f\";", fields));
		REQUIRE(ReadStatus::Error == ReadCSV(';', record7, fields));
		REQUIRE(ReadStatus::Ok == ReadCSV(';', record5, fields));
		REQUIRE(5u == fields.size());
		if (5u == fields.size())
		{
			std::vector<wxString> fields2;
			GetFields(fields2);
			REQUIRE(VerifyFields(fields, fields2));
		}
	}


	SECTION("ReadCSVMultiLine1")
	{
		std::vector<wxString> fields;
		REQUIRE(ReadStatus::NeedMore == ReadCSV(';', recordMore1a, fields));
		REQUIRE(ReadStatus::Ok == ReadCSV(';', recordMore2a, fields, true));
		REQUIRE(5u == fields.size());
		if (5u == fields.size())
		{
			std::vector<wxString> fields2;
			GetFields(fields2);
			REQUIRE(VerifyFields(fields, fields2));
		}
	}


	SECTION("ReadCSVMultiLine2")
	{
		std::vector<wxString> fields;
		REQUIRE(ReadStatus::NeedMore == ReadCSV(';', recordMore1b, fields));
		REQUIRE(ReadStatus::Ok == ReadCSV(';', recordMore2b, fields, true));
		REQUIRE(4u == fields.size());
		if (4u == fields.size())
		{
			REQUIRE(fields[0] == L"2010-10-30");
			REQUIRE(fields[1] == L"Name");
			REQUIRE(fields[2] == L"Subname");
			REQUIRE(fields[3] == L"Line 1\nLine 2");
		}
	}


	SECTION("ReadCSVMultiLine3")
	{
		std::vector<wxString> fields;
		REQUIRE(ReadStatus::NeedMore == ReadCSV(';', recordMore1c, fields));
		REQUIRE(ReadStatus::NeedMore == ReadCSV(';', recordMore2c, fields, true));
		REQUIRE(ReadStatus::Ok == ReadCSV(';', recordMore3c, fields, true));
		REQUIRE(3u == fields.size());
		if (3u == fields.size())
		{
			REQUIRE(fields[0] == L"field1");
			REQUIRE(fields[1] == L"Line1\nLine2\nLine3");
			REQUIRE(fields[2] == L"field3");
		}
	}


	SECTION("ReadCSVMultiLine4")
	{
		std::vector<wxString> fields;
		REQUIRE(ReadStatus::NeedMore == ReadCSV(';', recordMore1c, fields));
		REQUIRE(ReadStatus::NeedMore == ReadCSV(';', recordMore2c, fields, true));
		REQUIRE(ReadStatus::NeedMore == ReadCSV(';', recordMore2cb, fields, true));
		REQUIRE(ReadStatus::Ok == ReadCSV(';', recordMore3c, fields, true));
		REQUIRE(3u == fields.size());
		if (3u == fields.size())
		{
			REQUIRE(fields[0] == L"field1");
			REQUIRE(fields[1] == L"Line1\nLine2\n\nLine3");
			REQUIRE(fields[2] == L"field3");
		}
	}


	SECTION("WriteCSV")
	{
		std::vector<wxString> fields;
		GetFields(fields);
		wxString data = WriteCSV(';', fields);
		REQUIRE(data == record5);
	}
}

} // namespace dconSoft
