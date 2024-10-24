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

	void SetImage(wxWindow const* inParent, wxArtID const& artId, int defaultSize = 128);

	wxBitmapBundle image;

	// Main page
	wxString productName; // Product name
	wxString copyright;   // Copyright message
	wxString productDesc; // Description
	struct LinkInfo
	{
		wxString desc; // Visible text
		wxString url;  // URL
		bool offset;   // Inset control
	};
	std::vector<LinkInfo> links; // Email, website, etc

	// Info page
	wxString version;                                                                      // Version number
	wxString compiledOn{ARBCommon::CVersionNum::GetCompiledOn(__DATE__, __TIME__, false)}; // Compiled-on information
	wxString userDir; // User data directory (logging)
	// 3rd party frameworks
	//  wxWidgets and libfmt are automatically added.
	std::vector<std::pair<wxString, wxString>> frameworks;
};

// The following macros need the specified header included where used.
// Usage "ADD_THING(aboutinfo.frameworks);" - yes, use a trailing ';' so it "looks" right.
// #include "wx/wxsqlite3_version.h"
#define ADD_ABOUT_WXSQLITE3(frameworks) \
	frameworks.push_back(std::make_pair( \
		L"wxSqlite3", \
		wxString::Format( \
			"%d.%d.%d.%d", \
			WXSQLITE3_MAJOR_VERSION, \
			WXSQLITE3_MINOR_VERSION, \
			WXSQLITE3_RELEASE_NUMBER, \
			WXSQLITE3_SUBRELEASE_NUMBER)))
// #include "nlohmann/json_fwd.hpp"
#define ADD_ABOUT_JSON(info) \
	info.frameworks.push_back(std::make_pair( \
		L"nlohmann/json", \
		wxString::Format( \
			"%d.%d.%d", \
			NLOHMANN_JSON_VERSION_MAJOR, \
			NLOHMANN_JSON_VERSION_MINOR, \
			NLOHMANN_JSON_VERSION_PATCH)))
// I also use 'gsl', 'tidy', 'stduuid' - but they don't have versions in their headers.
#define ADD_ABOUT_GSL(frameworks)     frameworks.push_back(std::make_pair(L"gsl", L"4.1.0"))
#define ADD_ABOUT_TIDY(frameworks)    frameworks.push_back(std::make_pair(L"tidy", L"5.8.0"))
#define ADD_ABOUT_STDUUID(frameworks) frameworks.push_back(std::make_pair(L"stduuid", L"1.2.3"))


/**
 * Display an about box.
 * @param aboutInfo Information to populate into dialog
 * @param inParent Parent window
 * @param inCaption Caption
 */
ARBWIN_API void About(AboutInfo const& aboutInfo, wxWindow* inParent, wxString const* inCaption = nullptr);

} // namespace ARBWin
} // namespace dconSoft
