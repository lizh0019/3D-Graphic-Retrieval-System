// ModelRetrievalDoc.cpp : implementation of the CModelRetrievalDoc class
//

#include "stdafx.h"
#include "ModelRetrieval.h"

#include "ModelRetrievalDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModelRetrievalDoc

IMPLEMENT_DYNCREATE(CModelRetrievalDoc, CDocument)

BEGIN_MESSAGE_MAP(CModelRetrievalDoc, CDocument)
	//{{AFX_MSG_MAP(CModelRetrievalDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModelRetrievalDoc construction/destruction

CModelRetrievalDoc::CModelRetrievalDoc()
{
	// TODO: add one-time construction code here

}

CModelRetrievalDoc::~CModelRetrievalDoc()
{
}

BOOL CModelRetrievalDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CModelRetrievalDoc serialization

void CModelRetrievalDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CModelRetrievalDoc diagnostics

#ifdef _DEBUG
void CModelRetrievalDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CModelRetrievalDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CModelRetrievalDoc commands


