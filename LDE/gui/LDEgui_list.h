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

#include "../LDEvariables.h"
#include "../LDEvec2i.h"
#include "../LDEvec3f.h"

#include "../LDEinput.h"

#include "../LDEldet.h"
#include "../LDEldef.h"

#include "tree.hh"

//#include "LDEtree.h"

#include "LDEgui_editbox.h"
#include "LDEgui_scrollbar.h"
#include "LDEgui_button.h"
#include "LDEgui_checkbox.h"

struct LDEgui_list_item
{
	LDEgui_button button;
    LDEgui_checkbox checkbox, checkbox_hide_children;
    LDEgui_editbox editbox; // for renaming possibilities
    
    tree<LDEgui_list_item>::iterator item_group_parent;
    
	LDEint  key,
            can_move;
	
	bool    selected,
            renaming,
            type;
	
	LDEgui_list_item();
	~LDEgui_list_item();
};

struct LDEgui_list
{
    LDEgui_list();
	~LDEgui_list();
	
    std::string name_click,
                name_dbclick;
	
	LDEgui_scrollbar scrollbar;

    tree<LDEgui_list_item>items_tree;
    tree<LDEgui_list_item>::iterator item_root, item_first_selected, item_last_selected, item_indicator;
    
    std::vector<LDEinput>input;
    std::vector<LDEmouse_event>mouse; // list of mouse events in one frame
	
	LDEldet *texture_list,
	
            *texture_list_item,
            *texture_list_item_selected,
    
            *texture_list_checkbox,
            *texture_list_checkbox_checked,
    
            *texture_list_checkbox_folder_hide_children,
            *texture_list_checkbox_folder_hide_children_checked,
    
            *texture_list_traits,
    
            *texture_editbox,
            *texture_editbox_hover,
            *texture_editbox_active,
    
            *texture_folder;
    
	bool	focus,
            active,
            fucked_selection,
            coi,
            click,
            dbclick,
            changed,
            changed_order,
            test_coi,
            hide_indicator,
            show_indicator,
            cursor_over_selected,
            allow_group,
            allow_reorder,
            ctrl,        // control key, to multiple select
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
            
            coi_side,
    
            num_selected,
            offset,
            
            item_height,
            
            group_num,
    
            start_left,
            start_right,
            start_up,
            start_down;
	
	void	erase();
	
	vec2i	pos,
            size,
            app_size;
	
	LDEldef *font;
	
    bool canMoveToIndicator() const;
    LDEint getInnerHeight() const;
    void deselect();
	void remove( LDEuint number );
	void select( tree<LDEgui_list_item>::iterator it, bool keep_rest );
    void selectBetween( tree<LDEgui_list_item>::iterator it_begin, tree<LDEgui_list_item>::iterator it_end );
    void moveSelection();
    void moveSelectionToFolder();
    void groupSelected( std::string group_name );
    tree<LDEgui_list_item>::iterator addGroup( std::string group_name );
	tree<LDEgui_list_item>::iterator addItem( LDEint key, std::string value );
    tree<LDEgui_list_item>::iterator addItemTo( tree<LDEgui_list_item>::iterator item_to, LDEint key, std::string value );
	void draw( vec2i cursor, LDEfloat frametime );
};

#endif // LDE_GUI_LIST_H
