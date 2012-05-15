#ifndef transf_tool_h
#define transf_tool_h

#include "LDEvariables.h"
#include "LDEvec2i.h"
#include "LDEldet.h"
#include "LDEprimitives.h"

struct LDEtransf_tool
{
    LDEldet *image;
    
    vec2i   new_pos,
            new_size;

    LDEfloat new_rot;
    
    void draw( vec2i pos );
    
    LDEtransf_tool();
    ~LDEtransf_tool();
};

#endif