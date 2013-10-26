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
	void addVBO();
	void rmVBO(GLuint uid);
	
	GLuint uidsVBO[SCENE_HEIGHT][SCENE_DEPTH][SCENE_WIDHT];
	Block ***sceneBlocks;
};
