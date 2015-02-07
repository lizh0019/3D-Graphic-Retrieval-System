// RetrievalMethod.h: interface for the CRetrievalMethod class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RETRIEVALMETHOD_H__BAC24044_3755_4C4E_8EDE_2E0A637B2286__INCLUDED_)
#define AFX_RETRIEVALMETHOD_H__BAC24044_3755_4C4E_8EDE_2E0A637B2286__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define MAX_MODEL_NUMBER 10000


typedef struct tagFeatureStruct
{
	char m_sOriginalFileName[MAX_PATH];//Original File name
	BYTE m_bType;//For bmp: 0; For Jpg: 1
	BYTE m_bBitCount;//Color bit
	LONG m_lImageWidth;//Image width
	LONG m_lImageHeight;//Image Height
	WORD m_wDimensions;//The feature vector dimension
	//以下用不到……
	float m_dOAverage; //Original vector average
	double m_dOVariance;//Original vector Variance
	double m_dNAverage; //Normalized vector average
	double m_dNVariance;//Normalized vector Variance
	double *m_dOriginalFeature; //Original feature vectors
	double *m_dNormalizedFeature; //Normalized feature vectors
}FEATUREVECTOR,FAR *LPFEATUREVECTOR,*PFEATUREVECTOR;

//for image reading
#define WIDTHBYTES(bits) (((bits)+31)/32*4)
#define SAVEWIDTH(mywidth)  (mywidth+3)/4*4

class CRetrievalMethod  
{
public:
	void Retrieval20Result(int *distance,int array[],int m_totle = 1814);
//	void Retrieve20Result(int *distance,int array[],int m_totle=1814);
	int FineMinNum(int *array,int m_num);
	int *ComputeDistance(CString Queryfeature,CString DataBasefeature[],int Model_num);
	int readfeaturefile(const char *filename, int feature[]);
	int featurevector[64];

	FEATUREVECTOR m_OFeatureVector;


	//for the retieval
	CString *m_sFeatureFilename[MAX_MODEL_NUMBER];
	float *featruedistanc;




	CRetrievalMethod();
	virtual ~CRetrievalMethod();

};

#endif // !defined(AFX_RETRIEVALMETHOD_H__BAC24044_3755_4C4E_8EDE_2E0A637B2286__INCLUDED_)
