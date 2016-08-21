/*
 * draw.h
 *
 *  Created on: 21 Feb 2016
 *      Author: Mason
 */

#ifndef DRAW_H_
#define DRAW_H_

#include <vector>

class Draw {
private:

	static const float DEG2RAD;
	static const int STARTING_HEIGHT;
	static const int STARTING_WIDTH;
	static int frame_height;
	static float height;
	static float width;
	static float ratio;
	static int type;

	static int resolution;
	static int radius;

public:

	static void initialiseDraw();
	static void agents();
	static void display();

	static void circle(int, int, int);
	static void square(int, int);

	static void colouring(int);

	static int closest(int, int);
	static int calculateDistance(int, int, int, int);

	static void mouse(int, int, int , int);
	static void key(unsigned char, int , int);
	static void specialKey(int, int , int);

	static std::vector<int> pixelToGlut(int, int);


};


#endif /* DRAW_H_ */
