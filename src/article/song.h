/*
 * song.h
 *
 *  Created on: 1 Mar 2016
 *      Author: Mason
 */

#ifndef SRC_ARTICLE_SONG_H_
#define SRC_ARTICLE_SONG_H_

#include "article.h"

class Song: public Article {
public:
	Song();
	Song(int, int, int, char*);
	virtual ~Song();
	void draw();
};

#endif /* SRC_ARTICLE_SONG_H_ */
