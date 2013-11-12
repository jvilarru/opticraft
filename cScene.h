#pragma once
#include "Globals.h"
#include "Block.h"
#include "Shader.h"

class cScene {
public:
	cScene(void);
	virtual ~cScene(void);
	void Draw();
	bool Init(FILE* fd);

private:
	GLuint idV, idN, idI;
	void initVBO();
	void initNormals();
	void destroyVBO();	//to be called when program finishes
	
	char mapa[SCENE_HEIGHT][SCENE_WIDTH][SCENE_DEPTH];	//stores block type per each position
	int heightMap[SCENE_WIDTH][SCENE_DEPTH];			//??
	int maxHeight,minHeight;							//??
	unsigned int nCubes[SCENE_HEIGHT];					//how many cubes per level

	Shader shader;
};
