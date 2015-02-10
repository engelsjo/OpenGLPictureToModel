/*
 * Castle.h
 *
 *  Created on: Feb 7, 2015
 *      Author: Zachary Ash
 */

#ifndef CASTLE_H_
#define CASTLE_H_

#include "BufferObject.h"
#include "Cube.h"
#include "TCone.h"
#include "Cone.h"


class Castle : public BufferObject {
private:
	Cube castle;
	TCone tower;
	Cone roof;
	TCone bigTower;
	Cone bigRoof;

public:
	void build(void*);
	void render(bool) const;
};

#endif /* CASTLE_H_ */
