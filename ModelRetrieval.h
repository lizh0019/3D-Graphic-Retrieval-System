// ModelRetrieval.h : main header file for the ModelRetrieval application
//

#if !defined(AFX_ModelRetrieval_H__E564C5D3_D0D7_40F3_9B06_B8FCE210154B__INCLUDED_)
#define AFX_ModelRetrieval_H__E564C5D3_D0D7_40F3_9B06_B8FCE210154B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CModelRetrievalApp:
// See ModelRetrieval.cpp for the implementation of this class
//

class CModelRetrievalApp : public CWinApp
{
public:
	CModelRetrievalApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModelRetrievalApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CModelRetrievalApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ModelRetrieval_H__E564C5D3_D0D7_40F3_9B06_B8FCE210154B__INCLUDED_)
