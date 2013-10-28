#pragma once
#include "Point.h"
#include "Vertex.h"

#define NUM_VERT_IN_FACE 4

class Face
{
public:
	Face(void);
	~Face(void);
	Face(Vertex *vertices, Point normal);
	Point getNormal();
	void getVertices(Vertex *vert);

private:
	Vertex vertices[4];	//indices of each vertex
	Point normal;		//face's normal
	int textureID;		//textureID of the block
};

