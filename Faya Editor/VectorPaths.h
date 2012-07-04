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

// This is used to hold vector paths (for now no curves nor triangulation, but these are to come)
struct VectorPaths
{
    std::vector<vec2i>vertex;
    
    std::string name;
    
    bool active;
    
    void addVertex( vec2i pos );
    LDEint selected_vertex;
    
    void draw();
    
    VectorPaths();
    ~VectorPaths();
};

#endif
