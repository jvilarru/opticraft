#pragma once

#include "Globals.h"
#include "Point.h"

#define NUM_FACES_BLOCK 6

class Block
{
public:
	Block(void);
	Block(GLuint idVert, GLuint idNorm, GLuint idText, GLuint idIndi);
	~Block(void);

	void setVBOID(GLuint idVert, GLuint idNorm, GLuint idText, GLuint idIndi);
	GLuint getVBOIDvert();
	GLuint getVBOIDnorm();
	GLuint getVBOIDtext();
	GLuint getVBOIDindi();


private:
	GLuint idVBOvert;	//identifier for VBO vertices
	GLuint idVBOnorm;	//identifier for VBO normals
	GLuint idVBOtext;	//identifier for VBO textures
	GLuint idVBOindi;	//identifier for VBO indices
};
