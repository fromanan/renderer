//
// Renderer.cpp : Defines the class behaviors for the application.
//

#include "pch.h"

#include "framework.h"
#include "afxdialogex.h"

#include "Renderer.h"

#include <iostream>

#include "AboutDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CRendererApp

BEGIN_MESSAGE_MAP(CRendererApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CRendererApp::OnAppAbout)
END_MESSAGE_MAP()

// CRendererApp construction

CRendererApp::CRendererApp() noexcept
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
	
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	#ifdef _MANAGED
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
	#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Renderer.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

#ifdef _DEBUG
int CRendererApp::Run()
{
	try {
		return CWinApp::Run();
	} catch (std::exception& exception) {
		std::cout << "Application failed to execute with message: " << exception.what() << std::endl;
		return 1;
	}
}
#endif

// The one and only CRendererApp object
CRendererApp Instance;

// CRendererApp initialization
BOOL CRendererApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX initControls;
	initControls.dwSize = sizeof(initControls);
	
	// Set this to include all the common control classes you want to use
	// in your application.
	initControls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&initControls);

	CWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object
	CFrameWnd* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// create and load the frame with its resources
	#ifdef _DEBUG
	try {
		pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, nullptr, nullptr);
	} catch (std::exception& exception) {
		std::cout << "Failed to load mainframe with message: " << exception.what() << std::endl;
		return FALSE;
	}
	#else
	pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, nullptr, nullptr);
	#endif

	// The one and only window has been initialized, so show and update it
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}

int CRendererApp::ExitInstance()
{
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// App command to run the dialog
void CRendererApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CRendererApp message handlers



