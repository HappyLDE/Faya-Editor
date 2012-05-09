/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Graphical User Interface : Drawable scene. Calls a function() with gl calls in it to respect z order
\********************************************************************/

#include "LDEgui_drawable.h"

LDEgui_drawable::LDEgui_drawable()
{
    wait = 0;
    coi = 0;
	test_coi = 0;
	x = 0;
	y = 0;
}

LDEgui_drawable::~LDEgui_drawable()
{
	wait = 0;
    coi = 0;
	test_coi = 0;
	x = 0;
	y = 0;
}

void LDEgui_drawable::draw( vec2i cursor, LDEfloat frametime )
{
	coi = cursorOnIt( cursor );
	
	//glEnable(GL_SCISSOR_TEST);
	//LDEscissor(pos.x, pos.y, size.x, size.y);
	scene( vec2i(pos.x+x,pos.y+y), size, test_coi && coi ? 1 : 0, frametime );
	//glDisable(GL_SCISSOR_TEST);
}

bool LDEgui_drawable::cursorOnIt( vec2i cursor )
{
    return cursor.x > x+pos.x && cursor.x < x+pos.x+size.x && cursor.y > y+pos.y && cursor.y < y+pos.y+size.y;
}
