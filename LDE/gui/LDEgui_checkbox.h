/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Graphical User Interface : Checbox
 \********************************************************************/

#ifndef LDE_GUI_CHECKBOX_H
#define LDE_GUI_CHECKBOX_H

#include "LDEgui_button.h"
#include "LDEvariables.h"
#include "LDEvec2i.h"

struct LDEgui_checkbox
{
    LDEgui_button button;
    
    bool    checked,
            changed;
    
    vec2i   pos;
    
    void setCheck( bool state );
    void draw( vec2i cursor, LDEfloat frametime );
    
    LDEgui_checkbox();
    ~LDEgui_checkbox();
};

#endif