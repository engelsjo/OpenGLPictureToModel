//
//  Cube.h
//  ProjectOne
//
//  Created by Joshua Engelsma on 2/3/15.
//
//

#ifndef __ProjectOne__Cube__
#define __ProjectOne__Cube__

#include <stdio.h>
#include "BufferObject.h"
class Cube : public BufferObject {
private:
    const float LENGTH = 1.0;
    const float WIDTH = 1.0;
    const float HEIGHT = 1.0; /* half thick */
    int top_count;
    
protected:
public:
    void build (void*);
    void render(bool) const;
};
#endif /* defined(__ProjectOne__Cube__) */


