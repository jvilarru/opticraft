#pragma once
#include "Globals.h"

class entity {
public:
	entity(int health,Point pos, Point direction);
	~entity(void);
	bool hurt(int damage); //damage the entity with damage and return if its death
	void move(int direction);
	void turn(float xGraus, float yGraus);
private:
	int health;
	Point pos;
	Point direction; //this needs to be a unitari vector
};

