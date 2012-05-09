//
//  Vector.h
//  Faya Editor
//
//  Created by Dorin Grigore on 17/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Faya_Editor_Vector_h
#define Faya_Editor_Vector_h

#include <iostream>
#include <OpenGL/gl.h>
#include "LDEvec2i.h"
#include <vector>
#include <string>

using namespace std;

struct VectorPaths
{
    vector<vec2i>vertex;
    
    bool active;
    
    void addVertex( vec2i pos );
    LDEint selected;
    
    void draw();
    
    VectorPaths();
    ~VectorPaths();
};

#endif
