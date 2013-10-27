#include "Globals.h"
#include "Point.h"

#pragma once
class Block
{
public:
	Block(void);
	Block(Point center,char id);
	~Block(void);

	void drawBlock();

private:
	Point center;
	char id;
};

