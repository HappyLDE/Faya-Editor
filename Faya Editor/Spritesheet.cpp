//
//  Spritesheet.cpp
//  Faya Editor
//
//  Created by Dorin Grigore on 28/04/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Spritesheet.h"

//// ITEM ///
Spritesheet_frame::Spritesheet_frame()
{
    
}

Spritesheet_frame::~Spritesheet_frame()
{
    
}

///////////// SPRITESHEET /////////////
Spritesheet::Spritesheet()
{
    test_coi = 0;
    used = 0;
    selected = -1;
    mouse_down = 0;
}

Spritesheet::~Spritesheet()
{
    frames.erase( frames.begin(), frames.end() );
}

void Spritesheet::draw()
{
    used = 0;
    
    glBindTexture(GL_TEXTURE_2D, image.id );
    
    for ( LDEuint s = 0; s < frames.size(); ++s )
    {
        LDErectp( image.size,
                 vec4i( frames[s].pos.x, frames[s].pos.y, frames[s].size.x, frames[s].size.y),
                 vec4i( frames[s].pos_window.x + frames[s].margin.x, frames[s].pos_window.y + frames[s].margin.y, frames[s].size_100.x, frames[s].size_100.y) );
    }
    
    glDisable(GL_TEXTURE_2D);
    
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1,0x0101);
    
    for ( LDEuint s = 0; s < frames.size(); ++s )
    {
        // Test coi
        if ( cursor_pos.x >= window_pos.x + frames[s].pos_window.x && cursor_pos.x <= window_pos.x + frames[s].pos_window.x + 100 &&
            cursor_pos.y >= window_pos.y + frames[s].pos_window.y && cursor_pos.y <= window_pos.y + frames[s].pos_window.y + 100 && test_coi )
        {
            glColor3f( 0, 1, 0 );
            used = 1;
            
            // If left clicked on that one
            for ( LDEuint i = 0; i < mouse.size(); ++i )
            {
                if ( mouse[i].left && mouse[i].down )
                {
                    selected = s;
                    mouse_down = 1;
                }
            }
        }
        else
            glColor4f( 1, 1, 1, 0.3 );
        
        LDErectw( frames[s].pos_window.x, frames[s].pos_window.y, 100, 100);
    }
    
    glDisable(GL_LINE_STIPPLE);
    
    glEnable(GL_TEXTURE_2D);
    
    // If left clicked on that one
    for ( LDEuint i = 0; i < mouse.size(); ++i )
    {
        if ( mouse[i].left && !mouse[i].down )
        {
            selected = -1;
            mouse_down = 0;
        }
    }
    
    mouse.erase( mouse.begin(), mouse.end() );
}