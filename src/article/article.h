/*
 * Article.h
 *
 *  Created on: 1 Mar 2016
 *      Author: Mason
 */

#ifndef ARTICLE_H_
#define ARTICLE_H_

#include <vector>
#include <string>

class Article {

protected:
	std::vector<int> position;
	std::string dir;
	std::vector<float> hitbox;

public:

	Article();
	Article(int, int, int, char*);
	virtual ~Article();
	std::vector<int> getPosition() { return position;}
	std::vector<float> getHitbox() { return hitbox;}
	std::string getDirectory() { return dir;}

	virtual void draw() {return;};
};

#endif /* ARTICLE_H_ */
