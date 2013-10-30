#include "cGame.h"

cGame::cGame(void)
{
	drawGlut = false;
}

cGame::~cGame(void){
}

bool cGame::Init()
{
	Point eye(SCENE_WIDTH+20, SCENE_HEIGHT+20, SCENE_DEPTH+20);
	Point center(SCENE_WIDTH/2, SCENE_HEIGHT/2, SCENE_DEPTH/2);
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

	int start = glutGet(GLUT_ELAPSED_TIME);
	basaur = Scene.Init();
	int end = glutGet(GLUT_ELAPSED_TIME);
	FILE* fd = fopen("time.txt","w+");
	fprintf(fd,"%d",end-start);
	fclose(fd);
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

void cGame::MouseMove(int x, int y,bool pressed){

}


//Process
bool cGame::Process() {
	if(keys[27])return false;
	if(keys['W'] || keys['w'] || specialKeys[GLUT_KEY_UP]) {
		Point camEye = cam.getCameraEye();
		camEye.setZ(camEye.getZ()+1);
		cam.setCamera(camEye, cam.getCameraCenter());
		return true;
	}
	if(keys['A'] || keys['a'] || specialKeys[GLUT_KEY_LEFT]) {
		Point camEye = cam.getCameraEye();
		camEye.setX(camEye.getX()-1);
		cam.setCamera(camEye, cam.getCameraCenter());
		return true;
	}
	if(keys['S'] || keys['s'] || specialKeys[GLUT_KEY_DOWN]) {
		Point camEye = cam.getCameraEye();
		camEye.setZ(camEye.getZ()-1);
		cam.setCamera(camEye, cam.getCameraCenter());
		return true;
	}
	if(keys['D'] || keys['d'] || specialKeys[GLUT_KEY_RIGHT]) {
		Point camEye = cam.getCameraEye();
		camEye.setX(camEye.getX()+1);
		cam.setCamera(camEye, cam.getCameraCenter());
		return true;
	}
	return true;
}

//Output
void cGame::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix();
	glColor3f(1,1,1);
	Scene.Draw();
	glPopMatrix();
	//cam.updateCamera();
	glutSwapBuffers();
}
