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
#include <wx/stdpaths.h>

#if defined(__WXMSW__)
#include <wx/msw/msvcrt.h>
#endif


namespace
{
constexpr wchar_t k_logTimestamp[] = L"%Y-%m-%d %H:%M:%S.%l";
constexpr wxLogLevelValues k_defLogLevel = wxLOG_User;
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
{
	wxLog::SetTimestamp(k_logTimestamp);
}


CLogger::~CLogger()
{
}


void CLogger::EnableLogWindow(wxWindow* parent, bool show)
{
	if (!m_logger)
	{
#pragma PRAGMA_TODO(Add ability to log to a file at same time)
		// Do this be setting the default logger to a file-writer and then
		// change the passToOld to true

		// Note: m_logger does not need to be cleaned up. wxWidgets auto-hooks
		// this into the logging framework and it is cleaned up there.
		m_logger = new wxLogWindow(parent, _("Logging"), show, false);
		wxLogGeneric(k_defLogLevel, L"Starting logging");
	}
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
