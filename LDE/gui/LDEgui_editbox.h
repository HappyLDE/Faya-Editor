/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Graphical User Interface : elements
 *  // Editbox
\********************************************************************/

#ifndef LDE_GUI_EDITBOX_H
#define LDE_GUI_EDITBOX_H

#include <string>
#include <vector>

using namespace std;

#include "../LDEvariables.h"

#include "../LDEinput.h"

#include "../LDEldet.h"

#include "LDEgui_button.h"

struct LDEgui_editbox
{
    LDEgui_editbox();
	~LDEgui_editbox();
	
	vector<LDEinput>input;
	
	LDEldet *texture_editbox,
			*texture_editbox_hover,
			*texture_editbox_active;
	
	bool focus,
		 cursor_flag;
	
	LDEgui_button button;
	
	vec2i   pos,
            size,
            app_size;
	
	string name;
	
	LDEint cursor_pos;
	LDEint text_offset;
	
	LDEfloat cursor_toggle_time;
	
	void draw( vec2i cursor, LDEfloat frametime );
};

#endif // LDE_GUI_EDITBOX_H
