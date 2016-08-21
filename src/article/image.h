/*
 * image.h
 *
 *  Created on: 1 Mar 2016
 *      Author: Mason
 */

#ifndef SRC_ARTICLE_IMAGE_H_
#define SRC_ARTICLE_IMAGE_H_

#include "article.h"
#include <vector>

class image: public Article {
private:
	unsigned char* img;
	std::vector<int> img_size;
	float res;
public:
	image();
	image(int, int, int, char*);
	virtual ~image();
	void draw();
	float determineRes(float);
	float getRes() { return res; };
	void shiftPosition(int, int, int);
};

#endif /* SRC_ARTICLE_IMAGE_H_ */
