/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Graphical User Interface : elements
 *  // List of butons
 \********************************************************************/

#include "LDEgui_list.h"

using namespace std;

LDEgui_list_item::LDEgui_list_item()
{
	key = 0;
	selected = 0;
    type = 0; // 0 = row 1 = group parent
    renaming = 0;
    
    can_move = 2; // 2 = can move, 1 = can move only on the same depth, 0 = can not move
}

LDEgui_list_item::~LDEgui_list_item()
{

}

/////////
LDEgui_list::LDEgui_list()
{
    group_num = 1;
    
    allow_group = 1;
    allow_reorder = 1;
    
    show_indicator = 0;

    coi_side = 0;
    
    cursor_over_selected = 0;
    
    fucked_selection = 0;
    
    item_root = items_tree.begin();
    
	size = vec2i( 20, 20 );
	
    hide_indicator = 0;
    
	changed = 0;
    changed_order = 0;
    
	focus = 0;
	test_coi = 0;
	active = 0;
	
	offset = 0;
	
	shift = 0;
    ctrl = 0;
	
	x = 0,
	y = 0;
	
	uv_left = 8;	// left
	uv_right = 8;	// right
	uv_up = 8;		// up
	uv_down = 8;	// down
	
	start_left = 0;
	start_right = 0;
	start_up = 4;
	start_down = 4;
	
	item_height = 15;
	
	num_selected = 0;
	
	scroll = 0;
	
	coi = 0;
	
	content_height = start_up + start_down;
	
	color = vec3f( 1,1,1 );
	
	click = 0;
	dbclick = 0;
}

LDEgui_list::~LDEgui_list()
{
    
}

void LDEgui_list::remove( LDEuint number )
{
	//selected = 0;
	
	//items.erase( items.begin() + number );
}

void LDEgui_list::deselect()
{
    num_selected = 0;
    
    tree<LDEgui_list_item>::iterator item_itr = items_tree.begin();
    while( item_itr != items_tree.end() )
    {
        item_itr->button.texture_rel = texture_list_item;
        item_itr->button.texture_coi = texture_list_item;
        
        item_itr->button.text_color = color;
        
        item_itr->selected = 0;
        
        ++item_itr;
    }
    
    item_last_selected = item_root;
    
    changed = 1;
    focus = 0;
}

tree<LDEgui_list_item>::iterator LDEgui_list::addItem( LDEint key, string value )
{
    LDEgui_list_item item_temp;
    
	item_temp.button.name = value;
	item_temp.button.text_side = 1;
	item_temp.button.size.y = item_height;
    
	content_height += item_height;
	
    item_temp.key = key;
    
    item_temp.button.font = font;
    item_temp.button.texture_rel = texture_list_item;
    item_temp.button.texture_coi = texture_list_item;
    item_temp.button.texture_pre = texture_list_item;
    item_temp.button.texture_locked = texture_list_item;
    
    item_temp.button.text_pos.x = 15;
    
    item_temp.checkbox.button.font = font;
	item_temp.checkbox.button.texture_rel = texture_list_checkbox;
	item_temp.checkbox.button.texture_coi = texture_list_checkbox;
    item_temp.checkbox.button.texture_pre = texture_list_checkbox;
    item_temp.checkbox.button.texture_icon = texture_list_checkbox_checked;
	item_temp.checkbox.button.name = "";
	
    item_temp.checkbox.pos = vec2i( 3, 3 );
	item_temp.checkbox.button.size = vec2i( 16, 16 );
    
    item_temp.checkbox.setCheck( 1 );
    
	item_temp.checkbox.button.uv_up = 6;
    item_temp.checkbox.button.uv_down = 6;
    item_temp.checkbox.button.uv_left = 6;
    item_temp.checkbox.button.uv_right = 6;
    
    // eb
    item_temp.editbox.button.font = font;
	item_temp.editbox.button.texture_rel = texture_editbox;
	
	item_temp.editbox.button.texture_coi = texture_editbox_hover;
    item_temp.editbox.button.texture_pre = texture_editbox_active;
    item_temp.editbox.button.texture_locked = texture_editbox;
	
	item_temp.editbox.texture_editbox = texture_editbox;
	item_temp.editbox.texture_editbox_hover = texture_editbox_hover;
	item_temp.editbox.texture_editbox_active = texture_editbox_active;
	
	item_temp.editbox.button.uv_up = 8;
    item_temp.editbox.button.uv_down = 8;
    item_temp.editbox.button.uv_left = 8;
    item_temp.editbox.button.uv_right = 8;
    
    scrollbar.scroll_height = content_height;
	scrollbar.button_middle_offset = 0;
	scrollbar.scroll_amount = 0;
	offset = 0;
	scroll = 0;
    
    return items_tree.insert( item_root, item_temp );
}

tree<LDEgui_list_item>::iterator LDEgui_list::addItemTo( tree<LDEgui_list_item>::iterator item_to, LDEint key, std::string value )
{
    LDEgui_list_item item_temp;
    
	item_temp.button.name = value;
	item_temp.button.text_side = 1;
	item_temp.button.size.y = item_height;
    
	content_height += item_height;
	
    item_temp.key = key;
    
    item_temp.button.font = font;
    item_temp.button.texture_rel = texture_list_item;
    item_temp.button.texture_coi = texture_list_item;
    item_temp.button.texture_pre = texture_list_item;
    item_temp.button.texture_locked = texture_list_item;
    
    item_temp.button.text_pos.x = 15;
    
    item_temp.checkbox.button.font = font;
	item_temp.checkbox.button.texture_rel = texture_list_checkbox;
	item_temp.checkbox.button.texture_coi = texture_list_checkbox;
    item_temp.checkbox.button.texture_pre = texture_list_checkbox;
    item_temp.checkbox.button.texture_icon = texture_list_checkbox_checked;
	item_temp.checkbox.button.name = "";
	
    item_temp.checkbox.pos = vec2i( 3, 3 );
	item_temp.checkbox.button.size = vec2i( 16, 16 );
    
    item_temp.checkbox.setCheck( 1 );
    
	item_temp.checkbox.button.uv_up = 6;
    item_temp.checkbox.button.uv_down = 6;
    item_temp.checkbox.button.uv_left = 6;
    item_temp.checkbox.button.uv_right = 6;
    
    // eb
    item_temp.editbox.button.font = font;
	item_temp.editbox.button.texture_rel = texture_editbox;
	
	item_temp.editbox.button.texture_coi = texture_editbox_hover;
    item_temp.editbox.button.texture_pre = texture_editbox_active;
    item_temp.editbox.button.texture_locked = texture_editbox;
	
	item_temp.editbox.texture_editbox = texture_editbox;
	item_temp.editbox.texture_editbox_hover = texture_editbox_hover;
	item_temp.editbox.texture_editbox_active = texture_editbox_active;
	
	item_temp.editbox.button.uv_up = 8;
    item_temp.editbox.button.uv_down = 8;
    item_temp.editbox.button.uv_left = 8;
    item_temp.editbox.button.uv_right = 8;
    
    scrollbar.scroll_height = content_height;
	scrollbar.button_middle_offset = 0;
	scrollbar.scroll_amount = 0;
	offset = 0;
	scroll = 0;
    
    return items_tree.append_child( item_to, item_temp );
}

void LDEgui_list::erase()
{
    items_tree.clear();
    
	changed = 0;
	
	focus = 0;
	test_coi = 0;
	active = 0;
	
	offset = 0;
	
	shift = 0;
	
	scroll = 0;
	
	coi = 0;
	
	content_height = start_up + start_down;
	
	click = 0;
	dbclick = 0;
}

void LDEgui_list::select( tree<LDEgui_list_item>::iterator it, bool keep_rest )
{
    if ( !keep_rest )
    {
        tree<LDEgui_list_item>::iterator item_itr = items_tree.begin();
        while( item_itr != items_tree.end() )
        {
            item_itr->button.texture_rel = texture_list_item;
            item_itr->button.texture_coi = texture_list_item;
            
            item_itr->button.text_color = color;
            
            item_itr->selected = 0;
            
            ++item_itr;
        }
        
        num_selected = 0;
        
        item_first_selected = it;
    }
    
    item_last_selected = it;

    it->button.texture_rel = texture_list_item_selected;
    it->button.texture_coi = texture_list_item_selected;
    it->selected = 1;
    it->button.text_color = color_selected;
    
    ++num_selected;
    
    changed = 1;
    focus = 1;
    
    fucked_selection = 0;
}

void LDEgui_list::selectBetween( tree<LDEgui_list_item>::iterator it_begin, tree<LDEgui_list_item>::iterator it_end )
{
    // First, deselect ALL
    tree<LDEgui_list_item>::iterator item_itr = items_tree.begin();
    while( item_itr != items_tree.end() )
    {
        item_itr->button.texture_rel = texture_list_item;
        item_itr->button.texture_coi = texture_list_item;
        
        item_itr->button.text_color = color;
        
        item_itr->selected = 0;
        
        ++item_itr;
    }
    
    num_selected = 0;
    
    // Then select the in betweens
    item_itr = it_begin;

    bool traverse_order = items_tree.index( it_begin ) < items_tree.index( it_end );
    
    tree<LDEgui_list_item>::iterator item_end2 = it_end;
    
    if ( traverse_order )
    {
        it_end = items_tree.end( it_end );
    
        --item_end2;
    }
    else
        --it_end;
    
    if ( items_tree.depth(it_begin) != items_tree.depth(item_end2) )
        fucked_selection = 1;
    
    //cout<<"items_tree.depth(it_begin) "<<items_tree.depth(it_begin)<<"\n";
    //cout<<"items_tree.depth(item_end2) "<<items_tree.depth(item_end2)<<" // "<<rand()<<"\n";
    
    while( item_itr != it_end )
    {
        if ( items_tree.is_valid(item_itr) )
        {
            item_itr->button.texture_rel = texture_list_item_selected;
            item_itr->button.texture_coi = texture_list_item_selected;
            
            item_itr->button.text_color = color_selected;
            
            item_itr->selected = 1;
            
            ++num_selected;
        }
        else
        {
            item_itr = traverse_order ? items_tree.begin() : items_tree.end();
            fucked_selection = 1;
        }
        
        traverse_order ? ++item_itr : --item_itr;
    }
    
    if ( fucked_selection )
        num_selected = 0;
    
    changed = 1;
}

tree<LDEgui_list_item>::iterator LDEgui_list::addGroup( std::string group_name )
{
    LDEgui_list_item item_temp;
    
    item_temp.type = 1; //  group folder
    item_temp.button.name = group_name;
    item_temp.button.text_side = 1;
    item_temp.button.size.y = item_height;
    
    content_height += item_height;
    
    item_temp.button.font = font;
    item_temp.button.texture_rel = texture_list_item;
    item_temp.button.texture_coi = texture_list_item;
    item_temp.button.texture_pre = texture_list_item;
    item_temp.button.texture_locked = texture_list_item;
    
    item_temp.button.texture_icon = texture_folder;
    item_temp.button.icon_pos = vec2i( 28, 2);
    item_temp.button.text_pos.x = 44;
    item_temp.button.draw_icon = 1;
    
    // Toggle row visibility
    item_temp.checkbox.button.font = font;
    item_temp.checkbox.button.texture_rel = texture_list_checkbox;
    item_temp.checkbox.button.texture_coi = texture_list_checkbox;
    item_temp.checkbox.button.texture_pre = texture_list_checkbox;
    item_temp.checkbox.button.texture_icon = texture_list_checkbox_checked;
    item_temp.checkbox.button.name = "";
    
    item_temp.checkbox.setCheck( 1 );
    
    item_temp.checkbox.pos = vec2i( 15, 3 );
    item_temp.checkbox.button.size = vec2i( 16, 16 );
    
    item_temp.checkbox.button.uv_up = 6;
    item_temp.checkbox.button.uv_down = 6;
    item_temp.checkbox.button.uv_left = 6;
    item_temp.checkbox.button.uv_right = 6;
    
    /// TOGGLE SHOW Group Children
    item_temp.checkbox_hide_children.button.font = font;
    item_temp.checkbox_hide_children.button.texture_rel = texture_list_checkbox_folder_hide_children;
    item_temp.checkbox_hide_children.button.texture_coi = texture_list_checkbox_folder_hide_children;
    item_temp.checkbox_hide_children.button.texture_pre = texture_list_checkbox_folder_hide_children;
    item_temp.checkbox_hide_children.button.texture_icon = texture_list_checkbox_folder_hide_children_checked;
    item_temp.checkbox_hide_children.button.name = "";
    
    item_temp.checkbox_hide_children.setCheck( 0 );
    
    item_temp.checkbox_hide_children.pos = vec2i( 4, 4 );
    item_temp.checkbox_hide_children.button.size = vec2i( 8, 8 );
    
    item_temp.checkbox_hide_children.button.uv_up = 6;
    item_temp.checkbox_hide_children.button.uv_down = 6;
    item_temp.checkbox_hide_children.button.uv_left = 6;
    item_temp.checkbox_hide_children.button.uv_right = 6;
    
    // eb
    item_temp.editbox.button.font = font;
    item_temp.editbox.button.texture_rel = texture_editbox;
    
    item_temp.editbox.button.texture_coi = texture_editbox_hover;
    item_temp.editbox.button.texture_pre = texture_editbox_active;
    item_temp.editbox.button.texture_locked = texture_editbox;
    
    item_temp.editbox.texture_editbox = texture_editbox;
    item_temp.editbox.texture_editbox_hover = texture_editbox_hover;
    item_temp.editbox.texture_editbox_active = texture_editbox_active;
    
    item_temp.editbox.button.uv_up = 8;
    item_temp.editbox.button.uv_down = 8;
    item_temp.editbox.button.uv_left = 8;
    item_temp.editbox.button.uv_right = 8;
    
    // Add "GROUP folder" node
    return items_tree.insert( item_root, item_temp );
}

void LDEgui_list::groupSelected( std::string group_name )
{
    if ( !fucked_selection && allow_group )
    {
        LDEgui_list_item item_temp;
        
        item_temp.type = 1; //  group folder
        item_temp.button.name = group_name;
        item_temp.button.text_side = 1;
        item_temp.button.size.y = item_height;
        
        content_height += item_height;
        
        item_temp.button.font = font;
        item_temp.button.texture_rel = texture_list_item;
        item_temp.button.texture_coi = texture_list_item;
        item_temp.button.texture_pre = texture_list_item;
        item_temp.button.texture_locked = texture_list_item;
        
        item_temp.button.texture_icon = texture_folder;
        item_temp.button.icon_pos = vec2i( 28, 2);
        item_temp.button.text_pos.x = 44;
        item_temp.button.draw_icon = 1;
        
        // Toggle row visibility
        item_temp.checkbox.button.font = font;
        item_temp.checkbox.button.texture_rel = texture_list_checkbox;
        item_temp.checkbox.button.texture_coi = texture_list_checkbox;
        item_temp.checkbox.button.texture_pre = texture_list_checkbox;
        item_temp.checkbox.button.texture_icon = texture_list_checkbox_checked;
        item_temp.checkbox.button.name = "";
        
        item_temp.checkbox.setCheck( 1 );
        
        item_temp.checkbox.pos = vec2i( 15, 3 );
        item_temp.checkbox.button.size = vec2i( 16, 16 );
        
        item_temp.checkbox.button.uv_up = 6;
        item_temp.checkbox.button.uv_down = 6;
        item_temp.checkbox.button.uv_left = 6;
        item_temp.checkbox.button.uv_right = 6;
        
        /// TOGGLE SHOW Group Children
        item_temp.checkbox_hide_children.button.font = font;
        item_temp.checkbox_hide_children.button.texture_rel = texture_list_checkbox_folder_hide_children;
        item_temp.checkbox_hide_children.button.texture_coi = texture_list_checkbox_folder_hide_children;
        item_temp.checkbox_hide_children.button.texture_pre = texture_list_checkbox_folder_hide_children;
        item_temp.checkbox_hide_children.button.texture_icon = texture_list_checkbox_folder_hide_children_checked;
        item_temp.checkbox_hide_children.button.name = "";
        
        item_temp.checkbox_hide_children.setCheck( 1 );
        
        item_temp.checkbox_hide_children.pos = vec2i( 4, 4 );
        item_temp.checkbox_hide_children.button.size = vec2i( 8, 8 );
        
        item_temp.checkbox_hide_children.button.uv_up = 6;
        item_temp.checkbox_hide_children.button.uv_down = 6;
        item_temp.checkbox_hide_children.button.uv_left = 6;
        item_temp.checkbox_hide_children.button.uv_right = 6;
        
        // eb
        item_temp.editbox.button.font = font;
        item_temp.editbox.button.texture_rel = texture_editbox;
        
        item_temp.editbox.button.texture_coi = texture_editbox_hover;
        item_temp.editbox.button.texture_pre = texture_editbox_active;
        item_temp.editbox.button.texture_locked = texture_editbox;
        
        item_temp.editbox.texture_editbox = texture_editbox;
        item_temp.editbox.texture_editbox_hover = texture_editbox_hover;
        item_temp.editbox.texture_editbox_active = texture_editbox_active;
        
        item_temp.editbox.button.uv_up = 8;
        item_temp.editbox.button.uv_down = 8;
        item_temp.editbox.button.uv_left = 8;
        item_temp.editbox.button.uv_right = 8;
        
        // Add "GROUP folder" node
        tree<LDEgui_list_item>::iterator item_group = items_tree.insert( items_tree.index( item_first_selected ) < items_tree.index( item_last_selected ) ? item_first_selected : item_last_selected, item_temp );
        
        // Add temporary child to the folder so that we move all selected rows "next to" this child, then we'll delete it
        tree<LDEgui_list_item>::iterator item_itr_temp = items_tree.append_child( item_group, item_temp );

        tree<LDEgui_list_item>::iterator item_last_moved = item_itr_temp;
        
        // For every selected row
        tree<LDEgui_list_item>::iterator item_itr = items_tree.begin();
        while( item_itr != items_tree.end() )
        {
            if ( item_itr->selected )
            {
                if ( items_tree.is_valid( item_itr->item_group_parent ) )
                {
                    item_group->item_group_parent = item_itr->item_group_parent;
                    item_group->can_move = item_itr->can_move;
                }
                
                item_last_moved = items_tree.move_after( item_last_moved, item_itr );
                
                item_itr->selected = 0;
            }

            ++item_itr;
        }
    
        items_tree.erase( item_itr_temp );
        
        item_group->selected = 1;
        item_group->button.texture_rel = texture_list_item_selected;
        item_group->button.texture_coi = texture_list_item_selected;
        
        scrollbar.setInnerHeight( getInnerHeight() );
        
        ++group_num;
        
        num_selected = 1;
        
        changed = 1;
        
        //cout<<"grouping done successfully\n";
    }
}

void LDEgui_list::moveSelectionToFolder()
{
    if ( coi_side == 2 )
    {
        LDEgui_list_item item_temp;
        // Add temporary child to the folder so that we move all selected rows "next to" this child, then we'll delete it
        tree<LDEgui_list_item>::iterator item_itr_temp = items_tree.append_child( item_indicator, item_temp );
        
        tree<LDEgui_list_item>::iterator item_itr = items_tree.begin();
        
        tree<LDEgui_list_item>::iterator item_last_moved = item_itr_temp;
        while( item_itr != items_tree.end() )
        {
            if ( item_itr->selected )
            {
                item_last_moved = items_tree.move_after( item_last_moved, item_itr );
                
                item_itr->selected = 0;
            }
            
            ++item_itr;
        }
        
        items_tree.erase( item_itr_temp );
        
        scrollbar.setInnerHeight( getInnerHeight() );
        
        changed = 1;
        changed_order = 1;
    }
}

void LDEgui_list::moveSelection()
{
    tree<LDEgui_list_item>::iterator item_itr = items_tree.begin();
    tree<LDEgui_list_item>::iterator item_last_moved = item_indicator;
    while( item_itr != items_tree.end() )
    {
        //cout<<item_itr->button.name<<"\n";
        
        if ( item_itr->selected )
        {
            item_itr->selected = 0;
            
            tree<LDEgui_list_item>::iterator item_itr_temp = items_tree.begin( item_itr );
            
            if ( item_last_moved == item_indicator )
            {
                if ( coi_side == 3 )
                    item_last_moved = items_tree.move_after( item_last_moved, item_itr);
                else
                    item_last_moved = items_tree.move_before( item_last_moved, item_itr);
            }
            else
                item_last_moved = items_tree.move_after( item_last_moved, item_itr);
            --item_itr_temp;
            item_itr = item_itr_temp;
        }
        
        ++item_itr;
    }
    
    // Reselect back again those moved
    item_itr = items_tree.begin();
    while( item_itr != items_tree.end() )
    {
        if ( item_itr->button.texture_coi == texture_list_item_selected )
            item_itr->selected = 1;
        
        ++item_itr;
    }
    
    changed = 1;
    changed_order = 1;
}

LDEint LDEgui_list::getInnerHeight() const
{
    LDEint height = 0;
    
    //
    tree<LDEgui_list_item>::iterator item_itr = items_tree.begin();
    while( item_itr != items_tree.end() )
    {
        LDEint depth = items_tree.depth( item_itr );
        
        height += item_itr->button.size.y;
        
        // If we are on a "group folder" row and it's children are hidden
        if ( item_itr->type == 1 && item_itr->checkbox_hide_children.checked )
        {
            tree<LDEgui_list_item>::iterator item_parent = items_tree.parent(item_itr);
            
            item_itr = items_tree.next_sibling(item_itr);
            
            if ( !items_tree.is_valid( item_itr ) && !depth )
            {
                item_itr = items_tree.end();
            }
            else
            {
                while ( !items_tree.is_valid( item_itr ) )
                {
                    item_itr = items_tree.next_sibling(item_parent);
                    
                    item_parent = items_tree.parent(item_parent);
                    
                    if ( !items_tree.is_valid(item_parent) && !items_tree.is_valid( item_itr ) )
                    {
                        item_itr = items_tree.end();
                        break;
                    }
                }
            }
        }
        else
            ++item_itr;
    }
    
    return height;
}

bool LDEgui_list::canMoveToIndicator() const
{
    // For ALL the rows (because some can be selected randomly) so we need to iterate all
    tree<LDEgui_list_item>::iterator item_itr = items_tree.begin();
    while( item_itr != items_tree.end() )
    {
        // If this row is selected
        if ( item_itr->selected )
        {
            //
            switch( item_itr->can_move )
            {
                // Can only move to destination if destination has parent item_group_parent
                case 3:
                {
                    bool is_within = 0;
                    
                    // From the indicator (indicator = row to move next to)
                    tree<LDEgui_list_item>::iterator item_parent = items_tree.parent( item_indicator );
                    
                    // We go upper in the tree
                    while ( items_tree.is_valid( item_parent ) )
                    {
                        if ( item_itr->item_group_parent == item_parent )
                            is_within = 1;
                        
                        item_parent = items_tree.parent(item_parent);
                    }
                    
                    if ( !is_within )
                        return 0;
                    
                    break;
                }

                // default or 2 (can move everywhere) except in (child) subtree (see below)
                default:
                {
                    if ( items_tree.depth( item_itr ) < items_tree.depth( item_indicator ) )
                    {
                        // From the indicator (indicator = row to move next to)
                        tree<LDEgui_list_item>::iterator item_parent = items_tree.parent( item_indicator );
                        
                        // We go upper in the tree
                        while ( items_tree.is_valid( item_parent ) )
                        {
                            if ( item_itr == item_parent )
                                return 0;
                            
                            item_parent = items_tree.parent(item_parent);
                        }
                    }
                    
                    break;
                }
                
                // Can only move on the same depth (can't go to subtree)
                case 1:
                {
                    if ( (items_tree.depth( item_itr ) != items_tree.depth( item_indicator )) || coi_side == 2 )
                        return 0;
                        
                    break;
                }
                
                // Can't move
                case 0: return 0;
            }
        }
        
        ++item_itr;
    }
    
    return 1;
}

void LDEgui_list::draw( vec2i cursor, LDEfloat frametime )
{
	click = 0;
	dbclick = 0;
	active = 0;
	changed = 0;
    changed_order = 0;
    cursor_over_selected = 0;
    hide_indicator = 0;
	
	coi = cursor.x >= x && cursor.x <= x + size.x && cursor.y >= y && cursor.y <= y+size.y;
	
	if ( focus )
    {
        for ( LDEuint i = 0; i < input.size(); ++i )
        {
            if ( input[i].key_down )
            {
                if ( input[i].lshift )
                    shift = 1;
                
                if ( input[i].lcmd )
                    ctrl = 1;
                
                if ( input[i].g && ctrl )
                {
                    groupSelected( "Group"+LDEnts(group_num) );
                }
            }
            
            if ( !input[i].key_down )
            {
                if ( input[i].lshift )
                    shift = 0;
                
                if ( input[i].lcmd )
                    ctrl = 0;
            }
            else
            {
                // Down arrow key
                if ( input[i].down )
                {
                    // On regarde l'élément couramment sélecitonné
                    tree<LDEgui_list_item>::iterator iterator_temp = item_last_selected;
                    
                    // On récupère sa profondeur
                    LDEint depth = items_tree.depth(iterator_temp);
                    
                    // Si c'est un row groupe contenant d'autres enfants ET qu'il est fermé (ses enfants on les voit pas/collapsed)
                    if ( iterator_temp->type == 1 && iterator_temp->checkbox_hide_children.checked )
                    {
                        // On récupère le parent de l'élément actuellement sélectionné (au cas où on a besoin plus bas)
                        tree<LDEgui_list_item>::iterator item_parent = items_tree.parent(iterator_temp);
                        
                        // Si tout se passe bien, cette ligne résout tout, il passe au prochain élément dans la même profondeur
                        // (donc sans aller sélectionner les enfants du row groupe)
                        iterator_temp = items_tree.next_sibling(iterator_temp);
                        
                        // S'il n'y a pas de prochain élément à la même profondeur et qu'on est au lvl 1 dans l'arbre (depth 0)
                        if ( !items_tree.is_valid( iterator_temp ) && !depth )
                        {
                            // Annoncer qu'on est à la fin de la liste
                            iterator_temp = items_tree.end();
                        }
                        // Sinon
                        else
                        {
                            // Lancer une boucle tant qu'on n'a pas un bon élément à sélectionner en remontant à son parent
                            while ( !items_tree.is_valid( iterator_temp ) )
                            {
                                //
                                iterator_temp = items_tree.next_sibling(item_parent);
                                
                                item_parent = items_tree.parent(item_parent);
                                
                                if ( !items_tree.is_valid(item_parent) && !items_tree.is_valid( iterator_temp ) )
                                {
                                    iterator_temp = items_tree.end();
                                    break;
                                }
                            }
                        }
                    }
                    // Sinon passer au prochain row
                    else
                        ++iterator_temp;
                    
                    if ( items_tree.is_valid(iterator_temp) )
                        select( iterator_temp, 0 );
                    
                    //if ( selected * item_height + scroll > (size.y - (item_height + start_up + start_down)) )
                    //    scroll = -((selected * item_height) - (size.y - (item_height + start_up + start_down)));
                }
                
                // Up arrow key
                if ( input[i].up )
                {
                    tree<LDEgui_list_item>::iterator iterator_temp = item_last_selected;
                    
                    --iterator_temp;
                    
                    if ( items_tree.is_valid(iterator_temp) )
                        select( iterator_temp, 0 );
                 
                    //if ( selected * item_height + scroll < 0 )
                    //    scroll = -(selected * item_height);
                }
            }
        }
    }
    
	if ( test_coi )
	{
		LDEfloat scroll_y = 0;
		
		for ( LDEuint i = 0; i < mouse.size(); ++i )
		{
			if ( mouse[i].left && mouse[i].down )
			{
                focus = coi;
			}
			
			if ( mouse[i].scroll_y != 0 )
				scroll_y += mouse[i].scroll_y;
			
			
			if ( mouse[i].swipe_y != 0 )
			{
				if ( mouse[i].swipe_y == -1 )
					scrollbar.setPercent( 0 );
				else
					scrollbar.setPercent( 1 );
                
				if ( scrollbar.changed )
					scroll = -scrollbar.scroll_amount;
			}
		}
		
		if ( scroll_y != 0 )
		{
			LDEfloat percent_y = scrollbar.percent + (scroll_y / 100);
			
			if ( percent_y > 1 )
				percent_y = 1;
			else if ( percent_y < 0 )
				percent_y = 0;
			
			scrollbar.setPercent( percent_y );
			
			if ( scrollbar.changed )
				scroll = -scrollbar.scroll_amount;
		}
	}
	
	glBindTexture(GL_TEXTURE_2D, texture_list->id);
	LDEcustomrectp( texture_list->size, vec4i( x, y, size.x, size.y ), vec4i( uv_left, uv_up, uv_right, uv_down ) );
    
	glEnable( GL_SCISSOR_TEST );
	glScissor( x, app_size.y - (y+size.y), size.x - scrollbar.size.x, size.y );
    
	/*if ( scroll )
		offset = -scroll / item_height;
	else
		offset = 0;
	
	LDEint num = (size.y / item_height) + offset + 1;*/
    
    //LDEuint selected_temp = selected;
    
    tree<LDEgui_list_item>::iterator item_itr = items_tree.begin();
    LDEint count = 0;
    while( item_itr != items_tree.end() )
    {
        LDEint depth = items_tree.depth( item_itr ) * 12;
        
        LDEint y_advance = (count * item_itr->button.size.y);
        
        item_itr->button.test_coi = test_coi;
        
        item_itr->button.mouse = mouse;
		item_itr->button.x = x + start_left + depth;
		item_itr->button.y = y + scroll + y_advance + start_up;
		
		item_itr->button.size.x = size.x - (start_left + start_right) - scrollbar.size.x - 2 - depth;
		item_itr->button.draw( cursor, frametime );
        
        item_itr->checkbox.button.test_coi = test_coi;
        
        item_itr->checkbox.button.mouse = mouse;
		item_itr->checkbox.button.x = x + item_itr->checkbox.pos.x + start_left + depth;
		item_itr->checkbox.button.y = y + item_itr->checkbox.pos.y + scroll + y_advance + start_up;
		
		item_itr->checkbox.draw( cursor, frametime );
        
        if ( item_itr->type )
        {
            item_itr->checkbox_hide_children.button.test_coi = test_coi;
            
            item_itr->checkbox_hide_children.button.mouse = mouse;
            item_itr->checkbox_hide_children.button.x = x + item_itr->checkbox_hide_children.pos.x + start_left + depth;
            item_itr->checkbox_hide_children.button.y = y + item_itr->checkbox_hide_children.pos.y + scroll + y_advance + start_up;
            
            item_itr->checkbox_hide_children.draw( cursor, frametime );
            
            if ( item_itr->checkbox_hide_children.changed )
                scrollbar.setInnerHeight( getInnerHeight() );
        }
        
        if ( item_itr->renaming )
        {
            item_itr->editbox.button.pos = item_itr->editbox.pos;
            item_itr->editbox.button.x = x + item_itr->editbox.button.pos.x + start_left + depth + ( item_itr->type ? 40 : 11 );
            item_itr->editbox.button.y = y + item_itr->editbox.button.pos.y + scroll + y_advance + start_up - 5;
            item_itr->editbox.button.test_coi = test_coi;
            item_itr->editbox.size.x = item_itr->button.size.x - ( item_itr->type ? 40 : 11 );
            item_itr->editbox.app_size = app_size;
            item_itr->editbox.input = input;
            item_itr->editbox.button.mouse = mouse;
            item_itr->editbox.draw( cursor, frametime );
            
            if ( item_itr->editbox.blured )
            {
                item_itr->button.name = item_itr->editbox.name;
                
                item_itr->editbox.button.clicked_away = 0;
                
                item_itr->renaming = 0;
            }
        }
        
        if ( depth )
        {
            glBindTexture(GL_TEXTURE_2D, texture_list_traits->id);
            LDErect(x + depth - 13, y + y_advance + scroll - 1, texture_list_traits->size.x, texture_list_traits->size.y);
        }
        
        if ( coi )
		{
            /////////////// If click on list row //////////////
			if ( item_itr->button.click )
			{
				if ( shift )
                {
                    item_last_selected = item_itr;
                    
                    selectBetween( item_first_selected, item_itr );
                }
				else
					select( item_itr, ctrl );

				click = 1;
			}
            
			if ( item_itr->button.dbclick )
            {
                if ( !item_itr->checkbox_hide_children.changed )
                {
                    item_itr->renaming = 1;
                    
                    item_itr->editbox.name = item_itr->button.name;
                    item_itr->editbox.setFocus();
                }
                
				dbclick = 1;
            }
            
            if ( item_itr->button.pressed )
            {
                active = 1;
                show_indicator = 1;
            }
            
            if ( item_itr->button.coi )
            {
                item_indicator = item_itr;

                coi_side = item_itr->button.coi_side;

                cursor_over_selected = item_itr->selected;

                if ( item_itr->button.pressed )
                    show_indicator = 0;
            }
		}

        // If we are on a "group folder" row and it's children are hidden
        if ( item_itr->type == 1 && item_itr->checkbox_hide_children.checked )
        {
            tree<LDEgui_list_item>::iterator item_parent = items_tree.parent(item_itr);
            
            item_itr = items_tree.next_sibling(item_itr);
            
            if ( !items_tree.is_valid( item_itr ) && !depth )
            {
                item_itr = items_tree.end();
            }
            else
            {
                while ( !items_tree.is_valid( item_itr ) )
                {
                    item_itr = items_tree.next_sibling(item_parent);
                    
                    item_parent = items_tree.parent(item_parent);
                    
                    if ( !items_tree.is_valid(item_parent) && !items_tree.is_valid( item_itr ) )
                    {
                        item_itr = items_tree.end();
                        break;
                    }
                }
            }
        }
        else
            ++item_itr;
        
        ++count;
    }

	glDisable( GL_SCISSOR_TEST );
    
    if ( (items_tree.is_valid(item_indicator) && item_indicator->selected) || !canMoveToIndicator() )
        show_indicator = 0;

    if ( allow_reorder && show_indicator )
    {
        glDisable(GL_TEXTURE_2D);
        glColor3f(1, 1, 1);
        
        if ( coi_side != 2 || item_indicator->type == 0 )
        {
            glPushMatrix();
            
            if ( coi_side != 1 )
                glTranslatef(0, item_height, 0);
            
            glBegin(GL_LINE_STRIP);
                glVertex2i( item_indicator->button.x - 3, item_indicator->button.y - 3);
                glVertex2i( item_indicator->button.x, item_indicator->button.y);
                glVertex2i( item_indicator->button.x + item_indicator->button.size.x, item_indicator->button.y);
                glVertex2i( item_indicator->button.x + item_indicator->button.size.x, item_indicator->button.y+1);
                glVertex2i( item_indicator->button.x, item_indicator->button.y+1);
                glVertex2i( item_indicator->button.x - 3, item_indicator->button.y + 4);
            glEnd();
            
            glPopMatrix();
            
            for ( LDEuint i = 0; i < mouse.size(); ++i )
            {
                if ( mouse[i].left && !mouse[i].down )
                {
                    show_indicator = 0;
                    
                    moveSelection();
                }
            }
        }
        else
        {
            glBegin(GL_LINE_STRIP);
                glVertex2i( item_indicator->button.x, item_indicator->button.y);
                glVertex2i( item_indicator->button.x + item_indicator->button.size.x, item_indicator->button.y);
                glVertex2i( item_indicator->button.x + item_indicator->button.size.x, item_indicator->button.y + item_indicator->button.size.y);
                glVertex2i( item_indicator->button.x, item_indicator->button.y + item_indicator->button.size.y);
                glVertex2i( item_indicator->button.x, item_indicator->button.y);
            glEnd();
            
            for ( LDEuint i = 0; i < mouse.size(); ++i )
            {
                if ( mouse[i].left && !mouse[i].down )
                {
                    show_indicator = 0;
                    
                    moveSelectionToFolder();
                }
            }
        }
        
        glEnable(GL_TEXTURE_2D);
    }
    
	scrollbar.mouse = mouse;
	scrollbar.x = x + size.x - scrollbar.size.x - 1;
	scrollbar.y = y + 1;
	
	scrollbar.size.y = size.y - 2;
	
	scrollbar.test_coi = test_coi;
	scrollbar.draw( cursor, frametime );
	
	if ( scrollbar.changed )
	{
		scroll = -scrollbar.scroll_amount;
	}
	
	if ( scrollbar.active )
		active = 1;
}