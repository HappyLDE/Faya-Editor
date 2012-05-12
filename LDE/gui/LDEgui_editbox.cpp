/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Graphical User Interface : elements
 *  // Editbox
\********************************************************************/

#include "LDEgui_editbox.h"

LDEgui_editbox::LDEgui_editbox()
{
	size = vec2i( 40, 22 );
	focus = 0;
	cursor_toggle_time = 0;
	cursor_flag = 0;
	cursor_pos = 0;
	text_offset = 0;
}

LDEgui_editbox::~LDEgui_editbox()
{

}

void LDEgui_editbox::draw( vec2i cursor, LDEfloat frametime )
{
	//button.pos = pos;
	button.size = size;

	button.draw( cursor, frametime );
	
	button.font->pos.x = button.x + text_offset + 4;
	button.font->pos.y = button.y + 4;
	
	if ( button.click )
	{
		button.texture_rel = texture_editbox_active;
		button.texture_coi = texture_editbox_active;
		cursor_toggle_time = 0;
		cursor_flag = 1;
		focus = 1;
		button.font->setText( name );
		
		if ( button.font->size.x + text_offset > button.size.x )
			text_offset = -(button.font->size.x - button.size.x + 9);
		
		cursor_pos = button.font->size.x - text_offset;
	}
	
	if ( button.clicked_away )
	{
		focus = 0;
		button.texture_rel = texture_editbox;
		button.texture_coi = texture_editbox_hover;
	}
	
	glEnable(GL_SCISSOR_TEST);
	//LDEscissor( button.x + 3, button.y, button.size.x - 6, button.size.y );
    glScissor( button.x + 3, app_size.y - (button.y+button.size.y), button.size.x - 6, button.size.y );
	glColor3f(0, 0, 0);
	
    // If the editbox has FOCUS
	if ( focus )
	{
        // If keys on tkeyboard was pressed
		if ( input.size() )
		{
			for ( LDEuint i = 0; i < input.size(); ++i )
			{
				if ( input[i].backspace && input[i].key_down && name.size() )
				{
					name = name.substr( 0, name.size()-1 );
					
					if ( text_offset < 0 )
						 text_offset += 10;
					else
						text_offset = 0;
				}
				else if ( input[i].characters.size() && input[i].key_down )
					name += input[i].characters;
			}
			
			button.font->setText( name );
			
			if ( button.font->size.x + text_offset > button.size.x )
				text_offset = -(button.font->size.x - button.size.x + 9);
			
			cursor_pos = button.font->size.x - text_offset;
		}
		
        //
		cursor_toggle_time += 0.3 + frametime;
	
		if ( cursor_toggle_time > 10 )
		{
			cursor_toggle_time = 0;
		
			if ( cursor_flag )
				cursor_flag = 0;
			else
				cursor_flag = 1;
		}
	
		if ( cursor_flag )
		{
			glDisable(GL_TEXTURE_2D);
			glBegin(GL_LINES);
				glVertex2i( button.font->pos.x + cursor_pos + text_offset, button.y );
				glVertex2i( button.font->pos.x + cursor_pos + text_offset, button.y + button.size.y );
			glEnd();
			glEnable(GL_TEXTURE_2D);
		}
	}
	
	button.font->setText( name );
	button.font->draw();
	glDisable(GL_SCISSOR_TEST);
	
	
}