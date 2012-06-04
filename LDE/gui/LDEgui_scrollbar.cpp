/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Graphical User Interface : elements
 *  // Scrollbar
\********************************************************************/

#include "LDEgui_scrollbar.h"

LDEgui_scrollbar::LDEgui_scrollbar()
{
	size = vec2i( 16, 50 );
	
	test_coi = 0;
	active = 0;
	
	side = 0;
	
	x = y = 0;
	
	old_size_y = 0;
	
	changed = 0;
	
	button_up.size = vec2i( 16, 16 );
	button_down.size = vec2i( 16, 16 );
	button_middle.size = vec2i( 16, 32 );
	
	button_middle.uv_up = 12;
	button_middle.uv_down = 12;
	button_middle.uv_left = 4;
	button_middle.uv_right = 4;
	
	uv_left = 0;
	uv_up = 0;
	uv_right = 0;
	uv_down = 0;
	
	scroll_height = 0;
	scroll_amount = 0;
	button_middle_offset = 0;
	
	percent = 0;
}

LDEgui_scrollbar::~LDEgui_scrollbar()
{

}

void LDEgui_scrollbar::reset()
{
	scroll_amount = 0;
	scroll_height = 100;
	button_middle_offset = 0;
}

void LDEgui_scrollbar::setRightTextures()
{
	if ( side )
	{
		button_up.texture_rel = texture_scrollbar_h_button_up;
		button_up.texture_coi = texture_scrollbar_h_button_up_hover;
		button_up.texture_pre = texture_scrollbar_h_button_up_pressed;
		button_up.texture_locked = texture_scrollbar_h_button_up;
		
		button_down.texture_rel = texture_scrollbar_h_button_down;
		button_down.texture_coi = texture_scrollbar_h_button_down_hover;
		button_down.texture_pre = texture_scrollbar_h_button_down_pressed;
		button_down.texture_locked = texture_scrollbar_h_button_down;

		button_middle.texture_rel = texture_scrollbar_h_button_middle;
		button_middle.texture_coi = texture_scrollbar_h_button_middle_hover;
		button_middle.texture_pre = texture_scrollbar_h_button_middle_pressed;
		button_middle.texture_locked = texture_scrollbar_h_button_middle_pressed;
		
		size.y = button_up.size.y;
		
		uv_left = 10;
		uv_up = 0;
		uv_right = 10;
		uv_down = 0;
		
		button_up.size = vec2i( 16, 16 );
		button_down.size = vec2i( 16, 16 );
		button_middle.size = vec2i( 32, 16 );
		
		button_middle.uv_up = 4;
		button_middle.uv_down = 4;
		button_middle.uv_left = 12;
		button_middle.uv_right = 12;
		
		old_size_y = size.x;
	}
	else
	{
		button_up.texture_rel = texture_scrollbar_button_up;
		button_up.texture_coi = texture_scrollbar_button_up_hover;
		button_up.texture_pre = texture_scrollbar_button_up_pressed;
		button_up.texture_locked = texture_scrollbar_button_up;
		
		button_down.texture_rel = texture_scrollbar_button_down;
		button_down.texture_coi = texture_scrollbar_button_down_hover;
		button_down.texture_pre = texture_scrollbar_button_down_pressed;
		button_down.texture_locked = texture_scrollbar_button_down;

		button_middle.texture_rel = texture_scrollbar_button_middle;
		button_middle.texture_coi = texture_scrollbar_button_middle_hover;
		button_middle.texture_pre = texture_scrollbar_button_middle_pressed;
		button_middle.texture_locked = texture_scrollbar_button_middle_pressed;
		
		size.x = button_up.size.x;
		
		uv_left = 0;
		uv_up = 10;
		uv_right = 0;
		uv_down = 10;
		
		button_up.size = vec2i( 16, 16 );
		button_down.size = vec2i( 16, 16 );
		button_middle.size = vec2i( 16, 32 );
		
		button_middle.uv_up = 12;
		button_middle.uv_down = 12;
		button_middle.uv_left = 4;
		button_middle.uv_right = 4;
		
		old_size_y = size.y;
	}
	
	button_middle.reset();
}

void LDEgui_scrollbar::setSide( bool side_ )
{
	side = side_;
	setRightTextures();
}

void LDEgui_scrollbar::setPercent( LDEfloat value )
{
	if ( value >= 0 && value <= 1 && value != percent )
	{
		percent = value;
		
		if ( side )
		{
			LDEint height = size.x - button_up.size.x - button_down.size.x;
			button_middle_offset = percent * (height-button_middle.size.x);
			
			scroll_amount = percent * (scroll_height-size.x);
			
			if ( scroll_amount < 0 )
				scroll_amount = 0;
		}
		else
		{
			LDEint height = size.y - button_up.size.y - button_down.size.y;
			button_middle_offset = percent * (height-button_middle.size.y);
			
			scroll_amount = percent * (scroll_height-size.y);
            
			if ( scroll_amount < 0 )
				scroll_amount = 0;
		}
		
		changed = 1;
		
		button_middle.transp = 1;
	}
}

void LDEgui_scrollbar::setInnerHeight( LDEint new_height )
{
    scroll_height = new_height;
    
    button_middle_offset = 0;
}

void LDEgui_scrollbar::draw( vec2i cursor, LDEfloat frametime )
{
	changed = 0;
	active = 0;

	button_middle.mouse = mouse;
	button_middle.test_coi = test_coi;
	
	if ( side )
	{
		glBindTexture( GL_TEXTURE_2D, texture_scrollbar_h_middle->id );
		LDEcustomrectp( texture_scrollbar_h_middle->size, vec4i( x+button_up.size.x, y, size.x-button_up.size.y-button_down.size.y, size.y ), vec4i( uv_left, uv_up, uv_right, uv_down ) );

		button_up.x = x;
		button_up.y = y;
	
		button_down.x = x + size.x - button_down.size.x;
		button_down.y = y;
		
		LDEint height = size.x - button_up.size.x - button_down.size.x;
		
		if ( size.x != old_size_y )
		{
			button_middle_offset = percent * (height-button_middle.size.x);
			
			if ( button_middle_offset < 0 )
				button_middle_offset = 0;
			
			changed = 1;
			
			scroll_amount = percent * (scroll_height-size.x);
			
			if ( scroll_amount < 0 )
				scroll_amount = 0;
			
			old_size_y = size.x;
		}
		
		button_middle.x = x + button_up.size.x + button_middle_offset;
		button_middle.y = y;
		button_middle.size.x = size.x - (scroll_height-height);
		
		if ( button_middle.size.x < 32 )
			button_middle.size.x = 32;
		
		if ( button_middle.size.x < height )
		{
			button_middle.draw( cursor, frametime );
			
			if ( button_middle.pressed )
			{
				button_middle_offset = cursor.x - x - button_up.size.x - button_middle.pos_temp.x;
				
				if ( button_middle_offset < 0 )
					button_middle_offset = 0;
				
				if ( button_middle_offset > height-button_middle.size.x )
				{
					button_middle_offset = (LDEfloat)height-button_middle.size.x;
				}
				
				if ( height-button_middle.size.x )
					percent = (LDEfloat)button_middle_offset / (height-button_middle.size.x);
				else
					percent = 0;
				
				scroll_amount = percent * (scroll_height-size.x);
				
				changed = 1;
			}
		}
	}
	else
	{
		glBindTexture( GL_TEXTURE_2D, texture_scrollbar_middle->id );
		LDEcustomrectp( texture_scrollbar_middle->size, vec4i( x, y+button_up.size.y, size.x, size.y-button_up.size.y-button_down.size.y ), vec4i( uv_left, uv_up, uv_right, uv_down ) );

		button_up.x = x;
		button_up.y = y;

		button_down.x = x;
		button_down.y = y + size.y - button_down.size.y;

		LDEint height = size.y - button_up.size.y - button_down.size.y;

		if ( size.y != old_size_y )
		{
			button_middle_offset = percent * (height-button_middle.size.y);
			
			if ( button_middle_offset < 0 )
				button_middle_offset = 0;
			
			changed = 1;
			
			scroll_amount = percent * (scroll_height-size.y);
			
			if ( scroll_amount < 0 )
				scroll_amount = 0;
			
			old_size_y = size.y;
		}
		
		button_middle.x = x;
		button_middle.y = y + button_up.size.y + button_middle_offset;
		button_middle.size.y = size.y - (scroll_height-height);
		
		if ( button_middle.size.y < 32 )
			button_middle.size.y = 32;
		
		if ( button_middle.size.y < height )
		{
			button_middle.draw( cursor, frametime );
			
			if ( button_middle.pressed )
			{
				button_middle_offset = cursor.y - y - button_up.size.y - button_middle.pos_temp.y;
				
				if ( button_middle_offset < 0 )
					button_middle_offset = 0;
				
				if ( button_middle_offset > height-button_middle.size.y )
				{
					button_middle_offset = (LDEfloat)height-button_middle.size.y;
				}
				
				if ( height-button_middle.size.y )
					percent = (LDEfloat)button_middle_offset / (height-button_middle.size.y);
				else
					percent = 0;
				
				scroll_amount = percent * (scroll_height-size.y);
				
				changed = 1;
			}
		}
	}
	
	button_up.mouse = mouse;
	button_up.test_coi = test_coi;
	button_up.draw( cursor, frametime );
	
	button_down.mouse = mouse;
	button_down.test_coi = test_coi;
	button_down.draw( cursor, frametime );
	
	if ( button_down.click )
	{
		LDEfloat new_percent = percent+0.01;
		
		if ( new_percent > 1 )
			new_percent = 1;
		
		setPercent( new_percent );
	}
	
	if ( button_up.click )
	{
		LDEfloat new_percent = percent-0.01;
		
		if ( new_percent < 0 )
			new_percent = 0;
		
		setPercent( new_percent );
	}
	
	if ( button_up.pressed || button_down.pressed || button_middle.pressed )
		active = 1;
	
	//button_middle.font->pos.x = x+20;
	//button_middle.font->pos.y = y+20;
	//button_middle.font->setText( "percent "+LDEnts(percent) );
	//button_middle.font->draw();
}