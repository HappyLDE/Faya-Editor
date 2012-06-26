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
#include "LDEinput.h"
#include <string>
#include <vector>
#include <iostream>
#include <math.h>

struct Sprite
{
    vec2i   pos,    // Pos in px
            pos_offset,
            size,   // Size in px
            size_100,
            image_size,
            offset,
            flip;   // Texture orientation
    
    bool    selected,
            init_dist;
    
    std::string name;
    
    vec4i   texture_uv;
    
    LDEuint image_id;
    
    LDEfloat rot,       // Rotation in degrees
            rot_offset,
            opacity,
            dist;
    
    Sprite();
    ~Sprite();
};

struct SpriteBatchNode
{
    std::vector<Sprite>sprites;
    
    std::vector<LDEinput>input;
    std::vector<LDEmouse_event>mouse; // list of mouse events in one frame
    
    bool    test_coi,
            changed,
            keep_select;    // When we click on a sprite, if we keep the previous selected ones
    
    LDEfloat selected_rot,
            selected_opacity;
    
    vec2i   cursor,
            selected_pos,
            selected_size,
            selected_ap,
            tool_pos,
            camera_pos;
    
    LDEfloat camera_zoom;
    
    LDEuint last_texture_id;
    
    void deselect();
    
    vec2i getTransfPos() const;
    void showPosOffset( vec2i pos_offset );
    void applyPosOffset();
    void setPosition( vec2i pos );
    void setRotation( LDEfloat rotation );
    void setOpacity( LDEfloat opacity );
    void setOffset( vec2i offset );
    LDEint setSizeX( LDEint size_x, bool keep_ratio );
    LDEint setSizeY( LDEint size_y, bool keep_ratio );
    LDEuint getNumSelected() const;
    void draw();
    
    SpriteBatchNode();
    ~SpriteBatchNode();
};

#endif
