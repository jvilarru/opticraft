#pragma once
#include "Globals.h"
class cScene {
public:
	cScene(void);
	virtual ~cScene(void);
	void Draw();
	bool Init();

private:
	char ***map;	//scene
};
