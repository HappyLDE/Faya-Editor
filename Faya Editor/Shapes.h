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

struct Shapes
{
    Shapes();
    ~Shapes();
    
    void draw();
    
    std::vector<vec2i>vertex;
    std::vector<vec2i>path_vertex;
};

#endif