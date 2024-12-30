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
 * 2024-10-09 Tweak tolower/upper to use transform. Add some todo notes.
 * 2018-04-19 Fixed string/double parsing for locales.
 * 2015-11-13 Added zetta and yotta bytes.
 * 2015-04-22 Specifically use std::abs, on mac it used abs(int).
 * 2014-11-17 Enhanced FormatBytes (added true units as they're meant to be!)
 * 2014-08-28 Enhanced FormatBytes
 * 2014-06-24 Added CompareNoCase.
 * 2013-01-25 Better non-wx support.
 * 2012-08-12 Moved FormatBytes to StringUtil
 * 2012-04-10 Based on wx-group thread, use std::string for internal use
 * 2010-12-30 Fix a memory leak when transforming a stream.
 * 2009-11-24 Optimize locale usage when reading/writing the ARB file.
 * 2009-09-13 Add support for wxWidgets 2.9, deprecate tstring.
 * 2009-03-30 Remove Convert and replaced with stringA/etc
 * 2008-06-29 Moved string stuff out of ARBTypes.
 */

#include "stdafx.h"
#include "ARBCommon/StringUtil.h"

#include "ARBCommon/ARBMisc.h"
#include "ARBCommon/ARBTypes.h"
#include <wx/mstream.h>
#include <wx/numformatter.h>
#include <wx/strconv.h>
#include <wx/uilocale.h>
#include <algorithm>
#include <cwctype>
#include <locale>
#include <sstream>

#if defined(WIN32) && (_WIN32_IE >= _WIN32_IE_IE55)
#include "Shlwapi.h"
#pragma comment(lib, "shlwapi.lib")
#endif

#ifdef _WIN32
#if !defined(SORT_DIGITSASNUMBERS)
// Only defined when: (WINVER >= _WIN32_WINNT_WIN7)
// Note: Move to CompareStringEx once XP support is dropped
#define SORT_DIGITSASNUMBERS 0x00000008 // use digits as numbers sort method
#endif
#endif

#if defined(__WXMSW__)
#include <wx/msw/msvcrt.h>
#endif

/////////////////////////////////////////////////////////////////////////////

namespace dconSoft
{
namespace ARBCommon
{
namespace StringUtil
{

long ToLong(wxString const& inStr)
{
	long val = 0;
	inStr.ToLong(&val);
	return val;
}


unsigned long ToULong(wxString const& inStr)
{
	unsigned long val = 0;
	inStr.ToULong(&val);
	return val;
}


bool ToDouble(wxString const& inStr, double& outValue)
{
	bool rc = inStr.ToDouble(&outValue);

	if (!rc)
	{
		// This may have failed for 2 reasons:
		// - Bad data.
		// - Different decimal point from Locale (using "." in non"." locale)

		wxChar pt = wxNumberFormatter::GetDecimalSeparator();

		// So we only reparse if the incoming string does not contain
		// the locale's decimal point.
		if (pt != L'.' && wxNOT_FOUND == inStr.Find(pt))
			rc = inStr.ToCDouble(&outValue);
	}
	return rc;
}


double ToDouble(wxString const& inStr)
{
	double val = 0.0;
	ToDouble(inStr, val);
	return val;
}


bool ToCLong(wxString const& inStr, long& outValue, bool bRetry)
{
	bool bOk = inStr.ToCLong(&outValue);
	// The above fails for "123-45" and returns 0. Before it returned 123.
	// That's the behavior I'm relying on. (Needed when reading dates)
	if (!bOk && bRetry)
	{
		std::wistringstream str(inStr.wc_str());
		str >> outValue;
	}
	return bOk;
}


long ToCLong(wxString const& inStr)
{
	long val = 0;
	ToCLong(inStr, val, true);
	return val;
}


bool ToCULong(wxString const& inStr, unsigned long& outValue, bool bRetry)
{
	bool bOk = inStr.ToCULong(&outValue);
	// The above fails for "123-45" and returns 0. Before it returned 123.
	// That's the behavior I'm relying on. (Needed when reading dates)
	if (!bOk && bRetry)
	{
		std::wistringstream str(inStr.wc_str());
		str >> outValue;
	}
	return bOk;
}


unsigned long ToCULong(wxString const& inStr)
{
	unsigned long val = 0;
	ToCULong(inStr, val, true);
	return val;
}


double ToCDouble(wxString const& inStr)
{
	double val = 0.0;
	inStr.ToCDouble(&val);
	return val;
}


namespace
{
constexpr char sc_Whitespace[] = "\r\n\t ";
constexpr wchar_t sc_wWhitespace[] = L"\r\n\t ";
enum class TrimType
{
	Left = 0x1,
	Right = 0x2,
	Both = Left | Right
};


template <typename T> T TrimImpl(T const& inStr, T const& toTrim, TrimType type)
{
	if (0 == inStr.length())
		return inStr;
	typename T::size_type posFirst = 0;
	if (static_cast<unsigned int>(type) & static_cast<unsigned int>(TrimType::Left))
	{
		posFirst = inStr.find_first_not_of(toTrim);
		if (T::npos == posFirst)
			return T();
	}
	typename T::size_type posLast = inStr.length() - 1;
	if (static_cast<unsigned int>(type) & static_cast<unsigned int>(TrimType::Right))
	{
		posLast = inStr.find_last_not_of(toTrim);
		if (T::npos == posLast)
			return T();
	}
	if (inStr.length() == posLast - posFirst + 1)
		return inStr;
	typename T::size_type posLength = posLast - posFirst + 1;
	return inStr.substr(posFirst, posLength);
}


bool UseCompareString()
{
#ifdef WIN32
	// No need to check OS version - we now target only Win7 or better.
	return true;
#else
	return false;
#endif
}
} // namespace


bool CanCompareDigits()
{
	return UseCompareString();
}


int CompareNoCase(wxString const& inStr1, wxString const& inStr2)
{
#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PC_APP || WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
	return inStr1.CmpNoCase(inStr2);
#elif defined(WIN32)
	// WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP
	if (UseCompareString())
	{
		switch (CompareStringW(
			LOCALE_USER_DEFAULT,
			NORM_IGNORECASE | SORT_DIGITSASNUMBERS,
			inStr1.wc_str(),
			static_cast<int>(inStr1.length()),
			inStr2.wc_str(),
			static_cast<int>(inStr2.length())))
		{
		case CSTR_LESS_THAN:
			return -1;
		case CSTR_EQUAL:
			return 0;
		case CSTR_GREATER_THAN:
			return 1;
		// Fall thru on error
		default:
			break;
		}
	}
#if (_WIN32_IE >= _WIN32_IE_IE55)
	return StrCmpLogicalW(inStr1.wc_str(), inStr2.wc_str());
#else
	return inStr1.CmpNoCase(inStr2);
#endif
#else
	return inStr1.CmpNoCase(inStr2);
#endif
}


std::string Trim(std::string const& inStr)
{
	return TrimImpl<std::string>(inStr, sc_Whitespace, TrimType::Both);
}


wxString Trim(wxString const& inStr)
{
	return TrimImpl<wxString>(inStr, sc_wWhitespace, TrimType::Both);
}


wxString Trim(wxString const& inStr, wchar_t toTrim)
{
	return TrimImpl<wxString>(inStr, wxString(1, toTrim), TrimType::Both);
}


std::string TrimLeft(std::string const& inStr)
{
	return TrimImpl<std::string>(inStr, sc_Whitespace, TrimType::Left);
}


wxString TrimLeft(wxString const& inStr)
{
	return TrimImpl<wxString>(inStr, sc_wWhitespace, TrimType::Left);
}


wxString TrimLeft(wxString const& inStr, wchar_t toTrim)
{
	return TrimImpl<wxString>(inStr, wxString(1, toTrim), TrimType::Left);
}


std::string TrimRight(std::string const& inStr)
{
	return TrimImpl<std::string>(inStr, sc_Whitespace, TrimType::Right);
}


wxString TrimRight(wxString const& inStr)
{
	return TrimImpl<wxString>(inStr, sc_wWhitespace, TrimType::Right);
}


wxString TrimRight(wxString const& inStr, wchar_t toTrim)
{
	return TrimImpl<wxString>(inStr, wxString(1, toTrim), TrimType::Right);
}


template <typename T, typename S> T ReplaceImpl(T const& inStr, T const& inReplace, T const& inReplaceWith)
{
	if (inReplace.empty())
		return inStr;
	S str;
	T text(inStr);
	while (!text.empty())
	{
		typename T::size_type pos = text.find(inReplace);
		if (T::npos != pos)
		{
			if (0 < pos)
			{
				str << text.substr(0, pos);
			}
			if (!inReplaceWith.empty())
				str << inReplaceWith;
			text = text.substr(pos + inReplace.length(), T::npos);
		}
		else
		{
			str << text;
			text.clear();
		}
	}
	return str.str();
}


std::string Replace(std::string const& inStr, std::string const& inReplace, std::string const& inReplaceWith)
{
	return ReplaceImpl<std::string, std::stringstream>(inStr, inReplace, inReplaceWith);
}


// Note: Use wxString::Replace instead unless you need a copy modified.
wxString Replace(wxString const& inStr, wxString const& inReplace, wxString const& inReplaceWith)
{
	return ReplaceImpl<wxString, std::wstringstream>(inStr, inReplace, inReplaceWith);
}


// Using IEC binary prefixes
wxString FormatBytes(double inSize, int inPrec, ByteSizeStyle inSizeStyle)
{
	// byte, kilo, mega, giga, tera, peta, exa, zetta, yotta, ronna, quetta
	static wchar_t const* const sc_unitsSI[]
		= {L" B", L" kB", L" MB", L" GB", L" TB", L" PB", L" EB", L"ZB", L"YB", L"RB", L"QB"};
	// byte, kibi, mebi, gibi, tebi, pebi, exbi, zebi, yobi, ??, ??
	static wchar_t const* const sc_unitsBinary[]
		= {L" B", L" KiB", L" MiB", L" GiB", L" TiB", L" PiB", L" EiB", L"ZiB", L"YiB", L"RiB", L"QiB"};
	static wchar_t const* const sc_unitsTrue[]
		= {L" B", L" KB", L" MB", L" GB", L" TB", L" PB", L" EB", L"ZB", L"YB", L"RB", L"QB"};
	static const struct
	{
		wchar_t const* const* units;
		size_t numUnits;
		double base;
	} sc_units[] = {
		{sc_unitsSI, _countof(sc_unitsSI), 1000.0},
		{sc_unitsBinary, _countof(sc_unitsBinary), 1024.0},
		{sc_unitsTrue, _countof(sc_unitsTrue), 1024.0},
	};

	size_t unitIndex = 0;
	switch (inSizeStyle)
	{
	case ByteSizeStyle::SI:
		unitIndex = 0;
		break;
	case ByteSizeStyle::Binary:
		unitIndex = 1;
		break;
	case ByteSizeStyle::True:
		unitIndex = 2;
		break;
	}

	int index = 0;
	if (std::abs(inSize) != 0.0)
	{
		index = std::min(
			static_cast<int>(log(inSize) / log(sc_units[unitIndex].base)),
			static_cast<int>(sc_units[unitIndex].numUnits) - 1);
		inSize /= pow(sc_units[unitIndex].base, index);
	}
	wxString form(sc_units[unitIndex].units[index]);

	wxString val = ARBDouble::ToString(inSize, inPrec, ARBDouble::ZeroStrip::Strip) + form;
	return val;
}

} // namespace StringUtil
} // namespace ARBCommon
} // namespace dconSoft
