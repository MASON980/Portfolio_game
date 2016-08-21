/*
 * world.h
 *
 *  Created on: 9 Dec 2015
 *      Author: Mason
 */

#ifndef WORLD_H_
#define WORLD_H_

#include "article/article.h"
#include "article/game.h"
#include "article/doc.h"
#include "article/song.h"
#include "article/image.h"
#include "article/video.h"
#include "article/door.h"

#include "button.h"


#include <array>
#include <vector>

class World {
private:

	static int collisionRange;
	static double full_distance;
	static bool paused;
	static int selected;

	static char* text_data;
	static unsigned char* blob_data;
	static int blob_width;
	static int blob_height;
	static int blob_depth;
	static int blob_size;

	static unsigned char* buffer;


public:
	struct vewing_image {
		char* blob;
		int width;
		int height;
	};

	static int scroll_level;
	static bool scrollable;
	static bool scrolling_max;

	static char* directory;
	static char* starting_directory;
	static char* dd;
	static std::string bmp_path;

	static std::vector<Article*> articles;	// Set of all agents in the world

	static std::vector<Game> games;	// Set of all agents in the world
	static std::vector<Video> videos;	// Set of all agents in the world
	static std::vector<Song> songs;	// Set of all agents in the world
	static std::vector<image> images;	// Set of all agents in the world
	static std::vector<door> doors;
	static std::vector<doc> documents;

	static std::vector<UIE::Button> buttons;	// Set of all agents in the world
	static const std::vector<int> RESOLUTION;

	static void initWorld(char*);
	static void worldTick(); // Go through and do everything in the world, agent logic then draw

	static std::vector<Article*> getArticles() { return articles;}
	static void addArticle(Article*);

	static bool getPaused();
	static int getSelected() {return selected;};
	
	static std::vector<int> getResolution() { return RESOLUTION;}
	static int getCollisionRange() { return collisionRange;}
	static double getFullDistance() {return full_distance;};

	static char* getText() {return text_data;};
	static unsigned char* getBitmap(char*);
	static std::vector <int> getBitmapSize() {return {blob_height, blob_width, blob_depth};};

	static long readFile(char*, bool);
	static void runGame(char*);
	static void openFolder(char*);
	static void openFile(char*);
	static void exitWorld(char*);
	static void continueWorld(char*);

	static int findArticle(int, int);
	static int findButton(int, int);
	static void beginArticle();
	static void selectArticle(int);
	static void selectButton(int);
	static void createButton(char*, char*, char*);


	static std::vector<int> twoForces(int, int, int, double);
	static std::vector<int> generatePosition(int);	// generates an x, y, z position based on the number given and map size


	// Event handling
	static void mouse(int, int, int , int);
	static void key(unsigned char, int , int);
	static void passiveMouse(int, int);
	static void specialKey(int, int, int);
};


#endif /* WORLD_H_ */
