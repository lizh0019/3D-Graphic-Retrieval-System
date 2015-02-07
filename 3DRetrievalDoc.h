// 3DRetrievalDoc.h : interface of the CMy3DRetrievalDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_3DRETRIEVALDOC_H__B8420288_06A2_4792_9884_066786AF804D__INCLUDED_)
#define AFX_3DRETRIEVALDOC_H__B8420288_06A2_4792_9884_066786AF804D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RetrievalMethod.h"
#include "jpeg.h"


class CMy3DRetrievalDoc : public CDocument
{
public: // create from serialization only
	CMy3DRetrievalDoc();
	DECLARE_DYNCREATE(CMy3DRetrievalDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy3DRetrievalDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	void ExtractQueryModFeature_D1();
	void DataBaseFeatureExtractD1();
	void GLUTMainLoop();
	void GLUTInit(int *argc, char **argv);
	void DataBaseFeatureExtract();
	int * Featurevertices();
	int * Featurevertices_D1();
	int * bins1024();
	int * binsD1_1024();
	BOOL ExtractQueryModFeature();
	int ReadQueryImage(CString ImagePathName,PFEATUREVECTOR FeatureVector);
	unsigned char m_StandardBmpInfo[1078];
	unsigned char m_StandardBmpInfoc[54];
	//for the whole system;
	//current directory
	char m_CurrentDirectory[_MAX_PATH];
	BOOL Success;

	//The query image info(including size,features)
	FEATUREVECTOR m_vQueryFeatureVector;

	//++++++++For query menu++++++++++++
	//The global memory for query model image
	HGLOBAL Imagehg;
	unsigned char *m_ModelImageFile;//Query Model image File
	BYTE *m_bQueryImageData;//RGB data for query image
	//***********************************

	//*******For the display*************;
	void QueryVariableInitial();
	CString m_sQueryModelPath;
	CString m_sQueryImagePath;
	BOOL m_bQueryModelChanged;
	BOOL m_bFileOpen;
	BOOL m_bDisplayRetrieval;
	void WholeDataProcessing();
	void DataBaseVariableinitialize();
	int display_num[20];

	//for the retrieval of the files in the files. 
	BOOL GetApproximateImagesNumber(CString sPath,long int *number);
	CString m_OldDataBasePath;  //Old DataBase directory and Manly directory;
	BOOL m_DataBasePathChange;  //If the DataBase directory Changed?
	long  m_TotalNumMedol;   //Total mumble of Models( or jpeg files);
	BOOL m_DataBaseOpened;  // If the DataBaseOpened;
	char openfilename[50];
	CString m_saModelfilename[MAX_MODEL_NUMBER];
	CString m_saModelimagename[MAX_MODEL_NUMBER];
	unsigned char m_dDisplayNumber;  //Display image number for current page 0-16
	int m_ipage;

    //**********for the feature extracted***************************;
	int *bins;   // for 1024 bins
	int *histogram;  // for 64 vertices.
	BOOL m_bDataBaseFeatureExtracted; // is DataBase feature Extracted?
	BOOL m_bQueryModelFeatrueEXtracted; // is Model feature Extracted?
	BOOL m_bQueryModelFeatrueEXtracted_D1; // is the Model's D1 Feature extracted?
	CString m_sDataBaseFeatrue[MAX_MODEL_NUMBER];
	CString m_sDataBaseFeatrue_D1[MAX_MODEL_NUMBER];
	int m_iRetrievalMethod; //  ..=0 for nothing;
							//	..=1 for D2 Feature;
							//  ..=2 for D1 Feature;
							//  ..=3 for D3 Feature;
							//  ..=4 for A3 Feature;
							//  ..=5 for My own-Feature;

	CRetrievalMethod MyRetrievalMethod;
	

	virtual ~CMy3DRetrievalDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMy3DRetrievalDoc)
	afx_msg void OnDateBaseSelectDataBase();
	afx_msg void OnFileOpen3dmodel();
	afx_msg void OnFILEDisplaytModel();
	afx_msg void OnStartquery();
	afx_msg void OnSTATICRetrievalResults1();
	afx_msg void OnSTATICRetrievalResults2();
	afx_msg void OnSTATICRetrievalResults3();
	afx_msg void OnSTATICRetrievalResults4();
	afx_msg void OnFileFeatureEXtracting();
	afx_msg void OnDataBaseFeatrueExtract();
	afx_msg void OnSTATICRetrievalResults5();
	afx_msg void OnSTATICRetrievalResults6();
	afx_msg void OnSTATICRetrievalResults7();
	afx_msg void OnSTATICRetrievalResults8();
	afx_msg void OnSTATICRetrievalResults9();
	afx_msg void OnSTATICRetrievalResults10();
	afx_msg void OnPreviouspage();
	afx_msg void OnNextpage();
	afx_msg void OnQueryFeatureD2();
	afx_msg void OnFeatureD1();
	afx_msg void OnFeatureD3();
	afx_msg void OnFeatureA3();
	afx_msg void OnFeatureMyOwen();
	afx_msg void OnDateBaseFeatureExtractD1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void OpenStandardBMPHeader();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DRETRIEVALDOC_H__B8420288_06A2_4792_9884_066786AF804D__INCLUDED_)





















