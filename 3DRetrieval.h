// 3DRetrieval.h : main header file for the 3DRETRIEVAL application
//

#if !defined(AFX_3DRETRIEVAL_H__7903C7CD_FC32_463C_8769_5C53734CEC6F__INCLUDED_)
#define AFX_3DRETRIEVAL_H__7903C7CD_FC32_463C_8769_5C53734CEC6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMy3DRetrievalApp:
// See 3DRetrieval.cpp for the implementation of this class
//

class CMy3DRetrievalApp : public CWinApp
{
public:
	CMy3DRetrievalApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy3DRetrievalApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMy3DRetrievalApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DRETRIEVAL_H__7903C7CD_FC32_463C_8769_5C53734CEC6F__INCLUDED_)
