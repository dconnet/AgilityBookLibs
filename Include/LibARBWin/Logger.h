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
#include <wx/log.h>


class ARBWIN_API CLogger
{
	DECLARE_NO_COPY_IMPLEMENTED(CLogger)
public:
	// Default logging level (currently set to wxLOG_User)
	static wxLogLevelValues GetLogLevel();

	static void Log(wxString const& msg);

	CLogger();
	virtual ~CLogger();

	void EnableLogWindow(wxWindow* parent, bool show);

	wxFrame* GetFrame() const;
	void Show(bool show = true);

private:
	wxLogWindow* m_logger;
};
