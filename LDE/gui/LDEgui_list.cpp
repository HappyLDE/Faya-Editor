/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Graphical User Interface : elements
 *  // List of butons
\********************************************************************/

#include "LDEgui_list.h"


LDEgui_list_item::LDEgui_list_item()
{
	key = 0;
	selected = 0;
}

LDEgui_list_item::~LDEgui_list_item()
{
	
}

/////////
LDEgui_list::LDEgui_list()
{
	size = vec2i( 20, 20 );
	
	changed = 0;
	
	focus = 0;
	test_coi = 0;
	active = 0;
	
	offset = 0;
	
	shift = 0;
	
	x = 0,
	y = 0;
	
	uv_left = 8;	// left
	uv_right = 8;	// right
	uv_up = 8;		// up
	uv_down = 8;	// down
	
	start_left = 0;
	start_right = 0;
	start_up = 4;
	start_down = 4;
	
	item_height = 15;
	
	selected = -1;
	
	scroll = 0;
	
	coi = 0;
	
	content_height = start_up + start_down;
	
	color = vec3f( 1,1,1 );
	
	click = 0;
	dbclick = 0;
}

LDEgui_list::~LDEgui_list()
{

}

void LDEgui_list::remove( LDEuint number )
{
	selected = 0;
	
	item.erase( item.begin() + number );
}

void LDEgui_list::deselect()
{
    selected = -1;
    
    for ( LDEuint i = 0; i < item.size(); ++i )
    {
        item[i].button.texture_rel = texture_list_item;
        item[i].button.texture_coi = texture_list_item;
        
        item[i].button.text_color = color;
        
        item[i].selected = 0;
    }
    
    changed = 1;
    focus = 0;
}

void LDEgui_list::select( LDEuint number, bool keep_rest )
{
	if ( !keep_rest )
	{
		for ( LDEuint i = 0; i < item.size(); ++i )
		{
			item[i].button.texture_rel = texture_list_item;
			item[i].button.texture_coi = texture_list_item;
			
			item[i].button.text_color = color;
			
			item[i].selected = 0;
		}
	}

	selected = number;
	
	if ( selected < 0 )
		selected = 0;
	
	if ( selected > item.size() - 1 )
		selected = item.size() - 1;

	item[selected].button.texture_rel = texture_list_item_selected;
	item[selected].button.texture_coi = texture_list_item_selected;
	item[selected].selected = 1;
	item[selected].button.text_color = color_selected;
	
	changed = 1;
	
	focus = 1;
}

void LDEgui_list::addItem( LDEint key, string value )
{
	LDEgui_list_item item_temp;
	
    item_temp.button.font = font;
	
	item_temp.button.name = value;
	
	item_temp.button.text_side = 1;
	
	item_temp.button.size.y = item_height;
	
	item_temp.key = key;
	
	content_height += item_height;
	
    item_temp.button.texture_rel = texture_list_item;
    item_temp.button.texture_coi = texture_list_item;
    item_temp.button.texture_pre = texture_list_item;
    item_temp.button.texture_locked = texture_list_item;
	
	item.push_back( item_temp );
	
	scrollbar.scroll_height = content_height;
	scrollbar.button_middle_offset = 0;
	scrollbar.scroll_amount = 0;
	offset = 0;
	scroll = 0;
}

void LDEgui_list::erase()
{
	item.erase( item.begin(), item.end() );

	changed = 0;
	
	focus = 0;
	test_coi = 0;
	active = 0;
	
	offset = 0;
	
	shift = 0;
	
	selected = 0;
	
	scroll = 0;
	
	coi = 0;
	
	content_height = start_up + start_down;
	
	click = 0;
	dbclick = 0;
}

void LDEgui_list::draw( vec2i cursor, LDEfloat frametime )
{
	click = 0;
	dbclick = 0;
	active = 0;
	changed = 0;
	
	coi = cursor.x >= x && cursor.x <= x + size.x && cursor.y >= y && cursor.y <= y+size.y;
	
	if ( focus )
	for ( LDEuint i = 0; i < input.size(); ++i )
	{
		if ( input[i].key_down )
			shift = input[i].lshift;
		
		if ( !input[i].key_down )
			shift = input[i].lshift;

		if ( input[i].down )
		{
			select( selected + 1, 0 );
			
			if ( selected * item_height + scroll > (size.y - (item_height + start_up + start_down)) )
				scroll = -((selected * item_height) - (size.y - (item_height + start_up + start_down)));
		}
	
		if ( input[i].up )
		{
			select( selected - 1, 0 );
			
			if ( selected * item_height + scroll < 0 )
				scroll = -(selected * item_height);
		}
	}

	if ( test_coi )
	{
		LDEfloat scroll_y = 0;
		
		for ( LDEuint i = 0; i < mouse.size(); ++i )
		{
			if ( mouse[i].left && mouse[i].down )
			{
				if ( !coi )
				{
					focus = 0;
				}
			}
			
			if ( mouse[i].scroll_y != 0 )
				scroll_y += mouse[i].scroll_y;
			
			
			if ( mouse[i].swipe_y != 0 )
			{
				if ( mouse[i].swipe_y == -1 )
					scrollbar.setPercent( 0 );
				else
					scrollbar.setPercent( 1 );
			
				if ( scrollbar.changed )
					scroll = -scrollbar.scroll_amount;
			}
		}
		
		if ( scroll_y != 0 )
		{
			LDEfloat percent_y = scrollbar.percent + (scroll_y / 100);
			
			if ( percent_y > 1 )
				percent_y = 1;
			else if ( percent_y < 0 )
				percent_y = 0;
			
			scrollbar.setPercent( percent_y );
			
			if ( scrollbar.changed )
				scroll = -scrollbar.scroll_amount;
		}
	}
	
	glBindTexture(GL_TEXTURE_2D, texture_list->id);
	LDEcustomrectp( texture_list->size, vec4i( x, y, size.x, size.y ), vec4i( uv_left, uv_up, uv_right, uv_down ) );

	glEnable( GL_SCISSOR_TEST );
	glScissor( x, app_size.y - (y+size.y), size.x - scrollbar.size.x, size.y );

	if ( scroll )
		offset = -scroll / item_height;
	else
		offset = 0;
	
	LDEint num = (size.y / item_height) + offset + 1;
	
	if ( num > item.size() )
		num = item.size();
	
	LDEuint selected_temp = selected;
	for ( LDEuint i = offset; i < num; ++i )
	{
		item[i].button.test_coi = test_coi;
		item[i].button.mouse = mouse;
		item[i].button.x = x + start_left;
		item[i].button.y = y + scroll + (i * item[i].button.size.y) + start_up;
		
		item[i].button.size.x = size.x - (start_left + start_right) - scrollbar.size.x - 2;
		item[i].button.draw( cursor, frametime );
		
		if ( coi )
		{
			if ( item[i].button.click )
			{
				if ( shift )
				{
					if ( selected_temp < i )
					{
						for ( LDEuint l = selected_temp; l <= i; ++l )
						{
							select( l, 1 );
						}
					}
					else
					{
						for ( LDEuint l = i; l <= selected_temp; ++l )
						{
							select( l, 1 );
						}
					}
				}
				else
					select( i, 0 );
				
				click = 1;
				changed = 1;
			}
		
			if (item[i].button.pressed )
				active = 1;
			
			if ( item[i].button.dbclick )
				dbclick = 1;
		}
	}
	
	glDisable( GL_SCISSOR_TEST );
	
	scrollbar.mouse = mouse;
	scrollbar.x = x + size.x - scrollbar.size.x - 1;
	scrollbar.y = y + 1;
	
	scrollbar.size.y = size.y - 2;
	
	scrollbar.test_coi = test_coi;
	scrollbar.draw( cursor, frametime );
	
	if ( scrollbar.changed )
	{
		scroll = -scrollbar.scroll_amount;
	}
	
	if ( scrollbar.active )
		active = 1;
}