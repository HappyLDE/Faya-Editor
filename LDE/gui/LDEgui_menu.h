/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Graphical User Interface : elements
 * // Menu
\********************************************************************/

#ifndef LDE_GUI_MENU_H
#define LDE_GUI_MENU_H

#include <vector>

using namespace std;

#include "../LDEvariables.h"
#include "../LDEvec2i.h"

#include "../LDEldef.h"

#include "LDEgui_button.h"
#include "LDEgui_menu_item.h"

class LDEgui_menu
{
    vector<LDEgui_menu_item*>item;
    public:
	
	vector<LDEmouse_event>mouse; // list of mouse events in one frame

    LDEldef *font_elements;

    LDEgui_menu_item *menu_item;

    LDEldet *texture_button_rel,        // released
            *texture_button_coi,        // cursor on it
            *texture_button_pre,        // pressed
            *texture_button_switch,     // switch (blend between released and cursor on it)
            *texture_button_locked,     // locked texture

            /// default BUTTONS MENU TEXTURES
            *texture_menu_button_rel,        // released
            *texture_menu_button_coi,        // cursor on it
            *texture_menu_button_pre,        // pressed
            *texture_menu_button_switch,     // switch (blend between released and cursor on it)
            *texture_menu_button_locked;     // locked texture

    LDEuint button_uv_up,
            button_uv_down,
            button_uv_left,
            button_uv_right;

	LDEint	selected;
	
    vec2i   pos;

    bool    opened;

    LDEint  item_height;

    void addItem( LDEgui_menu_item *arg );

    void draw( vec2i cursor, LDEfloat frametime, bool test_coi );
	
    LDEgui_menu();
    ~LDEgui_menu();
};

#endif // LDE_GUI_MENU_H
