//
//  LDEgui_sprite.h
//  Faya Editor
//
//  Created by Dorin Grigore on 6/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LDE_GUI_SPRITE_H
#define LDE_GUI_SPRITE_H

#include "LDEvariables.h"
#include "LDEprimitives.h"
#include "LDEmouse_event.h"
#include "LDEvec3f.h"
#include <vector>
#include <iostream>

struct LDEgui_sprite
{
    std::vector<LDEmouse_event>mouse; // list of mouse events in one frame
    
    LDEint x, y,
            borde_width;
    
    vec2i   pos,
            pos_temp,
            size;
    
    vec3f   color,
            color_border;
    
    LDEfloat opacity;
    
    LDEuint texture_id;
    
    bool    coi, pressed, click, test_coi, clicked_away;
    
    LDEgui_sprite();
    ~LDEgui_sprite();
    
    void draw( vec2i cursor, LDEfloat frametime );
};

#endif