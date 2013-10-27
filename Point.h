#pragma once
class Point
{
public:
	Point(void);
	Point(int x, int y, int z);
	~Point(void);

	int getX();
	int getY();
	int getZ();

	void setX(int x);
	void setY(int y);
	void setZ(int z);

	void setPoint(int x, int y, int z);
	int x, y, z;
};

