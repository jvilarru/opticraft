#include "Camera.h"

Camera::Camera(void)
{
}

Camera::Camera(Point eye, Point center, Point up) {
	this->eye = eye;
	this->center = center;
	this->up = up;
	gluPerspective(90, 1, 0, RENDER_DISTANCE*BLOCK_SIZE);
	gluLookAt(this->eye.getX(), this->eye.getY(), this->eye.getZ(), this->center.getX(), this->center.getY(), this->center.getZ(), this->up.getX(), this->up.getY(), this->up.getZ());
}

Camera::~Camera(void)
{
}

void Camera::setCamera(Point eye, Point center) {
	this->eye = eye;
	this->center = center;
	gluPerspective(90, 1, 0, RENDER_DISTANCE*BLOCK_SIZE);
	gluLookAt(this->eye.getX(), this->eye.getY(), this->eye.getZ(), this->center.getX(), this->center.getY(), this->center.getZ(), this->up.getX(), this->up.getY(), this->up.getZ());
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
	gluLookAt(this->eye.getX(), this->eye.getY(), this->eye.getZ(), this->center.getX(), this->center.getY(), this->center.getZ(), this->up.getX(), this->up.getY(), this->up.getZ());
	glMatrixMode(GL_MODELVIEW);
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);
}
