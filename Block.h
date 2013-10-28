#pragma once

#include "Globals.h"
#include "Point.h"
#include "Face.h"

#define NUM_FACES_BLOCK 6

class Block
{
public:
	Block(void);
	Block(int initX, int initY, int initZ);
	~Block(void);

	void getFaces(Face *f);

	void setVBOID(GLuint idVert, GLuint idNorm, GLuint idText, GLuint idIndi);
	GLuint getVBOIDvert();
	GLuint getVBOIDnorm();
	GLuint getVBOIDtext();
	GLuint getVBOIDindi();


private:
	Face faces[NUM_FACES_BLOCK];		//TOP-BOTTOM-FRONT-BACK-LEFT-RIGTH
	int idX;	//identifier in width, it is his lowest (x) at the scene
	int idY;	//identifier in height, it is his lowest (y) at the scene
	int idZ;	//identifier in depth, it is his lowest (z) at the scene
	GLuint idVBOvert;	//identifier for VBO vertices
	GLuint idVBOnorm;	//identifier for VBO normals
	GLuint idVBOtext;	//identifier for VBO textures
	GLuint idVBOindi;	//identifier for VBO indices
};
