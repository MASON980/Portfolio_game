/*
 * Button.h
 *
 *  Created on: 1 Mar 2016
 *      Author: Mason
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include <vector>

namespace UIE {

class Button {

private:
	char *text;
	std::vector<int> position;
	void (*func)(char*);
	char* file;
	int tSize;
	int fSize;
	bool pressed;

public:

	Button(int, int, char*, void (*func)(char*), char*);
	virtual ~Button();
	std::vector<int> getPosition() { return position;}
	char* getText() {return text;};
	void press() {pressed = !pressed;};
	bool getPressed() {return pressed;};

	void run();

};

}

#endif /* BUTTON_H_ */
