#if !defined(AFX_TUNGAHELP_H__A09C4FA2_5193_43EB_B931_B96BA88778D2__INCLUDED_)
#define AFX_TUNGAHELP_H__A09C4FA2_5193_43EB_B931_B96BA88778D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TungaHelp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTungaHelp dialog

class CTungaHelp : public CDialog
{
// Construction
public:
	CTungaHelp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTungaHelp)
	enum { IDD = IDD_TUNGA_HELP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTungaHelp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTungaHelp)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TUNGAHELP_H__A09C4FA2_5193_43EB_B931_B96BA88778D2__INCLUDED_)
