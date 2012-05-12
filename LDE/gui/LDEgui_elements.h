/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Graphical User Interface : elements
 * // All the elements that the gui contains : button, check etc
\********************************************************************/

#ifndef LDE_GUI_ELEMENTS_H
#define LDE_GUI_ELEMENTS_H

#include <string>
#include <vector>

using namespace std;

#include "../LDEvariables.h"

#include "LDEgui_drawable.h"
#include "LDEgui_button.h"
#include "LDEgui_editbox.h"
#include "LDEgui_list.h"
#include "LDEgui_menu.h"
#include "LDEgui_scrollbar.h"
#include "LDEgui_text.h"
#include "LDEgui_combobox.h"
#include "LDEgui_checkbox.h"

class LDEgui_elements
{
    public:

	vector<LDEgui_drawable*>drawable;
    vector<LDEgui_button*>button;
	vector<LDEgui_editbox*>editbox;
	vector<LDEgui_list*>list;
    vector<LDEgui_menu*>menu;
	vector<LDEgui_scrollbar*>scrollbar;
	vector<LDEgui_text*>text;
	vector<LDEgui_combobox*>combobox;
	vector<LDEgui_checkbox*>checkbox;
    
	vector<LDEinput>input;
	vector<LDEmouse_event>mouse; // list of mouse events in one frame

    /// default BUTTONS TEXTURE
    LDEldet *texture_button_rel,        // released
            *texture_button_coi,        // cursor on it
            *texture_button_pre,        // pressed
            *texture_button_locked,     // locked texture

			*texture_list,
	
			*texture_list_item,
			*texture_list_item_selected,
	
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
	
			//h
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
	
			*texture_combobox,
			*texture_combobox_hover,
			*texture_combobox_pressed,
    
            *texture_checkbox,
            *texture_checkbox_hover,
            *texture_checkbox_pressed,
            *texture_checkbox_checked,
	
			*texture_editbox,
			*texture_editbox_hover,
			*texture_editbox_active,
	
            /// default BUTTONS MENU TEXTURES
            *texture_menu_button_rel,        // released
            *texture_menu_button_coi,        // cursor on it
            *texture_menu_button_pre,        // pressed
            *texture_menu_button_locked;     // locked texture

	vec2i	app_size;
	
    LDEuint button_uv_up,
            button_uv_down,
            button_uv_left,
            button_uv_right;

    LDEldef *font_elements;

    bool    test_coi,
			active;

    LDEgui_menu_item *menu_item;

	void addText( LDEgui_text *arg );
	void addDrawable( LDEgui_drawable *arg );
    void addButton( LDEgui_button *arg );
	void addEditbox( LDEgui_editbox *arg );
	void addList( LDEgui_list *arg );
    void addMenu( LDEgui_menu *arg );
	void addScrollbar( LDEgui_scrollbar *arg );
	void addCombobox( LDEgui_combobox *arg );
    void addCheckbox( LDEgui_checkbox *arg );
	
	void reset();
    void draw( LDEint x, LDEint y, vec2i cursor, LDEfloat frametime );

    LDEgui_elements();
    ~LDEgui_elements();
};

#endif // LDE_GUI_ELEMENTS_H
