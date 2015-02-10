/*
 * Gate.h
 *
 *  Created on: Feb 9, 2015
 *      Author: Zachary Ash
 */

#ifndef GATE_H_
#define GATE_H_

#include "BufferObject.h"
#include "Cube.h"
#include "TCone.h"

class Gate : public BufferObject {
private:
	Cube side;
	Cube top;
	TCone gate;

public:
	void build(void*);
	void render(bool) const;
};

#endif /* GATE_H_ */
