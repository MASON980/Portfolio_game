/*
 * Draw.h
 *
 *  Created on: 8 Dec 2015
 *      Author: Mason
 */

#ifndef DRAW_H_
#define DRAW_H_

#include <string>
#include "agent.h"
#include <vector>

// Draw is for drawing the GUI/Graphics to make stuff easier to follow for humans

class Draw {

private:
	static const int TICK;

	//static char *myargv;
	//static char v;
	//static int myargc;

	static const float RADIUS;
	static const int STARTING_HEIGHT;
	static const int STARTING_WIDTH;
	static double line;
	static int frame_height;
	static float height;
	static float width;
	static int frames;

	static long prev;
	static int f;
	static int hold;

	static bool hovering;
	static Agent ag;
	static Agent agg;

public:

	static bool h;
	static bool hh;



	static const float DEG2RAD;
	static float ratio;	// it was complaining about this being private

	static void initialiseDraw();
	static void agents();
	static void display();

	static void reshape(int, int);
	static void info(Agent, int, int);

	static void circle(int, int, int);
	static void string(std::string, int, int);
	static void stringWithInt(std::string, int);

	static void incrementFrames() { frames++; }
	static void setHovering(bool b) { hovering = b; }

	static std::vector<int> pixelToGlut(int, int);

	static void pane();

};



#include <iostream>
#include <unordered_map>
#include <string>
#include <functional>
using namespace std;

typedef pair<string,string> Name;

#endif /* DRAW_H_ */
