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
	Block ***sceneBlocks;	//real map
};
