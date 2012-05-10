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

void SpriteBatchNode::draw()
{
    changed = 0;

    // If clicked and we must not keep old selected sprites
    if ( !keep_select && mouse.size() )
    {
        // For every click that was done on that frame
        for ( LDEuint inp = 0; inp < mouse.size(); ++inp )
        {
            // If left click (mousedown)
            if ( mouse[inp].left && mouse[inp].down )
            {
                // Unselect every sprite
                for ( LDEuint i = 0; i < sprites.size(); ++i )
                {
                    sprites[i].selected = 0;
                }
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
        
        LDErectp( sprites[i].image_size,
                 vec4i( sprites[i].texture_uv.x, sprites[i].texture_uv.y, sprites[i].texture_uv.z, sprites[i].texture_uv.w),
                 vec4i( sprites[i].pos.x, sprites[i].pos.y, sprites[i].size.x, sprites[i].size.y) );
        
        // Check for click on the sprite
        if ( (LDEfloat)cursor.x/camera_zoom - camera_pos.x >= sprites[i].pos.x && (LDEfloat)cursor.x/camera_zoom - camera_pos.x <= sprites[i].pos.x + sprites[i].size.x &&
             (LDEfloat)cursor.y/camera_zoom - camera_pos.y >= sprites[i].pos.y && (LDEfloat)cursor.y/camera_zoom - camera_pos.y <= sprites[i].pos.y + sprites[i].size.y && test_coi )
        {
            // If left clicked on that one
            for ( LDEuint inp = 0; inp < mouse.size(); ++inp )
            {
                if ( mouse[inp].left && mouse[inp].down )
                {   
                    sprites[i].selected = 1;
                    changed = 1;
                    
                    if ( !keep_select )
                    {
                        for ( LDEuint u = 0; u < i; ++u )
                            sprites[u].selected = 0;	// les autres sprites ne sont plus sélectionnés
                    }
                }
            }
        }
    }
    
    // Here draw an outline for the selected sprites, on top of all of them to see the selection
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(5,0x1C47);
    glColor3f(0, 1, 0);
    for ( LDEuint i = 0; i < sprites.size(); ++i )
    {
        if ( sprites[i].selected )
        {
            LDErectw( sprites[i].pos.x, sprites[i].pos.y, sprites[i].size.x, sprites[i].size.y );
        }
    }
    glColor3f(1, 1, 1);
    glDisable(GL_LINE_STIPPLE);
    glEnable(GL_TEXTURE_2D);
}