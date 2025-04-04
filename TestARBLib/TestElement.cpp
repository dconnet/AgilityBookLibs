/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Test Element class
 * @author David Connet
 *
 * Revision History
 * 2017-11-09 Convert from UnitTest++ to Catch
 * 2017-08-03 Added basic read verification
 * 2012-03-16 Renamed LoadXML functions, added stream version.
 * 2009-09-13 Add support for wxWidgets 2.9, deprecate tstring.
 * 2008-12-27 Replace local LoadTree with LoadXMLData
 * 2008-01-11 Created
 */

#include "stdafx.h"
#include "TestARBLib.h"

#include "ARBCommon/ARBDate.h"
#include "ARBCommon/Element.h"
#include "ARBCommon/StringUtil.h"
#include <sstream>

#if defined(__WXWINDOWS__)
#include <wx/filefn.h>
#include <wx/mstream.h>
#endif

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>
#endif


namespace dconSoft
{
using namespace ARBCommon;


TEST_CASE("Element")
{
	SECTION("Name")
	{
		ElementNodePtr ele = ElementNode::New(L"name");
		REQUIRE(L"name" == ele->GetName());
	}


	SECTION("Value")
	{
		ElementNodePtr ele = ElementNode::New(L"name");
		wxString str = L"This random & text @#$@()<>";
		ele->SetValue(str);
		REQUIRE(str == ele->GetValue());
	}


	SECTION("AddAttrib")
	{
		ElementNodePtr ele = ElementNode::New(L"name");
		bool b = true;
		ele->AddAttrib(L"name", b);
		ARBAttribLookup rc = ele->GetAttrib(L"name", b);
		REQUIRE(ARBAttribLookup::Found == rc);
		REQUIRE(b);
		wxString s;
		rc = ele->GetAttrib(L"name", s);
		REQUIRE(ARBAttribLookup::Found == rc);
		REQUIRE(L"y" == s);
	}


	SECTION("AddAttribShort")
	{
		ElementNodePtr ele = ElementNode::New(L"name");
		short i = 42;
		ele->AddAttrib(L"test", i);
		wxString s;
		ele->GetAttrib(L"test", s);
		REQUIRE(L"42" == s);
		i = 0;
		ele->GetAttrib(L"test", i);
		REQUIRE(42 == i);
	}


	SECTION("AddAttribLong")
	{
		ElementNodePtr ele = ElementNode::New(L"name");
		long i = 42;
		ele->AddAttrib(L"test", i);
		wxString s;
		ele->GetAttrib(L"test", s);
		REQUIRE(L"42" == s);
		i = 0;
		ele->GetAttrib(L"test", i);
		REQUIRE(42 == i);
	}


	SECTION("AddAttribDbl")
	{
		ElementNodePtr ele = ElementNode::New(L"name");
		double i = 42.446;
		ele->AddAttrib(L"test", i);
		wxString s;
		ele->GetAttrib(L"test", s);
		REQUIRE(L"42.45" == s);
		i = 0.0;
		ele->GetAttrib(L"test", i);
		REQUIRE(42.45 == i);

		i = 42.446;
		ele->AddAttrib(L"test", i, 3);
		ele->GetAttrib(L"test", s);
		REQUIRE(L"42.446" == s);
		i = 0.0;
		ele->GetAttrib(L"test", i);
		REQUIRE(42.446 == i);
	}


	SECTION("AddAttribDate")
	{
		ElementNodePtr ele = ElementNode::New(L"name");
		ele->AddAttrib(L"test", L"1999-03-27");
		ARBDate d;
		ARBAttribLookup rc = ele->GetAttrib(L"test", d);
		REQUIRE(ARBAttribLookup::Found == rc);
		REQUIRE(1999 == d.GetYear());
		REQUIRE(3 == d.GetMonth());
		REQUIRE(27 == d.GetDay());
	}


	SECTION("AddAttribBadDate")
	{
		ElementNodePtr ele = ElementNode::New(L"name");
		ele->AddAttrib(L"test", L"1999-99-27");
		ARBDate d;
		ARBAttribLookup rc = ele->GetAttrib(L"test", d);
		REQUIRE(ARBAttribLookup::Invalid == rc);
	}


	SECTION("BadAttrib")
	{
		ElementNodePtr ele = ElementNode::New(L"name");
		ele->AddAttrib(L"test", L"junk");
		ele->AddAttrib(L"test", L"junk2");
		REQUIRE(1 == ele->GetAttribCount());
	}


	SECTION("ReallyBadAttrib")
	{
		ElementNodePtr ele = ElementNode::New(L"name");
		wxString attrib;
		REQUIRE(!ele->AddAttrib(attrib, L"test"));
	}


	SECTION("RemoveAttrib")
	{
		ElementNodePtr ele = ElementNode::New(L"name");
		ele->AddAttrib(L"test", L"junk");
		REQUIRE(1 == ele->GetAttribCount());
		REQUIRE(!ele->RemoveAttrib(L"test1"));
		REQUIRE(1 == ele->GetAttribCount());
		REQUIRE(ele->RemoveAttrib(L"test"));
		REQUIRE(0 == ele->GetAttribCount());
	}


	SECTION("RemoveAllAttribs")
	{
		ElementNodePtr ele = ElementNode::New(L"name");
		ele->AddAttrib(L"test", L"junk");
		ele->AddAttrib(L"test1", L"junk");
		REQUIRE(2 == ele->GetAttribCount());
		ele->RemoveAllAttribs();
		REQUIRE(0 == ele->GetAttribCount());
	}


	SECTION("AddElement")
	{
		ElementNodePtr ele = ElementNode::New(L"name");
		ElementNodePtr newEle = ele->AddElementNode(L"test");
		REQUIRE(L"test" == newEle->GetName());
		REQUIRE(1 == ele->GetElementCount());
		ElementNodePtr ele2 = ele->GetElementNode(0);
		REQUIRE(newEle.get() == ele2.get());
	}


	SECTION("AddElementAt")
	{
		ElementNodePtr ele = ElementNode::New(L"name");
		ele->AddElementNode(L"test1");
		ele->AddElementNode(L"test2", 0);
		REQUIRE(2 == ele->GetElementCount());
		ElementNodePtr newEle = ele->GetElementNode(0);
		REQUIRE(L"test2" == newEle->GetName());
		newEle = ele->GetElementNode(1);
		REQUIRE(L"test1" == newEle->GetName());
	}


	SECTION("RemoveElement")
	{
		ElementNodePtr ele = ElementNode::New(L"name");
		ele->AddElementNode(L"test1");
		ele->AddElementNode(L"test2");
		REQUIRE(2 == ele->GetElementCount());
		ele->RemoveElement(0);
		REQUIRE(1 == ele->GetElementCount());
	}


	SECTION("FindElement")
	{
		ElementNodePtr ele = ElementNode::New(L"name");
		ele->AddElementNode(L"test1");
		ele->AddElementNode(L"test2");
		REQUIRE(2 == ele->GetElementCount());
		REQUIRE(1 == ele->FindElement(L"test2"));
	}


	SECTION("FindElementFrom")
	{
		ElementNodePtr ele = ElementNode::New(L"name");
		ele->AddElementNode(L"test1");
		ele->AddElementNode(L"test2");
		ele->AddElementNode(L"test1");
		ele->AddElementNode(L"test2");
		REQUIRE(4 == ele->GetElementCount());
		REQUIRE(3 == ele->FindElement(L"test2", 2));
	}


	SECTION("LoadXML")
	{
		std::stringstream data;
		// clang-format off
		data << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
			 << "<Test attrib='a'>\n"
			 << "<ele>Content</ele>\n"
			 << "<ele ele='2'>More content</ele>"
			 << "</Test>";
		// clang-format on

		wxString errMsg;
		ElementNodePtr tree(ElementNode::New());
		REQUIRE(tree->LoadXML(data, errMsg));

		wxString str;
		REQUIRE(tree->GetName() == L"Test");
		REQUIRE(tree->GetAttribCount() == 1);
		REQUIRE(tree->GetAttrib(L"attrib", str) == ARBAttribLookup::Found);
		REQUIRE(str == L"a");
		REQUIRE(tree->GetElementCount() == 2);
		REQUIRE(tree->GetElementNode(0)->GetAttribCount() == 0);
		REQUIRE(tree->GetElementNode(1)->GetAttribCount() == 1);
		REQUIRE(tree->GetElementNode(1)->GetAttrib(L"ele", str) == ARBAttribLookup::Found);
		REQUIRE(str == L"2");
		REQUIRE(tree->GetElementNode(0)->GetValue() == L"Content");
		REQUIRE(tree->GetElementNode(1)->GetValue() == L"More content");
	}


	SECTION("Save")
	{
		std::stringstream data;
		// clang-format off
		data << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
			 << "<Test attrib='a'>\n"
			 << "<ele>Content</ele>\n"
			 << "<ele ele='2'>More content</ele>"
			 << "</Test>";
		const std::string formattedData("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n\
<Test attrib=\"a\">\n\
  <ele>Content</ele>\n\
  <ele ele=\"2\">More content</ele>\n\
</Test>\n");
		// clang-format on

		wxString errMsg;
		ElementNodePtr tree(ElementNode::New());
		REQUIRE(tree->LoadXML(data, errMsg));

		wxString tmpFile(L"data.tmp");
		std::stringstream tmp1;
		REQUIRE(tree->SaveXML(tmpFile));
		REQUIRE(tree->SaveXML(tmp1));

		ElementNodePtr tree2(ElementNode::New());
		wxString errs;
		REQUIRE(tree2->LoadXML(tmpFile, errs));

#if defined(__WXWINDOWS__)
		wxRemoveFile(tmpFile);
#else
#pragma PRAGMA_TODO(remove file)
#endif

		std::stringstream tmp2;
		REQUIRE(tree2->SaveXML(tmp2));

		std::string tmp1data = tmp1.str();
		std::string tmp2data = tmp2.str();
		REQUIRE(tmp1data == tmp2data);
		REQUIRE(tmp1data == formattedData);
	}
}

} // namespace dconSoft
