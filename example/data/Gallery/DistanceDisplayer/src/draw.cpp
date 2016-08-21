/*
 * draw.cpp
 *
 *  Created on: 21 Feb 2016
 *      Author: Mason
 */

#include "draw.h"

#include <windows.h>  // For MS Windows
#include <math.h>
#define FREEGLUT_STATIC
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <string>  // For MS Windows

// Glut init
char *myargv[1];
char v = ' ';
int myargc = 1;

const float Draw::DEG2RAD = 3.14159 / 180;
const int Draw::STARTING_HEIGHT = 720;
const int Draw::STARTING_WIDTH = 1080;

int Draw::radius = 20;
int Draw::resolution = 50;

int Draw::frame_height = Draw::STARTING_HEIGHT;
// maybe left top or something
float Draw::height = 1;
float Draw::width = 1;
float Draw::ratio  = Draw::width / Draw::height;

int Draw::type = 0;		// 0 == taxicab, 1 == euclidean

std::vector< std::vector< int > > points;



void Draw::initialiseDraw() {
	// TODO Auto-generated constructor stub
	myargv[0] = &v;
	glutInit(&myargc, myargv);
	glutInitWindowSize(Draw::STARTING_WIDTH, Draw::STARTING_HEIGHT); // Set the window's initial width & height
	glutInitWindowPosition(50, 100); // Position the window's initial top-left corner
	glutCreateWindow(
			"Distance Displayer"); // Create a window with the given title
	glutDisplayFunc(Draw::display);
	glutKeyboardFunc(Draw::key);
	glutMouseFunc(Draw::mouse);
	glutSpecialFunc(Draw::specialKey);
	//glutPassiveMotionFunc(Draw::passiveMouse);

	glutMainLoop();           // Enter the infinitely event-processing loop

}

std::vector< int > Draw::pixelToGlut(int px, int py) {				// convert pixel coord to glut coord
	// could just save the actual height and width
	double current_height = Draw::height * Draw::STARTING_HEIGHT;
	double current_width =  Draw::width * Draw::STARTING_WIDTH;

//	double dx = ((px / current_width) * 2 - 1) * World::getResolution();
//	double dy = ((1 - (py / current_height)) * 2 - 1) * World::getResolution();
	// 1, 1 is now bottom right
		// has a problem with some negatives, I think primarily negative y

	double dx = ((px / current_width)*2) * Draw::resolution;
	double dy = ((1 - (py / current_height))*2) * Draw::resolution;

	int x = dx;
	int y = dy;

	return std::vector<int> {x, y};
}

void Draw::circle(int x, int y, int id) {
	glBegin(GL_TRIANGLE_FAN);         // Each set of 4 vertices form a something

	// make it over the negative thing as well
	x = x - Draw::resolution;
	y = y - Draw::resolution;
	// change the colour depending on the status of the thing (moving or not)	-	maybe

	double fx = (x+0.5) * Draw::width / Draw::resolution;
	double fy = (y+0.5) * Draw::height / Draw::resolution;
	//float fy = (1 - y * height) / 100;
	for (int i = 0; i <= 18; i++) {
		float degInRad = i * Draw::DEG2RAD * 20;		// 10 * 36(used for how many loops) is where the 360 degrees come from
		glVertex2d(fx + cos(degInRad) * Draw::radius / 1000 * Draw::ratio,
				fy + sin(degInRad) * Draw::radius / 1000);
	}
	glEnd();

	glColor3d(0.0, 0.0, 0.0);
	glRasterPos2d(fx, fy); // line
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, id + 48);
}

void Draw::square(int x, int y) {
	glBegin(GL_TRIANGLE_FAN);         // Each set of 4 vertices form a something

	// make it over the negative thing as well
	x = x - Draw::resolution;
	y = y - Draw::resolution;
	// change the colour depending on the status of the thing (moving or not)	-	maybe

	double fx = (x+0.5) * Draw::width / Draw::resolution;
	double fy = (y+0.5) * Draw::height / Draw::resolution;
	//float fy = (1 - y * height) / 100;
	for (int i = 0; i <= 4; i++) {
		float degInRad = (i+0.5) * Draw::DEG2RAD * 90;		// 10 * 36(used for how many loops) is where the 360 degrees come from
		glVertex2d(fx + cos(degInRad) * Draw::radius / 1000 * Draw::ratio,
				fy + sin(degInRad) * Draw::radius / 1000);
	}
	glEnd();

}


void Draw::display() {			// draw all the stuff that needs to be seen, mainly just the colours
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f); // Set background color to white and opaque


	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer



	for (int i = 0; i < Draw::resolution*2; i++) {
		for (int j = 0; j < Draw::resolution*2; j++) {
			int c = closest(j, i);
			colouring(c);

			square(j, i);

		}
	}


	for (int i = 0; i < points.size(); i++) {
		colouring(i);
		glColor4f(0.4f, 0.4f, 0.4f, 1.0f); // Set background color to white and opaque

		circle(points[i][0], points[i][1], i);
	}

	glFlush();

}

void Draw::colouring(int c) {


	if (c == -1) {
		glColor4f(0.0f, 0.0f, 0.0f, 0.0f); // Set background color to white and opaque
	} else if (c == 0) {
		glColor4f(1.0f, 1.0f, 0.0f, 1.0f); // Set background color to white and opaque
	} else if (c == 1) {
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f); // Set background color to white and opaque
	} else if (c == 2) {
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to white and opaque
	} else if (c == 3) {
		glColor4f(0.0f, 1.0f, 0.0f, 1.0f); // Set background color to white and opaque
	} else if (c == 4) {
		glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // Set background color to white and opaque
	} else if (c == 5) {
		glColor4f(1.0f, 0.0f, 1.0f, 1.0f); // Set background color to white and opaque
	} else {
		int a = 9;
	}
}

int Draw::closest(int x, int y) {		// find the closest point to this coord


	int lowest_distance = Draw::resolution*4;
	int lowest = -1;
	for (int i = 0; i < points.size(); i++) {
		int dist = Draw::calculateDistance(x, y, points[i][0], points[i][1]);

		if (dist < lowest_distance) {
			lowest_distance = dist;
			lowest = i;
		}
	}

	return lowest;
}

int Draw::calculateDistance(int x, int y, int px, int py) {		// px and py are the location of the point
	if (type == 0){	// manhat
		return abs(x-px)+abs(y-py);

	} else if (type == 1) {	// euc
		// this may be a little off
		int dx = abs(x-px);
		int dy = abs(y-py);
		return sqrt(dx*dx + dy*dy);

	} else if (type == 2) {	// nothing
		return sqrt(abs(x-px)+abs(y-py));
	}

}

void Draw::mouse(int button, int state, int x, int y) {		// add a point or remove if one is already there

	if (state == 1) {
		return;
	}

	std::vector<int> xy = Draw::pixelToGlut(x, y);

	for (int i = 0; i < points.size(); i++) {
		if (points[i][0] == xy[0] &&
				points[i][1] == xy[1]) {

			points.erase(points.begin()+i);
			return;
		}

	}

	// add point
	points.push_back(xy);
}
void Draw::key(unsigned char k, int x, int y){
	if (k == ' ') {
		if (type < 2) {
			type++;
		} else {
			type = 0;
		}
	}


	// change the type of distance		--	euclid, manhattan, other (it may be a real thing, I don't know)		-- see "calculateDistance()"
	if (k == '0') {
		type = 0;
	}
	if (k == '1') {
			type = 1;
	}
	if (k == '2') {
			type = 2;
	}
	if (k == '3') {
			type = 3;
	}

	glutPostRedisplay();
}

void Draw::specialKey(int key, int x, int y) {

	if (key == GLUT_KEY_UP) {
		Draw::resolution++;
	}
	if (key == GLUT_KEY_DOWN) {
		Draw::resolution--;
		if (Draw::resolution <= 0) {
			Draw::resolution++;
		}
	}
	if (key == GLUT_KEY_LEFT) {
		Draw::radius++;

	}
	if (key == GLUT_KEY_RIGHT) {
		Draw::radius--;
		if (Draw::radius <= 0) {
			Draw::radius++;
		}
	}

	glutPostRedisplay();
}





