#pragma once
class Point
{
public:
	Point(void);
	Point(float x, float y, float z);
	~Point(void);

	float getX();
	float getY();
	float getZ();

	void setX(float x);
	void setY(float y);
	void setZ(float z);

	void setPoint(float x, float y, float z);

private:
	float x, y, z;
};

