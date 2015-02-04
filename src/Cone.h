//
//  Cone.h
//  ProjectOne
//
//  Created by Joshua Engelsma on 2/3/15.
//
//

#ifndef __ProjectOne__Cone__
#define __ProjectOne__Cone__

#include <stdio.h>
#include "BufferObject.h"
class Cone : public BufferObject {
private:
    const float RADIUS = 1.0;
    const float HEIGHT = 1.0; /* half thick */
    const float SUB_DIVIDE = 200;
    
protected:
public:
    void build (void*);
    void render(bool) const;
};

#endif /* defined(__ProjectOne__Cone__) */
