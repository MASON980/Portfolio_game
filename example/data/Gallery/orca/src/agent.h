/*
 * Agent.h
 *
 *  Created on: 8 Dec 2015
 *      Author: Mason
 */

#ifndef AGENT_H_
#define AGENT_H_

// Agent is for each circle or whatever, and its movement and logic behind that movement

#include <functional>
#include <vector>
#include <map>
#include <iterator>


using namespace std;



class Agent {
protected:
	int const static INITIAL_SPEED; // All agents can start at the same speed, thats not really important
	int speed;			// Speed of the agent
	int direction;		// Direction of the agent, using 360 degrees
	int start_direction;	// direction at the start of thinking
	int turn_number;
	bool spawning;
	std::vector<int> position;		// Position of the agent
	std::vector<int> startPosition;
	std::vector<int> goalPosition;	// Position agents wants to reach


public:
	Agent();
	Agent(bool);
	virtual ~Agent();

	int getSpeed() const { return speed;}
	int getDirection() const { return direction;}


	// this sometimes doesn't work with iterators
	std::vector<int> getPosition() const {
		return position;
	}

	std::vector<int> getStart() const { return startPosition;}
	std::vector<int> getGoal() const { return goalPosition;}

	bool atGoal() const;

	void generatePositionOffScreen();
	void generatePosition();	// Generate a random position to spawn an agent at
	void generateGoal();		// Generate the goal position for the agent to try to get to

	// for testing
	void readPosition();
	void readGoal();

	void act(std::map<int, Agent>::iterator);
	void move();
	void think(std::map<int, Agent>::iterator);
	bool look(std::map<int, Agent>::iterator);
	void turn();

	bool dodge(std::vector<int>, int, int);


};

#endif /* AGENT_H_ */
