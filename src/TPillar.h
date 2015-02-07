//
//  TPillar.h
//  ProjectOne
//
//  Created by Joshua Engelsma on 2/7/15.
//
//  Triangular Pillar for the front of the Castle

#ifndef __ProjectOne__TPillar__
#define __ProjectOne__TPillar__

#include <stdio.h>
#include "BufferObject.h"
class TPillar : public BufferObject {
private:
    const float LENGTH = 1;
    const float WIDTH = .5;
    const float HEIGHT = 1;
    
protected:
public:
    void build (void*);
    void render(bool) const;
};

#endif /* defined(__ProjectOne__TPillar__) */


