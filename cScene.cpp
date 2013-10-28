#include "cScene.h"
#include "noise.h"

cScene::cScene(void) {
	sceneBlocks = (Block***)malloc(SCENE_HEIGHT*sizeof(Block**));
	sceneVertices = (Point***) malloc(SCENE_HEIGHT*sizeof(Point**));
	for (int i = 0; i < SCENE_HEIGHT; i++){
		sceneBlocks[i] = (Block**)malloc(SCENE_DEPTH*sizeof(Block*));
		sceneVertices[i] = (Point**) malloc(SCENE_DEPTH*sizeof(Point*));
		for (int j = 0; j < SCENE_DEPTH; j++) {
			sceneBlocks[i][j] = (Block*)malloc(SCENE_WIDTH*sizeof(Block));
			sceneVertices[i][j] = (Point*)malloc(SCENE_WIDTH*sizeof(Point));
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

bool cScene::Init() {
	bool res = true;
	float *vector;
	vector = (float*)malloc(SCENE_WIDTH*SCENE_DEPTH*sizeof(float));
	/*for (int i = 0; i < SCENE_WIDTH*SCENE_DEPTH; i++){
		vector[i] = 0.0;
	}*/
	int featureSize = 8;
	for( int z = 0; z < SCENE_DEPTH; z += featureSize) {
		for (int x = 0; x < SCENE_WIDTH; x += featureSize) {
			setSample(vector,x, z, frand());  //IMPORTANT: frand() is a random function that returns a value between -1 and 1.
		}
	}
	int samplesize = featureSize;
	double scale = 1.0;
	while (samplesize > 1) {
		DiamondSquare(vector,samplesize, scale);
		samplesize /= 2;
		scale /= 2.0;
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

	//generating a BLOCK in each position of the map
	for (int i = 0; i < SCENE_HEIGHT; i++){
		for (int j = 0; j < SCENE_DEPTH; j++) {
			for (int k = 0; k < SCENE_WIDTH; k++) {
				sceneVertices[i][j][k] = Point((float) i, (float) j, (float) k);
				sceneBlocks[i][j][k] = Block(k, i, j);
			}
		}
	}
	initVBO();
	return true;
}

void cScene::initVBO() {
	//TODO
	/* La idea es la siguiente:
	Tenemos un vector con un uid de cada cubo.
	Por cada cubo hay que hacer un vector con sus vertices (8)
	Un vector con las normales de esos vertices (serán las de la cara)
	y el color de ese vertice (en este caso habrá que meter texturas tambien)
	Por último se tendrá que crear el vector de indices */

	//Generate four buffers per each cube (vertices, normals, textures and indices

	for(int i = 0; i<SCENE_HEIGHT; ++i) {
		for(int j = 0; j<SCENE_DEPTH; ++j) {
			for(int k = 0; k<SCENE_WIDTH; ++k) {
				
			}
		}
	}
}
