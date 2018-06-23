// KuvempuDlg.cpp : implementation file
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////AUTHOR : Sudheer HS	sudheer316@gmail.com////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////DATE : 6-apr-2006							////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////COMPANY : Maruthi Software Developers.,HASSAN - 573201 ,KARANATAKA, INDIA     ////////////////////////////////////////////////////////////////
////////////////Compiler Used : Microsoft Visual C++ 6.0////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	////////////////////////////////////////////////////////////////	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////  This has been done as a project for Hampi University ,Hampi,INDIA ////////////////////////////////////////////////////////////////
////////////////  this is part of the free software Kuvempu Kannada Thantramsha,launched by Hampi University ////////////////////////////////////////////////////////////////
////////////////  This code as is with out any kind of warranty ,Using or modifing the code or the library without ////////////////////////////////////////////////////////////////
////////////////  the written permission by the university is prohibited,Any such illegal activities is punishable offence as per ////////////////////////////////////////////////////////////////
////////////////  the copy rights ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
*
*Modified Added New chars pha ph with dots
*Date 11/03/2009 1:44 AM
*Author Sudheer HS 
*/

/*
*
*Modified Added New chars pha ph with dots
*Date 11/03/2009 1:44 AM
*Author Sudheer HS 
*/
#include <windows.h>
#include <shellapi.h>
#include <io.h>
#include <process.h>    /* _beginthread, _endthread */
#include <stddef.h>
#include <stdlib.h>

#include "stdafx.h"
#include "Kuvempu.h"
#include "KuvempuDlg.h"
#include "sinstance.h"
#include "HemavathiHelp.h"
#include "SharavathiHelp.h"
#include "NetravathiHelp.h"
#include "CauveryHelp.h"
#include "TungaHelp.h"

#include "AlreadyExist.h"

#include <afxpriv.h>
#include <stdio.h>
#include <windows.h>

#include "..\Hemavathi\hemavathi.h"
#include "..\Netravathi\netravathi.h"
#include "..\Sharavathi\sharavathi.h"
#include "..\Cauvery\cauvery.h"
#include "..\Tunga\tunga.h"

#define WIN32_LEAN_AND_MEAN


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



	int hookID = 0;
	static int ALLOWDUPLICATE = 0;
	static int WIN_NT_NO_TRAY = 0;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
CSystemTray	m_TrayIcon;


void isWinNTServer()
{
    OSVERSIONINFO osvi;
    BOOL bIsWindowsNTServer;

    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    GetVersionEx(&osvi);

    bIsWindowsNTServer  = 
       ( (osvi.dwMajorVersion == 4) );

    if(bIsWindowsNTServer)
	{
       ALLOWDUPLICATE = TRUE;
	   WIN_NT_NO_TRAY = TRUE;
	}

}
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKuvempuDlg dialog

CKuvempuDlg::CKuvempuDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKuvempuDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKuvempuDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
void CKuvempuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKuvempuDlg)
			DDX_Control(pDX, IDC_STATIC_NETRAVATHI, m_ButtonNetravathi);
			DDX_Control(pDX, IDC_STATIC_SHARAVATHI, m_ButtonSharavathi);
			DDX_Control(pDX, IDC_STATIC_HEMAVATHI, m_ButtonHemavathi);
			DDX_Control(pDX, IDC_STATIC_CAUVERY, m_ButtonCauvery);
			DDX_Control(pDX, IDC_STATIC_TUNGA, m_ButtonTunga);

			//DDX_Control(pDX, IDC_STATIC_SHARAVATHI,m_CheckNetravathi);
		
			//DDX_Control(pDX, IDC_STATIC_SYSTEMTRAY, m_ButtonSystemTray);
			DDX_Control(pDX, IDC_STATIC_CONVERTER, m_ButtonConverter);
			DDX_Control(pDX, IDC_STATIC_CLOSE, m_ButtonClose);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CKuvempuDlg, CDialog)
	//{{AFX_MSG_MAP(CKuvempuDlg)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CANCELMODE()
	ON_WM_SYSCOMMAND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_STATIC_HEMAVATHI,OnHemavathi)
	ON_BN_CLICKED(IDC_STATIC_SHARAVATHI,OnSharavathi)
	ON_BN_CLICKED(IDC_STATIC_NETRAVATHI,OnNetravathi)
	ON_BN_CLICKED(IDC_STATIC_CAUVERY,OnCauvery)
	ON_BN_CLICKED(IDC_STATIC_CONVERTER,OnConverter)
	ON_BN_CLICKED(IDC_STATIC_CLOSE,OnClose)
	ON_BN_CLICKED(IDD_HEMAVATHI_HELP, OnHemavathiHelp)
	ON_BN_CLICKED(IDD_NETRAVATHI_HELP, OnNetravathiHelp)
	ON_BN_CLICKED(IDD_CAUVERY_HELP, OnCauveryHelp)
	ON_BN_CLICKED(IDC_SHARAVATHI_HELP, OnSharavathiHelp)
	ON_COMMAND(ID_TRAYMENU_ITEM1, OnHemavathi)
	ON_COMMAND(ID_TRAYMENU_ITEM2, OnSharavathi)
	ON_COMMAND(ID_TRAYMENU_ITEM3, OnNetravathi)
	ON_COMMAND(ID_TRAYMENU_ITEM4, OnCauvery)
	ON_COMMAND(ID_TRAYMENU_ITEM5, OnTunga)
	ON_COMMAND(ID_TRAYMENU_ITEM6, OnConverter)
	ON_BN_CLICKED(IDD_SHARAVATHI_HELP, OnSharavathiHelp)
	ON_BN_CLICKED(IDC_STATIC_TUNGA, OnTunga)
	ON_BN_CLICKED(IDD_TUNGA_HELP, OnTungaHelp)
	//}}AFX_MSG_MAP

	ON_WM_INITMENUPOPUP()

	//ON_COMMAND(ID_TRAYMENU_ITEM6, OnKuvempu_Kannada)

//	ON_COMMAND(ID_TRAYMENU_ITEM7, OnHelp_Kuvempu)
	ON_COMMAND(ID_TRAYMENU_ITEM10,OnClose)
	ON_COMMAND(ID_TRAYMENU_ITEM9, OnOpen)
	ON_COMMAND(ID_TRAYMENU_ITEM11, OnAbout)
	
	ON_UPDATE_COMMAND_UI(ID_TRAYMENU_ITEM1,OnUPdateHemavathi)
	ON_UPDATE_COMMAND_UI(ID_TRAYMENU_ITEM2,OnUPdateSharavathi)
	ON_UPDATE_COMMAND_UI(ID_TRAYMENU_ITEM3,OnUPdateNetravathi)
	ON_UPDATE_COMMAND_UI(ID_TRAYMENU_ITEM4,OnUPdateCauvery)
	ON_UPDATE_COMMAND_UI(ID_TRAYMENU_ITEM5,OnUPdateTunga)

	//ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
	
	ON_MESSAGE(WM_TRAYNOTIFY, OnTrayNotify)

//	ON_UPDATE_COMMAND_UI(ID_TRAYMENU_ITEM3, OnUpdateCheck)
END_MESSAGE_MAP()

BOOL CKuvempuDlg::OnInitDialog()
{
//	CheckForInstance();
isWinNTServer();
	//	AfxMessageBox(_T("Already running ,will be restored"), MB_OK);
	  
  CInstanceChecker instanceChecker;
  if (instanceChecker.PreviousInstanceRunning())
  {
//	AfxMessageBox(_T("Already running ,will be restored"), MB_OK);
	  if(!ALLOWDUPLICATE)
	  {
		AlreadyExist Alreist;
		Alreist.DoModal();
		//instanceChecker.ActivatePreviousInstance();
		_exit(1);
	  }
	  else
	  {
		  //this->ShowWindow(SW_RESTORE);
		  //_exit(1);

		  instanceChecker.ActivatePreviousInstance();
	//  	  if(isTraySet && !WIN_NT_NO_TRAY)
	//	  {
			  //OnOpen();
	//		  AlreadyExist Alreist;
	//		  Alreist.DoModal();
	//	  }
		  _exit(1);//return FALSE;
	  }
  }


	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

   // Use the font to paint a control. This code assumes
   // a control named IDC_TEXT1 in the dialog box.


//	VERIFY(m_ButtonHemavathi1.AutoLoad(IDC_Button,this));

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	

	//SET THE TRAY
	HICON	hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Icon = hIcon;



	isTraySet = FALSE;


	EnableToolTips(TRUE);

//	m_fntTitle.CreateFont(18,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_ROMAN,"Times New Roman");

	// TODO: Add extra initialization here
   	m_ButtonNetravathi.LoadButtonBitmaps(	BUTTON_NETRAVATHI_UP,
											BUTTON_NETRAVATHI_NORM, 
											BUTTON_NETRAVATHI_DOWN);

	m_ButtonSharavathi.LoadButtonBitmaps(	BUTTON_SHARAVATHI_UP,
											BUTTON_SHARAVATHI_NORM,
											BUTTON_SHARAVATHI_DOWN);

	m_ButtonHemavathi.LoadButtonBitmaps(	BUTTON_HEMAVATHI_UP,
											BUTTON_HEMAVATHI_NORM,
                                            BUTTON_HEMAVATHI_DOWN
											);

	m_ButtonCauvery.LoadButtonBitmaps(		BUTTON_CAUVERY_UP,
											BUTTON_CAUVERY_NORM,
											BUTTON_CAUVERY_DOWN);

	m_ButtonTunga.LoadButtonBitmaps(	BUTTON_TUNGA_UP,
											BUTTON_TUNGA_NORM,
                                            BUTTON_TUNGA_DOWN
											);



	//m_ButtonSystemTray.LoadButtonBitmaps(	BUTTON_SYSTEMTRAY_UP,\
											BUTTON_SYSTEMTRAY_DOWN,\
											BUTTON_SYSTEMTRAY_NORM);

	m_ButtonConverter.LoadButtonBitmaps(
											BUTTON_CONVERTER_UP,
											BUTTON_CONVERTER_DOWN,
											BUTTON_CONVERTER_NORM);
	
	m_ButtonClose.LoadButtonBitmaps(	
											BUTTON_CLOSE_UP
											
									);


	m_ButtonNetravathi.ResetButton();
	m_ButtonSharavathi.ResetButton();
	m_ButtonCauvery.ResetButton();
	m_ButtonHemavathi.ResetButton();
	m_ButtonTunga.ResetButton();

//	m_ButtonSystemTray.ResetButton();
	m_ButtonConverter.ResetButton();

	m_ButtonClose.ResetButton();


	//Turn On The Scroll Lock

	if(!(GetKeyState(VK_SCROLL ) & 0x0001))
	{
	keybd_event( VK_SCROLL,
                      0x45,
                      KEYEVENTF_EXTENDEDKEY | 0,
                      0 );

        // Simulate a key release
        keybd_event( VK_SCROLL,
                      0x45,
                      KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                      0);
	}

	//CreateThreadEx(
	if(!WIN_NT_NO_TRAY)
	trayIconThreadHandle = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)CKuvempuDlg::animateTrayIcon,NULL,0,NULL);
//	_beginthread(animateTrayIcon,0,NULL);

if (!instanceChecker.PreviousInstanceRunning())
    instanceChecker.TrackFirstInstanceRunning();

if(WIN_NT_NO_TRAY)
{
		keybd_event( VK_SCROLL,
                      0x45,
                      KEYEVENTF_EXTENDEDKEY | 0,
                      0 );

        // Simulate a key release
        keybd_event( VK_SCROLL,
                      0x45,
                      KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                      0);
}
/*else
{

	OnHemavathi();
	this->ShowWindow(SW_HIDE);
	if(SetToTray == FALSE)
	SetToTray();
	
}*/
		return TRUE;  // return TRUE  unless you set the focus to a control
}


void CKuvempuDlg::OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex,BOOL bSysMenu)
{
    ASSERT(pPopupMenu != NULL);
    // Check the enabled state of various menu items.

    CCmdUI state;
    state.m_pMenu = pPopupMenu;
    ASSERT(state.m_pOther == NULL);
    ASSERT(state.m_pParentMenu == NULL);

    // Determine if menu is popup in top-level menu and set m_pOther to
    // it if so (m_pParentMenu == NULL indicates that it is secondary popup).
    HMENU hParentMenu;

    if (AfxGetThreadState()->m_hTrackingMenu == pPopupMenu->m_hMenu)
        state.m_pParentMenu = pPopupMenu;    // Parent == child for tracking popup.
    else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL)
    {
        CWnd* pParent = this;
           // Child windows don't have menus--need to go to the top!
        if (pParent != NULL &&
           (hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL)
        {
           int nIndexMax = ::GetMenuItemCount(hParentMenu);
           for (int nIndex = 0; nIndex < nIndexMax; nIndex++)
           {
            if (::GetSubMenu(hParentMenu, nIndex) == pPopupMenu->m_hMenu)
            {
                // When popup is found, m_pParentMenu is containing menu.
                state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
                break;
            }
           }
        }
    }

//	CWnd* pParent = this;
//	pParent->SetFont(&fnt);

    state.m_nIndexMax = pPopupMenu->GetMenuItemCount();
    for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;state.m_nIndex++)
    {
        state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex);
        if (state.m_nID == 0)
           continue; // Menu separator or invalid cmd - ignore it.

        ASSERT(state.m_pOther == NULL);
        ASSERT(state.m_pMenu != NULL);
        if (state.m_nID == (UINT)-1)
        {
           // Possibly a popup menu, route to first item of that popup.
           state.m_pSubMenu = pPopupMenu->GetSubMenu(state.m_nIndex);
           if (state.m_pSubMenu == NULL ||
            (state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 ||
            state.m_nID == (UINT)-1)
           {
            continue;       // First item of popup can't be routed to.
           }
           state.DoUpdate(this, TRUE);   // Popups are never auto disabled.
        }
        else
        {
           // Normal menu item.
           // Auto enable/disable if frame window has m_bAutoMenuEnable
           // set and command is _not_ a system command.
           state.m_pSubMenu = NULL;
           state.DoUpdate(this, FALSE);
        }

        // Adjust for menu deletions and additions.
        UINT nCount = pPopupMenu->GetMenuItemCount();
        if (nCount < state.m_nIndexMax)
        {
           state.m_nIndex -= (state.m_nIndexMax - nCount);
           while (state.m_nIndex < nCount &&
            pPopupMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
           {
            state.m_nIndex++;
           }
        }
        state.m_nIndexMax = nCount;
    }

}

void CKuvempuDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		if(nID == SC_MINIMIZE)
		{
			ShowWindow(SW_MINIMIZE);
		}
		if(nID == SC_CLOSE)
		{
			OnClose();
		}
		else
		{
			CDialog::OnSysCommand(nID, lParam);
		}
	}
}


void CKuvempuDlg::OnDestroy()
{
	WinHelp(0L, HELP_QUIT);
	CDialog::OnDestroy();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKuvempuDlg::OnPaint() 
{
//	CStatic* pTitle = (CStatic*)GetDlgItem(IDC_STATIC);
//	ASSERT_VALID(pTitle);
//	pTitle->SetFont(&m_fntTitle);

//	CString str;
//	str.LoadString(IDD_KUVEMPU_DIALOG);
//	SetDlgItemText(IDC_STATIC,(LPCSTR)str);

	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CKuvempuDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CKuvempuDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_ButtonNetravathi.ResetButton();
	m_ButtonSharavathi.ResetButton();
	m_ButtonCauvery.ResetButton();
	m_ButtonHemavathi.ResetButton();
	m_ButtonTunga.ResetButton();

//	m_ButtonSystemTray.ResetButton();
	m_ButtonConverter.ResetButton();
	m_ButtonClose.ResetButton();

	CDialog::OnMouseMove(nFlags, point);
}



void CKuvempuDlg::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}


//---------------------------------------------------------
//-- WM_LBUTTON_DOWN
// The left button of the mouse pressed -
// beahve as like the title bar was pressed
//----------------------------------------------------------
void CKuvempuDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default	
	CDialog::OnLButtonDown(nFlags, point);
	PostMessage( WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM( point.x, point.y));
}


void CKuvempuDlg::OnHemavathi() 
{
				
	ResteButton();

	        if(hookID == 3)
	 			DeInstallKeyboardHookSharavathi();
		    if(hookID == 2)
				DeInstallKeyboardHookNetravathi();					
		    if(hookID == 4)
				DeInstallKeyboardHookCauvery();
			if(hookID == 5)
				DeInstallKeyboardHookTunga();

			hookID = 1;
			InstallKeyboardHookHemavathiExpEXP(GetSafeHwnd());
		

				Sleep(50);

				if(isTraySet == FALSE && !WIN_NT_NO_TRAY)
				{
					this->ShowWindow(SW_HIDE);
					SetToTray();
					SetToolTip("KeyBoard Selected Hemavathi");
				}
}

void CKuvempuDlg::OnSharavathi() 
{
					
	ResteButton();

			if(hookID == 1)
				DeInstallKeyboardHookHemavathi();
			if(hookID == 2)
				DeInstallKeyboardHookNetravathi();					
			if(hookID == 4)
				DeInstallKeyboardHookCauvery();
			if(hookID == 5)
				DeInstallKeyboardHookTunga();
			
			hookID = 3;
			
			InstallKeyboardHookSharavathiExpEXP(GetSafeHwnd());


				Sleep(50);
				if(isTraySet == FALSE && !WIN_NT_NO_TRAY)
				{
					this->ShowWindow(SW_HIDE);
					SetToTray();
					SetToolTip("KeyBoard Selected Sharavathi");
				}
}

void CKuvempuDlg::OnNetravathi() 
{
			
	ResteButton();

			if(hookID == 1)
				DeInstallKeyboardHookHemavathi();
			if(hookID == 3)
				DeInstallKeyboardHookSharavathi();					
			if(hookID == 4)
				DeInstallKeyboardHookCauvery();
			if(hookID == 5)
				DeInstallKeyboardHookTunga();

					hookID = 2;

			InstallKeyboardHookNetravathiExpEXP(GetSafeHwnd());
		
				Sleep(50);
				if(isTraySet == FALSE && !WIN_NT_NO_TRAY)
				{
					this->ShowWindow(SW_HIDE);
					SetToTray();
					SetToolTip("KeyBoard Selected Netravathi");
				}
}


void CKuvempuDlg::OnCauvery() 
{
					
	ResteButton();

			if(hookID == 1)
				DeInstallKeyboardHookHemavathi();
			if(hookID == 2)
				DeInstallKeyboardHookNetravathi();					
			if(hookID == 3)
				DeInstallKeyboardHookSharavathi();
			if(hookID == 5)
				DeInstallKeyboardHookTunga();

			
			hookID = 4;

			InstallKeyboardHookCauveryExpEXP(GetSafeHwnd());

				Sleep(50);
				if(isTraySet == FALSE && !WIN_NT_NO_TRAY)
				{
					this->ShowWindow(SW_HIDE);
					SetToTray();
					SetToolTip("KeyBoard Selected Cauvery");
				}
}


void CKuvempuDlg::OnConverter() 
{
	STARTUPINFO si_splash;
	PROCESS_INFORMATION pi_splash;
	
	ZeroMemory(&si_splash,sizeof(si_splash));

	si_splash.cb = sizeof(si_splash);

	ZeroMemory(&pi_splash,sizeof(pi_splash));


	 if(!CreateProcess(NULL,
		"Text_Converter.exe",
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si_splash,
		&pi_splash))
	
	 ::WaitForSingleObjectEx(pi_splash.hProcess,INFINITE,FALSE);
	//printf("Child Complete");

	//closes handles
	CloseHandle(pi_splash.hProcess);
    CloseHandle(pi_splash.hThread);
}

void CKuvempuDlg::OnOpen() 
{
	//::MessageBox(NULL,"dbd","dfbd",MB_OK);
		ShowWindow(SW_SHOW);
}

void CKuvempuDlg::OnClose() 
{

	if((GetKeyState(VK_SCROLL) & 1))
	{
	keybd_event( VK_SCROLL,
                      0x45,
                      KEYEVENTF_EXTENDEDKEY | 0,
                      0 );
        // Simulate a key release
    keybd_event( VK_SCROLL,
                      0x45,
                      KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                      0);
	}

	DeInstallKeyboardHookHemavathi();
	DeInstallKeyboardHookNetravathi();					
	DeInstallKeyboardHookCauvery();
    DeInstallKeyboardHookSharavathi();
	DeInstallKeyboardHookTunga();

	if(!WIN_NT_NO_TRAY)
	CloseHandle(trayIconThreadHandle);
	
	CDialog::OnCancel();
}


//void CKuvempuDlg::OnSetToTray() 
//{
//	Sleep(50);
//	this->ShowWindow(SW_HIDE);
//}


void CKuvempuDlg::OnUpdateCheck(CCmdUI* pCmdUI)
{
   pCmdUI->Enable(0);
   // if (!m_CheckDisabled.GetCheck())
    //{
        pCmdUI->SetCheck(1);
   // }
}

LRESULT CKuvempuDlg::OnKickIdle(WPARAM, LPARAM)
{
    CMenu* pMainMenu = GetMenu();
    CCmdUI cmdUI;
    for (UINT n = 0; n < pMainMenu->GetMenuItemCount(); ++n)
    {
        CMenu* pSubMenu = pMainMenu->GetSubMenu(n);
        cmdUI.m_nIndexMax = pSubMenu->GetMenuItemCount();
        for (UINT i = 0; i < cmdUI.m_nIndexMax;++i)
        {
            cmdUI.m_nIndex = i;
            cmdUI.m_nID = pSubMenu->GetMenuItemID(i);
            cmdUI.m_pMenu = pSubMenu;
            cmdUI.DoUpdate(this, FALSE);
        }
    }
    return TRUE;
}

LRESULT CKuvempuDlg :: OnTrayNotify(WPARAM wParam, LPARAM lParam)
{
	return m_TrayIcon.OnTrayNotification(wParam, lParam);
	
}


void CKuvempuDlg::OnUPdateHemavathi(CCmdUI* pCmdUI)
{
	if(hookID == 1)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CKuvempuDlg::OnUPdateSharavathi(CCmdUI* pCmdUI)
{

	if(hookID == 3)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CKuvempuDlg::OnUPdateNetravathi(CCmdUI* pCmdUI)
{
	if(hookID == 2)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CKuvempuDlg::OnUPdateCauvery(CCmdUI* pCmdUI)
{
	if(hookID == 4)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CKuvempuDlg::OnUPdateTunga(CCmdUI* pCmdUI)
{
	if(hookID == 5)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CKuvempuDlg::ResteButton()
{
	if(hookID == 2)
	m_ButtonNetravathi.ResetButton();
	else
		if(hookID == 3)
	m_ButtonSharavathi.ResetButton();
	else 
		if(hookID == 4)
	m_ButtonCauvery.ResetButton();
	else
		if(hookID == 1)
	m_ButtonHemavathi.ResetButton();
	else
		if(hookID == 5)
	m_ButtonTunga.ResetButton();

//	m_ButtonSystemTray.ResetButton();
	m_ButtonConverter.ResetButton();
	m_ButtonClose.ResetButton();
 }


void CKuvempuDlg::OnAbout()
 {
	 CAboutDlg AbtDlg;
	 AbtDlg.DoModal();
 }

void CKuvempuDlg::SetToolTip(CString toolTip)
{
		m_TrayIcon.SetTooltipText(toolTip);
}


void CKuvempuDlg::CheckForInstance()
{
  CInstanceChecker instanceChecker;
  if (instanceChecker.PreviousInstanceRunning())
  {
	  AfxMessageBox(_T("Previous version detected, will now restore it"), MB_OK);
    instanceChecker.ActivatePreviousInstance();
	//  return FALSE;
  }

}

void CKuvempuDlg::SetToTray()
{
	if(!m_TrayIcon.Create(this,                             // Parent window
                           WM_TRAYNOTIFY,                   // Icon notify message to use
                           m_strStatus,						// tooltip
                           m_Icon,							// Icon to use
                           IDR_POPUP_MENU))                 // ID of tray icon
	{
		isTraySet = FALSE;
	}
	else
		isTraySet = TRUE;

	m_TrayIcon.SetIcon(IDR_TRAY);//m_TrayIcon.SetIcon(IDI_ICON2);
	SetToolTip("Kuvempu Kannada Tray Icon");
}

void CKuvempuDlg::OnHemavathiHelp() 
{
	// TODO: Add your control notification handler code here
	HemavathiHelp Hhelp;
	Hhelp.DoModal();
}

void CKuvempuDlg::OnNetravathiHelp() 
{
	// TODO: Add your control notification handler code here
	NetravathiHelp Nhelp;
	Nhelp.DoModal();
}

void CKuvempuDlg::OnCauveryHelp() 
{
	// TODO: Add your control notification handler code here
	CCauveryHelp Chelp;
	Chelp.DoModal();
}

void CKuvempuDlg::OnSharavathiHelp() 
{
	// TODO: Add your control notification handler code here
		SharavathiHelp  Shelp;
		Shelp.DoModal();
}

void CKuvempuDlg::OnTunga() 
{
	// TODO: Add your control notification handler code here
	ResteButton();

			if(hookID == 1)
				DeInstallKeyboardHookHemavathi();
			if(hookID == 2)
				DeInstallKeyboardHookNetravathi();					
			if(hookID == 3)
				DeInstallKeyboardHookSharavathi();
			if(hookID == 4)
				DeInstallKeyboardHookCauvery();

			hookID = 5;

			InstallKeyboardHookTungaExpEXP(GetSafeHwnd());

				Sleep(50);
				if(isTraySet == FALSE && !WIN_NT_NO_TRAY)
				{
					this->ShowWindow(SW_HIDE);
					SetToTray();
				}

				SetToolTip("KeyBoard Selected Tunga");
}

void CKuvempuDlg::OnTungaHelp() 
{
	// TODO: Add your control notification handler code here
	CTungaHelp Thelp;
	Thelp.DoModal();
	
}

unsigned long CKuvempuDlg::animateTrayIcon(void *d)
{
	while(1)
	{
		m_TrayIcon.SetIcon(IDI_ICON1);
		Sleep(1000);
		m_TrayIcon.SetIcon(IDR_TRAY);
		Sleep(1000);
		m_TrayIcon.SetIcon(IDR_MAINFRAME);
		Sleep(1000);
	}

	return 0;
}

