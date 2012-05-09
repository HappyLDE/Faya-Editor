/*
 *  LDEmouse_event.h
 *  Faya Editor
 *
 *  Created by Dorin Grigore on 25/07/11.
 *  Copyright 2011 Power Watt. All rights reserved.
 *
 */

#ifndef LDE_MOUSE_EVENT_H
#define LDE_MOUSE_EVENT_H

#include "LDEvec2i.h"

struct LDEmouse_event
{
    bool    left,
			right,
			wheel,
			down;
	
	LDEfloat scroll_x,
			scroll_y,
			scroll_z,
			swipe_x,
			swipe_y;
	
    vec2i   cursor_pos;
	
    LDEmouse_event();
    ~LDEmouse_event();
};

#endif
