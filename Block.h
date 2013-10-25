#include "Globals.h"

#pragma once
class Block
{
public:
	Block(float x, float y, float z);
	~Block(void);

	void drawBlock();

private:
	float x, y, z;
};

