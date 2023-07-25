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

#include "stdafx.h"
#include "LibARBWin/Logger.h"

#include <wx/dir.h>
#include <wx/log.h>
#include <wx/msgout.h>
#include <wx/regex.h>
#include <wx/stdpaths.h>
#include <fstream>

#if defined(__WXMSW__)
#include <wx/msw/msvcrt.h>
#endif


namespace
{
constexpr wchar_t k_logTimestamp[] = L"%Y-%m-%d %H:%M:%S.%l";
constexpr wxLogLevelValues k_defLogLevel = wxLOG_User;
constexpr wxLogLevelValues k_defStackLevel = static_cast<wxLogLevelValues>(wxLOG_User + 1);
constexpr wchar_t k_logExtension[] = L"log";
constexpr wchar_t k_logFormat[] = L"%Y%m%d";


class CFileMatcher : public wxDirTraverser
{
public:
	CFileMatcher(wxString const& basename, wxArrayString& files)
		: m_ex(wxString::Format(L"%s\\d{8}.%s", basename, k_logExtension))
		, m_files(files)
	{
	}

	wxDirTraverseResult OnFile(const wxString& filename) override
	{
		wxFileName file(filename);
		if (m_ex.Matches(file.GetFullName()))
			m_files.push_back(filename);
		return wxDIR_CONTINUE;
	}

	wxDirTraverseResult OnDir(const wxString& WXUNUSED(dirname)) override
	{
		return wxDIR_CONTINUE;
	}

private:
	wxRegEx m_ex;
	wxArrayString& m_files;

	wxDECLARE_NO_COPY_CLASS(CFileMatcher);
};


// Add the threadid when logging
class CLogFormatter : public wxLogFormatter
{
public:
	using wxLogFormatter::wxLogFormatter;

	wxString Format(wxLogLevel level, const wxString& msg, const wxLogRecordInfo& info) const override
	{
		return wxString::Format(L"%lu %s", info.threadId, wxLogFormatter::Format(level, msg, info));
	}
};

// This is basically what wxLogStream does.
class CLogFile
	: public wxLog
	, private wxMessageOutputWithConv

{
public:
	CLogFile(wxString const& path)
		: wxMessageOutputWithConv(wxMBConvUTF8())
	{
		auto* formatter = SetFormatter(new CLogFormatter);
		delete formatter;

		// ate: seek to end after open
		// app: seek to end before each write
		m_stream.open(path.utf8_str(), std::ios_base::app | std::ios_base::ate | std::ios_base::out);
	}

	virtual ~CLogFile()
	{
		if (m_stream.is_open())
			m_stream.close();
	}

	bool IsOpen() const
	{
		return m_stream.is_open();
	}

	void DoLogText(wxString const& msg) override
	{
		if (m_stream.is_open())
		{
			const wxCharBuffer& buf = PrepareForOutput(msg);
			m_stream.write(buf, buf.length());
			m_stream.flush();
		}
	}

private:
	std::ofstream m_stream;
};
} // namespace


namespace dconSoft
{
namespace ARBWin
{

bool CLogger::IsLoggerEnabled()
{
	return wxLog::GetLogLevel() >= k_defLogLevel;
}


wxLogLevelValues CLogger::GetLogLevel()
{
	return k_defLogLevel;
}


void CLogger::Log(wxString const& msg)
{
	wxLogGeneric(k_defLogLevel, L"%s", msg);
}


CLogger::CLogger()
	: m_logger(nullptr)
	, m_baseFilename()
	, m_currentLogName()
{
	wxLog::SetTimestamp(k_logTimestamp);
}


bool CLogger::Initialize(wchar_t const* baseFilename, bool enableStackLogger)
{
	// Once logging has started, no changes!
	if (m_logger)
	{
		CLogger::Log(L"IGNORED: Cannot reinitialize logging once enabled");
		return true;
	}

	if (enableStackLogger)
		wxLog::SetLogLevel(k_defStackLevel);
	else
		wxLog::SetLogLevel(k_defLogLevel);

	if (baseFilename)
	{
		m_baseFilename = baseFilename;

		auto dir = wxStandardPaths::Get().GetUserLocalDataDir();
		wxFileName name(dir, L"");
		if (!name.DirExists())
		{
			if (!name.Mkdir(wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL))
			{
				wxLogError(L"Failed to create '%s'", name.GetFullPath());
				m_baseFilename.clear();
				return false;
			}
		}
		m_currentLogName.SetPath(dir);
		m_currentLogName.SetName(wxString::Format(L"%s%s", baseFilename, GetTimeStamp()));
		m_currentLogName.SetExt(k_logExtension);
	}
	else
	{
		m_currentLogName.Clear();
		return false;
	}
	return true;
}


bool CLogger::IsEnabled() const
{
	return !!m_logger;
}


void CLogger::EnableLogWindow(
	wxWindow* parent,
	bool show,
	wchar_t const* baseFilename,
	bool enableStackLogger,
	size_t keepNlogs)
{
	if (!m_logger)
	{
		wxString rotateResults;

		if (baseFilename)
		{
			if (!Initialize(baseFilename, enableStackLogger))
				return;

			// Update filename.
			m_currentLogName.SetName(wxString::Format(L"%s%s", baseFilename, GetTimeStamp()));
			rotateResults = RotateLogs(keepNlogs);

			auto* logger = new CLogFile(m_currentLogName.GetFullPath());
			if (logger && !logger->IsOpen())
			{
				wxLogWarning(L"Warning: Unable to open logging with '%s'", m_currentLogName.GetFullPath());
				delete logger;
				m_baseFilename.clear();
				return;
			}

			auto* old = wxLog::SetActiveTarget(logger);
			delete old;
		}

		// Note: m_logger does not need to be cleaned up. wxWidgets auto-hooks
		// this into the logging framework and it is cleaned up there.
		m_logger = new wxLogWindow(parent, _("Logging"), show, !!baseFilename);
		wxLogGeneric(k_defLogLevel, L"%s", L"Starting logging");
		if (!rotateResults.empty())
			wxLogGeneric(k_defLogLevel, L"%s", rotateResults);
	}
}


wxString CLogger::GetCurrentLogDir() const
{
	return m_baseFilename.empty() ? wxString() : m_currentLogName.GetPath();
}


wxString CLogger::GetCurrentLogName() const
{
	return m_baseFilename.empty() ? wxString() : m_currentLogName.GetFullPath();
}


size_t CLogger::FindExistingLogs(wxArrayString& files)
{
	files.clear();

	if (m_baseFilename.empty())
		return 0;

	auto dirname = m_currentLogName.GetPath();
	if (dirname.empty())
		return 0;

	wxDir dir(dirname);
	if (dir.IsOpened())
	{
		CFileMatcher traverser(m_baseFilename, files);
		// We'll further reduce via regex, this does an initial pass using the OS.
		dir.Traverse(traverser, wxString::Format(L"%s*.%s", m_baseFilename, k_logExtension), wxDIR_FILES);
	}
	return files.size();
}


wxFrame* CLogger::GetFrame() const
{
	return m_logger ? m_logger->GetFrame() : nullptr;
}


void CLogger::Show(bool show)
{
	if (m_logger)
		m_logger->Show(show);
}


wxString CLogger::GetTimeStamp() const
{
	auto now = wxDateTime::Now();
	return now.Format(k_logFormat);
}


wxString CLogger::RotateLogs(size_t keepNlogs)
{
	if (0 == keepNlogs)
		return wxString();

	wxArrayString files;
	FindExistingLogs(files);

	// If the existing log exists, ignore it.
	auto logname = m_currentLogName.GetFullPath();
	auto n = files.Index(logname);
	if (0 <= n)
		files.RemoveAt(n);
	if (files.size() < keepNlogs)
		return wxString();

	files.Sort();

	wxString results;
	for (size_t i = 0; i <= files.size() - keepNlogs; ++i)
	{
		if (results.empty())
			results << L"Log Rotation cleanup, preserve " << keepNlogs << L"\n";
		else
			results << L"\n";
		results << L"Removed: " << files[i];
		wxRemoveFile(files[i]);
	}
	return results;
}

/////////////////////////////////////////////////////////////////////////////

int CStackLogger::m_indent = 0;


bool CStackLogger::IsLoggerEnabled()
{
	return wxLog::GetLogLevel() >= k_defStackLevel;
}


wxLogLevelValues CStackLogger::GetLogLevel()
{
	return k_defStackLevel;
}


CStackLogger::CStackLogger(wxString const& msg, bool disableStopWatch)
	: m_msg(msg)
	, m_disableStopWatch(disableStopWatch)
	, m_stopwatch()
	, m_tickle(0)
{
	++m_indent;
	wxLogGeneric(k_defStackLevel, "%*sEnter: %s", m_indent, " ", m_msg);
	if (!m_disableStopWatch)
		m_stopwatch.Start();
}


CStackLogger::~CStackLogger()
{
	if (m_disableStopWatch)
		wxLogGeneric(k_defStackLevel, "%*sLeave: %s", m_indent, " ", m_msg);
	else
	{
		m_stopwatch.Pause();
		wxLogGeneric(k_defStackLevel, "%*sLeave[%ld]: %s", m_indent, " ", m_stopwatch.Time(), m_msg);
	}
	--m_indent;
}


void CStackLogger::Tickle(wxString const& msg)
{
	if (m_disableStopWatch)
		wxLogGeneric(k_defStackLevel, "%*sTickle: %s", m_indent, " ", msg);
	else
	{
		long t = m_stopwatch.Time();
		wxLogGeneric(k_defStackLevel, "%*sTickle[%ld]: %s", m_indent, " ", t - m_tickle, msg);
		m_tickle = t;
	}
}

} // namespace ARBWin
} // namespace dconSoft
