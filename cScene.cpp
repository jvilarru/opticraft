#include "cScene.h"

cScene::cScene(void) {
	map = (char***)malloc(SCENE_HEIGHT*sizeof(char**));
	for (int i = 0; i < SCENE_HEIGHT; i++){
		map[i] = (char**)malloc(SCENE_DEPTH*sizeof(char*));
		for (int j = 0; j < SCENE_DEPTH; j++) {
			map[i][j] = (char*)malloc(SCENE_WIDHT*sizeof(char));
		}
	}
}

cScene::~cScene(void) {
	free(map);
}


void cScene::Draw() {
	
}

float frand(){
	float res = (float) rand() / (float) RAND_MAX;
	res *= 64.0;
	res += 32.0;
	return res;
}

double sample(float* values, int x, int z) {
	return values[(x & (SCENE_WIDHT - 1)) + (z &(SCENE_DEPTH - 1)) * SCENE_WIDHT];
}
 
void setSample(float * values, int x, int z, double value) {
	values[(x & (SCENE_WIDHT - 1)) + (z &(SCENE_DEPTH - 1)) * SCENE_WIDHT] = value;
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
		for (int x = halfstep; x < SCENE_WIDHT + halfstep; x += stepsize) {
            sampleSquare(vector,x, z, stepsize, frand() * scale);
        }
    }
	for (int z = 0; z < SCENE_DEPTH; z += stepsize) {
		for (int x = 0; x < SCENE_WIDHT; x += stepsize) {
            sampleDiamond(vector,x + halfstep, z, stepsize, frand() * scale);
            sampleDiamond(vector,x, z + halfstep, stepsize, frand() * scale);
        }
    }
}

bool cScene::Init() {
	bool res = true;
	float *vector;
	vector = (float*)malloc(SCENE_WIDHT*SCENE_DEPTH*sizeof(float));
	for (int i = 0; i < SCENE_WIDHT*SCENE_DEPTH; i++)
	{
		vector[i] = 0.0;
	}
	int featureSize = 8;
	for( int z = 0; z < SCENE_DEPTH; z += featureSize) {
		for (int x = 0; x < SCENE_WIDHT; x += featureSize) {
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

	FILE* fd = fopen("debug.txt","w+");
	float min,max;
	min = max =0.0;
	if(fd!=nullptr){
		for(int i=0;i<SCENE_WIDHT;i++){
			for(int j=0;j<SCENE_DEPTH;j++){
				
			}
		}
		fprintf(fd,"min-->%.8f\n",min);
		fprintf(fd,"max-->%.8f\n",max);
		fclose(fd);
		res = false;
	}
	free(vector);
	for (int i = 0; i < SCENE_HEIGHT; i++){
		for (int j = 0; j < SCENE_DEPTH; j++) {
			for (int k = 0; k < SCENE_WIDHT; k++) {
				map[i][j][k] = 42;
			}
		}
	}
	return true;
}
