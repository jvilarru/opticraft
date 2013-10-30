#include "cScene.h"
#include "noise.h"

cScene::cScene(void) {
}

cScene::~cScene(void) {
}

void cScene::Draw() {
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, sceneBlocks.getVBOIDvert());
	glVertexPointer(3, GL_FLOAT, 0, (GLvoid*)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sceneBlocks.getVBOIDindi());

	for(int y = 0; y<SCENE_HEIGHT; ++y) {
		glPushMatrix();
		glTranslatef(0.0, y, 0.0);
		glDrawElements(GL_QUADS, NUM_FACES_BLOCK*NUM_VERT_IN_FACE*SCENE_WIDTH*SCENE_DEPTH, GL_UNSIGNED_INT, (GLvoid*)0);
		glPopMatrix();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

float frand(){
	float res = (float) rand() / (float) RAND_MAX;
	res *= 64.0;
	res += 32.0;
	return res;
}

double sample(float* values, int x, int z) {
	return values[(x & (SCENE_WIDTH - 1)) + (z &(SCENE_DEPTH - 1)) * SCENE_WIDTH];
}
 
void setSample(float * values, int x, int z, double value) {
	values[(x & (SCENE_WIDTH - 1)) + (z &(SCENE_DEPTH - 1)) * SCENE_WIDTH] = value;
}

void sampleSquare(float * vector,int x, int z, int size, double value) {
    int hs = size / 2;
    double a = sample(vector,x - hs, z - hs);
    double b = sample(vector,x + hs, z - hs);
    double c = sample(vector,x - hs, z + hs);
    double d = sample(vector,x + hs, z + hs);
    setSample(vector,x, z, ((a + b + c + d) / 4.0) + value);
}
 
void sampleDiamond(float* vector, int x, int z, int size, double value) {
    int hs = size / 2;
    double a = sample(vector,x - hs, z);
    double b = sample(vector,x + hs, z);
    double c = sample(vector,x, z - hs);
    double d = sample(vector,x, z + hs);
    setSample(vector,x, z, ((a + b + c + d) / 4.0) + value);
}

void DiamondSquare(float* vector, int stepsize, double scale) {
    int halfstep = stepsize / 2;
	for (int z = halfstep; z < SCENE_DEPTH + halfstep; z += stepsize) {
		for (int x = halfstep; x < SCENE_WIDTH + halfstep; x += stepsize) {
            sampleSquare(vector,x, z, stepsize, frand() * scale);
        }
    }
	for (int z = 0; z < SCENE_DEPTH; z += stepsize) {
		for (int x = 0; x < SCENE_WIDTH; x += stepsize) {
            sampleDiamond(vector,x + halfstep, z, stepsize, frand() * scale);
            sampleDiamond(vector,x, z + halfstep, stepsize, frand() * scale);
        }
    }
}

bool cScene::Init() {
	FILE* fd = fopen("debug.txt","w+");
	double minp,maxp;
	minp = maxp =0.0;
	int randomseed = 0;
	double amplitude = SCENE_HEIGHT/4;
	PerlinNoise noise = PerlinNoise(0.5,amplitude/4,amplitude,8,randomseed);
	Point p;
	if(fd!=nullptr){
		for(int x=0;x<SCENE_WIDTH;x++){
			p.x = x;
			for(int z=0;z<SCENE_DEPTH;z++){
				p.z=z;
				double y = amplitude + noise.GetHeight(x,z);
				minp = min(y,minp);
				maxp = max(y,maxp);
				/*for(y=(int)SCENE_HEIGHT-1;y>(int)vector[x*SCENE_DEPTH+z];y--){
					p.y=y;
					sceneBlocks[y][z][x] = Block(p,0);
					fprintf(fd,"%d",0);
				}
				for(;y>=0;y--){
					p.y=y;
					sceneBlocks[y][z][x] = Block(p,1);
					fprintf(fd,"%d",1);
				}*/
			}
		}
		fprintf(fd,"min-->%f\nmax-->%f\n",minp,maxp);
		fclose(fd);
	}

	initVBO();
	return true;
}

void cScene::initVBO() {
	GLuint idV, idI;

	glGenBuffers(1, &idV);
	glGenBuffers(1, &idI);

	float v[SCENE_DEPTH*SCENE_WIDTH * 3*NUM_VERTICES_PER_CUBE];
	GLuint i[SCENE_DEPTH*SCENE_WIDTH * 3 * NUM_VERTICES_PER_CUBE];
	float zaux=0,xaux;
	for(int z = 0; z<SCENE_DEPTH; ++z) {
		xaux=0;
		for(int x = 0; x<SCENE_WIDTH; ++x) {
			float vAux[3*NUM_VERTICES_PER_CUBE] = {
				xaux, 1.0, zaux+1.0,	//0	TOP
				xaux+1.0, 1.0, zaux+1.0,	//1
				xaux+1.0, 1.0, zaux,	//2
				xaux, 1.0, zaux,	//3
				xaux, 0.0, zaux+1.0,	//4	BOTTOM
				xaux, 0.0, zaux,	//5
				xaux+1.0, 0.0, zaux,	//6
				xaux+1.0, 0.0, zaux+1.0,	//7
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

	sceneBlocks = Block(idV,0,0,idI);
}

void cScene::destroyVBO() {
	GLuint idV = sceneBlocks.getVBOIDvert(), idI = sceneBlocks.getVBOIDindi();
	glDeleteBuffers(1, &idV);
	glDeleteBuffers(1, &idI);
}
