#include "Face.h"

Face::Face(void)
{
}


Face::~Face(void)
{
}

Face::Face(Vertex *vertices, Point normal) {
	this->normal = normal;
	for(int i = 0; i<NUM_VERT_IN_FACE; ++i) {
		this->vertices[i] = Vertex(vertices[i].getX(), vertices[i].getY(), vertices[i].getZ());
	}
}

Point Face::getNormal() {
	return this->normal;
}

void Face::getVertices(Vertex* vert) {
	for(int i = 0; i<NUM_VERT_IN_FACE; ++i) {
		vert[i] = Vertex(this->vertices[i].getX(), this->vertices[i].getY(), this->vertices[i].getZ());
	}
}
