/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Graphical User Interface : base. A base is a container.
\********************************************************************/

#ifndef LDE_GUI_WINDOW_H
#define LDE_GUI_WINDOW_H

#include <string>
#include <vector>

using namespace std;

#include "../LDEvariables.h"
#include "../LDEvec2i.h"

#include "../LDEinput.h"

#include "../LDEldef.h"
#include "../LDEldet.h"

#include "../LDEprimitives.h"

#include "LDEgui_elements.h"
#include "LDEgui_button.h"

class LDEgui_window
{
    public:

    vec2i   pos,            // the position of the base
            size,           // the width and height of the base
			min_size,

            pos_temp;       // ?

	vec2i	cursor_inside;
	
    LDEldet *texture,
			*texture_inactive;

    LDEldef *font_title;

    vec2i   title_pos,
            button_close_pos,
            button_resize_pos,
			app_size;

	LDEint	title_scissor_left,
			title_scissor_right;
	
    bool    focus,          // Does this window has the focus ?
            on_top,         // Is our window on top of the others ?
            clicked_away,   // Was a click away and is hold ?
            wait,           // Action is performed on this window (like while moving the window)
            coi,
            bringOnTop,
			draw_design,
			can_move,
			can_resize,
			closed,
			show_close_button,
			button_close_side,
            move;

	vector<LDEmouse_event>mouse;
	
    void    getOnTop();

    LDEgui_elements elements;

    LDEgui_button   button_resize,
                    button_close;

    /// WINDOW UV
    LDEuint uv_up_right,
            uv_up_left,

            uv_down_right,
            uv_down_left,

            uv_up,
            uv_down,

            uv_left,
            uv_right,

            /// WINDOW real size (this just tells the shadow size)
            start_up,
            start_down,

            start_left,
            start_right,

            /// Là où les éléments (boutons etc) commencent à être affichés dans la fenêtre
            inner_start_up,
            inner_start_down,

            inner_start_left,
            inner_start_right;

    string  title;          // On top of the window, it's title

	void	open();
	void	close();
    bool    cursorOnIt( vec2i cursor );

    void    draw( vec2i cursor, LDEfloat frametime );

    LDEgui_window();          // Constructor
    ~LDEgui_window();         // Destructor
};

#endif // LDE_GUI_WINDOW_H
