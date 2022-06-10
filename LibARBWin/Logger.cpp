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

#include <wx/log.h>
#include <wx/msgout.h>
#include <wx/stdpaths.h>
#include <fstream>

#if defined(__WXMSW__)
#include <wx/msw/msvcrt.h>
#endif


namespace
{
constexpr wchar_t k_logTimestamp[] = L"%Y-%m-%d %H:%M:%S.%l";
constexpr wxLogLevelValues k_defLogLevel = wxLOG_User;

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
		auto formatter = SetFormatter(new CLogFormatter);
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
	, m_currentLogName()
{
	wxLog::SetTimestamp(k_logTimestamp);
}


void CLogger::EnableLogWindow(wxWindow* parent, bool show, wchar_t const* baseFilename, int keepNlogs)
{
	if (!m_logger)
	{
		if (baseFilename)
		{
			auto dir = wxStandardPaths::Get().GetUserLocalDataDir();
			wxFileName name(dir, L"");
			if (!name.DirExists())
			{
				if (!name.Mkdir(wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL))
				{
					wxLogError(L"Failed to create '%s'", name.GetFullPath());
					return;
				}
			}
			m_currentLogName.SetPath(dir);
			m_currentLogName.SetName(wxString::Format(L"%s%s", baseFilename, GetTimeStamp()));
			m_currentLogName.SetExt(L"log");
			RotateLogs(keepNlogs);

			auto logger = new CLogFile(m_currentLogName.GetFullPath());
			if (logger && !logger->IsOpen())
			{
				delete logger;
				return;
			}

			auto old = wxLog::SetActiveTarget(logger);
			delete old;
		}

		// Note: m_logger does not need to be cleaned up. wxWidgets auto-hooks
		// this into the logging framework and it is cleaned up there.
		m_logger = new wxLogWindow(parent, _("Logging"), show, !!baseFilename);
		wxLogGeneric(k_defLogLevel, L"Starting logging");
	}
}


wxString CLogger::GetCurrentLogDir() const
{
	return m_logger ? m_currentLogName.GetPath() : wxString();
}


wxString CLogger::GetCurrentLogName() const
{
	return m_logger ? m_currentLogName.GetFullPath() : wxString();
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
#pragma PRAGMA_TODO(Add timestamp)
#if 0
	// This can be enabled once we have log rotation.
	// Disabled so we don't fill the disk up.
	auto now = wxDateTime::Now();
	return now.Format(L"%Y%m%d");
#else
	return wxString();
#endif
}


void CLogger::RotateLogs(int keepNlogs)
{
#pragma PRAGMA_TODO(log rotation)
}
