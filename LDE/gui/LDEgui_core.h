/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Graphical User Interface : core
\********************************************************************/

#ifndef LDE_GUI_CORE_H
#define LDE_GUI_CORE_H

#include <string>
#include <vector>

using namespace std;

#include "../LDEvariables.h"
#include "../LDEvec2i.h"

#include "../LDEldet.h"
#include "../LDEldef.h"

#include "../LDEinput.h"

#include "../LDEprimitives.h"

#include "LDEgui_window.h"
#include "LDEgui_pannel.h"
#include "LDEgui_menu.h"

class LDEgui
{
    public:
    vector<LDEgui_window*>window;
    vector<LDEgui_pannel*>pannel;

	vector<LDEinput>input;
	vector<LDEmouse_event>mouse; // list of mouse events in one frame
	
    LDEgui_menu_item menu;
    bool close_menu;

    LDEuint texture_window_id,
            texture_window_inactive_id;

    bool    unused,
			window_button_close_side,
            focus_window,
            focus_menu;    // mouse button 1

    LDEldet *texture_window,
            *texture_window_inactive,

			*texture_window_close,
			*texture_window_close_hover,
			*texture_window_close_pressed,
	
            *texture_pannel,

			*texture_list,
			*texture_list_item_selected,
	
			*texture_list_item,
	
			*texture_combobox,
			*texture_combobox_hover,
			*texture_combobox_pressed,
	
			*texture_scrollbar_button_up,
			*texture_scrollbar_button_up_hover,
			*texture_scrollbar_button_up_pressed,
	
			*texture_scrollbar_button_down,
			*texture_scrollbar_button_down_hover,
			*texture_scrollbar_button_down_pressed,
	
			*texture_scrollbar_middle,
	
			*texture_scrollbar_button_middle,
			*texture_scrollbar_button_middle_hover,
			*texture_scrollbar_button_middle_pressed,
	
			*texture_scrollbar_h_button_up,
			*texture_scrollbar_h_button_up_hover,
			*texture_scrollbar_h_button_up_pressed,
			
			*texture_scrollbar_h_button_down,
			*texture_scrollbar_h_button_down_hover,
			*texture_scrollbar_h_button_down_pressed,
			
			*texture_scrollbar_h_middle,
			
			*texture_scrollbar_h_button_middle,
			*texture_scrollbar_h_button_middle_hover,
			*texture_scrollbar_h_button_middle_pressed,
	
			*texture_editbox,
			*texture_editbox_hover,
			*texture_editbox_active,
	
            /// default BUTTONS TEXTURE
            *texture_button_rel,        // released
            *texture_button_coi,        // cursor on it
            *texture_button_pre,        // pressed
			*texture_button_locked,     // locked texture

            /// window button resize texture
            *texture_button_window_resize_rel,

            /// default BUTTONS MENU TEXTURES
            *texture_menu_button_rel,        // released
            *texture_menu_button_coi,        // cursor on it
            *texture_menu_button_pre,        // pressed
            *texture_menu_button_locked;     // locked texture

    LDEldef *font_window_title,
            *font_elements;

    vec2i   window_title_pos,
            window_button_close_pos,
            window_button_resize_pos,
	
			app_size; // Desktop window size (not gui window!)

            /// WINDOW UV
    LDEuint window_uv_up_right,
            window_uv_up_left,

            window_uv_down_right,
            window_uv_down_left,

            window_uv_up,
            window_uv_down,

            window_uv_left,
            window_uv_right,

            // WINDOW real size (this just tells the shadow size)
            window_start_up,
            window_start_down,

            window_start_left,
            window_start_right,

            // Là où les éléments (boutons etc) commencent à être affichés dans la fenêtre
            window_inner_start_up,
            window_inner_start_down,

            window_inner_start_left,
            window_inner_start_right,

            /// PANNEL settings (UVs)
            pannel_uv_up,
            pannel_uv_down,

            pannel_uv_left,
            pannel_uv_right,

            // PANNEL real size (this just tells the shadow size)
            pannel_start_up,
            pannel_start_down,

            pannel_start_left,
            pannel_start_right,

            button_uv_up,
            button_uv_down,
            button_uv_left,
            button_uv_right;

    void addWindow( LDEgui_window *arg );   // procedure to add a window
    void addPannel( LDEgui_pannel *arg );   // Procedure du add a pannel (contains all stuff as a window but is under all the windows)

    void draw( vec2i cursor, LDEfloat frametime );

    LDEgui();
    ~LDEgui();
};

#endif // LDE_GUI_CORE_H