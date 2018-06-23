// TungaHelp.cpp : implementation file
//

#include "stdafx.h"
#include "Kuvempu.h"
#include "TungaHelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTungaHelp dialog


CTungaHelp::CTungaHelp(CWnd* pParent /*=NULL*/)
	: CDialog(CTungaHelp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTungaHelp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTungaHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTungaHelp)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTungaHelp, CDialog)
	//{{AFX_MSG_MAP(CTungaHelp)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTungaHelp message handlers
