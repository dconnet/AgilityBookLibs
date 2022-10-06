/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Test UniqueId functions
 *
 * Revision History
 * 2022-10-05 Created
 */

#include "stdafx.h"
#include "TestARBLib.h"

#include "ARBCommon/UniqueId.h"

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>
#endif

namespace dconSoft
{
namespace ARBCommon
{

TEST_CASE("UniqueId")
{
	SECTION("Null")
	{
		CUniqueId id;
		REQUIRE(id.IsNull());
		std::wstring uuid(L"00000000-0000-0000-0000-000000000000");
		REQUIRE(id.ToString() == uuid);
	}


	SECTION("AutoCreate")
	{
		CUniqueId id(true);
		REQUIRE(!id.IsNull());
	}


	SECTION("clear")
	{
		CUniqueId id(true);
		REQUIRE(!id.IsNull());
		id.clear();
		REQUIRE(id.IsNull());
	}


	SECTION("Create")
	{
		CUniqueId id;
		REQUIRE(id.Create());
		REQUIRE(!id.IsNull());
	}


	SECTION("Equal")
	{
		CUniqueId id1, id2;
		REQUIRE(id1.Create());
		REQUIRE(id2.Create());
		REQUIRE(id1 != id2);
	}


	SECTION("Formats")
	{
		static const wchar_t* k_uuids[] = {
			L"fbec55d8-6243-4142-b534-0e96c9f12270",
			L"{fbec55d8-6243-4142-b534-0e96c9f12270}",
			L"fbec55d862434142b5340e96c9f12270",
			L"{fbec55d862434142b5340e96c9f12270}",
		};
		for (auto uuid : k_uuids)
		{
			CUniqueId id(uuid);
			REQUIRE(!id.IsNull());
		}
	}


	SECTION("Strings")
	{
		std::wstring uuid(L"fbec55d8-6243-4142-b534-0e96c9f12270");
		CUniqueId id(uuid);
		REQUIRE(!id.IsNull());
		REQUIRE(id.ToString() == uuid);

		// Uuids are not case sensitive.
		std::wstring uuid2(L"FBEC55D8-6243-4142-B534-0E96C9F12270");
		CUniqueId id2(uuid2);
		REQUIRE(!id2.IsNull());
		REQUIRE(id == id2);
		// It always creates lower case uuids.
		REQUIRE(id2.ToString() != uuid2);
		REQUIRE(id2.ToString() == uuid);
	}


	SECTION("Parse")
	{
		std::wstring uuid(L"fbec55d8-6243-4142-b534-0e96c9f12270");
		CUniqueId id;
		REQUIRE(id.IsNull());
		REQUIRE(id.ParseString(uuid));
		REQUIRE(!id.IsNull());

		std::wstring uuidBad(L"fbec55d8-6243-4142-b534-0e96c");
		REQUIRE(!id.ParseString(uuidBad));
		REQUIRE(id.IsNull());
	}

}

} // namespace ARBCommon
} // namespace dconSoft
