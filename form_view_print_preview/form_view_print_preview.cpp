// form_view_print_preview.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "form_view_print_preview.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "form_view_print_previewDoc.h"
#include "form_view_print_previewView.h"


#include "catalog/QPrntSymDoc.h"
#include "catalog/QPrntSymView.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

// Cform_view_print_previewApp

BEGIN_MESSAGE_MAP(Cform_view_print_previewApp, CBCGPWinApp)
	ON_COMMAND(ID_APP_ABOUT, &Cform_view_print_previewApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CBCGPWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CBCGPWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CBCGPWinApp::OnFilePrintSetup)

	ON_COMMAND(ID_FILE_NEWCATALOG, &Cform_view_print_previewApp::OnFilePrintSymbols)

END_MESSAGE_MAP()


// Cform_view_print_previewApp construction

Cform_view_print_previewApp::Cform_view_print_previewApp()
{

	// Support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;

	CBCGPVisualManagerVS2012::m_bAutoGrayscaleImages = FALSE;

	SetApplicationLookMenu(ID_VIEW_APPLOOK, BCGP_THEMES_LIST_WIN_NATIVE | BCGP_THEMES_LIST_SCENIC | BCGP_THEMES_LIST_OFFICE_2007 | BCGP_THEMES_LIST_OFFICE_2010 | BCGP_THEMES_LIST_VS_2010 | BCGP_THEMES_LIST_OFFICE_2013 | BCGP_THEMES_LIST_VS_2013 | BCGP_THEMES_LIST_OFFICE_2016 | BCGP_THEMES_LIST_VS_2019 | BCGP_THEMES_LIST_OFFICE_2022 | BCGP_THEMES_LIST_VS_2022);

	// Enable VS 2022 look (Blue theme)
	SetVisualTheme(BCGP_VISUAL_THEME_VS_2022_BLUE);

	CBCGPToolbarOptions toolbarOptions;

	toolbarOptions.m_nViewToolbarsMenuEntryID = ID_VIEW_TOOLBARS;
	toolbarOptions.m_nCustomizeCommandID = ID_VIEW_CUSTOMIZE;
	toolbarOptions.m_strCustomizeCommandLabel = _T("Customize...");
	toolbarOptions.m_nUserToolbarCommandIDFirst = uiFirstUserToolBarId;
	toolbarOptions.m_nUserToolbarCommandIDLast = uiLastUserToolBarId;
	toolbarOptions.m_strToolbarCustomIconsPath = _T(".\\UserImages.png");

	SetToolbarOptions(toolbarOptions);

	m_bDPIAwareTooltips = TRUE;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only Cform_view_print_previewApp object

Cform_view_print_previewApp theApp;
CBCGPOccManager theOccManager;


// Cform_view_print_previewApp initialization

BOOL Cform_view_print_previewApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CBCGPWinApp::InitInstance();

	// Remove this line if you don't need themed product dialogs:
	globalData.m_bUseVisualManagerInBuiltInDialogs = TRUE;
	globalData.m_bIsDlgWsCaptionStyle = TRUE;
	globalData.m_bIsMiniFrameWsCaptionStyle = TRUE;
	globalData.m_FrameCornerType = globalData.m_DlgCornerType = globalData.m_PopupMenuCornerType = BCGP_DWMWCP_ROUND;
	globalData.m_MiniFrameCornerType = BCGP_DWMWCP_ROUNDSMALL;
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer(&theOccManager);

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: you should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("BCGP AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)

	SetRegistryBase(_T("Settings"));

	// Initialize all Managers for usage. They are automatically constructed
	// if not yet present
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views

	RegisterDocumentTemplates();



	// create main MDI Frame window
	CMainFrame * pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;
	// call DragAcceptFiles only if there's a suffix
	//  In an MDI app, this should occur immediately after setting m_pMainWnd
	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
	{
		if (!pMainFrame->LoadMDIState(GetRegSectionPath()) ||
			DYNAMIC_DOWNCAST(CMDIChildWnd, pMainFrame->GetActiveFrame()) == NULL)
		{
			if (!ProcessShellCommand(cmdInfo))
				return FALSE;
		}
	}
	else
	{
		// Dispatch commands specified on the command line
		if (!ProcessShellCommand(cmdInfo))
			return FALSE;
	}
	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

// Cform_view_print_previewApp message handlers

int Cform_view_print_previewApp::ExitInstance()
{
	return CBCGPWinApp::ExitInstance();
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CBCGPDialog
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif
	CBCGPURLLinkButton m_btnURL;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CBCGPDialog(IDD_ABOUTBOX)
{
	EnableVisualManagerStyle(TRUE, TRUE);
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMPANY_URL, m_btnURL);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CBCGPDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void Cform_view_print_previewApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}



void Cform_view_print_previewApp::OnFilePrintSymbols()
{
	if (m_pDocTemplatePrntSym != nullptr)
	{
		m_pDocTemplatePrntSym->OpenDocumentFile(NULL);
	}
}


BOOL Cform_view_print_previewApp::RegisterDocumentTemplates()
{

	m_pDocTemplateSxe = new CMultiDocTemplate(IDR_formviewprintpreviewTYPE,
		RUNTIME_CLASS(Cform_view_print_previewDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(Cform_view_print_previewView));
	if (!m_pDocTemplateSxe)
		return FALSE;
	AddDocTemplate(m_pDocTemplateSxe);


	m_pDocTemplatePrntSym = new CMultiDocTemplate(IDR_PRINT_SYMBOL_TYPE,
		RUNTIME_CLASS(QPrntSymDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(QPrntSymView));
	if (!m_pDocTemplatePrntSym)
	{
		return FALSE;
	}

	AddDocTemplate(m_pDocTemplatePrntSym);


}


// Cform_view_print_previewApp message handlers


void Cform_view_print_previewApp::PreLoadState()
{
	GetContextMenuManager()->AddMenu(_T("My menu"), IDR_CONTEXT_MENU);

	// TODO: add another context menus here
}

BOOL Cform_view_print_previewApp::SaveAllModified()
{
	if (!CBCGPWinApp::SaveAllModified())
	{
		return FALSE;
	}

	CBCGPMDIFrameWnd* pMainFrame = DYNAMIC_DOWNCAST(CBCGPMDIFrameWnd, m_pMainWnd);
	if (pMainFrame != NULL)
	{
		pMainFrame->SaveMDIState(GetRegSectionPath());
	}

	return TRUE;
}
