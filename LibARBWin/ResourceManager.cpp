/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Resource Manager
 * @author David Connet
 *
 * Revision History
 * 2025-10-01 Remove use of gsl::narrow. This was causing an exception on a user machine. (no-repro here)
 * 2022-04-15 Use wx DPI support.
 * 2021-12-18 Created.
 */

#include "stdafx.h"
#include "LibARBWin/ResourceManager.h"

#include "ARBCommon/ARBUtils.h"
#include "ARBCommon/LibArchive.h"
#include "LibARBWin/ImageHelperBase.h"

#include <wx/bmpbndl.h>
#include <wx/mstream.h>
#include <wx/stdpaths.h>
#include <sstream>

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>
#endif


namespace dconSoft
{
using namespace ARBCommon;
namespace ARBWin
{

CResourceManager* CResourceManager::Get()
{
	static CResourceManager* mgr = nullptr;
	if (!mgr)
	{
		// Note, this is cleanuped in wxWidget code for wxArtProviders
		mgr = new CResourceManager();
		wxArtProvider::Push(mgr);
	}
	return mgr;
}


CResourceManager::CResourceManager()
	: m_callback(nullptr)
	, m_archive(nullptr)
{
}


void CResourceManager::Initialize(IResourceManagerCallback* pCallback, wxString const* archiveName)
{
	m_callback = pCallback;

	wxString datafile;
	if (archiveName)
		datafile = *archiveName;
	else
	{
		wxFileName fileName(wxStandardPaths::Get().GetExecutablePath());
		datafile = ARBCommon::GetARBResourceDir() + wxFileName::GetPathSeparator() + fileName.GetName() + L".dat";
	}
	// The archive isn't actually opened until we extract. So we can't verify here.
	m_archive = new ARBCommon::CLibArchive(datafile);
}


void CResourceManager::Cleanup()
{
	delete m_archive;
	m_callback = nullptr;
}


bool CResourceManager::Exists(wxString const& archiveFile) const
{
	return m_archive && m_archive->Exists(archiveFile);
}


size_t CResourceManager::FindDirectories(wxString const& archiveDir, std::vector<wxString>& outDirectories) const
{
	if (!m_archive)
	{
		outDirectories.clear();
		return 0;
	}
	return m_archive->FindDirectories(archiveDir, outDirectories);
}


bool CResourceManager::LoadFile(wxString const& archiveFile, std::ostream& outData)
{
	return m_archive && m_archive->Extract(archiveFile, outData);
}


wxBitmap CResourceManager::CreateBitmap(wxArtID const& id, wxArtClient const& client, wxSize const& size)
{
	if (!m_callback)
		return wxBitmap();

	auto pWindow = m_callback->GetResourceWindow();
	wxBitmap bmp;

	// MENU/TOOLBAR uses size.
	// OTHER does not - these should all be imagelists
	// MESSAGE_BOX does not - these should all be 32px icons
	int imageSize = size.x;
	if (imageSize <= 0)
		imageSize = wxArtProvider::GetNativeSizeHint(client).x;
	if (imageSize <= 0)
	{
		if (wxART_OTHER == client)
			imageSize = pWindow->FromDIP(16);
		else if (wxART_MESSAGE_BOX == client)
			imageSize = pWindow->FromDIP(32);
	}
	assert(imageSize > 0);

	if (id == ImageMgrBlank)
	{
		// Initialize image to black.
		wxImage img(imageSize, imageSize, true);
		img.SetMaskColour(wxBLACK->Red(), wxBLACK->Green(), wxBLACK->Blue());
		bmp = wxBitmap(img);
	}
	else
	{
		wxString name;
		bool isSvg;
		if (m_callback->GetResImageName(id, client, name, isSvg))
		{
			if (isSvg)
			{
				name += L".svg";
				std::ostringstream str;
#ifdef _DEBUG
				bool extracted =
#endif
					m_archive->Extract(name, str);
#ifdef _DEBUG
				assert(extracted);
#endif

				wxBitmapBundle bundle = wxBitmapBundle::FromSVG(str.str().c_str(), wxSize(imageSize, imageSize));
				assert(bundle.IsOk());
				bmp = bundle.GetBitmap(wxSize(imageSize, imageSize));
			}
			else
			{
				std::ostringstream str;

				wxLogNull suppress;
				unsigned int scale = static_cast<unsigned int>(fabs(pWindow->GetDPIScaleFactor()) * 100.0);
				unsigned int rescale = 1;
#if defined(wxHAS_DPI_INDEPENDENT_PIXELS)
				scale = 100;
#else
				if (scale > 100)
				{
					wxString png(name);
					png += L"@2x.png";

					if (m_archive->Extract(png, str))
					{
						auto const& s = str.str();
						bmp = wxBitmap::NewFromPNGData(s.c_str(), s.size());
					}
					if (bmp.IsOk())
						rescale = 2;
				}
#endif
				if (!bmp.IsOk())
				{
					name += L".png";
					if (m_archive->Extract(name, str))
					{
						auto const& s = str.str();
						bmp = wxBitmap::NewFromPNGData(s.c_str(), s.size());
					}
				}

				if (100 * rescale != scale && bmp.IsOk())
				{
					wxImage image = bmp.ConvertToImage();
					int x = (bmp.GetWidth() * scale / 100) / rescale;
					int y = (bmp.GetHeight() * scale / 100) / rescale;
					image.Rescale(x, y);
					bmp = wxBitmap(image);
				}
				assert(bmp.IsOk());
			}
		}
		else
		{
#if defined(_DEBUG) || defined(__WXDEBUG__)
			// Image not found - and it's not something we except.
			// (if we start using other wx art, add to this list)
			// clang-format off
			if (id == wxART_FILE_SAVE_AS
			|| id == wxART_INFORMATION
			|| id == wxART_PRINT
			|| id == wxART_GOTO_FIRST
			|| id == wxART_GOTO_LAST
			|| id == wxART_GO_BACK
			|| id == wxART_GO_FORWARD
			|| id == wxART_MINUS
			|| id == wxART_PLUS
			|| id == wxART_WARNING
			|| id == wxART_ERROR)
				// clang-format on
				;
			else
				assert(0);
#endif
			bmp = wxArtProvider::CreateBitmap(id, client, size);
		}
	}
	return bmp;
}


wxIconBundle CResourceManager::CreateIconBundle(wxArtID const& id, wxArtClient const& client)
{
	wxIconBundle bundle;
	if (id == ImageMgrAppBundle)
	{
		bundle.AddIcon(CResourceManager::Get()->GetIcon(ImageMgrApp, wxART_OTHER, wxSize(16, 16)));
		bundle.AddIcon(CResourceManager::Get()->GetIcon(ImageMgrApp, wxART_OTHER, wxSize(32, 32)));
		bundle.AddIcon(CResourceManager::Get()->GetIcon(ImageMgrApp, wxART_OTHER, wxSize(48, 48)));
		bundle.AddIcon(CResourceManager::Get()->GetIcon(ImageMgrApp, wxART_OTHER, wxSize(256, 256)));
	}
	if (bundle.IsOk())
		return bundle;
	return wxArtProvider::CreateIconBundle(id, client);
}

} // namespace ARBWin
} // namespace dconSoft
