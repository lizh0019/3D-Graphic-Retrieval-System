// ModelRetrievalView.cpp : implementation of the CModelRetrievalView class
//

#include "stdafx.h"
#include "ModelRetrieval.h"

#include "ModelRetrievalDoc.h"
#include "ModelRetrievalView.h"
#include "DialogBase.h"
#include "DialogParamentSet.h"
#include <math.h>  // "floor", "ceil"
#include <stdlib.h> // "rand" 
#include <stdio.h>  // "rand"
//#include <time.h>   
#include <Shlobj.h> // for select a file folder



#include "offviewer.cpp"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModelRetrievalView

IMPLEMENT_DYNCREATE(CModelRetrievalView, CFormView)

BEGIN_MESSAGE_MAP(CModelRetrievalView, CFormView)
	//{{AFX_MSG_MAP(CModelRetrievalView)
	ON_BN_CLICKED(IDC_BUTTON_OPENSAMPLE, OnButtonOpensample)
	ON_BN_CLICKED(IDC_BUTTON_IMAGEDATABASE, OnButtonImagedatabase)
	ON_BN_CLICKED(IDC_BUTTON_RETRIEVAL, OnButtonRetrieval)
	ON_BN_CLICKED(IDC_BUTTON_NEXTPAGE, OnButtonNextpage)
	ON_BN_CLICKED(IDC_BUTTON_PREPAGE, OnButtonPrepage)
	ON_BN_CLICKED(IDC_BUTTON_HOMEPAGE, OnButtonHomepage)
	ON_EN_CHANGE(IDC_THRESHOLD, OnChangeThreshold)
	ON_BN_CLICKED(IDC_BUTTON_RELEVANCEFEEDBACK, OnButtonRelevancefeedback)
	ON_BN_CLICKED(IDC_BUTTON_PARAMETER, OnButtonParameter)
	ON_COMMAND(IDC_GETINFORMATINO, OnGetinformatino)
	ON_COMMAND(IDC_RETRIEVAL_METHOD_TEST, OnRetrievalMethodTest)
	ON_BN_CLICKED(IDC_BUTTON_OPENOFFPOLYGON, OnButtonOpenoffpolygon)
	ON_BN_CLICKED(IDC_BUTTON_OPENOFFPOINTS, OnButtonOpenoffpoints)
	ON_BN_CLICKED(IDC_BUTTON_OPENOFFLINES, OnButtonOpenofflines)
	ON_BN_CLICKED(IDC_BUTTON_OPENOFFTRIANGLES, OnButtonOpenofftriangles)
	ON_BN_CLICKED(IDC_BUTTON_DONE, OnButtonDone)
	ON_BN_CLICKED(IDC_BUTTON_HISTOGRAM, OnButtonHistogram)
	ON_BN_CLICKED(IDC_BUTTON_DTWO, OnButtonDtwo)
	ON_BN_CLICKED(IDC_BUTTON_SELECTDATABASE, OnButtonSelectdatabase)
	ON_BN_CLICKED(IDC_BUTTON_RETRIEVE, OnButtonRetrieve)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModelRetrievalView construction/destruction

CModelRetrievalView::CModelRetrievalView()
	: CFormView(CModelRetrievalView::IDD)
{
	//{{AFX_DATA_INIT(CModelRetrievalView)
	m_iRelevance_1 = -1;
	m_iRelevance_2 = -1;
	m_iRelevance_3 = -1;
	m_iRelevance_4 = -1;
	m_iRelevance_5 = -1;
	m_iRelevance_6 = -1;
	m_iRelevance_7 = -1;
	m_iRelevance_8 = -1;
	m_iRelevance_9 = -1;
	m_iRelevance_10 = -1;
	m_iRelevance_11 = -1;
	m_iRelevance_12 = -1;
	m_iRelevance_13 = -1;
	m_iRelevance_14 = -1;
	m_iRelevance_15 = -1;
	m_sSimilarity_1 = _T("");
	m_sSimilarity_10 = _T("");
	m_sSimilarity_11 = _T("");
	m_sSimilarity_12 = _T("");
	m_sSimilarity_13 = _T("");
	m_sSimilarity_14 = _T("");
	m_sSimilarity_15 = _T("");
	m_sSimilarity_2 = _T("");
	m_sSimilarity_3 = _T("");
	m_sSimilarity_4 = _T("");
	m_sSimilarity_5 = _T("");
	m_sSimilarity_6 = _T("");
	m_sSimilarity_7 = _T("");
	m_sSimilarity_8 = _T("");
	m_sSimilarity_9 = _T("");	
	m_dThreshold = 0.5;
	m_sNumberImageDataBase = _T("");
	m_sSampleID = _T("");
	m_sNumberResult = _T("");
	m_sImagePath = _T("");
	m_sStudyTimes = _T("");
	m_sTotalPage = _T("");
	m_sCurrentPage = _T("");
	m_dRecall = 0.0;
	m_dPrecise = 0.0;
	m_fPR = 0.0f;
	//}}AFX_DATA_INIT
	// TODO: add construction code here
		//initilaze the point 
	
	m_pCPictureCtrl[0]=&m_cRetrievalResult1;
	m_pCPictureCtrl[1]=&m_cRetrievalResult2;
	m_pCPictureCtrl[2]=&m_cRetrievalResult3;
	m_pCPictureCtrl[3]=&m_cRetrievalResult4;
	m_pCPictureCtrl[4]=&m_cRetrievalResult5;
	m_pCPictureCtrl[5]=&m_cRetrievalResult6;
	m_pCPictureCtrl[6]=&m_cRetrievalResult7;
	m_pCPictureCtrl[7]=&m_cRetrievalResult8;
	m_pCPictureCtrl[8]=&m_cRetrievalResult9;
	m_pCPictureCtrl[9]=&m_cRetrievalResult10;
	m_pCPictureCtrl[10]=&m_cRetrievalResult11;
	m_pCPictureCtrl[11]=&m_cRetrievalResult12;
	m_pCPictureCtrl[12]=&m_cRetrievalResult13;
	m_pCPictureCtrl[13]=&m_cRetrievalResult14;
	m_pCPictureCtrl[14]=&m_cRetrievalResult15;

	m_piRelevance[0]=&m_iRelevance_1;
	m_piRelevance[1]=&m_iRelevance_2;
	m_piRelevance[2]=&m_iRelevance_3;
	m_piRelevance[3]=&m_iRelevance_4;
	m_piRelevance[4]=&m_iRelevance_5;
	m_piRelevance[5]=&m_iRelevance_6;
	m_piRelevance[6]=&m_iRelevance_7;
	m_piRelevance[7]=&m_iRelevance_8;
	m_piRelevance[8]=&m_iRelevance_9;
	m_piRelevance[9]=&m_iRelevance_10;
	m_piRelevance[10]=&m_iRelevance_11;
	m_piRelevance[11]=&m_iRelevance_12;
	m_piRelevance[12]=&m_iRelevance_13;
    m_piRelevance[13]=&m_iRelevance_14;
    m_piRelevance[14]=&m_iRelevance_15;


	//
	m_psSimilarity[0]=&m_sSimilarity_1;
	m_psSimilarity[1]=&m_sSimilarity_2;
	m_psSimilarity[2]=&m_sSimilarity_3;
	m_psSimilarity[3]=&m_sSimilarity_4;
	m_psSimilarity[4]=&m_sSimilarity_5;
	m_psSimilarity[5]=&m_sSimilarity_6;
	m_psSimilarity[6]=&m_sSimilarity_7;
	m_psSimilarity[7]=&m_sSimilarity_8;
	m_psSimilarity[8]=&m_sSimilarity_9;
	m_psSimilarity[9]=&m_sSimilarity_10;
	m_psSimilarity[10]=&m_sSimilarity_11;
	m_psSimilarity[11]=&m_sSimilarity_12;
	m_psSimilarity[12]=&m_sSimilarity_13;
	m_psSimilarity[13]=&m_sSimilarity_14;
	m_psSimilarity[14]=&m_sSimilarity_15;

	m_bIntilization=false;
	m_bCanFeedback=false;
}

CModelRetrievalView::~CModelRetrievalView()
{
}

void CModelRetrievalView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModelRetrievalView)
	DDX_Control(pDX, IDC_BUTTON_RELEVANCEFEEDBACK, m_cFeedbackControl);
	DDX_Control(pDX, IDC_RADIO1, m_CRadio1);
	DDX_Control(pDX, IDC_BUTTON_RETRIEVAL, m_cShouldRetrieval);
	DDX_Control(pDX, IDC_BUTTON_HOMEPAGE, m_cHomePage);
	DDX_Control(pDX, IDC_BUTTON_PREPAGE, m_cPrePage);
	DDX_Control(pDX, IDC_BUTTON_NEXTPAGE, m_cNextPage);
	DDX_Control(pDX, IDC_RESULTE9, m_cRetrievalResult9);
	DDX_Control(pDX, IDC_RESULTE8, m_cRetrievalResult8);
	DDX_Control(pDX, IDC_RESULTE7, m_cRetrievalResult7);
	DDX_Control(pDX, IDC_RESULTE6, m_cRetrievalResult6);
	DDX_Control(pDX, IDC_RESULTE5, m_cRetrievalResult5);
	DDX_Control(pDX, IDC_RESULTE4, m_cRetrievalResult4);
	DDX_Control(pDX, IDC_RESULTE3, m_cRetrievalResult3);
	DDX_Control(pDX, IDC_RESULTE2, m_cRetrievalResult2);
	DDX_Control(pDX, IDC_RESULTE15, m_cRetrievalResult15);
	DDX_Control(pDX, IDC_RESULTE14, m_cRetrievalResult14);
	DDX_Control(pDX, IDC_RESULTE13, m_cRetrievalResult13);
	DDX_Control(pDX, IDC_RESULTE12, m_cRetrievalResult12);
	DDX_Control(pDX, IDC_RESULTE11, m_cRetrievalResult11);
	DDX_Control(pDX, IDC_RESULTE10, m_cRetrievalResult10);
	DDX_Control(pDX, IDC_RESULTE1, m_cRetrievalResult1);
	DDX_Control(pDX, IDC_SAMPLEIMAGE_PICTURE, m_cSampleImage);
	DDX_Radio(pDX, IDC_RADIO1, m_iRelevance_1);
	DDX_Radio(pDX, IDC_RADIO4, m_iRelevance_2);
	DDX_Radio(pDX, IDC_RADIO7, m_iRelevance_3);
	DDX_Radio(pDX, IDC_RADIO10, m_iRelevance_4);
	DDX_Radio(pDX, IDC_RADIO13, m_iRelevance_5);
	DDX_Radio(pDX, IDC_RADIO16, m_iRelevance_6);
	DDX_Radio(pDX, IDC_RADIO19, m_iRelevance_7);
	DDX_Radio(pDX, IDC_RADIO22, m_iRelevance_8);
	DDX_Radio(pDX, IDC_RADIO25, m_iRelevance_9);
	DDX_Radio(pDX, IDC_RADIO28, m_iRelevance_10);
	DDX_Radio(pDX, IDC_RADIO31, m_iRelevance_11);
	DDX_Radio(pDX, IDC_RADIO34, m_iRelevance_12);
	DDX_Radio(pDX, IDC_RADIO37, m_iRelevance_13);
	DDX_Radio(pDX, IDC_RADIO40, m_iRelevance_14);
	DDX_Radio(pDX, IDC_RADIO43, m_iRelevance_15);
	DDX_Text(pDX, IDC_DATA_SIMILARITY, m_sSimilarity_1);
	DDX_Text(pDX, IDC_DATA_SIMILARITY10, m_sSimilarity_10);
	DDX_Text(pDX, IDC_DATA_SIMILARITY11, m_sSimilarity_11);
	DDX_Text(pDX, IDC_DATA_SIMILARITY12, m_sSimilarity_12);
	DDX_Text(pDX, IDC_DATA_SIMILARITY13, m_sSimilarity_13);
	DDX_Text(pDX, IDC_DATA_SIMILARITY14, m_sSimilarity_14);
	DDX_Text(pDX, IDC_DATA_SIMILARITY15, m_sSimilarity_15);
	DDX_Text(pDX, IDC_DATA_SIMILARITY2, m_sSimilarity_2);
	DDX_Text(pDX, IDC_DATA_SIMILARITY3, m_sSimilarity_3);
	DDX_Text(pDX, IDC_DATA_SIMILARITY4, m_sSimilarity_4);
	DDX_Text(pDX, IDC_DATA_SIMILARITY5, m_sSimilarity_5);
	DDX_Text(pDX, IDC_DATA_SIMILARITY6, m_sSimilarity_6);
	DDX_Text(pDX, IDC_DATA_SIMILARITY7, m_sSimilarity_7);
	DDX_Text(pDX, IDC_DATA_SIMILARITY8, m_sSimilarity_8);
	DDX_Text(pDX, IDC_DATA_SIMILARITY9, m_sSimilarity_9);
	DDX_Text(pDX, IDC_THRESHOLD, m_dThreshold);
	DDV_MinMaxDouble(pDX, m_dThreshold, 0., 1.);
	DDX_Text(pDX, IDC_DATA_IMAGEDATABASESIZE, m_sNumberImageDataBase);
	DDX_Text(pDX, IDC_DATA_SAMPLEID, m_sSampleID);
	DDX_Text(pDX, IDC_DATA_RESULTNUMBER, m_sNumberResult);
	DDX_Text(pDX, IDC_DATA_IMAGERETRIEVALTIME, m_sImagePath);
	DDX_Text(pDX, IDC_DATA_STUDY_TIMES, m_sStudyTimes);
	DDX_Text(pDX, IDC_DATA_TOTALPAGES, m_sTotalPage);
	DDX_Text(pDX, IDC_DATA_CURRENTPAGE, m_sCurrentPage);
	DDX_Text(pDX, IDC_RECALL, m_dRecall);
	DDX_Text(pDX, IDC_PRECISE, m_dPrecise);
	DDX_Text(pDX, IDC_EDIT_PR, m_fPR);
	//}}AFX_DATA_MAP
}

BOOL CModelRetrievalView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CModelRetrievalView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CModelRetrievalView printing

BOOL CModelRetrievalView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CModelRetrievalView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CModelRetrievalView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CModelRetrievalView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CModelRetrievalView diagnostics

#ifdef _DEBUG
void CModelRetrievalView::AssertValid() const
{
	CFormView::AssertValid();
}

void CModelRetrievalView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CModelRetrievalDoc* CModelRetrievalView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CModelRetrievalDoc)));
	return (CModelRetrievalDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
//open the thumbnail of query
void CModelRetrievalView::OnButtonOpensample() 
{
	// TODO: Add your control notification handler code here

	char BASED_CODE szFilter[]="DataBase Files(*.jpg)|*.jpg|All Files(*.*)|*.*||";
	CFileDialog m_ldFile(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
	m_ldFile.m_ofn.lpstrTitle="Open thumbnail of query model";
	
	if(m_ldFile.DoModal()!=IDOK)
	{	
		return;
	}
	
	//load for display
	if(!this->m_cSampleImage.LoadImage(m_ldFile.GetPathName()))
	{
		AfxMessageBox("Query Thumbnail Error",MB_OK);
		m_cSampleImage.LoadImage(m_sSampleImageFullName);
		return;
	}

	//get the file name
	this->m_sSampleImageFullName=m_ldFile.GetPathName();

	// display information
	this->m_sSampleID=m_ldFile.GetFileTitle(); // display the query name
	queryname=m_sSampleID;
		
	databasepath=m_ldFile.GetPathName(); // display the modelbase path
	this->m_sImagePath=databasepath.Left(databasepath.Find("\\feature"));

	
	m_sFeatureFolder=m_sSampleImageFullName.Left(m_sSampleImageFullName.Find("\\m")); 
	if(m_sFeatureFolder.Right(1) != "\\")
		m_sFeatureFolder += "\\";
	m_sFeatureFolder += "*.txt";
	CFileFind file;
	int number=0;
	BOOL bcount = file.FindFile(m_sFeatureFolder);
	while(bcount)
	{
		number +=1;
		bcount = file.FindNextFile();
	}
	char ht[20]; 
	itoa(number,ht,10); 
    modelnumber = ht;
	this->m_sNumberImageDataBase=ht;// display the number of models

	this->UpdateData(false);//output the paraments
	Invalidate();//output the retrieval results
}


void CModelRetrievalView::OnButtonSelectdatabase() 
{
	// TODO: Add your control notification handler code here
	/*select model base, thumbnail base, feature base*/


}


//load or create an imagebase
void CModelRetrievalView::OnButtonImagedatabase() 
{
	// TODO: Add your control notification handler code here
	CDialogBase dialogbase;
	CString Path;  //the path
	int choose;   //the choose

	if(dialogbase.DoModal()!=IDOK)		return;

	Path=dialogbase.m_sPathName;  //get the path
	choose=dialogbase.imagebasechoose;  //get the choose
	
	//start
	BeginWaitCursor();
	m_bCanFeedback=false;
//	this->UpdateWindow();
	switch(choose) 
	{
	case 1://choose a base exist
		if (m_cImageBasemanage.LoadImageBase(Path)==false) 
		{
			MessageBox("Load Image Base error","System information",MB_OK);
			return;
		}
		break;
	case 2://creat a new base
		if (m_cImageBasemanage.CreatImageBase(Path)==false)
		{
			MessageBox("Create error,file exist or read error!","System information",MB_OK);
			return;
		}
		
		break;
	default:  
		break;
	}
	//end,get the path
	m_sImageBasePath=Path;	

	//read the path
	m_cRetrievalControl.ReadImageBase(m_sImageBasePath);
	EndWaitCursor();
	this->DisplayResult();
	
}



void CModelRetrievalView::OnButtonRetrieve() 
{
	// TODO: Add your control notification handler code here
	/************************************************************************/
	/* (1) get query feature in the feature database                        */ 
	/* (2) compute distance between the query feature and other features    */ 
	/* (3) sort these distance in ascending order                           */ 
	/* (4) display the thumbnails according to the sorted distance          */ 
	/************************************************************************/
	// (1) get a feature in the feature database  
	CString queryfeapath;
	queryfeapath = m_sSampleImageFullName.Left(m_sSampleImageFullName.Find("\.jpg"));
	queryfeapath += "\.txt";
	m_sQueryFeature = queryfeapath; 

	// read feature data into array    
	CFile mFile;
	if(mFile.Open(m_sQueryFeature,CFile::modeRead)==0)
	{
		return;
	}

	DWORD nFileSize = mFile.GetLength();
	int queryfea[500];
	mFile.Seek(0L,SEEK_SET);
	for(int k=0;;k++)
	{
		DWORD pos=mFile.GetPosition();
		if(pos==nFileSize) 
			break; // if the end of the file, break.
		char temp[20];
		queryfea[k]=0;
		for(int m=0;;m++)
		{
			mFile.Read((char*)temp+m,sizeof(char));
			if(temp[m]=='\n')  //m位为'\n'; m-1位为个位
			{				
				if (m==1)
					queryfea[k]=temp[m-1]-48;
				else if (m==2)
					queryfea[k]=temp[m-1]-48 + (temp[m-2]-48)*10;
				else if (m==3)
					queryfea[k]=temp[m-1]-48 + (temp[m-2]-48)*10 + (temp[m-3]-48)*100;
				else if (m==4)
					queryfea[k]=temp[m-1]-48 + (temp[m-2]-48)*10 + (temp[m-3]-48)*100 + (temp[m-4]-48)*1000;
				else if (m==5)
					queryfea[k]=temp[m-1]-48 + (temp[m-2]-48)*10 + (temp[m-3]-48)*100 + (temp[m-4]-48)*1000 + (temp[m-5]-48)*10000;
				else if (m==6)
					queryfea[k]=temp[m-1]-48 + (temp[m-2]-48)*10 + (temp[m-3]-48)*100 + (temp[m-4]-48)*1000 + (temp[m-5]-48)*10000 + (temp[m-6]-48)*100000;
				else if (m==7)
					queryfea[k]=temp[m-1]-48 + (temp[m-2]-48)*10 + (temp[m-3]-48)*100 + (temp[m-4]-48)*1000 + (temp[m-5]-48)*10000 + (temp[m-6]-48)*100000 + (temp[m-7]-48)*1000000;
				else 
					MessageBox("load query feature error1","System information",MB_OK);
				break;
			}
		}
	}
	mFile.Close();
	//test show query feature data
	//for (int ii=490; ii<500; ii++)
	//{
	//	CString test;
	//	test.Format("queryfea[%d]=%d",ii,queryfea[ii]);
	//	AfxMessageBox(test);
 	//}


	// get path of the feature folder
	CString str = m_sQueryFeature;	
	m_sFeatureFolder = str.Left(str.Find("\\m"));  //m_sFeatureFolder = str.Left(64); 
	//CString test;
	//test.Format("path=%s",m_sFeatureFolder);
    //AfxMessageBox(test);


	// read all features from the feature folder	
	if(m_sFeatureFolder.Right(1) != "\\")
		m_sFeatureFolder += "\\";
	m_sFeatureFolder += "*.txt";
	CFileFind file;
	BOOL bContinueNumber = file.FindFile(m_sFeatureFolder);
	int feaindex = 0;
	double querydis[96];
	double element[500];
	CString featurename[96];
	while(bContinueNumber)
	{
		feaindex = feaindex+bContinueNumber;
		bContinueNumber = file.FindNextFile();
		CString featurepath = file.GetFilePath(); // get the path of a feaure file
		featurename[feaindex] = file.GetFileTitle();//save name of the feature
		
		CFile mFile;
		if(mFile.Open(featurepath,CFile::modeRead)==0) return;
		
		DWORD nFileSize = mFile.GetLength();
		int feature[500];
		mFile.Seek(0L,SEEK_SET);
		for(int k=0;;k++)
		{
			DWORD pos=mFile.GetPosition();
			if(pos==nFileSize)
				break; // if the end of the file, break.
			char temp[20];
			feature[k]=0;
			for(int m=0;;m++)
			{
				mFile.Read((char*)temp+m,sizeof(char));
				if(temp[m]=='\n')  //m位为'\n'; m-1位为个位
				{				
					if (m==1)
						feature[k]=temp[m-1]-48;
					else if (m==2)
						feature[k]=temp[m-1]-48 + (temp[m-2]-48)*10;
					else if (m==3)
						feature[k]=temp[m-1]-48 + (temp[m-2]-48)*10 + (temp[m-3]-48)*100;
					else if (m==4)
						feature[k]=temp[m-1]-48 + (temp[m-2]-48)*10 + (temp[m-3]-48)*100 + (temp[m-4]-48)*1000;
					else if (m==5)
						feature[k]=temp[m-1]-48 + (temp[m-2]-48)*10 + (temp[m-3]-48)*100 + (temp[m-4]-48)*1000 + (temp[m-5]-48)*10000;
					else if (m==6)
						feature[k]=temp[m-1]-48 + (temp[m-2]-48)*10 + (temp[m-3]-48)*100 + (temp[m-4]-48)*1000 + (temp[m-5]-48)*10000 + (temp[m-6]-48)*100000;
					else if (m==7)
						feature[k]=temp[m-1]-48 + (temp[m-2]-48)*10 + (temp[m-3]-48)*100 + (temp[m-4]-48)*1000 + (temp[m-5]-48)*10000 + (temp[m-6]-48)*100000 + (temp[m-7]-48)*1000000;
					else 
						MessageBox("load feature error2","System information",MB_OK);
					break;
				}
			}
		}
		mFile.Close();
//		for (int i=0; i<10; i++)
//		{
//			CString test;
//			test.Format("feature[%d]=%d",i,feature[i]);
//			AfxMessageBox(test);
// 		}	

		// compute distance between the query feature and all features
		querydis[feaindex]=0;
		for (int j=0; j<500; j++)
		{
			element[j] = (queryfea[j]-feature[j])*(queryfea[j]-feature[j]);
			querydis[feaindex] +=element[j];
		}
		querydis[feaindex] = sqrt(querydis[feaindex]);// save distance
	}
	
//	for (int ha=1; ha<=3;ha++)
//	{
//		CString test;
//		test.Format("querydis[%d]=%f,name=%s",ha,querydis[ha],featurename[ha]);
//		AfxMessageBox(test);
// 	}
	

	// sort distances (querydis[]) and the corresponding feature title (featuretitle[])
	double distemp;
	CString nametemp;
	for(int i=1;i<95;i++)  //bubble sort
	{
		for(int j=i+1;j<96;j++)
			if(querydis[i]>querydis[j])
			{
				distemp = querydis[i];
				querydis[i] = querydis[j];
				querydis[j] = distemp;

				nametemp = featurename[i];
				featurename[i] = featurename[j];
				featurename[j] = nametemp;
			}
	}
//	for (int ha=1; ha<=24;ha++)  //24: total number of the feature file, actually 25 file
//	{
//		CString test;
//		test.Format("querydis[%d]=%f,name=%s",ha,querydis[ha],featurename[ha]);
//		AfxMessageBox(test);
// 	}       


	// display results  
	CString m_sThumbnailPath[96];
	for (int tn=1; tn<=15; tn++)  // display the first page
	{
		m_sThumbnailPath[tn] = m_sQueryFeature.Left(m_sQueryFeature.Find("\\m")) + "\\";
		m_sThumbnailPath[tn] = m_sThumbnailPath[tn] + featurename[tn];
		m_sThumbnailPath[tn] = m_sThumbnailPath[tn] + "\.jpg"; // get path of the results thumbnails 


		if((m_pCPictureCtrl[tn-1]->LoadImage(m_sThumbnailPath[tn]))==false) return;  
    
   
		//CString test;
		//test.Format("path=%s",m_sThumbnailPath[tn]);
		//AfxMessageBox(test);
	} 
 
	// save all path into global variable array (allpath)
	for (int ap=1; ap<=24; ap++)  
	{
		if (1<=ap<=15)
			allpath[ap] = m_sThumbnailPath[ap];
		if (16<=ap<=24)
		{
			m_sThumbnailPath[ap] = m_sQueryFeature.Left(m_sQueryFeature.Find("\\m")) + "\\";
			m_sThumbnailPath[ap] = m_sThumbnailPath[ap] + featurename[ap];
			m_sThumbnailPath[ap] = m_sThumbnailPath[ap] + "\.jpg"; // get path of the results thumbnails 

			allpath[ap] = m_sThumbnailPath[ap];
		}

		//CString test;
		//test.Format("path=%s",m_sThumbnailPath[tn]);
		//AfxMessageBox(test);
	} 
	
	GetDlgItem(IDC_BUTTON_NEXTPAGE)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_PREPAGE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_HOMEPAGE)->EnableWindow(TRUE);
  
}




//button for retrieval
void CModelRetrievalView::OnButtonRetrieval() 
{
	//get the par
	this->UpdateData(true);
	BeginWaitCursor();
	if(m_cRetrievalControl.Retrieval(this->m_dThreshold)==true)
		this->m_bCanFeedback=true;  //retrieval
	else m_bCanFeedback=false;
	EndWaitCursor();

	//display
	this->DisplayResult();  //display

}


//display the retrieval results
void CModelRetrievalView::DisplayResult()
{
  
	//display the images on pannel
	//this->m_cRetrievalControl.DisplayOnPictureStruct(*m_pCPictureCtrl,*this->m_piRelevance,*this->m_psSimilarity,i);
	BeginWaitCursor();
	m_cRetrievalControl.DisplayCurrentPage(m_pCPictureCtrl,this->m_piRelevance,this->m_psSimilarity);	
	this->UpdateDisplay();
	EndWaitCursor();
}

void CModelRetrievalView::ClearDisplayResult()
{
  
	//display the images on pannel
	//this->m_cRetrievalControl.DisplayOnPictureStruct(*m_pCPictureCtrl,*this->m_piRelevance,*this->m_psSimilarity,i);
	BeginWaitCursor();
	m_cRetrievalControl.ClearDisplayCurrentPage(m_pCPictureCtrl,this->m_piRelevance,this->m_psSimilarity);	
	this->UpdateDisplay();
	EndWaitCursor();
}


//display the next page
void CModelRetrievalView::OnButtonNextpage()  
{
/*
	    //original  
		// TODO: Add your control notification handler code here
		this->updateRelevanceData();
		if(m_cRetrievalControl.SetNexToBeCurrentPage()==false) 
		{
			return;
		}
		DisplayResult();
*/
	
	// clear all results	 
	for (int i=0; i<=14; i++)
	{
		m_pCPictureCtrl[i]->DisEnableDisplay();
	}
	this->UpdateDisplay();
	// ClearDisplayResult(); //also can use this function 
	

	for (int haha=16; haha<=24; haha++)  // display the first page
	{
		if((m_pCPictureCtrl[haha-16]->LoadImage(allpath[haha]))==false) return;  
	}	

	// display information
    this->m_sSampleID=queryname; 
	this->m_sImagePath=databasepath.Left(databasepath.Find("\\feature"));
	this->m_sNumberImageDataBase=modelnumber;// display the number of models
	this->UpdateData(false);//output the paraments
	Invalidate();//output the retrieval results

	GetDlgItem(IDC_BUTTON_NEXTPAGE)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_PREPAGE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_HOMEPAGE)->EnableWindow(TRUE);

}


//button for pre page
void CModelRetrievalView::OnButtonPrepage() 
{
/* original
		// TODO: Add your control notification handler code here
		this->updateRelevanceData();
		if (m_cRetrievalControl.SetPreToBeCurrentPage()==false) return ;
		DisplayResult();
*/
	
	// dispaly previous page
	for (int ap=1; ap<=15; ap++)  // display the first page
	{
		if((m_pCPictureCtrl[ap-1]->LoadImage(allpath[ap]))==false) return;  
	}

}


//button for home page
void CModelRetrievalView::OnButtonHomepage() 
{
/* original 
		// TODO: Add your control notification handler code here	
		this->updateRelevanceData();
		if (m_cRetrievalControl.SetFirstToCurrentPage()==false) return ;
		DisplayResult();
*/
	
	// dispaly first page
	for (int ap=1; ap<=15; ap++)  // display the first page
	{
		if((m_pCPictureCtrl[ap-1]->LoadImage(allpath[ap]))==false) return;  
	}

}


//update the display
void CModelRetrievalView::UpdateDisplay()
{
	//update the "information"
	this->m_sImagePath=this->m_cRetrievalControl.GetImageBasePath();
	this->m_sSampleID=m_cRetrievalControl.GetSampleID();
	this->m_sNumberImageDataBase=m_cRetrievalControl.GetNumberImageDataBase();
	this->m_sNumberResult=m_cRetrievalControl.GetNumberResult();
	
	//updata the result information
	this->m_cHomePage.EnableWindow(false);
	this->m_cPrePage.EnableWindow(false);
	this->m_cNextPage.EnableWindow(false);
	this->m_sCurrentPage.Empty();
	this->m_sCurrentPage.Format("%s%d",m_sCurrentPage,m_cRetrievalControl.GetCurrentPage());
	this->m_sTotalPage.Empty();
	this->m_sTotalPage.Format("%s%d",m_sTotalPage,m_cRetrievalControl.GetTotalPage());

	//update the "control"
	this->m_cFeedbackControl.EnableWindow(this->m_bCanFeedback);
	this->m_cShouldRetrieval.EnableWindow(m_cRetrievalControl.IsNeedRetrieval());
	this->m_sStudyTimes=m_cRetrievalControl.GetStudtyTimes();

	//update the retrieval result
	if(m_cRetrievalControl.GetNumberResult()!="")
	{
		if(m_cRetrievalControl.GetCurrentPage()>0)
		{
		this->m_cHomePage.EnableWindow(true);
		this->m_cPrePage.EnableWindow(true);
		}
		if (m_cRetrievalControl.GetCurrentPage()<m_cRetrievalControl.GetTotalPage()-1)		
			this->m_cNextPage.EnableWindow(true);

	}
	this->m_dRecall=m_cRetrievalControl.GetRecall();
	this->m_dPrecise=m_cRetrievalControl.GetPrecise();
	this->m_fPR=m_dRecall*m_dPrecise;
	//output the paraments
	this->UpdateData(false);

	//output the retrieval results
	Invalidate();
	
}


//initilization
void CModelRetrievalView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_bIntilization==false)
	{
		UpdateDisplay();
		m_bIntilization=true;
	}
		
}


//if change the threshold
void CModelRetrievalView::OnChangeThreshold() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(true);
}

//update the relevance of the data
void CModelRetrievalView::updateRelevanceData()
{
	UpdateData(true);	
	m_cRetrievalControl.SetRelevanceCurrentPageResult(this->m_piRelevance);
}

void CModelRetrievalView::OnButtonRelevancefeedback() 
{
	// TODO: Add your control notification handler code here
	//update
	updateRelevanceData();
	this->m_cRetrievalControl.UpdateMatrixbyRelevance();
	//retrieval
	this->OnButtonRetrieval();
}

void CModelRetrievalView::OnButtonParameter() 
{
	// TODO: Add your control notification handler code here
	CDialogParamentSet cParamentSet;
	this->m_cRetrievalControl.GetFeedbackParament(cParamentSet.m_dParamentRR,cParamentSet.m_dParamentSI,cParamentSet.m_dParamentSU,(bool &)(cParamentSet.m_bStudying));
	if(cParamentSet.DoModal()==false) return;
	this->m_cRetrievalControl.SetFeedbackParament(cParamentSet.m_dParamentRR,cParamentSet.m_dParamentSI,cParamentSet.m_dParamentSU,cParamentSet.m_bStudying);

	
}

//test 
//for the experiment 1, the output file is "exmperiment.txt"
void CModelRetrievalView::OnGetinformatino() 
{
	// TODO: Add your command handler code here
	//threshold=0.5:0.05:1
	//i=9:10:999
	double dThreshold=0.5;
	const double dThresholdIncrease=0.025;

	unsigned int iTestID=9;  //9+10
	const int iIDIncrease=10;
	const unsigned int IIMAGENUMBER=1000;

	double dRecall=0,dRecallAverage=0;
	double dPrecise=0,dPreciseAverage=0;

	CFile fTestOut;
	CString OutFileName="experiment.txt";  //out file
	CString sTempData;

	if(fTestOut.Open(OutFileName,CFile::modeCreate|CFile::modeReadWrite)==false) return;
	//
	int i,j=0;
	double di,dj;

	for(di=dThreshold;di<=1;di=di+dThresholdIncrease)
	{
		//write the threshold
		fTestOut.SeekToEnd();
		fTestOut.Write("\n\\\\\\\\\\\\\\\\\\\\\\\\n",sizeof("\n\\\\\\\\\\\\\\\\\\\\\\\\n"));
		sTempData.Empty();
		sTempData.Format("%s%f",sTempData,di);
		fTestOut.Write(sTempData,sizeof(double));
		fTestOut.Write("\n",sizeof("\n"));
		dPreciseAverage=0;
		dRecallAverage=0;
		j=0;
		
		for(i=iTestID;i<IIMAGENUMBER;i=i+iIDIncrease)
		{
			//retrieval
			m_cRetrievalControl.SetSampleID(i);
			if(this->m_cRetrievalControl.Retrieval(di)==false){ fTestOut.Close(); return;}
			dRecall=m_cRetrievalControl.GetRecall();
			dPrecise=m_cRetrievalControl.GetPrecise();
			dRecallAverage=dRecallAverage+dRecall;
			dPreciseAverage=dPreciseAverage+dPrecise;
			j++;

			//write the result
			/*
			fTestOut.SeekToEnd();
			sTempData.Empty();
			sTempData.Format("%s%f",sTempData,dRecall);
			fTestOut.Write(sTempData,sizeof(double));
			fTestOut.Write("\t",sizeof("\t"));
			sTempData.Empty();
			sTempData.Format("%s%f",sTempData,dPrecise);
			fTestOut.Write(sTempData,sizeof(double));
			 fTestOut.Write("\n",sizeof("\n"));
			 */

		} //end of one threshold
		//the threshold ,the average
		//write the average of this threshold
		dRecallAverage=dRecallAverage/j;
		dPreciseAverage=dPreciseAverage/j;
		fTestOut.SeekToEnd();
		sTempData.Empty();
		sTempData.Format("%s%f",sTempData,dRecallAverage);
		fTestOut.Write(sTempData,sizeof(double));
		fTestOut.Write("\t",sizeof("\t"));
		sTempData.Empty();
		sTempData.Format("%s%f",sTempData,dPreciseAverage);
		fTestOut.Write(sTempData,sizeof(double));


			
	}  //end for di

			
	
}


//test
//for the experiment 3, the output file is "exmperiment_3.txt"/
void CModelRetrievalView::OnRetrievalMethodTest() 
{
		// TODO: Add your command handler code here
	//threshold=0.5:0.05:1
	//i=9:10:999
	double dThreshold=0.5;
	const double dThresholdIncrease=0.025;

	unsigned int iTestID=9;  //9+10
	const int iIDIncrease=10;
	const unsigned int IIMAGENUMBER=1000;

	double dRecall=0,dRecallAverage=0;
	double dPrecise=0,dPreciseAverage=0;

	CFile fTestOut;
	CString OutFileName="experiment_3.txt";  //out file
	CString sTempData;

	if(fTestOut.Open(OutFileName,CFile::modeCreate|CFile::modeReadWrite)==false) return;
	//
	int i=0,j=0,iLayConsidered=0;
	int iTotalLayTestNumber=0;
	double di,dj;
	clock_t timestart,timeend;

	//write the head
	fTestOut.SeekToEnd();
	fTestOut.Write("This is experiment 3,test the retrieval method!",sizeof("This is experiment 3,test the retrieval method!"));

	//begin test
for(iLayConsidered=1;iLayConsidered<=5;iLayConsidered++)
{
	this->m_cRetrievalControl.SetTestLay(iLayConsidered);
	//write the head
	fTestOut.SeekToEnd();
	fTestOut.Write("Lays test!",sizeof("Lays test!"));
	iTotalLayTestNumber=0;
	timestart=clock();
	for(di=dThreshold;di<=1;di=di+dThresholdIncrease)
	{
		//write the threshold
		fTestOut.SeekToEnd();
		fTestOut.Write("\n\\\\\\\\\\\\\\\\\\\\\\\\n",sizeof("\n\\\\\\\\\\\\\\\\\\\\\\\\n"));
		sTempData.Empty();
		sTempData.Format("%s%f",sTempData,di);
		fTestOut.SeekToEnd();
		fTestOut.Write(sTempData,sizeof(double));
		fTestOut.SeekToEnd();
		fTestOut.Write("\n",sizeof("\n"));
		dPreciseAverage=0;
		dRecallAverage=0;
		j=0;
		
		for(i=iTestID;i<IIMAGENUMBER;i=i+iIDIncrease)
		{
			//retrieval
			m_cRetrievalControl.SetSampleID(i);
			if(this->m_cRetrievalControl.Retrieval(di)==false){ fTestOut.Close(); return;}
			dRecall=m_cRetrievalControl.GetRecall();
			dPrecise=m_cRetrievalControl.GetPrecise();
			dRecallAverage=dRecallAverage+dRecall;
			dPreciseAverage=dPreciseAverage+dPrecise;
			iTotalLayTestNumber++;
			j++;

		} //end of one threshold
		//the threshold ,the average
		//write the average of this threshold
		dRecallAverage=dRecallAverage/j;
		dPreciseAverage=dPreciseAverage/j;
		fTestOut.SeekToEnd();
		sTempData.Empty();
		sTempData.Format("%s%f",sTempData,dRecallAverage);
		fTestOut.Write(sTempData,sizeof(double));
		fTestOut.SeekToEnd();
		fTestOut.Write("\t",sizeof("\t"));
		sTempData.Empty();
		sTempData.Format("%s%f",sTempData,dPreciseAverage);
		fTestOut.SeekToEnd();
		fTestOut.Write(sTempData,sizeof(double));			
	}  //end for di
	timeend=clock();
	sTempData.Empty();
	sTempData.Format("%s%f",sTempData,(double)(timeend-timestart)/iTotalLayTestNumber/1000.0);
	fTestOut.SeekToEnd();
	fTestOut.Write(sTempData,sizeof(double));
	fTestOut.SeekToEnd();
	fTestOut.Write("\t\n",sizeof("\t\n"));
	
} //end of iLayConsidered
	
}



//open OFF file with different views

void CModelRetrievalView::OnButtonOpenoffpolygon() 
{
	// TODO: Add your control notification handler code here
	
	char BASED_CODE szFilter[]="OFF Files(*.off)|*.off|All Files(*.*)|*.*||";
	CFileDialog m_ldFile(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
	m_ldFile.m_ofn.lpstrTitle="open a off model";

	if(m_ldFile.DoModal()!=IDOK)
	{	
		return;
	}

	//get the file name 
	this->m_sQueryName=m_ldFile.GetPathName();
	
	mesh = ReadOffFile(m_sQueryName);//read model

	int argc=1;
	char **argv;
	GLUTInitpolygon(&argc, argv);	
    //GLUTRedraw;
	GLUTMainLoop();/**/

}

void CModelRetrievalView::OnButtonOpenoffpoints() 
{
	// TODO: Add your control notification handler code here
	
	char BASED_CODE szFilter[]="OFF Files(*.off)|*.off|All Files(*.*)|*.*||";
	CFileDialog m_ldFile(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
	m_ldFile.m_ofn.lpstrTitle="open a off model";

	if(m_ldFile.DoModal()!=IDOK)
	{	
		return;
	}

	//get the file name 
	this->m_sQueryName=m_ldFile.GetPathName();
	
	mesh = ReadOffFile(m_sQueryName);//read model

	int argc=1;
	char **argv;
	GLUTInitpoint(&argc, argv);
    //GLUTRedraw;
	GLUTMainLoop();/**/
	
}

void CModelRetrievalView::OnButtonOpenofflines() 
{
	// TODO: Add your control notification handler code here
	char BASED_CODE szFilter[]="OFF Files(*.off)|*.off|All Files(*.*)|*.*||";
	CFileDialog m_ldFile(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
	m_ldFile.m_ofn.lpstrTitle="open a off model";

	if(m_ldFile.DoModal()!=IDOK)
	{	
		return;
	}

	//get the file name 
	this->m_sQueryName=m_ldFile.GetPathName();
	
	mesh = ReadOffFile(m_sQueryName);//read model

	int argc=1;
	char **argv;
	GLUTInitlines(&argc, argv);
    //GLUTRedraw;
	GLUTMainLoop();/**/
}

void CModelRetrievalView::OnButtonOpenofftriangles() 
{
	// TODO: Add your control notification handler code here
	char BASED_CODE szFilter[]="OFF Files(*.off)|*.off|All Files(*.*)|*.*||";
	CFileDialog m_ldFile(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
	m_ldFile.m_ofn.lpstrTitle="open a off model";

	if(m_ldFile.DoModal()!=IDOK)
	{	
		return;
	}

	//get the file name 
	this->m_sQueryName=m_ldFile.GetPathName();
	
	mesh = ReadOffFile(m_sQueryName);//read model

	int argc=1;
	char **argv;
	GLUTInittriangles(&argc, argv);
    //GLUTRedraw;
	GLUTMainLoop();/**/
}


// D1 feature extraction    
// (1) sampling; (2)compute D1; (3)construct histigram

void CModelRetrievalView::OnButtonDone()    /* D1 */ 
{
	// TODO: Add your control notification handler code here
   	int NP = 1000000; // set the number of sample points

	char BASED_CODE szFilter[]="OFF Files(*.off)|*.off|All Files(*.*)|*.*||";
	CFileDialog m_ldFile(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
	m_ldFile.m_ofn.lpstrTitle="open a off model";

	if(m_ldFile.DoModal()!=IDOK)
	{	
		return;
	}

	//get the file name 
	this->m_sQueryName=m_ldFile.GetPathName();
    mesh = ReadOffFile(m_sQueryName);//read model


    // compute the centriod
	int i;
	int vertex;
	float sumx=0;
	float sumy=0;
	float sumz=0;

	for (i = 0; i < mesh->nverts; i++) 	
	{  	
		Vertex& v = mesh->verts[i];  // coordinates of the i-th vertex
		sumx += v.x;
		sumy += v.y;
		sumz += v.z;
	}	

	float centroidx = sumx/mesh->nverts;  // x coordinate of the centroid
	float centroidy = sumy/mesh->nverts;  // y coordinate of the centroid
	float centroidz = sumz/mesh->nverts;  // z coordinate of the centroid

/*
	    // compute distance between vertice and the centroid
		float distance[50000];
		char sTemp[20]; // write data of distance to disk one by one
		CFile cfdistance;
		cfdistance.Open("distance.txt",CFile::modeCreate|CFile::modeWrite);
		
		for (i = 0; i < mesh->nverts; i++) 	
		{  	
			Vertex& v = mesh->verts[i];  
			distance[i] =sqrt((v.x-centroidx)*(v.x-centroidx)+(v.y-centroidy)*(v.y-centroidy)+(v.z-centroidz)*(v.z-centroidz));
			gcvt(distance[i],10,sTemp); // convert double to char     (not itoa!!)		 
			cfdistance.Write(sTemp,strlen(sTemp));
			cfdistance.SeekToEnd();
			cfdistance.Write("\n",strlen("\n"));
			cfdistance.SeekToEnd();	
		}
		cfdistance.Close();
*/
	


	
/*	
	// get triangles normal vector
	int j;
	double trinormal1[10000];
	double trinormal2[10000];
	double trinormal3[10000];
	
	char sTemp1[20]; 
    char sTemp2[20]; 
    char sTemp3[20]; 
    CFile cftrinormal;
	cftrinormal.Open("trinormal.txt",CFile::modeCreate|CFile::modeWrite);
    for (j = 0; j < mesh->nfaces; j++) 	// get the triangles
	{  	
	Face& f = mesh->faces[j];// the j-th face
	if (f.nverts != 3) return;
	
	trinormal1[j] = f.normal[1];		
	gcvt(trinormal1[j],10,sTemp1); // convert double to char     (not itoa!!)
	cftrinormal.Write(sTemp1,strlen(sTemp1));
	cftrinormal.SeekToEnd();
	cftrinormal.Write(" ",strlen(" "));
	cftrinormal.SeekToEnd();
		  
    trinormal2[j] = f.normal[2];
	gcvt(trinormal2[j],10,sTemp2); // convert double to char     (not itoa!!)
	cftrinormal.Write(sTemp2,strlen(sTemp2));
	cftrinormal.SeekToEnd();
	cftrinormal.Write(" ",strlen(" "));
	cftrinormal.SeekToEnd();
	  
	trinormal3[j] = f.normal[3];
	gcvt(trinormal3[j],10,sTemp3); // convert double to char     (not itoa!!)
	cftrinormal.Write(sTemp3,strlen(sTemp3));
	cftrinormal.SeekToEnd();		
	cftrinormal.Write("\n",strlen("\n"));
	cftrinormal.SeekToEnd();
	}
	cftrinormal.Close();
*/	


/*
    sample on the triangles 
	(1): compute the triangles area, the total area, and the proportion
    (2): compute the number of points on each triangle
    (3): compute the position of sample points using vertice information 
*/

    int nf = mesh->nfaces;   //the number of the triangles
    float *area; //initialize area
	area = new float [nf];
	float A1,B1,C1,A2,B2,C2;
	int m;

	for (m = 0; m < mesh->nfaces; m++) 	// get the triangles  //for(int n = 0; n < mesh->faces[m].nverts; n++)
	{ 
		Face& face = mesh->faces[m];// the j-th face

	    // (1): compute the triangles area, the total area, and the proportion
		// triangle area = 0.5*norm(cross(p3-p1,p2-p1)); 
        // p1 = [x0;y0;z0]; 
        // p2 = [x1;y1;z1];
        // p3 = [x2;y2;z2];
		

		A1 = mesh->faces[m].verts[1]->x - mesh->faces[m].verts[0]->x;   //x1-x0
		B1 = mesh->faces[m].verts[1]->y - mesh->faces[m].verts[0]->y;   //y1-y0
		C1 = mesh->faces[m].verts[1]->z - mesh->faces[m].verts[0]->z;   //z1-z0

		A2 = mesh->faces[m].verts[2]->x - mesh->faces[m].verts[0]->x;   //x2-x0
		B2 = mesh->faces[m].verts[2]->y - mesh->faces[m].verts[0]->y;   //y2-y0
		C2 = mesh->faces[m].verts[2]->z - mesh->faces[m].verts[0]->z;   //z2-z0

		// cross(p3-p1,p2-p1) = (B1*C2-B2*C1)i+(A2*C1-A1*C2)j+(A1*B2-A2*B1)k;
		area[m] = 0.5*sqrt((B1*C2-B2*C1)*(B1*C2-B2*C1)+(A2*C1-A1*C2)*(A2*C1-A1*C2)+(A1*B2-A2*B1)*(A1*B2-A2*B1));
	}  
	
	float totalarea=0;	
	for (int l = 0; l < mesh->nfaces; l++) 
	{
		totalarea = totalarea + area[l];  // suface area of the model
	} 

	// (2): compute the number of points on each triangle
    float *sp; //initialize sp
	sp = new float [nf];
    for (int k = 0; k < mesh->nfaces; k++) 
	{
		sp[k] = floor(NP*area[k]/totalarea); // Note: floor is not accurate		
	} 
	
	delete [] area;

	// (3): compute the position of sample points
	//	for m = 1:P %采样P个随机点
	//        r1 = rand; r2 = rand;% 产生0-1两个随机数r1,r2
	//        SP_x(m,j) = (1-sqrt(r1))*x1 + sqrt(r1)*(1-r2)*x2 + sqrt(r1)*r2*x3;%第j个三角形第m个采样点x坐标
	//        SP_y(m,j) = (1-sqrt(r1))*y1 + sqrt(r1)*(1-r2)*y2 + sqrt(r1)*r2*y3;%第j个三角形第m个采样点y坐标
	//        SP_z(m,j) = (1-sqrt(r1))*z1 + sqrt(r1)*(1-r2)*z2 + sqrt(r1)*r2*z3;%第j个三角形第m个采样点z坐标
	//        I(m,:,j)=[SP_x(m,j),SP_y(m,j),SP_z(m,j)]; %I(m,:,j)为第j个三角形第m个采样点,中间控制x,y,z坐标

	double spx,spy,spz;
	double dt;
	double D1;
	char sDis[20]; 
	CFile cfdis;
	cfdis.Open("D1.txt",CFile::modeCreate|CFile::modeWrite); //wirte d1 to disk one by one
	
	for (int n = 0; n < mesh->nfaces; n++) 
		for (int q = 1; q <= sp[n]; q++)
		{
			// get two random value, with the range 0--1  
			double r[2];			
			for (int ii=0; ii<2; ii++)
			{
				r[ii] = ( (double)rand() / ((double)(RAND_MAX))); 
			}
			double r1=r[0];
			double r2=r[1];
		
			//spx, spy, spz are the x, y, z coordinate of the sample point
			spx = (1-sqrt(r1))*(mesh->faces[n].verts[0]->x) + sqrt(r1)*(1-r2)*(mesh->faces[n].verts[1]->x) + sqrt(r1)*r2*(mesh->faces[n].verts[2]->x);
			spy = (1-sqrt(r1))*(mesh->faces[n].verts[0]->y) + sqrt(r1)*(1-r2)*(mesh->faces[n].verts[1]->y) + sqrt(r1)*r2*(mesh->faces[n].verts[2]->y);
			spz = (1-sqrt(r1))*(mesh->faces[n].verts[0]->z) + sqrt(r1)*(1-r2)*(mesh->faces[n].verts[1]->z) + sqrt(r1)*r2*(mesh->faces[n].verts[2]->z);
			dt = sqrt((spx-centroidx)*(spx-centroidx) + (spy-centroidy)*(spy-centroidy) + (spz-centroidz)*(spz-centroidz));
			D1 = exp(-dt*dt/(2*0.01));

			gcvt(D1,10,sDis); // convert double to char  		 
			CString Data;
			Data.Format("%.10f",D1);
			cfdis.Write(Data,Data.GetLength());
			cfdis.SeekToEnd();  
			cfdis.Write("\n",strlen("\n")); 
			cfdis.SeekToEnd();	 
		}
		delete [] sp;
		
}



void CModelRetrievalView::OnButtonDtwo()  /* D2 */ 
{
	/*
    steps:
	(1): compute the triangles area, the total area, and the proportion
    (2): compute the number of points on each triangle
    (3): compute the position of sample points using vertice information
	(4): compute distance of two random points
	*/
	// TODO: Add your control notification handler code here
	
   	int NP = 1000; // set the number of sample points

	char BASED_CODE szFilter[]="OFF Files(*.off)|*.off|All Files(*.*)|*.*||";
	CFileDialog m_ldFile(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
	m_ldFile.m_ofn.lpstrTitle="open a off model";

	if(m_ldFile.DoModal()!=IDOK)
	{	
		return;
	}

	//get the file name 
	this->m_sQueryName=m_ldFile.GetPathName();
    mesh = ReadOffFile(m_sQueryName);//read model
    

	//(1): compute the triangles area, the total area, and the proportion
    int nf = mesh->nfaces;   //the number of the triangles
    float *area; //initialize area
	area = new float [nf];
	float A1,B1,C1,A2,B2,C2;
	
	for (int m = 0; m < mesh->nfaces; m++) 	// get the triangles 
	{ 
		Face& face = mesh->faces[m];// the j-th face

		A1 = mesh->faces[m].verts[1]->x - mesh->faces[m].verts[0]->x;   //x1-x0
		B1 = mesh->faces[m].verts[1]->y - mesh->faces[m].verts[0]->y;   //y1-y0
		C1 = mesh->faces[m].verts[1]->z - mesh->faces[m].verts[0]->z;   //z1-z0

		A2 = mesh->faces[m].verts[2]->x - mesh->faces[m].verts[0]->x;   //x2-x0
		B2 = mesh->faces[m].verts[2]->y - mesh->faces[m].verts[0]->y;   //y2-y0
		C2 = mesh->faces[m].verts[2]->z - mesh->faces[m].verts[0]->z;   //z2-z0

		// cross(p3-p1,p2-p1) = (B1*C2-B2*C1)i+(A2*C1-A1*C2)j+(A1*B2-A2*B1)k;
		area[m] = 0.5*sqrt((B1*C2-B2*C1)*(B1*C2-B2*C1)+(A2*C1-A1*C2)*(A2*C1-A1*C2)+(A1*B2-A2*B1)*(A1*B2-A2*B1));
	}  
	
	float totalarea=0;	
	for (int l = 0; l < mesh->nfaces; l++) 
	{
		totalarea += area[l];  // suface area of the model
	} 

	// (2): compute the number of points on each triangle
    float *sp; //initialize sp
	sp = new float [nf];
    for (int k = 0; k < mesh->nfaces; k++) 
	{
		sp[k] = floor(NP*area[k]/totalarea); // Note: floor is not accurate		
	} 
	delete [] area;

	//---ok!
	// (3): compute the position of sample points
    double *spx;
	double *spy;
	double *spz;
	spx = new double [NP]; //nearly NP sample points
	spy = new double [NP];
	spz = new double [NP];
	int cp=0;

	for (int n = 0; n <mesh->nfaces ; n++) //mesh->nfaces
	{
		if (sp[n]!=0)
		{
			for (int q = 1; q <= sp[n]; q++)
			{
				// get two random number, with the range 0--1  
				double r[2];	
				for (int ii=0; ii<2; ii++)
				{
					r[ii] = ( (double)rand() / ((double)(RAND_MAX))); 
				}
				double r1=r[0];
				double r2=r[1];
				
				//spx, spy, spz are the x, y, z coordinate of the sample point
				if (n==0)
					cp = q; // index of the current point
				if (n>0)
				{
					cp = q;
					for (int ll=0; ll<n; ll++)
					{
						cp += sp[ll]; // index of the current point
					}				
				}
							
				spx[cp] = (1-sqrt(r1))*(mesh->faces[n].verts[0]->x) + sqrt(r1)*(1-r2)*(mesh->faces[n].verts[1]->x) + sqrt(r1)*r2*(mesh->faces[n].verts[2]->x);
	     		spy[cp] = (1-sqrt(r1))*(mesh->faces[n].verts[0]->y) + sqrt(r1)*(1-r2)*(mesh->faces[n].verts[1]->y) + sqrt(r1)*r2*(mesh->faces[n].verts[2]->y);
		    	spz[cp] = (1-sqrt(r1))*(mesh->faces[n].verts[0]->z) + sqrt(r1)*(1-r2)*(mesh->faces[n].verts[1]->z) + sqrt(r1)*r2*(mesh->faces[n].verts[2]->z);
			}
		}
	}
	delete [] sp;
	CString t1;
	t1.Format("cp=%d",cp);
	AfxMessageBox(t1);
	
	// (4): compute distance of two random points
	double D2;
	char sDis[20]; 
	CFile cfdis;
	cfdis.Open("D2.txt",CFile::modeCreate|CFile::modeWrite); //wirte D2 to disk one by one

	for (int u = 1; u <cp ; u++) 
	{
		for (int v = u+1; v <=cp ; v++)
		{
			D2 = sqrt( (spx[u]-spx[v])*(spx[u]-spx[v]) + (spy[u]-spy[v])*(spy[u]-spy[v]) + (spz[u]-spz[v])*(spz[u]-spz[v]) );
			
			gcvt(D2,10,sDis); // convert double to char  		 
			CString Data;
			Data.Format("%.10f",D2);
			cfdis.Write(Data,Data.GetLength());
			cfdis.SeekToEnd();  
			cfdis.Write("\n",strlen("\n"));
			cfdis.SeekToEnd();	
		} 		
 	}
	
	delete [] spx;
	delete [] spy;
	delete [] spz;

}





void CModelRetrievalView::OnButtonHistogram() /* construct the histogram of D1 */
{
	// TODO: Add your control notification handler code here
	
    // open a .txt file (D1/D2)
	char BASED_CODE szFilter[]="Distance Files(*.txt)|*.txt|All Files(*.*)|*.*||";
	CFileDialog m_ldFile(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
	m_ldFile.m_ofn.lpstrTitle="open a distance file";

	if(m_ldFile.DoModal()!=IDOK)
	{	
		return;
	}

	//get the file name 
	this->m_sDone=m_ldFile.GetPathName(); 

	// read D1 data into array a    
	CFile mFile;
	if(mFile.Open(m_sDone,CFile::modeRead)==0)
	{
		return;
	}

	DWORD nFileSize = mFile.GetLength();
	mFile.Seek(0L,SEEK_SET);
	int number=nFileSize/13;   // each line need 13 bytes

    double *a; //initialize a
	a = new double [number];
	for(int k=0;;k++)
	{
		DWORD pos=mFile.GetPosition();
		if(pos==nFileSize) 
			break; // if the end of the file, break.
		char temp[20];
		a[k]=0.0;
		for(int m=0;;m++)
		{
			mFile.Read((char*)temp+m,sizeof(char));
			if(temp[m]=='\n')
			{
				a[k]+=temp[0]-48;
				for(int t=2;t<m-1;t++)
				{
					double p=pow(0.1,t-1)*(temp[t]-48);
					a[k]+=p;
				}
				//CString test;
				//test.Format("a[%d]=%.10f",k,a[k]);
				//AfxMessageBox(test);
				break;
			}
		}
	}
	mFile.Close();
	
	// find the max and min of the D1
	double maxD1=a[0];
	double minD1=a[0];
	for (int i=1; i< number; i++) 
	{
		if (a[i]>maxD1) 
			maxD1=a[i];
		else if (a[i]<minD1)
			minD1=a[i]; 	
	}	
	//	CString test1;
	//	test1.Format("maxD1=%.10f",maxD1);
	//	AfxMessageBox(test1);
	//	CString test2;
	//	test2.Format("minD1=%.10f",minD1);
	//	AfxMessageBox(test2);
	    

	// construct the histogram of D1
	int binsnumber = 1024;   //set the number of the bins  (1024 bins) 
	
	int *bins; //initialize all bins
	bins = new int [binsnumber];
	for (int tt=0; tt<binsnumber; tt++)
	{
		bins[tt]=0;
	}

	double bin = (maxD1-minD1)/binsnumber;
	char htemp[20]; 
	CFile chist;
	chist.Open("feature.txt",CFile::modeCreate|CFile::modeWrite); //wirte d1 to disk one by one

	for (int nb=0; nb<binsnumber; nb++) 
	{
		double lowerbound = minD1+nb*bin;
		double higherbound = minD1+(nb+1)*bin;
		for (int p=0; p<number; p++)
		{
			if ( lowerbound<=a[p] &&  a[p]<higherbound )
				bins[nb] += 1;
		}

		if (nb==(binsnumber-1)) // the last bin add one for the maxD1
			bins[binsnumber-1] += 1; 

		// write bins to disk one by one
		itoa(bins[nb],htemp,10); 	  
		CString hist;
		hist.Format("%d",bins[nb]);
		chist.Write(hist,hist.GetLength());
		chist.SeekToEnd(); 
		chist.Write("\n",strlen("\n")); 
		chist.SeekToEnd();	 
	}

	delete [] a;
	delete [] bins;	
	
}
