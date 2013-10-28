#include "Vertex.h"


Vertex::Vertex(void)
{
}


Vertex::~Vertex(void)
{
}


Vertex::Vertex(int x, int y, int z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

int Vertex::getX() {
	return x;
}

int Vertex::getY() {
	return y;
}

int Vertex::getZ() {
	return z;
}
