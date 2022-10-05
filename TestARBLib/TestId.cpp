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
#ifdef __WXMSW__
		REQUIRE(!id.IsNull());
#endif
	}


	SECTION("Create")
	{
		CUniqueId id;
#ifdef __WXMSW__
		REQUIRE(id.Create());
		REQUIRE(!id.IsNull());
#else
		// Only implemented on Windows for now.
		REQUIRE(!id.Create());
#endif
	}


	SECTION("Equal")
	{
#ifdef __WXMSW__
		CUniqueId id1, id2;
		REQUIRE(id1.Create());
		REQUIRE(id2.Create());
		REQUIRE(id1 != id2);
#endif
	}


	SECTION("Formats")
	{
#ifdef __WXMSW__
		constexpr wchar_t* k_uuids[] = {
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
#endif
	}


	SECTION("Strings")
	{
#ifdef __WXMSW__
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
#endif
	}
}

} // namespace ARBCommon
} // namespace dconSoft
