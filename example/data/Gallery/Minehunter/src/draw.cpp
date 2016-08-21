/*
 * Draw.cpp
 *
 *  Created on: 8 Dec 2015
 *      Author: Mason
 */

#include "draw.h"

#include "world.h"
#include <windows.h>  // For MS Windows
#include <math.h>

#define FREEGLUT_STATIC
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h


#include <string>  // For MS Windows
#include <thread>
#include <stdio.h>		// sprintf

int const static TICK = 20;

// Glut init
char *myargv[1];
char v = ' ';
int myargc = 1;

const float Draw::DEG2RAD = 3.14159 / 180;
const int Draw::RADIUS = 40;
const int Draw::STARTING_HEIGHT = 720;
const int Draw::STARTING_WIDTH = 1080;


int Draw::frames = 0;
double Draw::line = 1;

int Draw::frame_height = Draw::STARTING_HEIGHT;
// maybe left top or something
float Draw::height = Draw::STARTING_HEIGHT / Draw::STARTING_WIDTH;
float Draw::width = 1;
float Draw::ratio  = Draw::width / Draw::height;


void Draw::square(int x, int y, int n) {
	glBegin(GL_TRIANGLE_FAN);         // Each set of 4 vertices form a something

	// make it over the negative thing as well
	x = x - World::COLUMNS;
	y = y - World::ROWS;
	// change the colour depending on the status of the thing (moving or not)	-	maybe

	double fx = (x+0.5) * Draw::width / World::COLUMNS;
	double fy = (y+0.5) * Draw::height / World::ROWS;
	//float fy = (1 - y * height) / 100;
	for (int i = 0; i <= 4; i++) {
		float degInRad = (i+0.5) * Draw::DEG2RAD * 90;		// 10 * 36(used for how many loops) is where the 360 degrees come from
		glVertex2d(fx + cos(degInRad) * Draw::RADIUS / 750 * Draw::ratio,
				fy + sin(degInRad) * Draw::RADIUS / 750);
	}
	glEnd();

	if (n >= 0) {
		glColor3d(0.0, 0.0, 0.0);
		glRasterPos2d(fx-0.01, fy-0.02); // line
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, n + 48);
	}


}


void Draw::display() {

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Set background color to white and opaque

	if (World::won) {
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	}

	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

	std::vector <std::vector <int> > map = World::getMap();

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			colouring(map[i][j]);
			square(i, j, map[i][j]);

		}
	}



	glFlush();  // Render now

}


void Draw::colouring(int c) {

	if (c == -2) {
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to white and opaque
	} else if (c == -1) {
		glColor4f(0.4f, 0.4f, 0.4f, 1.0f); // Set background color to white and opaque
	} else if (c == 0) {
		glColor4f(0.1f, 0.1f, 0.1f, 1.0f); // Set background color to white and opaque
	} else if (c == 1) {
		glColor4f(1.0f, 0.2f, 0.2f, 1.0f); // Set background color to white and opaque
	} else if (c == 2) {
		glColor4f(1.0f, 0.4f, 1.0f, 1.0f); // Set background color to white and opaque
	} else if (c == 3) {
		glColor4f(0.0f, 1.0f, 0.0f, 1.0f); // Set background color to white and opaque
	} else if (c == 4) {
		glColor4f(0.0f, 1.0f, 1.0f, 1.0f); // Set background color to white and opaque
	} else if (c == 5) {
		glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // Set background color to white and opaque
	} else if (c == 6) {
		glColor4f(0.5f, 0.5f, 1.0f, 1.0f); // Set background color to white and opaque
	} else if (c == 7) {
		glColor4f(1.0f, 0.5f, 0.5f, 1.0f); // Set background color to white and opaque
	} else if (c == 8) {
		glColor4f(0.5f, 1.0f, 0.5f, 1.0f); // Set background color to white and opaque
	}
}



void Draw::reshape(int new_width, int new_height) {
	Draw::height = (float) new_height / Draw::STARTING_HEIGHT;
	Draw::width =  (float) new_width / Draw::STARTING_WIDTH;
	Draw::ratio = Draw::width / Draw::height;
	Draw::frame_height = new_height;

}

void Draw::initialiseDraw() {

	World::initMap();


	// TODO Auto-generated constructor stub
	myargv[0] = &v;
	glutInit(&myargc, myargv);
	glutInitWindowSize(Draw::STARTING_WIDTH, Draw::STARTING_HEIGHT); // Set the window's initial width & height
	glutInitWindowPosition(50, 100); // Position the window's initial top-left corner
	glutCreateWindow(
			"Minehunter?"); // Create a window with the given title
	glutDisplayFunc(Draw::display);
	glutReshapeFunc(Draw::reshape);
	//glutKeyboardFunc(World::key);
	glutMouseFunc(World::mouse);
	//glutPassiveMotionFunc(World::passiveMouse);
	//glutSpecialFunc(World::specialKey);

	glutMainLoop();           // Enter the infinitely event-processing loop

}

std::vector< int > Draw::pixelToGlut(int px, int py) {			// convert pixel coord to glut coord
	// could just save the actual height and width
	double current_height = Draw::height * Draw::STARTING_HEIGHT;
	double current_width =  Draw::width * Draw::STARTING_WIDTH;

//	double dx = ((px / current_width) * 2 - 1) * World::getResolution();
//	double dy = ((1 - (py / current_height)) * 2 - 1) * World::getResolution();
	// 1, 1 is now bottom right
		// has a problem with some negatives, I think primarily negative y

	double dx = ((px / current_width) * 2) * World::COLUMNS;
	double dy = ((1 - (py / current_height)) * 2) * World::ROWS;

	int x = dx;
	int y = dy;

	return std::vector<int> {x, y};
}


