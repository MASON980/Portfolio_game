/*
 * game.cpp
 *
 *  Created on: 1 Mar 2016
 *      Author: Mason
 */

#include "game.h"
#include "../draw.h"

Game::Game() {

}

Game::Game(int x, int y, int z, char* d) {
	// TODO Auto-generated constructor stub
	position = {x, y, z};
	dir= d;
	hitbox = {0.5, 1, 0.5};

}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

void Game::draw() {
	Draw::arcade(position[0], position[1], position[2], dir);

}
