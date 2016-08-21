/*
 * main.h
 *
 *  Created on: 9 Dec 2015
 *      Author: Mason
 */

#ifndef MAIN_H_
#define MAIN_H_

class Main {
public:
	int main(int argc, char** argv);


	static void drawSnowMan();
	static void display();
	static void renderScene(void);
	static void processNormalKeys();
	static void processSpecialKeys(int, int, int);
};

#endif /* MAIN_H_ */
