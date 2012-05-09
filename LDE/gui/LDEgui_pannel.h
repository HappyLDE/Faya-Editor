/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Graphical User Interface : pannel. A pannel is always under all windows.
 * // May contain menu, buttons etc.
\********************************************************************/

#ifndef LDE_GUI_PANNEL_H
#define LDE_GUI_PANNEL_H

#include "../LDEvariables.h"
#include "../LDEvec2i.h"

#include "../LDEldet.h"

#include "LDEgui_elements.h"

class LDEgui_pannel
{
    public:

    vec2i   pos,            // the position of the base
            size,           // the width and height of the base
			app_size;

    LDEuint uv_up,
            uv_down,

            uv_left,
            uv_right,

            start_up,
            start_down,
            start_left,
            start_right;

    LDEgui_elements elements;

    LDEldet *texture;

    bool    focus,          // Does this window has the focus ?
            coi,
            clicked_away,
            wait;
	
    bool    cursorOnIt( vec2i cursor );
    void    draw( vec2i cursor, LDEfloat frametime );

    LDEgui_pannel();          // Constructor
    ~LDEgui_pannel();         // Destructor
};

#endif // LDE_GUI_PANNEL_H
