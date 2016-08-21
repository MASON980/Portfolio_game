/*
 * Draw.cpp
 *
 *  Created on: 8 Dec 2015
 *      Author: Mason
 */

#include "draw.h"
#include "agent.h"
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
const float Draw::RADIUS = 0.02;
const int Draw::STARTING_HEIGHT = 720;
const int Draw::STARTING_WIDTH = 1080;

long Draw::prev = 0;
int Draw::hold = 0;
int Draw::f = 0;

int Draw::frames = 0;
double Draw::line = 1;


Agent Draw::ag = new Agent(false);	// the agent being hovered over
Agent Draw::agg = new Agent(false);
bool Draw::hovering = false;


int Draw::frame_height = Draw::STARTING_HEIGHT;
// maybe left top or something
float Draw::height = 1;
float Draw::width = 1;
float Draw::ratio  = Draw::width / Draw::height;


void Draw::circle(int x, int y, int id) {
	glBegin(GL_TRIANGLE_FAN);         // Each set of 4 vertices form a something

	// make it over the negative thing as well
	x = x - World::getResolution();
	y = y - World::getResolution();
	// change the colour depending on the status of the thing (moving or not)	-	maybe

	double  fx = x * Draw::width / World::getResolution();
	double fy = y * Draw::height / World::getResolution();
	//float fy = (1 - y * height) / 100;
	for (int i = 0; i <= 18; i++) {
		float degInRad = i * Draw::DEG2RAD * 20;		// 10 * 36(used for how many loops) is where the 360 degrees come from
		glVertex2d(fx + cos(degInRad) * Draw::RADIUS * Draw::ratio,
				fy + sin(degInRad) * Draw::RADIUS);
	}
	glEnd();

	glColor3d(0.0, 0.0, 0.0);
	glRasterPos2d(fx, fy); // line
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, id + 48);
}

void Draw::agents() {			// draw every agent
	std::map< int, Agent > agents = World::getAgents();

	std::map<int, Agent>::iterator it = agents.begin();
	for (it; it != agents.end(); it++) {

	glColor3f(1.0f, 1.0f, 0.0f); // Red

	circle(it->second.getPosition()[0], it->second.getPosition()[1], it->first);


	// draw all their directions
	if (World::getPaused()) {
		glColor3f(1.0f, 0.3f, 0.3f); // Red
		glLineWidth(2.5);

		int px = it->second.getPosition()[0]- World::getResolution();
		int py = it->second.getPosition()[1]- World::getResolution();
		double  dx = px * Draw::width / World::getResolution();
		double dy = py * Draw::height / World::getResolution();

		int d = it->second.getDirection();

		int x = (cos(d * Draw::DEG2RAD ) * 10000 + px);
		int y = (sin(d * Draw::DEG2RAD ) * 10000 + py);

		double  fx = x * Draw::width / World::getResolution();
		double fy = y * Draw::height / World::getResolution();

		glBegin(GL_LINES);
			glVertex2d(dx, dy);
			glVertex2d(fx,fy);
		glEnd();
	}

	}

}

void Draw::stringWithInt(std::string str, int i) {		// append an int to a string then draw it
	Draw::line = Draw::line + 0.05;

	char* c = new char;
	sprintf(c,"%d",i);
	std::string s(c);
	std::string text = str;
	if (i != NULL) {
		text = text + ": " + s;

	}

	glColor3d(0.0, 0.0, 0.0);
	glRasterPos2d(0.01, 1 - line); // line
	for (int i = 0; i < text.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text.at(i));
	}
	// 48 == 0
	// 65 == A
}

void Draw::display() {
	Draw::line = 0.05;

	glClearColor(0.8f, 1.0f, 1.0f, 1.0f); // Set background color to white and opaque


	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

	Draw::agents();
	Draw::stringWithInt("Collisions", World::getCollisionCount());
		// adding 1000 whenever they hit off screen/ are spawned into each other

	Draw::stringWithInt("Frames", Draw::frames);
	Draw::stringWithInt("Completed", World::getCompleted());
	Draw::stringWithInt("Framerate", Draw::hold);
	Draw::f++;

	Draw::pane();
	// the panes stays even if moving when not paused

	if (World::getPaused()) {
		Draw::stringWithInt("Paused", NULL);
	} else {
		World::worldTick();
	}

	glFlush();  // Render now

	// not very nice
	long now = time(0);
	if (Draw::prev + 1 < now) {
		Draw::prev = now;
		Draw::hold = Draw::f;
		Draw::f = 0;

	}


}

void Draw::pane() {
	if (!Draw::hovering) {
		return;
	}
	Draw::info(Draw::ag, 0, 0);
}

void Draw::reshape(int new_width, int new_height) {
	Draw::height = (float) new_height / Draw::STARTING_HEIGHT;
	Draw::width =  (float) new_width / Draw::STARTING_WIDTH;
	Draw::ratio = Draw::width / Draw::height;
	Draw::frame_height = new_height;

}
bool Draw::h = false;
bool Draw::hh = false;

void Draw::info(Agent a, int x, int y) {			// write some information about the agent parameter
	int xxx = 0;
	int yyy = 0;


										// if two agents are selected calculate when they will hit given the current trajectories of both of them
	// not very neat
	if (h) {
		// it's not really a hypotenuse
		std::vector<int> pos = a.getPosition();
		std::vector<int> position = ag.getPosition();

		if (pos != position || hh) {
			if (pos != position) {
				agg = a;
			}
			hh = true;
			pos = agg.getPosition();

			int dir = agg.getDirection() + 180;
			int direction = ag.getDirection() + 180;

			int pos_position = pos[0] - position[0];
			int pos_position_one = pos[1] - position[1];

			double hypotenuse = sqrt(pos_position *pos_position + pos_position_one * pos_position_one);
			double angle_base = atan2(pos_position_one, pos_position);		// it likes negatives

			int angle_base_i = angle_base / Draw::DEG2RAD + 180;
			// these need to be contextualized by above
			int angle_adj_i;

			bool neg = false;
			// get the smaller angle between direction and angle_base_i
			angle_adj_i = (angle_base_i) - (direction);
			if (angle_adj_i < 0) {
				neg = true;
			}

			angle_adj_i = abs(angle_adj_i);
			/// pay attention to if its nehative
					// opp needs to be the opposite
			if (angle_adj_i > 180) {
				angle_adj_i = 360 - angle_adj_i;
				neg = !neg;
			}

			// the problem is when the new one is up left of the orig
				// and orig is going down left

			// left up above
			// right 		 below

				// maybe 270
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

			/*
			down is -90
			left is 180/-180
			right is 0
			up is 90
			 */
			int sp = agg.getSpeed();
			int speed = ag.getSpeed();

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

				float opp_one = tan(angle_adj) * adj_one;
				float opp_two = tan(angle_opp) * adj_two;

				if (opp_one + opp_two < 600) {
					// they are going to graze

				}


			}

			if (angle_hyp_i <= 0) {
								// there is no collision point
			} else {

								// draw when they will hit to the screen as a triangle
				float angle_adj = angle_adj_i * Draw::DEG2RAD;
				float angle_opp = angle_opp_i * Draw::DEG2RAD;
				float angle_hyp = angle_hyp_i * Draw::DEG2RAD;

				double connection = hypotenuse / sin(angle_hyp);
				int side_opp = connection * sin(angle_adj);
				int side_adj = connection * sin(angle_opp);

				xxx = (cos((direction-180)*Draw::DEG2RAD ) * side_adj + position[0]);
				yyy = (sin((direction-180)*Draw::DEG2RAD ) *side_adj + position[1]);

				double p = xxx * Draw::width / World::getResolution();
				double pp = yyy * Draw::height / World::getResolution();


				glColor3d(0.7, 0.7, 0.7);
				glBegin(GL_TRIANGLES);         // Each set of 4 vertices form a something

				glVertex2d(p-1, pp-1);

				double fx = position[0] * Draw::width / World::getResolution();
				double fy = position[1]  * Draw::height / World::getResolution();
				glVertex2d(fx-1, fy-1);

				double dx = pos[0]   * Draw::width /  World::getResolution();
				double dy = pos[1]   * Draw::height / World::getResolution();
				glVertex2d(dx-1, dy-1);

				glEnd();

			}
		}
	} else {
		Draw::ag = a;
	}


	// write some information about the agent to the screen

	// show current
	int xx = a.getPosition()[0];
	int yy = a.getPosition()[1];
	char* cx = new char;
	sprintf(cx,"%d",xx);
	std::string sx(cx);

	char* cy = new char;
	sprintf(cy,"%d",yy);
	std::string sy(cy);

	std::string text = "This agent is at position x:" + sx + ", y:" + sy;

	double  fx = x * Draw::width / World::getResolution();					// this probably isn't the width but the radius or something
	double fy = y * Draw::height / World::getResolution();

	glColor3d(0.0, 0.0, 0.0);
	glRasterPos2d(fx, fy);
	for (int i = 0; i < text.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text.at(i));
	}


	// show start
	xx = a.getStart()[0];
	yy = a.getStart()[1];
	cx = new char;
	sprintf(cx,"%d",xx);
	std::string startx(cx);

	cy = new char;
	sprintf(cy,"%d",yy);
	std::string starty(cy);

	text = "It started at x:" + startx + ", y:"  + starty;

	glColor3d(0.0, 0.0, 0.0);
	glRasterPos2d(fx, fy - 0.05);
	for (int i = 0; i < text.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text.at(i));
	}

	// show direction
	int d = a.getDirection();

	char* c = new char;
	sprintf(c,"%d",d);
	std::string sd(c);

	text = "It's direction is "+ sd;

	glColor3d(0.0, 0.0, 0.0);
	glRasterPos2d(fx, fy - 0.10);
	for (int i = 0; i < text.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text.at(i));
	}

	// show speed
	d = a.getSpeed();

	c = new char;
	sprintf(c,"%d",d);
	std::string ss(c);

	text = "It's speed is "+ ss;

	glColor3d(0.0, 0.0, 0.0);
	glRasterPos2d(fx, fy - 0.15);
	for (int i = 0; i < text.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text.at(i));
	}

	// show goal
	glColor3f(1.0f, 1.0f, 0.0f); // Yellow		--	goal
	circle(a.getGoal()[0], a.getGoal()[1], -68);

	glColor3f(0.0f, 0.0f, 1.0f);
	circle(a.getPosition()[0], a.getPosition()[1], -68);

}

void Draw::string(std::string text, int x, int y) {

	double  fx = x * Draw::width / World::getResolution();					// this probably isn't the width but the radius or something
	double fy = y * Draw::height / World::getResolution();


	//double  fx = x * Draw::width / Draw::STARTING_WIDTH;					// this probably isn't the width but the radius or something
	//double fy = (Draw::STARTING_HEIGHT - y) * Draw::height / Draw::STARTING_HEIGHT;

	glColor3d(0.0, 0.0, 0.0);
	glRasterPos2d(fx, fy);
	for (int i = 0; i < text.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text.at(i));
	}

}

void Draw::initialiseDraw() {
	// TODO Auto-generated constructor stub
	myargv[0] = &v;
	glutInit(&myargc, myargv);
	glutInitWindowSize(Draw::STARTING_WIDTH, Draw::STARTING_HEIGHT); // Set the window's initial width & height
	glutInitWindowPosition(50, 100); // Position the window's initial top-left corner
	glutCreateWindow(
			"Collision Avoidance - Optimal Reciprocal Collision Avoidance?"); // Create a window with the given title
	glutDisplayFunc(Draw::display);
	glutIdleFunc(Draw::display); // Register display callback handler for window re-paint
	glutReshapeFunc(Draw::reshape);
	glutKeyboardFunc(World::key);
	//glutMouseFunc(World::mouse);
	glutPassiveMotionFunc(World::passiveMouse);

	glutMainLoop();           // Enter the infinitely event-processing loop

}

std::vector< int > Draw::pixelToGlut(int px, int py) {				// pixel coord -> glut coord
	// could just save the actual height and width
	double current_height = Draw::height * Draw::STARTING_HEIGHT;
	double current_width =  Draw::width * Draw::STARTING_WIDTH;

//	double dx = ((px / current_width) * 2 - 1) * World::getResolution();
//	double dy = ((1 - (py / current_height)) * 2 - 1) * World::getResolution();
	// 1, 1 is now bottom right
		// has a problem with some negatives, I think primarily negative y

	double dx = ((px / current_width) * 2) * World::getResolution();
	double dy = ((1 - (py / current_height)) * 2) * World::getResolution();

	int x = dx;
	int y = dy;

	return std::vector<int> {x, y};
}

