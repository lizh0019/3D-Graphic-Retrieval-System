// 3DRetrievalDoc.cpp : implementation of the CMy3DRetrievalDoc class
//

#include "stdafx.h"
#include "3DRetrieval.h"

#include "3DRetrievalDoc.h"
#include "3DRetrievalView.h"
#include "ThreeD.h"
#include "DialogDatabase.h"
#include "DialogFeatureSelection.h"
#include "offviewer.cpp"
#include "Jpeg.h"
#include "RetrievalMethod.h"
#include <io.h>
#include <FCNTL.h>
#include <SYS\STAT.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy3DRetrievalDoc

IMPLEMENT_DYNCREATE(CMy3DRetrievalDoc, CDocument)

BEGIN_MESSAGE_MAP(CMy3DRetrievalDoc, CDocument)
	//{{AFX_MSG_MAP(CMy3DRetrievalDoc)
	ON_COMMAND(ID_DateBase_SelectDataBase, OnDateBaseSelectDataBase)
	ON_COMMAND(ID_FILE_OPEN3DMODEL, OnFileOpen3dmodel)
	ON_BN_CLICKED(ID_FILE_DisplaytModel, OnFILEDisplaytModel)
	ON_BN_CLICKED(IDC_STARTQUERY, OnStartquery)
	ON_BN_CLICKED(IDC_STATIC_RetrievalResults1, OnSTATICRetrievalResults1)
	ON_BN_CLICKED(IDC_STATIC_RetrievalResults2, OnSTATICRetrievalResults2)
	ON_BN_CLICKED(IDC_STATIC_RetrievalResults3, OnSTATICRetrievalResults3)
	ON_BN_CLICKED(IDC_STATIC_RetrievalResults4, OnSTATICRetrievalResults4)
	ON_COMMAND(ID_File_FeatureEXtracting, OnFileFeatureEXtracting)
	ON_COMMAND(DataBase_FeatrueExtract, OnDataBaseFeatrueExtract)
	ON_BN_CLICKED(IDC_STATIC_RetrievalResults5, OnSTATICRetrievalResults5)
	ON_BN_CLICKED(IDC_STATIC_RetrievalResults6, OnSTATICRetrievalResults6)
	ON_BN_CLICKED(IDC_STATIC_RetrievalResults7, OnSTATICRetrievalResults7)
	ON_BN_CLICKED(IDC_STATIC_RetrievalResults8, OnSTATICRetrievalResults8)
	ON_BN_CLICKED(IDC_STATIC_RetrievalResults9, OnSTATICRetrievalResults9)
	ON_BN_CLICKED(IDC_STATIC_RetrievalResults10, OnSTATICRetrievalResults10)
	ON_BN_CLICKED(IDC_PREVIOUSPAGE, OnPreviouspage)
	ON_BN_CLICKED(IDC_NEXTPAGE, OnNextpage)
	ON_BN_CLICKED(IDC_Feature_D2, OnQueryFeatureD2)
	ON_BN_CLICKED(IDC_Feature_D1, OnFeatureD1)
	ON_BN_CLICKED(IDC_Feature_D3, OnFeatureD3)
	ON_BN_CLICKED(IDC_Feature_A3, OnFeatureA3)
	ON_BN_CLICKED(IDC_Feature_MyOwen, OnFeatureMyOwen)
	ON_COMMAND(ID_DateBase_FeatureExtract_D1, OnDateBaseFeatureExtractD1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy3DRetrievalDoc construction/destruction

CMy3DRetrievalDoc::CMy3DRetrievalDoc()
{
	// TODO: add one-time construction code here
	m_TotalNumMedol=0;
	m_dDisplayNumber=0; // for temp initial
	m_ipage=0;

	QueryVariableInitial();
	DataBaseVariableinitialize();

	GetCurrentDirectory(_MAX_PATH,m_CurrentDirectory);
	OpenStandardBMPHeader();
}

CMy3DRetrievalDoc::~CMy3DRetrievalDoc()
{
}

BOOL CMy3DRetrievalDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMy3DRetrievalDoc serialization

void CMy3DRetrievalDoc::Serialize(CArchive& ar)
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
// CMy3DRetrievalDoc diagnostics

#ifdef _DEBUG
void CMy3DRetrievalDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy3DRetrievalDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMy3DRetrievalDoc commands

void CMy3DRetrievalDoc::OnDateBaseSelectDataBase() 
{
	// TODO: Add your command handler code here
	m_bDisplayRetrieval = false; // Shut the Retrieval Display When Select a new Database.
	CDialogDataBase myDialogDatabase;//Create Database Dialog
	myDialogDatabase.m_Path=m_OldDataBasePath;//The old directory
	if(myDialogDatabase.DoModal()!=IDOK)//If the path selection canceled
	{
		m_DataBasePathChange=false;//no changed, remain the old path
		return;
	}
	if(m_OldDataBasePath==myDialogDatabase.m_Path)//If the path isn't changed
	{
		m_DataBasePathChange=false;//no changed, remain the old path
		return;
	}

	DataBaseVariableinitialize();
	m_OldDataBasePath=myDialogDatabase.m_Path;
	BeginWaitCursor();
	//Get the image number by file ext
	//If overflowed
	if(GetApproximateImagesNumber(m_OldDataBasePath,&m_TotalNumMedol)==false)
	{
		m_TotalNumMedol=0;
		MessageBox(NULL,"The number of Models has overflowed in the selected path!","Error",MB_OK|MB_ICONSTOP);
		m_OldDataBasePath="No Model database is selected!";
		UpdateAllViews(NULL);
		EndWaitCursor();
		return;
	}
	//If there are no models
	if(m_TotalNumMedol==0)
	{
		m_OldDataBasePath="No Model database is selected!";
		MessageBox(NULL,"No Model is in the selected path!","Error",MB_OK|MB_ICONSTOP);
		UpdateAllViews(NULL);
		EndWaitCursor();
		return;
	}
	///Obtain the exact image number
/*	if(GetValidImagesNumber(m_sDatabasePath,&m_validnum)==false)
	{
		m_validnum=MAX_IMAGE_NUMBER;
		MessageBox(NULL,"The number of images in the selected path is larger than 500000, this sytem can only deal with first 500000 images!","Information",MB_OK|MB_ICONINFORMATION);
		UpdateAllViews(NULL);
		EndWaitCursor();
		return;
	}

	if(m_validnum==0)//If No valid images
	{
		m_sDatabasePath="No image database is selected!";
		MessageBox(NULL,"No valid image is in the selected path!","Error!",MB_OK|MB_ICONSTOP);
		UpdateAllViews(NULL);
		EndWaitCursor();
		return;
	}
	*/
	m_DataBaseOpened=true;
	m_DataBasePathChange=true;
	UpdateAllViews(NULL);
	EndWaitCursor();
	
}
// One picture for One model;
BOOL CMy3DRetrievalDoc::GetApproximateImagesNumber(CString sPath, long *number)
{
	CFileFind file;
	CString str;
	str=sPath;
	BOOL bContinueNumber;
    
    if(str.Right(1)!="\\")str+="\\";
	str+="*.off";
	bContinueNumber=file.FindFile(str);
	while(bContinueNumber)
	{
		bContinueNumber=file.FindNextFile();
		if(!file.IsDirectory()&&!file.IsDots())
		{
			*number=*number+1;
			if(*number<0)return false;
			if(*number>=MAX_MODEL_NUMBER)return false;
			m_saModelfilename[*number]=file.GetFilePath();
			// Change Model filename to Image filename
			CString temp; //for the m_sQueryImagePath;
			temp = m_saModelfilename[*number];
			temp.Replace( ".off", "_thumb.jpg" );
			m_saModelimagename[*number]= temp;
			temp.Replace("_thumb.jpg","D2Feature.txt");
			m_sDataBaseFeatrue[*number]= temp; //for the D1 Database Feature;
			temp.Replace("D2Feature.txt","D1Feature.txt");
			m_sDataBaseFeatrue_D1[*number]= temp; // for the D2 DataBase Feature;
		}
	}
    
	//For sub-directory	
	file.Close();
	str.Empty();
	str=sPath;
	if(str.Right(1)!="\\")str+="\\";
	str+="*.*";
	bContinueNumber=file.FindFile(str);
	while(bContinueNumber)
	{
		bContinueNumber=file.FindNextFile();
		if (file.IsDots()) continue;
		else if(file.IsDirectory())
		{
			GetApproximateImagesNumber(file.GetFilePath(),number);
			if(*number<0)return false;
			if(*number>=MAX_MODEL_NUMBER)return false;
		}
	}
	return true;

}

void CMy3DRetrievalDoc::DataBaseVariableinitialize()
{
	m_OldDataBasePath = _T("");
	m_DataBasePathChange = FALSE;
	m_TotalNumMedol = 0;
	m_DataBaseOpened = FALSE;
	m_bDataBaseFeatureExtracted = FALSE;

	
//	modelfilename=NULL;

	
}

void CMy3DRetrievalDoc::OnFileOpen3dmodel() 
{
	// TODO: Add your command handler code here
	
	
	///return 0;
//	if(mesh2){
//		 mesh2->~Mesh();	
//	}
	ThreeD thd;
	//	Plane();
	int pointnumber;
	CString filename;
    pointnumber=thd.Read3D_OFF(filename);  /**/
    wholeshow=1;
	WholeDataProcessing();
	UpdateAllViews(NULL);
	
	//char filename[1024]="C:\\model\\snake";
	//char *filename=NULL;filename=ParseArgs(argc,argv,filename);
	//char filename1[1024];strcpy(filename1,"");
	//	char filename2[1024];strcpy(filename2,"");
	//	char filename3[1024];strcpy(filename3,"");
	//	strcat(filename1,filename);strcat(filename1,"watermarked.off");
	//	strcat(filename2,filename);strcat(filename2,"attacked.off");
	//	strcat(filename3,filename);strcat(filename3,"recovered.off");
	//strcat(filename,".off");
	

	mesh2 = ReadOffFile(filename);//orignal model

	float alpha0=0.0450,alpha1=0.2112;
	
	//SaveModified(filename3);
	
	int argc=1;
	char **argv;
	GLUTInit(&argc, argv);
	//if(formatright){
	GLUTMainLoop();  //draw mesh2 
	//}
}

void CMy3DRetrievalDoc::WholeDataProcessing()
{

	int i;
	int minx;
	int miny;
	int minz;
	int sumx;
	int sumy;
	int sumz;
	long float xcent;
	long float ycent;
	long float zcent;
	int modify;
	/*平移坐标系 */

minx=data[0][0];
miny=data[0][1];
minz=data[0][2];
  for(i=0;i<pointnumber;i++)
   {        
	  if (minx>data[i][0]) 
	  {minx=data[i][0];
	  }
	  if (miny>data[i][1]) 
	  {miny=data[i][1];
	  }
	  if (minz>data[i][2]) 
	  {minz=data[i][2];
	  }
   
   }   
  for(i=0;i<pointnumber;i++)
   {        
	 data[i][0]=data[i][0]-minx;
     data[i][1]=data[i][1]-miny;
	 data[i][2]=data[i][2]-minz;
  } 
  

/*找出归一化系数/**/
  modify=data[0][0];
  for(i=0;i<pointnumber;i++)
   {        
	  if (modify<data[i][0]) 
	  {modify=data[i][0];
	  }
	  if (modify<data[i][1]) 
	  {modify=data[i][1];
	  }
	  if (modify<data[i][2]) 
	  {modify=data[i][2];
	  }
    }
 /*求质心(centx,centy,centz)/**/
long float centx;
long float centy;
long float centz;
long float xx;
long float yy;
long float zz;
long float sumxx;
long float sumyy;
long float sumzz;
long float floatpointnumber;
sumxx=0.0;
sumyy=0.0;
sumzz=0.0;
floatpointnumber=pointnumber;
 for(i=0;i<pointnumber;i++)
   {        
	 xx=data[i][0];
     yy=data[i][1];
	 zz=data[i][2];
     sumxx=sumxx+xx;
     sumyy=sumyy+yy;
     sumzz=sumzz+zz;
  }
 centx=sumxx/floatpointnumber;
 centy=sumyy/floatpointnumber;
 centz=sumzz/floatpointnumber;

 /*产生一个新数组来存储要显示的数据 /**/
 long float modi;
 long float fx;
 long float fy;
 long float fz;
 modi=modify;
 for(i=0;i<pointnumber;i++)
   {        
	 fx=data[i][0];
     fy=data[i][1];
	 fz=data[i][2];
	 fx=fx-centx;
	 fy=fy-centy;
	 fz=fz-centz;
	 fx=fx/modi;
	 fy=fy/modi;
	 fz=fz/modi;
	 mod[i][0]=fx;
     mod[i][1]=fy;
	 mod[i][2]=fz;
  }

}

//The Overloaded function Open Query image
BOOL CMy3DRetrievalDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
	{
		UpdateAllViews(NULL);
 		MessageBox(NULL,"We Cannot Open the File You Choose!","Error",MB_ICONSTOP|MB_OK);
		return FALSE;
	}
	//If the same image is opened, just jump over
	if(m_sQueryModelPath==lpszPathName) 
		return FALSE;
	//the initial status
 	QueryVariableInitial();
	CString Pathname;
	Pathname=lpszPathName;
	if (Pathname.Right(3)!="off")
	{
		UpdateAllViews(NULL);
		MessageBox(NULL,"We Cann't open or deal with the File You Choose!","Error",MB_OK|MB_ICONSTOP);
 		return FALSE;
	}
	CString temp; //for the m_sQueryImagePath;
	temp = lpszPathName;
	BeginWaitCursor();
	mesh1= ReadOffFile(temp);  // read the off file to mesh1;
	temp.Replace( ".off", "_thumb.jpg" );
	ReadQueryImage((CString)temp,&m_vQueryFeatureVector);
	EndWaitCursor();
	m_bFileOpen=TRUE;
	m_bQueryModelChanged=TRUE;
	m_bDisplayRetrieval = FALSE;
	m_sQueryModelPath=lpszPathName;
	m_sQueryImagePath = temp;
	temp.Empty(); //empty the CString;
	UpdateAllViews(NULL);
	return TRUE;
}

void CMy3DRetrievalDoc::QueryVariableInitial()
{
	m_bFileOpen=false;//The Query image is not opened
	m_bQueryModelChanged=false;//The query file is not changed
	m_bQueryModelFeatrueEXtracted = false; // The feature of the model is not extracted;
	m_bQueryModelFeatrueEXtracted_D1=false;
	m_iRetrievalMethod = 0; // initial for nothing;
	bins = NULL;
	histogram =NULL;
	for (int i=0;i<20;i++)
	{
		display_num[i] = 0;
	}


}

void CMy3DRetrievalDoc::OpenStandardBMPHeader()
{
	Success=TRUE;
    long int fh;
    LPBITMAPFILEHEADER bitfile;
    LPBITMAPINFOHEADER bitinfo;
    //open the standard file
	fh=_open("standard.dat",_O_RDONLY|_O_BINARY);
	if(fh==-1)
	{
		MessageBox(NULL,"[standard.dat] no found or error!","Initial",MB_ICONSTOP|MB_OK);
		Success=FALSE;
		return;
	}
    //Read file
    if(_read(fh,m_StandardBmpInfo,1078)==-1)
    {
		_close(fh);   
		MessageBox(NULL,"[standard.dat] read error!","Initial",MB_ICONSTOP|MB_OK);
		Success=FALSE;
		return;
    }
    _close(fh);   
    //Read Infomation
	bitfile=(LPBITMAPFILEHEADER)m_StandardBmpInfo;
    bitinfo=(LPBITMAPINFOHEADER)(m_StandardBmpInfo+sizeof(BITMAPFILEHEADER));
    //Judge the information of the standard file
	if(bitfile->bfType!=0x4d42||bitfile->bfOffBits!=1078||bitinfo->biBitCount!=8||bitinfo->biCompression!=0)
	{
		MessageBox(NULL,"[standard.dat] format error!","Initial",MB_ICONSTOP|MB_OK);
		Success=FALSE;
		return;
	}
	
	fh=_open("standardc.dat",_O_RDONLY|_O_BINARY);
	if(fh==-1)
	{
		MessageBox(NULL,"[standardc.dat] no found or error!","Initial",MB_ICONSTOP|MB_OK);
		Success=FALSE;
		return;
	}
    //Read file
    if(_read(fh,m_StandardBmpInfoc,54)==-1)
    {
		_close(fh);   
		MessageBox(NULL,"[standardc.dat] read fail!","Initial",MB_ICONSTOP|MB_OK);
		Success=FALSE;
		return;
    }
    _close(fh);   
    //Read Infomation
	bitfile=(LPBITMAPFILEHEADER)m_StandardBmpInfoc;
    bitinfo=(LPBITMAPINFOHEADER)(m_StandardBmpInfoc+sizeof(BITMAPFILEHEADER));
    //Judge the information of the standard file
	if(bitfile->bfType!=0x4d42||bitfile->bfOffBits!=54||bitinfo->biBitCount!=24||bitinfo->biCompression!=0)
	{
		MessageBox(NULL,"[standardc.dat] format error!","Initial",MB_ICONSTOP|MB_OK);
        Success=FALSE;
		return;
	}
}


int CMy3DRetrievalDoc::ReadQueryImage(CString ImagePathName, PFEATUREVECTOR FeatureVector)
{
	unsigned int x,y;
	int type=-1;
	int iBitCount;
	int PaletteNumber;  //PaletteNumber
	long int fh;
	LONG ImageWidth;
	LONG ImageHeight;
	unsigned long int linebytes;
	CFile file;
	CJpeg jpg;
	CString temp;
	BYTE *p1,*p2,*p3;
	DWORD m_ibfbts,m_iImageSize;
	JPEG_IMAGE_INFO info;
	LPBITMAPFILEHEADER bitfile;
    LPBITMAPINFOHEADER bitinfo;
	
	//open new query image
	if(file.Open(ImagePathName,CFile::modeRead,NULL)==NULL)return -1;
	m_iImageSize=file.GetLength();//get the query image size
	Imagehg=NULL;//Clear the old Query image memory
	Imagehg=GlobalAlloc(GMEM_FIXED,m_iImageSize*2);//apply new query image memory
	if(Imagehg==NULL)
	{
	  file.Close();
	  return -2;
	}
	m_ModelImageFile=(unsigned char *)Imagehg;
	m_bQueryImageData=(BYTE *)(m_ModelImageFile+m_iImageSize);
	if(file.Read(m_ModelImageFile,m_iImageSize)!=m_iImageSize)
	{
	  file.Close();
	  GlobalFree(Imagehg);
	  return -2;
	}
	file.Close();//close the file
	bitfile=(LPBITMAPFILEHEADER)m_ModelImageFile;
	bitinfo=(LPBITMAPINFOHEADER)(m_ModelImageFile+sizeof(BITMAPFILEHEADER));
	m_ibfbts=bitfile->bfOffBits;
    ImageWidth=bitinfo->biWidth;
	ImageHeight=bitinfo->biHeight;
	iBitCount=bitinfo->biBitCount;
	type=0;
	if(bitfile->bfType!=0x4d42)
	{
        GlobalFree(Imagehg);//Free the memory
		
		//Reopen the file
		if(jpg.open(ImagePathName,IDCT_INT))
		{ 
		  jpg.getImageInfo(&info);
		  temp=m_CurrentDirectory;
		  temp=temp+"\\tempquery.bmp";
		  fh=_open(temp,_O_BINARY|_O_WRONLY|_O_CREAT|_O_TRUNC,_S_IREAD|_S_IWRITE);
		  if(fh==-1)
		  { 
	        jpg.close();
			return -1;
		  }
		  if(info.comNum==3)
		  {
		    bitfile=(LPBITMAPFILEHEADER)m_StandardBmpInfoc;
            bitinfo=(LPBITMAPINFOHEADER)(m_StandardBmpInfoc+sizeof(BITMAPFILEHEADER));
            bitinfo->biHeight=info.imgHeight;
            bitinfo->biWidth=info.imgWidth;
			ImageWidth=bitinfo->biWidth;
	        ImageHeight=bitinfo->biHeight;
		    linebytes=(info.imgWidth*24+31)/32*4;
			m_ibfbts=bitfile->bfOffBits;
			iBitCount=bitinfo->biBitCount;
			bitfile->bfSize=info.imgHeight*linebytes+54;
		    bitinfo->biSizeImage=info.imgHeight*linebytes;
		    p1=info.image[0];
		    p2=info.image[1];
		    p3=info.image[2];
			m_iImageSize=bitfile->bfSize;
		    Imagehg=GlobalAlloc(GMEM_FIXED,m_iImageSize*2);//Apply the required memory
			////If memory is not enough, return directly
            if(Imagehg==NULL)
			{
              _close(fh); //Close the file
	          jpg.close();
			  return -2;
			}
            m_ModelImageFile=(unsigned char *)Imagehg;//Give the memory pointer to the file data pointer
			m_bQueryImageData=(BYTE *)(m_ModelImageFile+m_iImageSize);
	        memcpy(m_ModelImageFile,m_StandardBmpInfoc,54);
			for(y=0;y<info.imgHeight;y++)
			{
	          p1=info.image[0]+y*info.bufWidth;
			  p2=info.image[1]+y*info.bufWidth;
			  p3=info.image[2]+y*info.bufWidth;
			  for(x=0;x<linebytes/3;x++)
			  {
			    if(x<info.imgWidth)
				{
				  m_ModelImageFile[54+(info.imgHeight-y-1)*linebytes+x*3]=*p3++;
				  m_ModelImageFile[54+(info.imgHeight-y-1)*linebytes+x*3+1]=*p2++;
				  m_ModelImageFile[54+(info.imgHeight-y-1)*linebytes+x*3+2]=*p1++;
				}
			  }
			}
		  }
		  else
		  {
		    bitfile=(LPBITMAPFILEHEADER)m_StandardBmpInfo;
            bitinfo=(LPBITMAPINFOHEADER)(m_StandardBmpInfo+sizeof(BITMAPFILEHEADER));
		    bitinfo->biHeight=info.imgHeight;
            bitinfo->biWidth=info.imgWidth;
			ImageWidth=bitinfo->biWidth;
	        ImageHeight=bitinfo->biHeight;
			m_ibfbts=bitfile->bfOffBits;
			iBitCount=bitinfo->biBitCount;
		    linebytes=(info.imgWidth+3)/4*4;
		    bitfile->bfSize=info.imgHeight*linebytes+1078;
		    bitinfo->biSizeImage=info.imgHeight*linebytes;
		    m_iImageSize=bitfile->bfSize;
		    Imagehg=GlobalAlloc(GMEM_FIXED,m_iImageSize*2);//Apply the required memory
            ////If memory is not enough, return directly
            if(Imagehg==NULL)
			{
              _close(fh); //Close the file
	          jpg.close();
			  return -2;
			}
            m_ModelImageFile=(unsigned char *)Imagehg;//Give the memory pointer to the file data pointer
			m_bQueryImageData=(BYTE *)(m_ModelImageFile+m_iImageSize);
	        memcpy(m_ModelImageFile,m_StandardBmpInfo,1078);
			p1=info.image[0];
			for(y=0;y<info.imgHeight;y++)
			{
			  memcpy(m_ModelImageFile+1078+(info.imgHeight-y-1)*linebytes,p1,linebytes);
			  p1=p1+info.bufWidth;
			}
		  }
		  if(_write(fh,m_ModelImageFile,m_iImageSize)!=(int)m_iImageSize)
		  {
		    _close(fh);
		    GlobalFree(Imagehg);
            jpg.close();
		    return -2;
		  }
		  _close(fh);
		  jpg.close();
		  type=1;
  	    }
		else
 		   return -3;
		}
		////If the image is a 256-gray/24bits image or not
		if(bitinfo->biBitCount!=8&&bitinfo->biBitCount!=24)
		{
			GlobalFree(Imagehg);//Free the memory
			return -3;
		}
		////If the image is compressed or not
		if(bitinfo->biCompression!=0)
		{
			GlobalFree(Imagehg);//Free the memory
			return -3;
		}
		if(bitinfo->biBitCount==24)//No palette
			PaletteNumber=0;
		else if (bitinfo->biClrUsed==0) 
			PaletteNumber=(int)pow(2,bitinfo->biBitCount);
		else
			PaletteNumber=bitinfo->biClrUsed;
		
		///Check Palette
		if(m_ibfbts!=(int)(sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+PaletteNumber*sizeof(RGBQUAD)))
		{
			GlobalFree(Imagehg);//Free the memory
			return -3;
		}
		//File size judgement
		switch(iBitCount)
		{
		case 24:
			if(m_iImageSize-m_ibfbts-WIDTHBYTES(24*ImageWidth)*ImageHeight<0) 
			{
				GlobalFree(Imagehg);//Free the memory
				return -3;
			}
			break;
		case 8:
			if (m_iImageSize-m_ibfbts-SAVEWIDTH(ImageWidth)*ImageHeight<0) 
			{
				GlobalFree(Imagehg);//Free the memory
				return -3;
			}
			break;
		default:
			GlobalFree(Imagehg);//Free the memory
			return -3;
			break;
		} 
		strcpy(FeatureVector->m_sOriginalFileName,ImagePathName);///The filename
		FeatureVector->m_bType= type;
		FeatureVector->m_bBitCount=iBitCount;  ///The bits
		FeatureVector->m_lImageWidth=ImageWidth;    //The width
		FeatureVector->m_lImageHeight=ImageHeight;  ///The height
		//Get the RGB data from m_QueryImageFile
	//	MyRetrieveMethod.get_data_from_24or8bits_bmp_file(m_QueryImageFile,m_bQueryImageData,iBitCount,ImageWidth,ImageHeight);
		///end of Read Query Image
   return 0;
}

void CMy3DRetrievalDoc::OnFILEDisplaytModel() 
{
	// TODO: Add your control notification handler code here
	if (m_bFileOpen==TRUE)
	{
		BeginWaitCursor();
		mesh2 = mesh1;

		float alpha0=0.0450,alpha1=0.2112;
		
		//SaveModified(filename3);
		
		int argc=1;
		char **argv;
		GLUTInit(&argc, argv);
		EndWaitCursor();
		//if(formatright){
		GLUTMainLoop();  //draw mesh2 
	//}
	}
	else
	{
		MessageBox(NULL,"Please open a Model first","Error",MB_OK|MB_ICONSTOP);
	}
}

void CMy3DRetrievalDoc::OnStartquery() 
{
	// TODO: Add your control notification handler code here
	if (m_DataBaseOpened==FALSE)
	{
		MessageBox(NULL,"Please Select The DataBase First!","Error",MB_OK|MB_ICONSTOP);
	} 
	else if (m_bFileOpen==FALSE)
	{
		MessageBox(NULL,"Please Select The Query Model First!","Error",MB_OK|MB_ICONSTOP);
	}
	else if (m_iRetrievalMethod == 0)
	{
		MessageBox(NULL,"Please Extract the Feature First!","Error",MB_OK|MB_ICONSTOP);
	}
	else
	{
		if (m_iRetrievalMethod == 1)  // D2 Feature 
		{
			CString tempx = m_CurrentDirectory;
			tempx = tempx+"\\feature.txt"; //the feature file name;		
			int *arry;
			arry = new int[m_TotalNumMedol];
			//arry = MyRetrievalMethod.readfeaturefile(tempx);
			arry= MyRetrievalMethod.ComputeDistance((CString)tempx,m_sDataBaseFeatrue,m_TotalNumMedol);		
			MyRetrievalMethod.Retrieval20Result(arry,display_num,m_TotalNumMedol);
			delete[]arry;
			m_bDisplayRetrieval = TRUE;	
			m_dDisplayNumber = 20;
			m_ipage = 1;
		}

		if (m_iRetrievalMethod == 2) // D1 Feature
		{
			CString tempx = m_CurrentDirectory;
			tempx = tempx+"\\feature_D1.txt"; //the feature file name;		
			int *arry;
			arry = new int[m_TotalNumMedol];
			//arry = MyRetrievalMethod.readfeaturefile(tempx);
			arry= MyRetrievalMethod.ComputeDistance((CString)tempx,m_sDataBaseFeatrue_D1,m_TotalNumMedol);		
			MyRetrievalMethod.Retrieval20Result(arry,display_num,m_TotalNumMedol);
			delete[]arry;
			m_bDisplayRetrieval = TRUE;	
			m_dDisplayNumber = 20;
			m_ipage = 1;	
		}
	}
		UpdateAllViews(NULL);
}



void CMy3DRetrievalDoc::OnSTATICRetrievalResults1() 
{
	// TODO: Add your control notification handler code here
		if (m_ipage==1)
		{
			BeginWaitCursor();
			mesh2 = ReadOffFile(m_saModelfilename[display_num[0]+1]);//orignal model
			
			float alpha0=0.0450,alpha1=0.2112;
			
			//SaveModified(filename3);
			
			int argc=1;
			char **argv;
			GLUTInit(&argc, argv);
			EndWaitCursor();
			//if(formatright){
			GLUTMainLoop();  //draw mesh2 
		}
		else
		{
			BeginWaitCursor();
			mesh2 = ReadOffFile(m_saModelfilename[display_num[10]+1]);//orignal model
			
			float alpha0=0.0450,alpha1=0.2112;
			
			//SaveModified(filename3);
			
			int argc=1;
			char **argv;
			GLUTInit(&argc, argv);
			EndWaitCursor();
			//if(formatright){
			GLUTMainLoop();  //draw mesh2 

		}
  

	
}

void CMy3DRetrievalDoc::OnSTATICRetrievalResults2() 
{
	// TODO: Add your control notification handler code here
	if (m_ipage==1)
	{
		BeginWaitCursor();
		mesh2 = ReadOffFile(m_saModelfilename[display_num[1]+1]);//orignal model
		
		float alpha0=0.0450,alpha1=0.2112;
		
		//SaveModified(filename3);
		
		int argc=1;
		char **argv;
		GLUTInit(&argc, argv);
		EndWaitCursor();
		//if(formatright){
		GLUTMainLoop();  //draw mesh2 
	}
	else{
		BeginWaitCursor();
		mesh2 = ReadOffFile(m_saModelfilename[display_num[11]+1]);//orignal model
		
		float alpha0=0.0450,alpha1=0.2112;
		
		//SaveModified(filename3);
		
		int argc=1;
		char **argv;
		GLUTInit(&argc, argv);
		EndWaitCursor();
		//if(formatright){
		GLUTMainLoop();  //draw mesh2 
	}
}

void CMy3DRetrievalDoc::OnSTATICRetrievalResults3() 
{
	// TODO: Add your control notification handler code here
	if (m_ipage==1)
	{
		BeginWaitCursor();
		mesh2 = ReadOffFile(m_saModelfilename[display_num[2]+1]);//orignal model
		
		float alpha0=0.0450,alpha1=0.2112;
		
		//SaveModified(filename3);
		
		int argc=1;
		char **argv;
		GLUTInit(&argc, argv);
		EndWaitCursor();
		//if(formatright){
		GLUTMainLoop();  //draw mesh2 
	}
	else{
		BeginWaitCursor();
		mesh2 = ReadOffFile(m_saModelfilename[display_num[12]+1]);//orignal model
		
		float alpha0=0.0450,alpha1=0.2112;
		
		//SaveModified(filename3);
		
		int argc=1;
		char **argv;
		GLUTInit(&argc, argv);
		EndWaitCursor();
		//if(formatright){
			GLUTMainLoop();  //draw mesh2 
	}

	
}

void CMy3DRetrievalDoc::OnSTATICRetrievalResults4() 
{
	// TODO: Add your control notification handler code here
	if (m_ipage==1)
	{
		BeginWaitCursor();
		mesh2 = ReadOffFile(m_saModelfilename[display_num[3]+1]);//orignal model
		
		float alpha0=0.0450,alpha1=0.2112;
		
		//SaveModified(filename3);
		
		int argc=1;
		char **argv;
		GLUTInit(&argc, argv);
		EndWaitCursor();
		//if(formatright){
		GLUTMainLoop();  //draw mesh2 
	}
	else
	{
		BeginWaitCursor();
		mesh2 = ReadOffFile(m_saModelfilename[display_num[13]+1]);//orignal model
		
		float alpha0=0.0450,alpha1=0.2112;
		
		//SaveModified(filename3);
		
		int argc=1;
		char **argv;
		GLUTInit(&argc, argv);
		EndWaitCursor();
		//if(formatright){
			GLUTMainLoop();  //draw mesh2 
	}

	
}

BOOL CMy3DRetrievalDoc::ExtractQueryModFeature()
{
	if (m_bFileOpen==TRUE)
	{
		if (m_bQueryModelFeatrueEXtracted == TRUE)
		{
			MessageBox(NULL,"Feature has been extracted!","Error",MB_OK|MB_ICONSTOP);
			return FALSE;
		}

	 m_vQueryFeatureVector.m_dOAverage=mesh1->meanscale;
	 CString temp ;
	 temp= _T("");
	 temp = m_CurrentDirectory;
	 FILE *fileout;
	 int line_col_num=0;
	 char   fileout_name[121];
	 temp = temp+"\\feature.txt"; //the feature file name;
	 strcpy(fileout_name,temp);
	 //open the file;
	 fileout = fopen(fileout_name,"w");
	 //begin sampling;

	 BeginWaitCursor();
	 Featurevertices();

//	 float max_distanc;
//	 max_distanc = Sampling(mesh1);
	 // if can not open the file;
	 if ( fileout == NULL )
	 {
		 MessageBox(NULL,"Can not open the output file","Error",MB_OK|MB_ICONSTOP);
		 return FALSE;
	 }
     // record the sampling distance;
//	 fprintf (fileout, "%f ", max_distanc);
//	 fprintf ( fileout, "\n" );
//	 line_col_num = line_col_num + 1;
	 for (int i=0;i<64;i++)
	 {
		 fprintf (fileout, "%d ", histogram[i]);
		 fprintf ( fileout, "\n" );
		 line_col_num = line_col_num + 1;
	 }
	 fclose(fileout);
	 EndWaitCursor();
	 m_bQueryModelFeatrueEXtracted = TRUE;
	 return TRUE;
	}
	else
	{
		MessageBox(NULL,"Please open a Model first","Error",MB_OK|MB_ICONSTOP);
		return FALSE;
	}

}

void CMy3DRetrievalDoc::OnFileFeatureEXtracting() 
{
	// TODO: Add your command handler code here
	ExtractQueryModFeature();
	m_iRetrievalMethod = 1; // default for D2 Feature;
	
}

/************************************************************************/
/* for D2 Feature Extract                                                     */
/************************************************************************/

int * CMy3DRetrievalDoc::bins1024()
{	double Dt;
	float max_magnitude;
	max_magnitude = 0.0;
	Dt = 0.0; // for initial;

	if (bins == NULL)
	{
		bins = new int[1024];
		assert(bins); 
	}

	for (int j=0;j<1024;j++)
	{
		bins[j]=0;
	}  //  initial bins;
		
	//sampling 10 times and get the averages;
	for (int h=0;h<5;h++)
	{
		max_magnitude = Sampling(mesh1); 
		Dt = (double) (max_magnitude/1024.0000);// normalize the distance between the sampling point;
		
		int temp=0;
		for (int i=0;i<1024*1024;i++)
		{
			temp = (int) (a_distance[i]/Dt);
			if (temp==1024)
			{
				bins[1023]++;
			}
			(bins[temp])++;
		}
		delete[]a_distance;
	}
	for (int d=0;d<1024;d++)
	{
		bins[d]=(int)(bins[d]/5);
	}
	
	return bins;
}

int * CMy3DRetrievalDoc::Featurevertices()
{	
	bins1024();  // run bins1024;
	if (histogram == NULL)
	{
		histogram = new int[64];
		assert(histogram);
	}
	for (int h=0;h<64;h++)
	{
		histogram[h] = 0;
	}  // applied the memory for the 64 feature vectors and initial it;
	
	int temp=0; // temp variable for the 16 bins numbers;
	int d=0;  // rockon by timw 
	int x=0;  // for the histogram;
	for (int n=0; n<1024;n++)
	{
		d++;
		temp = +bins[n];  // total of the 16 bins numbers;
		if (d==16)
		{
			histogram[x] = (int) temp/16;
			x++;
			temp = 0;
			d = 0;
		}
	
	}
	return histogram;
}
/************************************************************************/
/* for D1 Feature Extracted                                                                     */
/************************************************************************/
int * CMy3DRetrievalDoc::binsD1_1024()
{
	double Dt;
	float max_magnitude;
	max_magnitude = 0.0f;
	Dt = 0.0f; // for initial;
	
	if (bins == NULL)
	{
		bins = new int[1024];
		assert(bins); 
	}
	
	for (int j=0;j<1024;j++)
	{
		bins[j]=0;
	}  //  initial bins;
	
		//sampling
		SamplingD1(mesh1,max_magnitude); 

		Dt = (double) (max_magnitude/1024.0f); // normalize the distance between the sampling point;
		
		int temp=0;
		for (int i=0;i<1024*1024*5;i++)
		{
			temp = (int) (D1_distance[i]/Dt);
			if (temp==1024)
			{
				bins[1023]++;
			}
			(bins[temp])++;
		}
		delete[]D1_distance;
	// we have 1024*1024*5 distance... 
		for (int d=0;d<1024;d++)
		{
			bins[d]=(int)(bins[d]/5);
		}

	return bins;	
}

int * CMy3DRetrievalDoc::Featurevertices_D1()
{	
	binsD1_1024();  // run bins1024;
	if (histogram == NULL)
	{
		histogram = new int[64];
		assert(histogram);
	}
	for (int h=0;h<64;h++)
	{
		histogram[h] = 0;
	}  // applied the memory for the 64 feature vectors and initial it;
	
	int temp=0; // temp variable for the 16 bins numbers;
	int d=0;  // rockon by time 
	int x=0;  // for the histogram;
	for (int n=0; n<1024;n++)
	{
		d++;
		temp = +bins[n];  // total of the 16 bins numbers;
		if (d==16)
		{
			histogram[x] = (int) temp/16;
			x++;
			temp = 0;
			d = 0;
		}		
	}
	return histogram;
}
/************************************************************************/
/* For D3 Feature Vecters                                                                     */
/************************************************************************/




/************************************************************************************/

void CMy3DRetrievalDoc::OnDataBaseFeatrueExtract() 
{
	// TODO: Add your command handler code here
	CString temp;
	temp = m_saModelfilename[1];
	temp.Replace( ".off" , "D2Feature.txt");  //get the filename of the feature;

	if (m_DataBaseOpened == FALSE)
	{
		MessageBox(NULL,"Please Open the DataBase first!","Error",MB_OK|MB_ICONSTOP);
	}
	else if (GetFileAttributes(temp) != (DWORD)-1)
	{
		MessageBox(NULL,"The Features of the DataBase have been extracted!","Error",MB_OK|MB_ICONSTOP);
	}
	else	
	{
		DataBaseFeatureExtract();
	}
	m_bDataBaseFeatureExtracted = TRUE;
}

void CMy3DRetrievalDoc::DataBaseFeatureExtract()
{	BeginWaitCursor();
	for (int j=1;j<m_TotalNumMedol+1;j++)
	{
		CString temp;
		temp=m_saModelfilename[j];
        //read off file
		mesh1 = ReadOffFile(temp);
		CString temptxt; //for the feature vector;
		temptxt = m_saModelfilename[j];
		temptxt.Replace( ".off", "D2Feature.txt" );
		m_sDataBaseFeatrue[j]=temptxt;

		// for recording
		FILE *fileout;
		int line_col_num=0;  // the line_col_num;
		char   fileout_name[121];  // out file name;
		strcpy(fileout_name,temptxt);
		//open the file;
		fileout = fopen(fileout_name,"w");
		// Extract the Featruevertices;
		Featurevertices();  
		// if can not open the file;
		if ( fileout == NULL )
		{
			MessageBox(NULL,"Can not open the output file","Error",MB_OK|MB_ICONSTOP);
		}
		// record the Feature;
		for (int i=0;i<64;i++)
		{
			fprintf (fileout, "%d ", histogram[i]);
			fprintf ( fileout, "\n" );
			line_col_num = line_col_num + 1;
		}
		fclose(fileout);
		mesh1->~Mesh(); mesh1=NULL;
		
	}
	EndWaitCursor();
}

//DEL void CMy3DRetrievalDoc::OnForTesting() 
//DEL {
//DEL 	// TODO: Add your command handler code here
//DEL 	CString tempx = m_CurrentDirectory;
//DEL 	 tempx = tempx+"\\feature.txt"; //the feature file name;
//DEL 	
//DEL int *arry;
//DEL arry = new int[m_TotalNumMedol];
//DEL //arry = MyRetrievalMethod.readfeaturefile(tempx);
//DEL arry= MyRetrievalMethod.ComputeDistance((CString)tempx,m_sDataBaseFeatrue,m_TotalNumMedol);
//DEL 
//DEL MyRetrievalMethod.Retrieval20Result(arry,display_num,m_TotalNumMedol);
//DEL 
//DEL 
//DEL /*
//DEL CString temp = m_CurrentDirectory;
//DEL FILE *fileout;
//DEL int line_col_num=0;
//DEL char   fileout_name[121];
//DEL temp = temp+"\\distance.txt"; //the feature file name;
//DEL strcpy(fileout_name,temp);
//DEL //open the file;
//DEL fileout = fopen(fileout_name,"w");
//DEL //begin sampling;
//DEL 
//DEL BeginWaitCursor();
//DEL Featurevertices();
//DEL 
//DEL //	 float max_distanc;
//DEL //	 max_distanc = Sampling(mesh1);
//DEL // if can not open the file;
//DEL if ( fileout == NULL )
//DEL {
//DEL 	MessageBox(NULL,"Can not open the output file","Error",MB_OK|MB_ICONSTOP);
//DEL 
//DEL }
//DEL // record the sampling distance;
//DEL //	 fprintf (fileout, "%f ", max_distanc);
//DEL //	 fprintf ( fileout, "\n" );
//DEL //	 line_col_num = line_col_num + 1;
//DEL for (int i=0;i<m_TotalNumMedol;i++)
//DEL {
//DEL 	fprintf (fileout, "%d ", arry[i]);
//DEL 	fprintf ( fileout, "\n" );
//DEL 	line_col_num = line_col_num + 1;
//DEL }
//DEL fclose(fileout);
//DEL 	 EndWaitCursor();
//DEL 	 */
//DEL }

void CMy3DRetrievalDoc::OnSTATICRetrievalResults5() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	if (m_ipage==1)
	{
		BeginWaitCursor();
		mesh2 = ReadOffFile(m_saModelfilename[display_num[4]+1]);//orignal model
		
		float alpha0=0.0450,alpha1=0.2112;
		
		//SaveModified(filename3);
		
		int argc=1;
		char **argv;
		GLUTInit(&argc, argv);
		EndWaitCursor();
		//if(formatright){
		GLUTMainLoop();  //draw mesh2 
	}
	else
	{
		BeginWaitCursor();
		mesh2 = ReadOffFile(m_saModelfilename[display_num[14]+1]);//orignal model
		
		float alpha0=0.0450,alpha1=0.2112;
		
		//SaveModified(filename3);
		
		int argc=1;
		char **argv;
		GLUTInit(&argc, argv);
		EndWaitCursor();
		//if(formatright){
		GLUTMainLoop();  //draw mesh2 
	}

	
}

void CMy3DRetrievalDoc::OnSTATICRetrievalResults6() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	if (m_ipage==1)
	{
		BeginWaitCursor();
		mesh2 = ReadOffFile(m_saModelfilename[display_num[5]+1]);//orignal model
		
		float alpha0=0.0450,alpha1=0.2112;
		
		//SaveModified(filename3);
		
		int argc=1;
		char **argv;
		GLUTInit(&argc, argv);
		EndWaitCursor();
		//if(formatright){
		GLUTMainLoop();  //draw mesh2 
	}
	else
	{
		BeginWaitCursor();
		mesh2 = ReadOffFile(m_saModelfilename[display_num[15]+1]);//orignal model
		
		float alpha0=0.0450,alpha1=0.2112;
		
		//SaveModified(filename3);
		
		int argc=1;
		char **argv;
		GLUTInit(&argc, argv);
		EndWaitCursor();
		//if(formatright){
			GLUTMainLoop();  //draw mesh2 
	}
	
}

void CMy3DRetrievalDoc::OnSTATICRetrievalResults7() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	if (m_ipage==1)
	{
		BeginWaitCursor();
		mesh2 = ReadOffFile(m_saModelfilename[display_num[6]+1]);//orignal model
		
		float alpha0=0.0450,alpha1=0.2112;
		
		//SaveModified(filename3);
		
		int argc=1;
		char **argv;
		GLUTInit(&argc, argv);
		EndWaitCursor();
		//if(formatright){
			GLUTMainLoop();  //draw mesh2 
	}
	else
	{
		BeginWaitCursor();
		mesh2 = ReadOffFile(m_saModelfilename[display_num[16]+1]);//orignal model
		
		float alpha0=0.0450,alpha1=0.2112;
		
		//SaveModified(filename3);
		
		int argc=1;
		char **argv;
		GLUTInit(&argc, argv);
		EndWaitCursor();
		//if(formatright){
			GLUTMainLoop();  //draw mesh2 
	}

	
}

void CMy3DRetrievalDoc::OnSTATICRetrievalResults8() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	if (m_ipage==1)
	{
		BeginWaitCursor();
		mesh2 = ReadOffFile(m_saModelfilename[display_num[7]+1]);//orignal model
		
		float alpha0=0.0450,alpha1=0.2112;
		
		//SaveModified(filename3);
		
		int argc=1;
		char **argv;
		GLUTInit(&argc, argv);
		EndWaitCursor();
		//if(formatright){
		GLUTMainLoop();  //draw mesh2 
	}
	else
	{
		BeginWaitCursor();
		mesh2 = ReadOffFile(m_saModelfilename[display_num[17]+1]);//orignal model
		
		float alpha0=0.0450,alpha1=0.2112;
		
		//SaveModified(filename3);
		
		int argc=1;
		char **argv;
		GLUTInit(&argc, argv);
		EndWaitCursor();
		//if(formatright){
			GLUTMainLoop();  //draw mesh2 
	}

	
}


void CMy3DRetrievalDoc::OnSTATICRetrievalResults9() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	if (m_ipage==1)
	{
		BeginWaitCursor();
		mesh2 = ReadOffFile(m_saModelfilename[display_num[8]+1]);//orignal model
		
		float alpha0=0.0450,alpha1=0.2112;
		
		//SaveModified(filename3);
		
		int argc=1;
		char **argv;
		GLUTInit(&argc, argv);
		EndWaitCursor();
		//if(formatright){
		GLUTMainLoop();  //draw mesh2 
	}
	else
	{
		BeginWaitCursor();
		mesh2 = ReadOffFile(m_saModelfilename[display_num[18]+1]);//orignal model
		
		float alpha0=0.0450,alpha1=0.2112;
		
		//SaveModified(filename3);
		
		int argc=1;
		char **argv;
		GLUTInit(&argc, argv);
		EndWaitCursor();
		//if(formatright){
		GLUTMainLoop();  //draw mesh2 
	}

	
}

void CMy3DRetrievalDoc::OnSTATICRetrievalResults10() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	if (m_ipage==1)
	{
		BeginWaitCursor();
		mesh2 = ReadOffFile(m_saModelfilename[display_num[9]+1]);//orignal model
		
		float alpha0=0.0450,alpha1=0.2112;
		
		//SaveModified(filename3);
		
		int argc=1;
		char **argv;
		GLUTInit(&argc, argv);
		EndWaitCursor();
		//if(formatright){
		GLUTMainLoop();  //draw mesh2 
	
	}
	else
	{
		BeginWaitCursor();
		mesh2 = ReadOffFile(m_saModelfilename[display_num[19]+1]);//orignal model
		
		float alpha0=0.0450,alpha1=0.2112;
		
		//SaveModified(filename3);
		
		int argc=1;
		char **argv;
		GLUTInit(&argc, argv);
		EndWaitCursor();
		//if(formatright){
		GLUTMainLoop();  //draw mesh2 
	
	}

}

void CMy3DRetrievalDoc::OnPreviouspage() 
{
	// TODO: Add your control notification handler code here
	if (m_ipage==0)
	{
		m_ipage==0;
	}
	else if (m_ipage ==1)
	{
		m_ipage = 1;
	}
	else if (m_ipage == 2)
	{
		m_ipage =1;
	}
	UpdateAllViews(NULL);
	
}

void CMy3DRetrievalDoc::OnNextpage() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	if (m_ipage==0)
	{
		m_ipage==0;
	}
	else if (m_ipage ==1)
	{
		m_ipage = 2;
	}
	else if (m_ipage == 2)
	{
		m_ipage =2;
	}
	
UpdateAllViews(NULL);
}

void CMy3DRetrievalDoc::GLUTInit(int *argc, char **argv)
{
	// Open window 
	//glutInit(argc, argv);
	//glutSetWindow(int win);
	
	glutInitWindowPosition(150, 150);
	glutInitWindowSize(GLUTwindow_width, GLUTwindow_height);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH| GLUT_STENCIL); 
	GLUTwindow = glutCreateWindow("OpenGL Viewer");
	
	// Initialize GLUT callback functions 
	glutReshapeFunc(GLUTResize);
	glutDisplayFunc(GLUTRedraw);
	glutKeyboardFunc(GLUTKeyboard);
	glutSpecialFunc(GLUTSpecial);
	glutMouseFunc(GLUTMouse);
	glutMotionFunc(GLUTMotion);
	glutIdleFunc(0);
    
	// Initialize lights 
	static GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	static GLfloat light0_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glEnable(GL_LIGHT0);
	static GLfloat light1_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glEnable(GL_LIGHT1);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	// Initialize graphics modes 
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_POLYGON);
	glEnd(); 
}

void CMy3DRetrievalDoc::GLUTMainLoop()
{
	
  // Compute bounding box
  float bbox[2][3] = { { 1.0E30F, 1.0E30F, 1.0E30F }, { -1.0E30F, -1.0E30F, -1.0E30F } };
  for (int i = 0; i < mesh2->nverts; i++) {
    Vector3& vert = mesh2->verts[i];
    if (vert.x < bbox[0][0]) bbox[0][0] = vert.x;
    else if (vert.x > bbox[1][0]) bbox[1][0] = vert.x;
    if (vert.y < bbox[0][1]) bbox[0][1] = vert.y;
    else if (vert.y > bbox[1][1]) bbox[1][1] = vert.y;
    if (vert.z < bbox[0][2]) bbox[0][2] = vert.z;
    else if (vert.z > bbox[1][2]) bbox[1][2] = vert.z;
  }

  // Setup initial viewing scale
  float dx = bbox[1][0] - bbox[0][0];
  float dy = bbox[1][1] - bbox[0][1];
  float dz = bbox[1][2] - bbox[0][2];
  scale = 2.0 / sqrt(dx*dx + dy*dy + dz*dz);

  // Setup initial viewing center
  center[0] = 0.5 * (bbox[1][0] + bbox[0][0]);
  center[1] = 0.5 * (bbox[1][1] + bbox[0][1]);
  center[2] = 0.5 * (bbox[1][2] + bbox[0][2]);

  // Run main loop -- never returns 
  glutMainLoop();
	
}

void CMy3DRetrievalDoc::OnQueryFeatureD2() 
{
	// TODO: Add your control notification handler code here
	m_iRetrievalMethod = 1;
	ExtractQueryModFeature();	
}

void CMy3DRetrievalDoc::OnFeatureD1() 
{
	// TODO: Add your control notification handler code here
	m_iRetrievalMethod = 2;
	ExtractQueryModFeature_D1();
}

void CMy3DRetrievalDoc::OnFeatureD3() 
{
	// TODO: Add your control notification handler code here
	m_iRetrievalMethod = 0;
	MessageBox(NULL,"Sorry! To be finished! Use D2 Feature!","Error",MB_OK|MB_ICONSTOP);
	return;
	
}

void CMy3DRetrievalDoc::OnFeatureA3() 
{
	// TODO: Add your control notification handler code here
	m_iRetrievalMethod = 0;
	MessageBox(NULL,"Sorry! To be finished! Use D2 Feature!","Error",MB_OK|MB_ICONSTOP);
	return;
	
}


void CMy3DRetrievalDoc::OnFeatureMyOwen() 
{
	// TODO: Add your control notification handler code here
	m_iRetrievalMethod = 0;
//	MessageBox(NULL,"Sorry! To be finished! Use D2 Feature!","Error",MB_OK|MB_ICONSTOP);
	CDialogFeatureSelection myFeatureSelection;
	if (myFeatureSelection.DoModal()!=IDOK)
	{
		return;
	}
	return;
}
/************************************************************************/
/* D1 DataBase Feature Extracted                                                  */
/************************************************************************/

void CMy3DRetrievalDoc::OnDateBaseFeatureExtractD1() 
{
	// TODO: Add your command handler code here
	CString temp;
	temp = m_saModelfilename[m_TotalNumMedol];
	temp.Replace( ".off" , "D1Feature.txt");  //get the filename of the feature;
	
	if (m_DataBaseOpened == FALSE)
	{
		MessageBox(NULL,"Please Open the DataBase first!","Error",MB_OK|MB_ICONSTOP);
	}
	else if (GetFileAttributes(temp) != (DWORD)-1)       //(== -1) represents there is not such file. 
	{
		MessageBox(NULL,"The D1 Features of the DataBase have been extracted!","Error",MB_OK|MB_ICONSTOP);
	}
	else	
	{
		DataBaseFeatureExtractD1();
	}
	m_bDataBaseFeatureExtracted = TRUE;
	
}

void CMy3DRetrievalDoc::DataBaseFeatureExtractD1()
{
	BeginWaitCursor();
	for (int j=1;j<m_TotalNumMedol+1;j++)
	{
		CString temp;
		temp=m_saModelfilename[j];
        //read off file
		mesh1 = ReadOffFile(temp);
		CString temptxt; //for the feature vector;
		temptxt = m_saModelfilename[j];
		temptxt.Replace( ".off", "D1Feature.txt" );
		//m_sDataBaseFeatrue[j]=temptxt;
		
		// for recording
		FILE *fileout;
		int line_col_num=0;  // the line_col_num;
		char   fileout_name[121];  // out file name;
		strcpy(fileout_name,temptxt);
		//open the file;
		fileout = fopen(fileout_name,"w");
		// Extract the Featruevertices;
		Featurevertices_D1();  
		// if can not open the file;
		if ( fileout == NULL )
		{
			MessageBox(NULL,"Can not open the output file","Error",MB_OK|MB_ICONSTOP);
		}
		// record the Feature;
		for (int i=0;i<64;i++)
		{
			fprintf (fileout, "%d ", histogram[i]);
			fprintf ( fileout, "\n" );
			line_col_num = line_col_num + 1;
		}
		fclose(fileout);
		mesh1->~Mesh(); mesh1=NULL;
		
	}
	EndWaitCursor();

}

void CMy3DRetrievalDoc::ExtractQueryModFeature_D1()
{
	if (m_bFileOpen==TRUE)
	{	if (m_bQueryModelFeatrueEXtracted_D1==TRUE)
		{
				MessageBox(NULL,"The D1 Feature of this Model has been extracted!","Error",MB_OK|MB_ICONSTOP);
				return;
		}
		
		m_vQueryFeatureVector.m_dOAverage=mesh1->meanscale;
		CString temp ;
		temp= _T("");
		temp = m_CurrentDirectory;
		FILE *fileout;
		int line_col_num=0;
		char   fileout_name[121];
		temp = temp+"\\feature_D1.txt"; //the feature file name;
		strcpy(fileout_name,temp);
		//open the file;
		fileout = fopen(fileout_name,"w");

		//begin sampling;		
		BeginWaitCursor();

		Featurevertices_D1();		
		//	 float max_distanc;
		//	 max_distanc = Sampling(mesh1);
		// if can not open the file;
		if ( fileout == NULL )
		{
			MessageBox(NULL,"Can not open the output file","Error",MB_OK|MB_ICONSTOP);
			return;
		}
		// record the sampling distance;
		//	 fprintf (fileout, "%f ", max_distanc);
		//	 fprintf ( fileout, "\n" );
		//	 line_col_num = line_col_num + 1;
		for (int i=0;i<64;i++)
		{
			fprintf (fileout, "%d ", histogram[i]);
			fprintf ( fileout, "\n" );
			line_col_num = line_col_num + 1;
		}
		fclose(fileout);
		EndWaitCursor();
		m_bQueryModelFeatrueEXtracted_D1=TRUE;
		return;
	}
	else
	{
		MessageBox(NULL,"Please open a Model first","Error",MB_OK|MB_ICONSTOP);
		return;
	}
}
