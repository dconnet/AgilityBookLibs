#pragma once

/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Type definitions.
 * @author David Connet
 *
 * Revision History
 * 2018-04-19 Fixed string/double parsing for locales.
 * 2014-11-17 Enhanced FormatBytes
 * 2014-06-24 Added CompareNoCase.
 * 2012-08-12 Moved FormatBytes to StringUtil
 * 2009-09-13 Add support for wxWidgets 2.9, deprecate tstring.
 * 2009-03-30 Remove Convert and replaced with stringA/etc
 * 2009-03-12 Converting all TCHAR stuff to wxWidgets
 * 2008-06-29 Moved string stuff out of ARBTypes.
 */

#include "LibwxARBCommon.h"

#include <string>

#include <wx/string.h>
class wxMemoryOutputStream;


/**
 * String utility functions
 */
namespace dconSoft
{
namespace ARBCommon
{
namespace StringUtil
{
ARBCOMMON_API long ToLong(wxString const& inStr);
ARBCOMMON_API unsigned long ToULong(wxString const& inStr);
/// @note This function differs from the others - instead of only
/// parsing in the current locale, this will also fall back to English
/// ('.' for decimal)
ARBCOMMON_API bool ToDouble(wxString const& inStr, double& outValue);
ARBCOMMON_API double ToDouble(wxString const& inStr);

// These functions mimic wx2.9.x. They allow wx2.8 usage.
// The ToC<type> use the "C" locale.
// Typically, the "ToC" routines are only used in Element.
// bRetry is for wx2.9+: It fails on "123-23" now. Old behavior returned "123".
ARBCOMMON_API bool ToCLong(wxString const& inStr, long& outValue, bool bRetry = false);
ARBCOMMON_API long ToCLong(wxString const& inStr);
ARBCOMMON_API bool ToCULong(wxString const& inStr, unsigned long& outValue, bool bRetry = false);
ARBCOMMON_API unsigned long ToCULong(wxString const& inStr);
ARBCOMMON_API double ToCDouble(wxString const& inStr);

// The following CompareNoCase functions can compare strings with digits
// ("x2" will work before "x10")
ARBCOMMON_API bool CanCompareDigits();

// Case insensitive comparison (for better lexical comparison)
// It does not mean that lower case sorts before (or after) upper case.
ARBCOMMON_API int CompareNoCase(wxString const& inStr1, wxString const& inStr2);

// Some CString-style functions

ARBCOMMON_API std::string Trim(std::string const& inStr);
ARBCOMMON_API wxString Trim(wxString const& inStr);
ARBCOMMON_API wxString Trim(wxString const& inStr, wchar_t toTrim);

ARBCOMMON_API std::string TrimLeft(std::string const& inStr);
ARBCOMMON_API wxString TrimLeft(wxString const& inStr);
ARBCOMMON_API wxString TrimLeft(wxString const& inStr, wchar_t toTrim);

ARBCOMMON_API std::string TrimRight(std::string const& inStr);
ARBCOMMON_API wxString TrimRight(wxString const& inStr);
ARBCOMMON_API wxString TrimRight(wxString const& inStr, wchar_t toTrim);

ARBCOMMON_API std::string Replace(
	std::string const& inStr,
	std::string const& inReplace,
	std::string const& inReplaceWith);

ARBCOMMON_API wxString Replace(wxString const& inStr, wxString const& inReplace, wxString const& inReplaceWith);

enum class ByteSizeStyle
{
	SI,     // KB == 1000 btyes
	Binary, // KiB == 1024 bytes
	True,   // KB == 1024 bytes (non-IEC)
};

/**
 * Return a formatted string using IEC binary prefixes.
 * @param inSize Number of bytes
 * @param inPrec Precision (passed to ARBDouble::ToString)
 * @param inSizeStyle Use SI, binary, or programmer (true!) units
 */
ARBCOMMON_API wxString FormatBytes(double inSize, int inPrec = 2, ByteSizeStyle inSizeStyle = ByteSizeStyle::Binary);

} // namespace StringUtil
} // namespace ARBCommon
} // namespace dconSoft
