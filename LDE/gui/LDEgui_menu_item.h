/*
 *  LDEgui_menu_item.h
 *  Faya Editor
 *
 *  Created by Dorin Grigore on 31/07/11.
 *  Copyright 2011 Power Watt. All rights reserved.
 *
 */

#ifndef LDE_GUI_MENU_ITEM_H
#define LDE_GUI_MENU_ITEM_H

#include "../LDEldef.h"

#include "LDEgui_button.h"

struct LDEgui_menu_item
{
    LDEgui_button button_parent;
    std::vector<LDEgui_button*>button;
	
    void addButton( LDEgui_button *arg );

    vec2i   pos,
			size;
	
	LDEint	selected;
	
    bool    closed,
			changed,
			coi;
	
	LDEuint identifier;

    LDEldef *font_elements;
	
    LDEldet *texture_button_rel,        // released
            *texture_button_coi,        // cursor on it
            *texture_button_pre,        // pressed
            *texture_button_locked;     // locked texture
	
	void	close();
	
    LDEuint button_uv_up,
	button_uv_down,
	button_uv_left,
	button_uv_right;
	
    LDEgui_menu_item();
    ~LDEgui_menu_item();
};

#endif