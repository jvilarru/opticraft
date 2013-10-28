#pragma once
//#include "GL/glew.h"
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
	
	Point ***sceneVertices;		//It contains all the vertices of the cubes
	Block ***sceneBlocks;		//It contains all the blocks in the scene
};
