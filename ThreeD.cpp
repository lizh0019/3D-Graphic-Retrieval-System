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
int numper[100];//ÿ��stripe��Ӧ��numperline��ֵ��
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
short int stripedata[100][1000][3];//�洢ÿ�����Ƶ�����
short int data[10000][3];//����������
long float mod[10000][3];//�޸ĵ�����
long float stripemode[100][1000][3];//ÿ���������ݵ��޸�
int pointnumber;
int numper[100];//ÿ��stripe��Ӧ��numperline��ֵ��
int numstripe[1];//stripe����ֵ
*/
	// *********** Read raw data *************
	 CFileDialog openxyz(TRUE,NULL,NULL,OFN_HIDEREADONLY,"OFF File(*.off)|*.off|");//XYZ File(*.xyz)|*.xyz|
	openxyz.m_ofn.lpstrTitle="��off�ļ�";
	
	if(openxyz.DoModal()==IDOK)
	{
	 filename=openxyz.GetPathName();
	 //CString filename1=openxyz.GetPathName();
	}
    else
	{
	//	MessageBox( NULL,"��off�ļ�����!","��off�ļ�",MB_ICONSTOP|MB_OK);
		 return FALSE; 
	}
	if (!fin.Open(filename,CFile::modeRead,&e)) return FALSE;
   /* Read data from file */
   cnt = 0; stripe=0;pointnumber=0;
   
   
   //TRACE("*** stripes ***:  %6d\n",stripe);
            //AfxMessageBox(showxyz);
  fin.Close();
  numstripe[0]=stripe;//һ�����Ƶ����������ǽű�ֵ
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
           
			/*���յ������ж�ȡ*/
			data[pointnumber][0]=x;
            data[pointnumber][1]=y;
            data[pointnumber][2]=z; 	
         /*�������ƶ�������*/
		    stripedata[stripe][numperline][0]=x;
			stripedata[stripe][numperline][1]=y;
			stripedata[stripe][numperline][2]=z;
		
		    
			numperline++;//ÿ�����Ƶ����ݸ���
		    pointnumber++;//�������ݵĸ���

		} 
		/*���ÿ�����ƶ�Ӧ�ĵ���*/
		numper[stripe]=numperline;//ÿ�����Ƶ�ĸ�������������ĽǱ���
		stripe++;
   }
   //TRACE("*** stripes ***:  %6d\n",stripe);
            //AfxMessageBox(showxyz);
  fin.Close();
  numstripe[0]=stripe;//һ�����Ƶ����������ǽű�ֵ
  return true;


}

