/*
 * World.cpp
 *
 *  Created on: 9 Dec 2015
 *      Author: Mason
 */

#include "world.h"
#include "draw.h"
#include "agent.h"
#include "orb.h"
#include <array>
#include <map>
#include <vector>
#include <iterator>
#include <utility>


const int World::AGENT_SPAWN_RATE = 5;
const int World::MAX_AGENT = 40;
int World::collisions = 0;
int World::resolution = 10000;
bool World::spawning = false;
bool World::paused = false;
int World::collisionRange = World::resolution / 50;
int World::completed = 0;
std::map<int, Agent> World::agents;	// Set of all agents in the world





void World::worldTick() { // Go through and do everything in the world

	// this was for the testing thing
/*	if (World::getAgentPopulation() < 2) {
			World::addAgent(new Agent());
	}*/

	//!World::spawning &&
	if (World::getAgentPopulation() < World::MAX_AGENT) {
		World::addAgent(new Orb());
	}

	std::vector<int> to_be_deleted;

	std::map<int, Agent>::iterator it = agents.begin();
	std::map<int, Agent>::iterator ij = agents.begin();

	for (it; it != agents.end(); ++it) {
		int i = it->first;
		ij = it;

		for (ij; ij != agents.end(); ++ij) {
			int j = ij->first;

			if (j != i) {
				if ( it->second.getPosition()[0] + World::collisionRange > ij->second.getPosition()[0] &&
						it->second.getPosition()[0] - World::collisionRange < ij->second.getPosition()[0] &&
						it->second.getPosition()[1] + World::collisionRange > ij->second.getPosition()[1] &&
						it->second.getPosition()[1] - World::collisionRange < ij->second.getPosition()[1] ) {

					World::incrementCollisionCount(i, j);
					to_be_deleted.push_back(i);
					break;
	//				to_be_deleted.push_back(j);
				}
			}
		}

		if (it->second.atGoal() ) {
	    	//agents.erase(i);
			to_be_deleted.push_back(i);
			completed++;
	    } else {
	    	ij = it;
	    	it->second.act(ij);
	    }
	}

	World::deleteAgents(to_be_deleted);
	Draw::incrementFrames();
}

std::vector<std::vector< int >> World::getAgentPositions(){		// I would rather it be a vector of arrays
	std::vector<std::vector< int >> v;
	if (agents.empty() == true) {
		return v;
	}
	std::map<int, Agent>::iterator it = agents.begin();
	for (it; it != agents.end(); it++) {
		v.push_back(it->second.getPosition());
	}
	return v;
}


void World::incrementCollisionCount(int i, int j) {
	Agent v = agents[i];
//	Agent d = agents[j];


	if (v.getPosition()[0] > resolution || v.getPosition()[0] < 0 ||
			v.getPosition()[1] > resolution || v.getPosition()[1] < 0 ) {
		collisions = collisions + 1000;												// if they collide offscreen - meaning they were spawned on top of each other

	} else {
		collisions++;

	}

	if (collisions >= 999999) {
		collisions = 0;
	}
}

void World::deleteAgents(std::vector<int> d) {
	for (int i = 0; i < d.size(); i++) {
		agents.erase(d[i]);
	}
}


void World::addAgent(Agent* a) {			// I think with the hash thing I could just collect the agent I need with the hash thing
	for (int i = 0; i < agents.size(); i++) {
		if (agents.count(i) == 0) {
			agents[i] = NULL;
			agents[i] = *a;
			return;
		}
	}
	agents[agents.size()] = NULL;
	agents[agents.size()-1] = *a;
}

void World::mouse(int button, int state, int x, int y) {

}
void World::key(unsigned char k, int x, int y){
	if (k == ' ') {
		paused = !paused;
	}
	if (k == 'z') {
		Draw::setHovering(false);
		Draw::h = false;
		Draw::hh = false;
	}
	if (k == 27) {
		//exit program
	}
}

void World::passiveMouse(int x, int y) {
	//x = 0, y = 0 	is up the top  left
		// and its done in pixels

	std::vector<int> xy = Draw::pixelToGlut(x, y);

	std::map<int, Agent>::iterator it = agents.begin();

	for (it; it != agents.end(); ++it) {						// hovering over an agent
		if (it->second.getPosition()[0] + World::collisionRange > xy[0] &&
				it->second.getPosition()[0] - World::collisionRange < xy[0] &&

				it->second.getPosition()[1] + World::collisionRange > xy[1] &&
				it->second.getPosition()[1] - World::collisionRange < xy[1] ) {

			// debugging
			int xxx = it->second.getPosition()[0];
			int yyy = it->second.getPosition()[1];
			int x = xy[0];
			int y = xy[1];


			Draw::info(it->second, xy[0], xy[1]);
			Draw::h = true;
			Draw::setHovering(true);
			break;

		}
		if (!paused) {
			Draw::setHovering(false);
			Draw::h = false;
			Draw::hh = false;

		}
	}
}



