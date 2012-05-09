//
//  Spritesheet.h
//  Faya Editor
//
//  Created by Dorin Grigore on 28/04/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Faya_Editor_Spritesheet_h
#define Faya_Editor_Spritesheet_h

#include <vector>
#include <string>
#include "LDEimage.h"
#include "LDEvec2i.h"
#include "LDEprimitives.h"
#include "LDEmouse_event.h"

struct Spritesheet_frame
{
    vec2i pos,
    pos_window,
    margin,       // We'll use this to center the thumbnail
    size,         // original size
    size_100;     // thumbnail size
    
    std::string name;
    
    Spritesheet_frame();
    ~Spritesheet_frame();
};

struct Spritesheet
{
    vec2i   cursor_pos,
    window_pos;
    
    bool    test_coi,
    used,
    mouse_down;
    
    LDEint  selected;
    
    std::vector<LDEmouse_event>mouse; // list of mouse events in one frame
    
    LDEimage image; // this will contain tha image spritesheet
    
    std::vector<Spritesheet_frame>frames;
    
    void draw();
    
    Spritesheet();
    ~Spritesheet();
};

#endif
