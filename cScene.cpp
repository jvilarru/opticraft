#include "cScene.h"

cScene::cScene(void) {
}

cScene::~cScene(void) {

}


void cScene::Draw() {
	
}

double sample(float* values, int x, int y) {
	return values[(x & (SCENE_WIDHT - 1)) + (y & (SCENE_DEPTH - 1)) * SCENE_WIDHT];
}
 
void setSample(float * values, int x, int y, double value) {
	values[(x & (SCENE_WIDHT - 1)) + (y & (SCENE_DEPTH - 1)) * SCENE_WIDHT] = value;
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

float frand(){
	return ((float)rand())/(RAND_MAX<<7);
}


bool cScene::Init() {
	//float *vector = (float*)malloc(SCENE_DEPTH*SCENE_WIDHT*sizeof(float));
	float *vector;
	vector = (float*)malloc(SCENE_WIDHT*SCENE_DEPTH*sizeof(float));
	int featureSize = 32;
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
	free(vector);
	return false;
}
