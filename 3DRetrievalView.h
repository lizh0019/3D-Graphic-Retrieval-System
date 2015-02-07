// 3DRetrievalView.h : interface of the CMy3DRetrievalView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_3DRETRIEVALVIEW_H__CF90F3A9_9D73_43C6_81B8_EEE43C714B8A__INCLUDED_)
#define AFX_3DRETRIEVALVIEW_H__CF90F3A9_9D73_43C6_81B8_EEE43C714B8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMy3DRetrievalView : public CFormView
{
protected: // create from serialization only
	CMy3DRetrievalView();
	DECLARE_DYNCREATE(CMy3DRetrievalView)

public:
	//{{AFX_DATA(CMy3DRetrievalView)
	enum { IDD = IDD_MY3DRETRIEVAL_FORM };
	CStatic	m_QueryImage;
	CStatic	m_RetrievalImage9;
	CStatic	m_RetrievalImage8;
	CStatic	m_RetrievalImage7;
	CStatic	m_RetrievalImage6;
	CStatic	m_RetrievalImage5;
	CStatic	m_RetrievalImage4;
	CStatic	m_RetrievalImage3;
	CStatic	m_RetrievalImage2;
	CStatic	m_RetrievalImage10;
	CStatic	m_RetrievalImage1;
	CString	m_DataBasePath;
	long	m_ModelNum;
	int		m_CurrentPage;
	CString	m_QueryInfor;
	CString	m_RetrievalInfor1;
	CString	m_RetrievalInfor10;
	CString	m_RetrievalInfor2;
	CString	m_RetrievalInfor3;
	CString	m_RetrievalInfor4;
	CString	m_RetrievalInfor5;
	CString	m_RetrievalInfor6;
	CString	m_RetrievalInfor7;
	CString	m_RetrievalInfor8;
	CString	m_RetrievalInfor9;
	//}}AFX_DATA

// Attributes
public:
	CMy3DRetrievalDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy3DRetrievalView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
	unsigned char DisplayModelNum;
	void DisplayRetrieval();
	int DisplayJpegFile(char m_sOriginalFileName[MAX_PATH],int num,int displayWidth,int displayHeight);
	int SuitableWidth(int Width,int Heigth,int DisplayWidth,int DisplayHeigth);
	void DisplayInitialParameters();
	virtual ~CMy3DRetrievalView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMy3DRetrievalView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int SuitableHeight(int Width, int Heigth, int DisplayWidth, int DisplayHeigth);
};

#ifndef _DEBUG  // debug version in 3DRetrievalView.cpp
inline CMy3DRetrievalDoc* CMy3DRetrievalView::GetDocument()
   { return (CMy3DRetrievalDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DRETRIEVALVIEW_H__CF90F3A9_9D73_43C6_81B8_EEE43C714B8A__INCLUDED_)
