// RetrievalMethod.cpp: implementation of the CRetrievalMethod class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "3DRetrieval.h"
#include "RetrievalMethod.h"
#include <io.h>
#include <FCNTL.h>
#include <SYS\STAT.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRetrievalMethod::CRetrievalMethod()
{

}

CRetrievalMethod::~CRetrievalMethod()
{

}



int CRetrievalMethod::readfeaturefile(const char *filename,int feature[])
{
	int i;
	
	// Open file
	FILE *fpin;
	if (!(fpin = fopen(filename, "r"))) {
		MessageBox(NULL,"Can not open the file!","Error",MB_OK|MB_ICONSTOP);
		return -1;

	}

	// Allocate feature vector
	for (i=0;i<64;i++)
	{
		feature[i] = 0;
	}


	// Read file
	int vectornum = 0;
	int line_count = 0;
	char buffer[1024];

	while (fgets(buffer, 1023, fpin)) 
	{
		// Increment line counter
		line_count++;
		
		// Skip white space
		char *bufferp = buffer;
		while (isspace(*bufferp)) bufferp++;
		
		// Skip blank lines and comments
		if (*bufferp == '#') continue;
		if (*bufferp == '\0') continue;
		
		// Check section
		if (line_count == 1) {//in the line 1
		
			if (sscanf(bufferp, "%d", &vectornum) != 1) {
				MessageBox(NULL,"Can not open the output file","Error",MB_OK|MB_ICONSTOP);
				fclose(fpin);
		
			}
		feature[line_count-1] = vectornum;
		}
		
		else if (line_count <= 64) 
		{
			int i = sscanf(bufferp, "%d", &vectornum);
			if (i != 1)
			{
				MessageBox(NULL,"Syntax error with the file!","Error",MB_OK|MB_ICONSTOP);
				fclose(fpin);
		
			}
			feature[line_count-1] = vectornum;
		}	
		}
	fclose(fpin);
	return 1;

}


int *CRetrievalMethod::ComputeDistance(CString Queryfeature, CString DataBasefeature[], int Model_num)
{
	//Allocate the Memory;
	int *distance;
	distance = new int[Model_num]; // array for the distance;
	for (int j=0;j<Model_num;j++)
	{
		distance[j] = 0;
	}

	int a_Quervector[64]; // array for query model vector;

	int a_DataBFeature[64];
	CString temp;
	temp = Queryfeature;
	readfeaturefile(temp,a_Quervector);  // Read Query Model feature;

	//computing the distance between the Query Model and the DataBase.
	for (int h=1; h<Model_num+1;h++)
	{
		temp = DataBasefeature[h];
		readfeaturefile(temp,a_DataBFeature); // read DataBase Model featrue;
	
		if (h>507)
		{
			for (int n=0;n<64;n++)
			{
				int temp2=0;
				temp2 = a_Quervector[n]-a_DataBFeature[n];
				distance[h-1] += abs(temp2); // here we use abs of the subtration;
			}
		
		}
		else{
		for (int n=0;n<64;n++)
		{
			int temp2=0;
			temp2 = a_Quervector[n]-a_DataBFeature[n];
			distance[h-1] += abs(temp2); // here we use abs of the subtration;
		}
			}

	}


	return distance;

}

int CRetrievalMethod::FineMinNum(int *array, int m_num)
{	int min;
	int num;
	min = 1000000;  // initial for the proble max
	num = -1;
	for (int i=0;i<m_num;i++)
	{
		if (array[i] != -1)
		{
			if (min > array[i])
			{
				min = array[i];
				num = i;
			}
		}
	}
	if (num != -1)
	{
		return num;
	} 
	else return -1;
	
}


// array is for the 20 results that the retrieval method feed back;
//we can use it for display. What in it are the number of the similar models number;
//void CRetrievalMethod::Retrieve20Result(int *distance, int array[], int m_totle=1814)

void CRetrievalMethod::Retrieval20Result(int *distance, int array[], int m_totle)
{	
	int *c_distance;
	c_distance = new int[m_totle];


	for (int i=0;i<m_totle;i++)
	{
		c_distance[i]=distance[i];
	}
	for (int h=0;h<20;h++)
	{
		array[h] = FineMinNum(c_distance,m_totle);
		c_distance[(array[h])] = -1;
	}   // array is the results of this retrieval;
	delete[] c_distance;
	//return;
}
