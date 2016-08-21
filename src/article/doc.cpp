/*
 * doc.cpp
 *
 *  Created on: 7 Mar 2016
 *      Author: Mason
 */

#include "doc.h"
#include "../draw.h"

int do_orientation;

doc::doc(int x, int y, int z, char* d) {
	// TODO Auto-generated constructor stub
	position = {x, y, z};
	do_orientation = 0;
	hitbox = {0.5, 1, 0.5};
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

doc::~doc() {
	// TODO Auto-generated destructor stub
}


void doc::draw() {
	// Draw::document will come more from frame

	//Draw::entrance(position[0], position[1], position[2], dr_orientation, dir);
	Draw::document(position[0], position[1], position[2], dir);
}
