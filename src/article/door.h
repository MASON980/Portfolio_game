/*
 * door.h
 *
 *  Created on: 4 Mar 2016
 *      Author: Mason
 */

#ifndef SRC_ARTICLE_DOOR_H_
#define SRC_ARTICLE_DOOR_H_

#include "article.h"

class door: public Article {
public:
	int orientation;
	door(int, int, int, char*);
	virtual ~door();
	void draw() override;

};

#endif /* SRC_ARTICLE_DOOR_H_ */
