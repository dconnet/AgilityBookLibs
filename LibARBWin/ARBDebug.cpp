/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Helper functions to retrieve debug data for dumps and ARBHelp
 * @author David Connet
 *
 * Revision History
 * 2024-01-29 Remove 'default' in wxConfig switch so compiler errors on new one
 * 2023-08-07 Return x.y.z for OS version, use shorter name for OS name.
 * 2022-04-15 Use wx DPI support.
 * 2021-07-11 Added compiled-at info, use wxGetLibraryVersionInfo for wx version
 * 2019-01-31 Moved from ARB.
 * 2018-01-28 Created
 */

#include "stdafx.h"
#include "LibARBWin/ARBDebug.h"

#include "ARBCommon/ARBMisc.h"
#include "ARBCommon/ARBUtils.h"
#include "ARBCommon/VersionNum.h"
#include <wx/config.h>
#include <wx/platinfo.h>
#include <wx/stdpaths.h>
#include <wx/string.h>
#include <wx/utils.h>

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>
#endif

namespace dconSoft
{
using namespace ARBCommon;
namespace ARBWin
{
namespace ARBDebug
{

wxString GetCompileDate()
{
	return wxString(std::string(__DATE__));
}


wxString GetCompileTime()
{
	return wxString(std::string(__TIME__));
}


wxString GetOSName()
{
	wxString str;

	int majVer;
	int minVer;
	int verMicro;
	if (!GetOSInfo(majVer, minVer, verMicro))
		return wxString();

#if defined(__WXWINDOWS__)
	wxPlatformInfo info;
	str = wxString::Format(L"%s %d.%d.%d", info.GetOperatingSystemFamilyName(), majVer, minVer, verMicro);

#elif defined(_WIN32)
	switch (majVer)
	{
	default:
		str = wxString::Format(L"Windows %d.%d.%d", majVer, minVer, verMicro);
		break;
	case 6:
		switch (minVer)
		{
		default:
			str = wxString::Format(L"Windows %d.%d.%d", majVer, minVer, verMicro);
			break;
		case 0:
			str = L"Windows Vista";
			break;
		case 1:
			str = L"Windows 7";
			break;
		case 2:
			str = L"Windows 8";
			break;
		case 3:
			str = L"Windows 8.1";
			break;
		}
		break;
	case 5:
		switch (minVer)
		{
		default:
			str = wxString::Format(L"Windows %d.%d.%d", majVer, minVer, verMicro);
			break;
		case 2:
			str = L"Windows XP"; // Not really, 64bitXP, or Server
			break;
		case 1:
			str = L"Windows XP";
			break;
		case 0:
			str = L"Windows 2000";
			break;
		}
		break;
	}

#else
#error Unknown OS
#endif

	return str;
}


wxString GetArchName()
{
#if defined(__WXWINDOWS__)
	wxPlatformInfo info;
	return info.GetBitnessName();

#elif defined(_WIN32)
	SYSTEM_INFO si;
	ZeroMemory(&si, sizeof(si));
	GetNativeSystemInfo(&si);
	switch (si.wProcessorArchitecture)
	{
	default:
	case PROCESSOR_ARCHITECTURE_UNKNOWN:
		return L"??";
	case PROCESSOR_ARCHITECTURE_AMD64:
		return L"x64";
	case PROCESSOR_ARCHITECTURE_ARM:
		return L"ARM";
	case PROCESSOR_ARCHITECTURE_IA64:
		return L"ia64";
	case PROCESSOR_ARCHITECTURE_INTEL:
		return L"x86";
	}

#else
#error Unknown OS
#endif
}


wxString GetEndiannessName()
{
#if defined(__WXWINDOWS__)
	wxPlatformInfo info;
	return info.GetEndiannessName();

#else
	// Copied from wxWidgets 2.9.5: utilscmn.cpp: wxIsPlatformLittleEndian
	// Are we little or big endian? This method is from Harbison & Steele.
	union
	{
		long l;
		char c[sizeof(long)];
	} u;
	u.l = 1;

	bool isLittleEndian = (u.c[0] == 1);
	if (isLittleEndian)
		return L"Little endian";
	else
		return L"Big endian";

#endif
}

/////////////////////////////////////////////////////////////////////////////

wxString GetSystemInfo(wxWindow const* pWindow, CVersionNum const& ver)
{
	wxString str;

	// Note: This is diagnostic data, so like wxWidgets, we're not translating it.

	// OS version
	str << L"OS: " << GetOSName() << L"\n";
	str << L"Architecture: " << GetArchName() << L", " << GetEndiannessName() << L"\n";

	// DPI

	str << L"DPI Scaling: " << pWindow->GetDPIScaleFactor() << L"\n";

	// Me.
	{
		str << wxStandardPaths::Get().GetExecutablePath() << L"(" << wxGetCpuArchitectureName() << L"): ";
		if (ver.Valid())
			str << ver.GetVersionString() << L"\n";
		else
			str << _("Unable to determine version information") << L"\n";

		// Lower case for consistency with wxGetLibraryVersionInfo()
		str << L"compiled at " << GetCompileDate() << L" " << GetCompileTime() << L"\n";
	}

	// wxWidgets
	auto info = wxGetLibraryVersionInfo();
	str << L"\n" << info.GetDescription() << L"\n";

	return str;
}


wxString GetRegistryInfo()
{
	wxString data;
	DumpRegistryGroup(wxEmptyString, &data, nullptr);
	return data;
}

/////////////////////////////////////////////////////////////////////////////
// Dump registry information

// .reg format (http://support.microsoft.com/kb/310516)
//
// RegistryEditorVersion
// Blank line
// [RegistryPath1]
// "DataItemName1"=DataType1:DataValue1
// DataItemName2=DataType2:DataValue2
// Blank line
// [RegistryPath2]
// "DataItemName3"="DataType3:DataValue3"
// "DataItemName4"="DataValue4"
// Blank line
//
// Difference between "REGEDIT4" and "Windows Registry Editor Version 5.00"
// - v5 supports unicode
//
// DataType (REG_SZ assumed unless DataType specified):
//  REG_BINARY		hex
//  REG_DWORD		dword
//  REG_EXPAND_SZ	hex(2)
//  REG_MULTI_SZ	hex(7)
//
// examples:
// "SetupType"=dword:00000000
// "CmdLine"="setup -newsetup"
// "SystemPrefix"=hex:c5,0b,00,00,00,40,36,02
// ; "String1\0String2" [in v5 (unicode) form, don't know how they look in v4]
// "Test"=hex(7):53,00,74,00,72,00,69,00,6e,00,67,00,20,00,31,00,00,00,53,00,74,\
//   00,72,00,69,00,6e,00,67,00,20,00,32,00,00,00,00,00
// ; %TMP%
// "Expand"=hex(2):25,00,54,00,4d,00,50,00,25,00,00,00
//
// To delete an item (hyphen in front of key):
// [-RegistryPath2]
// To delete a value (hyphen after '=' ):
// "DataItemName4"=-

size_t DumpRegistryGroup(wxString const& inGroup, wxString* outData, std::vector<wxString>* outItems)
{
	size_t added = 0; // Added to outData

	CConfigPathHelper config(inGroup);

	wxString str;
	long dummy;
	if (wxConfig::Get()->GetFirstEntry(str, dummy))
	{
		do
		{
			switch (wxConfig::Get()->GetEntryType(str))
			{
			case wxConfigBase::Type_Unknown:
				if (outData)
				{
					++added;
					*outData << wxConfig::Get()->GetPath() << L"/" << str << L" unknown\n";
				}
				break;
			case wxConfigBase::Type_String:
				if (outData)
				{
					++added;
					*outData << wxConfig::Get()->GetPath() << L"/" << str << L" string\n";
					*outData << wxConfig::Get()->Read(str, wxEmptyString) << L"\n";
				}
				if (outItems)
					outItems->push_back(wxConfig::Get()->Read(str, wxEmptyString));
				break;
			case wxConfigBase::Type_Boolean:
				if (outData)
				{
					++added;
					*outData << wxConfig::Get()->GetPath() << L"/" << str << L" bool\n";
					bool b;
					wxConfig::Get()->Read(str, &b);
					*outData << b << L"\n";
				}
				break;
			case wxConfigBase::Type_Integer:
				if (outData)
				{
					++added;
					*outData << wxConfig::Get()->GetPath() << L"/" << str << L" int\n";
					*outData << wxConfig::Get()->Read(str, 0L) << L"\n";
				}
				break;
			case wxConfigBase::Type_Float:
				if (outData)
				{
					++added;
					*outData << wxConfig::Get()->GetPath() << L"/" << str << L" float\n";
					double d;
					wxConfig::Get()->Read(str, &d);
					*outData << d << L"\n";
				}
				break;
			}
		} while (wxConfig::Get()->GetNextEntry(str, dummy));
	}

	if (wxConfig::Get()->GetFirstGroup(str, dummy))
	{
		do
		{
			added += DumpRegistryGroup(str, outData, outItems);
		} while (wxConfig::Get()->GetNextGroup(str, dummy));
	}

	return added;
}

} // namespace ARBDebug
} // namespace ARBWin
} // namespace dconSoft
