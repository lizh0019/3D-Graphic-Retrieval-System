#if !defined(AFX_THREED_H__10B94B1D_F58E_4DCD_89C7_6F9637E487E9__INCLUDED_)
#define AFX_THREED_H__10B94B1D_F58E_4DCD_89C7_6F9637E487E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThreeD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ThreeD document
extern short int stripedata[100][100][3];
extern short int data[10000][3];
extern long float tridata[10000][3];
extern long float mod[10000][3];
extern long float nose[10000][3];
extern long float stripemode[100][100][3];
extern int numper[100];
extern int numstripe[1];
extern int pointnumber;
extern int minx;
extern int wholeshow;
extern int NoseShow;
extern int PlaneShow;
extern int planepointnum;
extern int stripeshow;
extern int nosenum;
class ThreeD : public CDocument
{
//protected:
public:
	ThreeD();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(ThreeD)

// Attributes
public:
	bool opensuccess;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ThreeD)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	char openfacename[30];
	CString openfilename;
	int namelength;
	bool t_LoadSuccess;
	CString t_filename;
	bool Load3DFaceDialog();
	bool Load3D_RMA(CString filename);

	BOOL Save3D_RMAData(int pointnumber);
    CString m_PathName;
	BOOL Read3D_OFF(CString& filename);
	virtual ~ThreeD();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(ThreeD)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THREED_H__10B94B1D_F58E_4DCD_89C7_6F9637E487E9__INCLUDED_)
