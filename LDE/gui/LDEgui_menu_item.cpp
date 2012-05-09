/*
 *  LDEgui_menu_item.cpp
 *  Faya Editor
 *
 *  Created by Dorin Grigore on 31/07/11.
 *  Copyright 2011 Power Watt. All rights reserved.
 *
 */

#include "LDEgui_menu_item.h"

/// MENU ITEM //////
LDEgui_menu_item::LDEgui_menu_item()
{
    button_uv_up = 0;
    button_uv_down = 0,
    button_uv_left = 0,
    button_uv_right = 0;
	
    closed = 1;
	
    coi = 0;
	
	selected = -1;
	
	identifier = 0;
}

LDEgui_menu_item::~LDEgui_menu_item()
{

}

void LDEgui_menu_item::close()
{
	button.erase( button.begin(), button.end() );
	
	closed = 1;
}

void LDEgui_menu_item::addButton( LDEgui_button *arg )
{
    button.push_back( arg );
	
    LDEint button_size = button.size()-1;
    
    button[button_size]->font = font_elements;
    button[button_size]->texture_rel = texture_button_rel;
    button[button_size]->texture_coi = texture_button_coi;
    button[button_size]->texture_pre = texture_button_pre;
    button[button_size]->texture_locked = texture_button_locked;
    
	size.y = 0;
	
    for ( LDEuint i = 0; i < button_size; ++i )
	{
        button[i]->pos.y += button[i]->size.y;
		
		if ( size.y < button[i]->pos.y + button[i]->size.y )
			size.y = button[i]->pos.y + button[i]->size.y;
	}
}