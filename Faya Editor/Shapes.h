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
#include <vector>
#include <string>
#include "LDEmouse_event.h"
#include "Triangulate.h"
#include "LDEprimitives.h"
#include <iostream>

struct Shapes
{
    Shapes();
    ~Shapes();
    
    vec2i cursor;
    
    std::vector<LDEmouse_event>mouse; // list of mouse events in one frame
    
    bool assign_selected;
    
    void draw();
    
    std::string name;
    
    bool selected;
    
    std::vector<vec2i>vertex;
    std::vector<vec2i>path_vertex;
};

#endif