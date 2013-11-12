#include "cGame.h"

cGame::cGame(void)
{
	drawGlut = false;
}

cGame::~cGame(void){
}

bool cGame::Init()
{
	fd = fopen("debug.txt","w+");
	Point eye = Point(-50, SCENE_HEIGHT/2, -50);
	Point center = Point(SCENE_WIDTH/2, SCENE_HEIGHT/2, SCENE_DEPTH/2);
	Point up = Point(0.0f, 1.0f, 0.0f);
	bool basaur;

	/***********************************************************************************/
	//Graphics initialization
	//CAMERA
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	cam = Camera(eye, center, up);
	glMatrixMode(GL_MODELVIEW);
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);
	//MATERIAL
	glEnable(GL_COLOR_MATERIAL);
	GLfloat matAmbient[] = {0.4, 0.4, 0.4, 1.0};
	GLfloat matDiffuse[] = {1.0, 1.0, 0.0, 1.0};
	GLfloat matSpecular[] = {0.0, 0.0, 1.0, 1.0};
	GLfloat matEmission[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat matShininnes = 20;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matEmission);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &matShininnes);
	//LIGHTNING
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat lightPos[] = { SCENE_WIDTH/2, SCENE_HEIGHT*2, SCENE_DEPTH/2};
	GLfloat specLight[] = { 1.0, 1.0, 1.0, 1.0};
	GLfloat ambiLight[] = { 0, 0, 0, 1.0};
	GLfloat diffLight[] = { 1.0, 1.0, 1.0, 1.0};
	GLfloat ambientModel[] = {.5, .5, .5, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiLight);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientModel);
	//glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1.0);
	/**********************************************************************************/

	int start = glutGet(GLUT_ELAPSED_TIME);
	basaur = Scene.Init(fd);
	int end = glutGet(GLUT_ELAPSED_TIME);
	fprintf(fd,"%d",end-start);
	return basaur;
}

bool cGame::Loop() {
	bool res = Process();
	if(res) Render();
	return res;
}

void cGame::Finalize() {
	fclose(fd);
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
		camEye.z=(camEye.z+1);
		cam.setCamera(camEye, cam.getCameraCenter());
		return true;
	}
	if(keys['A'] || keys['a'] || specialKeys[GLUT_KEY_LEFT]) {
		Point camEye = cam.getCameraEye();
		camEye.x=(camEye.x-1);
		cam.setCamera(camEye, cam.getCameraCenter());
		return true;
	}
	if(keys['S'] || keys['s'] || specialKeys[GLUT_KEY_DOWN]) {
		Point camEye = cam.getCameraEye();
		camEye.z=(camEye.z-1);
		cam.setCamera(camEye, cam.getCameraCenter());
		return true;
	}
	if(keys['D'] || keys['d'] || specialKeys[GLUT_KEY_RIGHT]) {
		Point camEye = cam.getCameraEye();
		camEye.x=(camEye.x+1);
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
	cam.updateCamera();
	glutSwapBuffers();
}
