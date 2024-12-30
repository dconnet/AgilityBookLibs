#pragma once

/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief ARBDebug class
 * @author David Connet
 *
 * Revision History
 * 2019-01-31 Moved from ARB.
 * 2018-01-28 Created
 */

#include "LibwxARBWin.h"

#include "ARBCommon/VersionNum.h"
#include <vector>


/**
 * General information to be reported
 */

namespace dconSoft
{
namespace ARBWin
{
namespace ARBDebug
{

// These are for consistent reporting in About dialog and sysinfo.
// The libraries and exe are always compiled together at one time.
ARBWIN_API wxString GetCompileDate();
ARBWIN_API wxString GetCompileTime();

ARBWIN_API wxString GetOSName();
ARBWIN_API wxString GetArchName();
ARBWIN_API wxString GetEndiannessName();

ARBWIN_API wxString GetSystemInfo(wxWindow const* pWindow, ARBCommon::CVersionNum const& ver);
ARBWIN_API wxString GetRegistryInfo();

/**
 * Dump registry information
 * @param inGroup Registry item (relative to wxConfig current path)
 * @param outData Output for all registry data
 * @param outItems Output for string items (only)
 * @return Number of registry items added to outData.
 */
ARBWIN_API size_t DumpRegistryGroup(wxString const& inGroup, wxString* outData, std::vector<wxString>* outItems);

} // namespace ARBDebug
} // namespace ARBWin
} // namespace dconSoft
