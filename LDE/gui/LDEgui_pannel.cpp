/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Graphical User Interface : pannel. A pannel is always under all windows.
 * // May contain menu, buttons etc.
\********************************************************************/

#include "LDEgui_pannel.h"

LDEgui_pannel::LDEgui_pannel()
{
    focus = 0;
    coi = 0;

    uv_up = 0,
    uv_down = 0,
    uv_left = 0,
    uv_right = 0;

    start_up = 0;
    start_down = 0;
    start_left = 0;
    start_right = 0;

    clicked_away = 0;
    wait = 0;
}

LDEgui_pannel::~LDEgui_pannel()
{

}

bool LDEgui_pannel::cursorOnIt( vec2i cursor )
{
	coi = cursor.x > pos.x && cursor.x < pos.x+size.x && cursor.y > pos.y && cursor.y < pos.y+size.y;
	
    return coi;
}

void LDEgui_pannel::draw( vec2i cursor, LDEfloat frametime )
{
    glBindTexture(GL_TEXTURE_2D, texture->id);

    LDEcustomrectp( texture->size, vec4i( pos.x - start_left, pos.y - start_up, size.x + start_right + start_left, size.y + start_down + start_up ), vec4i( uv_left, uv_up, uv_right, uv_down ) );

    elements.test_coi = focus;
    elements.draw( pos.x, pos.y, cursor, frametime );
}
