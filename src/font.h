/*
 * font.h
 *
 *  Created on: 4 Mar 2016
 *      Author: Mason
 */

#ifndef SRC_FONT_H_
#define SRC_FONT_H_

class font {
public:
	static float width;
	static float height;
	static float thick;

	static float x;
	static float y;
	static float z;
	static float o;

	static void vert (float, float);
	static int drawChar (float, float, float, float, char);
	static int drawChar (int, int, char);

};

#endif /* SRC_FONT_H_ */
