/*
 * World.cpp
 *
 *  Created on: 9 Dec 2015
 *      Author: Mason
 */

#include "world.h"
#include "draw.h"

#include <array>
#include <map>
#include <vector>
#include <iterator>
#include <utility>
#include <ctime>

#define FREEGLUT_STATIC
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h

std::vector <std::vector <int> > World::mines;

int const World::COLUMNS = 12;
int const World::ROWS = 12;
int const World::MINE_NUMBER = 74;

bool World::won = false;
std::vector < std::vector < int > > World::map;


void World::initMap() {		// fill up the empty map
	std::vector < std::vector <int> > m;

	for (int i = 0; i < World::COLUMNS*2; i++) {
		std::vector<int> row;
		for (int j = 0; j < World::ROWS*2; j++) {
			row.push_back(-1);
		}
		m.push_back(row);
	}
	World::map = m;

	std::vector < std::vector <int> > n;
	int x = 0;
	int y = 0;

	for (int i = 0; i < MINE_NUMBER; i++) {
		bool done = false;
		do {
			done = false;
			x = rand() % (COLUMNS*2);
			y = rand() % (ROWS*2);

			for (int j = 0; j < n.size(); j++) {
				if (n[j][0] == x && n[j][1] == y) {
					done = true;
				}
			}
		} while (done);
		n.push_back({x, y});
	}
	World::mines = n;
}

bool World::winCheck() {	// check to see if all the mines have been found
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j] < 0) {
				bool flagged = false;
				for (int m = 0; m < mines.size(); m++) {
					if (i == mines[m][0] && j == mines[m][1]) {
						flagged = true;
					}
				}
				if (!flagged) {
					return false;
				}
			}
		}
	}
	return true;
}

void World::check(int x, int y) {				// colours the square based upon the amount of neighbouring mines, if there are no neighbouring mines check() all adjacent squares	-- recursive
	int close = 0;
	for (int i = 0; i < mines.size(); i++) {
		if (x == mines[i][0] && y == mines[i][1]) {		// if there is a mine here
			gameOver();
			return;
		}
		if (x-1 <= mines[i][0] && x+1 >= mines[i][0] && y-1 <= mines[i][1] && y+1 >= mines[i][1]) {			// if there is a mine next to here
			close++;
		}
	}

	map[x][y] = close;			// colour the square based upon how many mines are next to it

	std::vector <int> pos;
	if (close == 0) {				// no mines, so find all the neighbouring squares
		for (int i = 1; i < 9; i++) {
			switch (i) {
				case 1: pos = {x-1,		y+1};
				break;
				case 2: pos = {x,		y+1};
				break;
				case 3: pos = {x+1,		y+1};
				break;
				case 4: pos = {x+1,		y};
				break;
				case 5: pos = {x+1,		y-1};
				break;
				case 6: pos = {x,		y-1};
				break;
				case 7: pos = {x-1,		y-1};
				break;
				case 8: pos = {x-1, 	y};
				break;
			}

			if (pos[0] < 0) {

			} else if (pos[0] >= COLUMNS*2) {

			} else if (pos[1] < 0) {

			} else if (pos[1] >= ROWS*2+4) {

			} else {
				if (map[pos[0]][pos[1]] == -1) {
					check(pos[0], pos[1]);				// go through every adjacent place and do this again
				}
			}
		}
	}


}

void World::gameOver() {

	World::initMap();
}


void World::mouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		return;
	}

	if (won) {
		gameOver();
		won = false;
	} else {

		std::vector <int> pos = Draw::pixelToGlut(x, y);		// find what square has been clicked

		if (button == GLUT_RIGHT_BUTTON) {
			if (map[pos[0]][pos[1]] == -1) {
				map[pos[0]][pos[1]] = -2;
			} else if (map[pos[0]][pos[1]] == -2) {
				map[pos[0]][pos[1]] = -1;
			}
		} else {
			if (map[pos[0]][pos[1]] == -1) {
				check(pos[0], pos[1]);
			}
		}

		won = winCheck();
	}


	glutPostRedisplay();

}
void World::key(unsigned char k, int x, int y){
	if (k == ' ') {
	}
	if (k == 'z') {
	}

}

void World::passiveMouse(int x, int y) {

}


void World::specialKey(int key, int x, int y) {

	if (key == GLUT_KEY_UP) {
	}
	if (key == GLUT_KEY_DOWN) {
	}

	if (key == GLUT_KEY_LEFT) {
	}
	if (key == GLUT_KEY_RIGHT) {
	}

	glutPostRedisplay();
}





