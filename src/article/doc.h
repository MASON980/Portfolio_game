/*
 * doc.h
 *
 *  Created on: 7 Mar 2016
 *      Author: Mason
 */

#ifndef SRC_ARTICLE_DOC_H_
#define SRC_ARTICLE_DOC_H_

#include "article.h"

class doc: public Article {
public:
	int do_orientation;
	doc(int, int, int, char*);
	virtual ~doc();
	void draw() override;
};

#endif /* SRC_ARTICLE_DOC_H_ */
