#pragma once

/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Image Manager
 * @author David Connet
 *
 * Usage:
 * Users of this can extend by associating a callback class.
 *
 * Revision History
 * 2020-08-22 Fixed for usage with wx3.1.5
 * 2018-10-11 Moved to Win LibARBWin
 * 2015-08-22 Expose LOAD_BITMAP_PNG for use in OnCreateBitmap.
 * 2013-10-13 Changed ImageManager to an art provider.
 * 2012-12-29 Created.
 */

#include "LibwxARBWin.h"

#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/icon.h>


namespace dconSoft
{
namespace ARBWin
{
namespace ImageHelper
{

ARBWIN_API wxBitmap GetBitmap(
	wxWindow* pWindow,
	const wxArtID& id,
	const wxArtClient& client = wxART_OTHER,
	const wxSize& size = wxDefaultSize);

ARBWIN_API wxIcon GetIcon(
	wxWindow* pWindow,
	const wxArtID& id,
	const wxArtClient& client = wxART_OTHER,
	const wxSize& size = wxDefaultSize);

ARBWIN_API wxIcon CreateIconFromBitmap(const wxBitmap& bitmap);


// Setup image ids for things used in LibARBWin.
// Note the user app must provide the loading of these in the Do* functions.

#define ImageMgrAppBundle wxART_MAKE_ART_ID(ImageMgrAppBundle)
#define ImageMgrApp       wxART_MAKE_ART_ID(ImageMgrApp)

#define ImageMgrFolderOpened wxART_MAKE_ART_ID(ImageMgrFolderOpened)

#define ImageMgrBlank     wxART_MAKE_ART_ID(ImageMgrBlank)
#define ImageMgrCheck     wxART_MAKE_ART_ID(ImageMgrCheck)
#define ImageMgrChecked   wxART_MAKE_ART_ID(ImageMgrChecked)
#define ImageMgrUnChecked wxART_MAKE_ART_ID(ImageMgrUnChecked)
#define ImageMgrQuestion  wxART_MAKE_ART_ID(ImageMgrQuestion)

#define ImageMgrAbout     wxART_MAKE_ART_ID(ImageMgrAbout)
#define ImageMgrCalendar  wxART_MAKE_ART_ID(ImageMgrCalendar)
#define ImageMgrCopy      wxART_MAKE_ART_ID(ImageMgrCopy)
#define ImageMgrCut       wxART_MAKE_ART_ID(ImageMgrCut)
#define ImageMgrDelete    wxART_MAKE_ART_ID(ImageMgrDelete)
#define ImageMgrDuplicate wxART_MAKE_ART_ID(ImageMgrDuplicate)
#define ImageMgrFind      wxART_MAKE_ART_ID(ImageMgrFind)
#define ImageMgrNew       wxART_MAKE_ART_ID(ImageMgrNew)
#define ImageMgrOpen      wxART_MAKE_ART_ID(ImageMgrOpen)
#define ImageMgrPaste     wxART_MAKE_ART_ID(ImageMgrPaste)
#define ImageMgrPreview   wxART_MAKE_ART_ID(ImageMgrPreview)
#define ImageMgrPrint     wxART_MAKE_ART_ID(ImageMgrPrint)
#define ImageMgrSave      wxART_MAKE_ART_ID(ImageMgrSave)
#define ImageMgrSettings  wxART_MAKE_ART_ID(ImageMgrSettings)

} // namespace ImageHelper
} // namespace ARBWin
} // namespace dconSoft
