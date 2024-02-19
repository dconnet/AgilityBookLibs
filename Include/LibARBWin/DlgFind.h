#pragma once
#pragma once

/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief interface of the CDlgFind class
 * @author David Connet
 *
 * Revision History
 * 2024-02-19 Added more options, made more configurable, moved to ARBWin
 * 2009-01-26 Ported to wxWidgets.
 * 2003-12-27 Created
 */

#include "LibwxARBWin.h"

#include "LibARBWin/Logger.h"
#include <list>

class wxGrid;


namespace dconSoft
{
namespace ARBWin
{
class CDlgFind;
class CReportListCtrl;
class CTextCtrl;


class ARBWIN_API CFindCallback
{
	DECLARE_NO_COPY_IMPLEMENTED(CFindCallback)
public:
	enum class Feature
	{
		Normal,
		Disabled,
		Hidden,
	};

	CFindCallback() = default;
	virtual ~CFindCallback() = default;

	// Caption for Find dialog
	wxString const& GetCaption() const
	{
		return m_caption;
	}

	// Search text from dialog
	wxString const& Text() const
	{
		return m_search;
	}
	void Text(wxString const& text)
	{
		m_search = text;
	}

	// Match case
	bool MatchCase() const
	{
		return m_matchCase;
	}
	void MatchCase(bool value)
	{
		m_matchCase = value;
	}

	// Match word not yet implemented
	Feature IsMatchWordEnabled() const
	{
		return m_enableMatchWord;
	}
	bool MatchWord() const
	{
		return m_matchWord;
	}
	void MatchWord(bool value)
	{
		m_matchWord = value;
	}

	// Regex not yet implemented
	Feature IsRegexEnabled() const
	{
		return m_enableRegex;
	}
	bool Regex() const
	{
		return m_isRegex;
	}
	void Regex(bool value)
	{
		m_isRegex = value;
	}

	// By default, wrap is hidden. It must be implemented in Search()
	Feature IsWrapEnabled() const
	{
		return m_enableWrap;
	}
	bool Wrap() const
	{
		return m_wrap;
	}
	void Wrap(bool value)
	{
		m_wrap = value;
	}

	// Search all/visible is enabled. Derived class controls this flag.
	Feature IsSearchAllEnabled() const
	{
		return m_enableSearchAll;
	}
	bool SearchAll() const
	{
		return m_searchAll;
	}
	void SearchAll(bool value)
	{
		m_searchAll = value;
	}

	// Search direction is enabled. Derived class controls this flag.
	Feature IsDirectionEnabled() const
	{
		return m_enableDirection;
	}
	bool SearchDown() const
	{
		return m_down;
	}
	void SearchDown(bool value)
	{
		m_down = value;
	}

	// If pDlg is null, this is a find-next/prev (no dialog present)
	virtual bool Search(CDlgFind* pDlg) = 0;
	void AddSearchTerm(wxString const& value);

protected:
	bool Compare(wxString const& value) const;

	wxString m_caption;
	wxString m_search;
	std::list<wxString> m_previousSearch; // MRU
	bool m_matchCase{false};
	Feature m_enableMatchWord{Feature::Hidden};
	bool m_matchWord{false};
	Feature m_enableRegex{Feature::Hidden};
	bool m_isRegex{false};
	Feature m_enableWrap{Feature::Hidden};
	bool m_wrap{false};
	Feature m_enableSearchAll{Feature::Normal};
	bool m_searchAll{true};
	Feature m_enableDirection{Feature::Normal};
	bool m_down{true};
};

/////////////////////////////////////////////////////////////////////////////

class ARBWIN_API CFindDataBase : public ARBWin::CFindCallback
{
public:
	CFindDataBase();

protected:
	virtual int GetCount() const = 0;
	virtual int GetSelection() const = 0;
	int GetCurrent() const;
	int GetNext(int sel) const;
	void NotFound() const;
};

/////////////////////////////////////////////////////////////////////////////

class ARBWIN_API CFindDataList : public CFindDataBase
{
public:
	CFindDataList() = default;

protected:
	int GetCount() const override;
	int GetSelection() const override;

	// Set in Search()
	CReportListCtrl* m_list{nullptr};
};

/////////////////////////////////////////////////////////////////////////////

class ARBWIN_API CFindDataGrid : public CFindDataBase
{
public:
	CFindDataGrid() = default;

protected:
	int GetCount() const override;
	int GetSelection() const override;

	// Set in Search()
	wxGrid* m_grid{nullptr};
	int m_count{0};
};

/////////////////////////////////////////////////////////////////////////////

class ARBWIN_API CDlgFind : public wxDialog
{
public:
	CDlgFind(CFindCallback& callback, wxWindow* pParent = nullptr);

private:
	CFindCallback& m_Callback;
	CTextCtrl* m_textCtrl{nullptr};
	wxCheckBox* m_ctrlMatchCase{nullptr};
	wxCheckBox* m_ctrlMatchWord{nullptr};
	wxCheckBox* m_ctrlRegex{nullptr};
	wxCheckBox* m_ctrlWrap{nullptr};
	wxRadioBox* m_radioBoxSearch{nullptr};
	wxRadioBox* m_radioBoxDir{nullptr};
	wxButton* m_btnFind{nullptr};
	CStackLogger m_trace;
};

} // namespace ARBWin
} // namespace dconSoft
