// ThreeD.cpp : implementation file
//

#include "stdafx.h"
#include "3DRetrieval.h"
#include "ThreeD.h"
#include "3DRetrievalDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
short int stripedata[100][100][3];
short int data[10000][3];

long float tridata[10000][3];
long float mod[10000][3];
long float nose[10000][3];
long float stripemode[100][100][3];
int pointnumber;
int minx;
int wholeshow;
int NoseShow;
int PlaneShow;
int nosenum;
int planepointnum;
int stripeshow;
int numper[100];//每个stripe对应的numperline的值；
int numstripe[1];
/////////////////////////////////////////////////////////////////////////////
// ThreeD

IMPLEMENT_DYNCREATE(ThreeD, CDocument)

ThreeD::ThreeD()
{
	opensuccess=FALSE;
}

BOOL ThreeD::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

ThreeD::~ThreeD()
{
}


BEGIN_MESSAGE_MAP(ThreeD, CDocument)
	//{{AFX_MSG_MAP(ThreeD)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ThreeD diagnostics

#ifdef _DEBUG
void ThreeD::AssertValid() const
{
	CDocument::AssertValid();
}

void ThreeD::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ThreeD serialization

void ThreeD::Serialize(CArchive& ar)
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
// ThreeD commands

BOOL ThreeD::Read3D_OFF(CString &filename)
{
	CFile fin,fout;
	CFileException e;

	short x,y,z;
	short cnt;
	int stripe;
	int numperline;
	long	i; 
    CString  showxyz;
    int size=0;
/*
short int stripedata[100][1000][3];//存储每个条纹的数据
short int data[10000][3];//整体点的数据
long float mod[10000][3];//修改的数据
long float stripemode[100][1000][3];//每个条纹数据的修改
int pointnumber;
int numper[100];//每个stripe对应的numperline的值；
int numstripe[1];//stripe的数值
*/
	// *********** Read raw data *************
	 CFileDialog openxyz(TRUE,NULL,NULL,OFN_HIDEREADONLY,"OFF File(*.off)|*.off|");//XYZ File(*.xyz)|*.xyz|
	openxyz.m_ofn.lpstrTitle="打开off文件";
	
	if(openxyz.DoModal()==IDOK)
	{
	 filename=openxyz.GetPathName();
	 //CString filename1=openxyz.GetPathName();
	}
    else
	{
	//	MessageBox( NULL,"打开off文件错误!","打开off文件",MB_ICONSTOP|MB_OK);
		 return FALSE; 
	}
	if (!fin.Open(filename,CFile::modeRead,&e)) return FALSE;
   /* Read data from file */
   cnt = 0; stripe=0;pointnumber=0;
   
   
   //TRACE("*** stripes ***:  %6d\n",stripe);
            //AfxMessageBox(showxyz);
  fin.Close();
  numstripe[0]=stripe;//一共条纹的数量，而非脚标值
  return pointnumber;

}

BOOL ThreeD::Save3D_RMAData(int pointnumber)
{
	char BASED_CODE szFilter[]="CRectangle Date(*.txt)|*.txt||";
	CFileDialog m_ldFile(FALSE,"*.txt",m_PathName,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
	if(m_ldFile.DoModal()!=IDOK)
		return FALSE;
	m_PathName=m_ldFile.GetPathName();
	//open file
	FILE *fpout;
	if (!(fpout = fopen(m_PathName, "w"))) {
    fprintf(stderr, "Unable to open file %s\n", m_PathName);
	fclose(fpout);
	exit(1);
	}
	char buffer[40];strcpy(buffer,"");
	char temp[11];strcpy(temp,"");
	for (long i=0;i<pointnumber;i++){
			/*itoa(data[i][0],temp,10);strcat(buffer,temp);strcat(buffer," ");
			itoa(data[i][1],temp,10);strcat(buffer,temp);strcat(buffer," ");
			itoa(data[i][2],temp,10);strcat(buffer,temp);strcat(buffer,"\n");*/
		    itoa(mod[i][0],temp,10);strcat(buffer,temp);strcat(buffer," ");
			itoa(mod[i][1],temp,10);strcat(buffer,temp);strcat(buffer," ");
			itoa(mod[i][2],temp,10);strcat(buffer,temp);strcat(buffer,"\n");
			fputs(buffer,fpout);
			strcpy(buffer,"");
	}

	fclose(fpout);
	return TRUE;


}



bool ThreeD::Load3D_RMA(CString filename)
{
	CFile fin,fout;
	CFileException e;

	short x,y,z;
	short cnt;
	int stripe;
	int numperline;
	long	i; 
    int size=0;
	
 if (!fin.Open(filename,CFile::modeRead,&e)) return FALSE;
   /* Read data from file */
   cnt = 0; stripe=0;pointnumber=0;
   while (fin.Read(&cnt,sizeof(short)) == sizeof(short)) 
	{
		/* New stripe */
		numperline=0;
		for (i=0; i < cnt; i++) {
			if (fin.Read(&x, sizeof(short)) <1) return FALSE;
			if (fin.Read(&y, sizeof(short)) <1) return FALSE;
			if (fin.Read(&z, sizeof(short)) <1) return FALSE;
		   /* now a 3D point (x,y,z) is ready, here you can do 
			 anything about (x,y,z), for example, to store it in an array */
           
			/*按照点数进行读取*/
			data[pointnumber][0]=x;
            data[pointnumber][1]=y;
            data[pointnumber][2]=z; 	
         /*按照条纹读出数据*/
		    stripedata[stripe][numperline][0]=x;
			stripedata[stripe][numperline][1]=y;
			stripedata[stripe][numperline][2]=z;
		
		    
			numperline++;//每个条纹的数据个数
		    pointnumber++;//整体数据的个数

		} 
		/*存放每条条纹对应的点数*/
		numper[stripe]=numperline;//每个条纹点的个数，而非数组的角标数
		stripe++;
   }
   //TRACE("*** stripes ***:  %6d\n",stripe);
            //AfxMessageBox(showxyz);
  fin.Close();
  numstripe[0]=stripe;//一共条纹的数量，而非脚标值
  return true;


}

