//
//  PalmTree.h
//  ProjectOne
//
//  Created by Joshua Engelsma on 2/7/15.
//
//

#ifndef __ProjectOne__PalmTree__
#define __ProjectOne__PalmTree__


#include <stdio.h>
#include "BufferObject.h"
#include "TCone.h"
class PalmTree : public BufferObject {
    
protected:
public:
    void build (void*);
    void render(bool) const;
};



#endif /* defined(__ProjectOne__PalmTree__) */
