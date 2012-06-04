/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Graphical User Interface : elements
 *  // Button
\********************************************************************/

#include "LDEgui_button.h"

using namespace std;

LDEgui_button::LDEgui_button()
{
	x = 0, y = 0;	// position from LDEgui base.pos

	size.x = 20;
	size.y = 20;

	coi = 0,
	pressed = 0;
	click = 0;
	dbclick = 0;
	clicked_away = 0;
	transp = 0;
    
    coi_side = 0;

	get_pos_temp = 1;

	uv_left = 3,	// left
	uv_right = 3,	// right
	uv_up = 3,		// up
	uv_down = 3;	// down

	moveInfo = 0;
	moveInfoSide = 0;

	test_coi = 0;

	icon_angle = 0;

	text_side = 0;
	icon_side = 0;

	texture_type = 0;

	moveable_info = 0;

	locked = 0;

	scissor = 0;

    draw_icon = 0;
    
	text_color = vec3f( 1,1,1 );
	text_color_inactive = vec3f( 1,1,1 );
	
	dbclick_counter = -1;
}

LDEgui_button::~LDEgui_button()
{

}

void LDEgui_button::reset()
{
	coi = 0,
	pressed = 0;
	click = 0;
	dbclick = 0;
	clicked_away = 0;
	transp = 0;
	
	get_pos_temp = 1;
	
	test_coi = 0;
	
	dbclick_counter = -1;
}

void LDEgui_button::draw_button()
{
	LDEcustomrectp( texture_rel->size, vec4i( x, y, size.x, size.y ), vec4i( uv_left, uv_up, uv_right, uv_down ) );
}

void LDEgui_button::setText( string myname )
{
    name = myname;

    font->setText( name );

    if ( size.x < font->size.x + 10 )
         size.x = font->size.x + 10;
}

void LDEgui_button::lock()
{
	locked = 1;
	transp = 0;
	dbclick_counter = 0;
	click = 0;
	dbclick = 0;
}

void LDEgui_button::unlock()
{
	locked = 0;
	transp = 0;
	dbclick_counter = 0;
	click = 0;
	dbclick = 0;
}

void LDEgui_button::draw( vec2i cursor, LDEfloat frametime )
{
	click = 0;
	dbclick = 0;
	coi_side = 0;
    
    coi = cursor.x >= x && cursor.x <= x + size.x && cursor.y > y && cursor.y <= y+size.y;
    
    coi_side = cursor.y <= y + 2 + size.y / 2 ? 1 : 3;
    
    if ( cursor.y > y + size.y / 2 && cursor.y <= y + 3 + size.y / 2 )
        coi_side = 2;
    
	if ( test_coi && coi && !clicked_away )
    {
        if ( transp < 1 && !locked )
            transp += frametime * 4.5f;
    }
    else
    {
        if ( transp > 0 )
            transp -= frametime * 4.5f;
    }

	for ( LDEuint i = 0; i < mouse.size(); ++i )
	{
		if ( mouse[i].left && mouse[i].down )
		{
			if ( coi )
			{
				if ( test_coi )
				{
					pressed = 1;
					
					pos_temp.x = cursor.x - x;
					pos_temp.y = cursor.y - y;
				}
				
				clicked_away = 0;
			}
			else
			{
				clicked_away = 1;
			}

		}
	}
	
	glColor3f(1, 1, 1);
	
	glBindTexture(GL_TEXTURE_2D, texture_rel->id );
	
	// draw mesh
	if ( !texture_type )
		draw_button();
	else
		LDErectuv( 0,1,-1,1,-1,0,0,0, x, y, size.x, size.y+1 );

	if ( transp && !locked )
	{
		glColor4d(1,1,1,transp);
		glBindTexture(GL_TEXTURE_2D, texture_coi->id );
	
		if ( pressed )
		{
			glBindTexture(GL_TEXTURE_2D, texture_pre->id );
			transp = 1;
		}
	 
		// draw mesh
		if ( !texture_type )
			draw_button();
		else
			LDErectuv( 0,1,-1,1,-1,0,0,0, x, y, size.x, size.y+1 );
	}

	if ( scissor )
	{
		//glEnable(GL_SCISSOR_TEST);
		//LDEscissor( x , y , size.x /* - decrease_scissor.x */, size.y /* - decrease_scissor.y */ );
	}

    // an icon
    if ( draw_icon && texture_icon )
    {
        glColor3f(1,1,1);
        glBindTexture(GL_TEXTURE_2D, texture_icon->id);
        LDErect( x + icon_pos.x, y + icon_pos.y, texture_icon->size.x, texture_icon->size.y );
    }

    // text name
    if ( name.size() )
    {
        if ( locked )
            glColor3d(0.6,0.6,0.6);
        else
            glColor3d(text_color.x,text_color.y,text_color.z);

        // center text
        if ( text_side == 0 )
        {
            font->setText( name );
            font->setPos( LDEint(x + ((size.x / 2)) - (font->size.x / 2)) + text_pos.x, LDEint(y + ((size.y/2)-font->char_size/2)) + text_pos.y );
            font->draw();
        }
        // left side text
        else if ( text_side == 1 )
        {
            font->setText( name );
            font->setPos( x + text_pos.x, LDEint(y + ((size.y/2)-font->char_size/2)) + text_pos.y );
            font->draw();
        }
        // right side text
        else if ( text_side >= 2 )
        {
            font->setText( name );
            font->setPos( LDEint(x + size.x - font->size.x) + text_pos.x, LDEint(y + ( size.y / 2 - 3 )) + text_pos.y );
            font->draw();
        }
    }

	if ( scissor )
	{
		//glDisable(GL_SCISSOR_TEST);
	}

	glColor3d(1,1,1);

	if ( dbclick_counter > -1 )
		dbclick_counter += frametime;
	
	if ( dbclick_counter > 0.3 )
		dbclick_counter = -1;
	
	for ( LDEuint i = 0; i < mouse.size(); ++i )
	{
		if ( mouse[i].left && !mouse[i].down )
		{
			if ( coi && !clicked_away && test_coi )
			{				
				if ( dbclick_counter == -1 )
					dbclick_counter = 0;
				
				if ( dbclick_counter > 0 && dbclick_counter < 0.3 )
				{
					dbclick = 1;
					dbclick_counter = -1;
				}
				
				click = 1;
			}
			
			pressed = 0;
			clicked_away = 0;
		}
	}
	
	if ( locked )
	{
		click = 0;
		dbclick = 0;
	}
}
