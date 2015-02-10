/*
 * Ram.h
 *
 *  Created on: Feb 7, 2015
 *      Author: Zachary Ash
 */

#ifndef RAM_H_
#define RAM_H_

#include "BufferObject.h"
#include "Cube.h"
#include "TCone.h"
#include "TPillar.h"

class Ram : public BufferObject {
private:
	TCone cylinder;
	Cube cube;
	TPillar roof;

public:
	void build(void*);
	void render(bool) const;
};

#endif /* RAM_H_ */
