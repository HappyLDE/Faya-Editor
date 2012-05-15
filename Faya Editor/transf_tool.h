#ifndef transf_tool_h
#define transf_tool_h

#include "LDEvariables.h"
#include "LDEvec2i.h"
#include "LDEldet.h"
#include "LDEprimitives.h"
#include "LDEmouse_event.h"
#include <vector>

struct LDEtransf_tool
{
    LDEldet *image;
    
    vec2i   new_pos,
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
            wait;
    
    std::vector<LDEmouse_event>mouse; // list of mouse events in one frame
    
    LDEfloat new_rot;
    
    bool changed;
    
    void draw( vec2i pos );
    
    LDEtransf_tool();
    ~LDEtransf_tool();
};

#endif