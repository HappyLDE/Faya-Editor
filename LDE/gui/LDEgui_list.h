/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Graphical User Interface : elements
 *  // List of buttons
\********************************************************************/

#ifndef LDE_GUI_LIST_H
#define LDE_GUI_LIST_H

#include <string>
#include <vector>

using namespace std;

#include "../LDEvariables.h"
#include "../LDEvec2i.h"
#include "../LDEvec3f.h"

#include "../LDEinput.h"

#include "../LDEldet.h"
#include "../LDEldef.h"

#include "LDEgui_scrollbar.h"
#include "LDEgui_button.h"

struct LDEgui_list_item
{
	LDEgui_button button;
	
	LDEint key;
	
	bool selected;
	
	LDEgui_list_item();
	~LDEgui_list_item();
};

struct LDEgui_list
{
    LDEgui_list();
	~LDEgui_list();
	
	string name_click,
			name_dbclick;
	
	LDEgui_scrollbar scrollbar;
	
	vector<LDEgui_list_item>item;
	
	vector<LDEinput>input;
	vector<LDEmouse_event>mouse; // list of mouse events in one frame
	
	LDEldet *texture_list,
	
			*texture_list_item,
			*texture_list_item_selected;

	bool	focus,
			active,
			coi,
			click,
			dbclick,
			changed,
			test_coi,
			shift;

	vec3f	color_selected,
			color;
	
	LDEint	x, y,
			uv_left,			// left
			uv_right,			// right
			uv_up,				// up
			uv_down,			// down
	
			content_height,
	
			scroll,
	
			selected,
			offset,
	
			item_height,
	
			start_left,
			start_right,
			start_up,
			start_down;
	
	void	erase();
	
	vec2i	pos,
			size,
			app_size;
	
	LDEldef *font;
	
    void deselect();
	void remove( LDEuint number );
	void select( LDEuint number, bool keep_rest );
	void addItem( LDEint key, string value );
	void draw( vec2i cursor, LDEfloat frametime );
};

#endif // LDE_GUI_LIST_H
