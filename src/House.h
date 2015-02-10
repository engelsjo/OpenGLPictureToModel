//
//  House.h
//  ProjectOne
//
//  Created by Joshua Engelsma on 2/7/15.
//
//

#ifndef __ProjectOne__House__
#define __ProjectOne__House__

#include <stdio.h>
#include "Cube.h"
#include "TPillar.h"

class House : public BufferObject {
    
protected:
public:
    void build (void*);
    void render(bool) const;
};


#endif /* defined(__ProjectOne__House__) */
