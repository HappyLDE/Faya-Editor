/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Graphical User Interface : elements
 *  // Button
\********************************************************************/

#ifndef LDE_GUI_BUTTON_H
#define LDE_GUI_BUTTON_H

#include <string>

using namespace std;

#include <OpenGL/gl.h>

#include "../LDEvariables.h"
#include "../LDEvec2i.h"
#include "../LDEvec2f.h"
#include "../LDEvec3f.h"
#include "../LDEvec4i.h"

#include "../LDEldef.h"
#include "../LDEldet.h"

#include "../LDEinput.h"

#include "../LDEprimitives.h"

class LDEgui_button
{
    public:

	vector<LDEmouse_event>mouse; // list of mouse events in one frame
	
    LDEint	x, y,
			uv_left,			// left
			uv_right,			// right
			uv_up,				// up
			uv_down;			// down

	bool	coi,				// cursor on it
			pressed,
			get_pos_temp,
			click,
			dbclick,
			locked,
			test_coi,
			clicked_away,
			texture_type,
			icon_side,
			moveable_info,
			scissor,

			moveInfo,
			moveInfoSide;

	string	name;				// Text

	LDEfloat transp,
			dbclick_counter,
			icon_angle;

	vec2i	icon_pos,

			pos,
			size,
			size_temp,

			pos_temp;

	vec2f	offset_temp;

	vec4i	sides;

    LDEldef *font;

   LDEuint	text_side;

   LDEldet  *texture_rel,
            *texture_coi,
            *texture_pre,
            *texture_locked;

	vec3f	text_color,
			text_color_inactive;

	void	lock();
	void	unlock();
	void	reset();
    void    setText( string myname );

	LDEgui_button();			// Constructor
	~LDEgui_button();			// Destructor

	void draw_button(); 		// only mesh
	void draw( vec2i cursor, LDEfloat frametime );				// draw the button
};

#endif // LDE_GUI_BUTTON_H
