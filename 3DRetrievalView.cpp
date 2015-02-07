// 3DRetrievalView.cpp : implementation of the CMy3DRetrievalView class
//

#include "stdafx.h"
#include "3DRetrieval.h"

#include "3DRetrievalDoc.h"
#include "3DRetrievalView.h"
#include "Jpeg.h"
//#include "offviewer.cpp"
#include <io.h>
#include <FCNTL.h>
#include <SYS\STAT.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy3DRetrievalView

IMPLEMENT_DYNCREATE(CMy3DRetrievalView, CFormView)

BEGIN_MESSAGE_MAP(CMy3DRetrievalView, CFormView)
	//{{AFX_MSG_MAP(CMy3DRetrievalView)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy3DRetrievalView construction/destruction

CMy3DRetrievalView::CMy3DRetrievalView()
	: CFormView(CMy3DRetrievalView::IDD)
{
	//{{AFX_DATA_INIT(CMy3DRetrievalView)
	m_DataBasePath = _T("");
	m_ModelNum = 0;
	m_CurrentPage = 0;
	m_QueryInfor = _T("");
	m_RetrievalInfor1 = _T("");
	m_RetrievalInfor10 = _T("");
	m_RetrievalInfor2 = _T("");
	m_RetrievalInfor3 = _T("");
	m_RetrievalInfor4 = _T("");
	m_RetrievalInfor5 = _T("");
	m_RetrievalInfor6 = _T("");
	m_RetrievalInfor7 = _T("");
	m_RetrievalInfor8 = _T("");
	m_RetrievalInfor9 = _T("");
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CMy3DRetrievalView::~CMy3DRetrievalView()
{
}

void CMy3DRetrievalView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMy3DRetrievalView)
	DDX_Control(pDX, IDC_STATIC_Query, m_QueryImage);
	DDX_Control(pDX, IDC_STATIC_RetrievalResults9, m_RetrievalImage9);
	DDX_Control(pDX, IDC_STATIC_RetrievalResults8, m_RetrievalImage8);
	DDX_Control(pDX, IDC_STATIC_RetrievalResults7, m_RetrievalImage7);
	DDX_Control(pDX, IDC_STATIC_RetrievalResults6, m_RetrievalImage6);
	DDX_Control(pDX, IDC_STATIC_RetrievalResults5, m_RetrievalImage5);
	DDX_Control(pDX, IDC_STATIC_RetrievalResults4, m_RetrievalImage4);
	DDX_Control(pDX, IDC_STATIC_RetrievalResults3, m_RetrievalImage3);
	DDX_Control(pDX, IDC_STATIC_RetrievalResults2, m_RetrievalImage2);
	DDX_Control(pDX, IDC_STATIC_RetrievalResults10, m_RetrievalImage10);
	DDX_Control(pDX, IDC_STATIC_RetrievalResults1, m_RetrievalImage1);
	DDX_Text(pDX, IDC_EDIT_DataBasePath, m_DataBasePath);
	DDX_Text(pDX, IDC_EDIT_ModelNum, m_ModelNum);
	DDX_Text(pDX, IDC_EDIT_Page, m_CurrentPage);
	DDX_Text(pDX, IDC_EDIT_QueryInfor, m_QueryInfor);
	DDX_Text(pDX, IDC_EDIT_RetrievalName1, m_RetrievalInfor1);
	DDX_Text(pDX, IDC_EDIT_RetrievalName10, m_RetrievalInfor10);
	DDX_Text(pDX, IDC_EDIT_RetrievalName2, m_RetrievalInfor2);
	DDX_Text(pDX, IDC_EDIT_RetrievalName3, m_RetrievalInfor3);
	DDX_Text(pDX, IDC_EDIT_RetrievalName4, m_RetrievalInfor4);
	DDX_Text(pDX, IDC_EDIT_RetrievalName5, m_RetrievalInfor5);
	DDX_Text(pDX, IDC_EDIT_RetrievalName6, m_RetrievalInfor6);
	DDX_Text(pDX, IDC_EDIT_RetrievalName7, m_RetrievalInfor7);
	DDX_Text(pDX, IDC_EDIT_RetrievalName8, m_RetrievalInfor8);
	DDX_Text(pDX, IDC_EDIT_RetrievalName9, m_RetrievalInfor9);
	//}}AFX_DATA_MAP
}

BOOL CMy3DRetrievalView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CMy3DRetrievalView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CMy3DRetrievalView printing

BOOL CMy3DRetrievalView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMy3DRetrievalView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMy3DRetrievalView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMy3DRetrievalView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CMy3DRetrievalView diagnostics

#ifdef _DEBUG
void CMy3DRetrievalView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMy3DRetrievalView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMy3DRetrievalDoc* CMy3DRetrievalView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3DRetrievalDoc)));
	return (CMy3DRetrievalDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMy3DRetrievalView message handlers

void CMy3DRetrievalView::DisplayInitialParameters()
{
	CMy3DRetrievalDoc* pDoc = GetDocument();//Get pDoc
	ASSERT_VALID(pDoc);//Make pDoc valid
	//For query image
	m_QueryImage.SetBitmap(NULL);
	m_QueryInfor="No query model opened!";
	m_ModelNum=pDoc->m_TotalNumMedol;
	m_DataBasePath=pDoc->m_OldDataBasePath;

	//for the retrieval results;
	m_CurrentPage = 0;
	m_RetrievalInfor1 = _T("No model");
	m_RetrievalInfor10 = _T("No model");
	m_RetrievalInfor2 = _T("No model");
	m_RetrievalInfor3 = _T("No model");
	m_RetrievalInfor4 = _T("No model");
	m_RetrievalInfor5 = _T("No model");
	m_RetrievalInfor6 = _T("No model");
	m_RetrievalInfor7 = _T("No model");
	m_RetrievalInfor8 = _T("No model");
	m_RetrievalInfor9 = _T("No model");

	UpdateData(NULL);
}

void CMy3DRetrievalView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
		CMy3DRetrievalDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		int displayWidth;
		int displayHeight;
		char str[80];
		CString temp;
		HBITMAP QueryImage;
		

		/////Display the inital parameters
		DisplayInitialParameters();
		
		//draw the Query image//
		if(pDoc->m_bFileOpen==TRUE)
		{
			displayWidth=SuitableWidth(160,120,300,175);
			displayHeight=SuitableHeight(160,120,300,175);
			m_QueryInfor="Query image filename:"+pDoc->m_sQueryModelPath;
/*
				QueryImage=(HBITMAP)::LoadImage(NULL,pDoc->m_sQueryImagePath,IMAGE_BITMAP,displayWidth,displayHeight,\
					LR_LOADFROMFILE|LR_CREATEDIBSECTION);	
				m_QueryImage.SetBitmap(QueryImage);
				::DeleteObject(QueryImage);
			
		//display the jepg file;	
		//	char temp1[MAX_PATH];
		//	sprintf(temp1,   "%s",  pDoc->m_sQueryImagePath);
		//	DisplayJpegFile(temp1,2,160,120);
		*/
			if(pDoc->m_vQueryFeatureVector.m_bType==0)
			{
				QueryImage=(HBITMAP)::LoadImage(NULL,pDoc->m_sQueryImagePath,IMAGE_BITMAP,displayWidth,displayHeight,\
					LR_LOADFROMFILE|LR_CREATEDIBSECTION);	
				m_QueryImage.SetBitmap(QueryImage);
				::DeleteObject(QueryImage);
			} 
			else if(pDoc->m_vQueryFeatureVector.m_bType==1)
			{ 
				temp=pDoc->m_CurrentDirectory;
				temp=temp+"\\tempquery.bmp";
				QueryImage=(HBITMAP)::LoadImage(NULL,temp,IMAGE_BITMAP,displayWidth,displayHeight,\
					LR_LOADFROMFILE|LR_CREATEDIBSECTION);	
				m_QueryImage.SetBitmap(QueryImage);
				::DeleteObject(QueryImage); 
		        	/*
					char temp1[MAX_PATH];
		        	sprintf(temp1,   "%s",  pDoc->m_sQueryImagePath);
				    DisplayJpegFile(temp1,11,160,120);
					*/
			}
		}
	//Display the retrieval results
		if (pDoc->m_bDisplayRetrieval==TRUE)
		{
			m_CurrentPage = pDoc->m_ipage;
			DisplayModelNum=pDoc->m_dDisplayNumber;
			DisplayRetrieval();
		}

		UpdateData(false);

		
}

int CMy3DRetrievalView::SuitableHeight(int Width, int Heigth, int DisplayWidth, int DisplayHeigth)
{
	return (int)(Heigth*min((double)DisplayWidth/Width,(double)DisplayHeigth/Heigth));
}

int CMy3DRetrievalView::SuitableWidth(int Width, int Heigth, int DisplayWidth, int DisplayHeigth)
{
	 return (int)(Width*min((double)DisplayWidth/Width,(double)DisplayHeigth/Heigth));
}

int CMy3DRetrievalView::DisplayJpegFile(char m_sOriginalFileName[], int num, int displayWidth, int displayHeight)
{
	CMy3DRetrievalDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	HBITMAP RetrievalImage;
	unsigned int x,y;
	long int fh;
	unsigned char *m_cImageBytes;
	unsigned long int linebytes;
	CFile file;
	CJpeg jpg;
	CString temp;
	BYTE *p1,*p2,*p3;
	JPEG_IMAGE_INFO info;
	HGLOBAL Imagehg;
    LPBITMAPFILEHEADER bitfile;
    LPBITMAPINFOHEADER bitinfo;
	if(jpg.open(m_sOriginalFileName,IDCT_INT))
	{ 
		  jpg.getImageInfo(&info);
		  temp=pDoc->m_CurrentDirectory;
		  temp=temp+"\\tempretri.bmp";
	      fh=_open(temp,_O_BINARY|_O_WRONLY|_O_CREAT|_O_TRUNC,_S_IREAD|_S_IWRITE);
		  if(fh==-1)
		  { 
	        jpg.close();
			return -1;
		  }
		  if(info.comNum==3)
		  {
		    bitfile=(LPBITMAPFILEHEADER)pDoc->m_StandardBmpInfoc;
            bitinfo=(LPBITMAPINFOHEADER)(pDoc->m_StandardBmpInfoc+sizeof(BITMAPFILEHEADER));
            bitinfo->biHeight=info.imgHeight;
            bitinfo->biWidth=info.imgWidth;
		    linebytes=(info.imgWidth*24+31)/32*4;
		    bitfile->bfSize=info.imgHeight*linebytes+54;
		    bitinfo->biSizeImage=info.imgHeight*linebytes;
		    p1=info.image[0];
		    p2=info.image[1];
		    p3=info.image[2];
		    Imagehg=GlobalAlloc(GMEM_FIXED,bitfile->bfSize);//Apply the required memory
            ////If memory is not enough, return directly
            if(Imagehg==NULL)
			{
              _close(fh); //Close the file
	          jpg.close();
			  return -2;
			}
            m_cImageBytes=(unsigned char *)Imagehg;//Give the memory pointer to the file data pointer
            memcpy(m_cImageBytes,pDoc->m_StandardBmpInfoc,54);
			for(y=0;y<info.imgHeight;y++)
			{
	          p1=info.image[0]+y*info.bufWidth;
			  p2=info.image[1]+y*info.bufWidth;
			  p3=info.image[2]+y*info.bufWidth;
			  for(x=0;x<linebytes/3;x++)
			  {
			    if(x<info.imgWidth)
				{
				  m_cImageBytes[54+(info.imgHeight-y-1)*linebytes+x*3]=*p3++;
				  m_cImageBytes[54+(info.imgHeight-y-1)*linebytes+x*3+1]=*p2++;
				  m_cImageBytes[54+(info.imgHeight-y-1)*linebytes+x*3+2]=*p1++;
				}
			  }
			}
		  }
		  else
		  {
		    bitfile=(LPBITMAPFILEHEADER)pDoc->m_StandardBmpInfo;
            bitinfo=(LPBITMAPINFOHEADER)(pDoc->m_StandardBmpInfo+sizeof(BITMAPFILEHEADER));
		    bitinfo->biHeight=info.imgHeight;
            bitinfo->biWidth=info.imgWidth;
			linebytes=(info.imgWidth+3)/4*4;
		    bitfile->bfSize=info.imgHeight*linebytes+1078;
		    bitinfo->biSizeImage=info.imgHeight*linebytes;
		    Imagehg=GlobalAlloc(GMEM_FIXED,bitfile->bfSize);//Apply the required memory
            ////If memory is not enough, return directly
            if(Imagehg==NULL)
			{
              _close(fh); //Close the file
	          //MessageBox(NULL,"No enough memory!","Temporary File Save",MB_ICONSTOP|MB_OK);//Display Info
	          jpg.close();
			  return -2;
			}
            m_cImageBytes=(unsigned char *)Imagehg;//Give the memory pointer to the file data pointer
            memcpy(m_cImageBytes,pDoc->m_StandardBmpInfo,1078);
			p1=info.image[0];
			for(y=0;y<info.imgHeight;y++)
			{
			  memcpy(m_cImageBytes+1078+(info.imgHeight-y-1)*linebytes,p1,linebytes);
			  p1=p1+info.bufWidth;
			}
		  }
		  if(_write(fh,m_cImageBytes,bitfile->bfSize)!=(int)bitfile->bfSize)
		  {
			//MessageBox(NULL,"File save error","Error!", MB_ICONSTOP|MB_OK);
			_close(fh);
			GlobalFree(Imagehg);
            jpg.close();
			return -2;
		  }
		  _close(fh);
		  GlobalFree(Imagehg);
		  jpg.close();
	}
	RetrievalImage=(HBITMAP)::LoadImage(NULL,temp,IMAGE_BITMAP,displayWidth,displayHeight,\
	LR_LOADFROMFILE|LR_CREATEDIBSECTION);	
	switch(num)
	{

		  case 1:
			m_RetrievalImage1.SetBitmap(RetrievalImage);
			//((CButton *)GetDlgItem(IDC_BUTTON_RETRIEVAL1))->SetBitmap(RetrievalImage);
		  break;
		  case 2:
			m_RetrievalImage2.SetBitmap(RetrievalImage);
		  break;
		  case 3:
			m_RetrievalImage3.SetBitmap(RetrievalImage);
		  break;
		  case 4:
			m_RetrievalImage4.SetBitmap(RetrievalImage);
		  break;
		  case 5:
			m_RetrievalImage5.SetBitmap(RetrievalImage);
		  break;
		  case 6:
			m_RetrievalImage6.SetBitmap(RetrievalImage);
		  break;
		  case 7:
			m_RetrievalImage7.SetBitmap(RetrievalImage);
		  break;
		  case 8:
			m_RetrievalImage8.SetBitmap(RetrievalImage);
		  break;
		  case 9:
			m_RetrievalImage9.SetBitmap(RetrievalImage);
		  break;
		  case 10:
			m_RetrievalImage10.SetBitmap(RetrievalImage);
		  break;
		  case 11:
			m_QueryImage.SetBitmap(RetrievalImage);
		  break;
		  default:
		  break;
	}
	::DeleteObject(RetrievalImage);
	return 0;

}


void CMy3DRetrievalView::DisplayRetrieval()
{
	CMy3DRetrievalDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	HBITMAP RetrievalImage;
	int displayWidth;
    int displayHeight;
	displayWidth=SuitableWidth(160,120,160,160);
    displayHeight=SuitableHeight(160,120,160,160);
if (m_CurrentPage == 1)
{
	if (DisplayModelNum>1)
	{
		char temp1[MAX_PATH];
		sprintf(temp1,   "%s", pDoc->m_saModelimagename[pDoc->display_num[0]+1]);
		DisplayJpegFile(temp1,1,displayWidth,displayHeight);
		m_RetrievalInfor1=pDoc->m_saModelfilename[pDoc->display_num[0]+1];
	}
	if (DisplayModelNum>2)
	{
		char temp2[MAX_PATH];
		sprintf(temp2,   "%s", pDoc->m_saModelimagename[pDoc->display_num[1]+1]);
		DisplayJpegFile(temp2,2,displayWidth,displayHeight);
		m_RetrievalInfor2=pDoc->m_saModelfilename[pDoc->display_num[1]+1];
	}
	if (DisplayModelNum>=3)
	{
		char temp3[MAX_PATH];
		sprintf(temp3,   "%s", pDoc->m_saModelimagename[pDoc->display_num[2]+1]);
		DisplayJpegFile(temp3,3,displayWidth,displayHeight);
		m_RetrievalInfor3=pDoc->m_saModelfilename[pDoc->display_num[2]+1];
	}
	if (DisplayModelNum>=4)
	{
		char temp4[MAX_PATH];
		sprintf(temp4,   "%s", pDoc->m_saModelimagename[pDoc->display_num[3]+1]);
		DisplayJpegFile(temp4,4,displayWidth,displayHeight);
		m_RetrievalInfor4=pDoc->m_saModelfilename[pDoc->display_num[3]+1];
	}
	if (DisplayModelNum>=5)
	{
		char temp5[MAX_PATH];
		sprintf(temp5,   "%s", pDoc->m_saModelimagename[pDoc->display_num[4]+1]);
		DisplayJpegFile(temp5,5,displayWidth,displayHeight);
		m_RetrievalInfor5=pDoc->m_saModelfilename[pDoc->display_num[4]+1];
	}
	if (DisplayModelNum>=6)
	{
		char temp6[MAX_PATH];
		sprintf(temp6,   "%s", pDoc->m_saModelimagename[pDoc->display_num[5]+1]);
		DisplayJpegFile(temp6,6,displayWidth,displayHeight);
		m_RetrievalInfor6=pDoc->m_saModelfilename[pDoc->display_num[5]+1];
	}
	if (DisplayModelNum>=7)
	{
		char temp7[MAX_PATH];
		sprintf(temp7,   "%s", pDoc->m_saModelimagename[pDoc->display_num[6]+1]);
		DisplayJpegFile(temp7,7,displayWidth,displayHeight);
		m_RetrievalInfor7=pDoc->m_saModelfilename[pDoc->display_num[6]+1];
	}
	if (DisplayModelNum>=8)
	{
		char temp8[MAX_PATH];
		sprintf(temp8,   "%s", pDoc->m_saModelimagename[pDoc->display_num[7]+1]);
		DisplayJpegFile(temp8,8,displayWidth,displayHeight);
		m_RetrievalInfor8=pDoc->m_saModelfilename[pDoc->display_num[7]+1];
	}
	if (DisplayModelNum>=9)
	{
		char temp9[MAX_PATH];
		sprintf(temp9,   "%s", pDoc->m_saModelimagename[pDoc->display_num[8]+1]);
		DisplayJpegFile(temp9,9,displayWidth,displayHeight);
		m_RetrievalInfor9=pDoc->m_saModelfilename[pDoc->display_num[8]+1];
	}
	if (DisplayModelNum>=10)
	{
		char temp10[MAX_PATH];
		sprintf(temp10,   "%s", pDoc->m_saModelimagename[pDoc->display_num[9]+1]);
		DisplayJpegFile(temp10,10,displayWidth,displayHeight);
		m_RetrievalInfor10=pDoc->m_saModelfilename[pDoc->display_num[9]+1];
	}
}
else
{
	if (DisplayModelNum>11)
	{
		char temp1[MAX_PATH];
		sprintf(temp1,   "%s", pDoc->m_saModelimagename[pDoc->display_num[10]+1]);
		DisplayJpegFile(temp1,1,displayWidth,displayHeight);
		m_RetrievalInfor1=pDoc->m_saModelfilename[pDoc->display_num[10]+1];
	}
	if (DisplayModelNum>12)
	{
		char temp2[MAX_PATH];
		sprintf(temp2,   "%s", pDoc->m_saModelimagename[pDoc->display_num[11]+1]);
		DisplayJpegFile(temp2,2,displayWidth,displayHeight);
		m_RetrievalInfor2=pDoc->m_saModelfilename[pDoc->display_num[11]+1];
	}
	if (DisplayModelNum>=13)
	{
		char temp3[MAX_PATH];
		sprintf(temp3,   "%s", pDoc->m_saModelimagename[pDoc->display_num[12]+1]);
		DisplayJpegFile(temp3,3,displayWidth,displayHeight);
		m_RetrievalInfor3=pDoc->m_saModelfilename[pDoc->display_num[12]+1];
	}
	if (DisplayModelNum>=14)
	{
		char temp4[MAX_PATH];
		sprintf(temp4,   "%s", pDoc->m_saModelimagename[pDoc->display_num[13]+1]);
		DisplayJpegFile(temp4,4,displayWidth,displayHeight);
		m_RetrievalInfor4=pDoc->m_saModelfilename[pDoc->display_num[13]+1];
	}
	if (DisplayModelNum>=15)
	{
		char temp5[MAX_PATH];
		sprintf(temp5,   "%s", pDoc->m_saModelimagename[pDoc->display_num[14]+1]);
		DisplayJpegFile(temp5,5,displayWidth,displayHeight);
		m_RetrievalInfor5=pDoc->m_saModelfilename[pDoc->display_num[14]+1];
	}
	if (DisplayModelNum>=16)
	{
		char temp6[MAX_PATH];
		sprintf(temp6,   "%s", pDoc->m_saModelimagename[pDoc->display_num[15]+1]);
		DisplayJpegFile(temp6,6,displayWidth,displayHeight);
		m_RetrievalInfor6=pDoc->m_saModelfilename[pDoc->display_num[15]+1];
	}
	if (DisplayModelNum>=17)
	{
		char temp7[MAX_PATH];
		sprintf(temp7,   "%s", pDoc->m_saModelimagename[pDoc->display_num[16]+1]);
		DisplayJpegFile(temp7,7,displayWidth,displayHeight);
		m_RetrievalInfor7=pDoc->m_saModelfilename[pDoc->display_num[16]+1];
	}
	if (DisplayModelNum>=18)
	{
		char temp8[MAX_PATH];
		sprintf(temp8,   "%s", pDoc->m_saModelimagename[pDoc->display_num[17]+1]);
		DisplayJpegFile(temp8,8,displayWidth,displayHeight);
		m_RetrievalInfor8=pDoc->m_saModelfilename[pDoc->display_num[17]+1];
	}
	if (DisplayModelNum>=19)
	{
		char temp9[MAX_PATH];
		sprintf(temp9,   "%s", pDoc->m_saModelimagename[pDoc->display_num[18]+1]);
		DisplayJpegFile(temp9,9,displayWidth,displayHeight);
		m_RetrievalInfor9=pDoc->m_saModelfilename[pDoc->display_num[18]+1];
	}
	if (DisplayModelNum>=20)
	{
		char temp10[MAX_PATH];
		sprintf(temp10,   "%s", pDoc->m_saModelimagename[pDoc->display_num[19]+1]);
		DisplayJpegFile(temp10,10,displayWidth,displayHeight);
		m_RetrievalInfor10=pDoc->m_saModelfilename[pDoc->display_num[19]+1];
	}

}




	/*
	//ÏÔÊ¾10¸öÍ¼Ïñ
	for (int j=0;j<11;j++)
	{
		char temp1[MAX_PATH];
		sprintf(temp1,   "%s", pDoc->m_saModelimagename[j*13]);
		DisplayJpegFile(temp1,j,displayWidth,displayHeight);
	}
	*/

	UpdateData(NULL);
}




