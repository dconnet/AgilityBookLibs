/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Tree structure to store XML.
 * @author David Connet
 *
 * Actual reading and writing of XML is done using wxWidgets
 *
 * Revision History
 * 2022-08-29 Add UTC wxDateTime support.
 * 2022-01-31 Add wxDateTime support.
 * 2017-08-03 Added initial expat support (reader, not write)
 * 2015-04-04 Add support for C99 printf formats. (Breaking change)
 * 2014-06-09 Move string->arbversion parsing to ARBVersion.
 * 2014-03-31 Fixed POCO xml load.
 * 2014-02-26 Add support for POCO xml.
 * 2013-03-23 Implement libxml LoadXML stream api.
 * 2012-11-25 Add libxml support back in.
 * 2012-09-29 Trap wx generated xml parsing errors into our buffer.
 * 2012-04-10 Based on wx-group thread, use std::string for internal use
 * 2012-03-16 Renamed LoadXML functions, added stream version.
 * 2009-09-13 Add support for wxWidgets 2.9, deprecate tstring.
 * 2009-03-12 Converting all TCHAR stuff to wxWidgets
 * 2009-02-08 Fix wxWidget xml creation
 * 2009-01-05 Added libxml2 support
 * 2008-12-27 Added wxWidget support (xml)
 * 2008-11-02 Added xerces 3.0 support
 * 2007-09-06 Added GetNthElementNode
 * 2007-08-15 Modified to support mixed text/nodes.
 * 2007-08-08 Moved initialization here, so all XML usage is contained.
 * 2007-03-37 Fixed a problem releasing transcoded data.
 * 2005-06-09 Numbers were being stored/shown in scientific notation.
 * 2004-06-16 Changed ARBDate::GetString to put leadingzero into format.
 * 2004-01-04 Moved date parsing code to ARBDate::FromString.
 * 2003-11-26 Changed version number to a complex value.
 * 2003-10-22 Added a DTD parameter to SaveXML.
 * Code evolved to AgilityRecordBook Element
 * 2002-11-27 Added additional SetValue methods.
 * 2002-11-22 Fixed a problem between unicode/mbcs compiles.
 * 2002-11-19 Simplified to Element/Tree to a single class.
 * 2002-07-24 Convert to Xerces 2.0.0. Takeadvantage that
 *            XMLCh == wchar_t and MFC7's CString[AW]
 * 2001-09-13 Created CStringTree
 */

#include "stdafx.h"
#include "ARBCommon/Element.h"

#include "ARBCommon/ARBDate.h"
#include "ARBCommon/ARBTypes.h"
#include "ARBCommon/StringUtil.h"
#include "ARBCommon/UniqueId.h"
#include <fstream>
#include <list>
#include <map>
#include <sstream>

#include <wx/mstream.h>
#include <wx/stream.h>
#include <wx/wfstream.h>
#include <wx/xml/xml.h>
#pragma message("Compiling Element with wxWidgets " wxVERSION_NUM_DOT_STRING)

#if defined(__WXMSW__)
#include <wx/msw/msvcrt.h>
#endif


namespace
{

class wxInputStdStream : public wxInputStream
{
public:
	wxInputStdStream(std::istream& stream)
		: m_stream(stream)
	{
	}

	size_t OnSysRead(void* buffer, size_t size) override
	{
		size_t count = 0;
		if (m_stream.good())
		{
			m_stream.read(static_cast<char*>(buffer), size);
			count = static_cast<size_t>(m_stream.gcount());

			if (m_stream.eof())
			{
				m_lasterror = wxSTREAM_EOF;
			}
			else if (m_stream.good())
			{
				m_lasterror = wxSTREAM_NO_ERROR;
			}
			else
			{
				m_lasterror = wxSTREAM_READ_ERROR;
			}
		}
		return count;
	}

protected:
	std::istream& m_stream;
};


class wxOutputStdStream : public wxOutputStream
{
public:
	wxOutputStdStream(std::ostream& stream)
		: m_stream(stream)
	{
	}

	size_t OnSysWrite(const void* buffer, size_t size) override
	{
		size_t count = 0;
		if (m_stream.good())
		{
			m_stream.write(static_cast<const char*>(buffer), size);
			count = size;

			if (m_stream.eof())
			{
				m_lasterror = wxSTREAM_EOF;
			}
			else if (m_stream.good())
			{
				m_lasterror = wxSTREAM_NO_ERROR;
			}
			else
			{
				m_lasterror = wxSTREAM_WRITE_ERROR;
			}
		}
		return count;
	}

protected:
	std::ostream& m_stream;
};

} // namespace


namespace dconSoft
{
namespace ARBCommon
{

bool Element::Initialize(wxString& outMsg)
{
	// Note: This (and Terminate) were added when supporing other XML parsers.
	// For instance, libxml2 has global initialize/cleanup functions.
	outMsg.clear();
	return true;
}


void Element::Terminate()
{
}


Element::Element()
{
}


Element::~Element()
{
}


////////////////////////////////////////////////////////////////////////////

static void ReadDoc(wxXmlNode const* node, ElementNode& tree)
{
	wxXmlAttribute* attribs = node->GetAttributes();
	while (attribs)
	{
		tree.AddAttrib(attribs->GetName(), attribs->GetValue());
		attribs = attribs->GetNext();
	}
	wxString content = node->GetNodeContent();
	if (!content.empty())
		tree.SetValue(content);
	wxXmlNode* child = node->GetChildren();
	while (child)
	{
		if (wxXML_ELEMENT_NODE == child->GetType())
		{
			ElementNodePtr subtree = tree.AddElementNode(child->GetName());
			ReadDoc(child, *subtree);
		}
		child = child->GetNext();
	}
}


static void CreateDoc(wxXmlNode* node, ElementNode const& toWrite)
{
	int i;
	for (i = 0; i < toWrite.GetAttribCount(); ++i)
	{
		wxString name, value;
		toWrite.GetNthAttrib(i, name, value);
		node->AddAttribute(name, value);
	}
	int count = toWrite.GetElementCount();
	wxXmlNode* lastChild = nullptr;
	for (i = 0; i < count; ++i)
	{
		ElementPtr element = toWrite.GetElement(i);
		switch (element->GetType())
		{
		case ARBElementType::Node:
		{
			wxXmlNode* child = new wxXmlNode(nullptr, wxXML_ELEMENT_NODE, element->GetName());
			if (lastChild)
				lastChild->SetNext(child);
			else
				node->AddChild(child);
			lastChild = child;
			CreateDoc(child, *(dynamic_cast<ElementNode*>(element.get())));
		}
		break;
		case ARBElementType::Text:
		{
			wxXmlNode* child = new wxXmlNode(nullptr, wxXML_TEXT_NODE, element->GetName(), element->GetValue());
			node->AddChild(child);
		}
		break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////

namespace
{

wxString GetIndentBuffer(int indent)
{
	wxString str;
	if (0 < indent)
	{
		str = wxString::Format(L"%*s", indent, L" ");
	}
	return str;
}


class ElementNode_concrete : public ElementNode
{
public:
	ElementNode_concrete()
	{
	}
	ElementNode_concrete(wxString const& inName)
		: ElementNode(inName)
	{
	}
};
} // namespace


ElementNodePtr ElementNode::New()
{
	return std::make_shared<ElementNode_concrete>();
}


ElementNodePtr ElementNode::New(wxString const& inText)
{
	return std::make_shared<ElementNode_concrete>(inText);
}


ElementNode::ElementNode()
{
}


ElementNode::ElementNode(wxString const& inName)
	: m_Name(inName)
{
}


void ElementNode::RemoveAllTextNodes()
{
	for (std::vector<ElementPtr>::iterator i = m_Elements.begin(); i != m_Elements.end();)
	{
		if (ARBElementType::Text == (*i)->GetType())
			i = m_Elements.erase(i);
		else
			++i;
	}
}


void ElementNode::Dump(int inLevel) const
{
	int i;
	wxString msg;
	msg << GetIndentBuffer(inLevel) << m_Name;
	for (i = 0; i < GetAttribCount(); ++i)
	{
		wxString name, value;
		GetNthAttrib(i, name, value);
		msg << L" " << name << L"=\"" << value << L"\"";
	}
	wxLogMessage(L"%s", msg);
	for (i = 0; i < GetElementCount(); ++i)
	{
		GetElement(i)->Dump(inLevel + 1);
	}
}


ARBElementType ElementNode::GetType() const
{
	return ARBElementType::Node;
}


wxString const& ElementNode::GetName() const
{
	return m_Name;
}


void ElementNode::SetName(wxString const& inName)
{
	m_Name = inName;
}


wxString ElementNode::GetValue() const
{
	wxString value;
	for (int i = 0; i < GetElementCount(); ++i)
	{
		if (ARBElementType::Text == GetElement(i)->GetType())
			value += GetElement(i)->GetValue();
	}
	return value;
}


void ElementNode::SetValue(wxString const& inValue)
{
	RemoveAllTextNodes();
	ElementTextPtr pText = ElementText::New();
	pText->SetValue(inValue);
	m_Elements.push_back(pText);
}


void ElementNode::SetValue(short inValue)
{
	RemoveAllTextNodes();
	ElementTextPtr pText = ElementText::New();
	pText->SetValue(inValue);
	m_Elements.push_back(pText);
}


void ElementNode::SetValue(unsigned short inValue)
{
	RemoveAllTextNodes();
	ElementTextPtr pText = ElementText::New();
	pText->SetValue(inValue);
	m_Elements.push_back(pText);
}


void ElementNode::SetValue(long inValue)
{
	RemoveAllTextNodes();
	ElementTextPtr pText = ElementText::New();
	pText->SetValue(inValue);
	m_Elements.push_back(pText);
}


void ElementNode::SetValue(unsigned long inValue)
{
	RemoveAllTextNodes();
	ElementTextPtr pText = ElementText::New();
	pText->SetValue(inValue);
	m_Elements.push_back(pText);
}


void ElementNode::SetValue(double inValue, int inPrec)
{
	RemoveAllTextNodes();
	ElementTextPtr pText = ElementText::New();
	pText->SetValue(inValue, inPrec);
	m_Elements.push_back(pText);
}


void ElementNode::clear()
{
	m_Name.clear();
	m_Attribs.clear();
	m_Elements.clear();
}


int ElementNode::GetAttribCount() const
{
	return static_cast<int>(m_Attribs.size());
}


ARBAttribLookup ElementNode::GetNthAttrib(int inIndex, wxString& outName, wxString& outValue) const
{
	MyAttributes::const_iterator iter = m_Attribs.begin();
	while (0 < inIndex)
	{
		++iter;
		--inIndex;
	}
	if (iter != m_Attribs.end())
	{
		outName = (*iter).first;
		outValue = (*iter).second;
		return ARBAttribLookup::Found;
	}
	else
		return ARBAttribLookup::NotFound;
}


ARBAttribLookup ElementNode::GetAttrib(wxString const& inName, wxString& outValue) const
{
	MyAttributes::const_iterator iter = m_Attribs.find(inName);
	if (iter != m_Attribs.end())
	{
		outValue = (*iter).second;
		return ARBAttribLookup::Found;
	}
	else
		return ARBAttribLookup::NotFound;
}


ARBAttribLookup ElementNode::GetAttrib(wxString const& inName, ARBVersion& outValue) const
{
	wxString value;
	ARBAttribLookup rc = GetAttrib(inName, value);
	if (ARBAttribLookup::Found == rc)
	{
		outValue = ARBVersion(value);
	}
	return rc;
}


ARBAttribLookup ElementNode::GetAttrib(wxString const& inName, ARBDate& outValue) const
{
	wxString value;
	ARBAttribLookup rc = GetAttrib(inName, value);
	if (ARBAttribLookup::Found == rc)
	{
		ARBDate date = ARBDate::FromString(value, ARBDateFormat::DashYMD);
		if (date.IsValid())
			outValue = date;
		else
			rc = ARBAttribLookup::Invalid;
	}
	return rc;
}


ARBAttribLookup ElementNode::GetAttribUTC(wxString const& inName, wxDateTime& outValue) const
{
	auto rc = GetAttrib(inName, outValue);
	if (ARBAttribLookup::Found == rc)
	{
		outValue.MakeFromUTC();
	}
	return rc;
}


ARBAttribLookup ElementNode::GetAttrib(wxString const& inName, wxDateTime& outValue) const
{
	wxString value;
	ARBAttribLookup rc = GetAttrib(inName, value);
	if (ARBAttribLookup::Found == rc)
	{
		wxDateTime date;
		if (date.ParseISOCombined(value, ' '))
			outValue = date;
		else
			rc = ARBAttribLookup::Invalid;
	}
	return rc;
}


ARBAttribLookup ElementNode::GetAttrib(wxString const& inName, bool& outValue) const
{
	wxString value;
	ARBAttribLookup rc = GetAttrib(inName, value);
	if (ARBAttribLookup::Found == rc)
	{
		if (value == L"y")
			outValue = true;
		else if (value == L"n")
			outValue = false;
		else
			rc = ARBAttribLookup::Invalid;
	}
	return rc;
}


ARBAttribLookup ElementNode::GetAttrib(wxString const& inName, short& outValue) const
{
	wxString value;
	ARBAttribLookup rc = GetAttrib(inName, value);
	if (ARBAttribLookup::Found == rc)
	{
		if (0 < value.length())
			outValue = static_cast<short>(StringUtil::ToCLong(value));
		else
			rc = ARBAttribLookup::Invalid;
	}
	return rc;
}


ARBAttribLookup ElementNode::GetAttrib(wxString const& inName, unsigned short& outValue) const
{
	wxString value;
	ARBAttribLookup rc = GetAttrib(inName, value);
	if (ARBAttribLookup::Found == rc)
	{
		if (0 < value.length())
			outValue = static_cast<unsigned short>(StringUtil::ToCULong(value));
		else
			rc = ARBAttribLookup::Invalid;
	}
	return rc;
}


ARBAttribLookup ElementNode::GetAttrib(wxString const& inName, long& outValue) const
{
	wxString value;
	ARBAttribLookup rc = GetAttrib(inName, value);
	if (ARBAttribLookup::Found == rc)
	{
		if (0 < value.length())
		{
			if (!StringUtil::ToCLong(value, outValue))
				rc = ARBAttribLookup::Invalid;
		}
		else
			rc = ARBAttribLookup::Invalid;
	}
	return rc;
}


ARBAttribLookup ElementNode::GetAttrib(wxString const& inName, unsigned long& outValue) const
{
	wxString value;
	ARBAttribLookup rc = GetAttrib(inName, value);
	if (ARBAttribLookup::Found == rc)
	{
		if (0 < value.length())
		{
			if (!StringUtil::ToCULong(value, outValue))
				rc = ARBAttribLookup::Invalid;
		}
		else
			rc = ARBAttribLookup::Invalid;
	}
	return rc;
}


ARBAttribLookup ElementNode::GetAttrib(wxString const& inName, double& outValue) const
{
	wxString value;
	ARBAttribLookup rc = GetAttrib(inName, value);
	if (ARBAttribLookup::Found == rc)
	{
		if (0 < value.length())
		{
			if (!value.ToCDouble(&outValue))
				rc = ARBAttribLookup::Invalid;
		}
		else
			rc = ARBAttribLookup::Invalid;
	}
	return rc;
}


ARBAttribLookup ElementNode::GetAttrib(wxString const& inName, CUniqueId& outValue) const
{
	wxString value;
	ARBAttribLookup rc = GetAttrib(inName, value);
	if (ARBAttribLookup::Found == rc)
	{
		if (!outValue.ParseString(value) || outValue.IsNull())
			rc = ARBAttribLookup::Invalid;
	}
	return rc;
}


bool ElementNode::AddAttrib(wxString const& inName, wxString const& inValue)
{
	if (inName.empty())
		return false;
	m_Attribs[inName] = inValue;
	return true;
}


bool ElementNode::AddAttrib(wxString const& inName, wchar_t const* const inValue)
{
	if (inName.empty())
		return false;
	if (inValue)
		m_Attribs[inName] = inValue;
	else
		m_Attribs[inName] = wxString();
	return true;
}


bool ElementNode::AddAttrib(wxString const& inName, ARBVersion const& inValue)
{
	return AddAttrib(inName, inValue.str());
}


bool ElementNode::AddAttrib(wxString const& inName, ARBDate const& inValue)
{
	if (inValue.IsValid())
		AddAttrib(inName, inValue.GetString(ARBDateFormat::DashYMD));
	return false;
}


bool ElementNode::AddAttribUTC(wxString const& inName, wxDateTime const& inValue)
{
	wxDateTime utc(inValue);
	utc.MakeUTC();
	return AddAttrib(inName, utc);
}


bool ElementNode::AddAttrib(wxString const& inName, wxDateTime const& inValue)
{
	if (inValue.IsValid())
		AddAttrib(inName, inValue.FormatISOCombined(' '));
	return false;
}


bool ElementNode::AddAttrib(wxString const& inName, bool inValue)
{
	if (inName.empty())
		return false;
	if (inValue)
		m_Attribs[inName] = L"y";
	else
		m_Attribs[inName] = L"n";
	return true;
}


bool ElementNode::AddAttrib(wxString const& inName, short inValue)
{
	if (inName.empty())
		return false;
	m_Attribs[inName] << inValue;
	return true;
}


bool ElementNode::AddAttrib(wxString const& inName, unsigned short inValue)
{
	if (inName.empty())
		return false;
	m_Attribs[inName] << inValue;
	return true;
}


bool ElementNode::AddAttrib(wxString const& inName, long inValue)
{
	if (inName.empty())
		return false;
	m_Attribs[inName] << inValue;
	return true;
}


bool ElementNode::AddAttrib(wxString const& inName, unsigned long inValue)
{
	if (inName.empty())
		return false;
	m_Attribs[inName] << inValue;
	return true;
}


bool ElementNode::AddAttrib(wxString const& inName, double inValue, int inPrec)
{
	if (inName.empty())
		return false;
	m_Attribs[inName] = ARBDouble::ToString(inValue, inPrec, false);
	return true;
}


bool ElementNode::AddAttrib(wxString const& inName, CUniqueId const& inValue)
{
	return AddAttrib(inName, inValue.ToString());
}


bool ElementNode::RemoveAttrib(wxString const& inName)
{
	MyAttributes::iterator iter = m_Attribs.find(inName);
	if (iter != m_Attribs.end())
	{
		m_Attribs.erase(iter);
		return true;
	}
	else
		return false;
}


void ElementNode::RemoveAllAttribs()
{
	m_Attribs.clear();
}


int ElementNode::GetElementCount() const
{
	return static_cast<int>(m_Elements.size());
}


int ElementNode::GetNodeCount(ARBElementType type) const
{
	int nCount = 0;
	for (std::vector<ElementPtr>::const_iterator iter = m_Elements.begin(); iter != m_Elements.end(); ++iter)
	{
		if (type == (*iter)->GetType())
			++nCount;
	}
	return nCount;
}


bool ElementNode::HasTextNodes() const
{
	for (std::vector<ElementPtr>::const_iterator iter = m_Elements.begin(); iter != m_Elements.end(); ++iter)
	{
		if (ARBElementType::Text == (*iter)->GetType())
			return true;
	}
	return false;
}


ElementPtr ElementNode::GetElement(int inIndex) const
{
	return m_Elements[inIndex];
}


ElementPtr ElementNode::GetElement(int inIndex)
{
	return m_Elements[inIndex];
}


ElementNodePtr ElementNode::GetElementNode(int inIndex) const
{
	return std::dynamic_pointer_cast<ElementNode, Element>(m_Elements[inIndex]);
}


ElementNodePtr ElementNode::GetElementNode(int inIndex)
{
	return std::dynamic_pointer_cast<ElementNode, Element>(m_Elements[inIndex]);
}


ElementNodePtr ElementNode::GetNthElementNode(int inIndex) const
{
	int index = -1;
	int nElements = static_cast<int>(m_Elements.size());
	for (int iElement = 0; iElement < nElements; ++iElement)
	{
		if (ARBElementType::Node == m_Elements[iElement]->GetType())
		{
			++index;
			if (index == inIndex)
				return GetElementNode(iElement);
		}
	}
	return ElementNodePtr();
}


ElementNodePtr ElementNode::GetNthElementNode(int inIndex)
{
	ElementNode const* constThis = this;
	return constThis->GetNthElementNode(inIndex);
}


ElementNodePtr ElementNode::AddElementNode(wxString const& inName, int inAt)
{
	size_t index = 0;
	std::vector<ElementPtr>::iterator iter = m_Elements.begin();
	if (0 < inAt)
	{
		index = 0;
		for (; 0 < inAt && iter != m_Elements.end(); ++index, ++iter, --inAt)
			;
	}
	else if (0 > inAt)
	{
		index = m_Elements.size();
		iter = m_Elements.end();
	}
	ElementNodePtr pNode = ElementNode::New(inName);
	m_Elements.insert(iter, pNode);
	return pNode;
}


ElementTextPtr ElementNode::AddElementText(wxString const& inText, int inAt)
{
	assert(0 == m_Value.length());
	size_t index = 0;
	std::vector<ElementPtr>::iterator iter = m_Elements.begin();
	if (0 < inAt)
	{
		index = 0;
		for (; 0 < inAt && iter != m_Elements.end(); ++index, ++iter, --inAt)
			;
	}
	else
	{
		index = m_Elements.size();
		iter = m_Elements.end();
	}
	ElementTextPtr pText = ElementText::New(inText);
	m_Elements.insert(iter, pText);
	return pText;
}


bool ElementNode::RemoveElement(int inIndex)
{
	bool bOk = false;
	if (0 <= inIndex && inIndex < static_cast<int>(m_Elements.size()))
	{
		std::vector<ElementPtr>::iterator iter = m_Elements.begin();
		iter += inIndex;
		m_Elements.erase(iter);
		bOk = true;
	}
	return bOk;
}


void ElementNode::RemoveAllElements()
{
	m_Elements.clear();
}


int ElementNode::FindElement(wxString const& inName, int inStartFrom) const
{
	if (0 > inStartFrom)
		inStartFrom = 0;
	for (; inStartFrom < static_cast<int>(m_Elements.size()); ++inStartFrom)
	{
		if (m_Elements[inStartFrom]->GetName() == inName)
			return inStartFrom;
	}
	return -1;
}


bool ElementNode::FindElementDeep(
	ElementNode const*& outParentNode,
	int& outElementIndex,
	wxString const& inName,
	wxString const* inValue) const
{
	int nCount = GetElementCount();
	for (int i = 0; i < nCount; ++i)
	{
		ElementNodePtr element = GetElementNode(i);
		if (!element)
			continue;
		if (element->GetName() == inName && (!inValue || (inValue && element->GetValue() == *inValue)))
		{
			outParentNode = this;
			outElementIndex = i;
			return true;
		}
		else if (element->FindElementDeep(outParentNode, outElementIndex, inName, inValue))
			return true;
	}
	return false;
}


static bool LoadXMLNode(ElementNode& node, wxXmlDocument const& inSource, wxString& ioErrMsg)
{
	node.clear();

	if (!inSource.GetRoot())
		return false;
	node.SetName(inSource.GetRoot()->GetName());
	ReadDoc(inSource.GetRoot(), node);
	return true;
}


bool ElementNode::LoadXML(std::istream& inStream, wxString& ioErrMsg)
{
	if (!inStream.good())
		return false;

	wxLogBuffer* log = new wxLogBuffer();
	// wxLogChain will delete the log given to it.
	wxLogChain chain(log);
	chain.PassMessages(false);

	wxInputStdStream stream(inStream);
	wxXmlDocument source;
	if (!source.Load(stream))
	{
		ioErrMsg << log->GetBuffer();
		// This does not call Flush (which displays a dialog). Yea!
		chain.SetLog(nullptr);
		return false;
	}
	return LoadXMLNode(*this, source, ioErrMsg);
}


bool ElementNode::LoadXML(char const* inData, size_t nData, wxString& ioErrMsg)
{
	if (!inData || 0 == nData)
		return false;
	std::istringstream input(std::string(inData, nData));
	return LoadXML(input, ioErrMsg);
}


bool ElementNode::LoadXML(wchar_t const* inFileName, wxString& ioErrMsg)
{
	if (!inFileName)
		return false;
#ifdef ARB_HAS_ISTREAM_WCHAR
	std::ifstream input(inFileName);
#else
	std::string filename(wxString(inFileName).utf8_string());
	std::ifstream input(filename);
#endif
	if (!input.good())
		return false;
	return LoadXML(input, ioErrMsg);
}


bool ElementNode::SaveXML(std::ostream& outOutput) const
{
	std::string dtd;
	return SaveXML(outOutput, dtd);
}


bool ElementNode::SaveXML(std::ostream& outOutput, wxString const& inDTD) const
{
	wxXmlDocument doc;
	doc.SetVersion(L"1.0");
	doc.SetFileEncoding(L"utf-8");
	wxXmlNode* root = new wxXmlNode(nullptr, wxXML_ELEMENT_NODE, GetName());
	doc.SetRoot(root);
	// TODO: Insert DTD
	CreateDoc(root, *this);
	wxOutputStdStream out(outOutput);
	return doc.Save(out);
}


bool ElementNode::SaveXML(wxString const& outFile) const
{
	wxString dtd;
	return SaveXML(outFile, dtd);
}


bool ElementNode::SaveXML(wxString const& outFile, wxString const& inDTD) const
{
	bool bOk = false;
	if (outFile.empty())
		return bOk;
#if 1
#if defined(ARB_HAS_OSTREAM_WCHAR)
	std::ofstream output(outFile.wc_str(), std::ios::out | std::ios::binary);
#else
	char const* pFile = nullptr;
	std::string filename = outFile.utf8_string();
	pFile = filename.c_str();
	std::ofstream output(pFile, std::ios::out | std::ios::binary);
#endif
	output.exceptions(std::ios_base::badbit);
	if (output.is_open())
	{
		bOk = SaveXML(output, inDTD);
		output.close();
	}
#else
	wxFFileOutputStream output(outFile, L"wb");
	if (output.IsOk())
	{
		bOk = SaveXML(output, inDTD);
		output.Close();
	}
#endif
	return bOk;
}

/////////////////////////////////////////////////////////////////////////////

namespace
{
class ElementText_concrete : public ElementText
{
public:
	ElementText_concrete()
	{
	}
	ElementText_concrete(wxString const& inText)
		: ElementText(inText)
	{
	}
};
} // namespace


ElementTextPtr ElementText::New()
{
	return std::make_shared<ElementText_concrete>();
}


ElementTextPtr ElementText::New(wxString const& inText)
{
	return std::make_shared<ElementText_concrete>(inText);
}


ElementText::ElementText()
	: m_Value()
{
}


ElementText::ElementText(wxString const& inText)
	: m_Value(inText)
{
}


void ElementText::Dump(int inLevel) const
{
	wxString msg;
	msg << GetIndentBuffer(inLevel) << GetName();
	if (0 < m_Value.length())
	{
		msg << L": " << m_Value;
	}
	wxLogMessage(L"%s", msg);
}


ARBElementType ElementText::GetType() const
{
	return ARBElementType::Text;
}


wxString const& ElementText::GetName() const
{
	static const wxString name(L"#text");
	return name;
}


void ElementText::SetName(wxString const& /*inName*/)
{
}


wxString ElementText::GetValue() const
{
	return m_Value;
}


void ElementText::SetValue(wxString const& inValue)
{
	m_Value = inValue;
}


void ElementText::SetValue(short inValue)
{
	m_Value << inValue;
}


void ElementText::SetValue(unsigned short inValue)
{
	m_Value << inValue;
}


void ElementText::SetValue(long inValue)
{
	m_Value << inValue;
}


void ElementText::SetValue(unsigned long inValue)
{
	m_Value << inValue;
}


void ElementText::SetValue(double inValue, int inPrec)
{
	m_Value = ARBDouble::ToString(inValue, inPrec, false);
}

} // namespace ARBCommon
} // namespace dconSoft
