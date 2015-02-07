#if !defined(AFX_DIALOGDATABASE_H__13DF7352_D48E_4393_A47F_F1D09D1FCF56__INCLUDED_)
#define AFX_DIALOGDATABASE_H__13DF7352_D48E_4393_A47F_F1D09D1FCF56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogDataBase.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogDataBase dialog

class CDialogDataBase : public CDialog
{
// Construction
public:
	CString m_Path;
	CDialogDataBase(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogDataBase)
	enum { IDD = IDD_Dialog_DataBase };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogDataBase)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogDataBase)
	afx_msg void OnBrowes();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGDATABASE_H__13DF7352_D48E_4393_A47F_F1D09D1FCF56__INCLUDED_)
