/*
 *  LDEgui_combobox.h
 *  Faya Editor
 *
 *  Created by Dorin Grigore on 31/07/11.
 *  Copyright 2011 Power Watt. All rights reserved.
 *
 */

#ifndef LDE_GUI_COMBOBOX_H
#define LDE_GUI_COMBOBOX_H

#include <string>

using namespace std;

#include "LDEgui_button.h"
#include "LDEgui_menu_item.h"

struct LDEgui_combobox_option
{
	LDEint	key;
	string	value;
	
	LDEgui_button button;
	
	LDEgui_combobox_option();
	~LDEgui_combobox_option();
};

struct LDEgui_combobox
{
	LDEgui_button button;
	
	LDEgui_menu_item *menu_item;
	
	vector<LDEgui_combobox_option>option;
	
	LDEldef *font_item;
	
	LDEldet *texture_item,
			*texture_item_hover,
			*texture_item_pressed;
	
	bool	opened,
            changed,
            choice_pos;
	
	LDEint	selected;
	
	LDEuint	identifier;
	
	vec2i	pos,
			size;
	
	LDEint	key();
	string	value();
	
	void	addOption( LDEint value, string value_, bool selected_ );
	
	void	draw( vec2i cursor, LDEfloat frametime );
	
	LDEgui_combobox();
	~LDEgui_combobox();
};

#endif