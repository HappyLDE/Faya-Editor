/*
 *  LDEgui_text.cpp
 *  Faya Editor
 *
 *  Created by Dorin Grigore on 31/07/11.
 *  Copyright 2011 Power Watt. All rights reserved.
 *
 */

#include "LDEgui_text.h"

LDEgui_text::LDEgui_text()
{

}

LDEgui_text::~LDEgui_text()
{
	
}

void LDEgui_text::draw( vec2i pos_ )
{
	font->setText( value );
	font->pos.x = pos_.x + pos.x;
	font->pos.y = pos_.y + pos.y;
	
	font->draw();
}