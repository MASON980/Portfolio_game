/*
 * Button.cpp
 *
 *  Created on: 1 Mar 2016
 *      Author: Mason
 */

#include "Button.h"
#include <windows.h>      // std::ifstream

#include "draw.h"

namespace UIE {


std::vector<int> position (4);
char* text;
int tSize;
int fSize;
char* file;
void (*func)(char*);
bool pressed;

Button::Button(int x, int y, char* t, void (*fu)(char*), char* fi) {
	//	x and y is the position on the screen, and t is the text to be shown on the button
	//	fu being the function called when clicked on,  fi is the file which will be passed to the function (or it may be empty)
	std::string st (t);
	std::vector<int> p = Draw::getTextSize(st, 500);
	position = {x, y, x+p[0], y-p[1]};										//		-			-		-		- negative

	tSize = strlen(t)+1;
	fSize = strlen(fi)+1;
	text = (char*) malloc (tSize);
	file = (char*) malloc (fSize);

	strcpy(text, t);
	strcpy(file, fi);

	//text = t;
	func = fu;
	//file = fi;

	pressed = false;
}

Button::~Button() {
	// TODO Auto-generated destructor stub
	text = (char*) calloc (tSize, sizeof(char));
	file = (char*) calloc (fSize, sizeof(char));

	free(text);
	free(file);
}


void Button::run() {
	pressed = false;
	func(file);
}

}
