// RetrievalControl.h: interface for the CRetrievalControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RETRIEVALCONTROL_H__167F0CBA_B1D1_4D75_B685_DB6036373F1C__INCLUDED_)
#define AFX_RETRIEVALCONTROL_H__167F0CBA_B1D1_4D75_B685_DB6036373F1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/************************************************************************/
/*			Function: this class  control the retrieval, it is used only on CImageBaseManage
 *          the imagebase includes three folder and one head file
 *   folder 1: thumbnails,the ID is from 0~number-1
 *	 folder 2: features of the models in folder 1
 *	 foler  3: knowledges of semantic
 *   headfile: a file that include the information 
 *   author	 : jinhaijun	email:jinhaijun@dsp.hit.edu.cn
 *	 version : version 1
 *	 data	 : 2005,5,12~
 *  class added:CMatrix,CPictureCtrl
 * description:
 *                                                                     */
/************************************************************************/
#include "Classes/Matrix.h"
#include "Classes/PictCtrl.h"
#define MAX_FEATURE 200
#define NUMBER_IMAGE_PERPAGE 15
#ifndef __IMAGEBASE_STRUECT
#define __IMAGEBASE_STRUECT
#define MAX_THESHOLD 1.0
#define MIN_THESHOLD 0.1

//head file
typedef struct tagIMAGEHEADFILE
 {
		char m_sFileType[3];
		unsigned int m_iNumberTotalImage;  //the total of the images		
		int m_iNumberDimensionFeature;
		int m_iNumberRelevance;
		double m_dParament_a;
		double m_dParament_b;
		double m_dParament_c;    //three paraments
		int m_iVerson;
		
  } IMAGEHEADFILE, FAR *LPIMAGEHEADFILE, *PIMAGEHEADFILE;

// feature vector, one file of feature
typedef struct tagFEATUREVECOTR
 {
        unsigned int m_iID;  ///ID of the image
		double m_dFileOriginalCharacter[MAX_FEATURE]; //the original features
		int m_iImageWidth;        //the height of the image
		int m_iImageHeight;    ////the height of the image
  } FEATUREVECTOR, FAR *LPFEATUREVECTOR, *PFEATUREVECTOR;	

#endif
class CRetrievalControl  
{
public:
	void SetTestLay(int i);
	bool SetSampleID(unsigned int iID);
	double GetPrecise();
	double GetRecall();
	void SetFeedbackParament(double dparamentRR,double dparamentRI,double dparamentRU,bool bStudying);
	//get the paraments
	void GetFeedbackParament(double &dparamentRR,double &dparamentRI,double &dparamentRU,bool &bStudying);
	//get studying times
	CString GetStudtyTimes();

	bool UpdateMatrixbyRelevance();
	//set the relevance current number
	bool SetRelevanceCurrentPageResult(int *piRelevance[]);
	//whether need retrieval 
	bool IsNeedRetrieval();

	//get the current page number
	unsigned int GetCurrentPage();
	//get the total page
	unsigned int GetTotalPage();
	//get the number of the results
	CString GetNumberResult();
	//get the number of the images in the database
	CString GetNumberImageDataBase();
	//get the id of the sample image,it is string
	CString GetSampleID();
	//get the path of the database
	CString GetImageBasePath();
	//set the current page to 0
	bool SetFirstToCurrentPage();
	//set the current page to pre one
	bool SetPreToBeCurrentPage();
	////set the current page to next one
	bool SetNexToBeCurrentPage();
	//interface:retrieval
	bool DisplayCurrentPage(CPictureCtrl *pclPictureCtrl[],int *piRelevance[],CString *psSimilarity[]);
	bool ClearDisplayCurrentPage(CPictureCtrl *pclPictureCtrl[],int *piRelevance[],CString *psSimilarity[]);// +
	//interface: read the knowledge and headfile from the path:sImageBasePath
	//it read the headfile and the knowledge file,and set the sample id
	bool ReadImageBase(CString sImageBasePath);
//	//interface: the sample image must be in the base,else we don't retrieve
	bool SetSampleID(CString sSampleImageFullPathName);

	//interface:retrieval
	bool Retrieval(double dThreshold);
	CRetrievalControl();
	virtual ~CRetrievalControl();
	
protected:

	bool SaveImageBase(CString sPath);
	bool SaveKnowledge(CString sPathName);
	
	//if read base error, we should initilize the paraments
	void InitilizeReadBaseError();
	//if read sample image error, we should initilize the paraments
	void InitilizeReadSampleError();
	//retrieval the similarity image from the up lays
	void RetrievalFromUpLayMatrix(CMatrix &cImageBaseKnowledgeMatrix, CMatrix &cUpResultLay, CMatrix &cThisResultLay, vector<int> &viIDListdouble, double dThreshold);
	//retrieval the similarity by the algorithm that using 3 lays, 
	void RetrievalFromMatrix_3Lays(CMatrix cImageBaseKnowledgeMatrix,CMatrix &cResultInformation,unsigned int iSampleImageID,double dThreshold);
	//if cHight='3',iID=5;ibit=1,then iID=3*pow(10,1)+5;
	bool AddHighBit(char cHighBit,unsigned int &iID,int iBit);
	//retrieval the similar images from the semantic matrix
	bool RetrievalFromMatrix(CMatrix cImageBaseKnowledgeMatrix,CMatrix &cResultInformation,unsigned int iSampleImageID,double dThreshold);
	//read the semantic matrix from the database :sPathName
	bool ReadKnowledgeFile(CString sPathName);

	bool m_bStudying; //studying
	bool m_bKnowledgeVaild;   //knowledge is valid or not
	unsigned int m_iNumberTotalImage;			//the total of images in database
	CMatrix m_cImageBaseKnowledgeMatrix;     //the matrix of the knowledge
	CMatrix m_cRetrievalInformation;   //3 rows,id,similarity,relevance, col is: m_iNumberResultImages

	bool m_bSampleImageInvalid;   ////sample image is valid or not
	unsigned int m_iSampleImageID;			//the id of the sample image

	int m_iNumberResultImages;  //the number of the result
	bool m_bResultValid;

	int m_iNumberRetrievalLay;  //the lays of retrieval
	
	double m_dThreshold;                  ///the threshold of the retrieval
	double m_dParament_a,m_dParament_b,m_dParament_c;    //three paraments
	int m_iNumberStudyTimes;              //the times of study

	CString m_sFolder[3];//folder
	CString m_sBasePathName;         //Image base path name
	CString m_sHeadFile;		//head file name
	CString m_sKnowlegeFile	;	//knoledge file name
	CString m_sSampleImageFullName;//Thumbnail of Query Model full name
	IMAGEHEADFILE m_stImageHeadFile;	//the struct of headfile

	//for display
	unsigned int m_iCurrentPage;  //current page
	unsigned int m_iTotalPage;//total page

	bool m_bShouldRetrievalAgain; //should retrieval again

	unsigned int m_iMaxNumberRelevance;   //from 0 to the max that has been relevant

	//for test
	int m_iTestLay;
	

};

#endif // !defined(AFX_RETRIEVALCONTROL_H__167F0CBA_B1D1_4D75_B685_DB6036373F1C__INCLUDED_)
