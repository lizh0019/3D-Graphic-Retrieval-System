// DialogDataBase.cpp : implementation file
//

#include "stdafx.h"
#include "3DRetrieval.h"
#include "DialogDataBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogDataBase dialog


CDialogDataBase::CDialogDataBase(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogDataBase::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogDataBase)
	m_Path = _T("");
	//}}AFX_DATA_INIT
}


void CDialogDataBase::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogDataBase)
	DDX_Text(pDX, IDC_EDIT_DataBase, m_Path);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogDataBase, CDialog)
	//{{AFX_MSG_MAP(CDialogDataBase)
	ON_BN_CLICKED(IDC_Browes, OnBrowes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogDataBase message handlers

void CDialogDataBase::OnBrowes() 
{
	// TODO: Add your control notification handler code here
	CString str;
	BROWSEINFO bi;
	char name[MAX_PATH];
	ZeroMemory(&bi,sizeof(BROWSEINFO));
	bi.hwndOwner=GetSafeHwnd();
	bi.pszDisplayName=name;
	bi.lpszTitle="Select Folder";
	//	bi.ulFlags=BIF_USENEWUI;
	LPITEMIDLIST idl=SHBrowseForFolder(&bi);
	if(idl==NULL)return;
	SHGetPathFromIDList(idl,str.GetBuffer(MAX_PATH));
	str.ReleaseBuffer();
	this->m_Path=str;
	if(str.GetAt(str.GetLength()-1)!='\\')
		this->m_Path+="\\";
	UpdateData(FALSE);
	
}
