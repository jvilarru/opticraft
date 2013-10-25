
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gl/glut.h>

#define BLOCK_SIZE		128

#define SCENE_WIDHT		1024
#define SCENE_DEPTH		1024
#define SCENE_HEIGHT	256

#define GAME_WIDTH	1024
#define GAME_HEIGHT	768

#define EMPTY	0
#define DIRT	1
#define ROCK	2
#define WATER	3
#define SAND	4

#define FPS	60