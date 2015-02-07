//
//  TCone.h
//  ProjectOne
//
//  Created by Joshua Engelsma on 2/5/15.
//
//

#ifndef __ProjectOne__TCone__
#define __ProjectOne__TCone__

#include <stdio.h>
#include "BufferObject.h"
class TCone : public BufferObject {
private:
    const float TOP_RAD = 1.0;
    const float BOT_RAD = .8;
    const float CONE_HEIGHT = .5; /* half thick */
    float N_POINTS = 30;
    
protected:
public:
    void build (void*);
    void render(bool) const;
};

#endif /* defined(__ProjectOne__TCone__) */
