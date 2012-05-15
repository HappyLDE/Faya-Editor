//
//  Sprite.cpp
//  Faya Editor
//
//  Created by Dorin Grigore on 2/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "SpriteBatchNode.h"

using namespace std;

Sprite::Sprite()
{
    rot = 0;
    opacity = 1;
    image_id = 0;
    selected = 0;
}

Sprite::~Sprite()
{
    
}

/////////// SPRITES ////////////
SpriteBatchNode::SpriteBatchNode()
{
    last_texture_id = 0;
    test_coi = 0;
    camera_zoom = 1;
    changed = 0;
    keep_select = 0;
}

SpriteBatchNode::~SpriteBatchNode()
{
    
}

void SpriteBatchNode::setPosition( vec2i pos )
{
    for ( LDEuint i = 0; i < sprites.size(); ++i )
    {
        if ( sprites[i].selected )
        {
            sprites[i].pos = pos;
        }
    }
}

void SpriteBatchNode::setOffset( vec2i offset )
{
    for ( LDEuint i = 0; i < sprites.size(); ++i )
    {
        if ( sprites[i].selected )
        {
            sprites[i].offset = offset;
        }
    }
}

LDEint SpriteBatchNode::setSizeX( LDEint size_x, bool keep_ratio )
{
    vec2i new_size;
    
    for ( LDEuint i = 0; i < sprites.size(); ++i )
    {
        if ( sprites[i].selected )
        {
            if ( keep_ratio )
            {
                LDEfloat ratio = (LDEfloat)size_x / sprites[i].size.x;
                
                new_size.x = size_x;
                new_size.y = round( (LDEfloat)sprites[i].size.y * ratio );
            }
            else
                new_size = vec2i( size_x, sprites[i].size.y );
            
            sprites[i].size = new_size;
            sprites[i].offset = new_size/2;
        }
    }
    
    return new_size.y;
}

LDEint SpriteBatchNode::setSizeY( LDEint size_y, bool keep_ratio )
{
    vec2i new_size;
    
    for ( LDEuint i = 0; i < sprites.size(); ++i )
    {
        if ( sprites[i].selected )
        {
            if ( keep_ratio )
            {
                LDEfloat ratio = (LDEfloat)size_y / sprites[i].size.y;
                
                new_size.y = size_y;
                new_size.x = round( (LDEfloat)sprites[i].size.x * ratio );
            }
            else
                new_size = vec2i( sprites[i].size.x, size_y );
            
            sprites[i].size = new_size;
            sprites[i].offset = new_size/2;
        }
    }
    
    return new_size.x;
}

void SpriteBatchNode::setRotation( LDEfloat rotation )
{
    for ( LDEuint i = 0; i < sprites.size(); ++i )
    {
        if ( sprites[i].selected )
        {
            sprites[i].rot = rotation;
        }
    }
}

void SpriteBatchNode::setOpacity( LDEfloat opacity )
{
    for ( LDEuint i = 0; i < sprites.size(); ++i )
    {
        if ( sprites[i].selected )
        {
            sprites[i].opacity = opacity;
        }
    }
}

void SpriteBatchNode::unselectAll()
{
    for ( LDEuint i = 0; i < sprites.size(); ++i )
    {
        sprites[i].selected = 0;
    }
}

void SpriteBatchNode::draw()
{
    changed = 0;

    // If clicked and we must not keep old selected sprites
    if ( test_coi && !keep_select && mouse.size() )
    {
        // For every click that was done on that frame
        for ( LDEuint inp = 0; inp < mouse.size(); ++inp )
        {
            // If left click (mousedown)
            if ( mouse[inp].left && mouse[inp].down )
            {
                unselectAll();
            }
        }
    }
    
    glEnable(GL_TEXTURE_2D);
    for ( LDEuint i = 0; i < sprites.size(); ++i )
    {
        //if ( last_texture_id != sprites[i].image_id )
        {
            glBindTexture(GL_TEXTURE_2D, sprites[i].image_id );
            
            //last_texture_id = sprites[i].image_id;
        }
        
        glColor4f(1, 1, 1, sprites[i].opacity);
        glPushMatrix();
        glTranslatef( sprites[i].pos.x, sprites[i].pos.y, 0);
        glRotatef(sprites[i].rot, 0, 0, 1);
        LDErectp( sprites[i].image_size,
                 vec4i( sprites[i].texture_uv.x, sprites[i].texture_uv.y, sprites[i].texture_uv.z, sprites[i].texture_uv.w),
                 vec4i( -sprites[i].offset.x, -sprites[i].offset.y, sprites[i].size.x, sprites[i].size.y) );
        glPopMatrix();
        
        // Check for click on the sprite
        if ( (LDEfloat)cursor.x/camera_zoom - camera_pos.x >= sprites[i].pos.x - sprites[i].offset.x && (LDEfloat)cursor.x/camera_zoom - camera_pos.x <= sprites[i].pos.x + sprites[i].size.x - sprites[i].offset.x &&
             (LDEfloat)cursor.y/camera_zoom - camera_pos.y >= sprites[i].pos.y - sprites[i].offset.y && (LDEfloat)cursor.y/camera_zoom - camera_pos.y <= sprites[i].pos.y + sprites[i].size.y - sprites[i].offset.y && test_coi )
        {
            // If left clicked on that one
            for ( LDEuint inp = 0; inp < mouse.size(); ++inp )
            {
                if ( mouse[inp].left && mouse[inp].down )
                {   
                    sprites[i].selected = 1;
                    changed = 1;
                    
                    for ( LDEuint u = 0; u < i; ++u )
                        sprites[u].selected = 0;	// les autres sprites ne sont plus sélectionnés
                }
            }
        }
    }
    
    // Here draw an outline for the selected sprites, on top of all of them to see the selection
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(5,0x1C47);
    glColor3f(0, 1, 0);
    bool some_selected = 0;
    for ( LDEuint i = 0; i < sprites.size(); ++i )
    {
        if ( sprites[i].selected )
        {
            some_selected = 1;
            
            glPushMatrix();
            glTranslatef( sprites[i].pos.x, sprites[i].pos.y, 0);
            glRotatef( sprites[i].rot, 0, 0, 1);
            LDErectw( -sprites[i].offset.x, -sprites[i].offset.y, sprites[i].size.x, sprites[i].size.y );
            glPopMatrix();
            
            selected_pos.x = (LDEfloat)(sprites[i].pos.x + camera_pos.x)*camera_zoom;
            selected_pos.y = (LDEfloat)(sprites[i].pos.y + camera_pos.y)*camera_zoom;
        }
    }
    glColor3f(1, 1, 1);
    glDisable(GL_LINE_STIPPLE);
    glEnable(GL_TEXTURE_2D);
    
    if ( !some_selected )
        selected_pos.reset();
}