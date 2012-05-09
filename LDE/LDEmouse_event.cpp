/*
 *  LDEmouse_event.cpp
 *  Faya Editor
 *
 *  Created by Dorin Grigore on 25/07/11.
 *  Copyright 2011 Power Watt. All rights reserved.
 *
 */

#include "LDEmouse_event.h"

/// Mouse ////////
LDEmouse_event::LDEmouse_event()
{
    left = 0,
    right = 0,
    wheel = 0;
	down = 0;
	
	scroll_x = 0;
	scroll_y = 0;
	scroll_z = 0;
	
	swipe_x = 0,
	swipe_y = 0;
}

LDEmouse_event::~LDEmouse_event()
{
	
}