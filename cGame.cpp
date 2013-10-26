#include "cGame.h"

cGame::cGame(void)
{
}

cGame::~cGame(void){
}

bool cGame::Init()
{
	Point eye(-SCENE_WIDTH*2, SCENE_HEIGHT*3, -SCENE_DEPTH*2);
	Point center(SCENE_WIDTH, SCENE_HEIGHT, 0.0);
	Point up(0.0, 1.0, 0.0);
	bool basaur;
	//Graphics initialization
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	cam = Camera(eye, center, up);
	glMatrixMode(GL_MODELVIEW);
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	basaur = Scene.Init();
	return basaur;
}

bool cGame::Loop() {
	bool res = Process();
	if(res) Render();
	return res;
}

void cGame::Finalize() {
	exit(0);
}

//Input
void cGame::ReadKeyboard(unsigned char key, bool press) {
	keys[key] = press;
}
void cGame::ReadSpecialKeyboard(unsigned char specialkey, bool press) {
	specialKeys[specialkey] = press;

}

void cGame::ReadMouse(int button, int state, int x, int y) {
}

//Process
bool cGame::Process() {
	if(keys[27])return false;
	if(keys['W'] || keys['w'] || specialKeys[GLUT_KEY_UP]) {
		return true;
	}
	if(keys['A'] || keys['a'] || specialKeys[GLUT_KEY_LEFT]) {
		return true;
	}
	if(keys['S'] || keys['s'] || specialKeys[GLUT_KEY_DOWN]) {
		return true;
	}
	if(keys['D'] || keys['d'] || specialKeys[GLUT_KEY_RIGHT]) {
		return true;
	}
	return true;
}

//Output
void cGame::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	Scene.Draw();
	glutSwapBuffers();
}
