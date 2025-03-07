/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Test MD5 class
 * @author David Connet
 *
 * Revision History
 * 2017-11-09 Convert from UnitTest++ to Catch
 * 2010-02-07 Created
 */

#include "stdafx.h"
#include "TestARBLib.h"

#include "ARBCommon/ARBMsgDigest.h"
#include <sstream>

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>
#endif


namespace dconSoft
{
using namespace ARBCommon;


TEST_CASE("MsgDigest")
{
	// String
	constexpr char RawString[] = "This is a test of a string";
	static wxString DigestStringMD5(L"b36b52c4835d88fdb548087b9a829bf1");
	static wxString DigestStringSHA1(L"7d56b53d54b141cb77e465abcfe63436a35ae222");
	static wxString DigestStringSHA256(L"5d2819684143b99d8b9c9a254e1b5584529a3fe947862e8ae15e246eda292c37");


	SECTION("RawDecode")
	{
		std::stringstream buffer(RawString);
		wxString digest = ARBMsgDigest::Compute(buffer, ARBMsgDigest::ARBDigest::MD5);
		REQUIRE(digest == DigestStringMD5);
	}


	SECTION("RawDecodeSha1")
	{
		std::stringstream buffer(RawString);
		wxString digest = ARBMsgDigest::Compute(buffer, ARBMsgDigest::ARBDigest::SHA1);
		REQUIRE(digest == DigestStringSHA1);
	}


	SECTION("RawDecodeSha256")
	{
		std::stringstream buffer(RawString);
		wxString digest = ARBMsgDigest::Compute(buffer, ARBMsgDigest::ARBDigest::SHA256);
		REQUIRE(digest == DigestStringSHA256);
	}
}

} // namespace dconSoft
