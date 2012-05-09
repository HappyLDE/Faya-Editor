/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Graphical User Interface : base (every stuff has a base)
\********************************************************************/

#include "LDEgui_window.h"

LDEgui_window::LDEgui_window()
{
	min_size = vec2i( 100, 20 );
	
	show_close_button = 1;
	
    focus = 0;
    on_top = 0;
    clicked_away = 0;
    wait = 0;
    coi = 0;
	
	button_close_side = 0;

	title_scissor_left = 1,
	title_scissor_right = 1;
	
	closed = 0;
	
    move = 0;
	can_move = 1;
	can_resize = 1;
	
    bringOnTop = 0;

    // window default UVs
    uv_left = 0,			// left
	uv_up_left = 0,			// upper left
	uv_down_left = 0,		// down left
	uv_right = 0,			// right
	uv_up_right = 0,		// upper right
	uv_down_right = 0,		// down right
	uv_up = 0,				// up
	uv_down = 0;			// down

	// where the window starts (excluding shadow)
	start_up     = 0,    // pixels
    start_down   = 0,
    start_left   = 0,
    start_right  = 0;

    // Là où les éléments (boutons etc) commencent à être affichés dans la fenêtre
    inner_start_up     = 0,    // pixels
    inner_start_down   = 0,
    inner_start_left   = 0,
    inner_start_right  = 0;

    button_resize.texture_type = 1;
	
	draw_design = 1;
}

LDEgui_window::~LDEgui_window()
{

}

void LDEgui_window::draw( vec2i cursor, LDEfloat frametime )
{
	if ( !closed )
	{	
		if ( draw_design )
		{
			// upper_left
			LDErectp( texture->size,  vec4i( 0, 0, uv_up_left, uv_up ),
											vec4i( pos.x - start_left, pos.y - start_up, uv_up_left, uv_up ) );
			// up uv_up_left, 0, uv_up_right, uv_up
			LDErectp( texture->size,  vec4i( uv_up_left, 0, 0, uv_up ),
					 vec4i( pos.x + uv_up_left - start_left, pos.y - start_up, (size.x - (uv_up_left + uv_up_right)) + start_left + start_right, uv_up ) );

			// upper_right
			LDErectp( texture->size,  vec4i( texture->size.x - uv_up_right, 0, uv_up_right, uv_up ),
											vec4i( (pos.x + size.x - uv_up_right) + start_right, pos.y - start_up, uv_up_right, uv_up ) );

			// left
			LDErectp( texture->size,  vec4i( 0, uv_up, uv_left, texture->size.y - (uv_up + uv_down_left)  ),
											vec4i( pos.x - start_left, (pos.y + uv_up) - start_up, uv_left, (size.y - (uv_up + uv_down_left)) + start_down + start_up ) );

			// right
			LDErectp( texture->size,  vec4i( texture->size.x - uv_right, uv_up, uv_right, texture->size.y - (uv_up + uv_down_right)  ),
											vec4i( (pos.x + size.x - uv_right) + start_right, (pos.y + uv_up) - start_up, uv_left, (size.y - (uv_up + uv_down_right)) + start_down + start_up ) );

			// down
			LDErectp( texture->size,  vec4i( uv_down_left, texture->size.y - uv_down, texture->size.x - ( uv_down_left + uv_down_right ), uv_down ),
											vec4i( (pos.x + uv_down_left) - start_left, (pos.y + size.y - uv_down) + start_down, (size.x - ( uv_down_left + uv_down_right )) + start_left + start_right, uv_down ) );

			// lower_left
			LDErectp( texture->size,  vec4i( 0, texture->size.y - uv_down_left, uv_down_left, uv_down_left ),
											vec4i( pos.x - start_left, (pos.y + size.y - uv_down_left) + start_down, uv_down_left, uv_down_left ) );

			// lower_right
			LDErectp( texture->size,  vec4i( texture->size.x - uv_down_right, texture->size.y - uv_down_right, uv_down_right, uv_down_right ),
											vec4i( (pos.x + size.x - uv_down_right) + start_right, (pos.y + size.y - uv_down_right) + start_down, uv_down_right, uv_down_right ) );

			// middle
			LDErectp( texture->size,  vec4i( uv_left, uv_up, texture->size.x - ( uv_left + uv_right ), texture->size.y - ( uv_up + uv_down_right ) ),
											vec4i( (pos.x + uv_left) - start_left, (pos.y + uv_up) - start_up, (size.x - ( uv_left + uv_right )) + start_left + start_right, (size.y - (uv_up + uv_down)) + start_down + start_up ) );

			glEnable(GL_SCISSOR_TEST);
			glScissor( pos.x + title_scissor_left, app_size.y - (pos.y+20), size.x - (title_scissor_left+title_scissor_right), 20 );
			
			font_title->setText( title );
			font_title->setPos( pos.x + title_pos.x, pos.y + title_pos.y );
			font_title->draw();
		
			glDisable(GL_SCISSOR_TEST);
			
			if ( show_close_button )
			{
				if ( button_close_side )
					button_close.x = (pos.x + size.x) - button_close.size.x - button_close_pos.x;
				else
					button_close.x = pos.x + button_close_pos.x;
				
				button_close.y = pos.y + button_close_pos.y;
				button_close.test_coi = focus;
				button_close.mouse = mouse;
				button_close.draw( cursor, frametime );
			
				if ( button_close.pressed )
					move = 0;
			
				if ( button_close.click )
					close();
			}
		}
		
		elements.app_size = app_size;
		elements.test_coi = focus;
		elements.draw( pos.x + (inner_start_left - start_left), pos.y + (inner_start_up - start_up), cursor, frametime );
		can_move = !elements.active;
		
		if ( draw_design && can_resize )
		{
			button_resize.x = (pos.x + size.x) - (button_resize.size.x + button_resize_pos.x);
			button_resize.y = (pos.y + size.y) - (button_resize.size.y + button_resize_pos.y);
			button_resize.test_coi = focus;
			button_resize.mouse = mouse;
			button_resize.draw( cursor, frametime );
			
			// Resize window if resize button pressed
			if ( button_resize.pressed )
			{
				size.x = (cursor.x - pos.x) + (button_resize.size.x - button_resize.pos_temp.x);
				size.y = (cursor.y - pos.y) + ((button_resize.size.y - button_resize.pos_temp.y) + button_resize_pos.y);
				
				if ( size.x < min_size.x ) size.x = min_size.x;
				if ( size.y < min_size.y ) size.y = min_size.y;
			}
		}
		
		cursor_inside.x = cursor.x - pos.x - 1;
		cursor_inside.y = cursor.y - (pos.y + start_up);
	}
}

void LDEgui_window::getOnTop()
{
    bringOnTop = 1;
}

void LDEgui_window::open()
{
	closed = 0;
	bringOnTop = 1;
}

void LDEgui_window::close()
{
	closed = 1;
	
	elements.reset();
	
	button_resize.click = 0;
	button_close.click = 0;
}

bool LDEgui_window::cursorOnIt( vec2i cursor )
{
	coi = cursor.x > pos.x && cursor.x < pos.x+size.x && cursor.y > pos.y && cursor.y < pos.y+size.y;
	
    return coi;
}
