#include "Block.h"

#define COLOR
#ifdef COLOR
#define COLOR_R 0.75
#define COLOR_G 0.75
#define COLOR_B 0.75
#endif

Block::Block(float x, float y, float z)
{
}


Block::~Block(void)
{
}

void Block::drawBlock() {
#ifdef COLOR
	glColor3f(COLOR_R, COLOR_G, COLOR_B);
#endif
	glBegin(GL_QUADS);
	//Top face
	glVertex3f(this->x-BLOCK_SIZE/2, this->y+BLOCK_SIZE/2, this->z-BLOCK_SIZE/2);
	glVertex3f(this->x+BLOCK_SIZE/2, this->y+BLOCK_SIZE/2, this->z-BLOCK_SIZE/2);
	glVertex3f(this->x+BLOCK_SIZE/2, this->y+BLOCK_SIZE/2, this->z+BLOCK_SIZE/2);
	glVertex3f(this->x-BLOCK_SIZE/2, this->y+BLOCK_SIZE/2, this->z+BLOCK_SIZE/2);

	//Bottom face
	glVertex3f(this->x-BLOCK_SIZE/2, this->y-BLOCK_SIZE/2, this->z-BLOCK_SIZE/2);
	glVertex3f(this->x-BLOCK_SIZE/2, this->y-BLOCK_SIZE/2, this->z+BLOCK_SIZE/2);
	glVertex3f(this->x+BLOCK_SIZE/2, this->y-BLOCK_SIZE/2, this->z+BLOCK_SIZE/2);
	glVertex3f(this->x+BLOCK_SIZE/2, this->y-BLOCK_SIZE/2, this->z-BLOCK_SIZE/2);

	//Front face
	glVertex3f(this->x-BLOCK_SIZE/2, this->y-BLOCK_SIZE/2, this->z-BLOCK_SIZE/2);
	glVertex3f(this->x+BLOCK_SIZE/2, this->y-BLOCK_SIZE/2, this->z-BLOCK_SIZE/2);
	glVertex3f(this->x+BLOCK_SIZE/2, this->y+BLOCK_SIZE/2, this->z-BLOCK_SIZE/2);
	glVertex3f(this->x-BLOCK_SIZE/2, this->y+BLOCK_SIZE/2, this->z-BLOCK_SIZE/2);

	//Back face
	glVertex3f(this->x-BLOCK_SIZE/2, this->y-BLOCK_SIZE/2, this->z+BLOCK_SIZE/2);
	glVertex3f(this->x-BLOCK_SIZE/2, this->y+BLOCK_SIZE/2, this->z+BLOCK_SIZE/2);
	glVertex3f(this->x+BLOCK_SIZE/2, this->y+BLOCK_SIZE/2, this->z+BLOCK_SIZE/2);
	glVertex3f(this->x+BLOCK_SIZE/2, this->y-BLOCK_SIZE/2, this->z+BLOCK_SIZE/2);

	//Left face
	glVertex3f(this->x-BLOCK_SIZE/2, this->y-BLOCK_SIZE/2, this->z+BLOCK_SIZE/2);
	glVertex3f(this->x-BLOCK_SIZE/2, this->y-BLOCK_SIZE/2, this->z-BLOCK_SIZE/2);
	glVertex3f(this->x-BLOCK_SIZE/2, this->y+BLOCK_SIZE/2, this->z-BLOCK_SIZE/2);
	glVertex3f(this->x-BLOCK_SIZE/2, this->y+BLOCK_SIZE/2, this->z+BLOCK_SIZE/2);

	//Right face
	glVertex3f(this->x+BLOCK_SIZE/2, this->y-BLOCK_SIZE/2, this->z-BLOCK_SIZE/2);
	glVertex3f(this->x+BLOCK_SIZE/2, this->y-BLOCK_SIZE/2, this->z+BLOCK_SIZE/2);
	glVertex3f(this->x+BLOCK_SIZE/2, this->y+BLOCK_SIZE/2, this->z+BLOCK_SIZE/2);
	glVertex3f(this->x+BLOCK_SIZE/2, this->y+BLOCK_SIZE/2, this->z-BLOCK_SIZE/2);

	glEnd();
#ifdef COLOR
	glColor3f(0.0, 0.0, 0.0);
#endif
}
