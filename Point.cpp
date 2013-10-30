#include "Point.h"

Point::Point(void) {
	x=y=z=0;
}

Point::Point(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}


Point::~Point(void) {
}