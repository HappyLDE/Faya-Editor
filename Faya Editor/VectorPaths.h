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
#include "LDEfunctions.h"
#include "LDEprimitives.h"
#include "LDEinput.h"
#include "LDEmouse_event.h"

// This is used to hold vector paths (for now no curves nor triangulation, but these are to come)
struct VectorPaths
{
    std::vector<vec2i>vertex;
    
    std::vector<LDEinput>input;
    std::vector<LDEmouse_event>mouse; // list of mouse events in one frame
    
    std::string name;
    
    vec2i   cursor;
    
    bool    active,
            test_coi,
            moving,
            add_to_edge_mode;
    
    void addVertex( vec2i pos );
    LDEint selected_vertex;
    
    void draw();
    
    VectorPaths();
    ~VectorPaths();
};

#endif
