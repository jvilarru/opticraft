#pragma once
class Vertex
{
public:
	Vertex(void);
	~Vertex(void);
	Vertex(int x, int y, int z);

	int getX();
	int getY();
	int getZ();

private:
	int x;
	int y;
	int z;
};

