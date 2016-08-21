/*
 * main.cpp
 *
 *  Created on: 8 Dec 2015
 *      Author: Mason
 */

#include "draw.h"
#include "main.h"
#include <ctime>
#include <stdlib.h>
using namespace std;

int main(int argc, char* argv[])
{
	srand(time(0));
	Draw::initialiseDraw();
    return 0;
}



// more that could be done
/*
 * 	collision detection	-	things bouncing off each other
 *		 		get both bearings and the halfway point between the wider angle
 *
 * 	multiple shapes/ agent types
 * 		some dodge, some bounce, some stick around and do a bunch of goals
 *
 * 	font rendering isn't very nice
 * 	various things aren't used yet (some classes, many functions, and commented out blocks of code)
 * 	consistent commenting needs to be done, some is in the header files and some in the cpp files
 *
 */
