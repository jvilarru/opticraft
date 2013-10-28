
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "GL/glew.h"
#include "GL/glut.h"

#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glew32.lib")

#define BLOCK_SIZE		1.0
#define RENDER_DISTANCE 15

#define NUM_VERTICES_PER_CUBE 8
#define NUM_VERT_IN_FACE 4
#define NUM_FACES_BLOCK 6

#define SCENE_WIDTH		512
#define SCENE_DEPTH		512
#define SCENE_HEIGHT	128

#define GAME_WIDTH	800
#define GAME_HEIGHT	600

#define EMPTY	0
#define DIRT	1
#define ROCK	2
#define WATER	3
#define SAND	4

#define FPS	60