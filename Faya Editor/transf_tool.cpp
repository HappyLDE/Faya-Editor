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
    
}

LDEtransf_tool::~LDEtransf_tool()
{
    
}

void LDEtransf_tool::draw( vec2i pos )
{
    glBindTexture(GL_TEXTURE_2D, image->id);
    LDErect( pos.x - 13, pos.y - 14, image->size.x, image->size.y);
}