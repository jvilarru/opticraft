#include "cScene.h"
#include <algorithm>

cScene::cScene(void) {
}

cScene::~cScene(void) {

}


void cScene::Draw() {
	
}

bool cScene::Init() {
	for (int y = 0; y < SCENE_HEIGHT; y++) {
		for (int x = 0; x < SCENE_DEPTH; x++) {
			for (int z = 0; z < SCENE_WIDTH; z++) {
				sceneBlocks[x][y][z] = *(new Block((float)x,(float)y,(float)z));
			}

		}

	}
	return false;
}

int cScene::Process() {
	return 0;
}
