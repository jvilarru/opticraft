#pragma once
#include "cScene.h"
#include "Camera.h"
#include <map>
#include <shlobj.h>

using namespace std;

class cGame
{
public:
	cGame(void);
	virtual ~cGame(void);

	bool Init();
	bool Loop();
	void Finalize();

	//Input
	void ReadKeyboard(unsigned char key, bool press);
	void ReadSpecialKeyboard(unsigned char specialkey, bool press);
	void ReadMouse(int button, int state, int x, int y);
	void MouseMove(int x, int y,bool pressed);
	//Process
	bool Process();
	//Output
	void Render();

	int inittime;
	FILE* fd;

private:
	unsigned char keys[256];
	unsigned char specialKeys[256];
	cScene Scene;
	Camera cam;
	bool drawGlut;
};
