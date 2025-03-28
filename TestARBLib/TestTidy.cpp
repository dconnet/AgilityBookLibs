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

#include <sstream>
#include <stdarg.h>

#if defined(__WXWINDOWS__)
#include <wx/stdpaths.h>
#endif

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>
#endif


namespace dconSoft
{
using namespace ARBCommon;
using namespace ARBWin;


TEST_CASE("LibTidy")
{
	SECTION("tidy")
	{
		std::stringstream filedata;
		REQUIRE(CResourceManager::Get()->LoadFile(L"tidytest.xml", filedata));

		std::string data(filedata.str());

		std::string errTidy;
		std::string debug;
		auto treeData = TidyHtml::TidyHtmlData(data, errTidy, &debug);
		REQUIRE(!treeData.empty());

		wxString err;
		if (!errTidy.empty())
			err << errTidy;

		ElementNodePtr tidyTree = ElementNode::New();
		if (!tidyTree->LoadXML(treeData.data(), treeData.length(), err))
		{
			tidyTree.reset();
		}
		REQUIRE(tidyTree);
		// if (!tidyTree)
		//{
		//	if (err.empty())
		//		err = <some error msg>
		//	wxMessageBox(err, wxMessageBoxCaptionStr, wxOK | wxCENTRE);
		//}
	}
}

} // namespace dconSoft
