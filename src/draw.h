/*
 * Draw.h
 *
 *  Created on: 8 Dec 2015
 *      Author: Mason
 */

#ifndef DRAW_H_
#define DRAW_H_

#include <string>
//#include "article.h"
#include <vector>

// Draw is for drawing the GUI/Graphics to make stuff easier to follow for humans

class Draw {

private:
	//static char *myargv;
	//static char v;
	//static int myargc;

	static const int STARTING_HEIGHT;
	static const int STARTING_WIDTH;
	static const void* FONT_TYPE;
	static const int LINE_HEIGHT;

	static int frame_height;
	static float height;
	static float width;
	static int frames;

	static long prev;
	static float line;

	static int lineLength;
	static int scroll_level;

	static float red;
	static float green;
	static float blue;


public:
	static const int BORDER;
	static const int PANE_BORDER;


	static const float DEG2RAD;
	static float ratio;	// it was complaining about this being private

	static void initialiseDraw();
	static void display();
	static void displayScene();
	static void displayScreen();
	static void time(int);
	static void reshape(int, int);
	static void changeSize(int, int);
	static std::vector<int> getCentre();
	static int getWidth() {return width*STARTING_WIDTH;};
	static int getHeight() {return height*STARTING_HEIGHT;};

	static void displayGUI();
	
	static void open2d();
	static void close2d();

	static int string(std::string);
	static int string(std::string, float, float, int);
	static std::vector<int> getTextSize(std::string, int);
	static void rectangle(int, int, int, int);
	static void rectangleOutline(int, int, int, int);

	static void scrollBar();

	static void bitmap(double, double, double, int, unsigned char*, std::vector<int>,  float);
	static float calcRes(int, float);

	static void cuboid(float, float, float, float, float, float, bool);
	static void outline(float, float, float, float, float, float);
	static void room();
	static void button(int, int, int, int, char*, bool);

	// articles
	static void arcade(int, int, int, std::string);
	static void phonograph(int, int, int, std::string);
	static void frame(int, int, int, int, unsigned char*, std::vector<int>, std::string, float);
	static void entrance(int, int, int, int, std::string);
	static void television(int, int, int, std::string);
	static void document(int, int, int, std::string);
	
	static void table(int, int, int);
	static void sign(int, int, int, std::string);


	static void colouring(int);
	static std::vector<int> pixelToGlut(int, int);
	
	static void lookMove(int, int);
	static void locationMove(bool, int);



};

#endif /* DRAW_H_ */
