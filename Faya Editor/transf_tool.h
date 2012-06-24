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
            pos_old,
            click_offset,
            cursor; // cursor pos
    
    bool    test_coi,
            hover_arrow_right,
            hover_arrow_bottom,
            hover_circle,
            hover_square_right,
            hover_square_bottom,
            hover_rotate,
            hover,              // all hover
            mouse_down,
            init_change,
            wait;
    
    std::vector<LDEmouse_event>mouse; // list of mouse events in one frame
    
    LDEfloat rot,
            size,
            old_size,
            click_offset_angle;
    
    bool changed;
    
    void reset();
    void draw( vec2i my_pos );
    
    LDEtransf_tool();
    ~LDEtransf_tool();
};

#endif