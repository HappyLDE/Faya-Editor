/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Graphical User Interface : elements
 *  // drawable
\********************************************************************/

#ifndef LDE_GUI_DRAWABLE_H
#define LDE_GUI_DRAWABLE_H

#include "../LDEvariables.h"
#include "../LDEvec2i.h"

struct LDEgui_drawable
{
	bool	coi,
			test_coi,
			wait;
	
	LDEint x, y;
	
	vec2i	pos,
			size;

	LDEgui_drawable();			// Constructor
	~LDEgui_drawable();			// Destructor

	void (*scene)(vec2i mypos, vec2i mysize, bool mytest_coi, LDEfloat myframetime );
	
	void draw( vec2i cursor, LDEfloat frametime );				// draw the button
	
	bool cursorOnIt( vec2i cursor );
};

#endif // LDE_GUI_DRAWABLE_H
