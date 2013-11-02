#include "entity.h"

entity::entity(int health, Point pos, Point dir) {
	this->health = health;
	this->pos = pos;
	this->direction = dir;
}


entity::~entity(void) {
}

bool entity::hurt(int damage){
	health-=damage;
	return health <= 0;
}

void entity::move(int dir){
	switch (dir) {
	case UP:
		break;
	case DOWN:
		break;
	case LEFT:
		break;
	case RIGHT:
		break;
	default:
		break;
	}
}

