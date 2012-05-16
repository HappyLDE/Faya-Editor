//
//  transf_tool.m
//  Faya Editor
//
//  Created by Dorin Grigore on 15/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "transf_tool.h"

LDEtransf_tool::LDEtransf_tool()
{
    changed = 0;
    test_coi = 0;
    
    hover_arrow_right = 0,
    hover_arrow_bottom = 0,
    hover_circle = 0,
    hover_square_right = 0,
    hover_square_bottom = 0,
    hover_rotate = 0;
    
    mouse_down = 0;
    
    wait = 0;
    
    rot = 0;
    
    click_offset_angle = 0;
    
    init_angle = 0;
}

LDEtransf_tool::~LDEtransf_tool()
{
    
}

void LDEtransf_tool::draw( vec2i my_pos )
{
    if ( hover_arrow_right )
        pos.x = cursor.x - click_offset.x;
    else if ( hover_arrow_bottom )
        pos.y = cursor.y - click_offset.y;
    else if ( hover_circle )
        pos = vec2i( cursor.x - click_offset.x, cursor.y - click_offset.y );
    else
        pos = my_pos;
    
    if ( hover_rotate )
        rot = LDEangle2i( pos, cursor ) - click_offset_angle;
    
    changed = 0;
    
    for ( LDEuint i = 0; i < mouse.size(); ++i )
    {
        if ( mouse[i].left && mouse[i].down )
        {
            mouse_down = 1;
        }
    }
    
    glBindTexture(GL_TEXTURE_2D, image->id);

    glPushMatrix();
    glTranslatef( pos.x, pos.y, 0);
    
    glRotatef( rot, 0, 0, 1 );
    
    LDErectp(   image->size,
                vec4i(0,0,94,96),
                vec4i( -15, -14, 94,96) ); // -13, -14

    if ( test_coi )
    {
        // Down arrow
        if ( (cursor.x > pos.x - 3 && cursor.x < pos.x + 7 &&
              cursor.y > pos.y + 7 && cursor.y < pos.y + 49 && !wait) || hover_arrow_bottom )
        {
            LDErectp(   image->size,
                     vec4i( 109, 0, 19, 45),
                     vec4i( -11, 3, 19, 45) );
            
            if ( !wait )
                click_offset.y = cursor.y - pos.y;
            
            if ( mouse_down )
            {
                hover_arrow_bottom = 1;
                wait = 1;
            }
        }
        
        // Right arrow
        if ( (cursor.x > pos.x + 7 && cursor.x < pos.x + 51 &&
              cursor.y > pos.y - 4 && cursor.y < pos.y + 7 && !wait) || hover_arrow_right )
        {
            LDErectp(   image->size,
                     vec4i( 0, 107, 46, 21),
                     vec4i( 2, -11, 46, 21) );
            
            if ( !wait )
                click_offset.x = cursor.x - pos.x;
            
            if ( mouse_down )
            {
                hover_arrow_right = 1;
                wait = 1;
            }
        }
        
        // Circle
        if ( (cursor.x > pos.x - 5 && cursor.x < pos.x + 8 &&
              cursor.y > pos.y - 6 && cursor.y < pos.y + 8 && !wait) || hover_circle )
        {
            LDErectp(   image->size,
                     vec4i( 111, 45, 23, 23),
                     vec4i( -9, -8, 23, 23) );
            
            if ( !wait )
                click_offset = vec2i( cursor.x - pos.x, cursor.y - pos.y );
            
            if ( mouse_down )
            {
                hover_circle = 1;
                wait = 1;
            }
        }
        
        // Right square (resize)
        if ( (cursor.x > pos.x + 50 && cursor.x < pos.x + 65 &&
              cursor.y > pos.y - 7 && cursor.y < pos.y + 9 && !wait) || hover_square_right )
        {
            LDErectp(   image->size,
                     vec4i( 46, 107, 21, 21),
                     vec4i( 47, -11, 21, 21) );
            
            if ( mouse_down )
            {
                hover_square_right = 1;
                wait = 1;
            }
        }
        
        // Bottom square (resize)
        if ( (cursor.x > pos.x - 5 && cursor.x < pos.x + 10 &&
              cursor.y > pos.y + 48 && cursor.y < pos.y + 65 && !wait) || hover_square_bottom )
        {
            LDErectp(   image->size,
                     vec4i( 46, 107, 21, 21),
                     vec4i( -8, 45, 21, 21) );
            
            if ( mouse_down )
            {
                hover_square_bottom = 1;
                wait = 1;
            }
        }
        
        // Arc (rotate)
        if ( (cursor.x > pos.x + 10 && cursor.x < pos.x + 30 &&
              cursor.y > pos.y + 10 && cursor.y < pos.y + 30 && !wait) || hover_rotate )
        {
            LDErectp(   image->size,
                     vec4i( 94, 96, 34, 32),
                     vec4i( 3, 3, 34, 32) );
            
            if ( !wait )
            {
                click_offset = vec2i( cursor.x - pos.x, cursor.y - pos.y );
                
                click_offset_angle = LDEangle2i( pos, cursor );
            }
            
            if ( mouse_down )
            {
                hover_rotate = 1;
                wait = 1;
            }
        }
    }
    
    glPopMatrix();
    
    if ( hover_rotate )
    {
        glDisable(GL_TEXTURE_2D);
        glLineWidth(1);
        glEnable(GL_LINE_STIPPLE);
        glBegin(GL_LINES);
        glVertex2i( pos.x, pos.y );
        glVertex2i( cursor.x, cursor.y);
        glEnd();
        glDisable(GL_LINE_STIPPLE);
        glEnable(GL_TEXTURE_2D);
    }
    
    for ( LDEuint i = 0; i < mouse.size(); ++i )
    {
        if ( !mouse[i].down )
        {
            hover_arrow_right = 0,
            hover_arrow_bottom = 0,
            hover_circle = 0,
            hover_square_right = 0,
            hover_square_bottom = 0,
            hover_rotate = 0;
            
            mouse_down = 0;
            
            wait = 0;
            
            rot = 0;
            
            click_offset.reset();
            click_offset_angle = 0;
            
            init_angle = 0;
        }
    }
}