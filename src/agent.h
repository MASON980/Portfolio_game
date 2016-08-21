/*
 * Agent.h
 *
 *  Created on: 1 Mar 2016
 *      Author: Mason
 */

#ifndef AGENT_H_
#define AGENT_H_

#include <vector>


class Agent {


private:

	static float camera_rotation;
	static double camera_angle;
	static double camera_angle_y;
	static float looking_x;
	static float looking_y;
	static float looking_z;
	static float camera_x;
	static float camera_y;
	static float camera_z;

	static int previous_x;
	static int previous_y;

public:

	static std::vector<float> getLook();
	static std::vector<float> getStand();

	static void setLook(float, float, float);
	static void setStand(float, float, float);

	static void lookMove(int, int);
	static void locationMove(bool, float);


};

#endif /* AGENT_H_ */
