// ModelRetrievalView.h : interface of the CModelRetrievalView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ModelRetrievalVIEW_H__48B5165E_239E_49B8_9F92_047F98940B12__INCLUDED_)
#define AFX_ModelRetrievalVIEW_H__48B5165E_239E_49B8_9F92_047F98940B12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Classes\PictCtrl.h"
#include "LIB\CIMAGE.H"	// Added by ClassView
#include "ImageBaseManage.h"
#include "RetrievalControl.h"
class CModelRetrievalView : public CFormView
{
protected: // create from serialization only
	CModelRetrievalView();
	DECLARE_DYNCREATE(CModelRetrievalView)
protected:
	bool m_bIntilization;
	CPictureCtrl *m_pCPictureCtrl[15];
	int *m_piRelevance[15];
	CString *m_psSimilarity[15];
	CString allpath[25]; // save all paths of the sorted results 
	CString queryname;
	CString modelnumber;
	CString databasepath;

public:
	//{{AFX_DATA(CModelRetrievalView)
	enum { IDD = IDD_ModelRetrieval_FORM };
	CButton	m_cFeedbackControl;
	CButton	m_CRadio1;
	CButton	m_cShouldRetrieval;
	CButton	m_cHomePage;
	CButton	m_cPrePage;
	CButton	m_cNextPage;
	CPictureCtrl	m_cRetrievalResult9;
	CPictureCtrl	m_cRetrievalResult8;
	CPictureCtrl	m_cRetrievalResult7;
	CPictureCtrl	m_cRetrievalResult6;
	CPictureCtrl	m_cRetrievalResult5;
	CPictureCtrl	m_cRetrievalResult4;
	CPictureCtrl	m_cRetrievalResult3;
	CPictureCtrl	m_cRetrievalResult2;
	CPictureCtrl	m_cRetrievalResult15;
	CPictureCtrl	m_cRetrievalResult14;
	CPictureCtrl	m_cRetrievalResult13;
	CPictureCtrl	m_cRetrievalResult12;
	CPictureCtrl	m_cRetrievalResult11;
	CPictureCtrl	m_cRetrievalResult10;
	CPictureCtrl	m_cRetrievalResult1;  
	CPictureCtrl	m_cSampleImage;  //the key image
	int		m_iRelevance_1;
	int		m_iRelevance_2;
	int		m_iRelevance_3;
	int		m_iRelevance_4;
	int		m_iRelevance_5;
	int		m_iRelevance_6;
	int		m_iRelevance_7;
	int		m_iRelevance_8;
	int		m_iRelevance_9;
	int		m_iRelevance_10;
	int		m_iRelevance_11;
	int		m_iRelevance_12;
	int		m_iRelevance_13;
	int		m_iRelevance_14;
	int		m_iRelevance_15;
	CString	m_sSimilarity_1;
	CString	m_sSimilarity_10;
	CString	m_sSimilarity_11;
	CString	m_sSimilarity_12;
	CString	m_sSimilarity_13;
	CString	m_sSimilarity_14;
	CString	m_sSimilarity_15;
	CString	m_sSimilarity_2;
	CString	m_sSimilarity_3;
	CString	m_sSimilarity_4;
	CString	m_sSimilarity_5;
	CString	m_sSimilarity_6;
	CString	m_sSimilarity_7;
	CString	m_sSimilarity_8;
	CString	m_sSimilarity_9;
	double	m_dThreshold;
	CString	m_sNumberImageDataBase;
	CString	m_sSampleID;
	CString	m_sNumberResult;
	CString	m_sImagePath;
	CString	m_sStudyTimes;
	CString	m_sTotalPage;
	CString	m_sCurrentPage;
	double	m_dRecall;
	double	m_dPrecise;
	float	m_fPR;
	//}}AFX_DATA

// Attributes
public:
	CModelRetrievalDoc* GetDocument();

protected:
	CImageBaseManage m_cImageBasemanage;
// Operations
public:
	bool m_bCanFeedback;
	CString m_sSampleImageFullName;
	CString m_sQueryName;//+
	CString m_sQueryFeature;//+
	CString m_sFeatureFolder;//+ path of the feature file folder
	CString m_sThumbnailPath;//+ path of the thunbnail
	CString m_sDone;//+
	CString strTemp;//+
	CString m_simputvector;//+
	CString m_sImageBasePath;
	CRetrievalControl m_cRetrievalControl;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModelRetrievalView)
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
	void UpdateDisplay();
	virtual ~CModelRetrievalView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	void updateRelevanceData();
	void DisplayResult();
	void ClearDisplayResult();
	//{{AFX_MSG(CModelRetrievalView)
	afx_msg void OnButtonOpensample();
	afx_msg void OnButtonImagedatabase();
	afx_msg void OnButtonRetrieval();
	afx_msg void OnButtonNextpage();
	afx_msg void OnButtonPrepage();
	afx_msg void OnButtonHomepage();
	afx_msg void OnChangeThreshold();
	afx_msg void OnButtonRelevancefeedback();
	afx_msg void OnButtonParameter();
	afx_msg void OnGetinformatino();
	afx_msg void OnRetrievalMethodTest();
	afx_msg void OnDataSampleid();
	afx_msg void OnButtonOpenoffpolygon();
	afx_msg void OnButtonOpenoffpoints();
	afx_msg void OnButtonOpenofflines();
	afx_msg void OnButtonOpenofftriangles();
	afx_msg void OnButtonDone();
	afx_msg void OnButtonHistogram();
	afx_msg void OnButtonDtwo();
	afx_msg void OnButtonSelectdatabase();
	afx_msg void OnButtonRetrieve();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ModelRetrievalView.cpp
inline CModelRetrievalDoc* CModelRetrievalView::GetDocument()
   { return (CModelRetrievalDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ModelRetrievalVIEW_H__48B5165E_239E_49B8_9F92_047F98940B12__INCLUDED_)
