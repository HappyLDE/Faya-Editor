LDEldet texture_window,
        texture_window_inactive,

		texture_window_close,
		texture_window_close_hover,
		texture_window_close_pressed,

        texture_pannel,
        texture_pannel2,

		texture_list,
		texture_list_item_selected,

        texture_list_checkbox,
        texture_list_checkbox_checked,

        texture_list_checkbox_folder_hide_children,
        texture_list_checkbox_folder_hide_children_checked,

        texture_list_traits,

        texture_folder,

		texture_scrollbar_button_up,
		texture_scrollbar_button_up_hover,
		texture_scrollbar_button_up_pressed,

		texture_scrollbar_button_down,
		texture_scrollbar_button_down_hover,
		texture_scrollbar_button_down_pressed,
		
		texture_scrollbar_middle,

		texture_scrollbar_button_middle,
		texture_scrollbar_button_middle_hover,
		texture_scrollbar_button_middle_pressed,

		//h
		texture_scrollbar_h_button_up,
		texture_scrollbar_h_button_up_hover,
		texture_scrollbar_h_button_up_pressed,

		texture_scrollbar_h_button_down,
		texture_scrollbar_h_button_down_hover,
		texture_scrollbar_h_button_down_pressed,

		texture_scrollbar_h_middle,

		texture_scrollbar_h_button_middle,
		texture_scrollbar_h_button_middle_hover,
		texture_scrollbar_h_button_middle_pressed,

		texture_empty,

        texture_button_rel,
        texture_button_coi,
        texture_button_pre,
        texture_button_locked,

		texture_combobox,
		texture_combobox_hover,
		texture_combobox_pressed,

        texture_checkbox,
        texture_checkbox_hover,
        texture_checkbox_pressed,
        texture_checkbox_checked,

		texture_editbox,
		texture_editbox_hover,
		texture_editbox_active,

        texture_menu_button_rel,
        texture_menu_button_coi,
        texture_menu_button_pre,
        texture_menu_button_locked,

        texture_button_window_resize_rel;

LDEldef font_windowTitle,
        font_elements;

LDEldet texture_transf_tool;

void load_gui_theme( string path )
{
    // Transformation tool
    texture_transf_tool.load(path+"transf_tool.ldet");
    texture_transf_tool.opengl(0);
    transf_tool.image = &texture_transf_tool;
    
    texture_folder.load(path+"folder.ldet");
	texture_folder.opengl(0);
    gui.texture_folder = &texture_folder;
    
	texture_atlas_bg.load(path+"texture_atlas_bg.ldet");
	texture_atlas_bg.opengl(0);
	
	texture_shadow.load(path+"shadow.ldet");
	texture_shadow.opengl(0);
	
    /// WINDOW THEME ///
    texture_window.load(path+"window.ldet");
    texture_window.opengl(0);
    gui.texture_window = &texture_window;
	
    texture_window_inactive.load(path+"window_inactive.ldet");
    texture_window_inactive.opengl(0);
    gui.texture_window_inactive = &texture_window_inactive;

	// button_close
	texture_window_close.load(path+"window_close.ldet");
	texture_window_close.opengl(0);
	gui.texture_window_close = &texture_window_close;
	
	texture_window_close_hover.load(path+"window_close_hover.ldet");
	texture_window_close_hover.opengl(0);
	gui.texture_window_close_hover = &texture_window_close_hover;
	
	texture_window_close_pressed.load(path+"window_close_pressed.ldet");
	texture_window_close_pressed.opengl(0);
	gui.texture_window_close_pressed = &texture_window_close_pressed;

    /// PANNEL THEME ///
    texture_pannel.load(path+"menu_background.ldet");
    texture_pannel.opengl(0);
    gui.texture_pannel = &texture_pannel;

	/// list
	texture_list.load(path+"list.ldet");
	texture_list.opengl(0);
    gui.texture_list = &texture_list;
	
	texture_empty.load(path+"empty.ldet");
	texture_empty.opengl(0);
    gui.texture_list_item = &texture_empty;
	
	texture_list_item_selected.load(path+"list_item_selected.ldet");
	texture_list_item_selected.opengl(0);
    gui.texture_list_item_selected = &texture_list_item_selected;
	
    texture_list_checkbox.load(path+"list_checkbox.ldet");
	texture_list_checkbox.opengl(0);
	gui.texture_list_checkbox = &texture_list_checkbox;
    
    texture_list_checkbox_checked.load(path+"list_checkbox_checked.ldet");
	texture_list_checkbox_checked.opengl(0);
	gui.texture_list_checkbox_checked = &texture_list_checkbox_checked;
    
    texture_list_checkbox_folder_hide_children.load(path+"list_checkbox_hide_children.ldet");
	texture_list_checkbox_folder_hide_children.opengl(0);
	gui.texture_list_checkbox_folder_hide_children = &texture_list_checkbox_folder_hide_children;
    
    texture_list_checkbox_folder_hide_children_checked.load(path+"list_checkbox_hide_children_checked.ldet");
	texture_list_checkbox_folder_hide_children_checked.opengl(0);
	gui.texture_list_checkbox_folder_hide_children_checked = &texture_list_checkbox_folder_hide_children_checked;
    
    texture_list_traits.load(path+"liste_traits.ldet");
	texture_list_traits.opengl(0);
	gui.texture_list_traits = &texture_list_traits;
    
	// scrollbar
	texture_scrollbar_button_up.load(path+"scrollbar_button_up.ldet");
	texture_scrollbar_button_up.opengl(0);
    gui.texture_scrollbar_button_up = &texture_scrollbar_button_up;
	
	texture_scrollbar_button_up_hover.load(path+"scrollbar_button_up_hover.ldet");
	texture_scrollbar_button_up_hover.opengl(0);
    gui.texture_scrollbar_button_up_hover = &texture_scrollbar_button_up_hover;
	
	texture_scrollbar_button_up_pressed.load(path+"scrollbar_button_up_pressed.ldet");
	texture_scrollbar_button_up_pressed.opengl(0);
    gui.texture_scrollbar_button_up_pressed = &texture_scrollbar_button_up_pressed;
	
	texture_scrollbar_button_down.load(path+"scrollbar_button_down.ldet");
	texture_scrollbar_button_down.opengl(0);
    gui.texture_scrollbar_button_down = &texture_scrollbar_button_down;
	
	texture_scrollbar_button_down_hover.load(path+"scrollbar_button_down_hover.ldet");
	texture_scrollbar_button_down_hover.opengl(0);
    gui.texture_scrollbar_button_down_hover = &texture_scrollbar_button_down_hover;
	
	texture_scrollbar_button_down_pressed.load(path+"scrollbar_button_down_pressed.ldet");
	texture_scrollbar_button_down_pressed.opengl(0);
    gui.texture_scrollbar_button_down_pressed = &texture_scrollbar_button_down_pressed;
	
	texture_scrollbar_middle.load(path+"scrollbar_middle.ldet");
	texture_scrollbar_middle.opengl(0);
    gui.texture_scrollbar_middle = &texture_scrollbar_middle;
	
	texture_scrollbar_button_middle.load(path+"scrollbar_button_middle.ldet");
	texture_scrollbar_button_middle.opengl(0);
    gui.texture_scrollbar_button_middle = &texture_scrollbar_button_middle;
	
	texture_scrollbar_button_middle_hover.load(path+"scrollbar_button_middle_hover.ldet");
	texture_scrollbar_button_middle_hover.opengl(0);
    gui.texture_scrollbar_button_middle_hover = &texture_scrollbar_button_middle_hover;
	
	texture_scrollbar_button_middle_pressed.load(path+"scrollbar_button_middle_pressed.ldet");
	texture_scrollbar_button_middle_pressed.opengl(0);
    gui.texture_scrollbar_button_middle_pressed = &texture_scrollbar_button_middle_pressed;
	
	//h
	texture_scrollbar_h_button_up.load(path+"scrollbar_h_button_up.ldet");
	texture_scrollbar_h_button_up.opengl(0);
	gui.texture_scrollbar_h_button_up = &texture_scrollbar_h_button_up;
	
	texture_scrollbar_h_button_up_hover.load(path+"scrollbar_h_button_up_hover.ldet");
	texture_scrollbar_h_button_up_hover.opengl(0);
	gui.texture_scrollbar_h_button_up_hover = &texture_scrollbar_h_button_up_hover;
	
	texture_scrollbar_h_button_up_pressed.load(path+"scrollbar_h_button_up_pressed.ldet");
	texture_scrollbar_h_button_up_pressed.opengl(0);
	gui.texture_scrollbar_h_button_up_pressed = &texture_scrollbar_h_button_up_pressed;
	
	texture_scrollbar_h_button_down.load(path+"scrollbar_h_button_down.ldet");
	texture_scrollbar_h_button_down.opengl(0);
	gui.texture_scrollbar_h_button_down = &texture_scrollbar_h_button_down;
	
	texture_scrollbar_h_button_down_hover.load(path+"scrollbar_h_button_down_hover.ldet");
	texture_scrollbar_h_button_down_hover.opengl(0);
	gui.texture_scrollbar_h_button_down_hover = &texture_scrollbar_h_button_down_hover;
	
	texture_scrollbar_h_button_down_pressed.load(path+"scrollbar_h_button_down_pressed.ldet");
	texture_scrollbar_h_button_down_pressed.opengl(0);
	gui.texture_scrollbar_h_button_down_pressed = &texture_scrollbar_h_button_down_pressed;
	
	texture_scrollbar_h_middle.load(path+"scrollbar_h_middle.ldet");
	texture_scrollbar_h_middle.opengl(0);
	gui.texture_scrollbar_h_middle = &texture_scrollbar_h_middle;
	
	texture_scrollbar_h_button_middle.load(path+"scrollbar_h_button_middle.ldet");
	texture_scrollbar_h_button_middle.opengl(0);
	gui.texture_scrollbar_h_button_middle = &texture_scrollbar_h_button_middle;
	
	texture_scrollbar_h_button_middle_hover.load(path+"scrollbar_h_button_middle_hover.ldet");
	texture_scrollbar_h_button_middle_hover.opengl(0);
	gui.texture_scrollbar_h_button_middle_hover = &texture_scrollbar_h_button_middle_hover;
	
	texture_scrollbar_h_button_middle_pressed.load(path+"scrollbar_h_button_middle_pressed.ldet");
	texture_scrollbar_h_button_middle_pressed.opengl(0);
	gui.texture_scrollbar_h_button_middle_pressed = &texture_scrollbar_h_button_middle_pressed;
	
	// Combobox
	texture_combobox.load(path+"combobox.ldet");
	texture_combobox.opengl(0);
	gui.texture_combobox = &texture_combobox;
	
	texture_combobox_hover.load(path+"combobox_hover.ldet");
	texture_combobox_hover.opengl(0);
	gui.texture_combobox_hover = &texture_combobox_hover;
	
	texture_combobox_pressed.load(path+"combobox_pressed.ldet");
	texture_combobox_pressed.opengl(0);
	gui.texture_combobox_pressed = &texture_combobox_pressed;
	
    // Checkbox
	texture_checkbox.load(path+"checkbox.ldet");
	texture_checkbox.opengl(0);
	gui.texture_checkbox = &texture_checkbox;
    
	texture_checkbox_hover.load(path+"checkbox_hover.ldet");
	texture_checkbox_hover.opengl(0);
	gui.texture_checkbox_hover = &texture_checkbox_hover;
	
	texture_checkbox_pressed.load(path+"checkbox_pressed.ldet");
	texture_checkbox_pressed.opengl(0);
	gui.texture_checkbox_pressed = &texture_checkbox_pressed;
    
    texture_checkbox_checked.load(path+"checkbox_checked.ldet");
	texture_checkbox_checked.opengl(0);
	gui.texture_checkbox_checked = &texture_checkbox_checked;
    
	/// editbox
	texture_editbox.load(path+"editbox.ldet");
	texture_editbox.opengl(0);
    gui.texture_editbox = &texture_editbox;
	
	texture_editbox_hover.load(path+"editbox_hover.ldet");
	texture_editbox_hover.opengl(0);
    gui.texture_editbox_hover = &texture_editbox_hover;

	texture_editbox_active.load(path+"editbox_active.ldet");
	texture_editbox_active.opengl(0);
    gui.texture_editbox_active = &texture_editbox_active;
	
    /// BUTTON DEFAULT TEXTURE ///
    texture_button_rel.load(path+"bouton.ldet");
    texture_button_rel.opengl(0);
    gui.texture_button_rel = &texture_button_rel;

    texture_button_coi.load(path+"bouton_hover.ldet");
    texture_button_coi.opengl(0);
    gui.texture_button_coi = &texture_button_coi;

    texture_button_pre.load(path+"bouton_pressed.ldet");
    texture_button_pre.opengl(0);
    gui.texture_button_pre = &texture_button_pre;

    gui.texture_button_locked = &texture_button_pre;

     /// MENU BUTTON DEFAULT TEXTURE ///
    texture_menu_button_rel.load(path+"bouton_menu.ldet");
    texture_menu_button_rel.opengl(0);
    gui.texture_menu_button_rel = &texture_menu_button_rel;

    texture_menu_button_coi.load(path+"bouton_menu_hover.ldet");
    texture_menu_button_coi.opengl(0);
    gui.texture_menu_button_coi = &texture_menu_button_coi;

    texture_menu_button_pre.load(path+"bouton_menu_pressed.ldet");
    texture_menu_button_pre.opengl(0);
    gui.texture_menu_button_pre = &texture_menu_button_pre;

    gui.texture_menu_button_locked = &texture_menu_button_pre;

    /// BUTTON WINDOW RESIZE THEME ////
    texture_button_window_resize_rel.load(path+"bouton_resize.ldet");
    texture_button_window_resize_rel.opengl(0);
    gui.texture_button_window_resize_rel = &texture_button_window_resize_rel;

    /// FONTS
    font_windowTitle.load( path+"courbd.ldef" );
    gui.font_window_title = &font_windowTitle;

	font_elements.correction = vec2i( -2, -3 );
    font_elements.load( path+"cour.ldef" );
    gui.font_elements = &font_elements;

    // Default windows title position according to the default theme
    gui.window_title_pos = vec2i( 12, -2 );

    texture_pannel2.load(path+"panneau.ldet");
    texture_pannel2.opengl(0);
}
