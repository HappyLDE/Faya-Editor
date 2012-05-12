//
//  Sprite.h
//  Faya Editor
//
//  Created by Dorin Grigore on 2/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Faya_Editor_Sprite_h
#define Faya_Editor_Sprite_h

#include "LDEvariables.h"
#include "LDEvec2i.h"
#include "LDEvec4i.h"
#include "LDEprimitives.h"
#include "LDEmouse_event.h"
#include <string>
#include <vector>
#include <iostream>

struct Sprite
{
    vec2i   pos,    // Pos in px
            size,   // Size in px
            size_100,
            image_size,
            offset,
            flip;   // Texture orientation
    
    bool    selected;
    
    std::string name;
    
    vec4i   texture_uv;
    
    LDEuint image_id;
    
    LDEfloat rot,       // Rotation in degrees
             opacity;
    
    Sprite();
    ~Sprite();
};

struct SpriteBatchNode
{
    std::vector<Sprite>sprites;
    
    std::vector<LDEmouse_event>mouse; // list of mouse events in one frame
    
    bool    test_coi,
            changed,
            keep_select;    // When we click on a sprite, if we keep the previous selected ones
    
    vec2i   cursor,
            selected_pos,
            camera_pos;
    
    LDEfloat camera_zoom;
    
    LDEuint last_texture_id;
    
    void unselectAll();
    
    void setPosition( vec2i pos );
    void setSize( vec2i size );
    void draw();
    
    SpriteBatchNode();
    ~SpriteBatchNode();
};

#endif
