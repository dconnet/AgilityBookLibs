/*
 * Copyright (c) David Connet. All Rights Reserved.
 */

/**
 * @file
 * @brief About dialog
 * @author David Connet
 *
 * Revision History
 * 2022-08-13 Added 'Copy' button.
 * 2022-01-02 Add wx version to about dlg.
 * 2021-12-10 Change About API: Move CompiledOn to header. Otherwise, time
 *            reflects when the library was compiled.
 * 2018-12-14 Convert to fmt.
 * 2015-08-22 Fix hiDPI issues.
 * 2013-12-14 2.0.0 Standardized History
 * 2010-11-21       Cleaned up wx code (first use)
 * 2009-12-08       Added wxWidget support
 * 1999-04-24       Moved this common code into dconDll.
 */

#include "stdafx.h"
#include "LibARBWin/About.h"

#include "ARBCommon/VersionNum.h"
#include "LibARBWin/ARBDebug.h"
#include "LibARBWin/ARBWinUtilities.h"
#include "LibARBWin/ImageHelperBase.h"
#include "LibARBWin/Logger.h"
#include "LibARBWin/ResourceManager.h"
#include "fmt/xchar.h"

#include <wx/stdpaths.h>

#if defined(__WXMSW__)
#include <wx/msw/msvcrt.h>
#endif


namespace dconSoft
{
using namespace ARBCommon;
namespace ARBWin
{

namespace
{
constexpr int k_mainTextWrap = 200; // Dlg units
constexpr int k_offsetLinks = 10;   // Dlg units
constexpr int k_panelMain = 0;
constexpr int k_panelInfo = 1;
constexpr int k_panelCount = 2;

// For common formatting of items (and getting labels)
// Returns label/text
enum class AboutText
{
	ProdName,
	Copyright,
	ProdDesc,
	Version,
	CompiledOn,
	AppDir,
	UserDir,
	wxWidgets,
	Scaling,
	OS,
};


class CDlgAbout : public wxDialog
{
public:
	CDlgAbout(AboutInfo const& aboutInfo, wxWindow* inParent, wxString const* inCaption);

	std::pair<wxString, wxString> GetAboutText(AboutText text) const;

private:
	wxString GetAboutData() const;

	AboutInfo m_aboutInfo;
};

/////////////////////////////////////////////////////////////////////////////

class CAboutMain : public wxPanel
{
public:
	CAboutMain(CDlgAbout* dlg, wxWindow* parent, AboutInfo const& aboutInfo);
};


CAboutMain::CAboutMain(CDlgAbout* dlg, wxWindow* parent, AboutInfo const& aboutInfo)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL)
{
	// Controls (these are done first to control tab order)

	auto info = dlg->GetAboutText(AboutText::ProdName);
	wxStaticText* textName = nullptr;
	if (!info.second.empty())
		textName = new wxStaticText(this, wxID_ANY, info.second, wxDefaultPosition, wxDefaultSize);

	info = dlg->GetAboutText(AboutText::Copyright);
	wxStaticText* textCopyright = nullptr;
	if (!info.second.empty())
	{
		textCopyright = new wxStaticText(this, wxID_ANY, info.second, wxDefaultPosition, wxDefaultSize);
		textCopyright->Wrap(wxDLG_UNIT_X(this, k_mainTextWrap));
	}

	info = dlg->GetAboutText(AboutText::ProdDesc);
	wxStaticText* textDesc = nullptr;
	if (!info.second.empty())
	{
		textDesc = new wxStaticText(this, wxID_ANY, info.second, wxDefaultPosition, wxDefaultSize);
		textDesc->Wrap(wxDLG_UNIT_X(this, k_mainTextWrap));
	}

	std::vector<std::pair<wxWindow*, bool>> links;
	for (auto link : aboutInfo.links)
	{
		if (link.desc.empty() && link.url.empty())
		{
			links.push_back(std::make_pair(nullptr, false));
			continue;
		}
		if (!link.desc.empty() && link.url.empty())
		{
			auto ctrl = new wxStaticText(this, wxID_ANY, link.desc, wxDefaultPosition, wxDefaultSize);
			links.push_back(std::make_pair(ctrl, link.offset));
		}
		else
		{
			bool setTip = true;
			wxString desc = link.desc;
			wxString url = link.url;
			// If either are empty, set both the same.
			if (desc.empty())
			{
				setTip = false;
				desc = url;
			}
			auto ctrlLink
				= new wxHyperlinkCtrl(this, wxID_ANY, desc, url, wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE);
			if (setTip)
				ctrlLink->SetToolTip(url);
			links.push_back(std::make_pair(ctrlLink, link.offset));
		}
	}

	// Sizers

	wxBoxSizer* bSizer = new wxBoxSizer(wxVERTICAL);

	if (textName)
		bSizer->Add(textName, 0, wxLEFT | wxRIGHT | wxTOP | wxEXPAND, wxDLG_UNIT_X(this, 3));
	if (textCopyright)
		bSizer->Add(textCopyright, 0, wxLEFT | wxRIGHT | wxTOP | wxEXPAND, wxDLG_UNIT_X(this, 3));
	if (textDesc)
		bSizer->Add(textDesc, 0, wxLEFT | wxRIGHT | wxTOP | wxEXPAND, wxDLG_UNIT_X(this, 3));
	if (!links.empty())
	{
		bool bReset = false;
		int flags = wxLEFT | wxRIGHT | wxEXPAND;
		for (auto link : links)
		{
			if (!link.first)
			{
				bReset = true;
				flags |= wxTOP;
				continue;
			}
			wxBoxSizer* sizerLinks = bSizer;
			if (link.second)
			{
				sizerLinks = new wxBoxSizer(wxHORIZONTAL);
				sizerLinks->Add(wxDLG_UNIT_X(this, k_offsetLinks), 0, 0, wxEXPAND, 0);
				bSizer->Add(sizerLinks);
			}
			sizerLinks->Add(link.first, 0, flags, wxDLG_UNIT_X(this, 3));
			if (bReset)
				flags &= ~wxTOP;
		}
	}

	SetSizer(bSizer);
	Layout();
	GetSizer()->Fit(this);
}

/////////////////////////////////////////////////////////////////////////////

class CAboutInfo : public wxPanel
{
public:
	CAboutInfo(CDlgAbout* dlg, wxWindow* parent, AboutInfo const& aboutInfo);
};


CAboutInfo::CAboutInfo(CDlgAbout* dlg, wxWindow* parent, AboutInfo const& aboutInfo)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL)
{
	// Controls (these are done first to control tab order)

	auto info = dlg->GetAboutText(AboutText::Version);
	wxStaticText* textVersion = new wxStaticText(this, wxID_ANY, info.first, wxDefaultPosition, wxDefaultSize);
	wxStaticText* ctrlVersion = new wxStaticText(this, wxID_ANY, info.second, wxDefaultPosition, wxDefaultSize);

	info = dlg->GetAboutText(AboutText::CompiledOn);
	wxStaticText* textBuildDate = nullptr;
	wxStaticText* ctrlBuildDate = nullptr;
	if (!info.second.empty())
	{
		textBuildDate = new wxStaticText(this, wxID_ANY, info.first, wxDefaultPosition, wxDefaultSize);
		ctrlBuildDate = new wxStaticText(this, wxID_ANY, info.second, wxDefaultPosition, wxDefaultSize);
	}

	info = dlg->GetAboutText(AboutText::AppDir);
	wxStaticText* textAppDir = new wxStaticText(this, wxID_ANY, info.first, wxDefaultPosition, wxDefaultSize);
	wxStaticText* ctrlAppDir = new wxStaticText(this, wxID_ANY, info.second, wxDefaultPosition, wxDefaultSize);

	info = dlg->GetAboutText(AboutText::UserDir);
	wxStaticText* textUserDir = nullptr;
	wxStaticText* ctrlUserDir = nullptr;
	wxBitmapButton* ctrlOpen = nullptr;
	if (!aboutInfo.userDir.empty())
	{
		wxString dir = info.second;
		textUserDir = new wxStaticText(this, wxID_ANY, info.first, wxDefaultPosition, wxDefaultSize);
		ctrlUserDir = new wxStaticText(this, wxID_ANY, info.second, wxDefaultPosition, wxDefaultSize);
		ctrlOpen = new wxBitmapButton(
			this,
			wxID_ANY,
			CResourceManager::Get()
				->GetBitmap(ImageMgrFolderOpened, wxART_TOOLBAR, wxSize(parent->FromDIP(16), parent->FromDIP(16))));
		ctrlOpen->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [dir](wxCommandEvent& evt) { wxLaunchDefaultApplication(dir); });
	}

	info = dlg->GetAboutText(AboutText::wxWidgets);
	wxStaticText* textVersionWx = new wxStaticText(this, wxID_ANY, info.first, wxDefaultPosition, wxDefaultSize);
	wxStaticText* ctrlVersionWx = new wxStaticText(this, wxID_ANY, info.second, wxDefaultPosition, wxDefaultSize);

	info = dlg->GetAboutText(AboutText::Scaling);
	wxStaticText* textDPI = new wxStaticText(this, wxID_ANY, info.first, wxDefaultPosition, wxDefaultSize);
	wxStaticText* ctrlDPI = new wxStaticText(this, wxID_ANY, info.second, wxDefaultPosition, wxDefaultSize);

	info = dlg->GetAboutText(AboutText::OS);
	wxStaticText* textOS = new wxStaticText(this, wxID_ANY, info.first, wxDefaultPosition, wxDefaultSize);
	wxStaticText* ctrlOS = new wxStaticText(this, wxID_ANY, info.second, wxDefaultPosition, wxDefaultSize);

	// Sizers

	wxBoxSizer* bSizer = new wxBoxSizer(wxVERTICAL);

	auto sizerGrid = new wxFlexGridSizer(7, 2, wxDLG_UNIT_X(this, 3), wxDLG_UNIT_X(this, 3)); // rows/cols/vgap/hgap
	sizerGrid->SetFlexibleDirection(wxBOTH);
	sizerGrid->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
	sizerGrid->Add(textVersion, 0, wxALIGN_CENTER_VERTICAL);
	sizerGrid->Add(ctrlVersion, 0, wxALIGN_CENTER_VERTICAL);

	if (!aboutInfo.compiledOn.empty())
	{
		sizerGrid->Add(textBuildDate, 0, wxALIGN_CENTER_VERTICAL);
		sizerGrid->Add(ctrlBuildDate, 0, wxALIGN_CENTER_VERTICAL);
	}

	sizerGrid->Add(textAppDir, 0, wxALIGN_CENTER_VERTICAL);
	sizerGrid->Add(ctrlAppDir, 0, wxALIGN_CENTER_VERTICAL);

	if (!aboutInfo.userDir.empty())
	{
		wxBoxSizer* sizerDir = new wxBoxSizer(wxHORIZONTAL);
		sizerGrid->Add(textUserDir, 0, wxALIGN_CENTER_VERTICAL);
		sizerDir->Add(ctrlUserDir, 1, wxALIGN_CENTER_VERTICAL);
		sizerDir->Add(ctrlOpen, 0, wxLEFT | wxALIGN_CENTER_VERTICAL, wxDLG_UNIT_X(this, 3));
		sizerGrid->Add(sizerDir);
	}

	sizerGrid->Add(textVersionWx, 0, wxALIGN_CENTER_VERTICAL);
	sizerGrid->Add(ctrlVersionWx, 0, wxALIGN_CENTER_VERTICAL);

	sizerGrid->Add(textDPI, 0, wxALIGN_CENTER_VERTICAL);
	sizerGrid->Add(ctrlDPI, 0, wxALIGN_CENTER_VERTICAL);

	sizerGrid->Add(textOS, 0, wxALIGN_CENTER_VERTICAL);
	sizerGrid->Add(ctrlOS, 0, wxALIGN_CENTER_VERTICAL);

	bSizer->Add(sizerGrid, 0, wxALL, wxDLG_UNIT_X(this, 3));

	SetSizer(bSizer);
	Layout();
	GetSizer()->Fit(this);
}

/////////////////////////////////////////////////////////////////////////////

CDlgAbout::CDlgAbout(AboutInfo const& aboutInfo, wxWindow* inParent, wxString const* inCaption)
	: wxDialog()
	, m_aboutInfo(aboutInfo)
{
	std::vector<wxPanel*> panels;
	panels.resize(k_panelCount);

	wxString caption;
	if (inCaption)
		caption = *inCaption;
	else
		caption = _("About...");

	Create(inParent, wxID_ANY, caption, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE);

	// Controls (these are done first to control tab order)

	wxStaticBitmap* icon = nullptr;
	if (aboutInfo.image.IsOk())
		icon = new wxStaticBitmap(this, wxID_ANY, aboutInfo.image, wxDefaultPosition, wxDefaultSize, 0);

	wxStaticText* debug = nullptr;
#if defined(_DEBUG) || defined(__WXDEBUG__)
	debug = new wxStaticText(this, wxID_ANY, _("Debug"), wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER);
#endif

	wxNotebook* notebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

	auto panelMain = new CAboutMain(this, notebook, aboutInfo);
	panels[k_panelMain] = panelMain;
	notebook->AddPage(panelMain, _("About"), true);

	auto panelInfo = new CAboutInfo(this, notebook, aboutInfo);
	panels[k_panelInfo] = panelInfo;
	notebook->AddPage(panelInfo, _("Information"), true);

	notebook->ChangeSelection(k_panelMain);
	panels[k_panelMain]->SetFocus();

	auto ctrlCopy = new wxButton(this, wxID_ANY, _("Copy"));
	ctrlCopy->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this](wxCommandEvent& evt) {
		auto data = GetAboutData();
		if (!data.empty() && wxTheClipboard && wxTheClipboard->Open())
		{
			auto dataObj = new wxTextDataObject(data);
			dataObj->SetFormat(wxDataFormat(wxDF_UNICODETEXT));
			if (!wxTheClipboard->SetData(dataObj))
				delete dataObj;
			wxTheClipboard->Flush();
			wxTheClipboard->Close();
		}
	});
	ctrlCopy->Enable(!GetAboutData().empty());

	auto ctrlOk = new wxButton(this, wxID_ANY, _("Close"));
	ctrlOk->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this](wxCommandEvent& evt) { EndDialog(wxID_OK); });

	// Sizers

	wxBoxSizer* bSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* sizerMain = new wxBoxSizer(wxHORIZONTAL);

	if (icon || debug)
	{
		wxBoxSizer* sizerIcons = new wxBoxSizer(wxVERTICAL);
		if (icon)
		{
			sizerIcons->Add(0, 0, 1, wxEXPAND, 0);
			sizerIcons->Add(icon, 0, wxALL, wxDLG_UNIT_X(this, 3));
			sizerIcons->Add(0, 0, 1, wxEXPAND, 0);
		}
		if (debug)
		{
			sizerIcons->Add(debug, 0, wxALL, wxDLG_UNIT_X(this, 3));
		}
		sizerMain->Add(sizerIcons, 0, wxEXPAND, 0);
	}

	// Instead of using CreateStdDialogButtonSizer, create buttons directly.
	wxSizer* sdbSizer = new wxBoxSizer(wxHORIZONTAL);
	sdbSizer->Add(ctrlCopy);
	sdbSizer->AddStretchSpacer(1);
	sdbSizer->Add(ctrlOk);

	wxBoxSizer* sizerPanels = new wxBoxSizer(wxVERTICAL);
	sizerPanels->Add(notebook, 1, wxALL | wxEXPAND, wxDLG_UNIT_X(this, 3));
	sizerPanels->Add(sdbSizer, 0, wxALL | wxEXPAND, wxDLG_UNIT_X(this, 3));
	sizerMain->Add(sizerPanels);

	bSizer->Add(sizerMain);

	SetSizer(bSizer);
	Layout();
	GetSizer()->Fit(this);
	SetSizeHints(GetSize(), wxDefaultSize);
	CenterOnParent();

	IMPLEMENT_ON_INIT(CDlgAbout, ctrlOk)
}


std::pair<wxString, wxString> CDlgAbout::GetAboutText(AboutText text) const
{
	wxString label, content;
	switch (text)
	{
	case AboutText::ProdName:
		if (!m_aboutInfo.productName.empty())
		{
			content = m_aboutInfo.productName;
		}
		break;
	case AboutText::Copyright:
		if (!m_aboutInfo.copyright.empty())
		{
			content = m_aboutInfo.copyright;
		}
		break;
	case AboutText::ProdDesc:
		if (!m_aboutInfo.productDesc.empty())
		{
			content = m_aboutInfo.productDesc;
		}
		break;
	case AboutText::Version:
		if (!m_aboutInfo.version.empty())
		{
			label = _("Version");
			content = m_aboutInfo.version;
#ifdef ARB_64BIT
			content << L" " << _("(64-bit)");
#else
			content << L" " << _("(32-bit)");
#endif
		}
		break;
	case AboutText::CompiledOn:
		if (!m_aboutInfo.compiledOn.empty())
		{
			label = _("Build date");
			content = m_aboutInfo.compiledOn;
		}
		break;
	case AboutText::AppDir:
		label = _("Appplication directory");
		{
			wxFileName exe(wxStandardPaths::Get().GetExecutablePath());
			content = exe.GetPath();
		}
		break;
	case AboutText::UserDir:
		if (!m_aboutInfo.userDir.empty())
		{
			label = _("User data directory");
			content = m_aboutInfo.userDir;
		}
		break;
	case AboutText::wxWidgets:
		label = L"wxWidgets";
		content = wxString::Format(
			"%d.%d.%d.%d",
			wxGetLibraryVersionInfo().GetMajor(),
			wxGetLibraryVersionInfo().GetMinor(),
			wxGetLibraryVersionInfo().GetMicro(),
			wxGetLibraryVersionInfo().GetRevision());
		break;
	case AboutText::Scaling:
		label = _("DPI scaling");
		content = fmt::format(L"{}", GetDPIScaleFactor());
		break;
	case AboutText::OS:
		label = _("OS");
		content
			= fmt::format(L"{}, {}, {}", ARBDebug::GetOSName(), ARBDebug::GetArchName(), ARBDebug::GetEndiannessName());
		break;
	}
	return std::make_pair(label, content);
}


wxString CDlgAbout::GetAboutData() const
{
	wxString data;

	auto info = GetAboutText(AboutText::ProdName);
	if (!info.second.empty())
		data << info.second << L"\n";
	info = GetAboutText(AboutText::Copyright);
	if (!info.second.empty())
		data << info.second << L"\n";
	info = GetAboutText(AboutText::ProdDesc);
	if (!info.second.empty())
		data << info.second << L"\n";

	if (!m_aboutInfo.links.empty())
		data << L"\n";
	for (auto const& link : m_aboutInfo.links)
	{
		if (link.desc.empty() && link.url.empty())
			continue;
		if (!link.desc.empty())
			data << link.desc << L"\n";
		if (!link.url.empty())
		{
			if (!link.desc.empty())
				data << L"   ";
			data << link.url << L"\n";
		}
	}
	if (!m_aboutInfo.links.empty())
		data << L"\n";

	info = GetAboutText(AboutText::Version);
	if (!info.first.empty())
		data << info.first << L": " << info.second << L"\n";
	info = GetAboutText(AboutText::CompiledOn);
	if (!info.first.empty())
		data << info.first << L": " << info.second << L"\n";
	info = GetAboutText(AboutText::AppDir);
	if (!info.first.empty())
		data << info.first << L": " << info.second << L"\n";
	info = GetAboutText(AboutText::UserDir);
	if (!info.first.empty())
		data << info.first << L": " << info.second << L"\n";
	info = GetAboutText(AboutText::wxWidgets);
	if (!info.first.empty())
		data << info.first << L": " << info.second << L"\n";
	info = GetAboutText(AboutText::Scaling);
	if (!info.first.empty())
		data << info.first << L": " << info.second << L"\n";
	info = GetAboutText(AboutText::OS);
	if (!info.first.empty())
		data << info.first << L": " << info.second << L"\n";

	return data;
}

} // namespace

/////////////////////////////////////////////////////////////////////////////

#if defined(_WIN32) && 0
void About(HMODULE inInst, wxIcon inIcon, wxWindow* inParent, wxString const& inCaption)
{
	CLogger::Log("DIALOG: CDlgAbout (win32)");

	AboutInfo aboutInfo;
	aboutInfo.compiledOn.clear(); // Don't want library compiled-on, so just clear.

	IVersionInfoPtr pVersion = IVersionInfo::Create(inInst);
	if (pVersion)
	{
		// Get the product name strings.
		aboutInfo.productName = pVersion->GetProductName();

		// Get the product version string.
		VERSIONNUM ver;
		pVersion->GetProductVersionNumber(ver);
		aboutInfo.version << ver.part1 << L"." << ver.part2 << L"." << ver.part3 << L"." << ver.part4;

		// Get the legal copyright string.
		aboutInfo.copyright = pVersion->GetLegalCopyright();
	}
	CDlgAbout dlg(inIcon, aboutInfo, inParent, &inCaption);
	dlg.ShowModal();
}
#endif

AboutInfo::AboutInfo()
{
}


void AboutInfo::SetImage(wxWindow* inParent, wxArtID const& artId, int defaultSize)
{
	auto manager = CResourceManager::Get();
	if (manager && inParent)
	{
		auto size = inParent->FromDIP(defaultSize);
		if (defaultSize == 32)
			image = manager->GetBitmap(artId, wxART_MESSAGE_BOX, wxSize(size, size));
		else
			image = manager->GetBitmap(artId, wxART_OTHER, wxSize(size, size));
	}
}


void About(AboutInfo const& aboutInfo, wxWindow* inParent, wxString const* inCaption)
{
	CLogger::Log("DIALOG: CDlgAbout");

	CDlgAbout dlg(aboutInfo, inParent, inCaption);
	dlg.ShowModal();
}

} // namespace ARBWin
} // namespace dconSoft
