// ModelRetrievalDoc.h : interface of the CModelRetrievalDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ModelRetrievalDOC_H__A3C01076_5828_4198_92A1_3EC69A45AB80__INCLUDED_)
#define AFX_ModelRetrievalDOC_H__A3C01076_5828_4198_92A1_3EC69A45AB80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CModelRetrievalDoc : public CDocument
{
protected: // create from serialization only
	CModelRetrievalDoc();
	DECLARE_DYNCREATE(CModelRetrievalDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModelRetrievalDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CModelRetrievalDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CModelRetrievalDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ModelRetrievalDOC_H__A3C01076_5828_4198_92A1_3EC69A45AB80__INCLUDED_)
