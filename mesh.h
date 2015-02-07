#ifndef _TRIANGLE_MESH
#define _TRIANGLE_MESH

#include "stdafx.h"
#include "face.h"
#include "myvector.h"

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
	float meanscale;//the average distance from all poi
};



#endif
