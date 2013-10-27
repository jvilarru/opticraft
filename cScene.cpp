#include "cScene.h"
#include "noise.h"

cScene::cScene(void) {
	sceneBlocks = (Block***)malloc(SCENE_HEIGHT*sizeof(Block**));
	for (int i = 0; i < SCENE_HEIGHT; i++){
		sceneBlocks[i] = (Block**)malloc(SCENE_DEPTH*sizeof(Block*));
		for (int j = 0; j < SCENE_DEPTH; j++) {
			sceneBlocks[i][j] = (Block*)malloc(SCENE_WIDHT*sizeof(Block));
		}
	}
}

cScene::~cScene(void) {
	free(sceneBlocks);
}


void cScene::Draw() {
	//TODO: DrawVBO
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
		for(int x=0;x<SCENE_WIDHT;x++){
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
	return true;
}
