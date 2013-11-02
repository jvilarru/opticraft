#include "cScene.h"
#include "noise.h"

cScene::cScene(void) {
}

cScene::~cScene(void) {
}

void cScene::Draw() {
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, idV);
	glVertexPointer(3, GL_FLOAT, 0, (GLvoid*)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idI);

	for(int y = 0; y<SCENE_HEIGHT; ++y) {
		glPushMatrix();
		glTranslatef(0.0, (GLfloat)y, 0.0);
		glDrawElements(GL_QUADS, NUM_FACES_BLOCK*NUM_VERT_IN_FACE*SCENE_WIDTH*SCENE_DEPTH, GL_UNSIGNED_INT, (GLvoid*)0);
		glPopMatrix();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

bool cScene::Init(FILE* fd) {

	maxHeight = 0;
	minHeight = SCENE_HEIGHT;
	int randomseed = 0;
	int amplitude = SCENE_HEIGHT/2;
	PerlinNoise noise = PerlinNoise(0.1,1,amplitude,8,randomseed);
	
	for(int z=0;z<SCENE_DEPTH;z++){
		for(int x=0;x<SCENE_WIDTH;x++){
			int alt = amplitude + (int)noise.GetHeight(x,z);
			int y;
			for (y = 0; y < alt; y++){
				mapa[y][x][z] = 1;
			}
			minHeight = min(y,minHeight);
			maxHeight = max(y,maxHeight);
			heightMap[x][z] = y;
			for(;y<SCENE_HEIGHT;y++){
				mapa[y][x][z] = 0;
			}
		}
	}
	fprintf(fd,"min-->%d\nmax-->%d\n",minHeight,maxHeight);
	initVBO();
	return true;
}

void cScene::initVBO() {
	glGenBuffers(1, &idV);
	glGenBuffers(1, &idI);

	float v[SCENE_DEPTH*SCENE_WIDTH * 3*NUM_VERTICES_PER_CUBE];
	GLuint i[SCENE_DEPTH*SCENE_WIDTH * 3 * NUM_VERTICES_PER_CUBE];
	float zaux=0,xaux;
	for(int z = 0; z<SCENE_DEPTH; ++z) {
		xaux=0;
		for(int x = 0; x<SCENE_WIDTH; ++x) {
			float vAux[3*NUM_VERTICES_PER_CUBE] = {
				xaux, 1.0f, zaux+1.0f,	//0	TOP
				xaux+1.0f, 1.0f, zaux+1.0f,	//1
				xaux+1.0f, 1.0f, zaux,	//2
				xaux, 1.0f, zaux,	//3
				xaux, 0.0f, zaux+1.0f,	//4	BOTTOM
				xaux, 0.0f, zaux,	//5
				xaux+1.0f, 0.0f, zaux,	//6
				xaux+1.0f, 0.0f, zaux+1.0f,	//7
			};
			unsigned int base = (z*SCENE_WIDTH + x)*NUM_VERTICES_PER_CUBE;
			GLuint iAux[3 * NUM_VERTICES_PER_CUBE] = {
				base+0, base+1, base+2, base+3, //TOP
				base+4, base+5, base+6, base+7, //BOTTOM
				base+1, base+0, base+4, base+7, //FRONT
				base+6, base+5, base+3, base+2, //BACK
				base+0, base+3, base+5, base+4, //LEFT
				base+1, base+7, base+6, base+2, //RIGHT
			};
			for(int l=0; l<3*NUM_VERTICES_PER_CUBE; ++l) {
				v[(z*SCENE_WIDTH+x)*24 + l] = vAux[l];
				i[(z*SCENE_WIDTH+x)*24 + l] = iAux[l];
			}
		
			xaux += 1.0;
		}
		
		zaux += 1.0;
	}

	//sending vertices to GPU
	glBindBuffer(GL_ARRAY_BUFFER, idV);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*NUM_VERTICES_PER_CUBE*SCENE_WIDTH*SCENE_DEPTH,v, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//sending vertices indices to GPU
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idI);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*NUM_FACES_BLOCK*NUM_VERT_IN_FACE*SCENE_WIDTH*SCENE_DEPTH,i, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void cScene::destroyVBO() {
	glDeleteBuffers(1, &idV);
	glDeleteBuffers(1, &idI);
}
