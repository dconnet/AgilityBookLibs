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
 * 2019-01-31 Moved GetOSInfo to LibARBWin/ARBDebug.
 * 2014-06-19 Added IsWin7OrBetter.
 * 2013-07-17 Created
 */

#include "LibwxARBCommon.h"


namespace dconSoft
{
namespace ARBCommon
{

/**
 * Make a string safe for HTML viewing.
 * @param inRawData String to sanitize
 * @param bConvertCR Convert \n to html-breaks.
 */
ARBCOMMON_API wxString SanitizeStringForHTML(wxString const& inRawData, bool bConvertCR = true);

/**
 * These are the strings we recognize as platforms.
 * On Windows, we use the compiled arch. Other OSs use native.
 * The reason being we don't want to deal with a 32->64 bit MSI switch.
 */
ARBCOMMON_API wxString GetARBArch();

/**
 * Get the native arch.
 */
ARBCOMMON_API wxString GetNativeARBArch();


/**
 * Get OS version.
 * @param verMajor OS major version number.
 * @param verMinor OS minor version number.
 * @param verMicro OS micro version number.
 */
ARBCOMMON_API bool GetOSInfo(int& verMajor, int& verMinor, int& verMicro);


/**
 * Are we running on Win7 or better?
 */
ARBCOMMON_API bool IsWin7OrBetter();


/**
 * Translate a short to a Roman numeral
 */
ARBCOMMON_API wxString ShortToRoman(short value);

} // namespace ARBCommon
} // namespace dconSoft
