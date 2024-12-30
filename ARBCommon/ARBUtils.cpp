/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Global functions
 * @author David Connet
 *
 * Revision History
 * 2022-02-01 Added backup directory to CreateBackupFile.
 * 2021-08-24 Make StackTracer work on non-Win32 platforms.
 * 2019-08-15 Added GetARBResourceDir
 * 2019-06-28 Fix issue with change nBackups to less than existing backups.
 * 2018-10-30 Moved some utils from ARBWin.
 */

#include "stdafx.h"
#include "ARBCommon/ARBUtils.h"

#include <wx/config.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>
#endif


namespace dconSoft
{
namespace ARBCommon
{

#if USE_STACKTRACER
int CStackTracer::m_indent = 0;


CStackTracer::CStackTracer(wxString const& msg, bool disableStopWatch)
	: m_msg(msg)
	, m_disableStopWatch(disableStopWatch)
	, m_stopwatch()
	, m_tickle(0)
{
	++m_indent;
	wxLogDebug("%*sEnter: %s", m_indent, " ", m_msg);
	if (!m_disableStopWatch)
		m_stopwatch.Start();
}


CStackTracer::~CStackTracer()
{
	if (m_disableStopWatch)
		wxLogDebug("%*sLeave: %s", m_indent, " ", m_msg);
	else
	{
		m_stopwatch.Pause();
		wxLogDebug("%*sLeave[%ld]: %s", m_indent, " ", m_stopwatch.Time(), m_msg);
	}
	--m_indent;
}


void CStackTracer::Tickle(wxString const& msg)
{
	if (m_disableStopWatch)
		wxLogDebug("%*sTickle: %s", m_indent, " ", msg);
	else
	{
		long t = m_stopwatch.Time();
		wxLogDebug("%*sTickle[%ld]: %s", m_indent, " ", t - m_tickle, msg);
		m_tickle = t;
	}
}
#endif


CConfigPathHelper::CConfigPathHelper(wxString const& key)
	: m_path(wxConfig::Get()->GetPath())
{
	if (!key.empty())
	{
		wxConfig::Get()->SetPath(key);
	}
}


CConfigPathHelper::~CConfigPathHelper()
{
	wxConfig::Get()->SetPath(m_path);
}


wxString GetARBResourceDir()
{
#if defined(__WXMAC__)
	// Note: For command line, this now (as of 3.1.2) returns the exe path.
	// For the UI, it's the resource bundle path
	return wxStandardPaths::Get().GetResourcesDir();
#else
	wxFileName fileName(wxStandardPaths::Get().GetExecutablePath());
	return fileName.GetPath();
#endif
}


bool CreateBackupFile(wxString const& inFilename, int nBackups, wxString const& inDirectory)
{
	bool bChanged = false;
	if (0 < nBackups)
	{
		wxString filename(inFilename);
		if (!inDirectory.empty())
		{
			wxString dir = wxExpandEnvVars(inDirectory);
			wxFileName backup(dir, wxString());
			if (!backup.Exists())
			{
				if (!backup.Mkdir())
				{
					wxLogError("ERROR: Cannot create directory %s", backup.GetFullPath());
					return false;
				}
			}
			wxFileName file(inFilename);
			backup.SetFullName(file.GetFullName());
			filename = backup.GetFullPath();
		}
		// First find a hole.
		int nHole = -1;
		int i;
		for (i = 1; i <= nBackups; ++i)
		{
			wxString backup = wxString::Format(L"%s.bck%d", filename, i);
			if (!wxFile::Exists(backup))
			{
				nHole = i;
				break;
			}
		}
		if (-1 == nHole)
			nHole = nBackups;
		// Then shift all the files into the hole.
		for (i = nHole; i > 1; --i)
		{
			wxString backup = wxString::Format(L"%s.bck%d", filename, i);
			if (wxFile::Exists(backup))
				wxRemoveFile(backup);
			wxString oldFilename = wxString::Format(L"%s.bck%d", filename, i - 1);
			wxRenameFile(oldFilename, backup);
			bChanged = true;
		}
		// File may not exist if doing a 'save as'
		if (wxFile::Exists(inFilename))
		{
			bChanged = true;
			wxString backup = filename + L".bck1";
			wxCopyFile(inFilename, backup, true); // Force an overwrite (if nBackups+1 exists, we error out otherwise)
		}
	}
	return bChanged;
}


bool GetFileTimes(wxFileName const& filename, wxDateTime* dtAccess, wxDateTime* dtMod, wxDateTime* dtCreate)
{
#if defined(__WXMSW__)
	// Using wx to get the times on network files is really slow.
	// I suspect it's the win32 CreateFile/GetFileTime apis.
	struct __stat64 s;
	if (0 != _tstat64(filename.GetFullPath().wc_str(), &s))
		return false;
	if (dtAccess)
		*dtAccess = wxDateTime(s.st_atime);
	if (dtMod)
		*dtMod = wxDateTime(s.st_mtime);
	if (dtCreate)
		*dtCreate = wxDateTime(s.st_ctime);
	return true;
#else
	return filename.GetTimes(dtAccess, dtMod, dtCreate);
#endif
}

} // namespace ARBCommon
} // namespace dconSoft
