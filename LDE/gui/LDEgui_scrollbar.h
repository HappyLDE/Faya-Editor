/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Graphical User Interface : elements
 *  // Scrollbar
\********************************************************************/

#ifndef LDE_GUI_SCROLLBAR_H
#define LDE_GUI_SCROLLBAR_H

#include <vector>

#include "../LDEvariables.h"
#include "../LDEvec2i.h"

#include "../LDEinput.h"
#include "../LDEldet.h"

#include "LDEgui_button.h"

struct LDEgui_scrollbar
{
    LDEgui_scrollbar();
	~LDEgui_scrollbar();
	
	LDEgui_button button_up,
				  button_down,
				  button_middle;
	
    std::vector<LDEmouse_event>mouse;
	
	LDEldet *texture_scrollbar_button_up,
			*texture_scrollbar_button_up_hover,
			*texture_scrollbar_button_up_pressed,
			
			*texture_scrollbar_button_down,
			*texture_scrollbar_button_down_hover,
			*texture_scrollbar_button_down_pressed,
			
			*texture_scrollbar_middle,
	
			*texture_scrollbar_button_middle,
			*texture_scrollbar_button_middle_hover,
			*texture_scrollbar_button_middle_pressed,
			
			//h
			*texture_scrollbar_h_button_up,
			*texture_scrollbar_h_button_up_hover,
			*texture_scrollbar_h_button_up_pressed,
			
			*texture_scrollbar_h_button_down,
			*texture_scrollbar_h_button_down_hover,
			*texture_scrollbar_h_button_down_pressed,
			
			*texture_scrollbar_h_middle,
			
			*texture_scrollbar_h_button_middle,
			*texture_scrollbar_h_button_middle_hover,
			*texture_scrollbar_h_button_middle_pressed;
	
	LDEfloat scroll_height,
			 scroll_amount,
			 button_middle_offset,
			 percent; // 0.0 to 1.0
	
	LDEint x, y,
			uv_left, uv_up, uv_right, uv_down,
			old_size_y;	
	
	bool	test_coi,
			side,
			active,
			changed;
	
	vec2i pos,
		  size;
	
    void setInnerHeight( LDEint new_height );
    
	void setPercent( LDEfloat value );
	void setSide( bool side_ );
	void setRightTextures(); // according to side
	void reset();
	
	void draw( vec2i cursor, LDEfloat frametime );
};

#endif // LDE_GUI_SCROLLBAR_H
