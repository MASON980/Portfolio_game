/*
 * video.h
 *
 *  Created on: 2 Mar 2016
 *      Author: Mason
 */

#ifndef SRC_ARTICLE_VIDEO_H_
#define SRC_ARTICLE_VIDEO_H_

#include "article.h"

class Video: public Article {
public:
	Video();
	Video(int, int, int, char*);
	virtual ~Video();
	void draw();
};

#endif /* SRC_ARTICLE_VIDEO_H_ */
