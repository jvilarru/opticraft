#pragma once
#include "Globals.h"
class cScene {
public:
	cScene(void);
	virtual ~cScene(void);
	void Draw();
	bool Init();

private:
	char map[SCENE_HEIGHT][SCENE_DEPTH][SCENE_WIDHT];	//scene
};
