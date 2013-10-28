#include "cScene.h"
#include "noise.h"

cScene::cScene(void) {
	sceneBlocks = (Block***)malloc(SCENE_HEIGHT*sizeof(Block**));
	for (int i = 0; i < SCENE_HEIGHT; i++){
		sceneBlocks[i] = (Block**)malloc(SCENE_DEPTH*sizeof(Block*));
		for (int j = 0; j < SCENE_DEPTH; j++) {
			sceneBlocks[i][j] = (Block*)malloc(SCENE_WIDTH*sizeof(Block));
		}
	}
}

cScene::~cScene(void) {
	free(sceneBlocks);
}


void cScene::Draw() {
	for (int i = 0; i < SCENE_HEIGHT; ++i) {
		for (int j = 0; j < SCENE_DEPTH; ++j) {
			for (int k = 0; k < SCENE_WIDTH; ++k) {
				GLuint idVert = sceneBlocks[i][j][k].getVBOIDvert(), idIndi = sceneBlocks[i][j][k].getVBOIDindi();

				//vertices
				glEnableClientState(GL_VERTEX_ARRAY);
				glBindBuffer(GL_ARRAY_BUFFER, idVert);
				glVertexPointer(3, GL_FLOAT, 0, (GLvoid*)0);

				//indices
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIndi);
				glDrawElements(GL_QUADS, NUM_FACES_BLOCK*NUM_VERT_IN_FACE, GL_UNSIGNED_INT, (GLvoid*)0);

				//disabling states and unbinding buffers
				glDisableClientState(GL_VERTEX_ARRAY);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			}
		}
	}
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

//bool cScene::Init() {
//	bool res = true;
//	float *vector;
//	vector = (float*)malloc(SCENE_WIDTH*SCENE_DEPTH*sizeof(float));
//	/*for (int i = 0; i < SCENE_WIDTH*SCENE_DEPTH; i++){
//		vector[i] = 0.0;
//	}*/
//	int featureSize = 8;
//	for( int z = 0; z < SCENE_DEPTH; z += featureSize) {
//		for (int x = 0; x < SCENE_WIDTH; x += featureSize) {
//			setSample(vector,x, z, frand());  //IMPORTANT: frand() is a random function that returns a value between -1 and 1.
//		}
//	}
//	int samplesize = featureSize;
//	double scale = 1.0;
//	while (samplesize > 1) {
//		DiamondSquare(vector,samplesize, scale);
//		samplesize /= 2;
//		scale /= 2.0;
//	}
//
//}

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

	//generating a BLOCK in each position of the map
	for (int i = 0; i < SCENE_HEIGHT; i++){
		for (int j = 0; j < SCENE_DEPTH; j++) {
			for (int k = 0; k < SCENE_WIDTH; k++) {
				sceneBlocks[i][j][k] = Block(0, 0, 0, 0);
			}
		}
	}
	initVBO();
	return true;
}

void cScene::initVBO() {
	for(int i = 0; i<SCENE_HEIGHT; ++i) {
		for(int j = 0; j<SCENE_DEPTH; ++j) {
			for(int k = 0; k<SCENE_WIDTH; ++k) {
				//Make the float* with all the vertices and other one for the normals of each vertices
				//float *n = (float*) malloc(sizeof(float)*3*NUM_VERTICES_PER_CUBE); //I think is not needed if we sent the vertexs in the correct order
				//float *t = (float*) malloc(sizeof(float*2*NUM_FACES_BLOCK*NUM_VERT_IN_FACE));

				//Making v and n
				//We can hardcode this since our scene is composed only by cubes
				float x = (float) k, y = (float) i, z = (float) j;
				float v[3*NUM_VERT_IN_FACE*2]  = {
					x, y+1.0, z+1.0,	//0	TOP
					x+1.0, y+1.0, z+1.0,	//1
					x+1.0, y+1.0, z,	//2
					x, y+1.0, z,	//3
					x, y, z+1.0,	//4	BOTTOM
					x, y, z,	//5
					x+1.0, y, z,	//6
					x+1.0, y, z+1.0,	//7
				};

				//Now we have the 8 vertexs of the cube at v
				GLuint indi[NUM_FACES_BLOCK*NUM_VERT_IN_FACE] = {
					0, 1, 2, 3, //TOP
					4, 5, 6, 7, //BOTTOM
					1, 0, 4, 7, //FRONT
					6, 5, 3, 2, //BACK
					0, 3, 5, 4, //LEFT
					1, 7, 6, 2, //RIGHT
				};

				GLuint idVert, idIndi;
				glGenBuffers(1, &idVert);
				glGenBuffers(1, &idIndi);

				//sending vertices to GPU
				glBindBuffer(GL_ARRAY_BUFFER, idVert);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*NUM_VERTICES_PER_CUBE, v, GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				//sending vertices indices to GPU
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIndi);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*NUM_FACES_BLOCK*NUM_VERT_IN_FACE, indi, GL_STATIC_DRAW);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

				//TODO: send textures as GL_DYNAMIC_DRAW

				sceneBlocks[i][j][k].setVBOID(idVert, 0, 0, idIndi);
			}
		}
	}
}

void cScene::destroyVBO() {
	for(int i = 0; i<SCENE_HEIGHT; ++i) {
		for (int j = 0; j < SCENE_DEPTH; j++) {
			for (int k = 0; k < SCENE_WIDTH; k++) {
				GLuint idVert = sceneBlocks[i][j][k].getVBOIDvert(), idIndi = sceneBlocks[i][j][k].getVBOIDindi();
				if(idVert != 0) {
					glDeleteBuffers(1, &idVert);
				}
				if(idIndi != 0) {
					glDeleteBuffers(1, &idIndi);
				}
				sceneBlocks[i][j][k].setVBOID(0, 0, 0, 0);
			}
		}
	}
}
