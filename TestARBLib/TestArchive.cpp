/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Test LibArchive
 * @author David Connet
 *
 * Revision History
 * 2017-11-09 Convert from UnitTest++ to Catch
 * 2013-07-29 Created
 */

#include "stdafx.h"
#include "TestARBLib.h"

#include "ARBCommon/LibArchive.h"
#include "ARBCommon/StringUtil.h"

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>
#endif


namespace dconSoft
{
using namespace ARBCommon;


TEST_CASE("Archive")
{
#ifdef WIN32
	constexpr char FileData1[] = "This is test1\r\nOk";
	constexpr char FileData2[] = "This is test2\r\nOk\r\n";
#endif

	SECTION("ExtractFileFromRes")
	{
		CLibArchive archive(L"TestArchive.zip", ArchiveLocation::Resource);

		{
			std::ostringstream data;
#ifdef WIN32
			REQUIRE(archive.Extract(L"test1.txt", data));
			REQUIRE(data.str() == FileData1);
#else
			REQUIRE(!archive.Extract(L"test1.txt", data));
#endif
		}

		{
			std::ostringstream data;
#ifdef WIN32
			REQUIRE(archive.Extract(L"test2.txt", data));
			REQUIRE(data.str() == FileData2);
#else
			REQUIRE(!archive.Extract(L"test2.txt", data));
#endif
		}
	}

#ifndef __WXWINDOWS__
	constexpr char FileData3[] = "This is test3\r\nReplaced\r\n";

	static std::wstring CreateZip()
	{
		return std::wstring();
	}

	SECTION("Replace")
	{
		std::wstring file = CreateZip();
		REQUIRE(!file.empty());
		if (!file.empty())
		{
			CLibArchive archive(file);
			std::istringstream data(FileData3);
			REQUIRE(archive.ReplaceFile(L"test1.txt", data));
			_unlink(StringUtil::stringA(file).c_str());
		}
		TODO_TEST
		// See: http://docs.wxwidgets.org/stable/wx_wxarc.html#wxarcmodify
	}


	SECTION("Extract")
	{
		std::wstring file = CreateZip();
		REQUIRE(!file.empty());

		if (!file.empty())
		{
			CLibArchive archive(file);

			{
				std::ostringstream data;
				REQUIRE(archive.Extract(L"test1.txt", data));
				REQUIRE(data.str() == FileData1);
			}

			{
				std::ostringstream data;
				REQUIRE(archive.Extract(L"test2.txt", data));
				REQUIRE(data.str() == FileData2);
			}

			_unlink(StringUtil::stringA(file).c_str());
		}
	}
#endif
}

} // namespace dconSoft
