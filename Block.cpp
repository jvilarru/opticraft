#include "Block.h"

Block::Block(void)
{
}

Block::Block(GLuint idVert, GLuint idNorm, GLuint idText, GLuint idIndi) {
	this->idVBOvert = idVert;
	this->idVBOnorm = idNorm;
	this->idVBOtext = idText;
	this->idVBOindi = idIndi;
}


Block::~Block(void)
{
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
