/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Graphical User Interface : elements
 * // All the elements that the gui contains : button, check etc
\********************************************************************/

#include "LDEgui_elements.h"

LDEgui_elements::LDEgui_elements()
{
    button_uv_up = 0;
    button_uv_down = 0,
    button_uv_left = 0,
    button_uv_right = 0;

    test_coi = 0;
	active = 0;
}

LDEgui_elements::~LDEgui_elements()
{

}

void LDEgui_elements::addDrawable( LDEgui_drawable *arg )
{
	drawable.push_back( arg );
}

void LDEgui_elements::addText( LDEgui_text *arg )
{
	text.push_back( arg );
	
	LDEuint pointer = text.size()-1;
	
	text[pointer]->font = font_elements;
}

void LDEgui_elements::addList( LDEgui_list *arg )
{
	list.push_back( arg );
	
	LDEuint pointer = list.size()-1;
	
	list[pointer]->font = font_elements;
	list[pointer]->texture_list = texture_list;
	list[pointer]->texture_list_item = texture_list_item;
	list[pointer]->texture_list_item_selected = texture_list_item_selected;

	list[pointer]->scrollbar.texture_scrollbar_button_up = texture_scrollbar_button_up;
	list[pointer]->scrollbar.texture_scrollbar_button_up_hover = texture_scrollbar_button_up_hover;
	list[pointer]->scrollbar.texture_scrollbar_button_up_pressed = texture_scrollbar_button_up_pressed;
	list[pointer]->scrollbar.texture_scrollbar_button_up = texture_scrollbar_button_up;
	
	list[pointer]->scrollbar.texture_scrollbar_button_down = texture_scrollbar_button_down;
	list[pointer]->scrollbar.texture_scrollbar_button_down_hover = texture_scrollbar_button_down_hover;
	list[pointer]->scrollbar.texture_scrollbar_button_down_pressed = texture_scrollbar_button_down_pressed;
	list[pointer]->scrollbar.texture_scrollbar_button_down = texture_scrollbar_button_down;
	
	list[pointer]->scrollbar.texture_scrollbar_middle = texture_scrollbar_middle;
	
	list[pointer]->scrollbar.texture_scrollbar_button_middle = texture_scrollbar_button_middle;
	list[pointer]->scrollbar.texture_scrollbar_button_middle_hover = texture_scrollbar_button_middle_hover;
	list[pointer]->scrollbar.texture_scrollbar_button_middle_pressed = texture_scrollbar_button_middle_pressed;
	list[pointer]->scrollbar.texture_scrollbar_button_middle_pressed = texture_scrollbar_button_middle_pressed;
	
	//h
	list[pointer]->scrollbar.texture_scrollbar_h_button_up = texture_scrollbar_h_button_up;
	list[pointer]->scrollbar.texture_scrollbar_h_button_up_hover = texture_scrollbar_h_button_up_hover;
	list[pointer]->scrollbar.texture_scrollbar_h_button_up_pressed = texture_scrollbar_h_button_up_pressed;
	list[pointer]->scrollbar.texture_scrollbar_h_button_up = texture_scrollbar_h_button_up;
	
	list[pointer]->scrollbar.texture_scrollbar_h_button_down = texture_scrollbar_h_button_down;
	list[pointer]->scrollbar.texture_scrollbar_h_button_down_hover = texture_scrollbar_h_button_down_hover;
	list[pointer]->scrollbar.texture_scrollbar_h_button_down_pressed = texture_scrollbar_h_button_down_pressed;
	list[pointer]->scrollbar.texture_scrollbar_h_button_down = texture_scrollbar_h_button_down;
	
	list[pointer]->scrollbar.texture_scrollbar_h_middle = texture_scrollbar_h_middle;
	
	list[pointer]->scrollbar.texture_scrollbar_h_button_middle = texture_scrollbar_h_button_middle;
	list[pointer]->scrollbar.texture_scrollbar_h_button_middle_hover = texture_scrollbar_h_button_middle_hover;
	list[pointer]->scrollbar.texture_scrollbar_h_button_middle_pressed = texture_scrollbar_h_button_middle_pressed;
	list[pointer]->scrollbar.texture_scrollbar_h_button_middle_pressed = texture_scrollbar_h_button_middle_pressed;
	
	list[pointer]->scrollbar.button_middle.font = font_elements;
	
	list[pointer]->scrollbar.setRightTextures();
}

void LDEgui_elements::addButton( LDEgui_button *arg )
{
    button.push_back( arg );

	LDEuint pointer = button.size()-1;
	
    button[pointer]->font = font_elements;

    button[pointer]->texture_rel = texture_button_rel;
    button[pointer]->texture_coi = texture_button_coi;
    button[pointer]->texture_pre = texture_button_pre;
    button[pointer]->texture_locked = texture_button_locked;

    /// Pass texture adresses (JUST ADRESSES)
    button[pointer]->uv_up = button_uv_up;
    button[pointer]->uv_down = button_uv_down;
    button[pointer]->uv_left = button_uv_left;
    button[pointer]->uv_right = button_uv_right;
}

void LDEgui_elements::addCombobox( LDEgui_combobox *arg )
{
	combobox.push_back( arg );
	
	LDEuint pointer = combobox.size()-1;
	
	combobox[pointer]->button.font = font_elements;
	combobox[pointer]->button.texture_rel = texture_combobox;
	combobox[pointer]->button.texture_coi = texture_combobox_hover;
    combobox[pointer]->button.texture_pre = texture_combobox_pressed;
	combobox[pointer]->button.name = "?";
	
	combobox[pointer]->font_item = font_elements;
	combobox[pointer]->texture_item = texture_button_rel;
	combobox[pointer]->texture_item_hover = texture_button_coi;
    combobox[pointer]->texture_item_pressed = texture_button_pre;
	
	combobox[pointer]->size = vec2i( 80, 16 );

	combobox[pointer]->button.uv_up = 8;
    combobox[pointer]->button.uv_down = 8;
    combobox[pointer]->button.uv_left = 9;
    combobox[pointer]->button.uv_right = 14;

	combobox[pointer]->menu_item = menu_item;
}

void LDEgui_elements::addEditbox( LDEgui_editbox *arg )
{
	editbox.push_back( arg );
	
	LDEuint pointer = editbox.size()-1;
	
	editbox[pointer]->button.font = font_elements;
	editbox[pointer]->button.texture_rel = texture_editbox;
	
	editbox[pointer]->button.texture_coi = texture_editbox_hover;
    editbox[pointer]->button.texture_pre = texture_editbox_active;
    editbox[pointer]->button.texture_locked = texture_button_locked;
	
	editbox[pointer]->texture_editbox = texture_editbox;
	editbox[pointer]->texture_editbox_hover = texture_editbox_hover;
	editbox[pointer]->texture_editbox_active = texture_editbox_active;
	
	editbox[pointer]->button.uv_up = 8;
    editbox[pointer]->button.uv_down = 8;
    editbox[pointer]->button.uv_left = 8;
    editbox[pointer]->button.uv_right = 8;
	
	editbox[pointer]->input = input;
}

void LDEgui_elements::addMenu( LDEgui_menu *arg )
{
    menu.push_back( arg );

	LDEuint pointer = menu.size()-1;
	
    menu[pointer]->font_elements = font_elements;

    menu[pointer]->texture_button_rel = texture_button_rel;
    menu[pointer]->texture_button_coi = texture_button_coi;
    menu[pointer]->texture_button_pre = texture_button_pre;
    menu[pointer]->texture_button_locked = texture_button_locked;

    menu[pointer]->texture_menu_button_rel = texture_menu_button_rel;
    menu[pointer]->texture_menu_button_coi = texture_menu_button_coi;
    menu[pointer]->texture_menu_button_pre = texture_menu_button_pre;
    menu[pointer]->texture_menu_button_locked = texture_menu_button_locked;

    /// Pass texture adresses (JUST ADRESSES)
    menu[pointer]->button_uv_up = button_uv_up;
    menu[pointer]->button_uv_down = button_uv_down;
    menu[pointer]->button_uv_left = button_uv_left;
    menu[pointer]->button_uv_right = button_uv_right;

    menu[pointer]->menu_item = menu_item;
}

void LDEgui_elements::addScrollbar( LDEgui_scrollbar *arg )
{
	scrollbar.push_back( arg );
	
	LDEuint pointer = scrollbar.size()-1;
	
	scrollbar[pointer]->texture_scrollbar_button_up = texture_scrollbar_button_up;
	scrollbar[pointer]->texture_scrollbar_button_up_hover = texture_scrollbar_button_up_hover;
	scrollbar[pointer]->texture_scrollbar_button_up_pressed = texture_scrollbar_button_up_pressed;
	scrollbar[pointer]->texture_scrollbar_button_up = texture_scrollbar_button_up;
	
	scrollbar[pointer]->texture_scrollbar_button_down = texture_scrollbar_button_down;
	scrollbar[pointer]->texture_scrollbar_button_down_hover = texture_scrollbar_button_down_hover;
	scrollbar[pointer]->texture_scrollbar_button_down_pressed = texture_scrollbar_button_down_pressed;
	scrollbar[pointer]->texture_scrollbar_button_down = texture_scrollbar_button_down;
	
	scrollbar[pointer]->texture_scrollbar_middle = texture_scrollbar_middle;
	
	scrollbar[pointer]->texture_scrollbar_button_middle = texture_scrollbar_button_middle;
	scrollbar[pointer]->texture_scrollbar_button_middle_hover = texture_scrollbar_button_middle_hover;
	scrollbar[pointer]->texture_scrollbar_button_middle_pressed = texture_scrollbar_button_middle_pressed;
	scrollbar[pointer]->texture_scrollbar_button_middle_pressed = texture_scrollbar_button_middle_pressed;
	
	//h
	scrollbar[pointer]->texture_scrollbar_h_button_up = texture_scrollbar_h_button_up;
	scrollbar[pointer]->texture_scrollbar_h_button_up_hover = texture_scrollbar_h_button_up_hover;
	scrollbar[pointer]->texture_scrollbar_h_button_up_pressed = texture_scrollbar_h_button_up_pressed;
	scrollbar[pointer]->texture_scrollbar_h_button_up = texture_scrollbar_h_button_up;
	
	scrollbar[pointer]->texture_scrollbar_h_button_down = texture_scrollbar_h_button_down;
	scrollbar[pointer]->texture_scrollbar_h_button_down_hover = texture_scrollbar_h_button_down_hover;
	scrollbar[pointer]->texture_scrollbar_h_button_down_pressed = texture_scrollbar_h_button_down_pressed;
	scrollbar[pointer]->texture_scrollbar_h_button_down = texture_scrollbar_h_button_down;
	
	scrollbar[pointer]->texture_scrollbar_h_middle = texture_scrollbar_h_middle;
	
	scrollbar[pointer]->texture_scrollbar_h_button_middle = texture_scrollbar_h_button_middle;
	scrollbar[pointer]->texture_scrollbar_h_button_middle_hover = texture_scrollbar_h_button_middle_hover;
	scrollbar[pointer]->texture_scrollbar_h_button_middle_pressed = texture_scrollbar_h_button_middle_pressed;
	scrollbar[pointer]->texture_scrollbar_h_button_middle_pressed = texture_scrollbar_h_button_middle_pressed;
	
	scrollbar[pointer]->button_middle.font = font_elements;
	
	scrollbar[pointer]->setRightTextures();
}

void LDEgui_elements::reset()
{
	active = 0;
	
	for ( LDEuint i = 0; i < button.size(); ++i )
    {
        button[i]->reset();
    }
}

void LDEgui_elements::draw(  LDEint x, LDEint y, vec2i cursor, LDEfloat frametime )
{
	active = 0;
	
	for ( LDEuint i = 0; i < drawable.size(); ++i )
    {
        drawable[i]->x = x;
        drawable[i]->y = y;
		drawable[i]->test_coi = test_coi;
        drawable[i]->draw( cursor, frametime );
    }
	
	for ( LDEuint i = 0; i < text.size(); ++i )
    {
        text[i]->draw( vec2i(x, y) );
    }
	
    for ( LDEuint i = 0; i < menu.size(); ++i )
    {
        menu[i]->pos.x = x;
        menu[i]->pos.y = y;
		menu[i]->mouse = mouse;
        menu[i]->draw( cursor, frametime, test_coi );
    }
	
	for ( LDEuint i = 0; i < list.size(); ++i )
    {
        list[i]->x = x + list[i]->pos.x;
        list[i]->y = y + list[i]->pos.y;
        list[i]->test_coi = test_coi;
		list[i]->app_size = app_size;
		list[i]->input = input;
		list[i]->mouse = mouse;
        list[i]->draw( cursor, frametime );
		
		if ( list[i]->active )
			active = 1;
    }
	
	for ( LDEuint i = 0; i < editbox.size(); ++i )
    {
		editbox[i]->button.pos = editbox[i]->pos;
        editbox[i]->button.x = x + editbox[i]->button.pos.x;
        editbox[i]->button.y = y + editbox[i]->button.pos.y;
		editbox[i]->button.test_coi = test_coi;
        editbox[i]->app_size = app_size;
		editbox[i]->input = input;
		editbox[i]->button.mouse = mouse;
        editbox[i]->draw( cursor, frametime );
		
		if ( editbox[i]->button.pressed )
			active = 1;
    }
	
	for ( LDEuint i = 0; i < combobox.size(); ++i )
    {
		combobox[i]->button.pos = combobox[i]->pos;
        combobox[i]->button.x = x + combobox[i]->button.pos.x;
        combobox[i]->button.y = y + combobox[i]->button.pos.y;
		combobox[i]->button.test_coi = test_coi;
		combobox[i]->button.mouse = mouse;
        combobox[i]->draw( cursor, frametime );
		
		if ( combobox[i]->button.pressed )
			active = 1;
    }
	
    for ( LDEuint i = 0; i < button.size(); ++i )
    {
        button[i]->x = x + button[i]->pos.x;
        button[i]->y = y + button[i]->pos.y;
        button[i]->test_coi = test_coi;
		button[i]->mouse = mouse;
        button[i]->draw( cursor, frametime );
		
		if ( button[i]->pressed )
			active = 1;
    }
	
	for ( LDEuint i = 0; i < scrollbar.size(); ++i )
    {
        scrollbar[i]->x = x + scrollbar[i]->pos.x;
        scrollbar[i]->y = y + scrollbar[i]->pos.y;
        scrollbar[i]->test_coi = test_coi;
		scrollbar[i]->mouse = mouse;
        scrollbar[i]->draw( cursor, frametime );
		
		if ( scrollbar[i]->active )
			active = 1;
    }
}
