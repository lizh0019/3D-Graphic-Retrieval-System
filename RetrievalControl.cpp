// RetrievalControl.cpp: implementation of the CRetrievalControl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ModelRetrieval.h"
#include "RetrievalControl.h"
#include <VECTOR>
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRetrievalControl::CRetrievalControl()
{
	m_bStudying=false;
	m_bShouldRetrievalAgain=false;
	this->m_bKnowledgeVaild=false;
	this->m_bSampleImageInvalid=false;
	m_bResultValid=false;
	this->m_iNumberResultImages=0;
	this->m_iNumberStudyTimes=0;
	this->m_iNumberTotalImage=0;
	this->m_iSampleImageID=-1;
	m_iNumberRetrievalLay=3;   //three lays
	m_dParament_a=0.5;   //the change of the similarity
	m_dParament_b=0.3;   //the change of the similarity and dis
	m_dParament_c=0.1;	 //the change of the images that not choosed
	m_dThreshold=0.8;   //
	m_sKnowlegeFile="knowlege.k";
	m_sFolder[0]="\\thumbnail\\";//folder
	m_sFolder[1]="\\feature\\";//folder
	m_sFolder[2]="\\knowledge\\";//folder
	m_sHeadFile="\\databasehead.ibh";  //headfilename
	this->m_sBasePathName="";
	m_sSampleImageFullName="";

	//for display
	m_iCurrentPage=0;
	m_iTotalPage=0;

	//for relevance
	m_iMaxNumberRelevance=0;

	//for test
	m_iTestLay=5;

}

CRetrievalControl::~CRetrievalControl()
{

	//studying
	if(m_bStudying)
	SaveImageBase(this->m_sBasePathName);
}

bool CRetrievalControl::Retrieval(double dThreshold)
{
	if (dThreshold<MIN_THESHOLD)    dThreshold=MIN_THESHOLD;
	if (dThreshold>MAX_THESHOLD)	dThreshold=MAX_THESHOLD;
	//should retrieval
	if (m_bShouldRetrievalAgain==false) return false;  //sample or base error

	//it is true or should be true		
	this->m_dThreshold=dThreshold;  //get the threshold	
	return(this->RetrievalFromMatrix(this->m_cImageBaseKnowledgeMatrix,this->m_cRetrievalInformation,this->m_iSampleImageID,this->m_dThreshold));
	
}

bool CRetrievalControl::SetSampleID(CString sSampeleImageFullPathName)
{
	this->m_sSampleImageFullName=sSampeleImageFullPathName;
	
	CString SampleImagePath=sSampeleImageFullPathName;
	CString SampleFileName=sSampeleImageFullPathName;
	unsigned int iID=0;
	int ibit=0;
	int i;

	//get the path of sample image
	if (SampleImagePath=="")	
	{
		InitilizeReadSampleError();
		return false;

	}
	while ((SampleImagePath.GetAt(SampleImagePath.GetLength()-1)!='\\'))
	{
		SampleImagePath.Delete(SampleImagePath.GetLength()-1);		
	}

	//whether the same path
	if(SampleImagePath!=this->m_sBasePathName+m_sFolder[0])
	{
		InitilizeReadSampleError();	
		return false;
	}
	
//if same,set the id
	//delete the ".jpg"
	for(i=0;i<4;i++)
		SampleFileName.Delete(SampleFileName.GetLength()-1);
	//get the id
	while ((SampleFileName.GetAt(SampleFileName.GetLength()-1)!='\\'))
	{
		if(AddHighBit(SampleFileName.GetAt(SampleFileName.GetLength()-1),iID,ibit)==false)
		{
		InitilizeReadSampleError();
		return false;
		}
		ibit++;
		SampleFileName.Delete(SampleFileName.GetLength()-1);		
	}
	
	if(this->m_iSampleImageID==iID)  //the same id
		m_bShouldRetrievalAgain=false;  //not retrieval again;	
	else 
		m_bShouldRetrievalAgain=true;  //should retrieval again;
	this->m_iSampleImageID=iID;  //set the id
	this->m_bSampleImageInvalid=true;
	this->m_iCurrentPage=0;
	this->m_iNumberResultImages=0;
	this->m_iTotalPage=0;
	return true;
}



bool CRetrievalControl::ReadImageBase(CString sImageBasePath)
{
	this->m_sBasePathName=sImageBasePath;
	CString FullFileName=sImageBasePath+m_sHeadFile;
	CFile ReadFile;
	//

	//Open the file
	if(ReadFile.Open(FullFileName,CFile::modeRead)==false)
	{
		this->InitilizeReadBaseError();
		return false;
	}

	//read the head
	if(ReadFile.Read(&this->m_stImageHeadFile,sizeof(m_stImageHeadFile))!=sizeof(m_stImageHeadFile) )
			return false;
	if (m_stImageHeadFile.m_sFileType[0]!='i'||
		m_stImageHeadFile.m_sFileType[1]!='b'||
		m_stImageHeadFile.m_sFileType[2]!='h') 
	{
		this->InitilizeReadBaseError();
		return false;
	}

	//succeed 
	//close the file
	ReadFile.Close();

	//get the paraments
	this->m_iNumberTotalImage=m_stImageHeadFile.m_iNumberTotalImage;
	this->m_iNumberStudyTimes=m_stImageHeadFile.m_iNumberRelevance;
	this->m_dParament_a=m_stImageHeadFile.m_dParament_a;
	this->m_dParament_b=m_stImageHeadFile.m_dParament_b;
	this->m_dParament_c=m_stImageHeadFile.m_dParament_c;

	//read knowledge file
	if(ReadKnowledgeFile(sImageBasePath)==false) 
	{
		this->InitilizeReadBaseError();
		return false;
	}
	this->m_bKnowledgeVaild=true; 
	//reset the sample image ID
	return (this->SetSampleID(this->m_sSampleImageFullName));  
	
}

bool CRetrievalControl::ReadKnowledgeFile(CString sPathName)
{
	//create the memory
	CFile cKnowledgeFile;
	CString sKnowledgeFullPathName=this->m_sBasePathName+this->m_sFolder[2];

	//get the knowledge file path
	sKnowledgeFullPathName=sKnowledgeFullPathName+this->m_sKnowlegeFile; 
	m_cImageBaseKnowledgeMatrix.InitializeMatrixData(0.0,this->m_iNumberTotalImage,m_iNumberTotalImage);
	return (this->m_cImageBaseKnowledgeMatrix.LoadDataFromDoubleFile(sKnowledgeFullPathName));
}

bool CRetrievalControl::RetrievalFromMatrix(CMatrix cImageBaseKnowledgeMatrix,CMatrix &cResultInformation,unsigned int iSampleImageID,double dThreshold)
{
	//assert the row and col is right
	if(this->m_iNumberTotalImage!=cImageBaseKnowledgeMatrix.GetMatrixColNumber()||
		this->m_iNumberTotalImage!=cImageBaseKnowledgeMatrix.GetMatrixRowNumber())
	{
		this->m_iNumberResultImages=0;
		return false;
	}

	switch(this->m_iNumberRetrievalLay) {
	case 1:
		break;
	case 2:
		break;
	case 3:
		RetrievalFromMatrix_3Lays(cImageBaseKnowledgeMatrix,cResultInformation, iSampleImageID, dThreshold);
	default:
		break;
	}
	
	//get the result number
	this->m_iNumberResultImages=this->m_cRetrievalInformation.GetMatrixColNumber();
	this->m_iTotalPage=(m_iNumberResultImages+NUMBER_IMAGE_PERPAGE-1)/NUMBER_IMAGE_PERPAGE;
	this->m_cRetrievalInformation.ReListByRow_Decrease(1);   //list by similarity
	this->m_iCurrentPage=0;  //reset the current page
	return true;
}

bool CRetrievalControl::AddHighBit(char cHighBit, unsigned int &iID,int iBit)
{
	//get the bit of iID

	int iHighNumber;

	//get the high bit
	switch(cHighBit) {
	case '0':
		iHighNumber=0;
		break;
	case '1':
		iHighNumber=1;
		break;
	case '2':
		iHighNumber=2;
		break;
	case '3':
		iHighNumber=3;
		break;
	case '4':
		iHighNumber=4;
		break;
	case '5':
		iHighNumber=5;
		break;
	case '6':
		iHighNumber=6;
		break;
	case '7':
		iHighNumber=7;
		break;
	case '8':
		iHighNumber=8;
		break;
	case '9':
		iHighNumber=9;
		break;

	default:
		return false;
	}
	iID=iID+iHighNumber*pow(10,iBit);
	return true;
}

//retrieval for 3 lays
void CRetrievalControl::RetrievalFromMatrix_3Lays(CMatrix cImageBaseKnowledgeMatrix, CMatrix &cResultInformation, unsigned int iSampleImageID, double dThreshold)
{
	
	vector<int> viIDList;  //ID list
	CMatrix cResultLay_0(2,1),cResultLay_1(2,0),cResultLay_2(2,0),cResultLay_3(2,0);  //three lays,row :2,col: not sure
	//for test
	CMatrix cResultLay_4(2,0),cResultLay_5(2,0);
	//end of for test
	TMatrix pMatrixLayInformation;

	int i;
	int iNumberImageOnLay;

	viIDList.resize(this->m_iNumberTotalImage);
	for(i=0;i<m_iNumberTotalImage;i++)
		viIDList[i]=i;

	
	cResultLay_0.SetMatrixData(iSampleImageID,0,0);
	cResultLay_0.SetMatrixData(1.00,1,0);
	viIDList[iSampleImageID]=-1;  //make it impossible
	if(this->m_iTestLay>=1)
	RetrievalFromUpLayMatrix(cImageBaseKnowledgeMatrix, cResultLay_0, cResultLay_1, viIDList, dThreshold);
	if(this->m_iTestLay>=2)
	RetrievalFromUpLayMatrix(cImageBaseKnowledgeMatrix, cResultLay_1, cResultLay_2, viIDList, dThreshold);
	if(this->m_iTestLay>=3)
	RetrievalFromUpLayMatrix(cImageBaseKnowledgeMatrix, cResultLay_2, cResultLay_3, viIDList, dThreshold);
	if(this->m_iTestLay>=4)
	RetrievalFromUpLayMatrix(cImageBaseKnowledgeMatrix, cResultLay_3, cResultLay_4, viIDList, dThreshold);
	if(this->m_iTestLay>=5)
	RetrievalFromUpLayMatrix(cImageBaseKnowledgeMatrix, cResultLay_4, cResultLay_5, viIDList, dThreshold);


	cResultInformation.InitializeMatrixData(0.0,3,0);//Initialize the matrix

	//add the lay0
	iNumberImageOnLay=cResultLay_0.GetMatrixColNumber();
	pMatrixLayInformation=cResultLay_0.GetMatrixPoint();
	for(i=0;i<iNumberImageOnLay;i++)
	{
		cResultInformation.AddOneCol(0);//initilize it to 1,//it is itself,so relevance
		cResultInformation.SetMatrixData(pMatrixLayInformation[0][i],0,cResultInformation.GetMatrixColNumber()-1);
		cResultInformation.SetMatrixData(pMatrixLayInformation[1][i],1,cResultInformation.GetMatrixColNumber()-1);
	//	cResultInformation.SetMatrixData(1,2,cResultInformation.GetMatrixColNumber()-1);
	}
		//add the lay1
	pMatrixLayInformation=cResultLay_1.GetMatrixPoint();
	iNumberImageOnLay=cResultLay_1.GetMatrixColNumber();
	for(i=0;i<iNumberImageOnLay;i++)
	{
		cResultInformation.AddOneCol(1);//initilize it to 1
		cResultInformation.SetMatrixData(pMatrixLayInformation[0][i],0,cResultInformation.GetMatrixColNumber()-1);
		cResultInformation.SetMatrixData(pMatrixLayInformation[1][i],1,cResultInformation.GetMatrixColNumber()-1);
	//	cResultInformation.SetMatrixData(1,2,cResultInformation.GetMatrixColNumber()-1);
	}
		//add the lay2
	pMatrixLayInformation=cResultLay_2.GetMatrixPoint();
	iNumberImageOnLay=cResultLay_2.GetMatrixColNumber();
	for(i=0;i<iNumberImageOnLay;i++)
	{
		cResultInformation.AddOneCol(1);//initilize it to 1
		cResultInformation.SetMatrixData(pMatrixLayInformation[0][i],0,cResultInformation.GetMatrixColNumber()-1);
		cResultInformation.SetMatrixData(pMatrixLayInformation[1][i],1,cResultInformation.GetMatrixColNumber()-1);
	//	cResultInformation.SetMatrixData(1,2,cResultInformation.GetMatrixColNumber()-1);
	}
		//add the lay3
	pMatrixLayInformation=cResultLay_3.GetMatrixPoint();
	iNumberImageOnLay=cResultLay_3.GetMatrixColNumber();

	for(i=0;i<iNumberImageOnLay;i++)
	{
		cResultInformation.AddOneCol(1);  //initilize it to 1
		cResultInformation.SetMatrixData(pMatrixLayInformation[0][i],0,cResultInformation.GetMatrixColNumber()-1);
		cResultInformation.SetMatrixData(pMatrixLayInformation[1][i],1,cResultInformation.GetMatrixColNumber()-1);
	//	cResultInformation.SetMatrixData(1,2,cResultInformation.GetMatrixColNumber()-1);
	}

		//add the lay4
	pMatrixLayInformation=cResultLay_4.GetMatrixPoint();
	iNumberImageOnLay=cResultLay_4.GetMatrixColNumber();

	for(i=0;i<iNumberImageOnLay;i++)
	{
		cResultInformation.AddOneCol(1);  //initilize it to 1
		cResultInformation.SetMatrixData(pMatrixLayInformation[0][i],0,cResultInformation.GetMatrixColNumber()-1);
		cResultInformation.SetMatrixData(pMatrixLayInformation[1][i],1,cResultInformation.GetMatrixColNumber()-1);
	//	cResultInformation.SetMatrixData(1,2,cResultInformation.GetMatrixColNumber()-1);
	}
		//add the lay5
	pMatrixLayInformation=cResultLay_5.GetMatrixPoint();
	iNumberImageOnLay=cResultLay_5.GetMatrixColNumber();

	for(i=0;i<iNumberImageOnLay;i++)
	{
		cResultInformation.AddOneCol(1);  //initilize it to 1
		cResultInformation.SetMatrixData(pMatrixLayInformation[0][i],0,cResultInformation.GetMatrixColNumber()-1);
		cResultInformation.SetMatrixData(pMatrixLayInformation[1][i],1,cResultInformation.GetMatrixColNumber()-1);
	//	cResultInformation.SetMatrixData(1,2,cResultInformation.GetMatrixColNumber()-1);
	}
}
//retrieval from the up lays
void CRetrievalControl::RetrievalFromUpLayMatrix(CMatrix &cImageBaseKnowledgeMatrix, CMatrix &cUpResultLay, CMatrix &cThisResultLay, vector<int> &viIDList, double dThreshold)
{
	
//	TMatrix pImageBaseKnoledgeMatrix=cImageBaseKnowledgeMatrix.GetMatrixPoint();
//	TMatrix *pResultInformation=cResultInformation.GetMatrixPoint();
	int iUpNumberLay=cUpResultLay.GetMatrixColNumber();//the number
	int i,j,iTempUpID;
	double dTempleUpSimilarity,dTempleThisSimilarity;
	//test
//	double *pdTempMatrixMemory=new double [cImageBaseKnowledgeMatrix.GetMatrixColNumber()*cImageBaseKnowledgeMatrix.GetMatrixRowData()];
	
	
	for(i=0;i<iUpNumberLay;i++)  //find
	{
		//temp up id
		iTempUpID=cUpResultLay.GetMatirxData_uint(0,i);
		dTempleUpSimilarity=cUpResultLay.GetMatirxData_double(1,i);
		for(j=0;j<this->m_iNumberTotalImage;j++)  //all
		{			
			//temp similarity
			dTempleThisSimilarity=dTempleUpSimilarity*(cImageBaseKnowledgeMatrix.GetMatirxData_double(iTempUpID,j));
			//
			if (viIDList[j]>=0&&dTempleThisSimilarity>=dThreshold)
				{
					cThisResultLay.AddOneCol();  ///add one col
					cThisResultLay.SetMatrixData(j,0,cThisResultLay.GetMatrixColNumber()-1);				
					cThisResultLay.SetMatrixData(dTempleThisSimilarity,1,cThisResultLay.GetMatrixColNumber()-1);
					viIDList[j]=-1;  //make it impossible
				}
		}
	}

}

/*  
//display the image  (original)
bool CRetrievalControl::DisplayCurrentPage(CPictureCtrl *pclPictureCtrl[],int *piRelevance[],CString *psSimilarity[])
{
	int iDisplayStart=this->m_iCurrentPage*NUMBER_IMAGE_PERPAGE;
	int iDisplayEnd=(this->m_iCurrentPage+1)*NUMBER_IMAGE_PERPAGE;
	int i;
	if(m_iCurrentPage>m_iTotalPage) 
	{
		m_iCurrentPage=0;		
		return false;  //can't display
	}	

	//no image base
	if(this->m_bKnowledgeVaild==false) return false;
	
	//display one by one
	CString fileID;
	CString ImageBaseFileName=this->m_sBasePathName+this->m_sFolder[0];
	for(i=iDisplayStart;i<iDisplayEnd;i++)
	{
		if (i>=this->m_iNumberResultImages)
		{
			pclPictureCtrl[i-iDisplayStart]->DisEnableDisplay();  //
			psSimilarity[i-iDisplayStart]->Empty();
			*piRelevance[i-iDisplayStart]=-1; 
			continue;
		}
		fileID.Empty();
		fileID.Format("%s%d",fileID,(int)m_cRetrievalInformation.GetMatrixPoint()[0][i]);
		fileID=fileID+".jpg";
		fileID=ImageBaseFileName+fileID;  //get the path of the result 

		if((pclPictureCtrl[i-iDisplayStart]->LoadImage(fileID))==false) return false;  //load image

		//Initialize the simliarity
		psSimilarity[i-iDisplayStart]->Empty();
		psSimilarity[i-iDisplayStart]->Format("%s%f",*psSimilarity[i-iDisplayStart],m_cRetrievalInformation.GetMatrixPoint()[1][i]);

		//Initialize the relevance
		*piRelevance[i-iDisplayStart]=(int)m_cRetrievalInformation.GetMatrixPoint()[2][i];  //
	}
		return true;
	
}
*/

//display the image 
bool CRetrievalControl::DisplayCurrentPage(CPictureCtrl *pclPictureCtrl[],int *piRelevance[],CString *psSimilarity[])
{
	int iDisplayStart=this->m_iCurrentPage*NUMBER_IMAGE_PERPAGE;
	int iDisplayEnd=(this->m_iCurrentPage+1)*NUMBER_IMAGE_PERPAGE;
	int i;
	if(m_iCurrentPage>m_iTotalPage) 
	{
		m_iCurrentPage=0;		
		return false;  //can't display
	}	
	FILE *fp;
	if (!(fp = fopen("id.txt", "w"))) {
		fprintf(stderr, "Unable to open file %s\n", "id.txt");
		return 0;
	}
	//no image base
	if(this->m_bKnowledgeVaild==false) return false;
	
	//display one by one
	CString fileID;
	CString ImageBaseFileName=this->m_sBasePathName+this->m_sFolder[0];
	for(i=iDisplayStart;i<iDisplayEnd;i++)
	{
		if (i>=this->m_iNumberResultImages)
		{
			pclPictureCtrl[i-iDisplayStart]->DisEnableDisplay();  //
			psSimilarity[i-iDisplayStart]->Empty();
			*piRelevance[i-iDisplayStart]=-1; 
			continue;
		}
		fileID.Empty();
		fileID.Format("%s%d",fileID,(int)m_cRetrievalInformation.GetMatrixPoint()[0][i]);
		fileID=fileID+".jpg";
		fileID=ImageBaseFileName+fileID;  //get the path of the result 
		fprintf(fp, "%s\n", fileID);
		if((pclPictureCtrl[i-iDisplayStart]->LoadImage(fileID))==false) return false;  //load image

		//Initialize the simliarity
		psSimilarity[i-iDisplayStart]->Empty();
		psSimilarity[i-iDisplayStart]->Format("%s%f",*psSimilarity[i-iDisplayStart],m_cRetrievalInformation.GetMatrixPoint()[1][i]);

		//Initialize the relevance
		*piRelevance[i-iDisplayStart]=(int)m_cRetrievalInformation.GetMatrixPoint()[2][i];  //
	}
	return true;
	
}

bool CRetrievalControl::ClearDisplayCurrentPage(CPictureCtrl *pclPictureCtrl[],int *piRelevance[],CString *psSimilarity[])
{
	for (int i=0; i<=14; i++)
	{
		pclPictureCtrl[i]->DisEnableDisplay();
	}
	
	return true;
	
}


bool CRetrievalControl::SetNexToBeCurrentPage()
{
	//0,1
	if (this->m_iCurrentPage>=this->m_iTotalPage-1)	return false;

	m_iCurrentPage++;
	return true;
}

bool CRetrievalControl::SetPreToBeCurrentPage()
{
	if (this->m_iCurrentPage<=0)	return false;

	m_iCurrentPage--;
	return true;
}

bool CRetrievalControl::SetFirstToCurrentPage()
{
	if (this->m_iCurrentPage==0)	return false;
	m_iCurrentPage=0;
	return true;
}
//get the path
CString CRetrievalControl::GetImageBasePath()
{
	return this->m_sBasePathName;
}

//get the sample id
CString CRetrievalControl::GetSampleID()
{
	CString temp;
	if (this->m_iSampleImageID==-1) 
	{
		temp.Empty();
		return temp;
	}
	temp.Format("%s%d",temp,m_iSampleImageID);
	return temp;
}

CString CRetrievalControl::GetNumberImageDataBase()
{
	CString temp;
	if (this->m_iNumberTotalImage==0) 
	{
		temp.Empty();
		return temp;
	}
	temp.Format("%s%d",temp,m_iNumberTotalImage);
	return temp;
}

CString CRetrievalControl::GetNumberResult()
{
	CString temp;
	if (this->m_iNumberResultImages==0) 
	{
		temp.Empty();
		return temp;
	}
	temp.Format("%s%d",temp,m_iNumberResultImages);
	return temp;
}

unsigned int CRetrievalControl::GetTotalPage()
{
	return this->m_iTotalPage;

}

unsigned int CRetrievalControl::GetCurrentPage()
{
	return this->m_iCurrentPage;

}

//if read sample error,we should initize the paraments
void CRetrievalControl::InitilizeReadSampleError()
{
	this->m_bSampleImageInvalid=false;
	m_bShouldRetrievalAgain=false;  //error
	this->m_iSampleImageID=-1;
	this->m_cRetrievalInformation.InitializeMatrixData(0.0,3,0);//Initialize
	this->m_iNumberResultImages=0;	
	this->m_iTotalPage=0;
	this->m_iCurrentPage=0;
	m_iMaxNumberRelevance=0;
}

//if read base error,we should initize the paraments
void CRetrievalControl::InitilizeReadBaseError()
{
	m_sBasePathName="";
	this->m_bKnowledgeVaild=false;
	m_bShouldRetrievalAgain=false;  //error
	this->m_iSampleImageID=-1;  //base error so the sample id also error
	this->m_cRetrievalInformation.InitializeMatrixData(0.0,3,0);//Initialize
	this->m_iNumberResultImages=0;	
	this->m_iTotalPage=0;
	this->m_iCurrentPage=0;
	this->m_iNumberStudyTimes=0;
	this->m_iNumberTotalImage=0;
	m_iMaxNumberRelevance=0;
	m_iNumberStudyTimes=0;
}

bool CRetrievalControl::IsNeedRetrieval()
{
return this->m_bShouldRetrievalAgain;
}

bool CRetrievalControl::SetRelevanceCurrentPageResult(int *piRelevance[])
{
	//get the real list number
	int iStartNumber=this->m_iCurrentPage*NUMBER_IMAGE_PERPAGE;
	int iEndNumber=(this->m_iCurrentPage+1)*NUMBER_IMAGE_PERPAGE;

	for(int i=iStartNumber;i<iEndNumber;i++)
	{
		if (i>this->m_cRetrievalInformation.GetMatrixColNumber()-1)//out of the result
		{
			//set the feedback
			this->m_iMaxNumberRelevance=this->m_cRetrievalInformation.GetMatrixColNumber()-1;
			return false;
		}
		m_iMaxNumberRelevance=i;  //set the feedback 
		this->m_cRetrievalInformation.SetMatrixData((double)(*piRelevance[i-iStartNumber]),2,i);
	}
	return true;
}

bool CRetrievalControl::UpdateMatrixbyRelevance()
{
	unsigned int i,j;
	unsigned int iIDi,iIDj;
	//m_dParament_a:0-0		sim=sim+m_dParament_a*(1-sim) 0.5
	//m_dParament_b:0-1		sim=sim-m_dParament_b*(sim-0) 0.3 
	//m_dParament_c:0-2		sim=sim-m_dParament_c*(sim-0) 0.2
	double dTempleRelevance1,dTempleRelevance2;
	double dTempeSimilarity;
	//start update,0,1,2,3.....11-1
	for(i=0;i<=this->m_iMaxNumberRelevance-1;i++)
	{
		iIDi=m_cRetrievalInformation.GetMatirxData_uint(0,i); //get the id
		dTempleRelevance1=m_cRetrievalInformation.GetMatirxData_double(2,i);//get the similarity
		if(dTempleRelevance1==0)   //similar
			for(j=i+1;j<=m_iMaxNumberRelevance;j++)//1,2....11
			{
				iIDj=m_cRetrievalInformation.GetMatirxData_uint(0,j); //get the id
				dTempleRelevance2=m_cRetrievalInformation.GetMatirxData_double(2,j);
				dTempeSimilarity=m_cImageBaseKnowledgeMatrix.GetMatirxData_double(iIDi,iIDj);
				switch((int)dTempleRelevance2) 
				{
				case 0:	//RR				
					dTempeSimilarity=min(1.0,dTempeSimilarity+m_dParament_a*(1-dTempeSimilarity));
					break;
				case 1: //RU
					dTempeSimilarity=max(0.0,dTempeSimilarity-m_dParament_c*(dTempeSimilarity-0));					
					break;
				case 2:  //RI
					dTempeSimilarity=max(0.0,dTempeSimilarity-m_dParament_b*(dTempeSimilarity-0));
					break;
				default:
					break;
				}
				m_cImageBaseKnowledgeMatrix.SetMatrixData(dTempeSimilarity,iIDi,iIDj);
				m_cImageBaseKnowledgeMatrix.SetMatrixData(dTempeSimilarity,iIDj,iIDi);
			}
	}
	//end
	this->m_iNumberStudyTimes++;
	return true;
	
}



bool CRetrievalControl::SaveKnowledge(CString sPathName)
{
	CString sKnowledgeFullPathName=this->m_sBasePathName+this->m_sFolder[2];

	//get the knowledge file path
	sKnowledgeFullPathName=sKnowledgeFullPathName+this->m_sKnowlegeFile; 
	return (this->m_cImageBaseKnowledgeMatrix.SaveDataDoubleToFile(sKnowledgeFullPathName));
}

bool CRetrievalControl::SaveImageBase(CString sPath)
{
	this->m_sBasePathName=sPath;
	CString FullFileName=sPath+m_sHeadFile;
	CFile ReadFile;
	//

	//Open the file
	if(ReadFile.Open(FullFileName,CFile::modeReadWrite)==false)
	{
		return false;
	}

	//change the head
	this->m_stImageHeadFile.m_dParament_a=this->m_dParament_a;
	m_stImageHeadFile.m_dParament_b=m_dParament_b;
	m_stImageHeadFile.m_dParament_c=m_dParament_c;
	m_stImageHeadFile.m_iNumberRelevance=this->m_iNumberStudyTimes;
	m_stImageHeadFile.m_iNumberTotalImage=this->m_iNumberTotalImage;

	ReadFile.Write(&this->m_stImageHeadFile,sizeof(m_stImageHeadFile));

	//succeed 
	//close the file
	ReadFile.Close();
	return SaveKnowledge(this->m_sBasePathName);

}

//get the study times
CString CRetrievalControl::GetStudtyTimes()
{
	CString temp;
	temp.Format("%s%d",temp,this->m_iNumberStudyTimes);
	return temp;
}

void CRetrievalControl::GetFeedbackParament(double &dparamentRR, double &dparamentRI, double &dparamentRU,bool &bStudying)
{
	//get the paraments
	dparamentRR=this->m_dParament_a;
	dparamentRI=this->m_dParament_b;
	dparamentRU=this->m_dParament_c;
	bStudying=this->m_bStudying;
}

void CRetrievalControl::SetFeedbackParament(double dparamentRR, double dparamentRI, double dparamentRU,bool bStudying)
{
	this->m_dParament_a=dparamentRR;
	this->m_dParament_b=dparamentRI;
	this->m_dParament_c=dparamentRU;
	this->m_bStudying=bStudying;
}
//NumberTotal/100
//one class number is 100
double CRetrievalControl::GetRecall()
{
int i,j,iClass;
unsigned int nCol;
unsigned int NumberTotal=0;
if (nCol=min(this->m_cRetrievalInformation.GetMatrixColNumber(),100),nCol==0)	return -1;

//get the class
	iClass=this->m_iSampleImageID/100;
	for(i=0;i<nCol;i++)
		if(m_cRetrievalInformation.GetMatirxData_uint(0,i)/100==iClass)
			NumberTotal++;
	return ((double)NumberTotal/100.0);


}
//NumberTotal/nCol
double CRetrievalControl::GetPrecise()
{
int i,j,iClass;
unsigned int nCol;
unsigned int NumberTotal=0;
if (nCol=min(this->m_cRetrievalInformation.GetMatrixColNumber(),100),nCol==0)	return -1;

//get the class
	iClass=this->m_iSampleImageID/100;
	for(i=0;i<nCol;i++)
		if(m_cRetrievalInformation.GetMatirxData_uint(0,i)/100==iClass)
			NumberTotal++;
	return ((double)NumberTotal/nCol);
}


//for test
bool CRetrievalControl::SetSampleID(unsigned int iID)
{
	this->m_iSampleImageID=iID;
	this->m_bSampleImageInvalid=true;
	return true;
	
}


void CRetrievalControl::SetTestLay(int i)
{
	if (i<1) i=1;
	if(i>5) i=5;
	this->m_iTestLay=i;
}