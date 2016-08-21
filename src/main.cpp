/*
 * main.cpp
 *
 *  Created on: 8 Dec 2015
 *      Author: Mason
 */

#include "draw.h"
#include "main.h"
#include "world.h"

#include <ctime>
#include <stdlib.h>

#include <math.h>
#define FREEGLUT_STATIC
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h


int main(int argc, char* argv[])
{
	srand(time(0));

	if (argc >= 2) {
		World::directory = (char*) malloc (strlen(argv[1])+1);
		strcpy(World::directory, argv[1]);
	}

	try
	{
		Draw::initialiseDraw();
	}
	catch(int e)  // Consider using a custom exception type for intentional
	{                             // throws. A good idea might be a `return_exception`.
		int a = 0;
	}
	free(World::directory);
    return 0;
}
/*
 *		various blocks of code are commented out they need to be either removed or reimplemented
 *		some commenting is done in .cpp and some in .h, needs to be consistent
 *		there are many work arounds in this that need to be tidied up
 *		many functions use global variables when they aren't necessary, this should be fixed
 *		want to make everything look nicer
 *			some of the UI in particular
 *		more efficient / faster loading etc.
 *
 *		video functionality needs to be implemented
 *
 *		better font rendering
 *
 *		better  resizing		--	buttons don't reposition and 2d images don't resize
 *
 */



/*
#include <stdlib.h>

#include <math.h>
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h


// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f,z=5.0f;

// all variables initialized to 1.0, meaning
// the triangle will initially be white
float red=1.0f, blue=1.0f, green=1.0f;

// angle for rotating triangle
float angle = 0.0f;

//int dummy = 5;

void drawSnowMan()
{

	glColor3f(1.0f, 1.0f, 1.0f);

	// Draw Body
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f,20,20);

	// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f,20,20);

	// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f,10,10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f,10,10);
	glPopMatrix();

	// Draw Nose
	glColor3f(1.0f, 0.5f , 0.5f);
	glRotatef(0.0f,1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f,0.5f,10,2);
}



void renderScene(void)
{

	// Clear Color and Depth Buffers

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt( x, 1.0f, z,
				x+lx, 1.0f, z+lz,
				0.0f, 1.0f, 0.0f);

	// Draw ground
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f, 100.0f);
		glVertex3f( 100.0f, 0.0f, 100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();

	// Draw 36 SnowMen
	for(int i = -3; i < 3; i++) {
		for(int j=-3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i*10.0,0,j * 10.0);
			drawSnowMan();
			glPopMatrix();
		}
	}

	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y)
{

	if (key == 27)
	exit(0);
}

void processSpecialKeys(int key, int xx, int yy)
{

	float fraction = 0.1f;

	switch (key) {
		case GLUT_KEY_LEFT :
			angle -= 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
		break;
		case GLUT_KEY_RIGHT :
			angle += 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
		break;
		case GLUT_KEY_UP :
			x += lx * fraction;
			z += lz * fraction;
		break;
		case GLUT_KEY_DOWN :
			x -= lx * fraction;
			z -= lz * fraction;
		break;
	}
}

int main(int argc, char **argv)
{



	return 1;
}
*/
