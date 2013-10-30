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
	
	Block sceneBlocks;

	/*GLuint idVertices[SCENE_HEIGHT];
	GLuint idIndices[SCENE_HEIGHT];*/
};
