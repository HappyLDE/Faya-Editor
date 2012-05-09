/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Graphical User Interface : elements
 * // Menu
\********************************************************************/

#include "LDEgui_menu.h"

/// MENU BAR ////////// CORE
LDEgui_menu::LDEgui_menu()
{
    button_uv_up = 0;
    button_uv_down = 0,
    button_uv_left = 0,
    button_uv_right = 0;

    item_height = 20;

    opened = 0;
	
	selected = -1;
}

LDEgui_menu::~LDEgui_menu()
{

}

void LDEgui_menu::addItem( LDEgui_menu_item *arg )
{
    item.push_back( arg );

    LDEint item_size = item.size()-1;
    
    for ( LDEuint i = 0; i < item_size; ++i )
    {
        item[item_size]->button_parent.pos.x += item[i]->button_parent.size.x + 1;
    }

    item[item_size]->button_parent.font = font_elements;

    item[item_size]->font_elements = font_elements;

    item[item_size]->button_parent.texture_rel = texture_menu_button_rel;
    item[item_size]->button_parent.texture_coi = texture_menu_button_coi;
    item[item_size]->button_parent.texture_pre = texture_menu_button_pre;
    item[item_size]->button_parent.texture_locked = texture_menu_button_locked;

    item[item_size]->texture_button_rel = texture_button_rel;
    item[item_size]->texture_button_coi = texture_button_coi;
    item[item_size]->texture_button_pre = texture_button_pre;
    item[item_size]->texture_button_locked = texture_button_locked;

    /// Pass texture adresses (JUST ADRESSES)
    item[item_size]->button_parent.uv_up = 0; // button_uv_up;
    item[item_size]->button_parent.uv_down = 0; // button_uv_down;
    item[item_size]->button_parent.uv_left = 0; // button_uv_left;
    item[item_size]->button_parent.uv_right = 0; // button_uv_right;

    item[item_size]->button_uv_up = button_uv_up;
    item[item_size]->button_uv_down = button_uv_down;
    item[item_size]->button_uv_left = button_uv_left;
    item[item_size]->button_uv_right = button_uv_right;

    item[item_size]->button_parent.size.y = item_height;
}

void LDEgui_menu::draw( vec2i cursor, LDEfloat frametime, bool test_coi )
{
	// Pour chaque item
    for ( LDEuint i = 0; i < item.size(); ++i )
    {
        item[i]->button_parent.x = pos.x + item[i]->button_parent.pos.x;
        item[i]->button_parent.y = pos.y + item[i]->button_parent.pos.y;
        item[i]->button_parent.test_coi = test_coi;
		item[i]->button_parent.mouse = mouse;
        item[i]->button_parent.draw( cursor, frametime );
		
        if ( item[i]->button_parent.click || (opened && item[i]->button_parent.coi && !menu_item->closed) )
        {
			for ( LDEuint s = 0; s < item.size(); ++s )
			{
				item[s]->button_parent.texture_rel = texture_menu_button_rel;
				item[s]->button_parent.texture_coi = texture_menu_button_coi;
			}
			
			item[i]->button_parent.texture_rel = texture_menu_button_pre;
			item[i]->button_parent.texture_coi = texture_menu_button_pre;
			
			selected = i;
			
			opened = 1;
			
            menu_item->button.erase( menu_item->button.begin(), menu_item->button.end() );

            menu_item->selected = -1;
            
            // Assign the menu_list of this item to the main menu_list
            if ( item[i]->button.size() )
            {
                menu_item->button = item[i]->button;
				
                menu_item->size.reset();
                
                for ( LDEuint b = 0;  b < menu_item->button.size(); ++b )
                {
                    if ( menu_item->size.x < menu_item->button[b]->size.x )
                        menu_item->size.x = menu_item->button[b]->size.x;

                    menu_item->size.y += menu_item->button[b]->size.y;
                    
                    menu_item->button[b]->pos.y = b * item_height;
                    
					menu_item->button[b]->mouse = mouse;
                }

                for ( LDEuint b = 0;  b < menu_item->button.size(); ++b )
                {
                    menu_item->button[b]->size.x = menu_item->size.x;
                }

                menu_item->closed = 0;
            }

            menu_item->pos.x = item[i]->button_parent.pos.x;
            menu_item->pos.y = item[i]->button_parent.pos.y + item_height + 5;
        }
    }
}
