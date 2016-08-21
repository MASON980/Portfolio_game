/*
 * font.cpp
 *
 *  Created on: 4 Mar 2016
 *      Author: Mason
 */

#include "font.h"

#define FREEGLUT_STATIC
#include "GL/glut.h"
#include <math.h>

float font::width = 10;
float font::height = -20;
float font::thick = 2;

float font::x;
float font::y;
float font::z;
float font::o;

void font::vert (float wp, float yp) {		// transforms 2d vertice into 3d vertice
	float xp = -wp*sin(o);
	float zp = -wp*cos(o);
	float yyyyyy = font::y;
	double xx = font::x+xp/100;
	double yy = font::y+yp/100;
	double zz = font::z+zp/100;

	glVertex3d(xx, yy,  zz);
}





int font::drawChar (float ax, float ay, float  az, float ao, char c) {			// draws a 3d letter based upon the position and where the camera is looking from (the o variable, orientation)
	int a = (int) c;
//	font::y = font::y - height;
//	height = height;
	font::o = ao;
	font::x = ax;
	font::y = ay;
	font::z = az;
	switch (a) {
		// sfont::ymbol
	case 32:     // ' '
	{


		break;}
		case 33:     // '!'
		{
			glBegin(GL_LINES);
				vert(width*1/2, 0);
				vert(width*1/2, height*2/3);
				vert(width*1/2, height*4/5);
				vert(width*1/2, height);
			glEnd();
		break;}
		case 34:     // '"'
		{
			glBegin(GL_LINES);
				vert(width*1/3, 0);
				vert(width*1/3, height*1/4);
				vert(width*2/3, 0);
				vert(width*2/3, height*1/4);
			glEnd();
		break;}
		case 35:     // '#'
		{

		break;}
		case 36:     // '$'
		{

		break;}
		case 37:     // '%'
		{

		break;}
		case 38:     // '&'
		{

		break;}
		case 39:     // '''
		{

		break;}
		case 40:     // '('
		{

		break;}
		case 41:     // ')'
		{

		break;}
		case 42:     // '*'
		{

		break;}
		case 43:     // '+'
		{
			glBegin(GL_LINES);
				vert(width*1/2, height);
				vert(width*1/2, 0);
				vert(0, height*1/2);
				vert(width, height*1/2);
			glEnd();
		break;}
		case 44:     // ','
		{
			glBegin(GL_LINES);
				vert(width*2/5, height);
				vert(width*3/5, height*4/5);
			glEnd();
		break;}
		case 45:     // '-'
		{
			glBegin(GL_LINES);
				vert(0, height*1/2);
				vert(width, height*1/2);
			glEnd();
		break;}
		case 46:     // '.'
		{
			glBegin(GL_LINES);
				vert(width*2/5, height);
				vert(width*3/5, height);
			glEnd();
		break;}
		case 47:     // '/'
		{
			glBegin(GL_LINES);
				vert(0, height);
				vert(width, 0);
			glEnd();
		break;}


		// numbers
		case 48:     // '0'
		{
			glBegin(GL_LINE_LOOP);
				vert(width*1/2, 0);
				vert(width*4/11, 0);
				vert(width*3/11, height*1/5);
				vert(width*2/11, height*2/5);
				vert(width*2/11, height*3/5);
				vert(width*3/11, height*4/5);
				vert(width*4/11, height);

				vert(width*6/11, height*4/5);
				vert(width*7/11, height*3/5);
				vert(width*8/11, height*2/5);
				vert(width*8/11, height*1/5);
				vert(width*7/11, 0);
				vert(width*6/11, 0);
			glEnd();
		break;}
		case 49:     // '1'
		{
			glBegin(GL_LINE_STRIP);
				vert(width*1/2, height);
				vert(width*1/2, 0);
				vert(width*2/5, height*1/5);
			glEnd();
		break;}
		case 50:     // '2'
		{
			glBegin(GL_LINE_STRIP);
				vert(width*1/4, height*1/5);
				vert(width*1/2, 0);
				vert(width*3/4, height*1/5);
				vert(width*3/4, height*2/5);
				vert(width*1/4, height);
				vert(width*3/4, height);
			glEnd();
		break;}
		case 51:     // '3'
		{

		break;}
		case 52:     // '4'
		{

		break;}
		case 53:     // '5'
		{

		break;}
		case 54:     // '6'
		{

		break;}
		case 55:     // '7'
		{
			glBegin(GL_LINE_STRIP);
				vert(width*1/2, height);
				vert(width*4/5, 0);
				vert(width*2/5, 0);
			glEnd();
		break;}
		case 56:     // '8'
		{
			int h = height/2;
			glBegin(GL_LINE_LOOP);
				vert(width*1/2, 0);
				vert(width*4/10, 0);
				vert(width*3/10, h*1/5);
				vert(width*2/10, h*2/5);
				vert(width*2/10, h*3/5);
				vert(width*3/10, h*4/5);
				vert(width*4/10, h);

				vert(width*6/10, h*4/5);
				vert(width*7/10, h*3/5);
				vert(width*8/10, h*2/5);
				vert(width*8/10, h*1/5);
				vert(width*7/10, 0);
				vert(width*6/10, 0);
			glEnd();

			font::y = font::y +height;
			glBegin(GL_LINE_LOOP);
				vert(width*1/2, 0);
				vert(width*4/10, 0);
				vert(width*3/10, h*1/5);
				vert(width*2/10, h*2/5);
				vert(width*2/10, h*3/5);
				vert(width*3/10, h*4/5);
				vert(width*4/10, h);

				vert(width*6/10, h*4/5);
				vert(width*7/10, h*3/5);
				vert(width*8/10, h*2/5);
				vert(width*8/10, h*1/5);
				vert(width*7/10, 0);
				vert(width*6/10, 0);
			glEnd();
		break;}
		case 57:     // '9'
		{

		break;}


		case 58:     // ':'
		{
			glBegin(GL_LINES);
				vert(width*2/5, height*2/5);
				vert(width*3/5, height*2/5);

				vert(width*2/5, height*4/5);
				vert(width*3/5, height*4/5);
			glEnd();
		break;}
		case 59:     // ';'
		{

		break;}
		case 60:     // '<'
		{

		break;}
		case 61:     // '='
		{
			glBegin(GL_LINES);
				vert(width*1/10, height*2/4);
				vert(width*9/10, height*2/4);
				vert(width*1/10, height*3/4);
				vert(width*9/10, height*3/4);
			glEnd();
		break;}
		case 62:     // '>'
		{

		break;}
		case 63:     // '?'
		{

		break;}
		case 64:     // '@'
		{

		break;}


		// upper case
		case 65:     // 'A'
		{
			glBegin(GL_LINE_STRIP);
				vert(0, height);
				vert(width*1/2, 0);
				vert(width, height);
			glEnd();
			glBegin(GL_LINES);
				vert(width*1/4, height*1/2);
				vert(width*3/4, height*1/2);
			glEnd();
		break;}
		case 66:     // 'B'
		{
			glBegin(GL_LINE_LOOP);
				vert(0, 0);
				vert(width*6/10, 0);
				vert(width*7/10, height*1/10);
				vert(width*8/10, height*2/10);
				vert(width*8/10, height*3/10);
				vert(width*6/10, height*4/10);
				vert(width*0/10, height*5/10);

				vert(width*6/10, height*6/10);
				vert(width*8/10, height*7/10);
				vert(width*8/10, height*8/10);
				vert(width*7/10, height*9/10);
				vert(width*6/10, height);
				vert(0, height);
			glEnd();
		break;}
		case 67:     // 'C'
		{
			glBegin(GL_LINE_STRIP);
				vert(width, 0);
				vert(width*4/10, 0);
				vert(width*3/10, height*1/5);
				vert(width*2/10, height*2/5);
				vert(width*2/10, height*3/5);
				vert(width*3/10, height*4/5);
				vert(width*4/10, height);
				vert(width, height);
			glEnd();
		break;}
		case 68:     // 'D'
		{

			glBegin(GL_LINE_LOOP);
				vert(0, 0);
				vert(width*6/10, 0);
				vert(width*7/10, height*1/5);
				vert(width*8/10, height*2/5);
				vert(width*8/10, height*3/5);
				vert(width*7/10, height*4/5);
				vert(width*6/10, height);
				vert(0, height);
			glEnd();
		break;}
		case 69:     // 'E'
		{
			glBegin(GL_LINE_STRIP);
				vert(width, height);
				vert(0, height);
				vert(0, 0);
				vert(width, 0);
			glEnd();
			glBegin(GL_LINES);
				vert(0, height*1/2);
				vert(width*4/5, height*1/2);
			glEnd();
		break;}
		case 70:     // 'F'
		{
			glBegin(GL_LINE_STRIP);
				vert(width, 0);
				vert(0, 0);
				vert(0, height);
			glEnd();
			glBegin(GL_LINES);
				vert(0, height*1/2);
				vert(width*4/5, height*1/2);
			glEnd();
		break;}
		case 71:     // 'G'
		{
			glBegin(GL_LINE_STRIP);
				vert(width, 0);
				vert(width*4/10, 0);
				vert(width*3/10, height*1/5);
				vert(width*2/10, height*2/5);
				vert(width*2/10, height*3/5);
				vert(width*3/10, height*4/5);
				vert(width*4/10, height);
				vert(width, height);
				vert(width, height*1/2);
				vert(width*4/5, height*1/2);
			glEnd();
		break;}
		case 72:     // 'H'
		{
			glBegin(GL_LINES);
				vert(0, 0);
				vert(0, height);
				vert(width*9/10, 0);
				vert(width*9/10, height);
				vert(0, height*1/2);
				vert(width*9/10, height*1/2);
			glEnd();
		break;}
		case 73:     // 'I'
		{
			glBegin(GL_LINE_STRIP);
				vert(width*1/2, 0);
				vert(width*1/2, height);
			glEnd();
			glBegin(GL_LINES);
				vert(width*1/5, 0);
				vert(width*4/5, 0);
				vert(width*1/5, height);
				vert(width*4/5, height);
			glEnd();
		break;}
		case 74:     // 'J'
		{
			glBegin(GL_LINE_STRIP);
				vert(width*9/10, 0);
				vert(width*9/10, height);
				vert(0, height);
			glEnd();
		break;}
		case 75:     // 'K'
		{
			glBegin(GL_LINES);
				vert(0, 0);
				vert(0, height);
				vert(0, height*1/2);
				vert(width, 0);
				vert(0, height*1/2);
				vert(width, height);
			glEnd();

		break;}
		case 76:     // 'L'
		{
			glBegin(GL_LINE_STRIP);
				vert(0.1, 0);
				vert(0.1, height);
				vert(width, height);
			glEnd();
		break;}
		case 77:     // 'M'
		{
			glBegin(GL_LINE_STRIP);
				vert(0, height);
				vert(0, 0);
				vert(width*1/2, height*1/4);
				vert(width*9/10, 0);
				vert(width*9/10, height);
			glEnd();
		break;}
		case 78:     // 'N'
		{
			glBegin(GL_LINE_STRIP);
				vert(0, height);
				vert(0, 0);
				vert(width*9/10, height);
				vert(width*9/10, 0);
			glEnd();
		break;}
		case 79:     // 'O'
		{
			glBegin(GL_LINE_LOOP);
				vert(width*1/2, 0);
				vert(width*4/10, 0);
				vert(width*3/10, height*1/5);
				vert(width*1/10, height*2/5);
				vert(width*1/10, height*3/5);
				vert(width*3/10, height*4/5);
				vert(width*4/10, height);
				vert(width*6/10, height);

				vert(width*7/10, height*4/5);
				vert(width*9/10, height*3/5);
				vert(width, height*2/5);
				vert(width*9/10, height*1/5);
				vert(width*7/10, 0);
				vert(width*6/10, 0);
			glEnd();
		break;}
		case 80:     // 'P'
		{
			font::x += width/100;
			int w = -width;
			glBegin(GL_LINE_LOOP);
				vert(w, 0);
				vert(w*4/10, 0);
				vert(w*3/10, height*1/10);
				vert(w*2/10, height*2/10);
				vert(w*2/10, height*3/10);
				vert(w*3/10, height*4/10);
				vert(w*4/10, height*1/2);
				vert(w, height*1/2);
			glEnd();
			glBegin(GL_LINES);
				vert(w, height*1/2);
				vert(w, height);
			glEnd();
		break;}
		case 81:     // 'Q'
		{
			glBegin(GL_LINE_LOOP);
				vert(width*1/2, 0);
				vert(width*4/10, 0);
				vert(width*3/10, height*1/5);
				vert(width*1/10, height*2/5);
				vert(width*1/10, height*3/5);
				vert(width*3/10, height*4/5);
				vert(width*4/10, height);
				vert(width*6/10, height);

				vert(width*7/10, height*4/5);
				vert(width*9/10, height*3/5);
				vert(width, height*2/5);
				vert(width*9/10, height*1/5);
				vert(width*7/10, 0);
				vert(width*6/10, 0);
			glEnd();

			glBegin(GL_LINES);
				vert(width*1/2, height);
				vert(width, height);
			glEnd();
		break;}
		case 82:     // 'R'
		{
			font::x += width/100;
			int w = -width;
			glBegin(GL_LINE_LOOP);
				vert(w, 0);
				vert(w*4/10, 0);
				vert(w*3/10, height*1/10);
				vert(w*2/10, height*2/10);
				vert(w*2/10, height*3/10);
				vert(w*3/10, height*4/10);
				vert(w*4/10, height*1/2);
				vert(w, height*1/2);
			glEnd();
			glBegin(GL_LINES);
				vert(w, height*1/2);
				vert(w, height);

				vert(w, height*1/2);
				vert(0, height);
			glEnd();
		break;}
		case 83:     // 'S'
		{
			glBegin(GL_LINE_STRIP);
				vert(width*8/10, 0);
				vert(width*4/10, 0);
				vert(width*3/10, height*1/10);
				vert(width*2/10, height*2/10);
				vert(width*2/10, height*3/10);
				vert(width*3/10, height*4/10);
				vert(width*4/10, height*1/2);

				vert(width*6/10, height*6/10);
				vert(width*7/10, height*6/10);
				vert(width*8/10, height*8/10);
				vert(width*8/10, height*9/10);
				vert(width*7/10, height);
				vert(width*4/10, height);
				vert(width*1/10, height*9/10);
			glEnd();
		break;}
		case 84:     // 'T'
		{
			glBegin(GL_LINES);
				vert(0, 0);
				vert(width, 0);

				vert(width*1/2, 0);
				vert(width*1/2, height);
			glEnd();
		break;}
		case 85:     // 'U'
		{
			glBegin(GL_LINE_STRIP);
				vert(width*1/10, 0);
				vert(width*1/10, height);
				vert(width*9/10, height);
				vert(width*9/10, 0);
			glEnd();
		break;}
		case 86:     // 'V'
		{
			glBegin(GL_LINE_STRIP);
				vert(0, 0);
				vert(width*1/2, height);
				vert(width, 0);
			glEnd();
		break;}
		case 87:     // 'W'
		{
			glBegin(GL_LINE_STRIP);
				vert(0, 0);
				vert(width*1/4, height);
				vert(width*1/2, height*1/2);
				vert(width*3/4, height);
				vert(width, 0);
			glEnd();
		break;}
		case 88:     // 'X'
		{
			glBegin(GL_LINES);
				vert(0, 0);
				vert(width, height);
				vert(width, 0);
				vert(0, height);
			glEnd();
		break;}
		case 89:     // 'Y'
		{
			glBegin(GL_LINES);
				vert(0, 0);
				vert(width*1/2, height*1/2);
				vert(width, 0);
				vert(width*1/2, height*1/2);
				vert(width*1/2, height*1/2);
				vert(width*1/2, height);
			glEnd();
		break;}
		case 90:     // 'Z'
		{
			glBegin(GL_LINE_STRIP);
				vert(0, 0);
				vert(width, 0);
				vert(0, height);
				vert(width, height);
			glEnd();
		break;}


		// sfont::ymbols
		case 91:     // '['
		{

		break;}
		case 92:     // '\'
		{
			glBegin(GL_LINES);
				vert(0, 0);
				vert(width, height);
			glEnd();
		break;}
		case 93:     // ']'
		{

		break;}
		case 94:     // '^'
		{

		break;}
		case 95:     // '_'
		{
			glBegin(GL_LINES);
				vert(0, height);
				vert(width, height);
			glEnd();
		break;}
		case 96:     // '`'
		{

		break;}


		// lowercase
		case 97:     // 'a'
		{
			font::y = font::y +height/200;
			int h = height/2;
			glBegin(GL_LINE_LOOP);
				vert(width*1/2, 0);
				vert(width*4/10, 0);
				vert(width*3/10, h*1/5);
				vert(width*2/10, h*2/5);
				vert(width*2/10, h*3/5);
				vert(width*3/10, h*4/5);
				vert(width*4/10, h);

				vert(width*6/10, h*4/5);
				vert(width*7/10, h*3/5);
				vert(width*8/10, h*2/5);
				vert(width*8/10, h*1/5);
				vert(width*7/10, 0);
				vert(width*6/10, 0);
			glEnd();
			glBegin(GL_LINES);
				vert(width*8/10, 0);
				vert(width*8/10, h);
			glEnd();
		break;}
		case 98:     // 'b'
		{
			font::y = font::y +height/200;
			int h = height/2;
			glBegin(GL_LINE_LOOP);
				vert(width*1/2, 0);
				vert(width*4/10, 0);
				vert(width*3/10, h*1/5);
				vert(width*2/10, h*2/5);
				vert(width*2/10, h*3/5);
				vert(width*3/10, h*4/5);
				vert(width*4/10, h);

				vert(width*6/10, h*4/5);
				vert(width*7/10, h*3/5);
				vert(width*8/10, h*2/5);
				vert(width*8/10, h*1/5);
				vert(width*7/10, 0);
				vert(width*6/10, 0);
			glEnd();
			glBegin(GL_LINES);
				vert(width*2/10, -h);
				vert(width*2/10, h);
			glEnd();
		break;}
		case 99:     // 'c'
		{
			font::y = font::y +height/200;
			int h = height/2;
			glBegin(GL_LINE_STRIP);
				vert(width*8/10, h*1/5);
				vert(width*7/10, 0);
				vert(width*6/10, 0);

				vert(width*1/2, 0);
				vert(width*4/10, 0);
				vert(width*3/10, h*1/5);
				vert(width*2/10, h*2/5);
				vert(width*2/10, h*3/5);
				vert(width*3/10, h*4/5);
				vert(width*4/10, h);

				vert(width*6/10, h*4/5);
				vert(width*7/10, h*3/5);

			glEnd();
			return width;

		break;}
		case 100:     // 'd'
		{
			font::y = font::y +height/200;
			int h = height/2;
			glBegin(GL_LINE_LOOP);
				vert(width*1/2, 0);
				vert(width*4/10, 0);
				vert(width*3/10, h*1/5);
				vert(width*2/10, h*2/5);
				vert(width*2/10, h*3/5);
				vert(width*3/10, h*4/5);
				vert(width*4/10, h);

				vert(width*6/10, h*4/5);
				vert(width*7/10, h*3/5);
				vert(width*8/10, h*2/5);
				vert(width*8/10, h*1/5);
				vert(width*7/10, 0);
				vert(width*6/10, 0);
			glEnd();
			glBegin(GL_LINES);
				vert(width*8/10, h);
				vert(width*8/10, -h);
			glEnd();
		break;}
		case 101:     // 'e'
		{
			font::y = font::y +height/200;
			int h = height/2;
			glBegin(GL_LINE_STRIP);
				vert(width*1/10, h*2/5);

				vert(width*7/10, h*2/5);
				vert(width*7/10, h*1/5);
				vert(width*6/10, 0);
				vert(width*5/10, 0);

				vert(width*4/10, 0);
				vert(width*3/10, 0);
				vert(width*2/10, h*1/5);
				vert(width*1/10, h*2/5);
				vert(width*1/10, h*3/5);
				vert(width*2/10, h*4/5);
				vert(width*3/10, h);

				vert(width*5/10, h*4/5);
		//		vert(width*7/10, h*3/5);
			glEnd();
			return width;
		break;}
		case 102:     // 'f'
		{
			int h = height/2;
			glBegin(GL_LINE_STRIP);
				vert(width*8/10, h*2/5);
				vert(width*8/10, h*1/5);
				vert(width*7/10, 0);
				vert(width*6/10, 0);

				vert(width*1/2, 0);
				vert(width*4/10, 0);
				vert(width*3/10, h*1/5);
				vert(width*2/10, h*2/5);
				vert(width*2/10, h*2);
			glEnd();
			glBegin(GL_LINES);
				vert(0, h);
				vert(width*6/10, h);
			glEnd();
		break;}
		case 103:     // 'g'
		{
			font::y = font::y+height/200;
			int h = height/2;
			glBegin(GL_LINE_LOOP);
				vert(width*1/2, 0);
				vert(width*4/10, 0);
				vert(width*3/10, h*1/5);
				vert(width*2/10, h*2/5);
				vert(width*2/10, h*3/5);
				vert(width*3/10, h*4/5);
				vert(width*4/10, h);

				vert(width*6/10, h*4/5);
				vert(width*7/10, h*3/5);
				vert(width*8/10, h*2/5);
				vert(width*8/10, h*1/5);
				vert(width*7/10, 0);
				vert(width*6/10, 0);
			glEnd();
			glBegin(GL_LINE_STRIP);
				vert(width*8/10, 0);
				vert(width*8/10, height*4/5);
				vert(width*5/10, height);
				vert(width*2/10, height);
			glEnd();
		break;}
		case 104:     // 'h'
		{
			font::y = font::y +height/200;
			int h = height/2;
			glBegin(GL_LINE_STRIP);
				vert(width*8/10, h);
				vert(width*8/10, h*2/5);
				vert(width*7/10, h*1/5);
				vert(width*6/10, h*1/10);

				vert(width*1/2, 0);
				vert(width*4/10, h*1/10);
				vert(width*3/10, h*1/5);
				vert(width*2/10, h*2/5);
				vert(width*2/10, h);


			glEnd();
			glBegin(GL_LINES);
				vert(width*2/10, -h);
				vert(width*2/10, h);
			glEnd();
		break;}
		case 105:     // 'i'
		{
			glBegin(GL_LINES);
				vert(width*1/4, height*3/8);
				vert(width*1/4, height*1/4);

				vert(width*1/4, height*1/2);
				vert(width*1/4, height);
			glEnd();
			return width/2;
		break;}
		case 106:     // 'j'
		{
			glBegin(GL_LINES);
				vert(width*8/10, height*3/8);
				vert(width*8/10, height*1/4);
			glEnd();
			glBegin(GL_LINE_STRIP);
				vert(width*8/10, height*1/2);
				vert(width*8/10, height);
				vert(width*7/10, height*4/3);
				vert(width*6/10, height*3/2);
				vert(width*2/10, height*3/2);

			glEnd();
		break;}
		case 107:     // 'k'
		{
			glBegin(GL_LINES);
				vert(0, 0);
				vert(0, height);
				vert(0, height*3/4);
				vert(width*3/4, height*1/2);
				vert(0, height*3/4);
				vert(width*3/4, height);
			glEnd();
		break;}
		case 108:     // 'l'
		{
			glBegin(GL_LINES);
				vert(width*1/4, 0);
				vert(width*1/4, height);
			glEnd();
			return width/2;
		break;}
		case 109:     // 'm'
		{
			glBegin(GL_LINE_STRIP);
				vert(width*1/10, height);
				vert(width*1/10, height*1/2);
				vert(width*1/2, height*3/4);
				vert(width, height*1/2);
				vert(width, height);
			glEnd();
		break;}
		case 110:     // 'n'
		{
			glBegin(GL_LINE_STRIP);
				vert(width*1/5, height);
				vert(width*1/5, height*1/2);
				vert(width*4/5, height*1/2);
				vert(width*4/5, height);
			glEnd();
		break;}
		case 111:     // 'o'
		{
			font::y = font::y +height/200;
			int h = height/2;
			glBegin(GL_LINE_LOOP);
				vert(width*1/2, 0);
				vert(width*4/10, 0);
				vert(width*3/10, h*1/5);
				vert(width*2/10, h*2/5);
				vert(width*2/10, h*3/5);
				vert(width*3/10, h*4/5);
				vert(width*4/10, h);

				vert(width*6/10, h*4/5);
				vert(width*7/10, h*3/5);
				vert(width*8/10, h*2/5);
				vert(width*8/10, h*1/5);
				vert(width*7/10, 0);
				vert(width*6/10, 0);
			glEnd();
			return width;
		break;}
		case 112:     // 'p'
		{
			font::y = font::y+height/200;
			int h = height/2;
			glBegin(GL_LINE_LOOP);
				vert(width*1/2, 0);
				vert(width*4/10, 0);
				vert(width*3/10, h*1/5);
				vert(width*2/10, h*2/5);
				vert(width*2/10, h*3/5);
				vert(width*3/10, h*4/5);
				vert(width*4/10, h);

				vert(width*6/10, h*4/5);
				vert(width*7/10, h*3/5);
				vert(width*8/10, h*2/5);
				vert(width*8/10, h*1/5);
				vert(width*7/10, 0);
				vert(width*6/10, 0);
			glEnd();
			glBegin(GL_LINES);
				vert(width*2/10, 0);
				vert(width*2/10, height);
			glEnd();
		break;}
		case 113:     // 'q'
		{
			font::y = font::y+height/200;
			int h = height/2;
			glBegin(GL_LINE_LOOP);
				vert(width*1/2, 0);
				vert(width*4/10, 0);
				vert(width*3/10, h*1/5);
				vert(width*2/10, h*2/5);
				vert(width*2/10, h*3/5);
				vert(width*3/10, h*4/5);
				vert(width*4/10, h);

				vert(width*6/10, h*4/5);
				vert(width*7/10, h*3/5);
				vert(width*8/10, h*2/5);
				vert(width*8/10, h*1/5);
				vert(width*7/10, 0);
				vert(width*6/10, 0);
			glEnd();
			glBegin(GL_LINES);
				vert(width*8/10, 0);
				vert(width*8/10, height);
			glEnd();
		break;}
		case 114:     // 'r'
		{
			glBegin(GL_LINE_STRIP);
				vert(width*1/5, height);
				vert(width*1/5, height*1/2);
				vert(width, height*1/2);
			glEnd();
		break;}
		case 115:     // 's'
		{
			font::y = font::y + height*1/200;
			int h = height/2;
			glBegin(GL_LINE_STRIP);
				vert(width*8/10, 0);
				vert(width*4/10, 0);
				vert(width*3/10, h*1/10);
				vert(width*2/10, h*2/10);
				vert(width*2/10, h*3/10);
				vert(width*3/10, h*4/10);
				vert(width*4/10, h*1/2);

				vert(width*6/10, h*6/10);
				vert(width*7/10, h*7/10);
				vert(width*8/10, h*8/10);
				vert(width*8/10, h*9/10);
				vert(width*7/10, h);
				vert(width*1/2, h);
				vert(width*2/10, h*9/10);
			glEnd();
		break;}
		case 116:     // 't'
		{
			glBegin(GL_LINES);
				vert(width*1/2, height);
				vert(width*1/2, height*1/4);
				vert(0, height*1/2);
				vert(width, height*1/2);
			glEnd();
		break;}
		case 117:     // 'u'
		{
			glBegin(GL_LINE_STRIP);
				vert(width*2/10, height*1/2);
				vert(width*2/10, height);
				vert(width*8/10, height);
				vert(width*8/10, height*1/2);
			glEnd();
		break;}
		case 118:     // 'v'
		{
			glBegin(GL_LINE_STRIP);
				vert(0, height*1/2);
				vert(width*1/2, height);
				vert(width, height*1/2);
			glEnd();
		break;}
		case 119:     // 'w'
		{
			font::y = font::y + height*3/200;
			int h = -height;
			glBegin(GL_LINE_STRIP);
				vert(width/1/10, h);
				vert(width/1/10, h*1/2);
				vert(width*1/2, h*3/4);
				vert(width, h*1/2);
				vert(width, h);
			glEnd();
		break;}
		case 120:     // 'x'
		{
			glBegin(GL_LINES);
				vert(0, height*1/2);
				vert(width, height);
				vert(width, height*1/2);
				vert(0, height);
			glEnd();
		break;}
		case 121:     // 'y'
		{
			font::y = font::y +height/200;
			glBegin(GL_LINES);
				vert(width*1/2, height*1/2);
				vert(0, 0);
				vert(width, 0);
				vert(0, height);
			glEnd();
		break;}
		case 122:     // 'z'
		{
			glBegin(GL_LINE_STRIP);
				vert(0, height*1/2);
				vert(width, height*1/2);
				vert(0, height);
				vert(width, height);
			glEnd();
		break;}



		// symbol
		case 123:     // '{'
		{

		break;}
		case 124:     // '|'
		{

		break;}
		case 125:     // ';}'
		{

		break;}
		case 126:     // '~'
		{

		break;}
		case 127:     // 'DEL'
		{

		break;}
	}

	return width+2;

}























int font::drawChar (int x, int y, char c) {					// draw a character in 2d
	int a = (int) c;
//	y = y - height;
//	height = -height;

	switch (a) {
		// symbol
		case 32:     // ' '
		{

		break;}
		case 33:     // '!'
		{
			glBegin(GL_LINES);
				glVertex2d(x+width*1/2, y);
				glVertex2d(x+width*1/2, y+height*2/3);
				glVertex2d(x+width*1/2, y+height*4/5);
				glVertex2d(x+width*1/2, y+height);
			glEnd();
		break;}
		case 34:     // '"'
		{
			glBegin(GL_LINES);
				glVertex2d(x+width*1/3, y);
				glVertex2d(x+width*1/3, y+height*1/4);
				glVertex2d(x+width*2/3, y);
				glVertex2d(x+width*2/3, y+height*1/4);
			glEnd();
		break;}
		case 35:     // '#'
		{

		break;}
		case 36:     // '$'
		{

		break;}
		case 37:     // '%'
		{

		break;}
		case 38:     // '&'
		{

		break;}
		case 39:     // '''
		{

		break;}
		case 40:     // '('
		{

		break;}
		case 41:     // ')'
		{

		break;}
		case 42:     // '*'
		{

		break;}
		case 43:     // '+'
		{
			glBegin(GL_LINES);
				glVertex2d(x+width*1/2, y+height);
				glVertex2d(x+width*1/2, y);
				glVertex2d(x, y+height*1/2);
				glVertex2d(x+width, y+height*1/2);
			glEnd();
		break;}
		case 44:     // ','
		{
			glBegin(GL_LINES);
				glVertex2d(x+width*2/5, y+height);
				glVertex2d(x+width*3/5, y+height*4/5);
			glEnd();
		break;}
		case 45:     // '-'
		{
			glBegin(GL_LINES);
				glVertex2d(x, y+height*1/2);
				glVertex2d(x+width, y+height*1/2);
			glEnd();
		break;}
		case 46:     // '.'
		{
			glBegin(GL_LINES);
				glVertex2d(x+width*2/5, y+height);
				glVertex2d(x+width*3/5, y+height);
			glEnd();
		break;}
		case 47:     // '/'
		{
			glBegin(GL_LINES);
				glVertex2d(x, y+height);
				glVertex2d(x+width, y);
			glEnd();
		break;}


		// numbers
		case 48:     // '0'
		{
			glBegin(GL_LINE_LOOP);
				glVertex2d(x+width*1/2, y);
				glVertex2d(x+width*4/11, y);
				glVertex2d(x+width*3/11, y+height*1/5);
				glVertex2d(x+width*2/11, y+height*2/5);
				glVertex2d(x+width*2/11, y+height*3/5);
				glVertex2d(x+width*3/11, y+height*4/5);
				glVertex2d(x+width*4/11, y+height);

				glVertex2d(x+width*6/11, y+height*4/5);
				glVertex2d(x+width*7/11, y+height*3/5);
				glVertex2d(x+width*8/11, y+height*2/5);
				glVertex2d(x+width*8/11, y+height*1/5);
				glVertex2d(x+width*7/11, y);
				glVertex2d(x+width*6/11, y);
			glEnd();
		break;}
		case 49:     // '1'
		{
			glBegin(GL_LINE_STRIP);
				glVertex2d(x+width*1/2, y+height);
				glVertex2d(x+width*1/2, y);
				glVertex2d(x+width*2/5, y+height*1/5);
			glEnd();
		break;}
		case 50:     // '2'
		{
			glBegin(GL_LINE_STRIP);
				glVertex2d(x+width*1/4, y+height*1/5);
				glVertex2d(x+width*1/2, y+0);
				glVertex2d(x+width*3/4, y+height*1/5);
				glVertex2d(x+width*3/4, y+height*2/5);
				glVertex2d(x+width*1/4, y+height);
				glVertex2d(x+width*3/4, y+height);
			glEnd();
		break;}
		case 51:     // '3'
		{

		break;}
		case 52:     // '4'
		{

		break;}
		case 53:     // '5'
		{

		break;}
		case 54:     // '6'
		{

		break;}
		case 55:     // '7'
		{
			glBegin(GL_LINE_STRIP);
				glVertex2d(x+width*1/2, y+height);
				glVertex2d(x+width*4/5, y);
				glVertex2d(x+width*2/5, y);
			glEnd();
		break;}
		case 56:     // '8'
		{
			int h = height/2;
			glBegin(GL_LINE_LOOP);
				glVertex2d(x+width*1/2, y);
				glVertex2d(x+width*4/10, y);
				glVertex2d(x+width*3/10, y+h*1/5);
				glVertex2d(x+width*2/10, y+h*2/5);
				glVertex2d(x+width*2/10, y+h*3/5);
				glVertex2d(x+width*3/10, y+h*4/5);
				glVertex2d(x+width*4/10, y+h);

				glVertex2d(x+width*6/10, y+h*4/5);
				glVertex2d(x+width*7/10, y+h*3/5);
				glVertex2d(x+width*8/10, y+h*2/5);
				glVertex2d(x+width*8/10, y+h*1/5);
				glVertex2d(x+width*7/10, y);
				glVertex2d(x+width*6/10, y);
			glEnd();

			y = y+height/2;
			glBegin(GL_LINE_LOOP);
				glVertex2d(x+width*1/2, y);
				glVertex2d(x+width*4/10, y);
				glVertex2d(x+width*3/10, y+h*1/5);
				glVertex2d(x+width*2/10, y+h*2/5);
				glVertex2d(x+width*2/10, y+h*3/5);
				glVertex2d(x+width*3/10, y+h*4/5);
				glVertex2d(x+width*4/10, y+h);

				glVertex2d(x+width*6/10, y+h*4/5);
				glVertex2d(x+width*7/10, y+h*3/5);
				glVertex2d(x+width*8/10, y+h*2/5);
				glVertex2d(x+width*8/10, y+h*1/5);
				glVertex2d(x+width*7/10, y);
				glVertex2d(x+width*6/10, y);
			glEnd();
		break;}
		case 57:     // '9'
		{

		break;}


		case 58:     // ':'
		{
			glBegin(GL_LINES);
				glVertex2d(x+width*2/5, y+height*2/5);
				glVertex2d(x+width*3/5, y+height*2/5);

				glVertex2d(x+width*2/5, y+height*4/5);
				glVertex2d(x+width*3/5, y+height*4/5);
			glEnd();
		break;}
		case 59:     // ';'
		{

		break;}
		case 60:     // '<'
		{

		break;}
		case 61:     // '='
		{
			glBegin(GL_LINES);
				glVertex2d(x+width*1/10, y+height*2/4);
				glVertex2d(x+width*9/10, y+height*2/4);
				glVertex2d(x+width*1/10, y+height*3/4);
				glVertex2d(x+width*9/10, y+height*3/4);
			glEnd();
		break;}
		case 62:     // '>'
		{

		break;}
		case 63:     // '?'
		{

		break;}
		case 64:     // '@'
		{

		break;}


		// upper case
		case 65:     // 'A'
		{
			glBegin(GL_LINE_STRIP);
				glVertex2d(x, y+height);
				glVertex2d(x+width*1/2, y);
				glVertex2d(x+width, y+height);
			glEnd();
			glBegin(GL_LINES);
				glVertex2d(x+width*1/4, y+height*1/2);
				glVertex2d(x+width*3/4, y+height*1/2);
			glEnd();
		break;}
		case 66:     // 'B'
		{
			glBegin(GL_LINE_LOOP);
				glVertex2d(x, y);
				glVertex2d(x+width*6/10, y);
				glVertex2d(x+width*7/10, y+height*1/10);
				glVertex2d(x+width*8/10, y+height*2/10);
				glVertex2d(x+width*8/10, y+height*3/10);
				glVertex2d(x+width*6/10, y+height*4/10);
				glVertex2d(x+width*0/10, y+height*5/10);

				glVertex2d(x+width*6/10, y+height*6/10);
				glVertex2d(x+width*8/10, y+height*7/10);
				glVertex2d(x+width*8/10, y+height*8/10);
				glVertex2d(x+width*7/10, y+height*9/10);
				glVertex2d(x+width*6/10, y+height);
				glVertex2d(x, y+height);
			glEnd();
		break;}
		case 67:     // 'C'
		{
			glBegin(GL_LINE_STRIP);
				glVertex2d(x+width, y);
				glVertex2d(x+width*4/10, y);
				glVertex2d(x+width*3/10, y+height*1/5);
				glVertex2d(x+width*2/10, y+height*2/5);
				glVertex2d(x+width*2/10, y+height*3/5);
				glVertex2d(x+width*3/10, y+height*4/5);
				glVertex2d(x+width*4/10, y+height);
				glVertex2d(x+width, y+height);
			glEnd();
		break;}
		case 68:     // 'D'
		{
			x += width;
			int w = -width;
			glBegin(GL_LINE_LOOP);
				glVertex2d(x+w, y);
				glVertex2d(x+w*4/10, y);
				glVertex2d(x+w*3/10, y+height*1/5);
				glVertex2d(x+w*2/10, y+height*2/5);
				glVertex2d(x+w*2/10, y+height*3/5);
				glVertex2d(x+w*3/10, y+height*4/5);
				glVertex2d(x+w*4/10, y+height);
				glVertex2d(x+w, y+height);
			glEnd();
		break;}
		case 69:     // 'E'
		{
			glBegin(GL_LINE_STRIP);
				glVertex2d(x+width, y+height);
				glVertex2d(x, y+height);
				glVertex2d(x, y);
				glVertex2d(x+width, y);
			glEnd();
			glBegin(GL_LINES);
				glVertex2d(x, y+height*1/2);
				glVertex2d(x+width*4/5, y+height*1/2);
			glEnd();
		break;}
		case 70:     // 'F'
		{
			glBegin(GL_LINE_STRIP);
				glVertex2d(x+width, y);
				glVertex2d(x, y);
				glVertex2d(x, y+height);
			glEnd();
			glBegin(GL_LINES);
				glVertex2d(x, y+height*1/2);
				glVertex2d(x+width*4/5, y+height*1/2);
			glEnd();
		break;}
		case 71:     // 'G'
		{
			glBegin(GL_LINE_STRIP);
				glVertex2d(x+width, y);
				glVertex2d(x+width*4/10, y);
				glVertex2d(x+width*3/10, y+height*1/5);
				glVertex2d(x+width*2/10, y+height*2/5);
				glVertex2d(x+width*2/10, y+height*3/5);
				glVertex2d(x+width*3/10, y+height*4/5);
				glVertex2d(x+width*4/10, y+height);
				glVertex2d(x+width, y+height);
				glVertex2d(x+width, y+height*1/2);
				glVertex2d(x+width*4/5, y+height*1/2);
			glEnd();
		break;}
		case 72:     // 'H'
		{
			glBegin(GL_LINES);
				glVertex2d(x, y);
				glVertex2d(x, y+height);
				glVertex2d(x+width*9/10, y);
				glVertex2d(x+width*9/10, y+height);
				glVertex2d(x, y+height*1/2);
				glVertex2d(x+width*9/10, y+height*1/2);
			glEnd();
		break;}
		case 73:     // 'I'
		{
			glBegin(GL_LINE_STRIP);
				glVertex2d(x+width*1/2, y);
				glVertex2d(x+width*1/2, y+height);
			glEnd();
			glBegin(GL_LINES);
				glVertex2d(x+width*1/4, y);
				glVertex2d(x+width*3/4, y);
				glVertex2d(x+width*1/4, y+height);
				glVertex2d(x+width*3/4, y+height);
			glEnd();
		break;}
		case 74:     // 'J'
		{
			glBegin(GL_LINE_STRIP);
				glVertex2d(x+width*9/10, y);
				glVertex2d(x+width*9/10, y+height);
				glVertex2d(x, y+height);
			glEnd();
		break;}
		case 75:     // 'K'
		{
			glBegin(GL_LINES);
				glVertex2d(x, y);
				glVertex2d(x, y+height);
				glVertex2d(x, y+height*1/2);
				glVertex2d(x+width, y);
				glVertex2d(x, y+height*1/2);
				glVertex2d(x+width, y+height);
			glEnd();

		break;}
		case 76:     // 'L'
		{
			glBegin(GL_LINE_STRIP);
				glVertex2d(x, y);
				glVertex2d(x, y+height);
				glVertex2d(x+width, y+height);
			glEnd();
		break;}
		case 77:     // 'M'
		{
			glBegin(GL_LINE_STRIP);
				glVertex2d(x, y+height);
				glVertex2d(x, y);
				glVertex2d(x+width*1/2, y+height*1/4);
				glVertex2d(x+width*9/10, y);
				glVertex2d(x+width*9/10, y+height);
			glEnd();
		break;}
		case 78:     // 'N'
		{
			glBegin(GL_LINE_STRIP);
				glVertex2d(x, y+height);
				glVertex2d(x, y);
				glVertex2d(x+width*9/10, y+height);
				glVertex2d(x+width*9/10, y);
			glEnd();
		break;}
		case 79:     // 'O'
		{
			glBegin(GL_LINE_LOOP);
				glVertex2d(x+width*1/2, y);
				glVertex2d(x+width*4/10, y);
				glVertex2d(x+width*3/10, y+height*1/5);
				glVertex2d(x+width*1/10, y+height*2/5);
				glVertex2d(x+width*1/10, y+height*3/5);
				glVertex2d(x+width*3/10, y+height*4/5);
				glVertex2d(x+width*4/10, y+height);
				glVertex2d(x+width*6/10, y+height);

				glVertex2d(x+width*7/10, y+height*4/5);
				glVertex2d(x+width*9/10, y+height*3/5);
				glVertex2d(x+width, y+height*2/5);
				glVertex2d(x+width*9/10, y+height*1/5);
				glVertex2d(x+width*7/10, y);
				glVertex2d(x+width*6/10, y);
			glEnd();
		break;}
		case 80:     // 'P'
		{
			x += width;
			int w = -width;
			glBegin(GL_LINE_LOOP);
				glVertex2d(x+w, y);
				glVertex2d(x+w*4/10, y);
				glVertex2d(x+w*3/10, y+height*1/10);
				glVertex2d(x+w*2/10, y+height*2/10);
				glVertex2d(x+w*2/10, y+height*3/10);
				glVertex2d(x+w*3/10, y+height*4/10);
				glVertex2d(x+w*4/10, y+height*1/2);
				glVertex2d(x+w, y+height*1/2);
			glEnd();
			glBegin(GL_LINES);
				glVertex2d(x+w, y+height*1/2);
				glVertex2d(x+w, y+height);
			glEnd();
		break;}
		case 81:     // 'Q'
		{
			glBegin(GL_LINE_LOOP);
				glVertex2d(x+width*1/2, y);
				glVertex2d(x+width*4/10, y);
				glVertex2d(x+width*3/10, y+height*1/5);
				glVertex2d(x+width*1/10, y+height*2/5);
				glVertex2d(x+width*1/10, y+height*3/5);
				glVertex2d(x+width*3/10, y+height*4/5);
				glVertex2d(x+width*4/10, y+height);
				glVertex2d(x+width*6/10, y+height);

				glVertex2d(x+width*7/10, y+height*4/5);
				glVertex2d(x+width*9/10, y+height*3/5);
				glVertex2d(x+width, y+height*2/5);
				glVertex2d(x+width*9/10, y+height*1/5);
				glVertex2d(x+width*7/10, y);
				glVertex2d(x+width*6/10, y);
			glEnd();

			glBegin(GL_LINES);
				glVertex2d(x+width*1/2, y+height);
				glVertex2d(x+width, y+height);
			glEnd();
		break;}
		case 82:     // 'R'
		{
			x += width;
			int w = -width;
			glBegin(GL_LINE_LOOP);
				glVertex2d(x+w, y);
				glVertex2d(x+w*4/10, y);
				glVertex2d(x+w*3/10, y+height*1/10);
				glVertex2d(x+w*2/10, y+height*2/10);
				glVertex2d(x+w*2/10, y+height*3/10);
				glVertex2d(x+w*3/10, y+height*4/10);
				glVertex2d(x+w*4/10, y+height*1/2);
				glVertex2d(x+w, y+height*1/2);
			glEnd();
			glBegin(GL_LINES);
				glVertex2d(x+w, y+height*1/2);
				glVertex2d(x+w, y+height);

				glVertex2d(x+w, y+height*1/2);
				glVertex2d(x, y+height);
			glEnd();
		break;}
		case 83:     // 'S'
		{
			glBegin(GL_LINE_STRIP);
				glVertex2d(x+width*8/10, y);
				glVertex2d(x+width*4/10, y);
				glVertex2d(x+width*3/10, y+height*1/10);
				glVertex2d(x+width*2/10, y+height*2/10);
				glVertex2d(x+width*2/10, y+height*3/10);
				glVertex2d(x+width*3/10, y+height*4/10);
				glVertex2d(x+width*4/10, y+height*1/2);

				glVertex2d(x+width*6/10, y+height*6/10);
				glVertex2d(x+width*7/10, y+height*6/10);
				glVertex2d(x+width*8/10, y+height*8/10);
				glVertex2d(x+width*8/10, y+height*9/10);
				glVertex2d(x+width*7/10, y+height);
				glVertex2d(x+width*4/10, y+height);
				glVertex2d(x+width*1/10, y+height*9/10);
			glEnd();
		break;}
		case 84:     // 'T'
		{
			glBegin(GL_LINES);
				glVertex2d(x, y);
				glVertex2d(x+width, y);

				glVertex2d(x+width*1/2, y);
				glVertex2d(x+width*1/2, y+height);
			glEnd();
		break;}
		case 85:     // 'U'
		{
			glBegin(GL_LINE_STRIP);
				glVertex2d(x+width*1/10, y);
				glVertex2d(x+width*1/10, y+height);
				glVertex2d(x+width*9/10, y+height);
				glVertex2d(x+width*9/10, y);
			glEnd();
		break;}
		case 86:     // 'V'
		{
			glBegin(GL_LINE_STRIP);
				glVertex2d(x, y);
				glVertex2d(x+width*1/2, y+height);
				glVertex2d(x+width, y);
			glEnd();
		break;}
		case 87:     // 'W'
		{
			glBegin(GL_LINE_STRIP);
				glVertex2d(x, y);
				glVertex2d(x+width*1/4, y+height);
				glVertex2d(x+width*1/2, y+height*1/2);
				glVertex2d(x+width*3/4, y+height);
				glVertex2d(x+width, y);
			glEnd();
		break;}
		case 88:     // 'X'
		{
			glBegin(GL_LINES);
				glVertex2d(x, y);
				glVertex2d(x+width, y+height);
				glVertex2d(x+width, y);
				glVertex2d(x, y+height);
			glEnd();
		break;}
		case 89:     // 'Y'
		{
			glBegin(GL_LINES);
				glVertex2d(x, y);
				glVertex2d(x+width*1/2, y+height*1/2);
				glVertex2d(x+width, y);
				glVertex2d(x+width*1/2, y+height*1/2);
				glVertex2d(x+width*1/2, y+height*1/2);
				glVertex2d(x+width*1/2, y+height);
			glEnd();
		break;}
		case 90:     // 'Z'
		{
			glBegin(GL_LINE_STRIP);
				glVertex2d(x, y);
				glVertex2d(x+width, y);
				glVertex2d(x, y+height);
				glVertex2d(x+width, y+height);
			glEnd();
		break;}


		// symbols
		case 91:     // '['
		{

		break;}
		case 92:     // '\'
		{
			glBegin(GL_LINES);
				glVertex2d(x, y);
				glVertex2d(x+width, y+height);
			glEnd();
		break;}
		case 93:     // ']'
		{

		break;}
		case 94:     // '^'
		{

		break;}
		case 95:     // '_'
		{
			glBegin(GL_LINES);
				glVertex2d(x, y+height);
				glVertex2d(x+width, y+height);
			glEnd();
		break;}
		case 96:     // '`'
		{

		break;}


		// lowercase
		case 97:     // 'a'
		{
			y = y+height/2;
			int h = height/2;
			glBegin(GL_LINE_LOOP);
				glVertex2d(x+width*1/2, y);
				glVertex2d(x+width*4/10, y);
				glVertex2d(x+width*3/10, y+h*1/5);
				glVertex2d(x+width*2/10, y+h*2/5);
				glVertex2d(x+width*2/10, y+h*3/5);
				glVertex2d(x+width*3/10, y+h*4/5);
				glVertex2d(x+width*4/10, y+h);

				glVertex2d(x+width*6/10, y+h*4/5);
				glVertex2d(x+width*7/10, y+h*3/5);
				glVertex2d(x+width*8/10, y+h*2/5);
				glVertex2d(x+width*8/10, y+h*1/5);
				glVertex2d(x+width*7/10, y);
				glVertex2d(x+width*6/10, y);
			glEnd();
			glBegin(GL_LINES);
				glVertex2d(x+width*8/10, y);
				glVertex2d(x+width*8/10, y+h);
			glEnd();
		break;}
		case 98:     // 'b'
		{
			y = y+height/2;
			int h = height/2;
			glBegin(GL_LINE_LOOP);
				glVertex2d(x+width*1/2, y);
				glVertex2d(x+width*4/10, y);
				glVertex2d(x+width*3/10, y+h*1/5);
				glVertex2d(x+width*2/10, y+h*2/5);
				glVertex2d(x+width*2/10, y+h*3/5);
				glVertex2d(x+width*3/10, y+h*4/5);
				glVertex2d(x+width*4/10, y+h);

				glVertex2d(x+width*6/10, y+h*4/5);
				glVertex2d(x+width*7/10, y+h*3/5);
				glVertex2d(x+width*8/10, y+h*2/5);
				glVertex2d(x+width*8/10, y+h*1/5);
				glVertex2d(x+width*7/10, y);
				glVertex2d(x+width*6/10, y);
			glEnd();
			glBegin(GL_LINES);
				glVertex2d(x+width*2/10, y-h);
				glVertex2d(x+width*2/10, y+h);
			glEnd();
		break;}
		case 99:     // 'c'
		{
			y = y+height/2;
			int h = height/2;
			glBegin(GL_LINE_STRIP);
				glVertex2d(x+width*8/10, y+h*1/5);
				glVertex2d(x+width*7/10, y);
				glVertex2d(x+width*6/10, y);

				glVertex2d(x+width*1/2, y);
				glVertex2d(x+width*4/10, y);
				glVertex2d(x+width*3/10, y+h*1/5);
				glVertex2d(x+width*2/10, y+h*2/5);
				glVertex2d(x+width*2/10, y+h*3/5);
				glVertex2d(x+width*3/10, y+h*4/5);
				glVertex2d(x+width*4/10, y+h);

				glVertex2d(x+width*6/10, y+h*4/5);
				glVertex2d(x+width*7/10, y+h*3/5);

			glEnd();
			return width;

		break;}
		case 100:     // 'd'
		{
			y = y+height/2;
			int h = height/2;
			glBegin(GL_LINE_LOOP);
				glVertex2d(x+width*1/2, y);
				glVertex2d(x+width*4/10, y);
				glVertex2d(x+width*3/10, y+h*1/5);
				glVertex2d(x+width*2/10, y+h*2/5);
				glVertex2d(x+width*2/10, y+h*3/5);
				glVertex2d(x+width*3/10, y+h*4/5);
				glVertex2d(x+width*4/10, y+h);

				glVertex2d(x+width*6/10, y+h*4/5);
				glVertex2d(x+width*7/10, y+h*3/5);
				glVertex2d(x+width*8/10, y+h*2/5);
				glVertex2d(x+width*8/10, y+h*1/5);
				glVertex2d(x+width*7/10, y);
				glVertex2d(x+width*6/10, y);
			glEnd();
			glBegin(GL_LINES);
				glVertex2d(x+width*8/10, y-h);
				glVertex2d(x+width*8/10, y+h);
			glEnd();
		break;}
		case 101:     // 'e'
		{
			y = y+height/2;
			int h = height/2;
			glBegin(GL_LINE_STRIP);
				glVertex2d(x+width*1/10, y+h*2/5);

				glVertex2d(x+width*7/10, y+h*2/5);
				glVertex2d(x+width*7/10, y+h*1/5);
				glVertex2d(x+width*6/10, y);
				glVertex2d(x+width*5/10, y);

				glVertex2d(x+width*4/10, y);
				glVertex2d(x+width*3/10, y);
				glVertex2d(x+width*2/10, y+h*1/5);
				glVertex2d(x+width*1/10, y+h*2/5);
				glVertex2d(x+width*1/10, y+h*3/5);
				glVertex2d(x+width*2/10, y+h*4/5);
				glVertex2d(x+width*3/10, y+h);

				glVertex2d(x+width*5/10, y+h*4/5);
		//		glVertex2d(x+width*7/10, y+h*3/5);
			glEnd();
			return width;
		break;}
		case 102:     // 'f'
		{
			int h = height/2;
			glBegin(GL_LINE_STRIP);
				glVertex2d(x+width*8/10, y+h*2/5);
				glVertex2d(x+width*8/10, y+h*1/5);
				glVertex2d(x+width*7/10, y);
				glVertex2d(x+width*6/10, y);

				glVertex2d(x+width*1/2, y);
				glVertex2d(x+width*4/10, y);
				glVertex2d(x+width*3/10, y+h*1/5);
				glVertex2d(x+width*2/10, y+h*2/5);
				glVertex2d(x+width*2/10, y+h*2);
			glEnd();
			glBegin(GL_LINES);
				glVertex2d(x, y+h);
				glVertex2d(x+width*6/10, y+h);
			glEnd();
		break;}
		case 103:     // 'g'
		{
			int h = height/2;
			y = y+h;
			glBegin(GL_LINE_LOOP);
				glVertex2d(x+width*1/2, y);
				glVertex2d(x+width*4/10, y);
				glVertex2d(x+width*3/10, y+h*1/5);
				glVertex2d(x+width*2/10, y+h*2/5);
				glVertex2d(x+width*2/10, y+h*3/5);
				glVertex2d(x+width*3/10, y+h*4/5);
				glVertex2d(x+width*4/10, y+h);

				glVertex2d(x+width*6/10, y+h*4/5);
				glVertex2d(x+width*7/10, y+h*3/5);
				glVertex2d(x+width*8/10, y+h*2/5);
				glVertex2d(x+width*8/10, y+h*1/5);
				glVertex2d(x+width*7/10, y);
				glVertex2d(x+width*6/10, y);
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex2d(x+width*8/10, y);
				glVertex2d(x+width*8/10, y+height*4/5);
				glVertex2d(x+width*5/10, y+height);
				glVertex2d(x+width*2/10, y+height);
			glEnd();
		break;}
		case 104:     // 'h'
		{
			y = y+height/2;
			int h = height/2;
			glBegin(GL_LINE_STRIP);
				glVertex2d(x+width*8/10, y+h);
				glVertex2d(x+width*8/10, y+h*2/5);
				glVertex2d(x+width*7/10, y+h*1/5);
				glVertex2d(x+width*6/10, y+h*1/10);

				glVertex2d(x+width*1/2, y);
				glVertex2d(x+width*4/10, y+h*1/10);
				glVertex2d(x+width*3/10, y+h*1/5);
				glVertex2d(x+width*2/10, y+h*2/5);
				glVertex2d(x+width*2/10, y+h);


			glEnd();
			glBegin(GL_LINES);
				glVertex2d(x+width*2/10, y-h);
				glVertex2d(x+width*2/10, y+h);
			glEnd();
		break;}
		case 105:     // 'i'
		{
			glBegin(GL_LINES);
				glVertex2d(x+width*1/4, y+height*3/8);
				glVertex2d(x+width*1/4, y+height*1/4);

				glVertex2d(x+width*1/4, y+height*1/2);
				glVertex2d(x+width*1/4, y+height);
			glEnd();
			return width/2;
		break;}
		case 106:     // 'j'
		{
			glBegin(GL_LINES);
				glVertex2d(x+width*8/10, y+height*3/8);
				glVertex2d(x+width*8/10, y+height*1/4);
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex2d(x+width*8/10, y+height*1/2);
				glVertex2d(x+width*8/10, y+height);
				glVertex2d(x+width*7/10, y+height*4/3);
				glVertex2d(x+width*6/10, y+height*3/2);
				glVertex2d(x+width*2/10, y+height*3/2);

			glEnd();
		break;}
		case 107:     // 'k'
		{
			glBegin(GL_LINES);
				glVertex2d(x+width/5, y);
				glVertex2d(x+width/5, y+height);
				glVertex2d(x+width/5, y+height*3/4);
				glVertex2d(x+width, y+height*1/2);
				glVertex2d(x+width/5, y+height*3/4);
				glVertex2d(x+width, y+height);
			glEnd();
		break;}
		case 108:     // 'l'
		{
			glBegin(GL_LINES);
				glVertex2d(x+width*1/4, y);
				glVertex2d(x+width*1/4, y+height);
			glEnd();
			return width/2;
		break;}
		case 109:     // 'm'
		{
			glBegin(GL_LINE_STRIP);
				glVertex2d(x+width/1/10, y+height);
				glVertex2d(x+width/1/10, y+height*1/2);
				glVertex2d(x+width*1/2, y+height*3/4);
				glVertex2d(x+width, y+height*1/2);
				glVertex2d(x+width, y+height);
			glEnd();
		break;}
		case 110:     // 'n'
		{
			glBegin(GL_LINE_STRIP);
				glVertex2d(x+width*1/5, y+height);
				glVertex2d(x+width*1/5, y+height*1/2);
				glVertex2d(x+width*4/5, y+height*1/2);
				glVertex2d(x+width*4/5, y+height);
			glEnd();
		break;}
		case 111:     // 'o'
		{
			y = y+height/2;
			int h = height/2;
			glBegin(GL_LINE_LOOP);
				glVertex2d(x+width*1/2, y);
				glVertex2d(x+width*4/10, y);
				glVertex2d(x+width*3/10, y+h*1/5);
				glVertex2d(x+width*2/10, y+h*2/5);
				glVertex2d(x+width*2/10, y+h*3/5);
				glVertex2d(x+width*3/10, y+h*4/5);
				glVertex2d(x+width*4/10, y+h);

				glVertex2d(x+width*6/10, y+h*4/5);
				glVertex2d(x+width*7/10, y+h*3/5);
				glVertex2d(x+width*8/10, y+h*2/5);
				glVertex2d(x+width*8/10, y+h*1/5);
				glVertex2d(x+width*7/10, y);
				glVertex2d(x+width*6/10, y);
			glEnd();
			return width;
		break;}
		case 112:     // 'p'
		{
			int h = height/2;
			y = y+h;
			glBegin(GL_LINE_LOOP);
				glVertex2d(x+width*1/2, y);
				glVertex2d(x+width*4/10, y);
				glVertex2d(x+width*3/10, y+h*1/5);
				glVertex2d(x+width*2/10, y+h*2/5);
				glVertex2d(x+width*2/10, y+h*3/5);
				glVertex2d(x+width*3/10, y+h*4/5);
				glVertex2d(x+width*4/10, y+h);

				glVertex2d(x+width*6/10, y+h*4/5);
				glVertex2d(x+width*7/10, y+h*3/5);
				glVertex2d(x+width*8/10, y+h*2/5);
				glVertex2d(x+width*8/10, y+h*1/5);
				glVertex2d(x+width*7/10, y);
				glVertex2d(x+width*6/10, y);
			glEnd();
			glBegin(GL_LINES);
				glVertex2d(x+width*2/10, y);
				glVertex2d(x+width*2/10, y+height);
			glEnd();
		break;}
		case 113:     // 'q'
		{
			int h = height/2;
			y = y+h;
			glBegin(GL_LINE_LOOP);
				glVertex2d(x+width*1/2, y);
				glVertex2d(x+width*4/10, y);
				glVertex2d(x+width*3/10, y+h*1/5);
				glVertex2d(x+width*2/10, y+h*2/5);
				glVertex2d(x+width*2/10, y+h*3/5);
				glVertex2d(x+width*3/10, y+h*4/5);
				glVertex2d(x+width*4/10, y+h);

				glVertex2d(x+width*6/10, y+h*4/5);
				glVertex2d(x+width*7/10, y+h*3/5);
				glVertex2d(x+width*8/10, y+h*2/5);
				glVertex2d(x+width*8/10, y+h*1/5);
				glVertex2d(x+width*7/10, y);
				glVertex2d(x+width*6/10, y);
			glEnd();
			glBegin(GL_LINES);
				glVertex2d(x+width*8/10, y);
				glVertex2d(x+width*8/10, y+height);
			glEnd();
		break;}
		case 114:     // 'r'
		{
			glBegin(GL_LINE_STRIP);
				glVertex2d(x+width*1/5, y+height);
				glVertex2d(x+width*1/5, y+height*1/2);
				glVertex2d(x+width, y+height*1/2);
			glEnd();
		break;}
		case 115:     // 's'
		{
			y = y + height*1/2;
			int h = height/2;
			glBegin(GL_LINE_STRIP);
				glVertex2d(x+width*8/10, y);
				glVertex2d(x+width*4/10, y);
				glVertex2d(x+width*3/10, y+h*1/10);
				glVertex2d(x+width*2/10, y+h*2/10);
				glVertex2d(x+width*2/10, y+h*3/10);
				glVertex2d(x+width*3/10, y+h*4/10);
				glVertex2d(x+width*4/10, y+h*1/2);

				glVertex2d(x+width*6/10, y+h*6/10);
				glVertex2d(x+width*7/10, y+h*7/10);
				glVertex2d(x+width*8/10, y+h*8/10);
				glVertex2d(x+width*8/10, y+h*9/10);
				glVertex2d(x+width*7/10, y+h);
				glVertex2d(x+width*1/2, y+h);
				glVertex2d(x+width*2/10, y+h*9/10);
			glEnd();
		break;}
		case 116:     // 't'
		{
			glBegin(GL_LINES);
				glVertex2d(x+width*1/2, y+height);
				glVertex2d(x+width*1/2, y+height*1/4);
				glVertex2d(x, y+height*1/2);
				glVertex2d(x+width, y+height*1/2);
			glEnd();
		break;}
		case 117:     // 'u'
		{
			glBegin(GL_LINE_STRIP);
				glVertex2d(x+width*2/10, y+height*1/2);
				glVertex2d(x+width*2/10, y+height);
				glVertex2d(x+width*8/10, y+height);
				glVertex2d(x+width*8/10, y+height*1/2);
			glEnd();
		break;}
		case 118:     // 'v'
		{
			glBegin(GL_LINE_STRIP);
				glVertex2d(x, y+height*1/2);
				glVertex2d(x+width*1/2, y+height);
				glVertex2d(x+width, y+height*1/2);
			glEnd();
		break;}
		case 119:     // 'w'
		{
			y = y + height*3/2;
			int h = -height;
			glBegin(GL_LINE_STRIP);
				glVertex2d(x+width/1/10, y+h);
				glVertex2d(x+width/1/10, y+h*1/2);
				glVertex2d(x+width*1/2, y+h*3/4);
				glVertex2d(x+width, y+h*1/2);
				glVertex2d(x+width, y+h);
			glEnd();
		break;}
		case 120:     // 'x'
		{
			glBegin(GL_LINES);
				glVertex2d(x, y+height*1/2);
				glVertex2d(x+width, y+height);
				glVertex2d(x+width, y+height*1/2);
				glVertex2d(x, y+height);
			glEnd();
		break;}
		case 121:     // 'y'
		{
			y = y+height/2;
			glBegin(GL_LINES);
				glVertex2d(x+width*1/2, y+height*1/2);
				glVertex2d(x, y);
				glVertex2d(x+width, y);
				glVertex2d(x, y+height);
			glEnd();
		break;}
		case 122:     // 'z'
		{
			glBegin(GL_LINE_STRIP);
				glVertex2d(x, y+height*1/2);
				glVertex2d(x+width, y+height*1/2);
				glVertex2d(x, y+height);
				glVertex2d(x+width, y+height);
			glEnd();
		break;}



		// symbol
		case 123:     // '{'
		{

		break;}
		case 124:     // '|'
		{

		break;}
		case 125:     // '}'
		{

		break;}
		case 126:     // '~'
		{

		break;}
		case 127:     // 'DEL'
		{

		break;}
	}

	return width+2;

}
