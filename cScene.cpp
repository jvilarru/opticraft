#include "cScene.h"
#include <algorithm>

cScene::cScene(void) {
	sceneBlocks = (Block *) malloc(SCENE_WIDTH*SCENE_HEIGHT*SCENE_DEPTH*sizeof(Block));
}

cScene::~cScene(void) {

}


void cScene::Draw() {
	for (int i = 0; i < SCENE_HEIGHT; ++i) {
		for (int j = 0; j < SCENE_DEPTH; ++j) {
			for (int k = 0; k < SCENE_WIDTH; ++k) {
				sceneBlocks[i*SCENE_WIDTH*SCENE_DEPTH + j*SCENE_WIDTH + k].drawBlock();
			}
		}
	}
}

bool cScene::Init() {
	for (int y = 0; y < SCENE_HEIGHT; y++) {
		for (int z = 0; z < SCENE_DEPTH; z++) {
			for (int x = 0; x < SCENE_WIDTH; x++) {
				sceneBlocks[y*SCENE_WIDTH*SCENE_DEPTH + z*SCENE_WIDTH + x] = Block(Point(x,y,z));
			}

		}

	}
	return false;
}

int cScene::Process() {
	return 0;
}
