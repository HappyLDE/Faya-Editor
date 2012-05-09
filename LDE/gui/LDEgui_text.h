/*
 *  LDEgui_text.h
 *  Faya Editor
 *
 *  Created by Dorin Grigore on 31/07/11.
 *  Copyright 2011 Power Watt. All rights reserved.
 *
 */

#ifndef LDE_GUI_TEXT_H
#define LDE_GUI_TEXT_H

#include <string>

using namespace std;

#include "../LDEvariables.h"
#include "../LDEldef.h"

struct LDEgui_text
{
	LDEldef *font;

	vec2i	pos;
	
	string	value;
	
	void	draw( vec2i pos_ );
	
	LDEgui_text();
	~LDEgui_text();
};

#endif