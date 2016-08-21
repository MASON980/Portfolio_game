/*
 * video.cpp
 *
 *  Created on: 2 Mar 2016
 *      Author: Mason
 */

#include "video.h"
#include "../draw.h"

// not implemented currently, as I have no videos to put in my portfolio
Video::Video() {

}

Video::Video(int x, int y, int z, char* d) {
	// TODO Auto-generated constructor stub

}

Video::~Video() {
	// TODO Auto-generated destructor stub
}

void Video::draw() {
	Draw::television(position[0], position[1], position[2], dir);

}
