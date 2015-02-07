    // Source file for the OFF file viewer



////////////////////////////////////////////////////////////
// INCLUDE FILES
////////////////////////////////////////////////////////////

// Standard include files
#include "GraphicsGems.h"
//#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <time.h>
#include <MATH.H>
#define WatermarkLength 256
#define WatermarkColumn 16
#define MaxNeighb 50
int key=66;

// Windows include files 

#ifdef _WIN32
#include <windows.h>
#endif



// OpenGL include files 

#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/glut.h"




////////////////////////////////////////////////////////////
// CLASSES
////////////////////////////////////////////////////////////
class Attack;
class Face;
class Genotype;
class Matrix;
class Mesh;
class Recover;
class Tools;
class Vector3;
class Vector4;
class Anneal;
class Permute;
class Permute{
public:
	void PSEUDO(unsigned char *origwmdata,unsigned char *pmwmdata,int N1,int N2,int seed);
	void DPSEUDO(unsigned char *pmwmdata,unsigned char *rewmdata,int N1,int N2,int seed);
}permute;
class Anneal{
public:
#define TFACTR  0.5
#define MBIG 1000000
#define MSEED 161803398
#define MZ 0
#define FAC (1.0/MBIG)
#define MMAX 2
float y,T;
long idum;
Anneal();
int bolziman(float de,float t);
float ran(long *idum);
int irbit(unsigned long *iseed);
float move(Mesh *mesh1,Mesh *mesh2,Mesh *tempmesh,int n,int s,float x[],float t[],float c[],float min,float *up,float *low);
Mesh *registration(Mesh *mesh1,Mesh *mesh2,int num=10);
}anneal;


class Vector4 {
public: 
	float x, y, z,w;
	Vector4();
	Vector4(Vector3 &p);
};
class Vector3 {
public: 
	float x, y, z;
	Vector3(void);
	Vector3(float xx,float yy,float zz);
	Vector3(Vector4 &p);
	Vector3 Scale(Vector3 vertex,float scale);
	Vector3 AddVector3(Vector3 vector1,Vector3 vector2);
	Vector3 SubVector3(Vector3 vector1,Vector3 vector2);
	float Magnitude(Vector3 vector);
	float Distance(Vector3 vector1,Vector3 vector2);
	Vector3 Direction(Vector3 vector1,Vector3 vector2);
	Vector3 Normalize(Vector3 vector1);
	Matrix3 V3MV3(Vector3 vector1,Vector3 vector2);
	float V3PlotMul(Vector3 vector1,Vector3 vector2);
	float Max(Vector3 &v);
} vector;
class Tools{
public:
	double SubEnergy(Mesh *mesh1,Mesh *mesh2);
	Vector3 mean(Vector3 *vertex,long nverts);
	Vector3 CrossOver(Vector3 vector1,Vector3 vector2);
	Vector3 FaceNormal(Mesh *mesh,Face &face);
	Vector4 Mat4MulV4(Matrix4 &m4,Vector4 &v4);//multiply matrix4 with vector4
	Vector3 Mat3MulV3(Matrix3 &m3,Vector3 &v3);//multiply matrix3 with vector3
	Matrix3 Variance(Mesh *mesh,int vertex);//compute the second order moment of the vertex's neighbourhoods
	void DeleteVertex(Mesh *mesh,int iVertex);
	void DeleteFace(Mesh *mesh,int iFace);
	bool bIsNeighb(Mesh *mesh,int a,int b);//found out if vertex cut's neighbourhoods a and b is neighbourhood 
	void AppendFaces(Mesh *mesh,int cut,int (*a)[2],int countface);//append faces when faces including the vertex is cut
	void NeighbFaces(Mesh *mesh,int cut,int (*a)[2],int *countface);//compute neighbourhood face vertices
	bool IsOdd(int vertex,int (*a)[2],int countface);//find out if vertex is single in the cut vertex's neighbourhood face vertices
	float FindND(Mesh *mesh1,Mesh *mesh2,int ivertex,int *matchi);//find the nearest distance between mesh1's vertex ivertex and mesh2's vertices 
	void DeleteOverlapFaces(Mesh *mesh);//delete overlap faces in mesh
	void DeleteAbnormal(Mesh *mesh);//delete all the abnormal faces in mesh
}tools;
class Recover{
public:
	Mesh *registration(Mesh *mesh1,Mesh *mesh2,Mesh *mesh3);//mesh1 is orignal,mesh2 is rotated
	Mesh *resort(Mesh *mesh1,Mesh *mesh2);//mesh1 is orignal,mesh2 is disturbed
	Mesh *resample(Mesh *mesh1,Mesh *mesh2,float alpha);//mesh1 is orignal,mesh2 is downsampled
}recover;
class Mesh {
public:  
	Mesh(void);
	Mesh(Mesh *mesh);
	~Mesh();
  Vector3 centriod;
  int nverts;
  Vector3 *verts;
  int nfaces;
  Face *faces;
  Vector3 *VertexNormal;
  int (*neighbourhood)[MaxNeighb];
  bool *VertexExcluded;
  float *weight;
  double *area;
  float magnitude;
  float meanscale;//the average distance from all points on the surfaces of all polygons to the center of mass.
} ;
class Matrix{
public:
	void nrerror(char error_text[]);
	double *vectorm(int nl,int nh);
	double **matrix(int nrl=0,int nrh=3,int ncl=0,int nch=3) ;
	void free_vector(double *v,int nl,int nh);
	void free_matrix(double **m,int nrl=0,int nrh=3,int ncl=0,int nch=3);
	void inverse(double **mat, int dim=3) ;
	void ludcmp(double **a, int n, int *indx, double *d) ;
	void lubksb(double **a, int n, int *indx, double *b) ;
	void print(double **m,int nrl=0,int nrh=3,int ncl=0,int nch=3);
	Matrix3 AddMatrix3(Matrix3 &M1,Matrix3 &M2);
	Matrix3 Mat3Div(Matrix3 &M,float n);
	float Mat3lemda(Matrix3 &M);
	float ComMat3lemda(Matrix3 &M,Vector3 *v,int iteration);
}mat;
class Face {
public:
  Face(void);
  Face(Face &face);
  Face(Face *face);
  double area(Face &face1, Mesh *mesh);
  int nverts;
  int *verts;
  Vector3 normal;
}face;
class Attack{
public:
	Mesh *ChangeView(Mesh *mesh,Mesh *tempmesh,float a=0,float b=0,float r=0,float dx=0,float dy=0,float dz=0);
	Vector3 Rotate(Vector3 v,float a,float b,float r,float dx,float dy,float dz);
	Mesh *Cut(Mesh *mesh);
	Mesh *AddPulseNoise(Mesh *mesh,float AlphaNoise);
	Mesh *ChangeOrder(Mesh *mesh,int RotateNum);
	Mesh *Disturb(Mesh *mesh);
	Mesh *Move(Mesh *mesh,Vector3 dCentriod);
	Mesh *Scale(Mesh *mesh,float scale);
	Mesh *DownSample(Mesh *mesh,int num);
	Mesh *DownSample1(Mesh *mesh,float prop);
	Mesh *AddNoise(Mesh *mesh,float *noise,float alpha);
}attack;
class Genotype           /* Each genotype is a number of the population */
{
public:
	#define POPSIZE   50    /* Population size */
#define MAXGENS   20  /* Maximum number of generations */
#define NVARS     6     /* Number of problem variables */
#define PXOVER    0.3   /* Probability of crossover */
#define PMUTATION 0.00  /* Proportion of mutated variables */
  double Gene[NVARS + 1]; /* A string of vars makes a genotype */
  double Fitness;         /* The genotype's fitness */
  double Upper[NVARS];           /* The genotype's upper bound */
  double Lower[NVARS];           /* The genotype's lower bound */
  double RFitness;        /* The relative fitness */
  double CFitness;        /* The cumulative fitness */
  int    Survivor;        /* Flag for selection procedure */
  int Generation;   /* Current generation number */
int NSurvivors;   /* The number of survivors in a generation */
int Best;         /* The best genotype in the population */
FILE *galog;      /* A log file to write results to */
	void initialize(void);
	double RandVal (double low, double high);
	void evaluate(Mesh *mesh1,Mesh *mesh2,Mesh *mesh3);
	void select(void);
	void crossover(void);
	void mutate(void);
	void report(void);
}genotype;
Anneal::Anneal():T(0),idum(-1){}
int Anneal::bolziman(float de,float t)
 {
      //float ran(long *idum);
      static long gljdum=-1;
      return de<0.0 ||ran(&gljdum)<exp(-de/(t));
  }
float Anneal::ran(long *idum)
{static int inext,inextp;
 static long ma[56];
 static int iff=0;
 long mj,mk;
 int i,ii,k;
 if(*idum<0||iff==0) {
		      iff=1;
		      mj=MSEED-(*idum<0?-*idum:*idum);
		      mj%=MBIG;
		      ma[55]=mj;
		      mk=1;
		      for(i=1;i<54;i++){
					ii=(21*i)%55;
					ma[ii]=mk;
					mk=mj-mk;
					if(mk<MZ)mk+=MBIG;
					mj=ma[ii];
			}
			for(k=1;k<=4;k++)
			     for(i=1;i<=55;i++){
				   ma[i]-=ma[1+(i+30)%55];
				   if(ma[i]<MZ) ma[i]+=MBIG;
				   }
			 inext=0;
			 inextp=31;
			 *idum=1;
		     }
    if(++inext==56)inext=1;
    if(++inextp==56) inextp=1;
    mj=ma[inext]-ma[inextp];
    if(mj<MZ) mj+=MBIG;
    ma[inext]=mj;
    return mj*FAC;
    }
 int Anneal::irbit(unsigned long *iseed)
 {
     unsigned long newbit;
      newbit=(*iseed &131072)>>17
	    ^(*iseed&16)>>4
	      ^(*iseed &2)>>1
	      ^(*iseed &1);
	      *iseed=(*iseed<<1)|newbit;
	      return newbit;
}
float Anneal::move(Mesh *mesh1,Mesh *mesh2,Mesh *tempmesh,int n,int s,float x[],\
				   float t[],float c[],float min,float *up,float *low)
{
 int i[6],j,k,flag;
 float sig(0),temp1(0),temp2(0),p1(0),p2(0),cost,mincost;

 float xtemp[6],xmin[6];
 for(j=0;j<6;j++)xtemp[j]=x[j];
   mincost=min;  flag=0;
for(i[5]=1;i[5]<=2;i[5]++)
    {  for(i[4]=1;i[4]<=2;i[4]++)
     {  for(i[3]=1;i[3]<=2;i[3]++)
       {for(i[2]=1;i[2]<=2;i[2]++)
	{for(i[1]=1;i[1]<=2;i[1]++)
	 {for(i[0]=1;i[0]<=2;i[0]++)
	  { for(j=0;j<n;j++)
	   { k=(j+s)%6;
	   if (i[j]==1) {
	   xtemp[k]=x[k]+(int)((up[k]-x[k])*ran(&idum)*MBIG*T)*FAC;
	   if(xtemp[k]>up[k]) xtemp[k]=up[k];
	   if(xtemp[k]<low[k])xtemp[k]=low[k];}
	    if(i[j]==2) {
	    xtemp[k]=x[k]-(int)((x[k]-low[k])*ran(&idum)*MBIG*T)*FAC;
            	   if(xtemp[k]>up[k]) xtemp[k]=up[k];
	   if(xtemp[k]<low[k])xtemp[k]=low[k];}

	    }

      float a=xtemp[0];float b=xtemp[1];float r=xtemp[2];
	  float dx=xtemp[3];float dy=xtemp[4];float dz=xtemp[5];
	  tempmesh=attack.ChangeView(mesh1,tempmesh,a,b,r,dx,dy,dz);
	  //fitness function
	 cost=tools.SubEnergy(mesh2,tempmesh);
      if ((mincost-cost)>FAC)
	   {flag=1;
	    mincost=cost;
	    for(j=0;j<6;j++)xmin[j]=xtemp[j];
	    }
	 } if(n==1) break;
	 }if(n==1||n==2) break;
	 }if(n==1||n==2||n==3) break;
	 }if(n==1||n==2||n==3||n==4) break;
	 }if(n==1||n==2||n==3||n==4||n==5)break;
	 }

      if(flag)
      for(j=0;j<6;j++)
	x[j]=xmin[j];

	return mincost;
     }

Mesh *Anneal::registration(Mesh *mesh1,Mesh *mesh2,int num){
	printf("registrating using anneal....\n");
	Mesh *tempmesh=new Mesh(mesh1);
	float x[6],t[6];
    float mx[6]={25*DTOR,50*DTOR,80*DTOR,0.001,0.001,0.001};//initial condition
    float c[6],mincost=MBIG,cost,dc;
    float up[6]={mx[0]*1.2,mx[1]*1.2,mx[2]*1.2,mx[3]*1.2,mx[4]*1.2,mx[5]*1.2};//up bound
	float low[6]={mx[0]*0.8,mx[1]*0.8,mx[2]*0.8,mx[3]*0.8,mx[4]*0.8,mx[5]*0.8};//low bound
    int m=0,i,j,n,s,k;
	for(i=0;i<6;i++){
		t[i]=0.005;c[i]=25;
	}
		for(k=0;k<6;k++){
			mx[k]=low[k]+(int)((up[k]-low[k])*anneal.ran(&anneal.idum)/FAC)*FAC;
			    if (mx[k]>up[k]) mx[k]=up[k];
			    if(mx[k]<low[k])mx[k]=low[k];
		}
		anneal.T=1.0;mincost=MBIG;
		for(i=1;i<=num;i++){
			for(j=1;j<=200;j++){
				n=(int)(anneal.ran(&anneal.idum)*4)%4+1;
				s=(1+(int)(anneal.ran(&anneal.idum)*6))%6;
					for(k=0;k<6;k++)x[k]=mx[k];
						cost=anneal.move(mesh1,mesh2,tempmesh,n,s,x,t,c,mincost,up,low);

					dc=cost-mincost;
					if(fabs(dc)>=FAC && anneal.bolziman(dc,anneal.T)){// && ??????????????
					for(k=0;k<6;k++)
						mx[k]=x[k];
					mincost=cost;
					}
			}
			printf("\nnumber:%d,T=%f,mincost=%f",i,anneal.T,mincost);
			printf("\n %f,%f,%f,%f,%f,%f",mx[0]*RTOD,mx[1]*RTOD,mx[2]*RTOD,mx[3],mx[4],mx[5]);
			anneal.T*=TFACTR;
		}/* end of i */
		double **m1 = mat.matrix(0,4,0,4); //用matrix函数，分配一个4*4的矩阵,通过m[i][j]赋值，对矩阵初始化 
		//Matrix4 RotMat(PI/6,PI/3,PI/4,0.1,0.2,0.3);//generate true Rotate Matrix according to a,b,r,dx,dy,dz		
		Matrix4 RotMat(mx[0],mx[1],mx[2],mx[3],mx[4],mx[5]);//generate computed Rotate Matrix according to a,b,r,dx,dy,dz
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				m1[i][j]=RotMat.element[i][j];//transfer matrix to array 4*4
			}
		}
		printf("\n");
		mat.print(m1,0,4,0,4);
		mat.inverse(m1,4); //矩阵求逆，结果也在m中 
		//Matrix4 iRotMat(m1);???????????
		Matrix4 iRotMat;
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
			iRotMat.element[i][j]=m1[i][j];
			}
		}
		mat.print(m1,0,4,0,4);
		for(i=0;i<mesh2->nverts;i++){
			Vector4 inv4(mesh2->verts[i]);
			tempmesh->verts[i]=tools.Mat4MulV4(iRotMat,inv4);//实现重定位
		}
		mat.free_matrix(m1,0,4,0,4); //释放矩阵。 
		return tempmesh;
}





 Genotype Population[POPSIZE+1]; /* The population of genotypes */
/* GA function prototypes */
 void Genotype::initialize(void)
{
  FILE     *infile;
  int      i,j;
  double   lbound,ubound;

  /* Open the input file */
  
  if((infile = fopen("gadata.txt","r"))==NULL)
    {
      fprintf(galog,"\nCannot open input file!\n");
      exit(1);
    }

/* Read in the lower and upper bounds for each variable. */
/* Note that there is no error checking here! */

  for(i=0;i<NVARS;i++)
    {
      fscanf(infile, "%lf", &lbound);
      fscanf(infile, "%lf", &ubound);
      for(j=0;j<POPSIZE;j++)
	{
	  Population[j].Lower[i]=lbound;
	  Population[j].Upper[i]=ubound;
	}
    }

/* Using the lower and upper bounds, randomly */
  srand((unsigned)time(NULL));
  for(i=0;i<POPSIZE;i++)
      for(j=0;j<NVARS;j++)
	  Population[i].Gene[j]=RandVal(Population[i].Lower[j], Population[i].Upper[j]);
  fclose(infile);
}

/*******************************************************************
  RandVal returns a pseudorandom value between the supplied
  low and high arguments.
********************************************************************/

double Genotype::RandVal (double low, double high)
{
  double val;
  val=((double) (rand() % 1000) / 1000.0) * (high - low) + low;
  return (val);
}
      
void Genotype::evaluate(Mesh *mesh1,Mesh *mesh2,Mesh *mesh3)
{
  int mem;
  int i;
  double a,b,r,dx,dy,dz;
  Best=0;Population[POPSIZE].Fitness=1e+8;
  for(mem=0;mem<POPSIZE;mem++){
      a=Population[mem].Gene[0];
      b=Population[mem].Gene[1];
      r=Population[mem].Gene[2];
	  dx=Population[mem].Gene[3];
	  dy=Population[mem].Gene[4];
	  dz=Population[mem].Gene[5];
	  mesh3=attack.ChangeView(mesh1,mesh3,a,b,r,dx,dy,dz);
	  //fitness function
	  Population[mem].Fitness=tools.SubEnergy(mesh2,mesh3);

      /* Keep track of the best member of the population */
      /* Note that the last member of the population holds */
      /* a copy of the best member. */

      if(Population[mem].Fitness < Population[POPSIZE].Fitness){
		  Best=mem;
		  Population[POPSIZE].Fitness=Population[mem].Fitness;
		  for(i=0;i<NVARS;i++)
			  Population[POPSIZE].Gene[i]=Population[mem].Gene[i];
	  }
  }
}


void Genotype::select(void)
{
  int mem;     /* A counter variable */
  double sum(0);  /* The total population fitness */


  /* First, find the total fitness of the population */

  for(mem=0;mem < POPSIZE+1;mem++)
    {
      sum+=Population[mem].Fitness;
    }
  /* Next, caculate the relative fitness of each genotype */

  for(mem=0;mem < POPSIZE+1;mem++)
    {
      Population[mem].RFitness = Population[mem].RFitness / sum;
    }
  /* Now calculate the cumulative fitness of each genotype */

  Population[0].CFitness = Population[0].RFitness;
  for(mem=1;mem < POPSIZE+1;mem++)
    {
      Population[mem].CFitness = Population[mem-1].CFitness +
	Population[mem].RFitness;
    }
  /* Finally, select the survivors using the cumulative fitness */

  for(mem=0;mem < POPSIZE;mem++)
    {
      /* Based on the probability of crossover, */
      /* decide if the member survives */
      
      if((double) (rand() % 1000) / 1000.0 <= PXOVER)
	{
	  Population[mem].Survivor = TRUE;
	  NSurvivors++;
	}
      else
	{
	  Population[mem].Survivor = FALSE;
	}
    }
  /* Make sure the best member survives! */

  Population[Best].Survivor = TRUE;
  Population[POPSIZE+1].Survivor = TRUE;
}

void Genotype::crossover(void)
{
  int i,count;
  int mem;       /* A counting variable */
  int POne, a;   /* Parent one */
  int PTwo, b;   /* Parent two */
  int point;     /* Crossover point */

  /* Loop through the population replacing nonsurviving */
  /* genotypes using crossover between pairs of survivors */

  for(mem=0;mem < POPSIZE;mem++)
    {
      /* Does this number need to be replaced ? */
      
      if(Population[mem].Survivor == FALSE)
	{
	  /* Select two survivors */

	  a = (rand() % NSurvivors) + 1;
	  b = (rand() % NSurvivors) + 1;

	  /* Now find those survivors in the population by searching */
	  /* for the a'th and b'th survivors. This is not efficient, */
	  /* but is easier to understand. */

	  count = 0;
	  POne = 0;
	  PTwo =0;
	  for(i=0;i<POPSIZE+1;i++)
	    {
	      if(Population[i].Survivor == TRUE)
		{
		  count++;
		  if(count == a) POne = count;
		  if(count == b) PTwo = count;
		}
	    }
	  /* Select the crossover point */

	  point = (rand() % NVARS) + 1;

	  /* Finally, perform the crossover. Copy everything up to */
	  /* the crossover point from the first parent. */

	  for(i = 0; i < point; i++)
	    {
	      Population[mem].Gene[i] = Population[POne].Gene[i];
	    }

	  for(i = point; i < NVARS; i++)
	    {
	      Population[mem].Gene[i] = Population[PTwo].Gene[i];
	    }
	}
    }
}


void Genotype::mutate(void)
{
  int i;
  double lbound, hbound; /* Bounds on the var to be mutated */
  int nmutations;        /* The number of mutations to be performed */
  int member;            /* The member to be mutated */
  int var;               /* The variable to be mutated */

  /* Find out how many mutations will be performed */

  nmutations = (int) ((double) (POPSIZE * NVARS) * PMUTATION);

  /* Loop until all mutations have been performed */

  for(i=0; i < nmutations; i++)
    {
      member = rand() % POPSIZE; /* Select a member for mutation */
      var = rand() % NVARS; /* Select a variable for mutation */
      lbound = Population[member].Lower[var]; /* Find the bounds on the var being mutated */
      hbound = Population[member].Upper[var];

      /* Generate a new value between the bounds and replace */
      /* the old value with the new mutated value. */

      Population[member].Gene[var] = RandVal(lbound, hbound);
    }
}


void Genotype::report(void)
{
  int i;
  double best_val;   /* Best population fitness */
  double avg;        /* Average population fitness */
  double stddev;     /* Std. deviation of population fitness */
  double sum_square; /* Sum of the squares for std. dev calc. */
  double square_sum; /* Square of the sums for std. dev calc. */
  double sum;        /* The summed population fitness */

  sum = 0.0;
  sum_square=0.0;

  /* Calculate the summed population fitness and the sum */
  /* of the squared individual fitness. */

for (i=0; i< POPSIZE; i++)
{
     sum += Population[i].Fitness;
     sum_square += Population[i].Fitness * Population[i].Fitness;
}

  /* Caculate the average and standard deviations of the population's fitness */

  avg = sum / (double) POPSIZE;
  square_sum = sum * sum / (double) POPSIZE;
  stddev = sqrt((1.0/(double) (POPSIZE - 1)) * (sum_square - square_sum));
  best_val = Population[POPSIZE].Fitness;

  /* Print the generation, best, avg, and std. deviation to a file in csv format. */

  fprintf(galog,"\n%d , %4.3f , %4.3f , %4.3f , \n\n", Generation, best_val, avg, stddev);
}

    Vector3::Vector3(void):x(0),y(0),z(0){}
	Vector3::Vector3(float xx,float yy,float zz){x=xx;y=yy;z=zz;}
	Vector3::Vector3(Vector4 &p){x=p.x;y=p.y;z=p.z;}
	Vector3 Vector3::Scale(Vector3 vertex,float scale){
		scale=(scale>1e8)?1e8:scale;
		vertex.x=vertex.x*scale;vertex.y=vertex.y*scale;vertex.z=vertex.z*scale;return vertex;
	}
	Vector3 Vector3::AddVector3(Vector3 vector1,Vector3 vector2){Vector3 vector;vector.x=vector1.x+vector2.x;vector.y=vector1.y+vector2.y;vector.z=vector1.z+vector2.z;return vector;}
	Vector3 Vector3::SubVector3(Vector3 vector1,Vector3 vector2){Vector3 vector;vector.x=vector1.x-vector2.x;vector.y=vector1.y-vector2.y;vector.z=vector1.z-vector2.z;return vector;}
	float Vector3::Magnitude(Vector3 vector){
		float result=sqrt((vector.x)*(vector.x)+(vector.y)*(vector.y)+(vector.z)*(vector.z));
		return (result<1e-8)?1e-8:result;
	}
	float Vector3::Distance(Vector3 vector1,Vector3 vector2){return Magnitude(SubVector3(vector1,vector2));}
	Vector3 Vector3::Direction(Vector3 vector1,Vector3 vector2){return Scale(SubVector3(vector1,vector2),1.0/Distance(vector1,vector2));}
	Vector3 Vector3::Normalize(Vector3 vector1){return vector.Scale(vector1,1.0/vector.Magnitude(vector1));}
    Matrix3 Vector3::V3MV3(Vector3 vector1,Vector3 vector2){//1*3 vector multiply 3*1 vector
		Matrix3 matrix3;
		matrix3.element[0][0]=vector1.x*vector2.x;
 		matrix3.element[0][1]=vector1.x*vector2.y;
 		matrix3.element[0][2]=vector1.x*vector2.z;
 		matrix3.element[1][0]=vector1.y*vector2.x;
 		matrix3.element[1][1]=vector1.y*vector2.y;
 		matrix3.element[1][2]=vector1.y*vector2.z;
 		matrix3.element[2][0]=vector1.z*vector2.x;
 		matrix3.element[2][1]=vector1.z*vector2.y;
 		matrix3.element[2][2]=vector1.z*vector2.z;
		return matrix3;
	}
	float Vector3::V3PlotMul(Vector3 vector1,Vector3 vector2){//1*3 vector plot multiply 1*3 vector
		return vector1.x*vector2.x+vector1.y*vector2.y+vector1.z*vector2.z;
	}
	float Vector3::Max(Vector3 &vector){
		return max(max(vector.x,vector.y),vector.z);
	}
Vector4::Vector4(){x=y=z=0;w=1;}
Vector4::Vector4(Vector3 &p){x=p.x;y=p.y;z=p.z;w=1;}

Face::Face(void) : nverts(0), verts(0) {};
Face::Face(Face &face){
	 nverts=face.nverts;
	 normal=face.normal;
	 verts=new int[face.nverts];
	 for (int i=0;i<face.nverts;i++){verts[i]=face.verts[i];}
}
Face::Face(Face *face){
	 nverts=face->nverts;
	 normal=face->normal;
	 verts=new int[face->nverts];
	 for (int i=0;i<face->nverts;i++){verts[i]=face->verts[i];}
}

Mesh::Mesh(void) : nverts(0), verts(0), nfaces(0), faces(0) ,magnitude(0),\
		VertexNormal(0),neighbourhood(0),VertexExcluded(0),weight(0){};
Mesh::Mesh(Mesh *mesh):nverts(mesh->nverts),nfaces(mesh->nfaces),\
			centriod(mesh->centriod),magnitude(mesh->magnitude){
		verts=new Vector3[mesh->nverts];assert(verts);
		VertexNormal=new Vector3[mesh->nverts];assert(VertexNormal);
		VertexExcluded=new bool[mesh->nverts];assert(VertexExcluded);
		weight=new float[mesh->nverts];assert(weight);
		neighbourhood=new int[mesh->nverts][MaxNeighb];assert(neighbourhood);
		for (int i=0;i<nverts;i++) {
			verts[i]=mesh->verts[i];
			VertexNormal[i]=mesh->VertexNormal[i];
			VertexExcluded[i]=mesh->VertexExcluded[i];
			weight[i]=mesh->weight[i];
			for(int j=0;j<MaxNeighb;j++){neighbourhood[i][j]=mesh->neighbourhood[i][j];}
		}
		faces=new Face[nfaces];assert(faces);
		for (i=0;i<nfaces;i++){
			faces[i].nverts=mesh->faces[i].nverts;
			faces[i].verts =new int[mesh->faces[i].nverts];assert(faces[i].verts);
			for (int j=0;j<mesh->faces[i].nverts;j++){faces[i].verts[j]=mesh->faces[i].verts[j];}
			faces[i].normal=mesh->faces[i].normal;
		}
	}
Mesh::~Mesh(){
	  delete []verts;
  for (int i=0;i<nfaces;i++){
		delete []faces[i].verts;
		delete []VertexExcluded;
		delete []weight;
  }
  delete []faces;
  delete []neighbourhood;
}
	double Tools::SubEnergy(Mesh *mesh2,Mesh *mesh3){
		double energy=0;
		for (int i=0;i<mesh2->nverts;i++){
			energy+=vector.Distance(mesh2->verts[i],mesh3->verts[i])*vector.Distance(mesh2->verts[i],mesh3->verts[i]);
		}
		return energy;
	}
	Vector3 Tools::mean(Vector3 *vertex,long nverts){
		Vector3 sum;
		for (int i=0;i<nverts;i++){
			sum=sum.AddVector3(sum,vertex[i]);
		}
		return sum.Scale(sum,1.0/nverts);
	};
	Vector3 Tools::CrossOver(Vector3 vector1,Vector3 vector2){
		Vector3 result;
		result.x=vector1.y*vector2.z-vector2.y*vector1.z;
		result.y=vector1.x*vector2.z-vector2.x*vector1.z;
		result.z=vector1.x*vector2.y-vector2.x*vector1.y;
		return result;
	}
	Vector3 Tools::FaceNormal(Mesh *mesh,Face &face){
		Vector3 *v1 = &(mesh->verts[face.verts[face.nverts-1]]);
		for (int i = 0; i < face.nverts; i++) {
			Vector3 *v2 = &(mesh->verts[face.verts[i]]);
			face.normal.x += (v1->y - v2->y) * (v1->z + v2->z);
			face.normal.y += (v1->z - v2->z) * (v1->x + v2->x);
			face.normal.z += (v1->x - v2->x) * (v1->y + v2->y);
			v1 = v2;
		}
		return face.normal;
	}
	void Tools::DeleteVertex(Mesh *mesh,int iVertex){
		int i,j,k,k1,temp,iNeighb;bool endsearch=FALSE;
		for (i=0;i<mesh->nverts;i++){//change neighbourhoods concerning iVertex
			iNeighb=-1;
			while (++iNeighb!=MaxNeighb) {
				if(mesh->neighbourhood[i][iNeighb]==iVertex){
					for(j=iNeighb;j<MaxNeighb-1;j++){
						temp=mesh->neighbourhood[i][j+1];
						mesh->neighbourhood[i][j]=(temp>iVertex)?(temp-1):temp;
					}
					for(j=0;j<iNeighb;j++){
						if(mesh->neighbourhood[i][iNeighb]>iVertex)
							mesh->neighbourhood[i][iNeighb]--;
					}
				}
				else if(mesh->neighbourhood[i][iNeighb]>iVertex)
							mesh->neighbourhood[i][iNeighb]--;
				}	
			}
		int nfaces=mesh->nfaces;
		for (i=0;i<nfaces;i++){//change faces concerning iVertex
			for (j=0;j<mesh->faces[i].nverts;j++){
				if(mesh->faces[i].verts[j]==iVertex){//delete the faces connected to iVertex
					mesh->nfaces--;
					if(i==mesh->nfaces) endsearch=TRUE;
					else {
						for(k=i;k<nfaces-1;k++){
							mesh->faces[k].normal=mesh->faces[k+1].normal;
							mesh->faces[k].nverts=mesh->faces[k+1].nverts;
							mesh->faces[k].verts[0]=mesh->faces[k+1].verts[0];
							mesh->faces[k].verts[1]=mesh->faces[k+1].verts[1];
							mesh->faces[k].verts[2]=mesh->faces[k+1].verts[2];
						}
						j=mesh->faces[i].nverts;//end searching j
						i--;//researching iVertex
					}
				}
			}
			if(endsearch) i=nfaces;
		}
		for (i=0;i<nfaces;i++){//change faces indexes concerning iVertex
			for(k1=0;k1<mesh->faces[i].nverts;k1++){
				if(mesh->faces[i].verts[k1]>iVertex)
					mesh->faces[i].verts[k1]--;
			}
		}
								
		for (i=iVertex;i<mesh->nverts-1;i++){//delete the vertex and its properities
			mesh->weight[i]=mesh->weight[i+1];
			mesh->VertexNormal[i]=mesh->VertexNormal[i+1];
			mesh->VertexExcluded[i]=mesh->VertexExcluded[i+1];
			mesh->verts[i]=mesh->verts[i+1];
			for(j=iNeighb;j<MaxNeighb-1;j++)
				mesh->neighbourhood[i][j]=mesh->neighbourhood[i+1][j];
		}
		mesh->nverts--;
	}
	void Tools::DeleteFace(Mesh *mesh,int iFace){
		int i;
		for (i=iFace;i<mesh->nfaces;i++){
			if(i==(mesh->nfaces-1)){//face to be cut is the last face
				mesh->nfaces--;
				return;
			}
			//delete face
			mesh->faces[i].normal =mesh->faces[i+1].normal;
			mesh->faces[i].nverts=mesh->faces[i+1].nverts;
			mesh->faces[i].verts[0]=mesh->faces[i+1].verts[0];
			mesh->faces[i].verts[1]=mesh->faces[i+1].verts[1];
			mesh->faces[i].verts[2]=mesh->faces[i+1].verts[2];
		}
	}
	void Tools::NeighbFaces(Mesh *mesh,int cut,int (*a)[2],int *countface){
		int t1,t2,t3;

		int icountface=0;
		for (t1=0;t1<mesh->nfaces;t1++){
			for(t2=0,t3=0;t2<mesh->faces[t1].nverts;t2++){//find all the neighbourhood faces vertices
				if (cut==mesh->faces[t1].verts[t2]){
						while(cut==mesh->faces[t1].verts[t3++]); 
						a[icountface][0]=mesh->faces[t1].verts[--t3];
						while(cut==mesh->faces[t1].verts[++t3]);
						a[icountface++][1]=mesh->faces[t1].verts[t3];
				}
			}
		}
	}
	void Tools::AppendFaces(Mesh *mesh,int cut,int (*a)[2],int countface){
	//	if(countface<1) return;
		int i,j;int first,mid,last,icountface=0;
		bool *NeighfaceUsed=new bool[countface];
		for(i=0;i<countface;i++){NeighfaceUsed[i]=FALSE;}
		first=a[0][0];mid=a[0][1];icountface=0;i=0;bool endflag=FALSE;
		NeighfaceUsed[0]=TRUE;
		do {
			bool tempflag=IsOdd(mid,a,countface);
			if(tempflag){
				tempflag=FALSE;
				for(int t1=0;t1<countface;t1++){
					for(int t2=0;t2<2;t2++){
						if(IsOdd(a[t1][t2],a,countface)&&!NeighfaceUsed[t1]&&(a[t1][t2]!=mid)){
							NeighfaceUsed[t1]=TRUE;
							mid=a[t1][t2];
							tempflag=TRUE;
						}
					}
				}
			if (!tempflag) return;
			}//process the odd condition

			if(i){
				if(mid==a[i][0]) {
					NeighfaceUsed[i]=TRUE;
					last=a[i][1];
					if(first!=last){
						mesh->faces[mesh->nfaces].verts[0]=first;
						mesh->faces[mesh->nfaces].verts[1]=mid;
						mesh->faces[mesh->nfaces].verts[2]=last;
						mesh->nfaces++;
					}
					mid=last;
				}
				else if(mid==a[i][1]){
					NeighfaceUsed[i]=TRUE;
					last=a[i][0];
					if(first!=last){
						mesh->faces[mesh->nfaces].verts[0]=first;
						mesh->faces[mesh->nfaces].verts[1]=mid;
						mesh->faces[mesh->nfaces].verts[2]=last;
						mesh->nfaces++;
					}
					mid=last;
				}
			}
			for(j=0,endflag=TRUE;j<countface;j++){endflag&=NeighfaceUsed[j];}
			i=++i%countface;
			if(first==last) endflag=TRUE;
		} while(!endflag);
	}
	void Tools::DeleteOverlapFaces(Mesh *mesh){
		int t1,t2,t3,t4;
				int equalnum;
				for(t1=0;t1<mesh->nfaces-1;t1++){
					for(t2=t1+1;t2<mesh->nfaces;t2++){
						equalnum=0;
						for(t3=0;t3<3;t3++){
							for(t4=0;t4<3;t4++){
								if(mesh->faces[t1].verts[t3]==mesh->faces[t2].verts[t4]){
									t4=3;
									equalnum++;
								}								
							}
						}
						if(equalnum==3){
							tools.DeleteFace(mesh,t2);
						}
					}
				}
	}
	void Tools::DeleteAbnormal(Mesh *mesh){
		printf("deleting abnormal faces and vertices....\n");
		int i,t1,t2;
		int countvert1=0,countface;int deleteface;bool abnormalend=TRUE;
		do{
			for (i=0;i<mesh->nverts;i++){
				countface=0;
				for (t1=0;t1<mesh->nfaces;t1++){
						for(t2=0;t2<3;t2++){
							if (i==mesh->faces[t1].verts[t2]){
								countface++;
								deleteface=t1;
							}
						}
					}
				if(countface==1) {
					tools.DeleteFace(mesh,deleteface);
					tools.DeleteVertex(mesh,i-countvert1++);
					abnormalend=FALSE;
				}
			}
		}while(!abnormalend);
	}
	bool Tools::IsOdd(int vertex,int (*a)[2],int countface){
		bool isodd=FALSE;
		for(int i=0;i<countface;i++){
			if((vertex==a[i][0])||(vertex==a[i][1]))
				isodd=!isodd;
		}
		return isodd;
	}
	bool Tools::bIsNeighb(Mesh *mesh,int a,int b){
		int iNeighb1=-1;
		while(mesh->neighbourhood[a][++iNeighb1]!=-1){
			if((b!=a)&&(mesh->neighbourhood[a][iNeighb1]==b))
				return TRUE;
			}
		return FALSE;
	}
	Vector4 Tools::Mat4MulV4(Matrix4 &m4,Vector4 &v4){
		Vector4 rv4;
		rv4.x=m4.element[0][0]*v4.x+m4.element[0][1]*v4.y+m4.element[0][2]*v4.z+m4.element[0][3]*v4.w;
		rv4.y=m4.element[1][0]*v4.x+m4.element[1][1]*v4.y+m4.element[1][2]*v4.z+m4.element[1][3]*v4.w;
		rv4.z=m4.element[2][0]*v4.x+m4.element[2][1]*v4.y+m4.element[2][2]*v4.z+m4.element[2][3]*v4.w;
		rv4.w=m4.element[3][0]*v4.x+m4.element[3][1]*v4.y+m4.element[3][2]*v4.z+m4.element[3][3]*v4.w;
		return rv4;
	}
	Vector3 Tools::Mat3MulV3(Matrix3 &m3,Vector3 &v3){
		Vector3 rv3;
		rv3.x=m3.element[0][0]*v3.x+m3.element[0][1]*v3.y+m3.element[0][2]*v3.z;
		rv3.y=m3.element[1][0]*v3.x+m3.element[1][1]*v3.y+m3.element[1][2]*v3.z;
		rv3.z=m3.element[2][0]*v3.x+m3.element[2][1]*v3.y+m3.element[2][2]*v3.z;
		return rv3;
	}
	Matrix3 Tools::Variance(Mesh *mesh,int vertex){
	  int iNeighb=0;Vector3 average,temp;
	  while(mesh->neighbourhood[vertex][iNeighb]!=-1){
		  temp=vector.AddVector3(temp,mesh->verts[mesh->neighbourhood[vertex][iNeighb++]]);
	  }
	  temp=vector.AddVector3(temp,mesh->verts[vertex]);
	  average=vector.Scale(temp,1.0/(iNeighb+1));
	  Vector3 vector1,vector2;
	  Matrix3 matrix3;
	  iNeighb=0;temp.x=temp.y=temp.z=0;
	  while(mesh->neighbourhood[vertex][iNeighb]!=-1){
	    vector1=vector.SubVector3(mesh->verts[mesh->neighbourhood[vertex][iNeighb]],average);
		vector2=vector1;
		matrix3=mat.AddMatrix3(matrix3,vector.V3MV3(vector1,vector2));
		iNeighb++;
	  }
	  vector1=vector.SubVector3(mesh->verts[vertex],average);vector2=vector1;
	  matrix3=mat.AddMatrix3(matrix3,vector.V3MV3(vector1,vector2));
	  matrix3=mat.Mat3Div(matrix3,iNeighb+1);
	  return matrix3;
	}
	float Tools::FindND(Mesh *mesh1,Mesh *mesh2,int ivertex,int *matchi){
		long int i;float min=MBIG;float distance;
		for(i=0;i<mesh2->nverts;i++){
			distance=vector.Distance(mesh1->verts[ivertex],mesh2->verts[i]);
			if(min>distance){
				min=distance;
				*matchi=i;
			}
		}
		return min;
	}

	Vector3 Attack::Rotate(Vector3 v,float a,float b,float r,float dx,float dy,float dz){
		Vector4 inv4(v);Matrix4 RotMat(a,b,r,dx,dy,dz);
		Vector4 outv4=tools.Mat4MulV4(RotMat,inv4);
		Vector3 outv3(outv4);
		return outv3;
	}
	Mesh *Attack::Cut(Mesh *mesh){
		float CutRate=0;//insection rate
	    printf("please input the cut rate:");scanf("%f",&CutRate);
		char axis;
again1:	printf("\nplease input the axis the model is to be cut along(x,y,z) or according to order(o):");scanf("%s",&axis);
		printf("\nCutting the model,please wait\n");
		int nverts=mesh->nverts;Vector3 *verts=mesh->verts;int VertsCut=nverts;
		int i;
 		int n=int(nverts*CutRate);//compute the vertices number to be cut
		float bbox[2][3] = { { 1.0E30F, 1.0E30F, 1.0E30F }, { -1.0E30F, -1.0E30F, -1.0E30F } };
		for (i = 0; i < nverts; i++) {//compute the bounding box
			Vector3& vert = verts[i];
			if (vert.x < bbox[0][0]) bbox[0][0] = vert.x;
			else if (vert.x > bbox[1][0]) bbox[1][0] = vert.x;
			if (vert.y < bbox[0][1]) bbox[0][1] = vert.y;
			else if (vert.y > bbox[1][1]) bbox[1][1] = vert.y;
			if (vert.z < bbox[0][2]) bbox[0][2] = vert.z;
			else if (vert.z > bbox[1][2]) bbox[1][2] = vert.z;
		}

		float ratio=0;float step;long unsigned int nstep=0;
		float bound;
		switch(axis) {//find the bound and the actual vertices cut number:VertsCut
		case 'x':
			step=(bbox[1][0]-bbox[0][0])/(3*nverts);//resolution
			while (VertsCut>n) {
				VertsCut=0;
				bound=bbox[0][0]+nstep++*step;
				for (i=0;i<nverts;i++){
					if(verts[i].x>bound) VertsCut++;
				}
			}
			break;
		case 'y':			
			step=(bbox[1][1]-bbox[0][1])/(3*nverts);//resolution
			while (VertsCut>n) {
				VertsCut=0;
				bound=bbox[0][1]+nstep++*step;
				for (i=0;i<nverts;i++){
					if(verts[i].y>bound) VertsCut++;
				}
			}
			break;
		case 'z':
			step=(bbox[1][2]-bbox[0][2])/(3*nverts);//resolution
			while (VertsCut>n) {
				VertsCut=0;
				bound=bbox[0][2]+nstep++*step;
				for (i=0;i<nverts;i++){
					if(verts[i].z>bound) VertsCut++;
				}
			}
			break;
		case 'o':
			VertsCut=n;
			break;
		default:
			printf("axis input error\n");goto again1;
		}

		int *indexcut=new int[VertsCut];//restore the indexes cut
		switch(axis) {
		case 'x':
			bound=bbox[0][0]+(nstep-1)*step;
			VertsCut=0;
			for (i=0;i<nverts;i++){
				if(verts[i].x>bound) indexcut[VertsCut++]=i;
			}
			break;
		case 'y':
			bound=bbox[0][1]+(nstep-1)*step;
			VertsCut=0;
			for (i=0;i<nverts;i++){
				if(verts[i].y>bound) indexcut[VertsCut++]=i;
			}
			break;
		case 'z':
			bound=bbox[0][2]+(nstep-1)*step;
			VertsCut=0;
			for (i=0;i<nverts;i++){
				if(verts[i].z>bound) indexcut[VertsCut++]=i;
			}
			break;
		case 'o':
			for(i=0;i<VertsCut;i++){
				indexcut[i]=nverts-VertsCut+i;
			}
			break;
		default:printf("this is impossible!");
		}


		
		int displacement=0;//vertices cut indexes displacement
			for (i=0;i<VertsCut;i++){
				tools.DeleteVertex(mesh,indexcut[i]-displacement++);
			}
		printf("%d vertices have been cut from model,%2.2f%s\n",VertsCut,(float)VertsCut/nverts*100,"%");//inform the cut number
		delete []indexcut;
		return mesh;
	}


	Mesh *Attack::AddPulseNoise(Mesh *mesh,float AlphaNoise){//add pulse noise
		printf("Adding noise....please wait\n");
		Mesh *tempmesh=new Mesh(mesh);
	    srand((unsigned)time(NULL));
		Vector3 temp;float Noise;
		for (int i=0;i<mesh->nverts;i++){
			Noise=rand();
			if (Noise>=16383.5) Noise=AlphaNoise;
			else Noise =-AlphaNoise;
			temp=vector.SubVector3(mesh->verts[i],mesh->centriod);
			temp=vector.Scale(temp,Noise);
			tempmesh->verts[i]=vector.AddVector3(mesh->verts[i],temp);
		}
		return tempmesh;
	};
	Mesh *Attack::AddNoise(Mesh *mesh,float *noise,float alpha){
		printf("adding gaussian noise.....\n");
		Mesh *tempmesh=new Mesh(mesh);
		int i;float max=0;Vector3 temp;
		for(i=0;i<mesh->nverts;i++){
			temp=vector.SubVector3(mesh->verts[i],mesh->centriod);
			float t=vector.Magnitude(temp);
			if(max<t)
				max=t;
		}
		for(i=0;i<mesh->nverts;i++){
			noise[i]*=max*alpha;
		    //printf("noise[%3d]=%f\n",i,noise[i]);
			temp=vector.SubVector3(mesh->verts[i],mesh->centriod);
			temp=vector.Normalize(temp);
			temp=vector.Scale(temp,noise[i]);
			tempmesh->verts[i]=vector.AddVector3(mesh->verts[i],temp);
		}
		return tempmesh;
	}
	Mesh *Attack::ChangeOrder(Mesh *mesh,int RotateNum){
		printf("Rotating....please wait\n");
		Mesh *tempmesh=new Mesh(mesh);
		RotateNum=RotateNum%mesh->nverts;
		for(int i=0;i<mesh->nverts;i++){
			tempmesh->verts[i]=mesh->verts[(i+RotateNum+mesh->nverts)%mesh->nverts];
		}
		for(i=0;i<mesh->nfaces;i++){
			for(int j=0;j<mesh->faces[i].nverts;j++){
				tempmesh->faces[i].verts[j]=(mesh->faces[i].verts[j]-RotateNum+mesh->nverts)%mesh->nverts;
			}
		}
		return tempmesh;
	}
	Mesh *Attack::ChangeView(Mesh *mesh,Mesh *tempmesh,float a,float b,float r,float dx,float dy,float dz){
		//printf("%f %f %f %f %f %f \n",a*RTOD,b*RTOD,r*RTOD,dx,dy,dz);
		for(int i=0;i<mesh->nverts;i++){
			tempmesh->verts[i]=attack.Rotate(mesh->verts[i],a,b,r,dx,dy,dz);
		}
		return tempmesh;
	}
	Mesh *Attack::Disturb(Mesh *mesh){
		printf("disturbing....please wait\n");
		Mesh *tempmesh=new Mesh(mesh);
		srand((unsigned)time(NULL));
		for(int i=0;i<tempmesh->nverts;i++){
			int RotateNum=rand()%tempmesh->nverts;
			Vector3 tempvector;
			tempvector=tempmesh->verts[i];
			tempmesh->verts[i]=tempmesh->verts[(i+RotateNum+tempmesh->nverts)%tempmesh->nverts];
			tempmesh->verts[(i+RotateNum+tempmesh->nverts)%tempmesh->nverts]=tempvector;
			for(int j=0;j<tempmesh->nfaces;j++){
				for(int k=0;k<tempmesh->faces[j].nverts;k++){
					if (tempmesh->faces[j].verts[k]==i){
						tempmesh->faces[j].verts[k]=(tempmesh->faces[j].verts[k]+RotateNum+tempmesh->nverts)%tempmesh->nverts;
					}
					else if (tempmesh->faces[j].verts[k]==((i+RotateNum)%tempmesh->nverts)){
						tempmesh->faces[j].verts[k]=(tempmesh->faces[j].verts[k]-RotateNum+tempmesh->nverts)%tempmesh->nverts;
					}
				}
			}
		}
		return tempmesh;
	}
	Mesh *Attack::Move(Mesh *mesh,Vector3 dCentriod){
		printf("moving whole model....please wait\n");
		Mesh *tempmesh=new Mesh(mesh);
		for(int i=0;i<mesh->nverts;i++){
			tempmesh->verts[i]=vector.AddVector3(mesh->verts[i],dCentriod);
		}
		tempmesh->centriod=tools.mean(tempmesh->verts,tempmesh->nverts);
		return tempmesh;
	}
	Mesh *Attack::Scale(Mesh *mesh,float scale){
		printf("scaling whole model....please wait\n");
		Mesh *tempmesh=new Mesh(mesh);
		for(int i=0;i<mesh->nverts;i++){
			Vector3 temp=vector.SubVector3(mesh->verts[i],mesh->centriod);
			temp=vector.Scale(temp,scale);
			tempmesh->verts[i]=vector.AddVector3(mesh->centriod,temp);
		}
		tempmesh->centriod=tools.mean(tempmesh->verts,tempmesh->nverts);
		return tempmesh;
	}
	Mesh *Attack::DownSample1(Mesh *mesh,float prop){/*downsample mesh2*/
		printf("downsampling.....please wait\n");
		Mesh *tempmesh=new Mesh(mesh);
		int i,j,cutvertex;
		int orignnum=tempmesh->nverts;
		srand((unsigned)time(NULL));
		for (i=0;i<orignnum*prop;i++){
			//tools.DeleteVertex(tempmesh,rand()%tempmesh->nverts);//cut the vertex
			cutvertex=rand()%tempmesh->nverts;
			if(cutvertex!=tempmesh->nverts-1){
				for (j=cutvertex;j<tempmesh->nverts-1;j++){
					tempmesh->verts[j]=tempmesh->verts[j+1];
				}
			}
			tempmesh->nverts--;
		}
		return tempmesh;
	}
	Mesh *Attack::DownSample(Mesh *mesh,int num){/*downsample mesh2*/
		printf("downsampling.....please wait\n");
		Mesh *tempmesh=new Mesh(mesh);
		int i,j,k1,t1,t2;
		int iNeighb=0;//neighbourhood index
		for(i=0;i<tempmesh->nverts;i++)	tempmesh->VertexExcluded[i]=FALSE;//all vertices can be cut
		int countvert=0;//vertices cut number
		int countface=0;//faces cut number
		for (i=0;i<tempmesh->nverts;i++){
			if((!tempmesh->VertexExcluded[i])&&(countvert<num)){//if the vertex can be cut
				printf("%d\t",i);
				countface=0;//neighbourhood face number of i
				for (t1=0;t1<tempmesh->nfaces;t1++){
					for(t2=0;t2<tempmesh->faces[t1].nverts;t2++){
						if (i==tempmesh->faces[t1].verts[t2])
							countface++;
					}
				}
				static int (*a)[2];//neighbourhood face vertices of i
				a=new int[countface][2];
				tools.NeighbFaces(tempmesh,i,a,&countface);//compute neighbourhood face vertices of i
				iNeighb=0;
				while(tempmesh->neighbourhood[i][iNeighb]!=-1) 
					tempmesh->VertexExcluded[tempmesh->neighbourhood[i][iNeighb++]]=TRUE;//neighbourhoods should not be cut
				for(j=0;j<tempmesh->nfaces;j++){//when the vertex is cut,faces containing it should be cut
					for(k1=0;k1<tempmesh->faces[j].nverts;k1++){
						if(i==tempmesh->faces[j].verts[k1]) {
							k1=tempmesh->faces[j].nverts;
							tools.DeleteFace(tempmesh,j--);
						}
					}
				}
				tools.AppendFaces(tempmesh,i-countvert,a,countface);//append faces
				delete []a;
				tools.DeleteVertex(tempmesh,i-countvert++);//cut the vertex
			}
		}
		tools.DeleteOverlapFaces(tempmesh);
		//tools.DeleteAbnormal(tempmesh);
		/*printf("\n");
		for(i=0;i<tempmesh->nverts;i++){
			  iNeighb=0;
			  printf("%s %d %s","Neighbourhoods of Vertex",i,"is:");
			  while(tempmesh->neighbourhood[i][iNeighb]!=-1) printf(" %d",tempmesh->neighbourhood[i][iNeighb++]);
			  printf("\n");	
		}*/
		printf("\n%d vertices cut\n",countvert);
		return tempmesh;
	}

Mesh *Recover::registration(Mesh *mesh1,Mesh *mesh2,Mesh *mesh3){/*registration GA*/
		  int i;
		  if((genotype.galog = fopen("galog.txt","w"))==NULL) exit(1);
			
		  genotype.initialize();
		  genotype.evaluate(mesh1,mesh2,mesh3);

		  while(genotype.Generation < MAXGENS)
			{
			  genotype.Generation++;
			  genotype.NSurvivors = 1; /* The best member always survives! */
			  genotype.select();
			  genotype.crossover();
			  genotype.mutate();
			  genotype.evaluate(mesh1,mesh2,mesh3);
			  genotype.report();
			}
		  fprintf(genotype.galog,"\n\nSimulation completed\n");
		  fprintf(genotype.galog,"\n  Best member :\n");

		  /* Print out the best member of the population */
		  for(i=0;i<NVARS;i++)
			{
			  fprintf(genotype.galog,"\n  Var(%d) = %3.3f",i,Population[POPSIZE].Gene[i]);
			}
		  fclose(genotype.galog);
	return mesh3;
}
Mesh *Recover::resort(Mesh *mesh1,Mesh *mesh2){//mesh1 is orignal,mesh2 is disturbed
		printf("resorting....please wait\n");
		Mesh *tempmesh=new Mesh(mesh2);
		int i,j,k1,k2;
		/*reshape mesh2 according to mesh1*/
		Vector3 dCentriod=vector.SubVector3(tempmesh->centriod,mesh1->centriod);
		float SizeMesh1(0),SizeMesh2(0);
		for(i=0;i<tempmesh->nverts;i++){
			SizeMesh1+=vector.Distance(mesh1->verts[i],mesh1->centriod);
			SizeMesh2+=vector.Distance(tempmesh->verts[i],tempmesh->centriod);
			tempmesh->verts[i]=vector.SubVector3(tempmesh->verts[i],dCentriod);
		}
		tempmesh->centriod=tools.mean(tempmesh->verts,tempmesh->nverts);
		SizeMesh1/=mesh1->nverts;SizeMesh2/=tempmesh->nverts;
		for(i=0;i<tempmesh->nverts;i++){
			Vector3 temp=vector.SubVector3(tempmesh->verts[i],tempmesh->centriod);
			temp=vector.Scale(temp,(float)SizeMesh1/SizeMesh2);
			tempmesh->verts[i]=vector.AddVector3(tempmesh->centriod,temp);
		}

		/*resort vertices of mesh2*/
	    bool *VertexUsed=new bool[mesh1->nverts];assert(VertexUsed);//if the match vertex is found,never use it
		for(i=0;i<mesh1->nverts;i++){VertexUsed[i]=FALSE;}
		float alpha1=0.005;float alpha2=alpha1/10;bool bFound=FALSE;int changenum=0;
		for(i=0;i<tempmesh->nverts;i++){
			if(bFound&&changenum) {alpha1-=alpha2*changenum;changenum=0;}
			bFound=FALSE;//if the match vertex is not found,change the finding range
			for(j=0;j<mesh1->nverts;j++){
				if (!VertexUsed[j]){
					float distance=vector.Distance(tempmesh->verts[i],mesh1->verts[j]);
					if(distance<alpha1*mesh1->weight[j]){
						bFound=TRUE;VertexUsed[j]=TRUE;
						tempmesh->verts[j]=tempmesh->verts[i];
						//change the index of each face
						for(k1=0;k1<tempmesh->nfaces;k1++){
							for(k2=0;k2<tempmesh->faces[k1].nverts;k2++){
								if (tempmesh->faces[k1].verts[k2]==i)
									tempmesh->faces[k1].verts[k2]=j;
							}
						}
					}					
				}
			}
			if(!bFound) {alpha1+=alpha2;changenum++;i--;}
		}
		delete []VertexUsed;
		return tempmesh;
}
Mesh *Recover::resample(Mesh *mesh1,Mesh *mesh2,float alpha){
	printf("resampling....please wait\n");
	Mesh *mesh=new Mesh(mesh1);
	int i,matchi;
	for(i=0;i<mesh->nverts;i++){
		float distance=tools.FindND(mesh1,mesh2,i,&matchi);
		float threshold2=mesh1->weight[i]*1.5;
		float threshold1=mesh1->weight[i]*0.5;
		if(distance<threshold2&&distance>threshold2)
			mesh->verts[i]=mesh2->verts[matchi];
	}
	return mesh; 
}


void Matrix::nrerror(char error_text[]) { 
		 fprintf(stderr,"Numerical Recipes Run-Time Error:\n"); 
		 fprintf(stderr,"%s\n",error_text); 
		 fprintf(stderr,"Now Exiting to system\n"); 
		 exit(1); 
		} 

double *Matrix::vectorm(int nl,int nh) { 
		 double *v; 
  
		 v = (double *) malloc((unsigned) (nh-nl+1) * sizeof(double)); 
		 if (!v) nrerror("allocation failure in vectorm()"); 
		 return v-nl; 
		} 

double **Matrix::matrix(int nrl,int nrh,int ncl,int nch) { 
		 int i; 
		 double **m; 

		 m = (double **) malloc((unsigned) (nrh-nrl+1) * sizeof(double*)); 
		 if (!m) nrerror("row allocation failure in matrix(r,c)"); 
		 m -= nrl; 
		 for (i=nrl;i<=nrh;i++) 
			{ 
			 m[i] = (double *) malloc((unsigned) (nch-ncl+1)*sizeof(double)); 
			 if (!m[i]) nrerror("column allocation failure in matrix(r,c)"); 
			 m[i] -= ncl; 
			} 
		 return m; 
		} 

void Matrix::free_vector(double *v,int nl,int nh){ 
		 free((char *) (v+nl)); 
		} 

void Matrix::free_matrix(double **m,int nrl,int nrh,int ncl,int nch){ 
		 int i; 

		 for (i=nrh;i>=nrl;i--) free((char *) (m[i] + ncl)); 
		 free((char *) (m + nrl)); 
		} 
void Matrix::inverse(double **mat, int dim) { 
	 int i,j,*indx; 
	 double **y,d,*col; 

	 y = matrix(0,dim-1,0,dim-1); 
	 indx = (int *)malloc((unsigned)(dim*sizeof(int))); 
	 col = vectorm(0,dim-1); 
	 ludcmp(mat,dim,indx,&d); 
	 for (j=0;j<dim;j++) 
		{ 
		 for (i=0;i<dim;i++) col[i] = 0.0; 
		 col[j] = 1.0; 
		 lubksb(mat,dim,indx,col); 
		 for (i=0;i<dim;i++) y[i][j] = col[i]; 
		} 
	 for (i=0;i<dim;i++) 
		for (j=0;j<dim;j++) 
		   mat[i][j] = y[i][j]; 
	 free_matrix(y,0,dim-1,0,dim-1); 
	 free_vector(col,0,dim-1); 
	 free(indx); 
	} 

void Matrix::ludcmp(double **a, int n, int *indx, double *d) { 
		 int i,imax,j,k; 
		 double   big,dum,sum,temp; 
		 double   *vv; 

		 vv = (double*)malloc((unsigned)(n*sizeof(double))); 
		 if (!vv)  
		   { 
			fprintf(stderr,"Error Allocating Vector Memory\n"); 
			exit(1); 
		   } 
		 *d = 1.0; 
		 for (i=0;i<n;i++) 
			{ 
			 big = 0.0; 
			 for (j=0;j<n;j++) 
			 { 
			  if ((temp=fabs(a[i][j])) > big) big = temp; 
			 } 
			 if (big == 0.0) 
			   { 
				fprintf(stderr,"Singular Matrix in Routine LUDCMP\n"); 
			 for (j=0;j<n;j++) printf(" %f ",a[i][j]); printf("/n"); 
			 exit(1); 
			   } 
			 vv[i] = 1.0/big; 
			} 
		 for (j=0;j<n;j++) 
			{ 
			 for (i=0;i<j;i++) 
			 { 
			  sum = a[i][j]; 
			  for (k=0;k<i;k++) sum -= a[i][k] * a[k][j]; 
			  a[i][j] = sum; 
			 } 
			 big = 0.0; 
			 for (i=j;i<n;i++) 
				{ 
			  sum = a[i][j]; 
			  for (k=0;k<j;k++) sum -= a[i][k] * a[k][j]; 
			  a[i][j] = sum; 
			  if ((dum=vv[i]*fabs(sum)) >= big) 
				{ 
				 big = dum; 
				 imax = i; 
				} 
			 } 
			 if (j != imax) 
			   { 
			 for (k=0;k<n;k++) 
				{ 
				 dum = a[imax][k]; 
				 a[imax][k] = a[j][k]; 
				 a[j][k] = dum; 
				} 
				*d = -(*d); 
			 vv[imax] = vv[j]; 
			   } 
			 indx[j] = imax; 
			 if (a[j][j] == 0.0) a[j][j] = TINY; 
			 if (j != n-1) 
			   { 
			 dum = 1.0 / a[j][j]; 
			 for (i=j+1;i<n;i++) a[i][j] *= dum; 
			   } 
			} 
		 free(vv); 
		} 

void Matrix::lubksb(double **a, int n, int *indx, double *b) { 
		 int i,ip,j,ii=-1; 
		 double   sum; 

		 for (i=0;i<n;i++) 
			{ 
			 ip = indx[i]; 
			 sum = b[ip]; 
			 b[ip] = b[i]; 
			 if (ii>=0) 
			   for (j=ii;j<i;j++) sum -= a[i][j] * b[j]; 
			 else if (sum) ii = i; 
			 b[i] = sum; 
			} 
		 for (i=n-1;i>=0;i--) 
			{ 
			 sum = b[i]; 
			 for (j=i+1;j<n;j++) sum -= a[i][j] * b[j]; 
			 b[i] = sum / a[i][i]; 
			} 
		} 
void Matrix::print(double **m,int nrl,int nrh,int ncl,int nch){
		for(int i=nrl;i<nrh;i++){
			for(int j=ncl;j<nch;j++){
				printf("%4.4e\t",m[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
Matrix3 Matrix::AddMatrix3(Matrix3 &M1,Matrix3 &M2){
	Matrix3 matrix3;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			matrix3.element[i][j]=M1.element[i][j]+M2.element[i][j];
		}
	}
		return matrix3;
	}
Matrix3 Matrix::Mat3Div(Matrix3 &M,float n){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			M.element[i][j]/=n;
		}
	}
	return M;
}
float Matrix::Mat3lemda(Matrix3 &M){
	Vector3 v;
	v.x=v.y=v.z=1;
	static int iteration=0;
	float lemda,lemda1;
	lemda=ComMat3lemda(M,&v,iteration);
	lemda1=ComMat3lemda(M,&v,iteration);
	if(lemda<0||lemda1<0){
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	}
	while(fabs(lemda-lemda1)>(0.001*fabs(lemda))){
		lemda=lemda1;
		lemda1=ComMat3lemda(M,&v,iteration);
		if (iteration>10000){
			printf("warning:iteration may not be convergent\n");
			return ((fabs(lemda1)<1e-4)?1e-4:lemda1);
		}
	}
	float result=(fabs(lemda1)<1e-4)?1e-4:fabs(lemda1);
	result=result>1e+8?1e+8:result;
	return result;
}
float Matrix::ComMat3lemda(Matrix3 &M,Vector3 *v,int iteration){
	iteration++;
	*v=tools.Mat3MulV3(M,*v);
	float MaxLemda=vector.Max(*v);
	*v=vector.Scale(*v,1.0/MaxLemda);
	return MaxLemda;
}
////////////////////////////////////////////////////////////
// GLOBAL VARIABLES
////////////////////////////////////////////////////////////

// Program arguments

 // generate HIT watermark
 /* int Watermark[126]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
					  1,1,0,0,1,1,0,1,1,1,0,0,1,1,1,1,1,0,\
				      1,1,1,1,1,1,0,1,1,1,0,0,1,1,1,1,1,0,\
				      1,1,1,1,1,1,0,1,1,1,0,0,0,1,1,1,0,0,\
				      1,1,1,1,1,1,0,1,1,1,0,0,0,1,1,1,0,0,\
				      1,1,0,0,1,1,0,1,1,1,0,0,0,1,1,1,0,0,\
				      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};*/


// Mesh variables

static Mesh *mesh1 = new Mesh();
static Mesh *mesh2 = new Mesh();
static Mesh *mesh3 = new Mesh();
static Mesh *mesh4 = new Mesh();
 bool formatright=FALSE;

// GLUT variables 

static int GLUTwindow = 0;
static int GLUTwindow_height = 400;
static int GLUTwindow_width = 450;
static int GLUTmouse[2] = { 0, 0 };
static int GLUTbutton[3] = { 0, 0, 0 };
static int GLUTarrows[4] = { 0, 0, 0, 0 };
static int GLUTmodifiers = 0;



// Display variables

static int scaling = 0;
static int translating = 0;
static int rotating = 0;
static float scale = 1.0;
static float center[3] = { 0.0, 0.0, 0.0 };
static float rotation[3] = { 0.0, 0.0, 0.0 };
static float translation[3] = { 0.0, 0.0, -4.0 };

// for the sampling
float *a_distance;
float *D1_distance;
float *D3_distance;
//.......
int seed;
//a_distance = new float[1024*1024]; //the array for the distance of sampling point;
//assert(a_distance);
// srand((unsigned)time(NULL));
// unsigned int seed=rand();
//unsigned int seed=(unsigned)time(NULL);

////////////////////////////////////////////////////////////////
//for mesh1 . computing the area of the mesh(here we use mesh1 for our feature-computing mesh)
double Face::area(Face &face1, Mesh *mesh)  //mesh1 for computing the feature vector
{
	float a,b,c;
	a=0.0;b=0.0;c=0.0;
	if (face1.nverts == 3)
	{
		a = vector.Distance(mesh->verts[face1.verts[0]],mesh->verts[face1.verts[1]]);
		b = vector.Distance(mesh->verts[face1.verts[1]],mesh->verts[face1.verts[2]]);
		c = vector.Distance(mesh->verts[face1.verts[0]],mesh->verts[face1.verts[2]]);
		float p=0.0;
		p = (a + b + c)/2;
		return sqrt(p*(p-a)*(p-b)*(p-c));
		
	}
	else if (face1.nverts > 3)
	{
		a = vector.Distance(mesh->verts[face1.verts[0]],mesh->verts[face1.verts[1]]);
		b = vector.Distance(mesh->verts[face1.verts[1]],mesh->verts[face1.verts[2]]);
		c = vector.Distance(mesh->verts[face1.verts[0]],mesh->verts[face1.verts[2]]);
		float p=0.0;
		p = (a + b + c)/2;
		if (p>=a && p>=b && p>=c)
		{
			return sqrt(p*(p-a)*(p-b)*(p-c));
		}
	}
	
	else return 0.0;
	
}

////////////////////////////////////////////////////////////
// READ NOISE DATA
////////////////////////////////////////////////////////////
void ReadNoiseData(float *noise,int length,const char *noisefile){
	printf("reading noise data....\n");
	int i;
	int count=0;
  // Open file
  FILE *fpin;
  if (!(fpin = fopen(noisefile, "r"))) {
    fprintf(stderr, "Unable to open file %s\n", noisefile);
	exit(0);
  }
  
  for(i=0;i<10000,count<length;i++){
	  fscanf(fpin,"%f",&(noise[count++]));
  }
  for(i=0;i<length;i++){
	  if(i>10000)
		  noise[i]=noise[i%10000];
  }
}
void LoadWatermark(unsigned char *Watermark,const char *watermarkfile){
  printf("loading watermark data....\n");
  FILE *fpin;int data;
  if (!(fpin = fopen(watermarkfile, "r"))) {
    fprintf(stderr, "Unable to open file %s\n", watermarkfile);
	exit(0);
  }  
  for(int i=0;i<WatermarkLength;i++){
	  fscanf(fpin,"%d",&data);
	  Watermark[i]=data;
  }
}



////////////////////////////////////////////////////////////
// OFF FILE READING CODE
////////////////////////////////////////////////////////////

Mesh *ReadOffFile(const char *filename)
{
  int i;

  // Open file
  FILE *fpin;
  if (!(fpin = fopen(filename, "r"))) {
    fprintf(stderr, "Unable to open file %s\n", filename);
    return 0;
  }
  // Allocate mesh structure
  Mesh *mesh = new Mesh();
  if (!mesh) {
    fprintf(stderr, "Unable to allocate memory for file %s\n", filename);
    fclose(fpin);
    return 0;
  }

  // Read file
  int nverts = 0;
  int nfaces = 0;
  int nedges = 0;
  int line_count = 0;
  char buffer[1024];
  printf("reading vertices and faces of model.....\n");
  while (fgets(buffer, 1023, fpin)) {
    // Increment line counter
    line_count++;

    // Skip white space
    char *bufferp = buffer;
    while (isspace(*bufferp)) bufferp++;

    // Skip blank lines and comments
    if (*bufferp == '#') continue;
    if (*bufferp == '\0') continue;

    // Check section
    if (nverts == 0) {//in the line 1
      // Read header 
		if (strstr(buffer,"OFF")&&(strlen(buffer)==4)) {
			formatright=TRUE;
			continue;
		}
		
		if (!formatright) {
          fprintf(stderr, "The format of the file %s is %s,not of OFF format\n", filename,buffer);
          fclose(fpin);
          return NULL;
        }
        // Read mesh counts
        if ((sscanf(bufferp, "%d%d%d", &nverts, &nfaces, &nedges) != 3) || (nverts == 0)) {
          fprintf(stderr, "Syntax error reading header on line %d in file %s\n", line_count, filename);
          fclose(fpin);
          return NULL;
        }

        // Allocate memory for mesh
        mesh->verts = new Vector3 [nverts];
        assert(mesh->verts);
        mesh->faces = new Face [nfaces];
        assert(mesh->faces);
      }

    else if (mesh->nverts < nverts) {
      // Read vertex coordinates
      Vector3& vert = mesh->verts[mesh->nverts++];  //the array of vert;
	  int i = sscanf(bufferp, "%f%f%f", &(vert.x), &(vert.y), &(vert.z));
      if (i != 3) {
        fprintf(stderr, "Syntax error with vertex coordinates on line %d in file %s\n", line_count, filename);
        fclose(fpin);
        return NULL;
      }
    }
    else if (mesh->nfaces < nfaces) {
      // Get next face
      Face& face = mesh->faces[mesh->nfaces++];

      // Read number of vertices in face 
      bufferp = strtok(bufferp, " \t");
      if (bufferp) face.nverts = atoi(bufferp);
      else {
        fprintf(stderr, "Syntax error with face on line %d in file %s\n", line_count, filename);
        fclose(fpin);
        return NULL;
      }

      // Allocate memory for face vertices
      face.verts = new int[face.nverts];
      assert(face.verts);

      // Read vertex indices for face
      for (i = 0; i < face.nverts; i++) {
        bufferp = strtok(NULL, " \t");
        if (bufferp) face.verts[i] = atoi(bufferp);
        else {
          fprintf(stderr, "Syntax error with face on line %d in file %s\n", line_count, filename);
          fclose(fpin);
          return NULL;
        }
      }
	  //normal lize the vector
      // Compute normal for face
	  tools.FaceNormal(mesh,face);
      // Normalize normal for face
      face.normal=vector.Normalize(face.normal);
    }



    else {
      // Should never get here
      fprintf(stderr, "Found extra text starting at line %d in file %s\n", line_count, filename);
      break;
    }

  }//get buffer end

  // Check whether read all faces
  if (nfaces != mesh->nfaces) 
    fprintf(stderr, "Expected %d faces, but read only %d faces in file %s\n", nfaces, mesh->nfaces, filename);
  // Close file
  fclose(fpin);


  mesh->centriod=tools.mean(mesh->verts,mesh->nverts);    //compute centriod of the mesh
  mesh->magnitude=0;
  mesh->meanscale=0;
  for(i=0;i<mesh->nverts;i++) {
	  float d=vector.Distance(mesh->verts[i],mesh->centriod);
	  if(mesh->magnitude<d) mesh->magnitude=d;
	  mesh->meanscale += d;
  }
  mesh->magnitude/=mesh->nverts;//compute magnitude of the mesh
  mesh->meanscale/=mesh->nverts;//compute the average distance to the centero;
  //我默认已经归一化了mesh,这里归一化函数没有写;
  mesh->area = new double[mesh->nfaces]; // compute the array of the area of the triangle;
  assert(mesh->area);

  for (int n=0;n<mesh->nfaces;n++)
  {
	  mesh->area[n] = 0.0;
  }
  Face & face1 = mesh->faces[0];
  float a= face1.area(face1,mesh);  
  mesh->area[0] = a;
  for (int j=1;j<mesh->nfaces;j++)
  {
	  mesh->area[j] = face.area(mesh->faces[j],mesh) + mesh->area[j-1];
  }
  

/*
  printf("finding neighbourhoods and computing normal of each vertex.....\n");
 //find the neighbourhoods and compute normal of each vertex
  mesh->neighbourhood=new int[mesh->nverts][MaxNeighb];assert(mesh->neighbourhood);
  for (i=0;i<mesh->nverts;i++)
	for(int j=0;j<MaxNeighb;j++)
		mesh->neighbourhood[i][j]=-1;
  mesh->VertexNormal=new Vector3[mesh->nverts];assert(mesh->VertexNormal);
  mesh->weight=new float[mesh->nverts];assert(mesh->weight);  
  mesh->VertexExcluded=new bool[mesh->nverts];assert(mesh->VertexExcluded);
  mesh->weight=new float[mesh->nverts];assert(mesh->weight);
  for(i=0;i<mesh->nverts;i++){mesh->VertexExcluded[i]=FALSE;mesh->weight[i]=0;}
  for (i=0;i<mesh->nverts;i++){
	  int nFace=0;int iNeighb,tempneighb;bool m_bFound=FALSE;
	  for (int j=0;j<mesh->nfaces;j++){
		  for(int k=0;k<mesh->faces[j].nverts;k++){
			  if (i==mesh->faces[j].verts[k]){
				  k=mesh->faces[i].nverts;//end searching
				  //compute normal of each vertex
				  Face& face = mesh->faces[j];
				  mesh->VertexNormal[i]=vector.AddVector3(mesh->VertexNormal[i],\
					vector.Normalize(face.normal));
				  nFace++;
				  //find the neighbourhoods
				  for(int kk=0;kk<mesh->faces[i].nverts;kk++){/*neighbourhood face of vertex i is found*/
/*					m_bFound=FALSE;
					iNeighb=-1;while(mesh->neighbourhood[i][++iNeighb]!=-1){
						if(mesh->neighbourhood[i][iNeighb]==mesh->faces[j].verts[kk])
							m_bFound=TRUE;/*if mesh->faces[j].verts[kk] is found in vertex i's neighbourhood,do nothing*/
/*					}
					if(!m_bFound && i!=mesh->faces[j].verts[kk]) 
					{
						iNeighb=-1;while(mesh->neighbourhood[i][++iNeighb]!=-1);//trace the iNeighb
						mesh->neighbourhood[i][iNeighb]=mesh->faces[j].verts[kk];//append vertex i's neighbourhood
						tempneighb=-1;while(mesh->neighbourhood[mesh->faces[j].verts[kk]][++tempneighb]!=-1);//trace the tempneighb
						mesh->neighbourhood[mesh->faces[j].verts[kk]][tempneighb]=i;//append vertex mesh->faces[j].verts[kk]'s neighbourhood
					}
				  }
			  }
		  }
	  }
	  mesh->VertexNormal[i]=vector.Scale(mesh->VertexNormal[i],1.0/nFace);
	  mesh->VertexNormal[i]=vector.Normalize(mesh->VertexNormal[i]);

  }

*/
  // Return mesh 
  return mesh;
}










////////////////////////////////////////////////////////////
// GLUT USER INTERFACE CODE
////////////////////////////////////////////////////////////

void GLUTRedraw(void)
{
  // Setup viewing transformation
  glLoadIdentity();
  glScalef(scale, scale, scale);
  glTranslatef(translation[0], translation[1], 0.0);

  // Set projection transformation
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (GLfloat) GLUTwindow_width /(GLfloat) GLUTwindow_height, 0.1, 100.0);

  // Set camera transformation
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(translation[0], translation[1], translation[2]);
  glScalef(scale, scale, scale);
  glRotatef(rotation[0], 1.0, 0.0, 0.0);
  glRotatef(rotation[1], 0.0, 1.0, 0.0);
  glRotatef(rotation[2], 0.0, 0.0, 1.0);
  glTranslatef(-center[0], -center[1], -center[2]);

  // Clear window 
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Set lights
  static GLfloat light0_position[] = { 3.0, 4.0, 5.0, 0.0 };
  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
  static GLfloat light1_position[] = { -3.0, -2.0, -3.0, 0.0 };
  glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

  // Set material
  static GLfloat material[] = { 0.9, 0.2, 0.0, 1.0 };
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material); 

  // Draw faces
  for (int i = 0; i < mesh2->nfaces; i++) {
    Face& face = mesh2->faces[i];
    //glBegin(GL_TRIANGLE_FAN);
	glBegin(GL_LINES);
	/*float normal[3]={face.normal.x,face.normal.y,face.normal.z};
	glNormal3fv(normal);*/
    for (int j = 0; j < face.nverts; j++) {
      Vector3 &vert = mesh2->verts[face.verts[j]];
      glVertex3f(vert.x, vert.y, vert.z);
    }
    glEnd();
  }

  // Swap buffers 
  glutSwapBuffers();
}    



void GLUTStop(void)
{
  // Destroy window 
  glutDestroyWindow(GLUTwindow);

  // Exit
  exit(0);
}



void GLUTResize(int w, int h)
{
  // Resize window
  glViewport(0, 0, w, h);

  // Remember window size 
  GLUTwindow_width = w;
  GLUTwindow_height = h;

  // Redraw
  glutPostRedisplay();
}



void GLUTMotion(int x, int y)
{
  // Invert y coordinate
  y = GLUTwindow_height - y;
  
  // Process mouse motion event
  if (rotating) {
    // ChangeOrder model
    rotation[0] += -0.5 * (y - GLUTmouse[1]);
    rotation[2] += 0.5 * (x - GLUTmouse[0]);
  }
  else if (scaling) {
    // Scale window
    scale *= exp(2.0 * (float) (x - GLUTmouse[0]) / (float) GLUTwindow_width);
  }
  else if (translating) {
    // Translate window
    translation[0] += 2.0 * (float) (x - GLUTmouse[0]) / (float) GLUTwindow_width;
    translation[1] += 2.0 * (float) (y - GLUTmouse[1]) / (float) GLUTwindow_height;
  }

  // Remember mouse position 
  GLUTmouse[0] = x;
  GLUTmouse[1] = y;
}



void GLUTMouse(int button, int state, int x, int y)
{
  // Invert y coordinate
  y = GLUTwindow_height - y;
  
  // Process mouse button event
  rotating = (button == GLUT_LEFT_BUTTON);
  scaling = (button == GLUT_MIDDLE_BUTTON);
  translating = (button == GLUT_RIGHT_BUTTON);
  if (rotating || scaling || translating) glutIdleFunc(GLUTRedraw);
  else glutIdleFunc(0);

  // Remember button state 
  int b = (button == GLUT_LEFT_BUTTON) ? 0 : ((button == GLUT_MIDDLE_BUTTON) ? 1 : 2);
  GLUTbutton[b] = (state == GLUT_DOWN) ? 1 : 0;

  // Remember modifiers 
  GLUTmodifiers = glutGetModifiers();

   // Remember mouse position 
  GLUTmouse[0] = x;
  GLUTmouse[1] = y;
}



void GLUTSpecial(int key, int x, int y)
{
  // Invert y coordinate
  y = GLUTwindow_height - y;

  // Process keyboard button event 

  // Remember mouse position 
  GLUTmouse[0] = x;
  GLUTmouse[1] = y;

  // Remember modifiers 
  GLUTmodifiers = glutGetModifiers();

  // Redraw
  glutPostRedisplay();
}



void GLUTKeyboard(unsigned char key, int x, int y)
{
  // Process keyboard button event 
  switch (key) {
  case 'Q':
  case 'q':
    GLUTStop();
    break;

  case 27: // ESCAPE
    GLUTStop();
    break;
  }

  // Remember mouse position 
  GLUTmouse[0] = x;
  GLUTmouse[1] = GLUTwindow_height - y;

  // Remember modifiers 
  GLUTmodifiers = glutGetModifiers();
}


/*
void GLUTInit(int *argc, char **argv)
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

*/
/*
void GLUTMainLoop()
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
  //glutMainLoop();
}
*/



////////////////////////////////////////////////////////////
// PROGRAM ARGUMENT PARSING
////////////////////////////////////////////////////////////

char *ParseArgs(int argc, char **argv,char *filename)
{
  // Innocent until proven guilty
  int print_usage = 0;

  // Parse arguments
  argc--; argv++;
  while (argc > 0) {
    if ((*argv)[0] == '-') {
      if (!strcmp(*argv, "-help")) { print_usage = 1; }
      else { fprintf(stderr, "Invalid program argument: %s", *argv); exit(1); }
      argv++; argc--;
    }
    else {
      if (!filename) filename = *argv;
      else { fprintf(stderr, "Invalid program argument: %s", *argv); exit(1); }
      argv++; argc--;
    }
  }
  if (print_usage)     printf("Usage: offviewer <filename>\n");

  // Check filename
  if (!filename) 
	  return NULL;
  else
      return filename;
}






///////////////////////////////////////////////////////////
// MODIFY DATA
///////////////////////////////////////////////////////////
Mesh *EmbedWatermark0(Mesh *mesh,unsigned char *Watermark,float alpha,int key){//embedding method of literature [33]
	printf("embedding watermark(method 0).....\n");
	int i,j,k;
	unsigned char *Watermark1=new unsigned char[WatermarkLength];
	memcpy(Watermark1,Watermark,WatermarkLength);
	permute.PSEUDO(Watermark1,Watermark,WatermarkColumn,WatermarkColumn,key);
	Vector3 *v=mesh->verts;
	float *weight=mesh->weight;
	Face *f=mesh->faces;
	float mod=MBIG;
	float S,s,a,b,c,d,dis;
	float thr=0.50;
  //compute the weight of each vertex
	for (i=0;i<mesh->nverts;i++){
		weight[i]=MBIG;
		  for (j=0;j<mesh->nfaces;j++){
			  for(k=0;k<f[j].nverts;k++){
				  if (i==f[j].verts[k]) {//compute each weight[i]
					  k=f[i].nverts;//end searching
					  a=vector.Distance(v[f[i].verts[0]],v[f[i].verts[1]]);
					  b=vector.Distance(v[f[i].verts[1]],v[f[i].verts[2]]);
					  c=vector.Distance(v[f[i].verts[2]],v[f[i].verts[0]]);
					  s=(a+b+c)/2;
					  S=sqrt(s*(s-a)*(s-b)*(s-c));
					  if(i==f[j].verts[0]) d=b;
					  else if(i==f[j].verts[1]) d=c;
					  else d=a;
					  dis=2*S/d;
					  mod=vector.V3PlotMul(vector.Normalize(vector.SubVector3(v[i],mesh->centriod)),f[i].normal);
					  mod=fabs(1.0/mod*dis*alpha);
				  }
			  }
			  if(weight[i]>mod)	
				  weight[i]=mod;//find the minimum weight[i]
		  }
		  if(weight[i]>thr){
			weight[i]=thr;
			printf("warning\n");
		  }
		//printf("%s %d %s %f\n","Weight of Vertex",i,"is:",weight[i]);
	}
  // Allocate mesh structure
  Mesh *tempmesh = new Mesh(mesh);
  if (!tempmesh) {
    fprintf(stderr, "Unable to allocate memory to embed watermark\n");
    return 0;
  }
  //definite and initialize variables
  int iBit=0;int ikey=0;int iNeighb=0;Vector3 temp; 
  	v=tempmesh->verts;
	weight=tempmesh->weight;
	f=tempmesh->faces;
  for (i=0;i<tempmesh->nverts;i++){tempmesh->VertexExcluded[i]=FALSE;}
  for (i=0;i<tempmesh->nverts;i++){
	  //embed the watermark with the weight
	  iNeighb=0;
	  ikey=(i+key)%tempmesh->nverts;
	  if(!tempmesh->VertexExcluded[ikey]){
		  temp=vector.Direction(v[ikey],mesh->centriod);
		  temp=vector.Scale(temp,weight[ikey]*(Watermark[iBit++%WatermarkLength]==0?-1:1));
		  v[ikey]=vector.AddVector3(v[ikey],temp);
		  //exclude the neighbourhoods
		  while(tempmesh->neighbourhood[ikey][iNeighb]!=-1) {
			  tempmesh->VertexExcluded[tempmesh->neighbourhood[ikey][iNeighb++]]=TRUE;
		  }
	  }
  }
  tempmesh->centriod=tools.mean(tempmesh->verts,tempmesh->nverts);//recompute the centriod of mesh
  memcpy(Watermark,Watermark1,WatermarkLength);
  printf("watermark energy is:%f\n",tools.SubEnergy(tempmesh,mesh));//display watermark energy
  delete []Watermark1;
//return the watermarked model
  return tempmesh;
}
Mesh *EmbedWatermark1(Mesh *mesh,unsigned char *Watermark,float alpha,int key){
	printf("embedding watermark(method 1).....\n");
	int i=0;
	unsigned char *Watermark1=new unsigned char[WatermarkLength];
	memcpy(Watermark1,Watermark,WatermarkLength);
	permute.PSEUDO(Watermark1,Watermark,WatermarkColumn,WatermarkColumn,key);
	Vector3 *v=mesh->verts;
	float *weight=mesh->weight;
	Face *f=mesh->faces;
  //compute the weight of each vertex
  int iNeighb=0;
	  for(i=0;i<mesh->nverts;i++){
		  iNeighb=0;
		  while(mesh->neighbourhood[i][iNeighb]!=-1){
				weight[i]+=1.0/vector.Distance(v[i],v[mesh->neighbourhood[i][iNeighb++]]);
		  }
	  if(iNeighb==2)
		  weight[i]=1.0/weight[i]*alpha;
	  else
		  weight[i]=1.0/weight[i]*alpha*iNeighb*sin(PI/2-PI/iNeighb);
	//   printf("%f\n",weight[i]);
	  } 
  // Allocate mesh structure
  Mesh *tempmesh = new Mesh(mesh);
  if (!tempmesh) {
    fprintf(stderr, "Unable to allocate memory to embed watermark\n");
    return 0;
  }


  //definite and initialize variables
  int iBit=0;int ikey=0;iNeighb=0;Vector3 temp; 
  v=tempmesh->verts;
  weight=tempmesh->weight;
  f=tempmesh->faces;
  for (i=0;i<tempmesh->nverts;i++){tempmesh->VertexExcluded[i]=FALSE;}
  for (i=0;i<tempmesh->nverts;i++){
	  //embed the watermark with the weight
	  ikey=(i+key)%tempmesh->nverts;iNeighb=0;
	  if(!tempmesh->VertexExcluded[ikey]){
		  temp=vector.Direction(v[ikey],mesh->centriod);
		  temp=tempmesh->VertexNormal[ikey];
		  temp=vector.Scale(temp,weight[ikey]*(Watermark[iBit++%WatermarkLength]==0?-1:1));
		  v[ikey]=vector.AddVector3(v[ikey],temp);
		  //exclude the neighbourhoods
		  while(tempmesh->neighbourhood[ikey][iNeighb]!=-1) {tempmesh->VertexExcluded[tempmesh->neighbourhood[ikey][iNeighb++]]=TRUE;}
	  }
	//printf("%s %d %s %f\n","Weight of Vertex",i,"is:",weight[i]);
  }
    //compute the centriod of mesh
  tempmesh->centriod=tools.mean(tempmesh->verts,tempmesh->nverts);
  memcpy(Watermark,Watermark1,WatermarkLength);
  printf("watermark energy is:%f\n",tools.SubEnergy(tempmesh,mesh));//display watermark energy
  delete []Watermark1;
//return the watermarked model
  return tempmesh;
}
Mesh *EmbedWatermark2(Mesh *mesh,unsigned char *Watermark,float alpha,int key){
	printf("embedding watermark(method 2).....\n");
	int i=0;
	unsigned char *Watermark1=new unsigned char[WatermarkLength];
	memcpy(Watermark1,Watermark,WatermarkLength);
	permute.PSEUDO(Watermark1,Watermark,WatermarkColumn,WatermarkColumn,key);
 	Vector3 *v=mesh->verts;
	float *weight=mesh->weight;
	Face *f=mesh->faces;
	//compute the weight of each vertex
      int iNeighb=0;
	  for(i=0;i<mesh->nverts;i++){
		     Matrix3 m=tools.Variance(mesh,i);
			 float lemda=mat.Mat3lemda(m);
			 //printf("%f\n",lemda);
			 mesh->weight[i]=1.0/lemda*2;

		  int tempiNeighb=0;float D0=0;
		  while(mesh->neighbourhood[i][tempiNeighb]!=-1){
				D0+=1.0/vector.Distance(mesh->verts[i],mesh->verts[mesh->neighbourhood[i][tempiNeighb++]]);
		  }
	  D0=1.0/D0*tempiNeighb*sin(PI/2-PI/tempiNeighb)*5;
	  D0=10;
		  if (mesh->weight[i]>D0){
			//printf("weight %d is %f,larger than D0 %f\n",i,mesh->weight[i],D0);
			mesh->weight[i]=D0;
		  }
			//printf("%f\n",mesh->weight[i]);

	  } 
  // Allocate mesh structure
  Mesh *tempmesh = new Mesh(mesh);
  if (!tempmesh) {
    fprintf(stderr, "Unable to allocate memory to embed watermark\n");
    return 0;
  }
  //definite and initialize variables
  int iBit=0;int ikey=0;iNeighb=0;Vector3 temp; 
  v=tempmesh->verts;
  weight=tempmesh->weight;
  f=tempmesh->faces;
  for (i=0;i<tempmesh->nverts;i++){tempmesh->VertexExcluded[i]=FALSE;}
  for (i=0;i<tempmesh->nverts;i++){
	  //embed the watermark with the weight
	  ikey=(i+key)%tempmesh->nverts;iNeighb=0;
	  if(!ikey){
		  ikey=0;
	  }
	  if(!tempmesh->VertexExcluded[ikey]){
		  temp=vector.Direction(v[ikey],mesh->centriod);
		  temp=tempmesh->VertexNormal[ikey];
		  temp=vector.Scale(temp,weight[ikey]*(Watermark[iBit++%WatermarkLength]==0?-1:1));
		  v[ikey]=vector.AddVector3(v[ikey],temp);
		  //exclude the neighbourhoods
		  while(tempmesh->neighbourhood[ikey][iNeighb]!=-1) {tempmesh->VertexExcluded[tempmesh->neighbourhood[ikey][iNeighb++]]=TRUE;}
	  }
	//printf("%s %d %s %f\n","Weight of Vertex",i,"is:",tempmesh->weight[i]);
  }
    //compute the centriod of mesh
  tempmesh->centriod=tools.mean(tempmesh->verts,tempmesh->nverts);
  memcpy(Watermark,Watermark1,WatermarkLength);
  printf("watermark energy is:%f\n",tools.SubEnergy(tempmesh,mesh));//display watermark energy
  delete []Watermark1;
//return the watermarked model
  return tempmesh;
}
///////////////////////////////////////////////////////////
// MODIFY DATA
///////////////////////////////////////////////////////////
void SaveModified(const char *filename1){
	//open file
	FILE *fpout;
	if (!(fpout = fopen(filename1, "w"))) {
    fprintf(stderr, "Unable to open file %s\n", filename1);
	fclose(fpout);
	exit(1);
	}
	//write header information
	fputs("OFF\n",fpout);
	char temp[20];
	ltoa(mesh2->nverts,temp,10);strcpy(temp+strlen(temp),"\0");strcat(temp," ");fputs(temp,fpout);
	ltoa(mesh2->nfaces,temp,10);strcpy(temp+strlen(temp),"\0");strcat(temp," ");fputs(temp,fpout);
	ltoa(0,temp,10);strcpy(temp+strlen(temp),"\0");strcat(temp,"\n");fputs(temp,fpout);
	//write vertices information
	for (int i=0;i<mesh2->nverts;i++){
		char buffer[1024];strcpy(buffer,"");
		char temp[20];strcpy(temp,"");
		gcvt(mesh2->verts[i].x,10,temp);strcat(buffer,temp);strcat(buffer," ");
		gcvt(mesh2->verts[i].y,10,temp);strcat(buffer,temp);strcat(buffer," ");
		gcvt(mesh2->verts[i].z,10,temp);strcat(buffer,temp);strcat(buffer,"\n");
		fputs(buffer,fpout);
	}
	//write topology information
	for (i=0;i<mesh2->nfaces;i++){
		char buffer[1024];strcpy(buffer,"");
		char temp[20];strcpy(temp,"");
		ltoa(mesh2->faces[i].nverts,temp,10);strcpy(temp+strlen(temp),"\0");strcat(buffer,temp);strcat(buffer," ");
		int nv=0;
		while (nv!=mesh2->faces[i].nverts) {
			ltoa(mesh2->faces[i].verts[nv++],temp,10);strcpy(temp+strlen(temp),"\0");strcat(buffer,temp);
			if (nv==mesh2->faces[i].nverts) 
				strcat(buffer,"\n");
			else strcat(buffer," ");
		}
		fputs(buffer,fpout);
	}
	//close file
	fclose(fpout);
}
/*permute watermark series*/
void Permute::PSEUDO(unsigned char *origwmdata,unsigned char *pmwmdata,int N1,int N2,int seed)
{
	int number=N1*N2;
	memcpy(pmwmdata,origwmdata,number);
  int bit[18];
  int i,j,scale,temp;
  int tempkey;
  int sequence[4096];
  if (number<4||number>(65536*2)) return;

    //取得m序列的阶数
	scale=0;//scale级反馈移位寄存器--用于产生长为2^scale-1的m序列     
    temp=number;
    while(temp!=1)//求阶数
	{    
	  temp=temp/2;
      scale=scale+1; 
	}
	
   tempkey=seed;//置随机序列的种子

   for (i=0;i<4095;i++) //周期为64*64,产生4095个伪随机值（种子给定）
	{
      for(j=0;j<scale;j++) //取各位0/1值-->bit[i]
	  {
        temp=tempkey>>j;
	    bit[j]=temp&1;
	  }
	  switch(scale)//作模2加法
	  {
	    case 2:
		  temp=bit[0]+bit[1];
		break;
		case 3:
          temp=bit[0]+bit[2];
		break;
		case 4:
		  temp=bit[0]+bit[3];
		break;
		case 5:
		  temp=bit[0]+bit[3];
		break;
		case 6:
		  temp=bit[0]+bit[5];
		break;
		case 7:
		  temp=bit[0]+bit[4];
		break;
		case 8:
		  temp=bit[0]+bit[4]+bit[5]+bit[6];
		break;
		case 9:
		  temp=bit[0]+bit[5];
		break;
		case 10:
		  temp=bit[0]+bit[7];
		break;
		case 11:
		  temp=bit[0]+bit[9];
		break;
		case 12:
		  temp=bit[0]+bit[6]+bit[8]+bit[11];
		break;
		case 13:
		  temp=bit[0]+bit[9]+bit[10]+bit[12];
		break;
		case 14:
          temp=bit[0]+bit[4]+bit[8]+bit[13];
	    break;
		case 15:
		  temp=bit[0]+bit[14];
		break;
		case 16:
		  temp=bit[0]+bit[4]+bit[13]+bit[15];
		break;
		case 17:
		  temp=bit[0]+bit[14];
		break;
		default:
		break;
	  }
	  bit[scale]=temp&1;
      tempkey=(int)(bit[scale]*(pow(2,(scale-1)))+(tempkey>>1));
	  sequence[i]=tempkey;

  }
     sequence[4095]=0;
	for(i=0;i<N1*N2;i++)
	{
		j=sequence[i];
		pmwmdata[j]=origwmdata[i];
	}
}
/*diverse permute watermark series*/
void Permute::DPSEUDO(unsigned char *pmwmdata,unsigned char *rewmdata,int N1,int N2,int seed)
{
  int number=N1*N2;
  int bit[18];
  int i,j,scale,temp;
  int tempkey;
  int sequence[4096];
  if (number<4||number>(65536*2)) return;

    //取得m序列的阶数
	scale=0;//scale级反馈移位寄存器--用于产生长为2^scale-1的m序列     
    temp=number;
    while(temp!=1)//求阶数
	{    
	  temp=temp/2;
      scale=scale+1; 
	}
	
   tempkey=seed;//置随机序列的种子

   for (i=0;i<4095;i++) //周期为64*64,产生4095个伪随机值（种子给定）
	{
      for(j=0;j<scale;j++) //取各位0/1值-->bit[i]
	  {
        temp=tempkey>>j;
	    bit[j]=temp&1;
	  }
	  switch(scale)//作模2加法
	  {
	    case 2:
		  temp=bit[0]+bit[1];
		break;
		case 3:
          temp=bit[0]+bit[2];
		break;
		case 4:
		  temp=bit[0]+bit[3];
		break;
		case 5:
		  temp=bit[0]+bit[3];
		break;
		case 6:
		  temp=bit[0]+bit[5];
		break;
		case 7:
		  temp=bit[0]+bit[4];
		break;
		case 8:
		  temp=bit[0]+bit[4]+bit[5]+bit[6];
		break;
		case 9:
		  temp=bit[0]+bit[5];
		break;
		case 10:
		  temp=bit[0]+bit[7];
		break;
		case 11:
		  temp=bit[0]+bit[9];
		break;
		case 12:
		  temp=bit[0]+bit[6]+bit[8]+bit[11];
		break;
		case 13:
		  temp=bit[0]+bit[9]+bit[10]+bit[12];
		break;
		case 14:
          temp=bit[0]+bit[4]+bit[8]+bit[13];
	    break;
		case 15:
		  temp=bit[0]+bit[14];
		break;
		case 16:
		  temp=bit[0]+bit[4]+bit[13]+bit[15];
		break;
		case 17:
		  temp=bit[0]+bit[14];
		break;
		default:
		break;
	  }
	  bit[scale]=temp&1;
      tempkey=(int)(bit[scale]*(pow(2,(scale-1)))+(tempkey>>1));
	  sequence[i]=tempkey;

  }
     sequence[4095]=0;
	for(i=0;i<N1*N2;i++)
	{
		j=sequence[i];
		rewmdata[i]=pmwmdata[j];
	}
}
////////////////////////////////////////////////////////////
// Attact Watermark
////////////////////////////////////////////////////////////
void AttractWatermark0(Mesh *mesh1,Mesh *mesh2,unsigned char *Watermark,int key,float CutRate){
  printf("attractting watermark <method 0>...\n");
  unsigned char *AttracttedWatermark=new unsigned char[WatermarkLength];
  float *sum=new float[WatermarkLength];assert(sum);
	//make sure that when there is no watermark,NC is approximately zero
	srand((unsigned)time(NULL));
	for (int i=0;i<WatermarkLength;i++)	sum[i]=(float)(rand()-16383.5)/32767*1e-9;
	//attract watermark
	int iBit=0; int iNeighb=0;int ikey=0;Vector3 sub;
	for (i=0;i<mesh2->nverts;i++){mesh2->VertexExcluded[i]=FALSE;}
	for (i=0;i<mesh2->nverts*(1-CutRate);i++) {
	  ikey=(i+key)%mesh2->nverts;
	  if(!mesh2->VertexExcluded[ikey]){
		sub=vector.SubVector3(mesh2->verts[ikey],mesh1->verts[ikey]);
		sum[iBit%WatermarkLength]+=vector.Magnitude(sub)*(vector.V3PlotMul(sub,vector.SubVector3(mesh1->verts[ikey],mesh1->centriod))>0?1:-1);
		  //exclude the neighbourhoods
		  iNeighb=0;
		  while(mesh2->neighbourhood[ikey][iNeighb]!=-1) {
			mesh2->VertexExcluded[mesh2->neighbourhood[ikey][iNeighb++]]=TRUE;
		  }
		  iBit++;
	  }	
	}
	for (i=0;i<WatermarkLength;i++){
		if (sum[i]>=0)
			AttracttedWatermark[i]=1;
		else AttracttedWatermark[i]=0;
	}
	unsigned char *Watermark1=new unsigned char[WatermarkLength];
	memcpy(Watermark1,AttracttedWatermark,WatermarkLength);
	permute.DPSEUDO(Watermark1,AttracttedWatermark,WatermarkColumn,WatermarkColumn,key);
	delete []Watermark1;
	//display orignal watermark and attractted watermark
	int temp=0;
	for (i=0;i<WatermarkLength;i++){
		if((temp++ % WatermarkColumn)==0 && temp!=0) printf("\n"); 
		if (Watermark[i]<0) Watermark[i]=0;
		printf("  %d",Watermark[i]);
	}
	printf("\n");
	for (i=0,temp=0;i<WatermarkLength;i++){
		if((temp++ % WatermarkColumn)==0 && temp!=0) printf("\n"); 
		printf("  %d",AttracttedWatermark[i]);
	}
	printf("\n");
	//display the NC between the watermarks (method 1)
	/*int right=0;int wrong=0;
	for (i=0;i<WatermarkLength;i++){
		printf("%f\t",sum[i]);
		if (Watermark[i]==AttracttedWatermark[i]) right++;
		else wrong++;
	}
	printf("%s : %f\n","NC",(float)(right-wrong)/WatermarkLength);
	delete []sum;*/

	//display the NC between the watermarks (method 2)
	float mean1,mean2,sum1=0,sum2=0,sum3=0;
	for(i=0;i<WatermarkLength;i++){
		sum1+=AttracttedWatermark[i];
		sum2+=Watermark[i];
	}
	mean1=sum1/WatermarkLength;mean2=sum2/=WatermarkLength;
	sum1=sum2=0;
	for(i=0;i<WatermarkLength;i++){
		sum1+=(AttracttedWatermark[i]-mean1)*(Watermark[i]-mean2);
		sum2+=(AttracttedWatermark[i]-mean1)*(AttracttedWatermark[i]-mean1);
		sum3+=(Watermark[i]-mean2)*(Watermark[i]-mean2);
	}
	float NC=sum1/sqrt(sum2*sum3);
	printf("\n%s : %f\n","NC",NC);
	delete []sum;
	delete []AttracttedWatermark;
}
void AttractWatermark(Mesh *mesh1,Mesh *mesh2,unsigned char *Watermark,int key,float CutRate){
  printf("attractting watermark...\n");
  unsigned char *AttracttedWatermark=new unsigned char[WatermarkLength];
  float *sum=new float[WatermarkLength];assert(sum);
	//make sure that when there is no watermark,NC is approximately zero
	srand((unsigned)time(NULL));
	for (int i=0;i<WatermarkLength;i++)	sum[i]=(float)(rand()-16383.5)/32767*1e-9;
	//attract watermark
	int iBit=0; int iNeighb=0;int ikey=0;Vector3 sub;
	for (i=0;i<mesh2->nverts;i++){mesh2->VertexExcluded[i]=FALSE;}
	for (i=0;i<mesh2->nverts*(1-CutRate);i++) {
	  ikey=(i+key)%mesh2->nverts;
	  if(!mesh2->VertexExcluded[ikey]){
		sub=vector.SubVector3(mesh2->verts[ikey],mesh1->verts[ikey]);
		sum[iBit%WatermarkLength]+=vector.Magnitude(sub)*(vector.V3PlotMul(sub,mesh1->VertexNormal[ikey])>0?1:-1);
		  //exclude the neighbourhoods
		  iNeighb=0;
		  while(mesh2->neighbourhood[ikey][iNeighb]!=-1) {
			mesh2->VertexExcluded[mesh2->neighbourhood[ikey][iNeighb++]]=TRUE;
		  }
		  iBit++;
	  }	
	}
	for (i=0;i<WatermarkLength;i++){
		if (sum[i]>=0)
			AttracttedWatermark[i]=1;
		else AttracttedWatermark[i]=0;
	}
	unsigned char *Watermark1=new unsigned char[WatermarkLength];
	memcpy(Watermark1,AttracttedWatermark,WatermarkLength);
	permute.DPSEUDO(Watermark1,AttracttedWatermark,WatermarkColumn,WatermarkColumn,key);
	delete []Watermark1;
	//display orignal watermark and attractted watermark
	int temp=0;
	for (i=0;i<WatermarkLength;i++){
		if((temp++ % WatermarkColumn)==0 && temp!=0) printf("\n"); 
		if (Watermark[i]<0) Watermark[i]=0;
		printf("  %d",Watermark[i]);
	}
	printf("\n");
	for (i=0,temp=0;i<WatermarkLength;i++){
		if((temp++ % WatermarkColumn)==0 && temp!=0) printf("\n"); 
		printf("  %d",AttracttedWatermark[i]);
	}
	printf("\n");
	//display the NC between the watermarks (method 1)
	/*int right=0;int wrong=0;
	for (i=0;i<WatermarkLength;i++){
		printf("%f\t",sum[i]);
		if (Watermark[i]==AttracttedWatermark[i]) right++;
		else wrong++;
	}
	printf("%s : %f\n","NC",(float)(right-wrong)/WatermarkLength);
	delete []sum;*/

	//display the NC between the watermarks (method 2)
	float mean1,mean2,sum1=0,sum2=0,sum3=0;
	for(i=0;i<WatermarkLength;i++){
		sum1+=AttracttedWatermark[i];
		sum2+=Watermark[i];
	}
	mean1=sum1/WatermarkLength;mean2=sum2/=WatermarkLength;
	sum1=sum2=0;
	for(i=0;i<WatermarkLength;i++){
		sum1+=(AttracttedWatermark[i]-mean1)*(Watermark[i]-mean2);
		sum2+=(AttracttedWatermark[i]-mean1)*(AttracttedWatermark[i]-mean1);
		sum3+=(Watermark[i]-mean2)*(Watermark[i]-mean2);
	}
	float NC=sum1/sqrt(sum2*sum3);
	printf("\n%s : %f\n","NC",NC);
	delete []sum;
	delete []AttracttedWatermark;
}
// bin search 
int BinarySearch(double area2[],const double &area3,int n)
{
	int a_left=0;
	int a_right=n-1;
	while (a_left<=a_right)
	{
		int middle=(a_left+a_right)/2;
		if (area3<=area2[0])
		{
			return 0;
		}
		if (area3<area2[middle] && area3>area2[middle-1])
		{
			return middle;
		}
		else if (area3>area2[middle])
		{
			a_left = middle+1;
		}
		else a_right = middle-1;
	}
	return -1;
}
void initial()
{
	srand((unsigned)time(NULL));
	unsigned int seed=rand();
}

unsigned int GetSeed()
{	

	seed = (25173*seed+3849)%65536;
	return seed;
}


Vector3 Getrandomvector(Mesh *mesh)
{
	int s_d = GetSeed();
	//srand(s_d); // produce a random frome o to area[mesh->nfaces];

	int random = 0;
	int random1 = 0; 
	int random2 = 0;  //initial

	random1 = rand();
	random = rand();
	random2 = rand();

	double area1,area2;
	area1 = 0.0; area2 = 0.0;
	area1= ((random)/(32768.0));
	area2 = mesh->area[mesh->nfaces-1]*area1;
	int num_face = BinarySearch(mesh->area,area2,mesh->nfaces);
	if (num_face == -1)
	{
		 MessageBox(NULL,"二分查找出错！","Error",MB_OK|MB_ICONSTOP);
	}

	////////////////////////////////// sampling
	//random r1 and r2 for the sampling;

	 float r1 = (float) (random1/ 32768.0);
	 float r2 = (float) (random2 / 32768.0);
	 Vector3 P;
	 Face& face1 = mesh->faces[num_face];
	 Vector3& A= mesh->verts[face1.verts[0]];
	 Vector3& B= mesh->verts[face1.verts[1]];
	 Vector3& C= mesh->verts[face1.verts[2]];
	 
	 P.x=(1-sqrt(r1))*A.x + sqrt(r1)*(1-r2)*B.x + sqrt(r1)*r2*C.x;
	 P.y=(1-sqrt(r1))*A.y + sqrt(r1)*(1-r2)*B.y + sqrt(r1)*r2*C.y;
	 P.z=(1-sqrt(r1))*A.z + sqrt(r1)*(1-r2)*B.z + sqrt(r1)*r2*C.z;

	return P; // ruturn the victor;
}

float Sampling(Mesh *mesh) // N=1024*1024 and return the max distance of the samplings;
{
	Vector3 P1,P2;
	float max_magnitude=0.0; // the largest distance between the sampling point;
	initial();


	a_distance = new float[1024*1024]; //the array for the distance of sampling point;
	assert(a_distance);
	for (int j=0;j<1024*1024;j++)
	{
		a_distance[j] = 0.0;
	}

	for (int i=0;i<1024*1024;i++)
	{
		P1 = Getrandomvector(mesh);
		P2 = Getrandomvector(mesh);
		a_distance[i] = vector.Distance(P1,P2);
		if (max_magnitude<a_distance[i])
		{
			max_magnitude = a_distance[i];
		}
	}
//	delete[]mesh->area;  // area is useless in the after computing
 return max_magnitude;
}
void DestroyD2Memery()
{
	delete[]a_distance;

}
void SamplingD1(Mesh *mesh, float &magnitude)
{
	Vector3 P1;
	magnitude = 0.0f;
	D1_distance = new float[1024*1024*5];
	assert(D1_distance);
	for (int i=0;i<1024*1024*5;i++)
	{
		D1_distance[i]=0.0f;
	} //initial the D1 Sampling 

	for (int j=0; j<1024*1024*5;j++)
	{
		P1 = Getrandomvector(mesh);
		D1_distance[j]=vector.Distance(P1,mesh->centriod);
		if (magnitude < D1_distance[j])
		{
			magnitude = D1_distance[j];
		}
	}
}
void SamplingD3(Mesh *mesh, float &magnitude)
{
	Vector3 p1, p2, p3;
	float a, b ,c;
	// initial the variable...
	a = b = c = 0.0f;
	magnitude = 0.0f;
		D3_distance = new float[1024*1024];
	assert(D3_distance);
	for (int i = 0; i<1024*1024; i++)
	{
		D3_distance[i] = 0.0f;
	}
	//Sampling D3;
	for (int j=0; j<1024*1024; j++)
	{
		p1 = Getrandomvector(mesh);
		p2 = Getrandomvector(mesh);
		p3 = Getrandomvector(mesh);

			a = vector.Distance(p1,p2);
			b = vector.Distance(p2,p3);
			c = vector.Distance(p1,p3);
			float p=0.0;
			p = (a + b + c)/2;
			D3_distance[j] = sqrt(p*(p-a)*(p-b)*(p-c));	
	
	}
}
  

////////////////////////////////////////////////////////////
// MAIN
////////////////////////////////////////////////////////////
/*
int main(int argc, char **argv)
{
	/*filename is the orignal,filename1 is the watermarked
	  filename2 is the attacked,filename3 is the recovered*/
	/*
	 char filename[1024]="model\\snake";
	 //char *filename=NULL;filename=ParseArgs(argc,argv,filename);
     char filename1[1024];strcpy(filename1,"");
	 char filename2[1024];strcpy(filename2,"");
	 char filename3[1024];strcpy(filename3,"");
     strcat(filename1,filename);strcat(filename1,"watermarked.off");
	 strcat(filename2,filename);strcat(filename2,"attacked.off");
	 strcat(filename3,filename);strcat(filename3,"recovered.off");
     strcat(filename,".off");
 

  mesh2 = ReadOffFile(filename);//orignal model
 
  float alpha0=0.0450,alpha1=0.2112;

  SaveModified(filename3);

 
  GLUTInit(&argc, argv);
  if(formatright){
	  GLUTMainLoop();  //draw mesh2 
  }

  return 0;
}*/