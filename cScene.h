#pragma once
#include "Globals.h"
#include "Block.h"
#include "GL/glew.h"

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
