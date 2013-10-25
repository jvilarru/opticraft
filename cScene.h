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
	//char ***map/*[SCENE_HEIGHT][SCENE_DEPTH][SCENE_WIDTH]*/;	//scene
	Block ***sceneBlocks/*[SCENE_HEIGHT][SCENE_DEPTH][SCENE_WIDTH]*/;	//real map
};
