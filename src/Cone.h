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
    float RADIUS = 1.0;
    float HEIGHT = 1.0; /* half thick */
    float SUB_DIVIDE = 200;
    
protected:
public:
    void build (void*);
    void build_with_params(float radius, float height, float subdivisions);
    void render(bool) const;
};

#endif /* defined(__ProjectOne__Cone__) */
