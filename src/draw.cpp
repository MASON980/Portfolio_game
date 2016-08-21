/*
 * Draw.cpp
 *
 *  Created on: 8 Dec 2015
 *      Author: Mason
 */

#include "draw.h"


#include "world.h"
#include "font.h"
//#include "article/article.h"

#include "agent.h"
#include "button.h"

#include <math.h>
#include <windows.h>  // For MS Windows
#define FREEGLUT_STATIC
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h


#include <stdio.h>		// sprintf




// Glut init
char *myargv[1];
char v = ' ';
int myargc = 1;

const float Draw::DEG2RAD = 3.14159 / 180;
const int Draw::STARTING_HEIGHT = 720;
const int Draw::STARTING_WIDTH = 1080;
const void* Draw::FONT_TYPE = GLUT_BITMAP_TIMES_ROMAN_24;
const int Draw::LINE_HEIGHT = 24;

long Draw::prev = 0;
int Draw::lineLength = 40;

int Draw::frame_height = Draw::STARTING_HEIGHT;
// maybe left top or something
float Draw::height = 1;
float Draw::width = 1;
float Draw::ratio  = Draw::width / Draw::height;

float Draw::line = 1;

const int Draw::BORDER = 20;
const int Draw::PANE_BORDER = 80;

float Draw::red = 1;
float Draw::green = 1;
float Draw::blue = 1;


//--	furniture --//
// most of the things below are furniture, most draw signs above themselves, and most colour() themselves based upon their x, y, and z

void Draw::arcade(int x, int y, int z, std::string text) {				// draws a sign above itself (Draw::sign())
	colouring(x+y+z % 10);
	glColor3f(red, green, blue);

	cuboid(x, x+0.5, y, y+0.5, z, z+0.5, true);
	cuboid(x, x+0.25, y+0.5, y+1, z, z+0.5, true);
	cuboid(x, x+0.5, y+1, y+1.1, z, z+0.5, true);

	colouring(x+y+z+2 % 10);
			glColor3f(red, green, blue);
	cuboid(x+0.375, x+0.4, y+0.5, y+0.55, z+0.1, z+0.15, true);
	cuboid(x+0.375, x+0.4, y+0.5, y+0.55, z+0.35, z+0.40, true);

	glColor3f(0.1f, 0.1f, 0.1f);
	cuboid(x+0.2, x+0.3, y+0.55, y+0.95, z+0.05, z+0.45, true);

	sign(x, y, z, text);
}

void Draw::sign(int x, int y, int z, std::string text) {			// draw a board up in the air which rotates to always be perpendicular to the camera, then draws text in front of it
	float cw = 0;
	float fx = x;
	float fz = z;
	glLineWidth(3);
	std::vector<float> look = Agent::getLook();
	float o = atan2(look[0], look[2]);
	float no = o+ 90*Draw::DEG2RAD;
	glColor3f(1.0f, 0.5f, 0.5f);
	glRasterPos3d(x+0.25, y+1.75, z+0.25);

	float len = text.length();
	fx = fx+(len*font::width/200)*sin(no);
	fz = fz+(len*font::width/200)*cos(no);

	float sx = fx;
	float sz = fz;

	for (int i = 0; i < len; i++) {
		cw = font::drawChar(fx, y+1.75-font::height/200, fz, no, text.at(i) );
		cw = cw/100;
		fx = fx-cw*sin(no);
		fz = fz-cw*cos(no);

	}

	glColor3f(0.1f, 0.1f, 0.1f);

	float nx = sin(no);
	float nz = cos(no);

	float ox = sin(o);
	float oz = cos(o);

	float b = (float)BORDER / 100;

	sx += ox*0.05 + nx*b;
	sz += oz*0.05 + nz*b;
	fx += ox*0.05 - nx*b;
	fz += oz*0.05 - nz*b;

	glBegin(GL_QUADS);
		glVertex3f(sx, y+1.5, sz);
		glVertex3f(fx, y+1.5, fz);
		glVertex3f( fx, y+2,  fz);
		glVertex3f( sx, y+2,  sz);

	glEnd();
}

void Draw::table(int x, int y, int z) {
//	colouring(x+y+z % 10);
	glColor3f(0.7f, 0.6f, 0.2f);

	cuboid(x, x+0.5, y+0.45, y+0.5, z, z+0.5, true);
	// texture on this one
	
	cuboid(x+0.1, x+0.05, y, y+0.47, z+0.1, z+0.015, true);
	cuboid(x+0.1, x+0.05, y, y+0.47, z+0.4, z+0.45, true);
	cuboid(x+0.4, x+0.45, y, y+0.475, z+0.4, z+0.45, true);
	cuboid(x+0.4, x+0.45, y, y+0.475, z+0.1, z+0.05, true);
	
}

void Draw::phonograph(int x, int y, int z, std::string text) {			//		/grammaphone			-- draws a table (Draw::table()) underneath itself 				// draws a sign above itself (Draw::sign())
	table(x, y, z);
	colouring(x+y+z % 10);
	glColor3f(red, green, blue);

	cuboid(x+0.1, x+0.4, y+0.5, y+0.6, z+0.1, z+0.4, true);

	colouring(x+y+z-2 % 10);
	glColor3f(red, green, blue);
	cuboid(x+0.24, x+0.26, y+0.6, y+0.65, z+0.24, z+0.26, true);
	cuboid(x+0.1, x+0.05, y+0.5, y+0.7, z+0.1, z+0.05, true);

	colouring(x+y+z+2 % 10);
	glColor3f(red, green, blue);
	glBegin(GL_QUADS);
		glVertex3f(	x+0.1, y+0.65, z+0.1);
		glVertex3f(	x+0.1, y+0.7, z+0.1);
		glVertex3f( x+0.3, y+0.7, z+0.15);
		glVertex3f( x+0.3, y+0.65, z+0.15);
	glEnd();


	glBegin(GL_QUADS);
		glVertex3f(	x+0.1, y+0.7, z+0.1);
		glVertex3f(	x+0.15, y+0.9, z+0.5);
		glVertex3f( x, y+0.9, z+0.5);
		glVertex3f( x+0.05, y+0.7, z+0.1);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(	x+0.05, y+0.7, z+0.1);
		glVertex3f(	x, y+0.9, z+0.5);
		glVertex3f( x, y+0.75, z+0.5);
		glVertex3f( x+0.05, y+0.65, z+0.1);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(	x+0.05, y+0.65, z+0.1);
		glVertex3f(	x, y+0.75, z+0.5);
		glVertex3f( x+0.15, y+0.75, z+0.5);
		glVertex3f( x+0.1, y+0.65, z+0.1);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f( x+0.1, y+0.65, z+0.1);
		glVertex3f( x+0.15, y+0.75, z+0.5);
		glVertex3f(	x+0.15, y+0.9, z+0.5);
		glVertex3f(	x+0.1, y+0.7, z+0.1);
	glEnd();

	float c = 0.2;
	float rc = c;
	float gc = c;
	float bc = c;

	if (red <= c) {
		rc = -0.2;
	}
	if (green <= c) {
		gc = -0.2;
	}
	if (blue <= c) {
		bc = -0.2;
	}

	glColor3f(red-rc, green-gc, blue-bc);
//	glPushMatrix();
	glColor3f(0, 0, 0);
	glLineWidth(2);
	glBegin(GL_LINES);
	// lines
		glVertex3f(	x+0.1, y+0.65, z+0.1);
		glVertex3f(	x+0.1, y+0.7, z+0.1);
		glVertex3f( x+0.3, y+0.7, z+0.15);
		glVertex3f( x+0.3, y+0.65, z+0.15);

		glVertex3f(	x+0.1, y+0.7, z+0.1);
		glVertex3f(	x+0.15, y+0.9, z+0.5);
		glVertex3f( x, y+0.9, z+0.5);
		glVertex3f( x+0.05, y+0.7, z+0.1);

		glVertex3f(	x+0.15, y+0.9, z+0.5);
		glVertex3f( x, y+0.9, z+0.5);

		glVertex3f(	x+0.05, y+0.7, z+0.1);
		glVertex3f(	x, y+0.9, z+0.5);
		glVertex3f( x, y+0.75, z+0.5);
		glVertex3f( x+0.05, y+0.65, z+0.1);

		glVertex3f(	x, y+0.9, z+0.5);
		glVertex3f( x, y+0.75, z+0.5);

		glVertex3f(	x+0.05, y+0.65, z+0.1);
		glVertex3f(	x, y+0.75, z+0.5);
		glVertex3f( x+0.15, y+0.75, z+0.5);
		glVertex3f( x+0.1, y+0.65, z+0.1);

		glVertex3f(	x, y+0.75, z+0.5);
		glVertex3f( x+0.15, y+0.75, z+0.5);

		glVertex3f( x+0.1, y+0.65, z+0.1);
		glVertex3f( x+0.15, y+0.75, z+0.5);
		glVertex3f(	x+0.15, y+0.9, z+0.5);
		glVertex3f(	x+0.1, y+0.7, z+0.1);

		glVertex3f( x+0.15, y+0.75, z+0.5);
		glVertex3f(	x+0.15, y+0.9, z+0.5);

	glEnd();
	glColor3f(red, green, blue);


	sign(x, y, z, text);

	// some sort of angled things
}

void Draw::frame(int x, int y, int z, int o, unsigned char* image, std::vector<int> image_size, std::string text, float res) {			// a  frame that a bitmap is drawn onto (Draw::bitmap()) as such it requires bitmap information to be passed to it, I don't think text is used
	// will the frame size be changed or will the pixels be stretched

	Draw::bitmap(x, y, z, o, image, image_size, res);


	glColor3f(1.0f, 1.0f, 1.0f);
	float h = image_size[0]*res + 0.1		-res;
	float w = image_size[1]*res + 0.1;
	float zn;
	float xn;
	float zp;
	float xp;

	switch (o) {
		case 0: {
			xn = w;
			zn = 0;
			xp = 0;
			zp = -0.1;
			break;
		}
		case 1: {
			xn = 0;
			zn = w;
			xp = -0.1;
			zp = 0;
			break;
		}
		case 2: {
			xn = -w;
			zn = 0;
			xp = -0;
			zp = +0.1;
			break;
		}
		case 3: {
			xn = -0;
			zn = -w;
			xp = +0.1;
			zp = -0;
			break;
		}
	};
	// pic itself
	cuboid(x-xp/10, x+xn-xp/10, y, y+h, z-zp/10, z+zn-zp/10, true);
	//cuboid(x+xp/10, x+xn+xp/10, y, y+h, z+zp/10, z+zn+zp/10);

	float d = 0.05;
	glColor3f(0.8f, 0.8f, 0.8f);

	cuboid(x-d, x+xn+d, y+h, y+h+d*2, z-d, z+zn+d, true);
	cuboid(x-d, x+xn+d, y, y+d*2, z-d, z+zn+d, true);

	cuboid(x+xn-d, x+xn+d, y, y+h+d*2, z+zn+d, z+zn-d, true);
	cuboid(x-d, x+d, y, y+h+d*2, z-d, z+d, true);




//	sign(x, y, z, text);		// might not be needed

}

void Draw::entrance(int x, int y, int z, int o, std::string text) {			// a door				// draws a sign above itself (Draw::sign())
	colouring(x+y+z+2 % 10);
	glColor3f(red, green, blue);

	float h = 2;
	float w = 1;
	float zn;
	float xn;
	float zp;
	float xp;

	switch (o) {
		case 0: {
			xn = w;
			zn = 0;
			xp = 0;
			zp = 0.1;
			break;
		}
		case 1: {
			xn = 0;
			zn = w;
			xp = 0.1;
			zp = 0;
			break;
		}
		case 2: {
			xn = -w;
			zn = 0;
			xp = -0;
			zp = -0.1;
			break;
		}
		case 3: {
			xn = -0;
			zn = -w;
			xp = -0.1;
			zp = -0;
			break;
		}
	};
	// pic itself
	cuboid(x+xp/10, x+xn+xp/10, y, y+h, z+zp/10, z+zn+zp/10, true);

	red-=0.3;
	green-=0.3;
	blue-=0.3;

	glColor3f(red, green, blue);

	cuboid(x+xn*1/3-xp, x+xn*2/9+xp, y+h*2/5, y+h/2, z+zn*1/3-zp, z+zn*2/9+zp, true);


	red+=0.1;
	green+=0.1;
	blue+=0.1;
	glColor3f(red, green, blue);


	float d = 0.05;

	cuboid(x-d, x+xn+d, y+h, y+h+d*2, z-d, z+zn+d, true);

	cuboid(x+xn-d, x+xn+d, y, y+h+d*2, z+zn+d, z+zn-d, true);
	cuboid(x-d, x+d, y, y+h+d*2, z-d, z+d, true);

	sign(x, y+1, z, text);		// might not be needed

}

void Draw::television(int x, int y, int z, std::string text) {				// draws a sign above itself (Draw::sign())


	table(x, y, z);

	colouring(x+y+z+7 % 10);
	glColor3f(red, green, blue);
	glBegin(GL_QUADS);
		glVertex3f(	x+0.1, y+0.55, z+0.05);
		glVertex3f(	x+0.1, y+0.75, z+0.05);
		glVertex3f( x+0.4, y+0.75, z+0.05);
		glVertex3f( x+0.4, y+0.55, z+0.05);
	glEnd();



	glBegin(GL_QUADS);
		glVertex3f(	x+0.1, y+0.55, z+0.05);
		glVertex3f(	x-0.1, y+0.55, z+0.45);
		glVertex3f( x-0.1, y+0.95, z+0.45);
		glVertex3f(	x+0.1, y+0.75, z+0.05);
	glEnd();

	// top
	glBegin(GL_QUADS);
		glVertex3f(	x+0.1, y+0.75, z+0.05);
		glVertex3f(	x-0.1, y+0.95, z+0.45);
		glVertex3f( x+0.6, y+0.95, z+0.45);
		glVertex3f( x+0.4, y+0.75, z+0.05);
	glEnd();

	//
	glBegin(GL_QUADS);
		glVertex3f( x+0.4, y+0.75, z+0.05);
		glVertex3f(	x+0.6, y+0.95, z+0.45);
		glVertex3f( x+0.6, y+0.55, z+0.45);
		glVertex3f( x+0.4, y+0.55, z+0.05);
	glEnd();

	// bottom
	glBegin(GL_QUADS);
		glVertex3f( x+0.4, y+0.55, z+0.05);
		glVertex3f( x+0.6, y+0.55, z+0.45);
		glVertex3f(	x-0.1, y+0.55, z+0.45);
		glVertex3f(	x+0.1, y+0.55, z+0.05);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
		glVertex3f(	x-0.05, y+0.6, z+0.4);
		glVertex3f(	x-0.05, y+0.9, z+0.4);
		glVertex3f( x+0.55, y+0.9, z+0.4);
		glVertex3f( x+0.55, y+0.6, z+0.4);
	glEnd();
	sign(x, y, z, text);


}

void Draw::document(int x, int y, int z, std::string text) {		// a scroll				-- draws a table (Draw::table()) underneath itself 				// draws a sign above itself (Draw::sign())


	table(x, y, z);

	colouring(x+y+z % 10);
	glColor3f(red, green, blue);
	
	// bottom
	glBegin(GL_QUADS);
		glVertex3f(	x+0.1, y+0.65, z+0.2);
		glVertex3f(	x+0.2, y+0.55, z+0.3);
		glVertex3f( x+0.3, y+0.55, z+0.2);
		glVertex3f(	x+0.2, y+0.65, z+0.1);
	glEnd();

	//
	glBegin(GL_QUADS);
		glVertex3f(	x+0.3, y+0.65, z+0.4);
		glVertex3f(	x+0.2, y+0.55, z+0.3);
		glVertex3f( x+0.3, y+0.55, z+0.2);
		glVertex3f( x+0.4, y+0.65, z+0.3);
	glEnd();




	// connecting
	glBegin(GL_QUADS);
		glVertex3f( x+0.4, y+0.65, z+0.3);
		glVertex3f(	x+0.2, y+0.85, z+0.1);
		glVertex3f(	x+0.1, y+0.85, z+0.2);
		glVertex3f(	x+0.3, y+0.65, z+0.4);
	glEnd();


	// top
	glBegin(GL_QUADS);
		glVertex3f(	x+0.1, y+0.85, z+0.2);
		glVertex3f(	x+0.2, y+0.95, z+0.3);
		glVertex3f( x+0.3, y+0.95, z+0.2);
		glVertex3f(	x+0.2, y+0.85, z+0.1);
	glEnd();

	//
	glBegin(GL_QUADS);
		glVertex3f(	x+0.3, y+0.85, z+0.4);
		glVertex3f(	x+0.2, y+0.95, z+0.3);
		glVertex3f( x+0.3, y+0.95, z+0.2);
		glVertex3f( x+0.4, y+0.85, z+0.3);
	glEnd();


	colouring(x+y+z+9 % 10);
	glColor3f(red, green, blue);
	glLineWidth(2);
	// lines
	glBegin(GL_LINES);
		glVertex3f(	x+0.1, y+0.65, z+0.2);
		glVertex3f(	x+0.2, y+0.55, z+0.3);

		glVertex3f( x+0.3, y+0.55, z+0.2);
		glVertex3f(	x+0.2, y+0.65, z+0.1);

		glVertex3f(	x+0.2, y+0.65, z+0.1);
		glVertex3f(	x+0.1, y+0.65, z+0.2);
		glVertex3f( x+0.3, y+0.55, z+0.2);
		glVertex3f(	x+0.2, y+0.55, z+0.3);



		glVertex3f(	x+0.3, y+0.65, z+0.4);
		glVertex3f(	x+0.2, y+0.55, z+0.3);

		glVertex3f( x+0.3, y+0.55, z+0.2);
		glVertex3f( x+0.4, y+0.65, z+0.3);

		glVertex3f( x+0.3, y+0.55, z+0.2);
		glVertex3f(	x+0.2, y+0.55, z+0.3);
		glVertex3f(	x+0.3, y+0.65, z+0.4);
		glVertex3f( x+0.4, y+0.65, z+0.3);



		glVertex3f( x+0.4, y+0.65, z+0.3);
		glVertex3f(	x+0.2, y+0.85, z+0.1);

		glVertex3f(	x+0.1, y+0.85, z+0.2);
		glVertex3f(	x+0.3, y+0.65, z+0.4);

		glVertex3f(	x+0.1, y+0.85, z+0.2);
		glVertex3f(	x+0.2, y+0.85, z+0.1);
		glVertex3f( x+0.4, y+0.65, z+0.3);
		glVertex3f(	x+0.3, y+0.65, z+0.4);




		glVertex3f(	x+0.1, y+0.85, z+0.2);
		glVertex3f(	x+0.2, y+0.95, z+0.3);

		glVertex3f( x+0.3, y+0.95, z+0.2);
		glVertex3f(	x+0.2, y+0.85, z+0.1);

		glVertex3f( x+0.3, y+0.95, z+0.2);
		glVertex3f(	x+0.2, y+0.95, z+0.3);
		glVertex3f(	x+0.1, y+0.85, z+0.2);
		glVertex3f(	x+0.2, y+0.85, z+0.1);



		glVertex3f(	x+0.3, y+0.85, z+0.4);
		glVertex3f(	x+0.2, y+0.95, z+0.3);

		glVertex3f( x+0.3, y+0.95, z+0.2);
		glVertex3f( x+0.4, y+0.85, z+0.3);

		glVertex3f(	x+0.3, y+0.85, z+0.4);
		glVertex3f( x+0.4, y+0.85, z+0.3);
		glVertex3f( x+0.3, y+0.95, z+0.2);
		glVertex3f(	x+0.2, y+0.95, z+0.3);


	glEnd();


	sign(x, y, z, text);


}

float Draw::calcRes(int resolution, float factor) {		// this is a double up of image::getRes			based upon the resolution determine how big each pixel will be drawn / scaled
	if (resolution > 1000) {
		return factor/5;
	} else if (resolution > 500) {
		return factor/2;
	} else if (resolution > 100) {
		return factor;
	} else if (resolution > 50) {
		return 2/factor;
	} else if (resolution > 10) {
		return 5/factor;
	}
	return 10/factor;

}

int Draw::string(std::string text) {			// string is positioned based upon global Draw::line
	Draw::line = Draw::line + 0.05;
	glColor3d(1.0, 0.2, 0.2);
	if (text.length() < 40) {
		glRasterPos2d(0.01, 1 - line); // line
		for (int i = 0; i < text.length(); i++) {
			glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24 , text.at(i));
		}
	} else {
		for (int i = 0; i < text.length(); i++) {
			glRasterPos2d(0.01, 1 - line); // line
			for (int i = 0; i < text.length(); i++) {
				glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24 , text.at(i));
			}
		}
	}

// 48 == 0
	// 65 == A
	return 0;
}


int Draw::string(std::string text, float x, float y, int max_width) {			// max_width is the line length before starting a new line
	int max_height = Draw::height*Draw::STARTING_HEIGHT - 500;
	int wid = 0;
	int x_line = x;
	bool bottom = false;
	//	glPushMatrix();
	glLineWidth(font::thick);

	//glScalef(0.5,0.5,1);
	glColor3d(0.0, 0.0, 0.0);
	glRasterPos2d(x, y); // line
	int space = 0;

	// scroll needs to only work on the certain thing
	int start = -1;
	int line = -1;
	if (max_width/font::width < text.length()) {
		start = World::scroll_level;
		line = 0;
		if (start > 0) {
			string(" ... ", x_line, y, 100);
			glColor4d(0.8, 0.8, 0.8, 0.8);
			rectangle(x_line-font::width, y-font::height, x_line+max_width+font::width, y+ font::height*7/4+1);
			glColor3d(0.0, 0.0, 0.0);
		}

	}
	int previous_space = 0;
	for (int i = 0; i < text.length(); i++) {
		if (space == i) {
			previous_space = space;
			space = text.find_first_of(" ", space+1);
			if (space == -1) {
				space = text.length();
			}
			int wi = 0;

			if (space - previous_space == 1) {		// '  ' double space/ new line work around	-	the reading thing doesn't get new lines properly and this was quicker to fix
				wi = max_width;
			}

			for (int j = i; j < space; j++) {
				//wid += glutBitmapWidth( GLUT_BITMAP_TIMES_ROMAN_24 , text.at(j));

				wi +=font::width;
					// approx
			}
			if (wid+wi >= (max_width)) {
				line++;
				if (start >= line) {
					text.erase(0, i);

					i = 0;
					space = 1;
					if (start == line) {
						y = y +font::height*7/4;
					}
				} else {
					y = y +font::height*7/4;
				}


				// to stop overflow
				if (y <= max_height) {
					i = 0;
					text = "...";
					Draw::scrollBar();
					bottom = false;
				} else if (World::scrollable) {
					World::scrolling_max = true;
					bottom = true;
				}
				wid = 0;
				x = x_line;
	//			glRasterPos2d(x, y); // line

			}
		}
		//glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24 , text.at(i));
		int cw = font::drawChar(x, y, text.at(i) );
		x+= cw;
		wid+=cw;

	}
	if (!bottom) {
		if (World::scrollable) {
			World::scrolling_max = false;
		}
	}
	//glPopMatrix();
	// GLUT_BITMAP_TIMES_ROMAN_24
	return wid;

}

void Draw::scrollBar() {				// TODO make visuals for the scroll bar
	World::scrollable = true;
	/*
	if (pressed) {
		glColor3d(0.8, 0.3, 0.4);
	} else {
		glColor3d(0.9, 0.4, 0.4);
	}

	rectangle(x-BORDER, y-BORDER, w+BORDER, h+BORDER);
	*/
}

void Draw::rectangle(int x, int y, int h, int w) {
	glRectd(x, y, h, w);

/*	glBegin(GL_TRIANGLE_FAN);         // Each set of 4 vertices form a something
	//float fy = (1 - y * height) / 100;
	for (int i = 0; i <= 4; i++) {
		float degInRad = (i+0.5) * Draw::DEG2RAD * 90;		// 10 * 36(used for how many loops) is where the 360 degrees come from
		glVertex2d(x + cos(degInRad) * w * Draw::ratio,
				y + sin(degInRad) * h);
	}
	glEnd();
*/
}
void Draw::rectangleOutline (int x, int y, int w, int h) {
	int mini_border = 4;
	rectangle(x, y-mini_border, w, y+mini_border);
	rectangle(x-mini_border, y, x+mini_border, h);
	rectangle(x, h+mini_border, w, h-mini_border);
	rectangle(w+mini_border, y, w-mini_border, h);

}

void Draw::bitmap(double x, double y, double z, int o, unsigned char* image, std::vector<int> image_size, float res) {	// position (x, y, z), orientation (o), image binary (image), width/height/depth(for certain orientation) in pixels (image_size), size of pixels (res)

	if (image == NULL) {
		return;
	} else if (image_size[0] <= res || image_size[1] <= res) {
		//return;
	}
	int depth = image_size[2];
	int f = image_size[1]*depth;

	std::vector<int> i;
	for (int l = 0; l < 75; l++) {
		i.push_back(image[l]);
	}

	if (f % 4 != 0) {
		f = f/4 *4 +4;

	}
	float b = 0;
	float g = 0;
	float r = 0;

	float zn;
	float xn;
	float yn = res;
	switch (o) {
		case -1:
		{	xn = res; zn = 0;
		if (res < 1) {
	//		xn = 1;
	//		yn = 1;
		}
		break;}
		case 0:
		{	xn = res;	zn = 0;
		//	x += 0.1;					// commenting out these 4 is how I solved having the pic be too far to one side
			y += 0.1;
		break;}
		case 1:
		{	xn = 0;		zn = res;
		//	z += 0.1;
			y += 0.1;
		break;}
		case 2:
		{	xn = -res;	zn = -0;
		//	x -= 0.1;
			y += 0.1;
		break;}
		case 3:
		{	xn = -0;	zn = -res;
		//	z -= 0.1;
			y += 0.1;
		break;}
	};
	int w = 0;
	for (int h = 0; h < image_size[0]-1; h++) {
		if (o == -1) {
			if (res < 1) {
				if (h % (int)(1/res) == 0) {

				} else {
					y += res;
					continue;
				}
			}
		}
		for (w = 0; w < image_size[1]; w++) {

			// determine colour
			// bgr not rgb is used to store, or draw colour somewhere (I think it was how glRect4d/glVertex4d draws it)
			r = image[h*f + w *depth +2];
			g = image[h*f + w * depth +1];
			b = image[h*f + w * depth +0];

			glColor3d(r/256, g/256, b/256);

			if (o == -1) {
				if (res < 1) {
					if (w % (int)(1/res) == 0) {
						glRectd(x, y, x+1, y+1);
					} else {

					}
				} else {
					glRectd(x, y, x+res, y+res);
				}

			} else {
				glBegin(GL_QUADS);
					glVertex3f(	x, y, 		z);
					glVertex3f(	x+xn, y, 		z+zn);
					glVertex3f( x+xn, y+res,	z+zn);
					glVertex3f( x, y+res, 	z);
				glEnd();	
				z += zn;
			}
			x += xn;
		}
		// next line
		y += res;
		x = x - xn*w;
		z = z - zn*w;
	}
}

void Draw::display() {
	if (World::getPaused()) {
		glutSetCursor( GLUT_CURSOR_INHERIT );		// draw cursor if menu is open
	} else {
		glutSetCursor(GLUT_CURSOR_NONE);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	displayScene();			// world
	if (World::getSelected() != -1 || World::getPaused()) {
		displayScreen();		// menu
	}

	glutSwapBuffers();


}

void Draw::cuboid(float x, float xx , float y, float yy, float z, float zz, bool b) {	// for cubes/rectangular prisms				b is whether you want an outline,   x -> xx is the start and end x values, same with the others
	// Draw bottom / top
	glBegin(GL_QUADS);
		glVertex3f(xx, yy, zz);
		glVertex3f(xx, yy,  z);
		glVertex3f( x, yy,  z);
		glVertex3f( x, yy, zz);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(xx, y, zz);
		glVertex3f(xx, y,  z);
		glVertex3f( x, y,  z);
		glVertex3f( x, y, zz);
	glEnd();

	//	Sides
	glBegin(GL_QUADS);
		glVertex3f(x, yy, zz);
		glVertex3f(x, yy,  z);
		glVertex3f( x, y,  z);
		glVertex3f( x, y, zz);
	glEnd();
	glBegin(GL_QUADS);
		glVertex3f(xx, yy, zz);
		glVertex3f(xx, yy,  z);
		glVertex3f(xx, y,  z);
		glVertex3f(xx, y, zz);
	glEnd();
	glBegin(GL_QUADS);
		glVertex3f(xx, yy, z);
		glVertex3f( x, yy, z);
		glVertex3f( x, y, z);
		glVertex3f(xx, y, z);
	glEnd();
	glBegin(GL_QUADS);
		glVertex3f(xx, yy, zz);
		glVertex3f( x, yy, zz);
		glVertex3f( x, y, zz);
		glVertex3f(xx, y, zz);
	glEnd();

	if (b) {
		outline(x, xx, y, yy, z, zz);
	}
}

void Draw::outline(float x, float xx , float y, float yy, float z, float zz) {		// outlines cuboids (cubes/rectangular prisms)
	float c = 0.2;
	float rc = c;
	float gc = c;
	float bc = c;

	if (red <= c) {
		rc = -0.2;
	}
	if (green <= c) {
		gc = -0.2;
	}
	if (blue <= c) {
		bc = -0.2;
	}

	glColor3f(red-rc, green-gc, blue-bc);
//	glPushMatrix();
//	glColor3f(0, 0, 0);
	glLineWidth(2);
	// lines


	glBegin(GL_LINES);
		glVertex3f(xx, yy, zz);
		glVertex3f(xx, yy,  z);
		glVertex3f( x, yy,  z);
		glVertex3f( x, yy, zz);

		glVertex3f(xx, y, zz);
		glVertex3f(xx, y,  z);
		glVertex3f( x, y,  z);
		glVertex3f( x, y, zz);



		glVertex3f(x, yy,  z);
		glVertex3f(x, y,   z);
		glVertex3f( x, y, zz);
		glVertex3f( x, yy, zz);
		glVertex3f(xx, yy, zz);
		glVertex3f(xx, y,  zz);
		glVertex3f(xx, yy,  z);
		glVertex3f(xx, y, 	z);



		glVertex3f(xx, yy, z);
		glVertex3f( x, yy, z);
		glVertex3f( x, y, z);
		glVertex3f(xx, y, z);

		glVertex3f(xx, yy, zz);
		glVertex3f( x, yy, zz);
		glVertex3f( x, y, zz);
		glVertex3f(xx, y, zz);

	glEnd();
	glColor3f(red, green, blue);
	//glPopMatrix();

}


void Draw::room() {					// the room/world that the character can walk around in, including pillars and patterns on the floor, roof etc.
	int x = World::RESOLUTION[0];
	int y = World::RESOLUTION[1];
	int z = World::RESOLUTION[2];

	// Draw ground/ roof
	glColor3f(0.6f, 0.6f, 0.6f);
		glBegin(GL_QUADS);
			glVertex3f(-x, 0.0f, -z);
			glVertex3f(-x, 0.0f,  z);
			glVertex3f( x, 0.0f,  z);
			glVertex3f( x, 0.0f, -z);
		glEnd();

		glColor3f(0.9f, 0.99f, 0.9f);
		glBegin(GL_QUADS);
			glVertex3f(-x, y, -z);
			glVertex3f(-x, y,  z);
			glVertex3f( x, y,  z);
			glVertex3f( x, y, -z);
		glEnd();

		//	Walls
		glColor3f(0.95f, 0.95f, 0.95f);
		glBegin(GL_QUADS);
			glVertex3f(x, 0, -z);
			glVertex3f(x, 0,  z);
			glVertex3f( x, y,  z);
			glVertex3f( x, y, -z);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(-x, 0, -z);
			glVertex3f(-x, 0,  z);
			glVertex3f(-x, y,  z);
			glVertex3f(-x, y, -z);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(-x, 0, z);
			glVertex3f( x, 0, z);
			glVertex3f( x, y, z);
			glVertex3f(-x, y, z);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(-x, 0, -z);
			glVertex3f( x, 0, - z);
			glVertex3f( x, y, -z);
			glVertex3f(-x, y, -z);
		glEnd();

	//	Columns at corners
		glColor3f(0.25f, 0.25f, 0.25f);
		glBegin(GL_QUADS);
			glVertex3f(x-2,	0,	z);
			glVertex3f(x, 	0,	z-2);
			glVertex3f( x, 	y, 	z-2);
			glVertex3f( x-2, y,	z);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(-x+2, 0,	-z);
			glVertex3f(-x, 	0, -z+2);
			glVertex3f(-x, 	y, 	-z+2);
			glVertex3f(-x+2, y, -z);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(-x+2, 0, z);
			glVertex3f(-x, 	0, 	z-2);
			glVertex3f(-x, 	y, 	z-2);
			glVertex3f(-x+2, y, z);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f( x-2, 0, -z);
			glVertex3f( x, 	0,	-z+2);
			glVertex3f( x, 	y, 	-z+2);
			glVertex3f( x-2, y,	-z);
		glEnd();


		cuboid(-1, 1, 0, y, -z+1, -z, false);
		cuboid(-1, 1, 0, y, z-1, z, false);
		cuboid(x-1, x, 0, y, 1, -1, false);
		cuboid(-x+1,-x, 0, y, 1, -1, false);

		for (int i = -x; i < x; i++) {

			// up down
			cuboid(i-0.1, i+0.1, 0, y, -z+0.1, -z, false);
			cuboid(i-0.1, i+0.1, 0, y, z-0.1, z, false);

			cuboid(-x+0.1, -x, 0, y, i-0.1, i+0.1, false);
			cuboid(x-0.1, x, 0, y, i-0.1, i+0.1, false);

			if (i % 2 == 0) {
				// across ground
				cuboid(i-0.01, i+0.01, 0.01, 0, z, -z, false);
				cuboid(i-0.01, i+0.01, 0.01, 0, z, -z, false);

				cuboid(-x, x, 0.01, 0, i-0.01, i+0.01, false);
				cuboid(-x, x, 0.01, 0, i-0.01, i+0.01, false);
			}

			// roof
			cuboid(-x, x, y-0.1, y, i-0.1, i+0.1, false);
			cuboid(-x, x, y-0.1, y, i-0.1, i+0.1, false);

			cuboid(i-0.1, i+0.1, y-0.1, y, z, -z, false);
			cuboid(i-0.1, i+0.1, y-0.1, y, z, -z, false);

			if (i >= 0 && i <= y) {
				// other thing
				cuboid(x-0.1, x-0.1, i-0.1, i+0.1, z, -z, false);
				cuboid(-x+0.1, -x+0.1, i-0.1, i+0.1, z, -z, false);

				cuboid(-x, x, i-0.1, i+0.1, z, z-0.1, false);
				cuboid(x, -x, i-0.1, i+0.1, -z, -z+0.1, false);
			}
		}
}

void Draw::displayScene() {				// draw the world (room, furniture) then the GUI
	// Clear Color and Depth Buffers
	glMatrixMode(GL_MODELVIEW);
	// Reset transformations
	glLoadIdentity();
	// Set the camera
	std::vector<float> look = Agent::getLook();
	std::vector<float> stand = Agent::getStand();

	gluLookAt(	stand[0], stand[1], stand[2],		stand[0]+look[0], stand[1]+look[1],  stand[2]+look[2],		0.0f, 1.0f,  0.0f);

	room();
	std::vector<Article*> a = World::articles;
	std::vector<Game> g = World::games;
	for(int i = 0; i < g.size(); i++) {
			glPushMatrix();
			g[i].draw();
			glPopMatrix();
	}
	std::vector<image> im = World::images;
	for(int i = 0; i < im.size(); i++) {
			glPushMatrix();
			im[i].draw();
			glPopMatrix();
	}
	std::vector<Song> so = World::songs;
	for(int i = 0; i < so.size(); i++) {
			glPushMatrix();
			so[i].draw();
			glPopMatrix();
	}

	std::vector<door> d;
	d = World::doors;
	for(int i = 0; i < d.size(); i++) {
			glPushMatrix();
			d[i].draw();
			glPopMatrix();
	}

	std::vector<doc> docu;
	docu = World::documents;

	for(int i = 0; i < docu.size(); i++) {
			glPushMatrix();
			docu[i].draw();
			glPopMatrix();
	}
	//change to iterator and it->draw(); like in spacewar 


	Draw::displayGUI();

}

void Draw::button(int x, int y, int w, int h, char* text, bool pressed) {		// pressed changes the colour
	const char* t = text;
	const char* d = ".";
	int len = strcspn(t, d);
	int width = string(text, x, y-font::height, 400);
/*
	// outline
	glColor3d(1.0, 0.0, 0.0);
	int mini_border = BORDER / 10;
	rectangle(x-BORDER-mini_border, y-BORDER-mini_border, width+x+BORDER+mini_border, y-BORDER+mini_border);
	rectangle(x-BORDER-mini_border, y-BORDER-mini_border, x-BORDER+mini_border, h+BORDER+mini_border);
	rectangle(x-BORDER-mini_border, h+BORDER-mini_border, width+x+BORDER+mini_border, h+BORDER+mini_border);
	rectangle(width+x+BORDER-mini_border, y-BORDER-mini_border, width+x+BORDER+mini_border, h+BORDER+mini_border);
*/
	if (pressed) {
		glColor3d(1.0, 0.3, 0.3);
	} else {
		glColor3d(1.0, 0.5, 0.5);
	}

	rectangle(x-BORDER, y-BORDER, width+x+BORDER, h+BORDER);




}

void Draw::displayScreen() {				// menu for when the game is paused
	open2d();
	int px = PANE_BORDER;
	int py = PANE_BORDER;
	int pw = width * STARTING_WIDTH - PANE_BORDER;
	int ph = height * STARTING_HEIGHT - PANE_BORDER;

	int s = World::getSelected();
	if (s >= 0) {
		//Article* a = World::articles[s];

		//string(a->getDirectory(), px+BORDER, ph-BORDER*2, Draw::width*STARTING_WIDTH-px+BORDER*2);

		// articles work around, see findArticle in world.cpp for details, I think		-- when being made all the articles were ordered in a specific way, so they can be pulled out in that same way

		std::string c;
		int i = s;
		if (i >= World::games.size()) {
			i = World::games.size() - i;

			if (i >= World::doors.size()) {
				i = World::doors.size() - i;

				if (i >= World::documents.size()) {
					i = World::documents.size() - i;

					if (i >= World::songs.size()) {
						i = World::songs.size() - i;

						if (i >= World::images.size()) {
							i = World::images.size() - i;

							if (i >= World::videos.size()) {
								i = World::videos.size() - i;

							} else {
								c = World::videos[i].getDirectory();
							}

						} else {
							c = World::images[i].getDirectory();
						}

					} else {
						c = World::songs[i].getDirectory();
					}

				} else {
					c = World::documents[i].getDirectory();
				}

			} else {
				c = World::doors[i].getDirectory();
			}

		} else {
			c = World::games[i].getDirectory();
		}

		string(c, px+BORDER, ph-BORDER*2, Draw::width*STARTING_WIDTH-px+BORDER*2);

	}	else {
		string(World::directory, px+BORDER, ph-BORDER*2, Draw::width*STARTING_WIDTH-px+BORDER*2);
	}

	std::vector<UIE::Button> b = World::buttons;
	
	for(int i = 0; i < b.size(); i++) {
		button(b[i].getPosition()[0], b[i].getPosition()[1], b[i].getPosition()[2], b[i].getPosition()[3], b[i].getText(), b[i].getPressed());
	}
	if (World::getText() != NULL) {
		std::string s (World::getText());
		string(s, px+BORDER*2, ph-BORDER*2-LINE_HEIGHT*2, Draw::width*STARTING_WIDTH - (px+BORDER*2*4));
	}
	
	if (World::bmp_path != "") {
		unsigned char* image;
		image = World::getBitmap(NULL);

		std::vector<int> image_size = World::getBitmapSize();

		float res = calcRes(image_size[0], 1);
		Draw::bitmap(PANE_BORDER+BORDER, BORDER, -1, -1, image, image_size, res);
	}

	// it would have a brief desc on the article
		// the instructions/controls could be done by the article itself though
//	glColor4d(0.2, 0.2, 0.2, 1.0);
//	rectangleOutline(px, 0, pw, ph);
	glColor4d(0.9, 0.9, 0.9, 0.8);
	rectangle(px, 0, pw, ph);

	close2d();

}

void Draw::displayGUI() {		// in game GUI
	open2d();
	//see text drawing things from ORCA
	int wide = string("Portfolio by Mason Tilley", 10, height * STARTING_HEIGHT -20, Draw::width*STARTING_WIDTH);
	string("esc = to menu", 10, height * STARTING_HEIGHT -40, Draw::width*STARTING_WIDTH);

	glColor3d(0.9, 0.6, 0.2);
	rectangle(0, height * STARTING_HEIGHT, wide+BORDER, height * STARTING_HEIGHT - PANE_BORDER );


	if (World::getPaused() == false) {
		int centre_y = Draw::STARTING_HEIGHT * Draw::height / 2;
		int centre_x = Draw::STARTING_WIDTH * Draw::width / 2;


		if (World::findArticle(0, 0) == -1) {
			glColor3d(0, 0, 0);

		} else {
			glColor3d(1.0, 0.2, 0.2);

		}

		rectangle(centre_x - 1, centre_y - 10, centre_x + 1, centre_y + 10);
		rectangle(centre_x - 10, centre_y - 1, centre_x + 10, centre_y + 1);

	}


	/*
		esc = 		close screen (game, picture, menu)	/	go to menu
		enter = 	start game	/	select
		m = mute/unmute
		e = end song if playing
		
		need to have instructions for games
	*/
	close2d();
}

void Draw::open2d() {		// convenience method for glutting in 2d rather than 3

	glMatrixMode(GL_PROJECTION);

	glPushMatrix();
		glLoadIdentity();
		glOrtho(0.0, width * STARTING_WIDTH, 0.0, height * STARTING_HEIGHT,  0, 1);
		glMatrixMode(GL_MODELVIEW);

		glPushMatrix();
			glLoadIdentity();
			glMatrixMode(GL_MODELVIEW);

}

void Draw::close2d() {		// convenience method for going backk to glutting in 3d after having been in 2

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);

glPopMatrix();

//glFlush();
//	glSwapBuffers();
}

void Draw::colouring(int c) {		// sets the global colour variables based upon c, fades everything a bit out down the bottom as well

	if (c == -1) {
		red = rand() % 256 / 256;
		green = rand() % 256 / 256;
		blue = rand() % 256 / 256;
	} else if (c == 0) {
		red = 1;
		green = 1;
		blue = 1;
	} else if (c == 1) {
		red = 1;
		green = 0;
		blue = 0;
	} else if (c == 2) {
		red = 0;
		green = 1;
		blue = 0;
	} else if (c == 3) {
		red = 0;
		green = 0;
		blue = 1;
	} else if (c == 4) {
		red = 1;
		green = 1;
		blue = 0;
	} else if (c == 5) {
		red = 1;
		green = 0;
		blue = 1;
	} else if (c == 6) {
		red = 0;
		green = 1;
		blue = 1;
	} else if (c == 7) {
		red = 0.5;
		green = 1;
		blue = 1;
	} else if (c == 8) {
		red = 1;
		green = 0.5;
		blue = 1;
	} else if (c == 9) {
		red = 1;
		green = 1;
		blue = 0.5;
	} else if (c == 10) {
		red = 0.5;
		green = 0.5;
		blue = 0.5;
	}

	// said everything a bit out (un-saturation?)
	float r = 0.8;
	red = red*r;
	green = green*r;
	blue = blue*r;


}


void Draw::reshape(int w, int h) {			// when the window is reshaped

	Draw::height = (float) h / Draw::STARTING_HEIGHT;
	Draw::width =  (float) w / Draw::STARTING_WIDTH;
	Draw::ratio = Draw::width / Draw::height;
	Draw::frame_height = h;

	changeSize(w, h);

}

void Draw::changeSize(int w, int h) {			// resize the glut projections

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0) {
		h = 1;
	}
	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void Draw::initialiseDraw() {

	World::initWorld(NULL);

	myargv[0] = &v;
	glutInit(&myargc, myargv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(Draw::STARTING_WIDTH, Draw::STARTING_HEIGHT); // Set the window's initial width & height
	glutInitWindowPosition(250, 120); // Position the window's initial top-left corner
	glutCreateWindow(
			"Mason's Portfolio"); // Create a window with the given title
	glutDisplayFunc(Draw::display);
//	glutIdleFunc(Draw::display); // Register display callback handler for window re-paint
	glutReshapeFunc(Draw::reshape);
	glutKeyboardFunc(World::key);
	glutMouseFunc(World::mouse);
	glutPassiveMotionFunc(World::passiveMouse);
	glutSpecialFunc(World::specialKey);
//	Draw::time(0);

	glEnable(GL_DEPTH_TEST);

	glutMainLoop();           // Enter the infinitely event-processing loop

}

std::vector< int > Draw::pixelToGlut(int px, int py) {				// convert pixel coord to glut coord
	// could just save the actual height and width
	double current_height = Draw::height * Draw::STARTING_HEIGHT;
	double current_width =  Draw::width * Draw::STARTING_WIDTH;

//	double dx = ((px / current_width) * 2 - 1) * World::getResolution();
//	double dy = ((1 - (py / current_height)) * 2 - 1) * World::getResolution();
	// 1, 1 is now bottom right
		// has a problem with some negatives, I think primarily negative y

	double dx = ((px / current_width) * 2) * World::getResolution()[0];
	double dy = ((1 - (py / current_height)) * 2) * World::getResolution()[1];

	int x = dx;
	int y = dy;

	return std::vector<int> {x, y};
}

std::vector<int> Draw::getTextSize(std::string text, int max_width) {		// find out how much space the text would take up, text is the text to test, max_width the the maximum width of the line before starting the next one
	int wid = 0;
	int yid = font::height;
	int space = 0;
	int previous_space = 0;
		for (int i = 0; i < text.length(); i++) {
			if (space == i) {
				previous_space = space;
				space = text.find_first_of(" ", space+1);
				if (space == -1) {
					space = text.length();
				}
				if (space - previous_space == 1) {		// '  ' double space/ new line work around	-	the reading thing doesn't get new lines properly and this was quicker to fix
					wid = max_width;
				}
				for (int j = i; j < space; j++) {
					//wid += glutBitmapWidth( GLUT_BITMAP_TIMES_ROMAN_24 , text.at(j));
					wid+= font::width;
				}
				if (wid >= (max_width)) {
					yid+=font::height*7/4;
					wid = 0;

				}
			}

		}
		//glPopMatrix();
		// GLUT_BITMAP_TIMES_ROMAN_24
		if (yid > font::height) {
			return {max_width, (yid-1)*font::height*7/4 + font::height};
		}
		return {wid, font::height};
}

std::vector<int> Draw::getCentre() {		// get the centre of the window
	//return 	{glutGet(GLUT_WINDOW_X) + glutGet(GLUT_WINDOW_WIDTH)/2,
		//	glutGet(GLUT_WINDOW_Y) + glutGet(GLUT_WINDOW_HEIGHT)/2};

	return 	{glutGet(GLUT_WINDOW_WIDTH)/2,
				glutGet(GLUT_WINDOW_HEIGHT)/2};


}

