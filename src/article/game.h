/*
 * game.h
 *
 *  Created on: 1 Mar 2016
 *      Author: Mason
 */

#ifndef SRC_ARTICLE_GAME_H_
#define SRC_ARTICLE_GAME_H_

#include "article.h"

class Game: public Article {
public:
	Game();
	Game(int, int, int, char*);
	virtual ~Game();
	void draw() override;
};

#endif /* SRC_ARTICLE_GAME_H_ */
