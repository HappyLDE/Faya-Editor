/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Graphical User Interface : Checbox
 \********************************************************************/

#include "LDEgui_checkbox.h"

LDEgui_checkbox::LDEgui_checkbox()
{
    checked = 0;
    changed = 0;
}

LDEgui_checkbox::~LDEgui_checkbox()
{
    
}

void LDEgui_checkbox::setCheck( bool state )
{
    button.draw_icon = checked = state;
    
    changed = 1;
}

void LDEgui_checkbox::draw( vec2i cursor, LDEfloat frametime )
{
    changed = 0;
    
    button.draw( cursor, frametime );
    
    if ( button.click )
        setCheck( 1-checked );
}