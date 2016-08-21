/*
 * door.cpp
 *
 *  Created on: 4 Mar 2016
 *      Author: Mason
 */

#include "door.h"
#include "../draw.h"

int dr_orientation;

door::door(int x, int y, int z, char* d) {
	// TODO Auto-generated constructor stub
	position = {x, y, z};
	dr_orientation = 0;
	hitbox = {0.5, 1, 0.3};
/*
	char* fn;
	fn = (char*) malloc (strlen(d)+strlen(World::directory)+strlen(World::dd));

	strcpy(fn, World::directory);
	strcat(fn, World::dd);
	strcat(fn, d);
	strcat(fn, "\\");
*/
	dir = d;
}

door::~door() {
	// TODO Auto-generated destructor stub
}

void door::draw() {
	// Draw::door will come more from frame

	Draw::entrance(position[0], position[1], position[2], dr_orientation, dir);
	//Draw::television(position[0], position[1], position[2], dir);
}
