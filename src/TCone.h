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
    float CONE_HEIGHT = .5; /* half thick */
    float N_POINTS = 30;
    float x_rad_top = 3.0;
    float y_rad_top = 1.5;
    float x_rad_bot = 3.0;
    float y_rad_bot = 1.5;
    
protected:
public:
    void build (void*);
    void build_with_params(float height, float x_rad_t, float
                           y_rad_t, float x_rad_b, float y_rad_b, float subdivisions);
    void build_cylinder(float height, float radius, float subdivisions);
    void render(bool) const;
};

#endif /* defined(__ProjectOne__TCone__) */
