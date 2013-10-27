#include "Point.h"

Point::Point(void)
{
}

Point::Point(int x, int y, int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}


Point::~Point(void)
{
}

int Point::getX() {
	return x;
}

int Point::getY() {
	return y;
}

int Point::getZ() {
	return z;
}

void Point::setX(int x) {
	this->x = x;
}

void Point::setY(int y) {
	this->y = y;
}

void Point::setZ(int z) {
	this->z = z;
}

void Point::setPoint(int x, int y, int z) {
	this->x = x;
	this->y = y;
	this->z = z;
}
