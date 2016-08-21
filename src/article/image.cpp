/*
 * image.cpp
 *
 *  Created on: 1 Mar 2016
 *      Author: Mason
 */

#include "image.h"
#include "../draw.h"
#include "../world.h"

#include <string.h>
#include <stdlib.h>
#include <vector>


int img_orientation;
unsigned char* img;
std::vector<int> img_size;
float res;

image::image() {

}

image::image(int x, int y, int z, char* d) {
	// TODO Auto-generated constructor stub
	position = {x, y, z};
	img_orientation = 1;

	if (x < 0) {
		img_orientation += 2;
	}
	dir = d;


	char* fn;
	fn = (char*) malloc (strlen(dir.c_str())*2+strlen(World::directory)+strlen(World::dd)+6);

	strcpy(fn, World::directory);
	strcat(fn, World::dd);
	strcat(fn, dir.c_str());
	strcat(fn, "\\");
	strcat(fn, dir.c_str());
	strcat(fn, ".bmp");

	unsigned char* c = World::getBitmap(fn);
	img_size = World::getBitmapSize();
	img = (unsigned char*) malloc (img_size[0]*img_size[1]*img_size[2]+1);
	memcpy(img, c, img_size[0]*img_size[1]*img_size[2]);

	free(fn);

	res = determineRes(100);

	if (img_orientation == 0) {
		hitbox = {res*img_size[0], res*img_size[1]+1, 0+0.1};
		if (hitbox[0] <= 0) {
			hitbox[0] = 1;
		}
	} else if (img_orientation == 1) {
		hitbox = {0+0.1, res*img_size[1]+1, res*img_size[0]};
		if (hitbox[2] <= 0) {
			hitbox[2] = 1;
		}
	} else if (img_orientation == 2) {
		hitbox = {-res*img_size[0], res*img_size[1]+1, 0+0.1};
		if (hitbox[0] <= 0) {
			hitbox[0] = 1;
		}
	} else if (img_orientation == 3) {
		hitbox = {0+0.1, res*img_size[1]+1, -res*img_size[0]};
		if (hitbox[2] <= 0) {
			hitbox[2] = 1;
		}

	}

float hzero = hitbox[0];
float hone = hitbox[1];
float htwo = hitbox[2];

					int a = 0;
}

image::~image() {
	// TODO Auto-generated destructor stub
//	free(img);
}

void image::draw() {
	if (position[0] > 0) {
		img_orientation = img_orientation%2;
	} else if (position[0] < 0) {
		img_orientation = img_orientation%2+2;
	}
	Draw::frame(position[0], position[1], position[2], img_orientation, img, img_size, dir, res);

}

float image::determineRes (float i) {

	return Draw::calcRes(img_size[0], i);

	if (img_size[0] > 1000) {
		return 2/i;
	} else if (img_size[0] > 500) {
		return 4/i;
	} else if (img_size[0] > 100) {
		return 20/i;
	} else if (img_size[0] > 50) {
		return 40/i;
	} else if (img_size[0] > 10) {
		return 200/i;
	}
	return 400.0f/i;

}

void image::shiftPosition(int x, int y, int z) {
	position = {x, y, z};
}
