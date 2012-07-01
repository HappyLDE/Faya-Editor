/*
 *  LDEgui_combobox.cpp
 *  Faya Editor
 *
 *  Created by Dorin Grigore on 31/07/11.
 *  Copyright 2011 Power Watt. All rights reserved.
 *
 */

#include "LDEgui_combobox.h"

LDEgui_combobox_option::LDEgui_combobox_option()
{
	key = 0;
}

LDEgui_combobox_option::~LDEgui_combobox_option()
{
	
}

/////////
LDEgui_combobox::LDEgui_combobox()
{
	selected = -1;
	opened = 0;
	identifier = 0;
    
    choice_pos = 0;
}

LDEgui_combobox::~LDEgui_combobox()
{
	
}

LDEint LDEgui_combobox::key()
{
	if ( selected >= 0 || selected < option.size() ) 
		return option[selected].key;
		
	return 0;
}

string LDEgui_combobox::value()
{
	if ( selected >= 0 || selected < option.size() ) 
		return option[selected].value;
	
	return 0;
}

void LDEgui_combobox::select( LDEuint key )
{
    for ( LDEuint i = 0; i < option.size(); ++i )
    {
        if ( option[i].key == key )
        {
            selected = i;
            
            button.name = option[i].button.name;
            
            break;
        }
    }
}

void LDEgui_combobox::draw( vec2i cursor, LDEfloat frametime )
{
	changed = 0;
	
	button.size = size;
	
	button.draw( cursor, frametime );
	
	if ( menu_item->identifier != identifier && opened )
		opened = 0;
	
	if ( menu_item->changed && opened )
	{
		button.name = option[menu_item->selected].button.name;
		selected = menu_item->selected;
		button.transp = 2;
		changed = 1;
		opened = 0;
	}
	
	if ( button.click )
	{
		opened = 1;
		
		menu_item->close();

		menu_item->pos.x = button.x;
		menu_item->pos.y = button.y;
		menu_item->size.x = size.x;
		menu_item->selected = selected;

		menu_item->identifier = identifier = LDErand(1111,999999999);
		
		for ( LDEuint i = 0; i < option.size(); ++i )
		{			
			menu_item->addButton( &option[i].button );
			option[i].button.pos.y = 0;
			option[i].button.size.x = button.size.x;
			option[i].button.size.y = button.size.y;
			option[i].button.font = font_item;
			option[i].button.texture_rel = texture_item;
			option[i].button.texture_coi = texture_item_hover;
			option[i].button.texture_pre = texture_item_pressed;
			
			if ( i == selected )
			{
				menu_item->pos.y -= button.size.y * (option.size()-1-i);
				option[i].button.transp = 1;
			}
		}
        
        if ( choice_pos )
            menu_item->pos.y = button.y + button.size.y + 5;
	}
}

void LDEgui_combobox::addOption( LDEint key, string value, bool selected_ )
{
	LDEgui_combobox_option option_temp;
	
	option_temp.button.name = value;
	
	option_temp.value = value;
	option_temp.key = key;
	
	option.push_back( option_temp );
	
	if ( selected_ || (option.size() && selected == -1) )
	{
		button.name = value;
		selected = option.size() - 1;
	}
}