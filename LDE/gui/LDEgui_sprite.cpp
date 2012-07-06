//
//  LDEgui_sprite.m
//  Faya Editor
//
//  Created by Dorin Grigore on 6/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "LDEgui_sprite.h"

using namespace std;

LDEgui_sprite::LDEgui_sprite()
{
    texture_id = 0;
    x = y = 0;
    
    opacity = 1;
    
    size = vec2i( 50, 50 );
    
    borde_width = 0;
    
    clicked_away = 0;
}

LDEgui_sprite::~LDEgui_sprite()
{
    
}

void LDEgui_sprite::draw( vec2i cursor, LDEfloat frametime )
{
    click = 0;
    
    coi = cursor.x >= pos.x+x && cursor.x <= pos.x+x + size.x && cursor.y > pos.y+y && cursor.y <= pos.y+y+size.y;
    
    for ( LDEuint i = 0; i < mouse.size(); ++i )
	{
		if ( mouse[i].left && mouse[i].down )
		{
			if ( coi )
			{
				if ( test_coi )
				{
					pressed = 1;
					
					pos_temp.x = cursor.x - (pos.x+x);
					pos_temp.y = cursor.y - (pos.y+y);
				}
				
				clicked_away = 0;
			}
			else
			{
				clicked_away = 1;
			}
            
		}
        
        if ( mouse[i].left && !mouse[i].down )
		{
			if ( coi && !clicked_away && test_coi )
			{				
				click = 1;
			}
			
			pressed = 0;
			clicked_away = 0;
		}
	}
    
    glDisable(GL_TEXTURE_2D);
    
    if ( borde_width )
    {
        glColor3f(color_border.x, color_border.y, color_border.z);
        LDErect( pos.x+x-borde_width, pos.y+y, borde_width, size.y );
        LDErect( pos.x+x-borde_width, pos.y+y-borde_width, size.x+borde_width+borde_width, borde_width );
        LDErect( pos.x+x-borde_width, pos.y+y+size.y, size.x+borde_width+borde_width, borde_width );
        LDErect( pos.x+x+size.x, pos.y+y, borde_width, size.y );
    }
    
    if ( texture_id )
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_id);
    }
    
    glColor4f(color.x, color.y, color.z, opacity);
    
    LDErect( pos.x+x, pos.y+y, size.x, size.y );
    
    glColor3f(1,1,1);
    
    glEnable(GL_TEXTURE_2D);
}