/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Base64/zlib encoding/decoding class.
 * @author David Connet
 *
 * Revision History
 * 2020-02-29 Removed raw pointers, use vectors.
 * 2014-03-07 Add support for Poco's compression.
 * 2009-09-13 Add support for wxWidgets 2.9, deprecate tstring.
 * 2009-02-12 Encoding/decoding 0 bytes should fail.
 * 2008-12-13 Added wxWidget support (zlib)
 * 2007-01-03 Created
 */

#include "stdafx.h"
#include "ARBCommon/BinaryData.h"

#include "ARBCommon/ARBBase64.h"
#include "ARBCommon/StringUtil.h"

#include <wx/mstream.h>
#include <wx/wfstream.h>
#include <wx/zstream.h>
#include <fstream>

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>
#endif


namespace dconSoft
{
namespace ARBCommon
{

bool BinaryData::Decode(std::string const& inBase64, std::vector<unsigned char>& outBinData)
{
	outBinData.clear();
	if (inBase64.empty())
		return false;

	bool bOk = false;
	std::vector<unsigned char> pData;
	if (ARBBase64::Decode(inBase64, pData))
	{
		wxMemoryOutputStream output;
		{
			wxZlibInputStream strm(new wxMemoryInputStream(pData.data(), pData.size()), wxZLIB_ZLIB);
			output.Write(strm);
			output.Close();
		}
		size_t outBytes = output.GetSize();
		outBinData = std::vector<unsigned char>(outBytes);
		output.CopyTo(outBinData.data(), outBytes);
		bOk = true;
	}

	return bOk;
}


bool BinaryData::Encode(std::vector<unsigned char> const& inBinData, std::string& outBase64)
{
	outBase64.clear();
	if (inBinData.empty())
		return false;

	bool bOk = false;
	size_t nData = 0;

	wxMemoryOutputStream output;
	{
		wxZlibOutputStream strm(output);
		strm.Write(inBinData.data(), inBinData.size());
		strm.Close();
	}
	nData = output.GetSize();
	auto pData = std::vector<unsigned char>(nData);
	output.CopyTo(pData.data(), nData);

	if (!pData.empty())
	{
		bOk = ARBBase64::Encode(pData, outBase64);
	}

	return bOk;
}


bool BinaryData::EncodeFile(wxString const& inFileName, std::string& outBase64)
{
	outBase64.clear();

	bool bOk = false;
	size_t nData = 0;

	wxFFile file;
	if (!file.Open(inFileName, L"rb"))
		return false;

	wxMemoryOutputStream output;
	{
		wxZlibOutputStream strm(output);
		wxFFileInputStream instrm(file);
		strm.Write(instrm);
		strm.Close();
	}
	nData = output.GetSize();
	auto pData = std::vector<unsigned char>(nData);
	output.CopyTo(pData.data(), nData);

	if (!pData.empty())
	{
		std::string tmp;
		bOk = ARBBase64::Encode(pData, tmp);
		outBase64 = tmp;
	}

	return bOk;
}


bool BinaryData::DecodeString(std::string const& inBase64, std::string& outData)
{
	if (inBase64.empty())
	{
		outData.clear();
		return false;
	}
	std::vector<unsigned char> data;
	if (!BinaryData::Decode(inBase64, data))
		return false;
	outData = std::string(data.begin(), data.end());
	return true;
}


bool BinaryData::EncodeString(std::string const& inData, std::string& outBase64)
{
	outBase64.clear();
	if (inData.empty())
		return false;
	// Do not include the null terminator. Otherwise decoding includes it into
	// the output string - which when streamed, then includes the null. Which
	// in an ostringstream, terminates the string on output of the stream.
	// TODO: Better conversion
	std::vector<unsigned char> data(inData.begin(), inData.end());
	return BinaryData::Encode(data, outBase64);
}

} // namespace ARBCommon
} // namespace dconSoft
