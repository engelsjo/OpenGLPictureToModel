//
//  LandBase.h
//  ProjectOne
//
//  Created by Joshua Engelsma on 2/2/15.
//
//

#ifndef __ProjectOne__LandBase__
#define __ProjectOne__LandBase__

#include "BufferObject.h"
class LandBase : public BufferObject {
private:
    const float LENGTH = 1.0;
    const float WIDTH = 1.0;
    const float THICKNESS = 0.4; /* half thick */
    int pts_count, top_count;
    
protected:
public:
    void build (void*);
    void render(bool) const;
};
#endif
