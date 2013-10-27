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

	GLuint quadVBO;
	Block ***sceneBlocks;
};
