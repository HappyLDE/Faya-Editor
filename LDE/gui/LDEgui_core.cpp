/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Scene Gamera
\********************************************************************/

#include "LDEgui_core.h"

LDEgui::LDEgui()
{
    /// window default UVs
	window_uv_up = 38,				// up
	window_uv_up_left = 28,			// upper left
	window_uv_up_right = 28,		// upper right
	
	window_uv_left = 30,			// left
	window_uv_right = 30,			// right
	
	window_uv_down = 25;			// down
	window_uv_down_left = 25,		// down left
	window_uv_down_right = 25,		// down right

	// where the window starts (excluding shadow)
	window_start_up     = 21,    // pixels
    window_start_down   = 20,
    window_start_left   = 22,
    window_start_right  = 22;

    window_inner_start_up     = 45,    // pixels
    window_inner_start_down   = 22,
    window_inner_start_left   = 22,
    window_inner_start_right  = 22;

	//window_title_pos = vec2i(0,10);
    window_button_resize_pos = vec2i( 0, 4 );
    window_button_close_pos = vec2i( 8, 5 );
	window_button_close_side = 0;
	
    /// Pannel UVs
    // window default UVs
    pannel_uv_left = 20,			// left
	pannel_uv_right = 20,			// right
	pannel_uv_up = 20,				// up
	pannel_uv_down = 20;			// down

	// where the window starts (excluding shadow)
	pannel_start_up     = 10,    // pixels
    pannel_start_down   = 10,
    pannel_start_left   = 10,
    pannel_start_right  = 10;

    button_uv_up = 8;
    button_uv_down = 8,
    button_uv_left = 8,
    button_uv_right = 8;

    unused = 1;
    focus_window = 0;
    focus_menu = 0;
    
    close_menu = 1;
}

LDEgui::~LDEgui()
{

}

void LDEgui::addWindow( LDEgui_window *arg )
{
    window.push_back( arg );
    //window_id.push_back( window_id.size() );

    window[window.size()-1]->texture = texture_window;
    window[window.size()-1]->texture_inactive = texture_window_inactive;

    // let's assign the default UVs for now
    window[window.size()-1]->uv_left = window_uv_left,			// left
	window[window.size()-1]->uv_up_left = window_uv_up_left,			// upper left
	window[window.size()-1]->uv_down_left = window_uv_down_left,		// down left
	window[window.size()-1]->uv_right = window_uv_right,			// right
	window[window.size()-1]->uv_up_right = window_uv_up_right,		// upper right
	window[window.size()-1]->uv_down_right = window_uv_down_right,		// down right
	window[window.size()-1]->uv_up = window_uv_up,				// up
	window[window.size()-1]->uv_down = window_uv_down;			// down

	// where the window starts (excluding shadow)
	window[window.size()-1]->start_up     = window_start_up,    // pixels
    window[window.size()-1]->start_down   = window_start_down,
    window[window.size()-1]->start_left   = window_start_left,
    window[window.size()-1]->start_right  = window_start_right;

    // where the window starts (excluding shadow)
	window[window.size()-1]->inner_start_up     = window_inner_start_up,    // pixels
    window[window.size()-1]->inner_start_down   = window_inner_start_down,
    window[window.size()-1]->inner_start_left   = window_inner_start_left,
    window[window.size()-1]->inner_start_right  = window_inner_start_right;

	window[window.size()-1]->button_close_side = window_button_close_side;
	
    window[window.size()-1]->title_pos = vec2i(30,1);

    window[window.size()-1]->font_title = font_window_title;

	window[window.size()-1]->elements.texture_list = texture_list;
	window[window.size()-1]->elements.texture_list_item = texture_list_item;
	window[window.size()-1]->elements.texture_list_item_selected = texture_list_item_selected;
	
	window[window.size()-1]->elements.texture_scrollbar_button_up = texture_scrollbar_button_up;
	window[window.size()-1]->elements.texture_scrollbar_button_up_hover = texture_scrollbar_button_up_hover;
	window[window.size()-1]->elements.texture_scrollbar_button_up_pressed = texture_scrollbar_button_up_pressed;
	
	window[window.size()-1]->elements.texture_scrollbar_button_down = texture_scrollbar_button_down;
	window[window.size()-1]->elements.texture_scrollbar_button_down_hover = texture_scrollbar_button_down_hover;
	window[window.size()-1]->elements.texture_scrollbar_button_down_pressed = texture_scrollbar_button_down_pressed;
	
	window[window.size()-1]->elements.texture_scrollbar_middle = texture_scrollbar_middle;
	
	window[window.size()-1]->elements.texture_scrollbar_button_middle = texture_scrollbar_button_middle;
	window[window.size()-1]->elements.texture_scrollbar_button_middle_hover = texture_scrollbar_button_middle_hover;
	window[window.size()-1]->elements.texture_scrollbar_button_middle_pressed = texture_scrollbar_button_middle_pressed;

	// h
	window[window.size()-1]->elements.texture_scrollbar_h_button_up = texture_scrollbar_h_button_up;
	window[window.size()-1]->elements.texture_scrollbar_h_button_up_hover = texture_scrollbar_h_button_up_hover;
	window[window.size()-1]->elements.texture_scrollbar_h_button_up_pressed = texture_scrollbar_h_button_up_pressed;
	
	window[window.size()-1]->elements.texture_scrollbar_h_button_down = texture_scrollbar_h_button_down;
	window[window.size()-1]->elements.texture_scrollbar_h_button_down_hover = texture_scrollbar_h_button_down_hover;
	window[window.size()-1]->elements.texture_scrollbar_h_button_down_pressed = texture_scrollbar_h_button_down_pressed;
	
	window[window.size()-1]->elements.texture_scrollbar_h_middle = texture_scrollbar_h_middle;
	
	window[window.size()-1]->elements.texture_scrollbar_h_button_middle = texture_scrollbar_h_button_middle;
	window[window.size()-1]->elements.texture_scrollbar_h_button_middle_hover = texture_scrollbar_h_button_middle_hover;
	window[window.size()-1]->elements.texture_scrollbar_h_button_middle_pressed = texture_scrollbar_h_button_middle_pressed;
	
	// Combobox
	window[window.size()-1]->elements.texture_combobox = texture_combobox;
	window[window.size()-1]->elements.texture_combobox_hover = texture_combobox_hover;
	window[window.size()-1]->elements.texture_combobox_pressed = texture_combobox_pressed;
	
    // Combobox
	window[window.size()-1]->elements.texture_checkbox = texture_checkbox;
	window[window.size()-1]->elements.texture_checkbox_hover = texture_checkbox_hover;
	window[window.size()-1]->elements.texture_checkbox_pressed = texture_checkbox_pressed;
    window[window.size()-1]->elements.texture_checkbox_checked = texture_checkbox_checked;
    
	// Editbox
	window[window.size()-1]->elements.texture_editbox = texture_editbox;
	window[window.size()-1]->elements.texture_editbox_hover = texture_editbox_hover;
	window[window.size()-1]->elements.texture_editbox_active = texture_editbox_active;

    /// Pass texture adresses (JUST ADRESSES)
    window[window.size()-1]->elements.texture_button_rel = texture_button_rel;
    window[window.size()-1]->elements.texture_button_coi = texture_button_coi;
    window[window.size()-1]->elements.texture_button_pre = texture_button_pre;
    window[window.size()-1]->elements.texture_button_locked = texture_button_locked;

    window[window.size()-1]->elements.font_elements = font_elements;

    /// Pass texture adresses (JUST ADRESSES)
    window[window.size()-1]->elements.button_uv_up = button_uv_up;
    window[window.size()-1]->elements.button_uv_down = button_uv_down;
    window[window.size()-1]->elements.button_uv_left = button_uv_left;
    window[window.size()-1]->elements.button_uv_right = button_uv_right;

    /// Resize button
    window[window.size()-1]->button_resize_pos = window_button_resize_pos;
	
    window[window.size()-1]->button_resize.size = vec2i(16,15);//texture_button_window_resize_rel->size;

    window[window.size()-1]->button_resize.texture_rel = texture_button_window_resize_rel;
    window[window.size()-1]->button_resize.texture_coi = texture_button_coi;
    window[window.size()-1]->button_resize.texture_pre = texture_button_pre;
    window[window.size()-1]->button_resize.texture_locked = texture_button_locked;

	// Close butotn
    window[window.size()-1]->button_close_pos = window_button_close_pos;
	window[window.size()-1]->button_close.texture_rel = texture_window_close;
	window[window.size()-1]->button_close.texture_coi = texture_window_close_hover;
	window[window.size()-1]->button_close.texture_pre = texture_window_close_pressed;
	
	window[window.size()-1]->button_close.size.x = texture_window_close->w;
	window[window.size()-1]->button_close.size.y = texture_window_close->h;
	
	window[window.size()-1]->elements.menu_item = &menu;
	
	window[window.size()-1]->app_size = app_size;
}

void LDEgui::addPannel( LDEgui_pannel *arg )
{
    pannel.push_back( arg );

    pannel[pannel.size()-1]->texture = texture_pannel;

    // let's assign the default UVs for now
    pannel[pannel.size()-1]->uv_left = pannel_uv_left,			// left
	pannel[pannel.size()-1]->uv_right = pannel_uv_right,			// right
	pannel[pannel.size()-1]->uv_up = pannel_uv_up,				// up
	pannel[pannel.size()-1]->uv_down = pannel_uv_down;			// down

	// where the pannel starts (excluding shadow)
	pannel[pannel.size()-1]->start_up     = pannel_start_up,    // pixels
    pannel[pannel.size()-1]->start_down   = pannel_start_down,
    pannel[pannel.size()-1]->start_left   = pannel_start_left,
    pannel[pannel.size()-1]->start_right  = pannel_start_right;

    /// Pass texture adresses (JUST ADRESSES)
    pannel[pannel.size()-1]->elements.texture_button_rel = texture_button_rel;
    pannel[pannel.size()-1]->elements.texture_button_coi = texture_button_coi;
    pannel[pannel.size()-1]->elements.texture_button_pre = texture_button_pre;
    pannel[pannel.size()-1]->elements.texture_button_locked = texture_button_locked;

    /// Pass texture adresses (JUST ADRESSES)
    pannel[pannel.size()-1]->elements.texture_menu_button_rel = texture_menu_button_rel;
    pannel[pannel.size()-1]->elements.texture_menu_button_coi = texture_menu_button_coi;
    pannel[pannel.size()-1]->elements.texture_menu_button_pre = texture_menu_button_pre;
    pannel[pannel.size()-1]->elements.texture_menu_button_locked = texture_menu_button_locked;

    // Combobox
	pannel[pannel.size()-1]->elements.texture_combobox = texture_combobox;
	pannel[pannel.size()-1]->elements.texture_combobox_hover = texture_combobox_hover;
	pannel[pannel.size()-1]->elements.texture_combobox_pressed = texture_combobox_pressed;
    
    pannel[pannel.size()-1]->elements.font_elements = font_elements;
	pannel[pannel.size()-1]->elements.input = input;
	
    /// Pass texture adresses (JUST ADRESSES)
    pannel[pannel.size()-1]->elements.button_uv_up = button_uv_up;
    pannel[pannel.size()-1]->elements.button_uv_down = button_uv_down;
    pannel[pannel.size()-1]->elements.button_uv_left = button_uv_left;
    pannel[pannel.size()-1]->elements.button_uv_right = button_uv_right;

    pannel[pannel.size()-1]->elements.menu_item = &menu;
	
	pannel[pannel.size()-1]->app_size = app_size;
}
