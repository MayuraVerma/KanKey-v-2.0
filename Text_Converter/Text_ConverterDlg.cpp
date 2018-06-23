// Text_ConverterDlg.cpp : implementation file
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


#include "stdafx.h"
#include "Text_Converter.h"
#include "Text_ConverterDlg.h"
#include "Converter.h"
#include "PrakToKuv.h"
#include <iostream>
#include <fstream>
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

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
// CText_ConverterDlg dialog

CText_ConverterDlg::CText_ConverterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CText_ConverterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CText_ConverterDlg)
		// NOTE: the ClassWizard will add member initialization here
		m_strSRC = _T("");
		m_strDST = _T("");
		m_chkScale = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CText_ConverterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CText_ConverterDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Text(pDX, IDC_SRC_PATH, m_strSRC);
	DDV_MaxChars(pDX, m_strSRC, 255);
	DDX_Text(pDX, IDC_DST_PATH, m_strDST);
	DDV_MaxChars(pDX, m_strDST, 255);
	DDX_Control(pDX,IDC_PROGRESS1,m_ctlProgress);
//	DDX_Control(pDX,IDC_STATIC,m_ctlBmp);
//	DDX_Check(pDX, IDC_CHECK_SCALE, m_chkScale);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CText_ConverterDlg, CDialog)
	//{{AFX_MSG_MAP(CText_ConverterDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO_SURABHI, OnSurabhi)
	ON_BN_CLICKED(IDC_RADIO_SRG, OnSrg)
	ON_BN_CLICKED(IDC_RADIO_SRG3, OnSrg)
	ON_BN_CLICKED(IDC_RADIO_SRG2, OnSrg2)
	ON_BN_CLICKED(IDC_RADIO_AKRUTHI, OnAnu)
	ON_BN_CLICKED(IDC_RADIO_PRA, OnPra)
	ON_BN_CLICKED(IDC_SRC, OnSrcFileSelect)
	ON_BN_CLICKED(IDC_DST, OnDscFileSelect)
	ON_BN_CLICKED(ID_CONVERT, OnConvert)
	ON_BN_CLICKED(IDC_RADIO_SREELIPI, OnSreeLipi)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CText_ConverterDlg message handlers

BOOL CText_ConverterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

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
	
	// TODO: Add extra initialization here
//////////////////////////////////////////////////////////////////////////
	// BIT MAP INITIALIASATION CODE//

	m_ctlBmp.LoadBitmap(IDB_BITMAP1);

	BlitBitmap(m_rcLft,m_ctlBmp);

	m_rcLft.left = 523 ;m_rcLft.right = 598;
	m_rcLft.top = 70; m_rcLft.bottom = 145;
/////////////////////////////////////////////////////////////////////////
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CText_ConverterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CText_ConverterDlg::OnPaint() 
{
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





void CText_ConverterDlg::OnSrcFileSelect() 
{
	// TODO: Add your control notification handler code here
		CString OpenFilter;
	OpenFilter = "TXT Files (*.txt)|*.txt||";

//	::MessageBox(NULL,"dfvd","bgb",MB_OK):		

	//file open dialog for selecting XML files
	CFileDialog FileOpenDialog(
		TRUE,
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_PATHMUSTEXIST,
		OpenFilter,					// filter
		AfxGetMainWnd());		
	//::MessageBox(NULL,"gffr","brgb",MB_OK);
	if(FileOpenDialog.DoModal()==IDOK)
	{
		m_strSRC = FileOpenDialog.GetPathName();
		UpdateData(FALSE);
	}	

}

void CText_ConverterDlg::OnDscFileSelect() 
{
	// TODO: Add your control notification handler code here
		CString OpenFilter;
	OpenFilter = "TXT Files (*.txt)|*.txt||";
		

	//file open dialog for selecting XML files
	CFileDialog FileOpenDialog(
		TRUE,
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_PATHMUSTEXIST,
		OpenFilter,					// filter
		AfxGetMainWnd());	
	if(FileOpenDialog.DoModal()==IDOK)
	{
		m_strDST = FileOpenDialog.GetPathName();
		UpdateData(FALSE);
	}	
//	else
///		m_strDST = '\0';
}




// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CText_ConverterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CText_ConverterDlg::OnSreeLipi() 
{
	// TODO: Add your control notification handler code here
	Choice = 2;
	
}

void CText_ConverterDlg::OnSurabhi() 
{
	// TODO: Add your control notification handler code here
	Choice = 3;
}

void CText_ConverterDlg::OnSrg() 
{
	// TODO: Add your control notification handler code here
	Choice = 1;
}

void CText_ConverterDlg::OnSrg2() 
{
	// TODO: Add your control notification handler code here
	Choice = 5;
}

void CText_ConverterDlg::OnAnu() 
{
	// TODO: Add your control notification handler code here
	Choice = 4;
}

void CText_ConverterDlg::OnPra() 
{
	// TODO: Add your control notification handler code here
	Choice = 6;
}

void CText_ConverterDlg::OnCancel() 
{
	// TODO: Add extra cleAnup here
CDialog::OnCancel();
}


//on OK 
void CText_ConverterDlg::OnConvert() 
{
	int Conv_Status;
	
	UpdateData(TRUE);

	// TODO: Add your control notification handler code here
if(Is_path_full(m_strSRC,m_strDST))
{
switch (Choice)
	{
//////////////////////////////////////////////////////////////////////////////////////////////////////////
	case 1:
	    Conv_Status = Srg_To_Kuvempu(m_strSRC,m_strDST);
 		::MessageBox(NULL,"Conversion Completed Srg_To_Kuvempu" ,"ALERT....",MB_OK);
	break;
////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case 2:
		Conv_Status = SreeLipi_To_Kuvempu(m_strSRC,m_strDST);
		::MessageBox(NULL,"Conversion Completed SreeLipi_To_Kuvempu" ,"ALERT....",MB_OK);
		 break;
///////////////////////////////////////////////////////////////////////////////////////////////////////
	case 3:
		Conv_Status = Surabhi_To_Kuvempu(m_strSRC,m_strDST);
		::MessageBox(NULL,"Conversion Completed Surabhi_To_Kuvempu" ,"ALERT....",MB_OK);
		break;
////////////////////////////////////////////////////////////////////////////////////////////////////////
	case 4:
		Conv_Status = Anu_To_Kuvempu(m_strSRC,m_strDST);
		::MessageBox(NULL,"Conversion Completed Anu_To_Kuvempu " ,"ALERT....",MB_OK);
		break;
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	case 5:
		Conv_Status = Srg_To_Kuvempu2(m_strSRC,m_strDST);
		::MessageBox(NULL,"Conversion Completed Srg_To_Kuvempu " ,"ALERT....",MB_OK);
		break;
	case 6:
		Conv_Status = Pra_To_Kuvempu(m_strSRC,m_strDST);
		::MessageBox(NULL,"Conversion Completed Prakashak To Kuvempu " ,"ALERT....",MB_OK);
		break;

	default :
		::MessageBox(NULL,"Make Proper Choice" ,"ALERT....",MB_OK);
	}//////////////////////////////end of switch//////////////////////////////////

	if(Conv_Status == TRUE)
	{
		//::MessageBox(NULL,"File Conversion OK","Status",MB_OK);
	}
	else
	{
		//::MessageBox(NULL,"Conversion FAILED !!! Check Path Names","Status",MB_OK);
	}

}
else//if files is not selected properly 
		::MessageBox(NULL,"Conversion FAILED !!! Check Path Names","Status",MB_OK);

m_ctlProgress.SetRange(0,0);
}

void CText_ConverterDlg::BlitBitmap(CRect& rc,CBitmap& bm) 
{
	CClientDC dc(this);

	CDC dcMem;
	HBITMAP hbmpOld;

	dcMem.CreateCompatibleDC(&dc);
	hbmpOld = (HBITMAP)dcMem.SelectObject(bm);

	GetDC()->BitBlt(rc.left,rc.top,rc.right,rc.bottom,&dcMem,0,0,SRCCOPY);
	dcMem.SelectObject(hbmpOld);
}


int CText_ConverterDlg::Srg_To_Kuvempu(const char* pszSRCFile,const char* pszDSTFile)
{
			int fchr;
			long int i;
		    
			found = 0;
			
			int flag = 1;
			int Made_Of_More_Chars = FALSE; // is set if character is made of 2 or more charcters
			
			long int k = 0;	// for buffer 
			
			int m = 0;  //Index for Progress Bar
			int l = 0;
			//long int x = sizeof(long int)-2;
			long int buffer[64000];
			FILE *fp1,*fp2;

			//fstream out(pszDSTFile , ios::out );
			//fstream in (pszSRCFile , ios::in  );

			fp1 = fopen(pszDSTFile,"w");
			fp2 = fopen(pszSRCFile,"r");

		
			i = 0;
			do 
			{
				fchr=fgetc(fp2);
			
				buffer[i++] = fchr; //insert it to buffer

			}while(fchr!=EOF);
		
			buffer[i] = -1; //To represent End of String

			k = 0; // INDEX FOR BUFFER TRAVERSING 
			while(buffer[k]!= -1)
			{
				found = 0;
				Made_Of_More_Chars = FALSE;

							//–	A	 G	H 
							if( (char)buffer[k] == '–' && ( (char)buffer[k+1] == 'A' || 
															(char)buffer[k+1] == 'G' || 
															(char)buffer[k+1] == 'H'
														  )
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"S");
								Made_Of_More_Chars = TRUE;
								k = k+1;
							}else
							//–	V
							if( (char)buffer[k] == '–' && (char)buffer[k+1] == 'V'  
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"SÈ");
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}else
							//¢	A	 G	H		¢	V
							if( (char)buffer[k] == '¢' && ( (char)buffer[k+1] == 'A' || 
															(char)buffer[k+1] == 'G' || 
															(char)buffer[k+1] == 'H'
														  )
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"e");
								Made_Of_More_Chars = TRUE;
								k = k+1;
							}else
							//V
							if( (char)buffer[k] == '¢' && (char)buffer[k+1] == 'V'  
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"eÈ");
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}else
							//¾	A	 G	H		¾	V
							if( (char)buffer[k] == '¾' && ( (char)buffer[k+1] == 'A' || 
															(char)buffer[k+1] == 'G' || 
															(char)buffer[k+1] == 'H'
														  )
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"¨");
								Made_Of_More_Chars = TRUE;
								k = k+1;
							}else
							//V
							if( (char)buffer[k] == '¾' && (char)buffer[k+1] == 'V'  
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"¨È");
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}else
							//Æ	A	 G	H		Æ	V
							if( (char)buffer[k] == 'Æ' && ( (char)buffer[k+1] == 'A' || 
															(char)buffer[k+1] == 'G' || 
															(char)buffer[k+1] == 'H'
														  )
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"¯");
								Made_Of_More_Chars = TRUE;
								k = k+1;
							}else
							//V
							if( (char)buffer[k] == 'Æ' && (char)buffer[k+1] == 'V' 
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"¯È");
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}else
							//Ù	A	 G	H		Ù	V
							if( (char)buffer[k] == 'Ù' && ( (char)buffer[k+1] == 'A' || 
															(char)buffer[k+1] == 'G' || 
															(char)buffer[k+1] == 'H'
														  )
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"eÕ");
								Made_Of_More_Chars = TRUE;
								k = k+1;
							}else
							//V
							if( (char)buffer[k] == 'Ù' && (char)buffer[k+1] == 'V'  
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"eÕÈ");
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}else
							//w	A	 G	H		í	V
							if( (char)buffer[k] == 'w' && ( (char)buffer[k+1] == 'A' || 
															(char)buffer[k+1] == 'G' || 
															(char)buffer[k+1] == 'H'
														  )
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"Pë");
								Made_Of_More_Chars = TRUE;
								k = k+1;
							}else
							//V
							if( (char)buffer[k] == 'w' && (char)buffer[k+1] == 'V'  
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"PëÈ");
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}else
							//Â		A	 G	H		í	V
							if( (char)buffer[k] == 'Â' && ( (char)buffer[k+1] == 'A' )
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"AiÀi");  //Á
								Made_Of_More_Chars = TRUE;
								k = k+1;
							}else
							//ëA
							if( (char)buffer[k] == 'ë' && (char)buffer[k+1] == 'A' 
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"gÀhiÁ");
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}else
							//ÀA
							if( (char)buffer[k] == 'À' && (char)buffer[k+1] == 'A'  
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"ªÀiÁ");
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}else
							//ÁA 
							if( (char)buffer[k] == 'Á' && (char)buffer[k+1] == 'A' 
														  ) 
							{
								found = 1 ;
								fprintf(fp1,"«iÁ");
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}else
							//[ 
							if( (char)buffer[k] == '[') 
							{
								found = 1 ;
								fprintf(fp1,"Ûç");
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}else
							// ËRD  ËRD
							if( (char)buffer[k] == 'Ë' &&  (char)buffer[k+1] == 'R' && (char)buffer[k+2] == 'D' ) 
							{
								found = 1 ;
								fprintf(fp1,"±ÀÄæ");
								Made_Of_More_Chars = TRUE;
								k = k+3;
							}else
							//<<
							if( (char)buffer[k] == '<' &&  (char)buffer[k+1] == '<') 
							{
								found = 1 ;
								fprintf(fp1,"“");
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}else//>>
							if( (char)buffer[k] == '>' &&  (char)buffer[k+1] == '>') 
							{
								found = 1 ;
								fprintf(fp1,"”");
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}else///////////////////////////if not in above case ie; if character is not made of 2 characters
							
				for(i=0;i<223;i++)
				{
					if( Srg[i].vSrg == (char)buffer[k] ) 
						{  
					//	::MessageBox(NULL,"vfdv","dfvfd",MB_OK);
							found = 1 ;
							j=0;
							flag = 0;
							
							while(Srg[i].vKump[j] != -1)
							{	
								fprintf(fp1,"%c",Srg[i].vKump[j]);
								j++;
							}
						}
				}
			
				if(!found)
				{
					fprintf(fp1,"%c",buffer[k]); //If not in Table
				}

				if(Made_Of_More_Chars != TRUE)
				{
					k++;//Set to next element in buffer
				}
			 }
	
		bRet = TRUE;
		
		for (l = 50; l < 100; l++)
		{
			m_ctlProgress.SetPos(l);
			m = 10;
			while(m>0)
			{
				Sleep(1);
				m--;
			}
		}

	fclose(fp1);
	fclose(fp2);
	return bRet;
}



int CText_ConverterDlg::Srg_To_Kuvempu2(const char* pszSRCFile,const char* pszDSTFile)
{
			int fchr;
			long int i;
		    
			found = 0;
			
			int flag = 1;
			int Made_Of_More_Chars = FALSE; // is set if character is made of 2 or more charcters
			
			long int k = 0;	// for buffer 
			
			int m = 0;  //Index for Progress Bar
			int l = 0;
			//long int x = sizeof(long int)-2;
			long int buffer[64000];
			FILE *fp1,*fp2;

			//fstream out(pszDSTFile , ios::out );
			//fstream in (pszSRCFile , ios::in  );

			fp1 = fopen(pszDSTFile,"w");
			fp2 = fopen(pszSRCFile,"r");

		
			i = 0;
			do 
			{
				fchr=fgetc(fp2);
			
				buffer[i++] = fchr; //insert it to buffer

			}while(fchr!=EOF);
		
			buffer[i] = -1; //To represent End of String

			k = 0; // INDEX FOR BUFFER TRAVERSING 
			while(buffer[k]!= -1)
			{
				found = 0;
				Made_Of_More_Chars = FALSE;

							//–	A	 G	H 
							if( (char)buffer[k] == '–' && ( (char)buffer[k+1] == 'A' || 
															(char)buffer[k+1] == 'G' || 
															(char)buffer[k+1] == 'H'
														  )
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"S");
								Made_Of_More_Chars = TRUE;
								k = k+1;
							}else
							//–	V
							if( (char)buffer[k] == '–' && (char)buffer[k+1] == 'V'  
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"SÈ");
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}else
							//¢	A	 G	H		¢	V
							if( (char)buffer[k] == '¢' && ( (char)buffer[k+1] == 'A' || 
															(char)buffer[k+1] == 'G' || 
															(char)buffer[k+1] == 'H'
														  )
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"e");
								Made_Of_More_Chars = TRUE;
								k = k+1;
							}else
							//V
							if( (char)buffer[k] == '¢' && (char)buffer[k+1] == 'V'  
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"eÈ");
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}else
							//¾	A	 G	H		¾	V
							if( (char)buffer[k] == '¾' && ( (char)buffer[k+1] == 'A' || 
															(char)buffer[k+1] == 'G' || 
															(char)buffer[k+1] == 'H'
														  )
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"¨");
								Made_Of_More_Chars = TRUE;
								k = k+1;
							}else
							//V
							if( (char)buffer[k] == '¾' && (char)buffer[k+1] == 'V'  
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"¨È");
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}else
							//Æ	A	 G	H		Æ	V
							if( (char)buffer[k] == 'Æ' && ( (char)buffer[k+1] == 'A' || 
															(char)buffer[k+1] == 'G' || 
															(char)buffer[k+1] == 'H'
														  )
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"¯");
								Made_Of_More_Chars = TRUE;
								k = k+1;
							}else
							//V
							if( (char)buffer[k] == 'Æ' && (char)buffer[k+1] == 'V' 
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"¯È");
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}else
							//Ù	A	 G	H		Ù	V
							if( (char)buffer[k] == 'Ù' && ( (char)buffer[k+1] == 'A' || 
															(char)buffer[k+1] == 'G' || 
															(char)buffer[k+1] == 'H'
														  )
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"eÕ");
								Made_Of_More_Chars = TRUE;
								k = k+1;
							}else
							//V
							if( (char)buffer[k] == 'Ù' && (char)buffer[k+1] == 'V'  
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"eÕÈ");
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}else
							//w	A	 G	H		í	V
							if( (char)buffer[k] == 'w' && ( (char)buffer[k+1] == 'A' || 
															(char)buffer[k+1] == 'G' || 
															(char)buffer[k+1] == 'H'
														  )
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"Pë");
								Made_Of_More_Chars = TRUE;
								k = k+1;
							}else
							//V
							if( (char)buffer[k] == 'w' && (char)buffer[k+1] == 'V'  
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"PëÈ");
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}else
							//Â		A	 G	H		í	V
							if( (char)buffer[k] == 'Â' && ( (char)buffer[k+1] == 'A' )
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"AiÀi");  //Á
								Made_Of_More_Chars = TRUE;
								k = k+1;
							}else
							//ëA
							if( (char)buffer[k] == 'ë' && (char)buffer[k+1] == 'A' 
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"gÀhiÁ");
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}else
							//ÀA
							if( (char)buffer[k] == 'À' && (char)buffer[k+1] == 'A'  
							  ) 
							{
								found = 1 ;
								fprintf(fp1,"ªÀiÁ");
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}else
							//ÁA 
							if( (char)buffer[k] == 'Á' && (char)buffer[k+1] == 'A' 
														  ) 
							{
								found = 1 ;
								fprintf(fp1,"«iÁ");
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}else
							//[ 
							if( (char)buffer[k] == '[') 
							{
								found = 1 ;
								fprintf(fp1,"Ûç");
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}else
							// ËRD  ËRD
							if( (char)buffer[k] == 'Ë' &&  (char)buffer[k+1] == 'R' && (char)buffer[k+2] == 'D' ) 
							{
								found = 1 ;
								fprintf(fp1,"±ÀÄæ");
								Made_Of_More_Chars = TRUE;
								k = k+3;
							}else
							//<<
							if( (char)buffer[k] == '<' &&  (char)buffer[k+1] == '<') 
							{
								found = 1 ;
								fprintf(fp1,"“");
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}else//>>
							if( (char)buffer[k] == '>' &&  (char)buffer[k+1] == '>') 
							{
								found = 1 ;
								fprintf(fp1,"”");
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}else///////////////////////////if not in above case ie; if character is not made of 2 characters
							
				for(i=0;i<223;i++)
				{
					if( Srg2[i].vSrg == (char)buffer[k] ) 
						{  
					//	::MessageBox(NULL,"vfdv","dfvfd",MB_OK);
							found = 1 ;
							j=0;
							flag = 0;
							
							while(Srg2[i].vKump[j] != -1)
							{	
								fprintf(fp1,"%c",Srg2[i].vKump[j]);
								j++;
							}
						}
				}
			
				if(!found)
				{
					fprintf(fp1,"%c",buffer[k]); //If not in Table
				}

				if(Made_Of_More_Chars != TRUE)
				{
					k++;//Set to next element in buffer
				}
			 }
	
		bRet = TRUE;
		
		for (l = 50; l < 100; l++)
		{
			m_ctlProgress.SetPos(l);
			m = 10;
			while(m>0)
			{
				Sleep(1);
				m--;
			}
		}

	fclose(fp1);
	fclose(fp2);
	return bRet;
}



int CText_ConverterDlg::SreeLipi_To_Kuvempu(const char* pszSRCFile,const char* pszDSTFile)
{
			int fchr;
			long int i;
		    
			found = 0;
			
			int flag = 1;
			int Made_Of_More_Chars = FALSE; // is set if character is made of 2 or more charcters
			
			int k = 0;	// for buffer 
			
			int m = 0;  //Index for Progress Bar
			int l = 0;
			//long int x = sizeof(long int)-2;
			long int buffer[64000];
			FILE *fp1,*fp2;

			//fstream out(pszDSTFile , ios::out );
			//fstream in (pszSRCFile , ios::in  );

			fp1 = fopen(pszDSTFile,"w");
			fp2 = fopen(pszSRCFile,"r");

		
			i = 0;
			do 
			{
				fchr=fgetc(fp2);
			
				buffer[i++] = fchr; //insert it to buffer

			}while(fchr!=EOF);
		
			buffer[i] = -1; //To represent End of String

			k = 0; // INDEX FOR BUFFER TRAVERSING 
			while(buffer[k]!= -1)
			{
				found = 0;
				Made_Of_More_Chars = FALSE;



							if((char)buffer[k] == 'S' && (char)buffer[k+1] == '|')
							{
								found = 1 ;
								fprintf(fp1,"%c",(char)121);
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}
							else
							if((char)buffer[k] == 'S' && (char)buffer[k+1] == '¬')
							{
								found = 1 ;
								fprintf(fp1,"%c",(char)120);
								Made_Of_More_Chars = TRUE;
								k = k+2;
								//::MessageBox(NULL,"fdvfdv","fdvdvf",MB_OK);
							}
							else
							if((char)buffer[k] == '×' && (char)buffer[k+1] == '¬')
							{
								found = 1 ;
								fprintf(fp1,"%c%c",(char)122 ,(char)115);
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}
							else
							if((char)buffer[k] == '×' && (char)buffer[k+1] == '|')
							{
								found = 1 ;
								fprintf(fp1,"%c%c",(char)162 ,(char)252);
								Made_Of_More_Chars = TRUE;
								k = k+2;
							//	::MessageBox(NULL,"fdvfdv","fdvdvf",MB_OK);
							}
							else
							if((char)buffer[k] == 'Ü' && (char)buffer[k+1] == '¦')
							{
								found = 1 ;
								fprintf(fp1,"%c%c",(char)114,(char)252);
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}
							else
							if((char)buffer[k] == 'Ü' && (char)buffer[k+1] == 'û')
							{
								found = 1 ;
								fprintf(fp1,"%c%c",(char)113,(char)115);
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}
							else
							if((char)buffer[k] == '´' && (char)buffer[k+1] == 'î')
							{
								found = 1 ;
								fprintf(fp1,"%c%c",(char)168 , (char)115);
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}
							else
							if((char)buffer[k] == '´' && (char)buffer[k+1] == '[')
							{
								found = 1 ;
								fprintf(fp1,"%c%c",(char)169 , (char)252);
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}
							else
							if((char)buffer[k] == 'i' && (char)buffer[k+1] == 'F')
							{
								found = 1 ;
								fprintf(fp1,"%c%c",(char)165 , (char)115);
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}
							else
							if((char)buffer[k] == 'i' && (char)buffer[k+1] == '¡')
							{
								found = 1 ;
								fprintf(fp1,"%c%c",(char)166 , (char)252);
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}
							else
							if((char)buffer[k] == 'ï' && (char)buffer[k+1] == '~')
							{
								found = 1 ;
								fprintf(fp1,"%c",(char)111);
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}
							else
							if((char)buffer[k] == 'ï' && (char)buffer[k+1] == 'Ô')
							{
								found = 1 ;
								fprintf(fp1,"%c",(char)112);
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}
							else
							if((char)buffer[k] == 'Æ' && (char)buffer[k+1] == 'F')
							{
								found = 1 ;
								fprintf(fp1,"%c",(char)181);
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}
							else
							if((char)buffer[k] == 'Æ' && (char)buffer[k+1] == '¡')
							{
								found = 1 ;
								fprintf(fp1,"%c",(char)182);
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}
							else
							if((char)buffer[k] == 'F' && (char)buffer[k+1] == '«' && (char)buffer[k+2] == 'Ù')
							{
								found = 1 ;
								fprintf(fp1,"%c%c%c%c",(char)165,(char)115,(char)192,(char)197);
								Made_Of_More_Chars = TRUE;
								k = k+3;
							}
							else
							if((char)buffer[k] == 'F' && (char)buffer[k+1] == 'ã' && (char)buffer[k+2] == 'Ù')
							{
								found = 1 ;
								fprintf(fp1,"%c%c%c%c",(char)165,(char)115,(char)201,(char)197);
								Made_Of_More_Chars = TRUE;
								k = k+3;
							}
							else
							if((char)buffer[k] == 'F' && (char)buffer[k+1] == '«'&& (char)buffer[k+2] == '¹')
							{
								found = 1 ;
								fprintf(fp1,"%c%c%c%c",(char)165,(char)115,(char)192,(char)199);
								Made_Of_More_Chars = TRUE;
								k = k+3;
							}
							else
							if((char)buffer[k] == 'F' && (char)buffer[k+1] == 'ã'&& (char)buffer[k+2] == '¹')
							{
								found = 1 ;
								fprintf(fp1,"%c%c%c%c",(char)165,(char)115,(char)193,(char)199);
								Made_Of_More_Chars = TRUE;
								k = k+3;
							}
							else///////////////////////////if not in above case ie; if character is not made of 2 characters
				for(i=0;i<148;i++)
				{
					if( Sree[i].vSrg == (char)buffer[k] ) 
						{  
					//	::MessageBox(NULL,"vfdv","dfvfd",MB_OK);
							found = 1 ;
							j=0;
							flag = 0;
							
							while(Sree[i].vKump[j] != -1)
							{	
								fprintf(fp1,"%c",Sree[i].vKump[j]);
								j++;
							}
						}
				}
			
				if(!found)
				{
					fprintf(fp1,"%c",buffer[k]); //If not in Table
				}

				if(Made_Of_More_Chars != TRUE)
				k++;//Set to next element in buffer
			 }
	
		bRet = TRUE;
		
		for (l = 50; l < 100; l++)
		{
			m_ctlProgress.SetPos(l);
			m = 10;
			while(m>0)
			{
				Sleep(1);
				m--;
			}
		}

	fclose(fp1);
	fclose(fp2);
	return bRet;
}


int CText_ConverterDlg::Surabhi_To_Kuvempu(const char* pszSRCFile,const char* pszDSTFile)
{
			int fchr;
			long int i;
		    
			found = 0;
			
			int flag = 1;
			int Made_Of_More_Chars = FALSE; // is set if character is made of 2 or more charcters
			
			int k = 0;	// for buffer 
			
			int m = 0;  //Index for Progress Bar
			int l = 0;
			//long int x = sizeof(long int)-2;
			long int buffer[64000];
			FILE *fp1,*fp2;

			//fstream out(pszDSTFile , ios::out );
			//fstream in (pszSRCFile , ios::in  );

			fp1 = fopen(pszDSTFile,"a");
			fp2 = fopen(pszSRCFile,"r");

		
			i = 0;
			do 
			{
				fchr=fgetc(fp2);
			
				buffer[i++] = fchr; //insert it to buffer

			}while(fchr!=EOF);
		
			buffer[i] = -1; //To represent End of String

			k = 0; // INDEX FOR BUFFER TRAVERSING 
			while(buffer[k]!= -1)
			{
				found = 0;
				Made_Of_More_Chars = FALSE;


							if((char)buffer[k] == '¤' && (char)buffer[k+1] == 'ì')
							{
								fprintf(fp1,"%c%c",(char)113,(char)115);
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}
							else
							if((char)buffer[k] == '¥' && (char)buffer[k+1] == 'ì')
							{
								fprintf(fp1,"%c%c",(char)114,(char)252);
								Made_Of_More_Chars = TRUE;
								k = k+2;
							//	::MessageBox(NULL,"fdvfdv","fdvdvf",MB_OK);
							}
							else
							if((char)buffer[k] == '¹' && (char)buffer[k+1] == 'ì')
							{
								fprintf(fp1,"%c%c",(char)122 ,(char)115);
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}
							else
							if((char)buffer[k] == 'º' && (char)buffer[k+1] == 'ì')
							{
								fprintf(fp1,"%c%c",(char)162 ,(char)252);
								Made_Of_More_Chars = TRUE;
								k = k+2;
							//	::MessageBox(NULL,"fdvfdv","fdvdvf",MB_OK);
							}
							else
							if((char)buffer[k] == 'Ã' && (char)buffer[k+1] == 'ì')
							{
								fprintf(fp1,"%c%c",(char)168,(char)115);
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}
							else
							if((char)buffer[k] == 'Å' && (char)buffer[k+1] == 'ì')
							{
								fprintf(fp1,"%c%c",(char)169,(char)252);
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}
							else
							if((char)buffer[k] == '¿' && (char)buffer[k+1] == 'ì')
							{
								fprintf(fp1,"%c%c",(char)165 , (char)115);
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}
							else
							if((char)buffer[k] == 'À' && (char)buffer[k+1] == 'ì')
							{
								fprintf(fp1,"%c%c",(char)166 , (char)252);
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}
							else
							if((char)buffer[k] == '¦' && (char)buffer[k+1] == 'í')
							{
								fprintf(fp1,"%c",(char)217);
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}
							else
							
							if((char)buffer[k] == '»' && (char)buffer[k+1] == 'í')
							{
								fprintf(fp1,"%c",(char)222);
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}
							else
							if((char)buffer[k] == 'Á' && (char)buffer[k+1] == 'í')
							{
								fprintf(fp1,"%c",(char)225);
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}
							else
							if((char)buffer[k] == 'Æ' && (char)buffer[k+1] == 'í')
							{
								fprintf(fp1,"%c",(char)227);
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}
							else
							if((char)buffer[k] == 'à' && (char)buffer[k+1] == 'í')
							{
								fprintf(fp1,"%c",(char)104);
								Made_Of_More_Chars = TRUE;
								k = k+2;
							}
							else///////////////////////////if not in above case ie; if character is not made of 2 characters
							for(i=0;i<143;i++)
							{
								if( Surabhi[i].vSrg == (char)buffer[k] ) 
									{  
										found = 1 ;
										j=0;
										flag = 0;
										while(Surabhi[i].vKump[j] != -1)
										{	
											fprintf(fp1,"%c",Surabhi[i].vKump[j]);
											j++;
										}
									}
							}
			
				if(!found)
				{
					fprintf(fp1,"%c",buffer[k]); //If not in Table
				}

				if(Made_Of_More_Chars != TRUE)
				k++;//Set to next element in buffer
			 }
	
		bRet = TRUE;
		
		for (l = 50; l < 100; l++)
		{
			m_ctlProgress.SetPos(l);
			m = 10;
			while(m>0)
			{
				Sleep(1);
				m--;
			}
		}

	fclose(fp1);
	fclose(fp2);
	return bRet;
}


int CText_ConverterDlg::Anu_To_Kuvempu(const char* pszSRCFile,const char* pszDSTFile)
{
			int l=0,m=0;

			fstream out(pszDSTFile , ios::out );
			fstream in (pszSRCFile , ios::in  );
			
			m_ctlProgress.SetRange(0, 100);
for (l = 0; l < 50; l++)
{
     m_ctlProgress.SetPos(l);
	 m = 10;
	 while(m>0)
	 {
		 Sleep(1);
		 m--;
	 }
}

		while(in.read((char * ) &fchr , sizeof fchr))
			{
				found = 0;
				for(i=0;i<188;i++)
				{
					if( Anu[i].vSrg == fchr ) 
						{  
							found = 1 ;
							j=0;
							while(Anu[i].vKump[j] != -1)
							{	
								out.write((char *) &Anu[i].vKump[j] ,sizeof Anu[i].vKump[j]);
								j++;
							}
						}
				}
				if(!found)
					{
						out.write((char *) &fchr ,sizeof fchr);
					}
			 }
			//::MessageBox(NULL,"File Conversion OK","SRG To KUVEMPU",MB_OK);

for (l = 50; l < 100; l++)
{
     m_ctlProgress.SetPos(l);
	 m = 10;
	 while(m>0)
	 {
		 Sleep(1);
		 m--;
	 }
}

			bRet = TRUE;
	out.close();
	in.close();
	return bRet;
}

int CText_ConverterDlg::Pra_To_Kuvempu(const char* pszSRCFile,const char* pszDSTFile)
{

//	AfxMessageBox("Hi I am Norm");
return PrakToKuve(pszSRCFile,pszDSTFile);
	
}

int CText_ConverterDlg::Is_path_full(const char* pszSRCFile,const char* pszDSTFile)
{
	if(strlen(pszDSTFile)<1 || strlen(pszSRCFile)<1)
	{
	//	if(strlen(pszDSTFile)<1)
	//	{
	//		pszDSTFile = "Converted//Converter1.txt";
	//	::MessageBox(NULL,"Destination file is set default ,\n Please select a destination file \n if not the converter file will be in the \"Converted\" directory \n Click OK","ALERT ........",MB_OK);
	//	}
		return 0;
		
	}
	else
	if(strcmp(pszDSTFile,pszSRCFile)==0)
	{
		::MessageBox(NULL,"Source and Destination are same","ALERT ........",MB_OK);
	return 0;
	}
	else
		return 1;
}


int CText_ConverterDlg::write(FILE *dstFile,const char *buffer)
{
		 fprintf(dstFile,"%s",buffer);
		 return 0;
}
