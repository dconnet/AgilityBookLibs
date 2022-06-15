#pragma once

/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 *
 * Revision History
 * 2022-06-09 Created
 */

#include "LibwxARBWin.h"
#include <wx/filename.h>
#include <wx/log.h>


class ARBWIN_API CLogger
{
	DECLARE_NO_COPY_IMPLEMENTED(CLogger)
public:
	// Default logging level (currently set to wxLOG_User)
	static wxLogLevelValues GetLogLevel();

	// Wrapper for wxLogGeneric(GetLogLevel(), L"%s", msg);
	static void Log(wxString const& msg);

	CLogger();

	// keep = 0 means keep all.
	// Sets base logger to write to a file, adds a wxLogWindow
	void EnableLogWindow(wxWindow* parent, bool show, wchar_t const* baseFilename, size_t keepNlogs = 5);

	// These functions are only valid if logging has been enabled
	wxString GetCurrentLogDir() const;
	wxString GetCurrentLogName() const;
	size_t FindExistingLogs(wxArrayString& files);
	wxFrame* GetFrame() const;
	void Show(bool show = true);

private:
	wxString GetTimeStamp() const;
	wxString RotateLogs(size_t keepNlogs);

	wxLogWindow* m_logger;
	wxString m_baseFilename;
	wxFileName m_currentLogName;
};
