/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Utility classes
 * @author David Connet
 *
 * Revision History
 * 2019-01-31 Moved GetOSInfo to LibARBWin/ARBDebug.
 * 2018-04-26 Moved ShortToRoman from ARBConfigTitle.
 * 2014-06-19 Added IsWin7OrBetter.
 * 2013-07-17 Created
 */

#include "stdafx.h"
#include "ARBCommon/ARBMisc.h"

#include "ARBCommon/StringUtil.h"
#include <math.h>

#include <wx/string.h>

#if defined(__WXMSW__)
#include <wx/msw/msvcrt.h>
#endif


namespace dconSoft
{
namespace ARBCommon
{

wxString SanitizeStringForHTML(wxString const& inRawData, bool bConvertCR)
{
	auto pos = inRawData.find_first_of(L"&<>");
	if (wxString::npos == pos && bConvertCR)
		pos = inRawData.find_first_of(L"\r\n");
	if (wxString::npos == pos)
		return inRawData;
	wxString data;
	for (size_t nChar = 0; nChar < inRawData.length(); ++nChar)
	{
		switch (inRawData[nChar].GetValue())
		{
		case L'&':
			data << L"&amp;";
			break;
		case L'<':
			data << L"&lt;";
			break;
		case L'>':
			data << L"&gt;";
			break;
		case L'\r':
			if (bConvertCR)
			{
				if (nChar + 1 < inRawData.length() && '\n' == inRawData[nChar + 1].GetValue())
					continue;
				else
					data << L"<br/>";
			}
			else
				data << inRawData[nChar];
			break;
		case '\n':
			if (bConvertCR)
				data << L"<br/>";
			else
				data << inRawData[nChar];
			break;
		default:
			data << inRawData[nChar];
			break;
		}
	}
	return data;
}

/////////////////////////////////////////////////////////////////////////////

// Every platform we support for download must be listed here.
//  win32,win64,osx,osx-arm64,osx-x64
//  pre v3.8.2: win32,win64,osx
//  pre v2.4.0: x86, x64, mac
// It must also be present in the version2.xml file (that creates an
// arch/lang to filename mapping).
wxString GetARBArch()
{
#if defined(__WXMSW__)
#if defined(_WIN64)
	return L"win64";
#else
	return L"win32";
#endif
#else
	return GetNativeARBArch();
#endif
}


wxString GetNativeARBArch()
{
#if defined(__WXMSW__)
	if (wxIsPlatform64Bit())
		return L"win64";
	else
		return L"win32";

#elif defined(__WXMAC__)
	// Note: this api returns the result of "uname -m"
	auto arch = wxGetNativeCpuArchitectureName();
	if (0 == arch.CmpNoCase(L"arm64"))
		return L"osx-arm64";
	else if (0 == arch.CmpNoCase(L"x86_64"))
		return L"osx-x64";
	else
		return L"osx";

#elif defined(__WXGTK__) || defined(__WXX11__)
	return L"linux";

#else
#error Unknown platform
#endif
}

/////////////////////////////////////////////////////////////////////////////

bool GetOSInfo(int& verMajor, int& verMinor, int& verMicro)
{
	wxPlatformInfo info;
	verMajor = info.GetOSMajorVersion();
	verMinor = info.GetOSMinorVersion();
	verMicro = info.GetOSMicroVersion();
	return true;
}

/////////////////////////////////////////////////////////////////////////////

#ifdef WIN32

bool CheckOS(DWORD dwMajor, DWORD dwMinor, int op)
{
	OSVERSIONINFOEX osvi = {0};
	DWORDLONG dwlConditionMask = 0;

	ZeroMemory(&osvi, sizeof(osvi));
	osvi.dwOSVersionInfoSize = sizeof(osvi);
	osvi.dwMajorVersion = dwMajor;
	osvi.dwMinorVersion = dwMinor;
	osvi.wServicePackMajor = 0;
	osvi.wServicePackMinor = 0;

#pragma warning(push)
#pragma warning(disable:4242) // conversion from 'int' to 'BYTE', possible loss of data
#pragma warning(disable:4244) // conversion from 'int' to 'BYTE', possible loss of data
	VER_SET_CONDITION(dwlConditionMask, VER_MAJORVERSION, op);
	VER_SET_CONDITION(dwlConditionMask, VER_MINORVERSION, op);
	VER_SET_CONDITION(dwlConditionMask, VER_SERVICEPACKMAJOR, op);
	VER_SET_CONDITION(dwlConditionMask, VER_SERVICEPACKMINOR, op);
#pragma warning(pop)

	return !!VerifyVersionInfo(
		&osvi,
		VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR | VER_SERVICEPACKMINOR,
		dwlConditionMask);
}

#endif

bool IsWin7OrBetter()
{
#ifdef WIN32
	return CheckOS(6, 1, VER_GREATER_EQUAL);
#else
	return false;
#endif
}


/////////////////////////////////////////////////////////////////////////////

/*
// Roman number conversion (modified from C# code on CodeProject)
static short RomanDigit(wchar_t digit)
{
	switch (digit)
	{
	case 'I':
		return 1;
	case 'V':
		return 5;
	case 'X':
		return 10;
	case 'L':
		return 50;
	case 'C':
		return 100;
	case 'D':
		return 500;
	case 'M':
		return 1000;
	default :
		//We're in a limited world - don't worry about out-of-range
		//throw new ArgumentOutOfRangeException("digit");
		return 0;
	}
}
static short RomanToShort(wxString  number)
{
	short result = 0;
	short oldValue = 1000;
	for (wxStringwstring::const_iterator index = number.begin(); index != number.end(); ++index)
	{
		short newValue = RomanDigit(*index);
		if (newValue > oldValue)
			result = result + newValue - 2 * oldValue;
		else
			result += newValue;
		oldValue = newValue;
	}
	return result;
}
*/

wxString ShortToRoman(short value)
{
	constexpr wchar_t const* romanDigits[9][4] = {
		// clang-format off
		{L"M",    L"C",    L"X",    L"I"   },
		{L"MM",   L"CC",   L"XX",   L"II"  },
		{L"MMM",  L"CCC",  L"XXX",  L"III" },
		{nullptr, L"CD",   L"XL",   L"IV"  },
		{nullptr, L"D",    L"L",    L"V"   },
		{nullptr, L"DC",   L"LX",   L"VI"  },
		{nullptr, L"DCC",  L"LXX",  L"VII" },
		{nullptr, L"DCCC", L"LXXX", L"VIII"},
		{nullptr, L"CM",   L"XC",   L"IX"  },
		// clang-format on
	};
	wxString result;
	for (int index = 0; index < 4; ++index)
	{
		short power = static_cast<short>(pow(10.0, 3 - index));
		short digit = value / power;
		value -= digit * power;
		if (digit > 0)
			result << romanDigits[digit - 1][index];
	}
	return result;
}

} // namespace ARBCommon
} // namespace dconSoft
