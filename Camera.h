#pragma once
#include "Point.h"
#include "Globals.h"

class Camera
{
public:
	Camera(void);
	Camera(Point eye, Point center, Point up);
	~Camera(void);

	void setCamera(Point eye, Point center);
	Point getCameraEye();
	Point getCameraCenter();
	void updateCamera();

private:
	Point eye;
	Point center;
	Point up;
};
