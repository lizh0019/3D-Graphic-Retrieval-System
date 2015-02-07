#if !defined(AFX_DIALOGFEATURESELECTION_H__1D3C8093_3799_470E_9309_E53B15BA02D5__INCLUDED_)
#define AFX_DIALOGFEATURESELECTION_H__1D3C8093_3799_470E_9309_E53B15BA02D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogFeatureSelection.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogFeatureSelection dialog

class CDialogFeatureSelection : public CDialog
{
// Construction
public:
	CDialogFeatureSelection(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogFeatureSelection)
	enum { IDD = IDD_DIALOG1_Feature };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogFeatureSelection)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogFeatureSelection)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGFEATURESELECTION_H__1D3C8093_3799_470E_9309_E53B15BA02D5__INCLUDED_)
