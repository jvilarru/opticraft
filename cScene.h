#pragma once
#include "Globals.h"
#include "Block.h"

class cScene {
public:
	cScene(void);
	virtual ~cScene(void);
	void Draw();
	bool Init();

private:
	void initVBO();
	void destroyVBO();	//to be called when program finishes
	
	Point ***sceneVertices;		//It contains all the vertices of the cubes
	Block ***sceneBlocks;		//It contains all the blocks in the scene
};
