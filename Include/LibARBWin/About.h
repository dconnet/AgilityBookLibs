#pragma once

/*
 * Copyright (c) David Connet. All Rights Reserved.
 */

/**
 * @file
 *
 * Revision History
 * 2021-12-10 Change About API: Move CompiledOn to header.
 * 2018-12-23 Added headers
 */

#include "LibARBWin/LibwxARBWin.h"

#include "ARBCommon/VersionNum.h"
#include <wx/artprov.h>


namespace dconSoft
{
namespace ARBWin
{

// Links:
// !desc.empty() && !url.empty(): Inserts space between links
// !desc.empty() && url.empty(): Inserts static text
// !desc.empty() && !url.empty(): Inserts hyperlink
// desc.empty() && !url.empty(): Uses URL text as visible text also
// Note: by default, links will start right next to the previous text.

struct ARBWIN_API AboutInfo
{
	AboutInfo();

	void SetImage(wxWindow* inParent, wxArtID const& artId, int defaultSize = 128);

	wxBitmapBundle image;
	wxString productName;                                                                  // Product name
	wxString productDesc;                                                                  // Description
	wxString version;                                                                      // Version number
	wxString copyright;                                                                    // Copyright message
	wxString compiledOn{ARBCommon::CVersionNum::GetCompiledOn(__DATE__, __TIME__, false)}; // Compiled-on information
	wxString userDir; // User data directory (logging)
	struct LinkInfo
	{
		wxString desc; // Visible text
		wxString url;  // URL
		bool offset;   // Inset control
	};
	std::vector<LinkInfo> links; // Email, website, etc
};


/**
 * Display an about box.
 * @param aboutInfo Information to populate into dialog
 * @param inParent Parent window
 * @param inCaption Caption
 */
ARBWIN_API void About(AboutInfo const& aboutInfo, wxWindow* inParent, wxString const* inCaption = nullptr);

} // namespace ARBWin
} // namespace dconSoft
