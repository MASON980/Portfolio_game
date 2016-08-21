/*
 * song.cpp
 *
 *  Created on: 1 Mar 2016
 *      Author: Mason
 */

#include "song.h"
#include "../draw.h"

Song::Song() {

}

Song::Song(int x, int y, int z, char* d) {
	// TODO Auto-generated constructor stub
	position = {x, y, z};
	dir= d;
	hitbox = {0.5, 1, 0.5};
}

Song::~Song() {
	// TODO Auto-generated destructor stub
}

void Song::draw() {
	Draw::phonograph(position[0], position[1], position[2], dir);

}
