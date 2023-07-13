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

#include "ARBCommon/ARBUtils.h"
#include <wx/filename.h>
#include <wx/log.h>


namespace dconSoft
{
namespace ARBWin
{

class ARBWIN_API CLogger
{
	DECLARE_NO_COPY_IMPLEMENTED(CLogger)
public:
	// Default logging level (currently set to wxLOG_User)
	static wxLogLevelValues GetLogLevel();

	// Wrapper for wxLogGeneric(GetLogLevel(), L"%s", msg);
	static void Log(wxString const& msg);

	CLogger();

	// Initialize log directory without starting logging.
	// EnableWindow will call this automatically.
	bool Initialize(wchar_t const* baseFilename);

	bool IsEnabled() const;

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


// This is the same thing as ARBCommon::CStackTracer, but uses CLogger
class ARBWIN_API CStackLogger
{
#if USE_STACKTRACER
public:
	explicit CStackLogger(wxString const& msg);
	~CStackLogger();
	void Tickle(wxString const& msg);

private:
	wxString m_msg;
	wxStopWatch m_stopwatch;
	long m_tickle;
	static int m_indent;

	CStackLogger() = delete;
	CStackLogger(CStackLogger const&) = delete;
	CStackLogger(CStackLogger&&) = delete;
	CStackLogger& operator=(CStackLogger const&) = delete;
	CStackLogger& operator=(CStackLogger&&) = delete;
#endif
};

#if USE_STACKTRACER
#define STACK_LOGGER(name, msg)     CStackLogger name(msg)
#define STACK_LOG_TICKLE(name, msg) name.Tickle(msg)

#else
#define STACK_LOGGER(name, msg)
#define STACK_LOG_TICKLE(name, msg)
#endif

} // namespace ARBWin
} // namespace dconSoft
