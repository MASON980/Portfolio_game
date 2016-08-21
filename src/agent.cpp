/*
 * Agent.cpp
 *
 *  Created on: 1 Mar 2016
 *      Author: Mason
 */

#include "Agent.h"

#include "draw.h"
#include "world.h"

#include <stdlib.h>
#include "math.h"
#include <windows.h>  // For MS Windows
#define FREEGLUT_STATIC
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h


float Agent::camera_rotation = 0.0f;
double Agent::camera_angle = 0;
double Agent::camera_angle_y = 0;

float Agent::looking_x = 0;
float Agent::looking_y = 0;
float Agent::looking_z = -1;
float Agent::camera_x = 0;
float Agent::camera_y = 1;
float Agent::camera_z = 5;

int Agent::previous_x = 0;
int Agent::previous_y = 0;


std::vector<float> Agent::getLook() {
	return {looking_x, looking_y, looking_z};
}

std::vector<float> Agent::getStand() {
	return {camera_x, camera_y, camera_z};
}

void Agent::setLook(float x, float y, float z) {
	looking_x = x;
	looking_y = y;
	looking_z = z;

	camera_rotation = 0.0f;
	camera_angle = 0;
	camera_angle_y = 0;
};
void Agent::setStand(float x, float y, float z) {
	camera_x = x;
	camera_y = y;
	camera_z = z;

};

void Agent::lookMove(int x, int y) {			// move the camera's direction based upon the new x,y coords (which change based upon the cursor position), then reset the cursor position

	double dx = (x - previous_x)/10;
	double dy = (previous_y - y)/10;

	if (abs(dx) <= 1 && abs(dy) <= 1) {
		return;
	}

	double move_x = (dx)/100;
	double move_y = (dy)/100;

	if (dx < 0) {
	//	move = -move;
	}

	camera_angle +=  move_x;

	looking_x = sin(camera_angle);
	looking_z = -cos(camera_angle);

	camera_angle_y +=  move_y;
	looking_y = sin(camera_angle_y);

	if (camera_angle_y > 1.2) {
		camera_angle_y = 1.2;
	} else if (camera_angle_y < -1) {
		camera_angle_y = -1;
	}

	float reset = 360 * Draw::DEG2RAD;
	if (camera_angle >= reset) {
		camera_angle -= reset;
	} else if (camera_angle <= -reset) {
		camera_angle += reset;
	}

	std::vector<int> c = {x, y};


	if (abs(x) > 10 || abs(y) > 10) {
		c = Draw::getCentre();
		//SetCursorPos(c[0], c[1]);
		glutWarpPointer(c[0], c[1]);
	}

	previous_x = c[0];
	previous_y = c[1];

}

void Agent::locationMove(bool b, float f) {			// move the camera		teleport to other side if you go through a wall
	// f is the amount to move, b is true if moving forward/backward and false if strafing
	if (b) {
		camera_x += looking_x * f;
		camera_z += looking_z * f;
	} else {
		double angle = camera_angle + (90*Draw::DEG2RAD);

		float x = sin(angle);
		float z = -cos(angle);

		camera_x += x * f;
		camera_z += z * f;
	}


	// disorientating invisible walls
	if (camera_x > World::RESOLUTION[0]) {
		camera_x = -World::RESOLUTION[0];
	} else if (camera_x < -World::RESOLUTION[0]) {
		camera_x = World::RESOLUTION[0];
	}
	if (camera_z > World::RESOLUTION[2]) {
		camera_z = -World::RESOLUTION[2];
	} else if (camera_z < -World::RESOLUTION[2]) {
		camera_z = World::RESOLUTION[2];
	}

}
