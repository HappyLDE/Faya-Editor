//
//  Shapes.h
//  Faya Editor
//
//  Created by Dorin Grigore on 3/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef SHAPES_H
#define SHAPES_H

#include <OpenGL/gl.h>
#include "LDEvec2i.h"
#include "LDEvec3f.h"
#include <vector>
#include <string>
#include "LDEinput.h"
#include "LDEmouse_event.h"
#include "Triangulate.h"
#include "LDEprimitives.h"
#include <iostream>
#include "LDEvariables.h"
#include "VectorPaths.h"

struct Shapes
{
    Shapes();
    ~Shapes();
    
    vec2i cursor;
    
    vec3f color;
    
    std::vector<LDEinput>input;
    std::vector<LDEmouse_event>mouse; // list of mouse events in one frame
    
    LDEint selected_vertex;
    
    bool    assign_selected,
            can_change_selected,
            edit_mode,
            active,
            test_coi,
            moving,
            add_to_edge_mode;
    
    void draw();
    void drawEditMode();
    
    std::string name;
    
    bool selected;
    
    void triangulate();
    
    std::vector<vec2i>vertex;
    
    VectorPaths path;

};

#endif