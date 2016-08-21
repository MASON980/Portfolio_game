/*
 * agent.cpp
 *
 *  Created on: 8 Dec 2015
 *      Author: Mason
 */

#include "agent.h"
#include "world.h"
#include "draw.h"
#include <cstdlib>
#include <map>
#include <functional>
#include <math.h>

// Position and goal position will be randomly generated then the agent will determine how to get there (which direction to go)
// Just 2D at the moment

// Check all the other agents calculating whether based upon their position, direction and speed whether they will hit
// Skip over ones that definitely won't (position with direction don't intersect with the path being taken)
// Maybe try and estimate the size of the turn needed
// Maybe only check ones within a certain range



//int const Agent::INITIAL_SPEED = World::getResolution() / 5000; // All agents can start at the same speed, thats not really important
int const Agent::INITIAL_SPEED = 11;

int speed;			// Speed of the agent
int direction;		// Direction of the agent, using 360 degrees
int turn_number;
int start_direction;	// the start of the think
std::vector<int> position(2);		// Position of the agent
std::vector<int> startPosition(2);		// Starting position of the agent
std::vector<int> goalPosition (2);	// Position agents wants to reach
bool spawning;

std::vector<std::vector<int>> test_goalPosition = {{9000, 9000}, {1, 1000}};
std::vector<std::vector<int>> test_position = {{1, 1}, {8000, 9000}};
int iter = 0;

Agent::Agent() {
	// TODO Auto-generated constructor stub


	/*		// test thing
	iter++;
	if (iter >= test_position.size()) {
		iter = 0;
	}
*/

}

// blank agent
Agent::Agent(bool f) {
// this is being used for 	ag		in draw which needs to remember the details of the one being hovered over but a blank is used for compile (or something)
}

Agent::~Agent() {
	// TODO Auto-generated destructor stub
}

void Agent::generatePositionOffScreen() {			// spawn off-screen

	// make them spawn off screen
	int a = World::getResolution();
	int r = a*2  + World::getCollisionRange()*4;
	int n = rand() % (a*2);

/*		// if you want the offscreen random
	int r = rand() % (a / 5);
	r = r - a/10;
	if (r > 0) {
		r = r + a*2 + World::getCollisionRange()*2;
	} else {
		r = r - World::getCollisionRange()*2;
	}
*/

	// choose whether x or y will be off screen
	if (rand() %2 == 1) {
		r = -r;
	}
	if (rand() % 2 == 1) {
		this->position[0] = r;
		this->position[1] = n;

	} else {
		this->position[0] = n;
		this->position[1] = r;

	}

}

void Agent::generatePosition() {
	this->position[0] = rand() % (World::getResolution() * 2);
	this->position[1] = rand() % (World::getResolution() * 2);
}

void Agent::generateGoal() {
	this->goalPosition[0] = rand() % (World::getResolution() * 2);
	this->goalPosition[1] = rand() % (World::getResolution() * 2);
}

// for testing
void Agent::readPosition() {
	this->position[0] = test_position[iter][0];
	this->position[1] = test_position[iter][1];
}
void Agent::readGoal() {
	this->goalPosition[0] = test_goalPosition[iter][0];
	this->goalPosition[1] = test_goalPosition[iter][1];
}

bool Agent::atGoal() const {	// is the agent at the goal?
	if (position == goalPosition) {
		return true;
	}
	return false;
}

void Agent::act(std::map<int, Agent>::iterator it) {		// the agent acts

	turn_number++;
	int position_goalPosition = position[0] - goalPosition[0];
	int position_goalPosition_one = position[1] - goalPosition[1];

	if (spawning) {
		if (position[0] > 0 && position[0] < World::getResolution()*2 && position[1] > 0 && position[1] < World::getResolution()*2) {
			World::setSpawning(false);
			spawning = false;
		}
	}

	// close enough to goal
	if (position_goalPosition < World::getCollisionRange() && position_goalPosition_one < World::getCollisionRange()) {
		position[0] = goalPosition[0];
		position[1] = goalPosition[1];
		if (spawning) {
			World::setSpawning(false);
			spawning = false;
		}
		return;

	}

	if (turn_number >= 30) {			// think every 30 turns
		if (speed == 0) {
			speed++;
		}

		double angle = atan2(-position_goalPosition_one, -position_goalPosition);		// it likes negatives, its because 0,0 is bottom left

		direction = angle / Draw::DEG2RAD;
		start_direction = direction;

		Agent::think(it);
		turn_number = 0;
	}
	Agent::move();

}

void Agent::move() {	// Move the agent according to the direction and speed
	if (speed == 0) {
		return;
	}
	double dir =  direction * Draw::DEG2RAD;
	double x = cos(dir) * speed;
	double y = sin(dir) * speed;
	position[0] = position[0] + x;
	position[1] = position[1] + y;

}

// stopping isn't good because
// doing something based on only one thing isn't good
// when checking if something will hit consider the distance this wants to move	-- others might have trouble knowing though

bool Agent::look(std::map<int, Agent>::iterator it) {	// look at the other agents and see where they are and their heading
	if (speed == 0) {
		return true;
	}

	// i = 0; i < agents.size	 works next to perfectly in misses at least, they get stuck
					//i < World::getAgents().size()
					// i < id

	std::map<int, Agent> agents = World::getAgents();

	//	for (int i = id; i < agents.size(); i++) {	// index OR World::getAgents().size()

	for (it = agents.begin(); it != agents.end(); ++it) {

		std::vector<int> pos = it->second.getPosition();
		if (pos == position) {

		} else {
			int dir = it->second.getDirection();
			int sp = it->second.getSpeed();

			bool b = dodge(pos, dir, sp);
			if (!b) {
				Agent::turn();
				return false;
			}
		}
	}

	return true;

}

bool Agent::dodge(std::vector<int> pos, int dir, int sp) {

	// differentiate between one this is going to run into and one that are going to run into this

	if (sp == 0) {
		int pos_position = pos[0] - position[0];
		int pos_position_one = pos[1] - position[1];

		if (sqrt(pos_position*pos_position + pos_position_one*pos_position_one) > (speed+sp) * 100 ) {
			// far away

		} else {
			// if it isn't moving

			// find if moving in the same direction as the pos - then turn
			float degInRad = direction * Draw::DEG2RAD;
			float distance = sqrt(pos_position*pos_position + pos_position_one*pos_position_one);
			float leeway = distance/(speed * 100);		// leeway between 0 and 1	-- closer to the pos the easier to hit
			if (pos_position / (double) pos_position_one >= tan(degInRad) * leeway &&
					pos_position / (double) pos_position_one <= tan(degInRad) * (1/leeway)	&&
					distance < speed * 20) {

				return false;
			}
		}

	} else {
		int pos_position = pos[0] - position[0];
		int pos_position_one = pos[1] - position[1];

		int speed_two = speed + 180;
		if (speed_two > 180) {
			speed_two = speed_two - 360;
		}
		// make some method that checks whether its out of range

		if (sqrt(pos_position*pos_position + pos_position_one*pos_position_one) > (speed+sp) * 100  ) {
			// far away

		} else {
			std::vector<int> endPos(2);
			std::vector<int> gPos(2);
			int r = World::getCollisionRange() * 4;

			float degInRad = dir * Draw::DEG2RAD;

			endPos[0] = pos[0] + cos(degInRad) * World::getResolution() * Draw::ratio;
			endPos[1] = pos[1] + sin(degInRad) * World::getResolution();

			// x positions
			int endPos_position = endPos[0] - position[0];
			int endPos_goalPosition = endPos[0] - goalPosition[0];
			int pos_goalPosition = pos[0] - goalPosition[0];

			// y positions
			int endPos_position_one = endPos[1] - position[1];
			int endPos_goalPosition_one = endPos[1] - goalPosition[1];
			int pos_goalPosition_one = pos[1] - goalPosition[1];


			float goalInRad = direction* Draw::DEG2RAD;
			// rather than goal make it in the current direction
			gPos[0] = position[0] + cos(goalInRad) *  (World::getResolution() / 10) * Draw::ratio;
			gPos[1] = position[1] + sin(goalInRad) * (World::getResolution() / 10);
			int pos_gPos = pos[0] - gPos[0];
			int pos_gPos_one = pos[1] - gPos[1];
			int endPos_gPos = endPos[0] - gPos[0];
			int endPos_gPos_one = endPos[1] - gPos[1];

			// if both the pos and end pos are both on one side of this
			if (endPos_position - r > 0 && pos_position - r > 0 &&
					endPos_gPos - r > 0 && pos_gPos - r > 0 ) {

			} else if (endPos_position + r < 0 && pos_position + r < 0 &&
					endPos_gPos + r < 0 && pos_gPos + r < 0 ) {

			} else if (endPos_position_one + r < 0 && pos_position_one + r < 0 &&
					endPos_gPos_one + r < 0 && pos_gPos_one + r < 0 ) {

			} else if (endPos_position_one - r > 0 && pos_position_one - r > 0 &&
					endPos_gPos_one - r > 0 && pos_gPos_one - r > 0 ) {

			} else {

				// it's not really a hypotenuse. well it might be, the triangle isn't right angled
				double hypotenuse = sqrt(pos_position *pos_position + pos_position_one * pos_position_one);
				double angle_base = atan2(pos_position_one, pos_position);		// it likes negatives

				int angle_base_i = angle_base / Draw::DEG2RAD + 180;
				int d = direction + 180;
				dir = dir + 180;
				// these need to be contextualized by above
				int angle_adj_i;
				bool neg = false;
				// get the smaller angle between direction and angle_base_i
				angle_adj_i = (angle_base_i) - (d);
				if (angle_adj_i < 0) {
					neg = true;
				}

				angle_adj_i = abs(angle_adj_i);
				/// pay attention to if its negative
						// opp needs to be the opposite
				if (angle_adj_i > 180) {
					angle_adj_i = 360 - angle_adj_i;
					neg = !neg;
				}



				int angle_base_i_opp = angle_base_i + 180;
				if (angle_base_i_opp > 360) {
					angle_base_i_opp = angle_base_i_opp - 360;
				}
				int angle_opp_i;

				// get the smaller angle between dir and angle_base_i_opp
				if (neg) {
					angle_opp_i = (angle_base_i_opp) - (dir);
					if (angle_opp_i > 180) {
						angle_opp_i = 360 - abs(angle_opp_i);
					}
				} else {
					angle_opp_i = (dir) - (angle_base_i_opp);
					if (angle_opp_i < -180) {
						angle_opp_i = 360 - abs(angle_opp_i);
					}
				}

				float angle_adj = angle_adj_i * Draw::DEG2RAD;
				float angle_opp = angle_opp_i * Draw::DEG2RAD;

				int angle_hyp_i = 0;
				if (angle_opp_i > 0) {
					angle_hyp_i = 180 - (angle_adj_i + angle_opp_i);

				} else if (angle_adj_i < 90 && angle_opp_i < 90) {
					// they won't collide on a thin path but they are wide
						// < 90 is that they are both getting closer to each other
							// may need to make it <180 if one is going father than the other

					double speed_ratio = sp / (double) speed;
					double dist_ratio = speed_ratio * cos(angle_adj) * cos(angle_opp);

					// one is this and two is [i]
					float adj_two = hypotenuse / (dist_ratio + 1);
					float adj_one = hypotenuse - adj_two;

					if (adj_one <= 0) {

					} else {
						int opp_one = tan(angle_adj) * adj_one;
						int opp_two = tan(angle_opp) * adj_two;

						if (abs(opp_one) + abs(opp_two) < r) {
							// they are going to graze
							Agent::turn();
							return false;
						}
					}


				}

				if (angle_hyp_i <= 0) {
					// there is no collision point
				} else {

					float angle_hyp = angle_hyp_i * Draw::DEG2RAD;

					double connection = hypotenuse / sin(angle_hyp);
					int side_adj = connection * sin(angle_opp);
					int side_opp = connection * sin(angle_adj);

					// distance that will be the hypotenuse of a right-angled triangle that has angle_hyp and an angle and
						// r*2 as the opposite	--	it is the distance in which the two agents can hit each other
					int unsafe = r / sin(angle_hyp);


					float f = side_opp / (float)sp;
					float fs = side_adj/(float)speed;
					int a = abs((int)fs - (int)f);

					int lesser = speed;
					if (speed > sp) {
						lesser = sp;
					}

					if (a <= unsafe/lesser ) {
						// they will be close to each other
							// I could probably estimate this just from the angles
						return false;
					}
					std::vector<int> collision(2);
					collision[0] = pos[0] + cos(angle_adj) * side_adj * Draw::ratio;
					collision[1] = pos[1] + sin(angle_adj) * side_adj;

					// they wont remember next turn and we will be stuck alternating

				}
// trying to dodge one which causes it to move in the way of another, it doesn't know that the next think will have it incapable of escaping
			}

		}

	}
	return true;
}

void Agent::think(std::map<int, Agent>::iterator it) {	// the agent thinks
	bool t = true;
	t = look(it);
	if (t) {
		if (speed < Agent::INITIAL_SPEED) {
			speed++;
		}
	}
	while (!t) {
		t = look(it);
	}
}

void Agent::turn() {
	// check the direction the offending agent is moving in so you don't go the same way

	direction = direction + 60;
	if (direction >= 180) {		// the range is -180, +180, or maybe 170 or something
		direction = direction - 360;
		if (direction == 0) {
			direction++;
			start_direction++;
		}
	}
	if (direction == start_direction) {
		// the idea is not to stop because of using the int i = id => max~
		speed = speed - 5;

		if (speed <= 0) {
			speed = 0;
		}

	}
}


