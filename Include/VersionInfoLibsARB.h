#pragma once

/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief EXE/DLL version number
 * @author David Connet
 *
 * @note To use this in VERSIONINFO, the VERSIONINFO resource must be moved
 * into the .rc2 file (non-editable resources). In addition, the vcproj files
 * need to have "../../Include" set on the project resource section (that path
 * is relative to the vcproj file). DO NOT include this file in the main .rc
 * as an include in the TEXTINCLUDE2 section. Otherwise you will have a
 * problem opening the resources in the resource editor as that needs a path
 * relative to the .rc file. (Ok, you could do this if you _also_ add
 * "../Include" to the vcproj resource path, but that just seems weird).
 * Since this file is only used in the rc2 file, just include it there.
 * This keeps all editors/compilers happy.
 *
 * IMPORTANT: When updating the copyright, also update ../../configure.in
 * (the version number is auto-updated)
 *
 * Revision History
 * 2022-03-30 Separated AgilityBook and AgilityBookLibs
 * 2019-02-13 Created
 */


#include "VersionNumberLibs.h"

#define _STR(x) #x
#define STR(x)  _STR(x)

#define ARBLIBS_VER_STR_MAJOR   STR(ARBLIBS_VER_MAJOR)
#define ARBLIBS_VER_STR_MINOR   STR(ARBLIBS_VER_MINOR)
#define ARBLIBS_VER_STR_DOT     STR(ARBLIBS_VER_DOT)
#define ARBLIBS_VER_STR_FILEVER STR(ARBLIBS_VER_BUILD)

#define ARBLIBS_VERSION        ARBLIBS_VER_MAJOR, ARBLIBS_VER_MINOR, ARBLIBS_VER_DOT, ARBLIBS_VER_BUILD
#define ARBLIBS_VERSION_STRING ARBLIBS_VER_STR_MAJOR "." ARBLIBS_VER_STR_MINOR "." ARBLIBS_VER_STR_DOT "." ARBLIBS_VER_STR_FILEVER

#define ARBLIBS_VERSION_CompanyName     "dcon Software"
#define ARBLIBS_VERSION_FileDescription "Agility Record Book"
#define ARBLIBS_VERSION_LegalCopyright  "Copyright (c) 2002-2022 David Connet. All Rights Reserved."
#define ARBLIBS_VERSION_ProductName     "Agility Record Book"
