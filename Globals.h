
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "GL/glew.h"
#include "GL/freeglut.h"
#pragma comment(lib, "glew32.lib")

#define BLOCK_SIZE		1.0
#define RENDER_DISTANCE 15

#define NUM_VERTICES_PER_CUBE 8
#define NUM_VERT_IN_FACE 4
#define NUM_FACES_BLOCK 6

#define CHUNK_WIDTH		16
#define CHUNK_DEPTH		16
#define	CHUNK_HEIGHT	128

#define TOTAL_CHUNKS_LOADED	16

#define SCENE_WIDTH		64
#define SCENE_DEPTH		64
#define SCENE_HEIGHT	128

#define GAME_WIDTH	800
#define GAME_HEIGHT	600

#define EMPTY	0
#define DIRT	1
#define ROCK	2
#define WATER	3
#define SAND	4

#define FPS	60

#define MAX_SHADERS 3
#define VERTEX_SHADER 0
#define GEOMETRY_SHADER 1
#define FRAGMENT_SHADER 2

//RETURN VALUES
#define OK 0
#define ERR_FD_NULL 1
#define ERR_EMPTY 2
#define ERR_OUT_MEM 3
#define ERR_NONEXISTENT_KIND_SHADER 4
#define ERR_COMPILE 5
#define ERR_LINK 6
