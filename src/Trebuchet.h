/*
 * Trebuchet.h
 *
 *  Created on: Feb 7, 2015
 *      Author: Zachary Ash
 */

#ifndef TREBUCHET_H_
#define TREBUCHET_H_

#include "BufferObject.h"
#include "TCone.h"
#include "Cube.h"

class Trebuchet : public BufferObject {
private:
	Cube long_beam;
	Cube short_beam;
	TCone mass;
	TCone arm;

public:
	void build(void*);
	void render(bool launching) const;
};

#endif /* TREBUCHET_H_ */
