#ifndef transf_tool_h
#define transf_tool_h

#include "LDEvariables.h"
#include "LDEvec2i.h"
#include "LDEldet.h"
#include "LDEprimitives.h"
#include "LDEmouse_event.h"
#include "LDEfunctions.h"
#include <vector>

struct LDEtransf_tool
{
    LDEldet *image;
    
    vec2i   pos,
            click_offset,
            cursor, // cursor pos
            new_size;

    bool    test_coi,
            hover_arrow_right,
            hover_arrow_bottom,
            hover_circle,
            hover_square_right,
            hover_square_bottom,
            hover_rotate,
            mouse_down,
            init_angle,
            wait;
    
    std::vector<LDEmouse_event>mouse; // list of mouse events in one frame
    
    LDEfloat rot,
            click_offset_angle;
    
    bool changed;
    
    void draw( vec2i my_pos );
    
    LDEtransf_tool();
    ~LDEtransf_tool();
};

#endif