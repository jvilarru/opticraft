#include "Block.h"

Block::Block(void)
{
}

Block::Block(int initX, int initY, int initZ) {
	Point n;
	Vertex v[NUM_VERT_IN_FACE];
	idX = initX;
	idY = initY;
	idZ = initZ;

	//TOP face
	v[0] = Vertex(initX, initY+1, initZ+1);
	v[1] = Vertex(initX+1, initY+1, initZ+1);
	v[2] = Vertex(initX+1, initY+1, initZ);
	v[3] = Vertex(initX, initY+1, initZ);
	n = Point(0.0, 1.0, 0.0);
	faces[0] = Face(v, n);

	//BOTTOM face
	v[0] = Vertex(initX, initY, initZ+1);
	v[1] = Vertex(initX, initY, initZ);
	v[2] = Vertex(initX+1, initY, initZ);
	v[3] = Vertex(initX+1, initY, initZ+1);
	n = Point(0.0, -1.0, 0.0);
	faces[1] = Face(v, n);

	//FRONT face (actually... it is the BACK face in the scene, but not in our map)
	v[0] = Vertex(initX, initY, initZ+1);
	v[1] = Vertex(initX+1, initY, initZ+1);
	v[2] = Vertex(initX+1, initY+1, initZ+1);
	v[3] = Vertex(initX, initY+1, initZ+1);
	n = Point(0.0, 0.0, 1.0);
	faces[2] = Face(v, n);

	//BACK face
	v[0] = Vertex(initX, initY, initZ);
	v[1] = Vertex(initX, initY+1, initZ);
	v[2] = Vertex(initX+1, initY+1, initZ);
	v[3] = Vertex(initX+1, initY, initZ);
	n = Point(0.0, 0.0, -1.0);
	faces[3] = Face(v, n);

	//LEFT face
	v[0] = Vertex(initX, initY, initZ);
	v[1] = Vertex(initX, initY, initZ+1);
	v[2] = Vertex(initX, initY+1, initZ+1);
	v[3] = Vertex(initX, initY+1, initZ);
	n = Point(-1.0, 0.0, 0.0);
	faces[4] = Face(v, n);

	//RIGHT face
	v[0] = Vertex(initX+1, initY, initZ);
	v[1] = Vertex(initX+1, initY+1, initZ);
	v[2] = Vertex(initX+1, initY+1, initZ+1);
	v[3] = Vertex(initX+1, initY, initZ+1);
	n = Point(+1.0, 0.0, 0.0);
	faces[5] = Face(v, n);
}


Block::~Block(void)
{
}

void Block::getFaces(Face *f) {
	for(int i = 0; i<NUM_FACES_BLOCK; ++i) {
		Vertex v[NUM_VERT_IN_FACE];
		Point n = this->faces[i].getNormal();
		this->faces[i].getVertices(v);
		f[i] = Face(v, n);
	}
}

void Block::setVBOID(GLuint idVert, GLuint idNorm, GLuint idText, GLuint idIndi) {
	this->idVBOvert = idVert;
	this->idVBOnorm = idNorm;
	this->idVBOtext = idText;
	this->idVBOindi = idIndi;
}

GLuint Block::getVBOIDvert() {
	return this->idVBOvert;
}

GLuint Block::getVBOIDnorm() {
	return this->idVBOnorm;
}

GLuint Block::getVBOIDtext() {
	return this->idVBOtext;
}

GLuint Block::getVBOIDindi() {
	return this->idVBOindi;
}
