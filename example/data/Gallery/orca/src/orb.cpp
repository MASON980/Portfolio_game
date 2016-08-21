/*
 * orb.cpp
 *
 *  Created on: 17 Feb 2016
 *      Author: Mason
 */

#include "orb.h"
#include "world.h"

Orb::Orb() {
	// TODO Auto-generated constructor stub

	speed = INITIAL_SPEED;
	direction = 1;
	position = {0, 0};
	goalPosition = {0, 0};
	generatePositionOffScreen();
	generateGoal();
	startPosition = position;
	World::setSpawning(true);
	spawning = true;

	turn_number = 0;



}

Orb::~Orb() {
	// TODO Auto-generated destructor stub
}

