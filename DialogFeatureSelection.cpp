// DialogFeatureSelection.cpp : implementation file
//

#include "stdafx.h"
#include "3DRetrieval.h"
#include "DialogFeatureSelection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogFeatureSelection dialog


CDialogFeatureSelection::CDialogFeatureSelection(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogFeatureSelection::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogFeatureSelection)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogFeatureSelection::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogFeatureSelection)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogFeatureSelection, CDialog)
	//{{AFX_MSG_MAP(CDialogFeatureSelection)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogFeatureSelection message handlers
