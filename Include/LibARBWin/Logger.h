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
 * 2023-08-18 Allow turning on/off CStackLogger (useful for tests)
 * 2022-06-09 Created
 */

#include "LibwxARBWin.h"

#include <wx/filename.h>
#include <wx/log.h>


namespace dconSoft
{
namespace ARBWin
{

// Note about these loggers.
// CLogger uses level wxLOG_User
// CStackLogger uses level wxLOG_User+1
// In release, we specifically set the level to wxLOG_User.
// In debug, we set wxLOG_User+1.
// In user code, calling wxLog::SetLogLevel will affect these.

class ARBWIN_API CLogger
{
	DECLARE_NO_COPY_IMPLEMENTED(CLogger)
public:
	// Will messages appear based on wxLogLevel
	static bool IsLoggerEnabled();
	// Default logging level (currently set to wxLOG_User)
	static wxLogLevelValues GetLogLevel();
	// Turn all logging on/off
	static bool IsLoggingedEnabled();
	static void EnableLogging(bool enable);

	// Wrapper for wxLogGeneric(GetLogLevel(), L"%s", msg);
	static void Log(wxString const& msg);

	CLogger();

	// Initialize log directory without starting logging.
	// EnableWindow will call this automatically.
	bool Initialize(wchar_t const* baseFilename, bool enableStackLogger);

	bool IsEnabled() const;

	// keep = 0 means keep all.
	// Sets base logger to write to a file, adds a wxLogWindow
	void EnableLogWindow(
		wxWindow* parent,
		bool show,
		wchar_t const* baseFilename,
		bool enableStackLogger,
		size_t keepNlogs = 5);

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
	static bool m_enabled;
};


// This is the same thing as ARBCommon::CStackTracer, but uses CLogger. Also,
// this is enabled in release builds, however it is suppressed by default.
// Use 'enableStackLogger' in CLogger to enable.
// The logging level of this is 1 higher than CLogger.
class ARBWIN_API CStackLogger
{
public:
	// Will messages appear based on wxLogLevel
	static bool IsLoggerEnabled();
	// Default logging level (currently set to wxLOG_User+1)
	static wxLogLevelValues GetLogLevel();

	// Wrapper for wxLogGeneric(GetLogLevel(), L"%s", msg);
	static void Log(wxString const& msg);

	explicit CStackLogger(wxString const& msg, bool disableStopWatch = false);
	~CStackLogger();
	void Tickle(wxString const& msg);

private:
	wxString m_msg;
	bool m_disableStopWatch;
	wxStopWatch m_stopwatch;
	long m_tickle;
	static int m_indent;

	CStackLogger() = delete;
	CStackLogger(CStackLogger const&) = delete;
	CStackLogger(CStackLogger&&) = delete;
	CStackLogger& operator=(CStackLogger const&) = delete;
	CStackLogger& operator=(CStackLogger&&) = delete;
};

} // namespace ARBWin
} // namespace dconSoft
