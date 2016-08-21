/*
 * world.h
 *
 *  Created on: 9 Dec 2015
 *      Author: Mason
 */

#ifndef WORLD_H_
#define WORLD_H_

#include "agent.h"
#include <array>
#include <map>
#include <vector>
// See if I can remove this includes

// World, holds all the agents and various performance measuring things

class World {
private:
	const static int AGENT_SPAWN_RATE;
	const static int MAX_AGENT;
	static std::map<int, Agent> agents;	// Set of all agents in the world
	static int collisions;
	static int resolution;
	static int collisionRange;
	static int completed;
	static bool spawning;
	static bool paused;
public:
	static void worldTick(); // Go through and do everything in the world, agent logic then draw

	static std::map<int, Agent> getAgents() { return agents;}
	static std::vector<std::vector< int > > getAgentPositions();		// I would rather it be a vector of arrays

	static void incrementCollisionCount(int, int);
	static void deleteAgents(std::vector<int>);

	static int getAgentPopulation() { return agents.size();}
	static int getResolution() { return World::resolution;}
	static int getCollisionCount() { return collisions;}
	static int getCompleted() { return completed;}
	static int getCollisionRange() { return collisionRange;}
	static void setSpawning(bool b) { spawning = b;}
	static bool getPaused() { return paused;}


	static void addAgent(Agent*);

	static void mouse(int, int, int , int);
	static void key(unsigned char, int , int);
	static void passiveMouse(int, int);


};


#endif /* WORLD_H_ */
