/*
 * World.cpp
 *
 *  Created on: 9 Dec 2015
 *      Author: Mason
 */

#include "world.h"
#include "draw.h"
#include "font.h"
/*
#include "article/article.h"
#include "article/game.h"
#include "article/song.h"
#include "article/image.h"
#include "article/video.h"
#include "article/document.h"
*/

#include "button.h"
#include "agent.h"

#include "math.h"
#define FREEGLUT_STATIC
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h

#include <vector>
#include <fstream>      // std::ifstream

#include <windows.h>
#include <mmsystem.h>
#include "stdlib.h"

const std::vector<int> World::RESOLUTION = {20, 8, 20};
int World::collisionRange = World::RESOLUTION[0] / 10;
//double World::full_distance = sqrt(World::resolution[0]/100*World::resolution[0]/100 + World::resolution[1]/100*World::resolution[1]/100);

bool World::paused = false;

int World::selected = -1;
std::vector<Article*> World::articles;	// Set of all agents in the world
std::vector<image> World::images;
std::vector<Song> World::songs;
std::vector<Video> World::videos;
std::vector<Game> World::games;
std::vector<door> World::doors;
std::vector<doc> World::documents;

std::vector<UIE::Button> World::buttons;	// Set of all agents in the world

char* World::text_data;
//World::vewing_image World::current;
unsigned char* World::blob_data;
int World::blob_width;
int World::blob_height;
int World::blob_depth = 3;
int World::blob_size;

bool World::scrollable = false;
bool World::scrolling_max = false;
int World::scroll_level = 0;

unsigned char* World::buffer;
char* World::directory;
char* World::starting_directory = NULL;
char* World::dd = "\\debug\\data\\";
std::string World::bmp_path = "";

void World::initWorld(char * d) {		//init world, including getting all the portfolio pieces
	articles.clear();
	images.clear();
	games.clear();
	videos.clear();
	songs.clear();
	doors.clear();
	documents.clear();

	buttons.clear();

	Agent::setStand(0, 1, 5);
	Agent::setLook(0, 0, -1);

	// for now
	selected = -1;
	paused = false;

	char* data_dir;
	if (d == NULL) {
		//int buffer_size = GetCurrentDirectory(0, NULL);
	    char current_file[MAX_PATH];
	    GetModuleFileName( NULL, current_file, MAX_PATH );
	    int pos = std::string( current_file ).find_last_of( "\\/" );
	    //current_file.substr( 0, pos);

		directory = (char*) malloc (pos+1);
		strncpy(directory, current_file, pos);
		directory[pos] = '\0';
		//DWORD dwr = GetCurrentDirectory(buffer_size, directory);
		dd = "\\data\\";
		// \\debug\\data\\	for non eclipse runs
	} else {
		directory = (char*) malloc (strlen(d)+1);
		strcpy(directory, d);
		dd = "";
	}
	data_dir = (char*) malloc (strlen(directory)+strlen(dd)+1);

	strcpy(data_dir, directory);
	strcat(data_dir, dd);

	if (starting_directory == NULL) {
		starting_directory = (char*) malloc (strlen(data_dir)+1);
		strcpy(starting_directory, data_dir);
	}



	char* data_search;
	data_search = (char*) malloc (strlen(data_dir)+2);
	strcpy(data_search, data_dir);
	strcat(data_search, "*");


	WIN32_FIND_DATA folder_data;
	WIN32_FIND_DATA data;
	HANDLE handle;
	HANDLE folder_handle = FindFirstFile(data_search, &folder_data);
	free(data_search);

	float image_space = 0;
	std::vector< int > open_position(World::RESOLUTION[0] / 2 * World::RESOLUTION[2] / 2, 1);	// the list of positions still open
											// hundred ints with the value 1

	int r = 1;
	if (GetLastError() ==  ERROR_FILE_NOT_FOUND) {
		r = 0;
	}
	while (r != 0) {
		bool cont = false;
		// do something with data
		std::string c = folder_data.cFileName;
		while (folder_data.cFileName[0] == '.') {
			// ||
			FindNextFile(folder_handle, &folder_data);
			c = folder_data.cFileName;

			if (GetLastError() ==  ERROR_FILE_NOT_FOUND || r == 0) {
				cont = true;
				break;
			}
		}
		
		if (cont) {
			continue;
		}
		
		char file_search[MAX_PATH];
		strcpy(file_search, data_dir);
		strcat(file_search, folder_data.cFileName);
		strcat(file_search, "//*");

		int article_type = 0;
		handle = FindFirstFile(file_search, &data);
		int h = 1;

		if (c.rfind('.') != -1) {
			char* file_type = strrchr(c.c_str(), '.');

			if (strcmp(file_type, "txt") == 0) {		// text file
				article_type = 0;
			} else if (strcmp(file_type, "exe") == 0 || strcmp(file_type, "jar") == 0) {		// program
				article_type = 4;
			} else if (strcmp(file_type, "bmp") == 0 || strcmp(file_type, "jpg") == 0 || strcmp(file_type, "png") == 0) {		// image
				article_type = 1;
			} else if (strcmp(file_type, "gif") == 0 || strcmp(file_type, "mkv") == 0 || strcmp(file_type, "mp4") == 0) {		// moving image
				article_type = 3;
			} else if (strcmp(file_type, "wav") == 0 || strcmp(file_type, "ogg") == 0 || strcmp(file_type, "mp3") == 0 || strcmp(file_type, "flac") == 0) {		// audio	--	fla == flac
				article_type = 2;
			} else {		// anything else eg. .cpp, .js
				article_type = 0;

			}
			h = 0;
		}
		
		if (GetLastError() ==  ERROR_FILE_NOT_FOUND) {
			h = 0;
		}
		while (h != 0) {
			cont = false;
			while (data.cFileName[0] == '.') {
				h = FindNextFile(handle, &data);

				if (GetLastError() ==  ERROR_FILE_NOT_FOUND || h == 0) {
					cont = true;
					break;
				}
			}
			if (cont) {
				article_type = -1;
				break;
			}

			char* file_name = data.cFileName;

			char* file_type = strrchr(file_name, '.');

			if (file_type == NULL) {		// a folder
				if (strcmp(file_name, "source") != -1) {		// the folder is a source folder

				} else {
					article_type = 5;
				}

			} else {
				file_type++;

				int prelim = 0;

				if (strcmp(file_type, "txt") == 0) {		// text file
					prelim = 0;
				} else if (strcmp(file_type, "exe") == 0 || strcmp(file_type, "jar") == 0) {		// program
					prelim = 4;
				} else if (strcmp(file_type, "bmp") == 0 || strcmp(file_type, "jpg") == 0 || strcmp(file_type, "png") == 0) {		// image
					prelim = 1;
				} else if (strcmp(file_type, "gif") == 0 || strcmp(file_type, "mkv") == 0 || strcmp(file_type, "mp4") == 0) {		// moving image
					prelim = 3;
				} else if (strcmp(file_type, "wav") == 0 || strcmp(file_type, "ogg") == 0 || strcmp(file_type, "mp3") == 0 || strcmp(file_type, "flac") == 0) {		// audio	--	fla == flac
					prelim = 2;
				} else if (file_type == "") {
					
				}

				if (prelim > article_type) {
					article_type = prelim;
				}
			}
/*
			std::ifstream ifs (file_name, std::ifstream::in);
			char c;
			std::string str;
			while (ifs.get(c)) {
				str+=c;
			}
			ifs.close();
*/
			h = FindNextFile(handle, &data);
		}
		FindClose(handle);
		int current = articles.size();

		std::vector<int> xyz;
		int sx;
		int sy;
		int sz;

		do {
			current++;
			xyz = generatePosition(current);
			sx = xyz[0];
			sy = xyz[1];
			sz = xyz[2];

		} while (open_position[current] == 0);

		open_position[current] = 0;



		char* name = folder_data.cFileName;
		switch (article_type) {
			case 5:
			{
				doors.push_back(*new door(sx, sy, sz, name));
				addArticle(&doors[doors.size()-1]);
				break;
			}
			case 0:
			{
				documents.push_back(*new doc(sx, sy, sz, name));
				addArticle(&documents[documents.size()-1]);
				break;
			}
			case 1:
			{
				images.push_back(*new image(sx, sy, sz, name));
				int current_image_space = images[images.size()-1].getHitbox()[2];

				if (current%10 + current_image_space >= 10) {		// if the image doesn't fit on the row, move it to the next
					open_position[current] = 1;
					do {
						if (current%10 + current_image_space >= 10) {
							current = current - current%10 + 10;

						} else {
							current++;
						}

						xyz = generatePosition(current);
						sx = xyz[0];
						sy = xyz[1];
						sz = xyz[2];

					} while (open_position[current] == 0);

					images[images.size()-1].shiftPosition(sx, sy, sz);

				}
				for (int i = 0; i < current_image_space; i++) {
					open_position[current+i] = 0;
				}

				addArticle(&images[images.size()-1]);
				break;
			}
			case 2:
			{
				songs.push_back(*new Song(sx, sy, sz, name));
				addArticle(&songs[songs.size()-1]);
				break;
			}
			case 3:
			{
				videos.push_back(*new Video(sx, sy, sz, name));
				addArticle(&videos[videos.size()-1]);
				break;
			}
			case 4:
			{
				games.push_back(*new Game(sx, sy, sz, name));
				addArticle(&games[games.size()-1]);
				break;
			}
		}

		r = FindNextFile(folder_handle, &folder_data);
	}
	FindClose(folder_handle);
	free(data_dir);

	paused = true;
	selectArticle(-2);
}

std::vector<int> World::generatePosition(int current) {	// generates an x, y, z position based on the number given and map size, 		it fills out the gallery without putting stuff on top of each otheer
	int space = 4;

	int fac = current / (World::RESOLUTION[0]*2-space*2);
	int sx = (current % 2*space/2-1) * (space/2+fac*space);
	int sy = 0;
	int sz = (current) / 2 * space - (current -space);

	sx = (current / (20/2) + 1) * space;
	if (current % 2) {
		sx = -sx;
	}
	sz = current % (20/2) * 2;

	return {sx, sy, sz};

}

void World::worldTick() { // Go through and do everything in the world
	if (selected == -1) {
		if (blob_data) {
			free(blob_data);
		}
	}


}

void World::addArticle(Article* a) {			// I think with the hash thing I could just collect the agent I need with the hash thing
	articles.push_back(a);
}

bool World::getPaused() {
	if (selected != -1) {
		return true;
	}
	return paused;
}

void World::selectArticle(int i) {		// based on the index (i) find the article and setup the screen to interact with it, this will consider the type of article it is
	buttons.clear();
	if (i == -1) {
		paused = false;
		selected = i;
		return;
	}

	World::bmp_path = "";
	if (World::text_data != NULL) {
		free(World::text_data);
		World::text_data = NULL;
	}

	paused = true;
	selected = i;
	char* dir;

	if (i == -2) {
		dir = (char*) malloc (strlen(directory)+strlen(dd)+2);
		strcpy(dir, directory);
		strcat(dir, dd);
//		strcat(dir, "\\");

	} else {

		// more part of the articles work around		-- when being made all the articles were ordered in a specific way, so they can be pulled out in that same way
		std::string c;
		if (i >= games.size()) {
			i = i - games.size();

			if (i >= doors.size()) {
				i = i - doors.size();

				if (i >= documents.size()) {
					i = i - documents.size();

					if (i >= songs.size()) {
						i = i - songs.size();

						if (i >= images.size()) {
							i = i - images.size();

							if (i >= videos.size()) {
								i = i - videos.size();

							} else {
								c = videos[i].getDirectory();
							}

						} else {
							c = images[i].getDirectory();
						}

					} else {
						c = songs[i].getDirectory();
					}

				} else {
					c = documents[i].getDirectory();
				}

			} else {
				c = doors[i].getDirectory();
			}

		} else {
			c = games[i].getDirectory();
		}




		//std::string c = articles[i]->getDirectory();
		
		const char* str_c = c.c_str();


		int a = strlen(str_c);

		dir = (char*) malloc (strlen(str_c)+strlen(directory)+strlen(dd)+2);

		strcpy(dir, directory);


		strcat(dir, dd);
		strcat(dir, str_c);

		if (c.rfind('.') != -1) {
			createButton(dir, " ", "Open in Default Program");
			free(dir);
			return;
		}

		strcat(dir, "\\");

	}

	WIN32_FIND_DATA data;

	char* dir_search;
	dir_search = (char*) malloc (strlen(dir)+2);
	strcpy(dir_search, dir);
	strcat(dir_search, "*");
	HANDLE handle = FindFirstFile(dir_search, &data);
	createButton(dir, "", "View Source");

	int h = 1;
	bool folder = false;
	while (h != 0) {

		while (data.cFileName[0] == '.') {
			h = FindNextFile(handle, &data);
		}

		char* file_name = data.cFileName;
		char* full_name;
		full_name = (char*) malloc (strlen(dir)+strlen(file_name)+1);
		strcpy(full_name, dir);
		strcat(full_name, file_name);

		char* file_type = strrchr(file_name, '.');

		int text_file_number = 0;
		int image_file_number = 0;
		int song_file_number = 0;
		int video_file_number = 0;
		int game_file_number = 0;


		if (file_type == NULL) {		// a folder
			if (strcmp(file_name, "source") != -1) {		// the folder is a source folder

			} else {
				folder = true;
			}

		} else {
			file_type++;

			if (strcmp(file_type, "txt") == 0) {		// text file
				text_file_number++;
				if (text_file_number == 2) {
//					createArchive();
				}
				long r = readFile(full_name, true);
				text_data = (char*) malloc (r+1);
				memcpy(text_data, buffer, r);
				text_data[r] = '\0';
				buffer = (unsigned char*) calloc (r, sizeof(char));
				free(buffer);

			} else if (strcmp(file_type, "exe") == 0) {		// program
				game_file_number++;
				createButton(dir, file_name, "Play Game");

			//} else if (strcmp(file_type, "jpg") == 0 || strcmp(file_type, "png") == 0) {		// image
			} else if (strcmp(file_type, "bmp") == 0) {		// image	-	bmp is uncompressed


				image_file_number++;
				if (image_file_number + video_file_number == 2) {
//					createVisualSlideshow();
				}
				bmp_path = full_name;
				long r = readFile(full_name, false);
				World::blob_data = (unsigned char*) malloc (r+1);
				memcpy(blob_data, buffer, r);
				buffer = (unsigned char*) calloc (r, sizeof(char));
				free(buffer);


			} else if (strcmp(file_type, "gif") == 0 || strcmp(file_type, "mkv") == 0 || strcmp(file_type, "mp4") == 0) {		// moving image
				video_file_number++;
				if (video_file_number + image_file_number == 2) {
//					createVisualSlideshow();
				}
			//} else if (strcmp(file_type, "ogg") == 0 || strcmp(file_type, "mp3") == 0 || strcmp(file_type, "flac") == 0) {		// audio	--	fla == flac
			} else if (strcmp(file_type, "wav") == 0) {	
			// openAL or Directsound
				song_file_number++;
				if (song_file_number == 2) {
//					createPlaylist();
				}
				PlaySound(full_name, NULL, SND_ASYNC);				// TODO		instead of playing it straight off, give them a button to play it from

			} else {
				
			}

		}

		free(full_name);
		h = FindNextFile(handle, &data);
	}
	if (i == -2) {
		if (strcmp(starting_directory, dir) != 0) {
			createButton(dir, "", "Return");
			createButton(dir, "", "Exit");
		} else {
			createButton(dir, "", "Exit");
		}
		createButton(dir, "", "Continue");
	} else if (folder) {
		createButton(dir, "", "Enter");
	}

	FindClose(handle);
	free (dir);
	free (dir_search);

}

long World::readFile(char* file_name, bool text) {		// read a file from the file system into a global buffer and return the length of the file, 'text' is true if the file is a text file and false if the file is binary
	// read and store the image

	FILE * pFile;
	if (text == true ) {
		pFile = fopen ( file_name , "r" );

		fseek(pFile, 0, SEEK_END);
		long lSize = ftell(pFile);
		buffer = (unsigned char*) malloc (lSize+1);	//sizeof(char)*
		if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

		rewind (pFile);
		long result;

		// copy the file into the buffer:
		result = fread (buffer, sizeof(unsigned char), lSize, pFile);
	//	if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

		buffer[result] = '\0';
		return result;

	}
	pFile = fopen ( file_name , "rb" );
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, pFile); // read the 54-byte header

    // extract image height and width from header
    blob_width = *(int*)&info[18];
    blob_height = *(int*)&info[22];

	long lSize = blob_width * blob_height * 3;
	buffer = (unsigned char*) malloc (lSize+1);	//sizeof(char)*
	if (buffer == NULL) {
		fputs ("Memory error",stderr); exit (2);
	}

	long result;
	int posiio = ftell(pFile);
	// copy the file into the buffer:
	result = fread (buffer, sizeof(unsigned char), lSize, pFile);
	if (result != lSize) {
		fputs ("Reading error",stderr); exit (3);
	}

	buffer[result] = '\0';
	return result;

}

//std::vector< std::vector <std::vector <int> > >
unsigned char* World::getBitmap(char* file_name) {			// read a bitmap from a file, returning the bitmap as an unsigned char*,   if the file_name given is null then use the global bmp_path as the file name
	long r;
	if (file_name == NULL) {
		// it wants the blob as is, I guess
		if (selected == -1) {

			return NULL;
		}
		return blob_data;

		char* f;
		f = (char*) malloc (bmp_path.size()+1);
		strcpy(f, bmp_path.c_str());
		r = readFile(f, false);
		free(f);

	} else {
		r = readFile(file_name, false);
		
	}
	
	World::blob_data = (unsigned char*) malloc (r+1);
	memcpy(World::blob_data, buffer, r);
	buffer = (unsigned char*) calloc (r, sizeof(char));
	free(buffer);

//	return blob_data;


	int depth = 3;

	int f = blob_width*depth;

	if (f % 4 != 0) {
		f = f/4 *4 +4;

	}

	std::vector<int> i;
	for (int l = 0; l < blob_height*blob_width*depth; l++) {
		i.push_back(blob_data[l]);
	}

	
	return blob_data;

	
	
}

int World::findArticle(int x, int y) {			// based upon where the camera is facing find the article being pointed and clicked at
	std::vector<float> look = Agent::getLook();
	std::vector<float> stand = Agent::getStand();
	
	std::vector<float> check = stand;
	int min_hit = 1;
	// maybe -res instead of 0
	int t = 0;
	while (t < 3) {
	//while (check[0] > -RESOLUTION[0] && check[0] < RESOLUTION[0] ||
	//		check[1] > -RESOLUTION[1] && check[1] < RESOLUTION[1] ||
	//		check[2] > -RESOLUTION[2] && check[2] < RESOLUTION[2]) {
		
		// take a step forward for the position to check if it coincides with an article, the amount stepped forwards considers the smallest possible size of an article
		check[0] += look[0] * min_hit/2.0f;
		check[1] += look[1] * min_hit/2.0f;
		check[2] += look[2] * min_hit/2.0f;
		t++;

		//std::vector<Article> articles =
			//	vector1.insert( vector1.end(), vector2.begin(), vector2.end() );
/*
		articles = doors.insert(
				doors.end(), documents.insert(
						documents.end(), games.insert(
								games.end(), songs.insert(
										songs.end(), images.insert(
												images.end(), videos.begin(), videos.end()
												), images.end()
										), songs.end()
								), games.end()
				), documents.end()
		);
*/

		// work around for articles messing up with bad allocs and the objects being pointed to dissappearing
		int i = 0;
		int pi = 0; // previous i
		for (i; i < games.size(); i++) {
			std::vector<int> loc = games[i].getPosition();
			std::vector<float> h = games[i].getHitbox();
			float x = check[0] - loc[0]-h[0]/2;
			float y = check[1] - loc[1]-h[1]/2;
			float z = check[2] - loc[2]-h[2]/2;

			if (abs(x) <= h[0] && abs(y) <= h[1] && abs(z) <= h[2]) {
				return i;
			}
		}
		pi = i;
		for (i; i < doors.size()+pi; i++) {
			std::vector<int> loc = doors[i-pi].getPosition();
			std::vector<float> h = doors[i-pi].getHitbox();
			float x = check[0] - loc[0]-h[0]/2;
			float y = check[1] - loc[1]-h[1]/2;
			float z = check[2] - loc[2]-h[2]/2;

			if (abs(x) <= h[0] && abs(y) <= h[1] && abs(z) <= h[2]) {
				return i;
			}
		}
		pi = i;
		for (i; i < documents.size()+pi; i++) {
			std::vector<int> loc = documents[i-pi].getPosition();
			std::vector<float> h = documents[i-pi].getHitbox();
			float x = check[0] - loc[0]-h[0]/2;
			float y = check[1] - loc[1]-h[1]/2;
			float z = check[2] - loc[2]-h[2]/2;

			if (abs(x) <= h[0] && abs(y) <= h[1] && abs(z) <= h[2]) {
				return i;
			}
		}
		pi = i;
		for (i; i < songs.size()+pi; i++) {
			std::vector<int> loc = songs[i-pi].getPosition();
			std::vector<float> h = songs[i-pi].getHitbox();
			float x = check[0] - loc[0]-h[0]/2;
			float y = check[1] - loc[1]-h[1]/2;
			float z = check[2] - loc[2]-h[2]/2;

			if (abs(x) <= h[0] && abs(y) <= h[1] && abs(z) <= h[2]) {
				return i;
			}
		}
		pi = i;
		for (i; i < images.size()+pi; i++) {
			std::vector<int> loc = images[i-pi].getPosition();
			std::vector<float> h = images[i-pi].getHitbox();
			float x = check[0] - loc[0]-h[0]/2;
			float y = check[1] - loc[1]-h[1]/2;
			float z = check[2] - loc[2]-h[2]/2;

			if (abs(x) <= h[0] && abs(y) <= h[1] && abs(z) <= h[2]) {
				return i;
			}
		}
		pi = i;
		for (i; i < videos.size()+pi; i++) {
			std::vector<int> loc = videos[i-pi].getPosition();
			std::vector<float> h = videos[i-pi].getHitbox();
			float x = check[0] - loc[0]-h[0]/2;
			float y = check[1] - loc[1]-h[1]/2;
			float z = check[2] - loc[2]-h[2]/2;

			if (abs(x) <= h[0] && abs(y) <= h[1] && abs(z) <= h[2]) {
				return i;
			}
		}
	}
	
	// probs not necc
	return -1;
	
	
}

void World::selectButton(int i) {
	buttons[i].run();
	
}

int World::findButton(int x, int y) {			// based upon where the mouse is positioned find the button being clicked on
	for (int i = 0; i < buttons.size(); i++) {
		std::vector<int> loc = buttons[i].getPosition();
		int b = Draw::BORDER;
		if (x >= loc[0]-b && x <= loc[2]+b &&
			y >= loc[1]-b && y <= loc[3]+b) {
		
			return i;
		}
	}
	return -1;
	
}



void World::createButton(char* dir, char* fileName, char* prefixText) {		// create a button, dir and fileName combined are the file related to the button,
	//	and the prefixText determines is used to determine where it should be positioned and what function the button should perform
	// prefix_text is like 	"Play " in "Play fileName"


	char* d;
	char* t;
	d = (char*) malloc (strlen(dir)+strlen(fileName)+1);
	t = (char*) malloc (strlen(prefixText)+strlen(fileName)+1);

	strcpy(d, dir);


	strcpy(t, prefixText);
	strcat(t, fileName);
	strchr(t, '.');

	void (*func)(char*);
	int x;
	int y;
	if (strcmp(prefixText, "Play Game") == 0 ) {			// run the application
		func = World::runGame;
		x = 850;
		y = 30;
		strcat(d, fileName);
	} else if (strcmp(prefixText, "View Source") == 0 ) {	// open the folder in windows explorer
		func = World::openFolder;
		x = 650;
		y = 30;
	} else if (strcmp(prefixText, "Enter") == 0 ) {			// enter into a new directory
		func = World::initWorld;
		x = 350;
		y = 30;
	} else if (strcmp(prefixText, "Return") == 0 ) {		// return to the parent directory
		return;				// TODO
		if (dd != "") {
			return;
		}
		func = World::initWorld;
		x = 250;
		y = 30;
		char * tmp_d;
		tmp_d = (char*) malloc (strlen(dir)+1);
		strncpy(tmp_d, dir, strlen(dir)-1);
		const char* di = tmp_d;

		free(d);
		d = (char*) malloc (strlen(di)+1);


		strncpy(d, di, strrchr(di, '\\')-di);
		d[strrchr(di, '\\')-di] = '\\';
		d[strrchr(di, '\\')-di+1] = '\0';

		free(tmp_d);
		free(dir);

	}  else if (strcmp(prefixText, "Exit") == 0 ) {			// close the program
		func = World::exitWorld;
		x = 250;
		y = 30;
	} else  if (strcmp(prefixText, "Continue") == 0 ) {		// close the menu that the button it being shown on
		func = World::continueWorld;
		x = 400;
		y = 30;
	} else if (strcmp(prefixText, "Open in Default Program") == 0 ) {			// open the file in whatever the default program is
		func = World::openFile;
		x = Draw::getWidth()/2 - (Draw::getTextSize(prefixText, Draw::getWidth())[0]/2);
		y = Draw::getHeight()/2 - font::height/2 + 50;
	} else {
		func = World::runGame;
		x = 350;
		y = 30;
		strcat(d, fileName);
	}



	UIE::Button* b = new UIE::Button (x, y, prefixText, func, d);
	buttons.push_back(*b);

	free(t);
	free(d);
	int a = 0;
}

void World::runGame(char* file) {		 // run the executable
	int result = system(file);
//	CreateProcess(file, FALSE, NORMAL_PRIORITY_CLASS, );
	// https://msdn.microsoft.com/en-us/library/windows/desktop/ms682425%28v=vs.85%29.aspx
	/*

BOOL WINAPI CreateProcess(
  _In_opt_    LPCTSTR               lpApplicationName,
  _Inout_opt_ LPTSTR                lpCommandLine,
  _In_opt_    LPSECURITY_ATTRIBUTES lpProcessAttributes,
  _In_opt_    LPSECURITY_ATTRIBUTES lpThreadAttributes,
  _In_        BOOL                  bInheritHandles,
  _In_        DWORD                 dwCreationFlags,
  _In_opt_    LPVOID                lpEnvironment,
  _In_opt_    LPCTSTR               lpCurrentDirectory,
  _In_        LPSTARTUPINFO         lpStartupInfo,
  _Out_       LPPROCESS_INFORMATION lpProcessInformation
);

	 */
}

void World::openFolder(char* file) {				// open the folder in windows explorer		--	currently ONLY windows explorer
	// stackoverflow.com/questions/34065/how-to-read-a-value-from-the-windows-registry
	
	char* exp = "\%windir\%\\explorer.exe";	// find default file viewer
	char* f;
	f =  (char*) malloc (strlen(exp)+strlen(file)+2);
	strcpy(f, exp);
	strcat(f, " ");
	strcat(f, file);
	
	int result = system(f);
}

void World::openFile(char* file) {		// open the file in the default program
	char* f;
	f =  (char*) malloc (strlen(file)+3);
	strcpy(f, "L ");
	strcat(f, file);
	
	//ShellExecute(0, 0, f, 0, 0 , SW_SHOW );
	int result = system(file);

}


void World::exitWorld(char* file) {		// close this program
	exit(0);
//	glutLeaveMainLoop(void);
	//throw 0;

}

void World::continueWorld(char* file) {		// close the menu
	selected = -1;
	paused = false;
	glutPostRedisplay();
}








// Event handling


void World::mouse(int button, int state, int x, int y) {
	int l = 0;
	y = Draw::getHeight() - y;
	if (paused) {					// if paused then the menu is up, so search for button presses
		l = findButton(x, y);
		if (l == -1) {
			return;
		}
		if (state == GLUT_DOWN) {
			buttons[l].press();;
		} else {
			if (buttons[l].getPressed()){
				selectButton(l);
			}
		}
	} else {						// if not paused then search for articles
		l = findArticle(x, y);
		selectArticle(l);
	}

	if (l != -1) {
		glutPostRedisplay();
	}

}


void World::key(unsigned char k, int x, int y){
	if (k == 27) {			// escape key (or maybe space, I can't remember),   close menu, pause sound, unselect whatever is selected
		World::buttons.clear();

		World::text_data = NULL;
		if (selected == -1) {
			paused = !paused;

			if (paused == true) {
				selectArticle(-2);
				glutPostRedisplay();
			}

		} else {
			selected = -1;
			paused = false;

			glutPostRedisplay();

		}
		PlaySound(NULL, NULL, NULL);
		scrollable = false;
		scroll_level = 0;
		return;
	}

	if (paused) {		// if paused you can't move
		return;
	}

					// movement
	float f = 0.2f;
	if (k == 'a') {
		f = -f;
		Agent::locationMove(false, f);
	}
	if (k == 'd') {
		Agent::locationMove(false, f);
	}
	if (k == 'w') {
		Agent::locationMove(true, f);
	}
	if (k == 's') {
		f = -f;
		Agent::locationMove(true, f);
	}

	glutPostRedisplay();

}
void World::passiveMouse(int x, int y) {
	if (paused) {		// if paused you can't look around
		return;
	}
	
	Agent::lookMove(x, y);
	glutPostRedisplay();

}

void World::specialKey(int key, int x, int y) {

	// movement or scrolling
	float f = 0.1f;
	switch (key) {
		case GLUT_KEY_LEFT :
			if (paused) {

			} else {
				f = -f;
				Agent::locationMove(false, f);
			}

		break;
		case GLUT_KEY_RIGHT :
			if (paused) {

			} else {
				Agent::locationMove(false, f);
			}
		break;
		case GLUT_KEY_UP :
			if (paused) {				// if paused menu is up, so scroll if possible
				if (scrollable) {
					scroll_level -= 1;
					if (scroll_level <= 0) {
						scroll_level = 0;
					}

				}
			} else {
				Agent::locationMove(true, f);
			}

		break;
		case GLUT_KEY_DOWN :
			if (paused) {				// if paused menu is up, so scroll if possible
				if (scrollable) {
					scroll_level += 1;

					if (scrolling_max) {
						scroll_level--;
					}
				}

			} else {
				f = -f;
				Agent::locationMove(true, f);
			}
		break;
	}
	glutPostRedisplay();

}


