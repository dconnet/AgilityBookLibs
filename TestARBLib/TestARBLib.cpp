/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @author David Connet
 *
 * Revision History
 * 2019-10-13 Separated ARB specific things from TestLib.
 * 2019-08-15 wx3.1.2 (maybe earlier) has fixed GetExecutablePath on Mac cmdline
 * 2018-12-16 Convert to fmt.
 * 2017-11-09 Convert from UnitTest++ to Catch
 * 2015-11-27 Added test duration to verbose option.
 * 2013-08-18 Reuse Win/LanguageManager
 * 2012-03-16 Renamed LoadXML functions, added stream version.
 * 2011-11-17 Add ability to switch languages
 * 2011-01-22 Simplified how configs are added (all in TestConfig.cpp).
 * 2009-09-13 Add support for wxWidgets 2.9, deprecate tstring.
 * 2008-01-11 Created
 */

#include "stdafx.h"
#if defined(USING_CATCH2)
#define CATCH_CONFIG_RUNNER
#endif
#pragma warning(disable:5219) // implicit conversion from 'uint64_t' to 'double', possible loss of data
#pragma warning(disable:4583) // destructor is not implicitly called
#include "TestARBLib.h"

// #include "Local.h"
// #include "TestARB.h"

#include "ARBCommon/ARBUtils.h"
#include "ARBCommon/Element.h"
#include "ARBCommon/StringUtil.h"
#include "LibARBWin/ResourceManager.h"
#include <iostream>
#include <stdexcept>

#if defined(__WXWINDOWS__)
#include <wx/app.h>
#include <wx/fs_arc.h>
#include <wx/fs_mem.h>
#include <wx/stdpaths.h>
#endif

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>
#endif


namespace dconSoft
{
using namespace ARBCommon;
using namespace ARBWin;

namespace
{
wxString GetDataFile()
{
#if defined(__WXWINDOWS__)
	wxFileName fileName(wxStandardPaths::Get().GetExecutablePath());
	wxString datafile = GetARBResourceDir() + wxFileName::GetPathSeparator() + fileName.GetName() + L".dat";
#else
#pragma PRAGMA_TODO(write LoadXMLData)
#ifdef WIN32
	wchar_t fileName[MAX_PATH];
	GetModuleFileNameW(nullptr, fileName, _countof(fileName));
	std::wstring datafile(fileName);
	size_t n = datafile.find_last_of('.');
	datafile = datafile.substr(0, n);
	datafile += L".dat";
#else
	wxString datafile = L"./testarb.dat";
#endif
#endif
	return datafile;
}
} // namespace


class CCallbackManager
#if defined(__WXWINDOWS__)
	: public IResourceManagerCallback
#endif
{
	DECLARE_NO_COPY_IMPLEMENTED(CCallbackManager);

public:
	CCallbackManager()
	{
#if defined(__WXWINDOWS__)
		auto datafile = GetDataFile();
		CResourceManager::Get()->Initialize(this, &datafile);
#endif
	}
	virtual ~CCallbackManager()
	{
		CResourceManager::Get()->Cleanup();
	}

	bool SetLang(wxLanguage langId);

private:
	// IResourceManagerCallback
	wxWindow* GetResourceWindow() override
	{
		return nullptr;
	}
	bool GetResImageName(wxArtID const& id, wxArtClient const& client, wxString& outName, bool& outSvg) const override
	{
		return false;
	}
};
namespace
{
CCallbackManager* g_callbackMgr = nullptr;
} // namespace


} // namespace dconSoft

using namespace dconSoft;


int main(int argc, char** argv)
{
#ifdef _WIN32
	_set_error_mode(_OUT_TO_MSGBOX);
#endif

	int ac = argc;
	bool bVerbose = false;
	if (argc >= 2)
	{
		for (int i = 1; i < argc; ++i)
		{
			if (0 == strcmp(argv[i], "verbose"))
			{
				bVerbose = true;
				continue;
			}
			// fprintf(stderr, "Usage: %s [verbose]\n", argv[0]);
			// return -1;
		}
	}

	bool bClean = false;
	char** av = argv;
	char verbose[3] = "-s";

	if (bVerbose)
	{
		bClean = true;
		av = new char*[ac];
		av[0] = argv[0];
		int iNew = 1;
		for (int i = 1; i < argc; ++i)
		{
			if (0 == strcmp(argv[i], "verbose"))
				av[iNew++] = verbose;
			else
				av[iNew++] = argv[i];
		}
	}

#if defined(__WXWINDOWS__)
	wxInitializer initializer(ac, av);
#if defined(__WXMSW__)
	// By default, the path directories are tweaked to remove debug/release.
	// I assume my files are in the same location as the binary.
	// Now I don't need to tweak the wx source!
	wxStandardPaths::Get().DontIgnoreAppSubDir();
#endif
#endif

	std::wstring errs;
	if (!Element::Initialize(errs))
	{
		return 1;
	}

#if defined(__WXWINDOWS__)
	wxFileSystem::AddHandler(new wxArchiveFSHandler);
	wxFileSystem::AddHandler(new wxMemoryFSHandler);
#endif

	bool bRunTests = true;
#if defined(__WXWINDOWS__)
	g_callbackMgr = new CCallbackManager();
#endif

	int rc = -1;
	if (bRunTests)
	{
		rc = Catch::Session().run(ac, av);
	}

	Element::Terminate();
	delete g_callbackMgr;
	g_callbackMgr = nullptr;

	if (bClean)
		delete[] av;

	return rc;
}
