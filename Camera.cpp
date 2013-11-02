#include "Camera.h"

Camera::Camera(void)
{
}

Camera::Camera(Point eye, Point center, Point up) {
	this->eye = eye;
	this->center = center;
	this->up = up;
	gluPerspective(90, 1, 0, 500);
	gluLookAt(this->eye.x, this->eye.y, this->eye.z, this->center.x, this->center.y, this->center.z, this->up.x, this->up.y, this->up.z);
}

Camera::~Camera(void)
{
}

void Camera::setCamera(Point eye, Point center) {
	this->eye = eye;
	this->center = center;
	gluPerspective(90, 1, 0, RENDER_DISTANCE*BLOCK_SIZE);
	gluLookAt(this->eye.x, this->eye.y, this->eye.z, this->center.x, this->center.y, this->center.z, this->up.x, this->up.y, this->up.z);
}

Point Camera::getCameraEye() {
	return this->eye;
}

Point Camera::getCameraCenter() {
	return this->center;
}

void Camera::updateCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 0, RENDER_DISTANCE*BLOCK_SIZE);
	gluLookAt(this->eye.x, this->eye.y, this->eye.z, this->center.x, this->center.y, this->center.z, this->up.x, this->up.y, this->up.z);
	glMatrixMode(GL_MODELVIEW);
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);
}
