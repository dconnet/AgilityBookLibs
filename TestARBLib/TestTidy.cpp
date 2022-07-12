/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Test tidy
 * @author David Connet
 *
 * Revision History
 * 2020-02-25 Created
 */

#include "stdafx.h"
#include "TestARBLib.h"

#include "ARBCommon/ARBUtils.h"
#include "ARBCommon/Element.h"
#include "ARBCommon/StringUtil.h"
#include "LibARBWin/ResourceManager.h"
#include "LibTidyHtml/LibTidyHtml.h"
#include "fmt/printf.h"

#include <stdarg.h>

#if defined(__WXWINDOWS__)
#include <wx/stdpaths.h>
#endif

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>
#endif

using namespace dconSoft;
using namespace dconSoft::ARBCommon;


TEST_CASE("LibTidy")
{
	SECTION("tidy")
	{
		std::stringstream filedata;
		REQUIRE(CResourceManager::Get()->LoadFile(L"tidytest.xml", filedata));

		std::string data(filedata.str());

		fmt::memory_buffer errTidy;
		std::string debug;
		auto treeData = TidyHtml::TidyHtmlData(data, errTidy, &debug);
		REQUIRE(!treeData.empty());

		fmt::wmemory_buffer err;
		auto msgTidy = StringUtil::stringW(fmt::to_string(errTidy));
		if (!msgTidy.empty())
			fmt::format_to(std::back_inserter(err), L"{}", msgTidy);

		ElementNodePtr tidyTree = ElementNode::New();
		if (!tidyTree->LoadXML(treeData.data(), treeData.length(), err))
		{
			tidyTree.reset();
		}
		REQUIRE(tidyTree);
		// if (!tidyTree)
		//{
		//	std::wstring msg = fmt::to_string(err);
		//	if (msg.empty())
		//		msg = fmt::format(_("IDS_ERR_PARSING_DATA").wx_str(), inAddress);
		//	wxMessageBox(msg, wxMessageBoxCaptionStr, wxOK | wxCENTRE);
		//}
	}
}
