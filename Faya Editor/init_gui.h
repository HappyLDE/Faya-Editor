LDEgui_pannel *pannel_menu = new LDEgui_pannel();

LDEgui_menu *main_menu = new LDEgui_menu();
LDEgui_menu_item *menu_file = new LDEgui_menu_item();
LDEgui_button *menu_button_save = new LDEgui_button();
LDEgui_button *menu_button_open = new LDEgui_button();
LDEgui_button *menu_button_export = new LDEgui_button();

LDEgui_menu_item *menu_data = new LDEgui_menu_item();

LDEgui_combobox *combobox_editor_mode = new LDEgui_combobox();
LDEgui_combobox *combobox_editor_zoom = new LDEgui_combobox();

//////////////// VECTOR MODE //////////////////////

// Window Tools : Vector
LDEgui_window *window_tools_vector = new LDEgui_window();
LDEgui_button *button_path_new = new LDEgui_button();
LDEgui_button *button_path_end = new LDEgui_button();
LDEgui_button *button_path_triangulate = new LDEgui_button();

// Window texture atlas list of sprites
LDEgui_window *window_vector_paths_list = new LDEgui_window();
LDEgui_list *list_vector_paths = new LDEgui_list();
LDEgui_button *button_vector_paths_delete = new LDEgui_button();

//////////////// TEXTURE ATLAS MODE (new spritesheet) //////////////////////

// Window Tools : Texture Atlas
LDEgui_window *window_tools_texture_atlas = new LDEgui_window();
LDEgui_button *button_texture_atlas_import_images = new LDEgui_button();
LDEgui_button *button_texture_atlas_spread = new LDEgui_button();
LDEgui_button *button_texture_atlas_save = new LDEgui_button();

LDEgui_text *text_tools_texture_atlas_width = new LDEgui_text();
LDEgui_combobox *combobox_texture_atlas_width = new LDEgui_combobox();

LDEgui_text *text_tools_texture_atlas_height = new LDEgui_text();
LDEgui_combobox *combobox_texture_atlas_height = new LDEgui_combobox();

LDEgui_text *text_tools_texture_atlas_spacing = new LDEgui_text();
LDEgui_combobox *combobox_texture_atlas_spacing = new LDEgui_combobox();

// Window texture atlas list of sprites
LDEgui_window *window_texture_atlas_sprites_list = new LDEgui_window();
LDEgui_list *list_texture_atlas_sprites = new LDEgui_list();
LDEgui_button *button_texture_atlas_sprites_delete = new LDEgui_button();

// Window Texture Atlas
LDEgui_window *window_texture_atlas = new LDEgui_window();
LDEgui_drawable *drawable_texture_atlas = new LDEgui_drawable();

LDEgui_combobox *combobox_texture_atlas_zoom = new LDEgui_combobox();

LDEgui_scrollbar *scrollbar_texture_atlas = new LDEgui_scrollbar();
LDEgui_scrollbar *scrollbar_texture_atlas_horizontal = new LDEgui_scrollbar();

//////////////// SPRITES WORLD EDITOR MODE //////////////////////

LDEgui_window *window_spritesheets = new LDEgui_window();
LDEgui_combobox *combobox_spritesheets = new LDEgui_combobox();
LDEgui_drawable *drawable_spritesheets = new LDEgui_drawable();
LDEgui_scrollbar *scrollbar_spritesheets = new LDEgui_scrollbar();

LDEgui_window *window_sprites_list = new LDEgui_window();
LDEgui_list *list_sprites = new LDEgui_list();

// Sprite pos
LDEgui_text *text_sprite_pos = new LDEgui_text();
LDEgui_editbox* editbox_sprite_pos_x = new LDEgui_editbox();
LDEgui_editbox* editbox_sprite_pos_y = new LDEgui_editbox();

// sprite anchor point
LDEgui_text *text_sprite_ap = new LDEgui_text(); // Anchor point
LDEgui_editbox* editbox_sprite_ap_x = new LDEgui_editbox();
LDEgui_editbox* editbox_sprite_ap_y = new LDEgui_editbox();

// Rotation
LDEgui_text *text_sprite_rot = new LDEgui_text();
LDEgui_editbox* editbox_sprite_rot = new LDEgui_editbox();

// Opacity
LDEgui_text *text_sprite_opacity = new LDEgui_text();
LDEgui_editbox* editbox_sprite_opacity = new LDEgui_editbox();

// Sprite size
LDEgui_text *text_sprite_size = new LDEgui_text();
LDEgui_editbox* editbox_sprite_size_x = new LDEgui_editbox();
LDEgui_editbox* editbox_sprite_size_y = new LDEgui_editbox();
LDEgui_checkbox* checkbox_sprite_size_keep_ratio = new LDEgui_checkbox();

//////////////// SHAPES MANAGEMENT //////////////////////

LDEgui_window *window_shapes_list = new LDEgui_window();
LDEgui_list *list_shapes = new LDEgui_list();
LDEgui_button *button_shapes_delete = new LDEgui_button();

LDEgui_window *window_shape_properties = new LDEgui_window();
LDEgui_text *text_shape_color = new LDEgui_text();
LDEgui_sprite *sprite_shape_color = new LDEgui_sprite();

void init_gui()
{
	texture_atlas_zoom = 1.0;
	
	// Menu
	gui.addPannel( pannel_menu );
    pannel_menu->pos = vec2i( 0, 0 );
    pannel_menu->size = vec2i( app.size.x, 20 );
    pannel_menu->texture = &texture_pannel2;
	
    pannel_menu->uv_up = 0;
    pannel_menu->uv_left = 0;
    pannel_menu->uv_right = 0;
    pannel_menu->uv_down = 5;
	
    pannel_menu->start_up = 0;
    pannel_menu->start_left = 0;
    pannel_menu->start_right = 0;
    pannel_menu->start_down = 5;
    
    pannel_menu->elements.addMenu( main_menu );
    
    main_menu->addItem(menu_file);
    menu_file->button_parent.setText("File");
    
    menu_file->addButton(menu_button_save);
    menu_button_save->setText("Save Project");
    
    menu_file->addButton(menu_button_open);
    menu_button_open->setText("Open Project");
    
    menu_file->addButton(menu_button_export);
    menu_button_export->setText("Export Scene");
    
    //main_menu->addItem(menu_data);
    //menu_data->button_parent.setText("Data");
    
    pannel_menu->elements.addCombobox(combobox_editor_mode);
    combobox_editor_mode->choice_pos = 1; // Alwais place options under the button
    combobox_editor_mode->size.x = 250;
    combobox_editor_mode->pos = vec2i( pannel_menu->size.x - combobox_editor_mode->size.x - 20, 2 );
	combobox_editor_mode->addOption( 3, "Shapes management", 0 );
    combobox_editor_mode->addOption( 2, "Sprites management", 1 );
    combobox_editor_mode->addOption( 0, "Vector editor", 0 );
	combobox_editor_mode->addOption( 1, "New spritesheet", 0 );

    pannel_menu->elements.addCombobox(combobox_editor_zoom);
    combobox_editor_zoom->choice_pos = 1; // Alwais place options under the button
    combobox_editor_zoom->pos = vec2i( pannel_menu->size.x - combobox_editor_zoom->size.x - combobox_editor_mode->size.x - 30, 2 );
	combobox_editor_zoom->addOption( 300, "300%", 0 );
    combobox_editor_zoom->addOption( 250, "250%", 0 );
    combobox_editor_zoom->addOption( 200, "200%", 0 );
    combobox_editor_zoom->addOption( 150, "150%", 0 );
    combobox_editor_zoom->addOption( 100, "100%", 1 );
    combobox_editor_zoom->addOption( 75, "75%", 0 );
    combobox_editor_zoom->addOption( 50, "50%", 0 );
    combobox_editor_zoom->addOption( 25, "25%", 0 );
    
    //////////////// SHAPES MANAGEMENT //////////////////////
    
    /// Window containing triangulated shapes list
	gui.addWindow(window_shapes_list);
	window_shapes_list->title_pos.x = 10;
	window_shapes_list->pos = vec2i( 10, 30 );
	window_shapes_list->size = vec2i( 230, app.size.y - 60 );
	window_shapes_list->title = "Triangulated Shapes";
	window_shapes_list->show_close_button = false;
    window_shapes_list->close();
    
    // Button delete shape
    window_shapes_list->elements.addButton(button_shapes_delete);
    button_shapes_delete->setText("Delete");
    button_shapes_delete->pos = vec2i( 5, window_shapes_list->size.y - 55 );
    button_shapes_delete->lock();
    
    // List of shapes
    window_shapes_list->elements.addList(list_shapes);
	list_shapes->size.x = window_shapes_list->size.x;
	list_shapes->size.y = window_shapes_list->size.y-60;
    list_shapes->allow_group = 0;
    list_shapes->allow_reorder = 0;
    list_shapes->allow_multiple_selection = 0;
    
    /// Window shape properties
    gui.addWindow(window_shape_properties);
	window_shape_properties->title_pos.x = 10;
	window_shape_properties->pos = vec2i( app.size.x - 280, 30 );
	window_shape_properties->size = vec2i( 250, 100 );
	window_shape_properties->title = "Shape properties";
	window_shape_properties->show_close_button = false;
    window_shape_properties->close();
    
    window_shape_properties->elements.addText(text_shape_color);
    text_shape_color->value = "Color:";
    text_shape_color->pos = vec2i( 10, 10 );
    
    window_shape_properties->elements.addSprite(sprite_shape_color);
    sprite_shape_color->color = vec3f( 0, 1, 0 );
    sprite_shape_color->color_border = vec3f( 1, 1, 1 );
    sprite_shape_color->borde_width = 2;
    sprite_shape_color->pos = vec2i( 80, 8 );
    sprite_shape_color->size = vec2i( 40, 20 );
    
    //////////////// SPRITES WORLD EDITOR MODE //////////////////////
    
    // Window containign spritesheets
	gui.addWindow(window_spritesheets);
	window_spritesheets->title_pos.x = 10;
	window_spritesheets->pos = vec2i( 10, 30 );
	window_spritesheets->size = vec2i( 230, app.size.y - 60 );
	window_spritesheets->title = "Spritesheets";
	window_spritesheets->show_close_button = false;
    
    //combobox_spritesheets
    window_spritesheets->elements.addCombobox(combobox_spritesheets);
    combobox_spritesheets->choice_pos = 1; // Alwais place options under the button
    combobox_spritesheets->size.x = window_spritesheets->size.x;
    combobox_spritesheets->button.name = "No Spritesheets";
    
    window_spritesheets->elements.addScrollbar( scrollbar_spritesheets );
	scrollbar_spritesheets->pos = vec2i( window_spritesheets->size.x - 16, 20 );
	scrollbar_spritesheets->size.y = window_spritesheets->size.y-63;
    
    drawable_spritesheets->scene = drawable_spritesheets_scene;
	window_spritesheets->elements.addDrawable( drawable_spritesheets );
    drawable_spritesheets->pos.y = 20;
	drawable_spritesheets->size = vec2i( window_spritesheets->size.x - 16, window_spritesheets->size.y - 63 );
    
    // window containing spritesheeets created in the world
    gui.addWindow(window_sprites_list);
    window_sprites_list->pos = vec2i(app.size.x - 260, 30 );
    window_sprites_list->size = vec2i( 230, app.size.y - 50 );
    window_sprites_list->can_resize = 0;
    window_sprites_list->title = "World Sprites";
    window_sprites_list->show_close_button = false;
    
    window_sprites_list->elements.addList(list_sprites);
	list_sprites->size.x = window_sprites_list->size.x;
	list_sprites->size.y = window_sprites_list->size.y-157;
    
    // Pos of sprite
    window_sprites_list->elements.addText(text_sprite_pos);
    text_sprite_pos->value = "Pos: x      y";
    text_sprite_pos->pos = vec2i( 15, window_sprites_list->size.y-150 );
    
    window_sprites_list->elements.addEditbox(editbox_sprite_pos_x);
    editbox_sprite_pos_x->pos = vec2i( 75, window_sprites_list->size.y-153 );
    editbox_sprite_pos_x->size.x = 50;
    editbox_sprite_pos_x->name = "0";
    
    window_sprites_list->elements.addEditbox(editbox_sprite_pos_y);
    editbox_sprite_pos_y->pos = vec2i( 145, window_sprites_list->size.y-153 );
    editbox_sprite_pos_y->size.x = 50;
    editbox_sprite_pos_y->name = "0";
    
    // Anchor point of sprite
    window_sprites_list->elements.addText(text_sprite_ap);
    text_sprite_ap->value = "APt: x      y";
    text_sprite_ap->pos = vec2i( 15, window_sprites_list->size.y-125 );
    
    window_sprites_list->elements.addEditbox(editbox_sprite_ap_x);
    editbox_sprite_ap_x->pos = vec2i( 75, window_sprites_list->size.y-128 );
    editbox_sprite_ap_x->size.x = 50;
    editbox_sprite_ap_x->name = "0";
    
    window_sprites_list->elements.addEditbox(editbox_sprite_ap_y);
    editbox_sprite_ap_y->pos = vec2i( 145, window_sprites_list->size.y-128 );
    editbox_sprite_ap_y->size.x = 50;
    editbox_sprite_ap_y->name = "0";
    
    // Rotation sprite
    window_sprites_list->elements.addText(text_sprite_rot);
    text_sprite_rot->value = "Angle:      deg";
    text_sprite_rot->pos = vec2i( 10, window_sprites_list->size.y-100 );
    
    window_sprites_list->elements.addEditbox(editbox_sprite_rot);
    editbox_sprite_rot->pos = vec2i( 75, window_sprites_list->size.y-103 );
    editbox_sprite_rot->size.x = 50;
    editbox_sprite_rot->name = "0";
    
    // Opacity sprite
    window_sprites_list->elements.addText(text_sprite_opacity);
    text_sprite_opacity->value = "Opac:";
    text_sprite_opacity->pos = vec2i( 20, window_sprites_list->size.y-75 );
    
    window_sprites_list->elements.addEditbox(editbox_sprite_opacity);
    editbox_sprite_opacity->pos = vec2i( 75, window_sprites_list->size.y-78 );
    editbox_sprite_opacity->size.x = 50;
    editbox_sprite_opacity->name = "0";
    
    // Size of sprite
    window_sprites_list->elements.addText(text_sprite_size);
    text_sprite_size->value = "Size: x      y";
    text_sprite_size->pos = vec2i( 5, window_sprites_list->size.y-50 );
    
    window_sprites_list->elements.addEditbox(editbox_sprite_size_x);
    editbox_sprite_size_x->pos = vec2i( 75, window_sprites_list->size.y-53 );
    editbox_sprite_size_x->size.x = 50;
    editbox_sprite_size_x->name = "0";
    
    window_sprites_list->elements.addEditbox(editbox_sprite_size_y);
    editbox_sprite_size_y->pos = vec2i( 145, window_sprites_list->size.y-53 );
    editbox_sprite_size_y->size.x = 50;
    editbox_sprite_size_y->name = "0";
    
    window_sprites_list->elements.addCheckbox(checkbox_sprite_size_keep_ratio);
    checkbox_sprite_size_keep_ratio->pos = vec2i( 200, window_sprites_list->size.y-49 );
    checkbox_sprite_size_keep_ratio->setCheck( 1 );
    
    //////////////// VECTOR MODE //////////////////////
    
    // Window Tools : Vector
	gui.addWindow(window_tools_vector);
	window_tools_vector->title_pos.x = 10;
	window_tools_vector->pos = vec2i( 10, 35 );
	window_tools_vector->size = vec2i( 100, 400 );
	window_tools_vector->title = "Tools";
	window_tools_vector->can_resize = false;
	window_tools_vector->show_close_button = false;
    window_tools_vector->close();
    
    window_tools_vector->elements.addButton(button_path_new);
    button_path_new->pos = vec2i( 5, 0 );
    button_path_new->setText("New Path");
    
    window_tools_vector->elements.addButton(button_path_end);
    button_path_end->pos = vec2i( 5, 30 );
    button_path_end->setText("End Path");
    
    window_tools_vector->elements.addButton(button_path_triangulate);
    button_path_triangulate->setText("Triang.");
    button_path_triangulate->size.y = 30;
    button_path_triangulate->pos = vec2i( window_tools_vector->size.x/2-button_path_triangulate->size.x/2, 90 );
    
    // Window Texture Atlas Creation : List of sprites
	gui.addWindow(window_vector_paths_list);
    window_vector_paths_list->title_pos.x = 10;
	window_vector_paths_list->pos = vec2i( 1000, 35 );
	window_vector_paths_list->size = vec2i( 165, 550 );
	window_vector_paths_list->min_size = vec2i( 100, 100 );
	window_vector_paths_list->title = "Vertex Paths";
	window_vector_paths_list->close();
    window_vector_paths_list->show_close_button = false;
    
	window_vector_paths_list->elements.addList(list_vector_paths);
	list_vector_paths->size.x = window_vector_paths_list->size.x;
	list_vector_paths->size.y = window_vector_paths_list->size.y-60;
	list_vector_paths->allow_group = 0;
    list_vector_paths->allow_reorder = 0;
    list_vector_paths->allow_multiple_selection = 0;
    
	window_vector_paths_list->elements.addButton(button_vector_paths_delete);
	button_vector_paths_delete->pos.x = 8;
	button_vector_paths_delete->pos.y = window_vector_paths_list->size.y-54;
	button_vector_paths_delete->setText("Delete");
	button_vector_paths_delete->lock();
    
    //////////////// ATLAS MODE //////////////////////
    
	//// Fentres
	
	// Window Texture Atlas Creation : List of sprites
	gui.addWindow(window_texture_atlas_sprites_list);
    window_texture_atlas_sprites_list->title_pos.x = 10;
	window_texture_atlas_sprites_list->pos = vec2i( 830, 35 );
	window_texture_atlas_sprites_list->size = vec2i( 300, 550 );
	window_texture_atlas_sprites_list->min_size = vec2i( 100, 100 );
	window_texture_atlas_sprites_list->title = "Frames";
	window_texture_atlas_sprites_list->show_close_button = false;
    
	window_texture_atlas_sprites_list->elements.addList(list_texture_atlas_sprites);
	list_texture_atlas_sprites->size.x = window_texture_atlas_sprites_list->size.x;
	list_texture_atlas_sprites->size.y = window_texture_atlas_sprites_list->size.y-60;
	list_texture_atlas_sprites->allow_group = 0;
    list_texture_atlas_sprites->allow_reorder = 0;
    
	window_texture_atlas_sprites_list->elements.addButton(button_texture_atlas_sprites_delete);
	button_texture_atlas_sprites_delete->pos.x = 8;
	button_texture_atlas_sprites_delete->pos.y = window_texture_atlas_sprites_list->size.y-54;
	button_texture_atlas_sprites_delete->setText("Delete");
	button_texture_atlas_sprites_delete->lock();
	
    window_texture_atlas_sprites_list->close();
    
	/// Window Texture Atlas
	gui.addWindow(window_texture_atlas);
    window_texture_atlas->title_pos.x = 10;
	window_texture_atlas->title_scissor_right = 105;
	window_texture_atlas->pos = vec2i( 200, 35 );
	window_texture_atlas->size = vec2i( 600, 400 );
	window_texture_atlas->min_size = vec2i( 400, 150 );
	window_texture_atlas->title = "Spritesheet";
	window_texture_atlas->show_close_button = false;
    
	drawable_texture_atlas->scene = drawable_texture_atlas_scene;
	window_texture_atlas->elements.addDrawable( drawable_texture_atlas );
	drawable_texture_atlas->size = vec2i( window_texture_atlas->size.x - 16, window_texture_atlas->size.y - 43 );
	
	// zoom
	window_texture_atlas->elements.addCombobox(combobox_texture_atlas_zoom);
	combobox_texture_atlas_zoom->pos = vec2i( window_texture_atlas->size.x - combobox_texture_atlas_zoom->size.x - 20, -20 );
	combobox_texture_atlas_zoom->addOption( 20, "20%", 0 );
	combobox_texture_atlas_zoom->addOption( 40, "40%", 0 );
	combobox_texture_atlas_zoom->addOption( 60, "60%", 0 );
	combobox_texture_atlas_zoom->addOption( 80, "80%", 0 );
	combobox_texture_atlas_zoom->addOption( 100, "100%", 1 );
	combobox_texture_atlas_zoom->addOption( 150, "150%", 0 );
	combobox_texture_atlas_zoom->addOption( 200, "200%", 0 );
	combobox_texture_atlas_zoom->addOption( 250, "250%", 0 );
	combobox_texture_atlas_zoom->addOption( 300, "300%", 0 );
	
	window_texture_atlas->elements.addScrollbar( scrollbar_texture_atlas );
	scrollbar_texture_atlas->pos = vec2i( window_texture_atlas->size.x - 16, 0 );
	scrollbar_texture_atlas->size.y = window_texture_atlas->size.y-43;
	scrollbar_texture_atlas->scroll_height = (texture_atlas_size.y*texture_atlas_zoom)+20;
	
	window_texture_atlas->elements.addScrollbar( scrollbar_texture_atlas_horizontal );
	scrollbar_texture_atlas_horizontal->setSide(1);
	scrollbar_texture_atlas_horizontal->pos.y = window_texture_atlas->size.y-43;
	scrollbar_texture_atlas_horizontal->size.x = window_texture_atlas->size.x - 16;
	scrollbar_texture_atlas_horizontal->scroll_height = (texture_atlas_size.x*texture_atlas_zoom)+20;
	
    window_texture_atlas->close();
    
	/// Window Tools : Texture Atlas
	gui.addWindow(window_tools_texture_atlas);
	window_tools_texture_atlas->title_pos.x = 10;
	window_tools_texture_atlas->pos = vec2i( 10, 35 );
	window_tools_texture_atlas->size = vec2i( 170, 290 );
	window_tools_texture_atlas->min_size = vec2i( 150, 400 );
	window_tools_texture_atlas->title = "Tools";
	window_tools_texture_atlas->can_resize = false;
	window_tools_texture_atlas->show_close_button = false;
	
	window_tools_texture_atlas->elements.addButton( button_texture_atlas_import_images );
	button_texture_atlas_import_images->setText("Import images");
	button_texture_atlas_import_images->pos = vec2i( 5, 0 );
	button_texture_atlas_import_images->size.x = window_tools_texture_atlas->size.x - 10;
	
    window_tools_texture_atlas->elements.addButton( button_texture_atlas_spread );
	button_texture_atlas_spread->setText("Spread");
	button_texture_atlas_spread->size = vec2i( 120, 60 );
    button_texture_atlas_spread->pos = vec2i( window_tools_texture_atlas->size.x/2 - button_texture_atlas_spread->size.x/2, 160 );
    
	window_tools_texture_atlas->elements.addButton( button_texture_atlas_save );
	button_texture_atlas_save->setText("Save sheet");
	button_texture_atlas_save->pos = vec2i( 5, window_tools_texture_atlas->size.y - 52 );
	button_texture_atlas_save->size.x = window_tools_texture_atlas->size.x - 10;
	
	// texture atlas text width and height
	window_tools_texture_atlas->elements.addText( text_tools_texture_atlas_width );
	text_tools_texture_atlas_width->value = "Width:";
	text_tools_texture_atlas_width->pos = vec2i( 24, 50 );
	
	window_tools_texture_atlas->elements.addCombobox(combobox_texture_atlas_width);
	combobox_texture_atlas_width->pos = vec2i( 85, 50 );
	
	combobox_texture_atlas_width->addOption( 128, "128px", 0 );
	combobox_texture_atlas_width->addOption( 256, "256px", 0 );
	combobox_texture_atlas_width->addOption( 512, "512px", 1 );
	combobox_texture_atlas_width->addOption( 1024, "1024px", 0 );
	combobox_texture_atlas_width->addOption( 2048, "2048px", 0 );
	
	window_tools_texture_atlas->elements.addText( text_tools_texture_atlas_height );
	text_tools_texture_atlas_height->value = "Height:";
	text_tools_texture_atlas_height->pos = vec2i( 14, 80 );
	
	window_tools_texture_atlas->elements.addCombobox(combobox_texture_atlas_height);
	combobox_texture_atlas_height->pos = vec2i( 85, 80 );
	
	combobox_texture_atlas_height->addOption( 128, "128px", 0 );
	combobox_texture_atlas_height->addOption( 256, "256px", 1 );
	combobox_texture_atlas_height->addOption( 512, "512px", 0 );
	combobox_texture_atlas_height->addOption( 1024, "1024px", 0 );
	combobox_texture_atlas_height->addOption( 2048, "2048px", 0 );
	
	window_tools_texture_atlas->elements.addText( text_tools_texture_atlas_spacing );
	text_tools_texture_atlas_spacing->value = "Spacing:";
	text_tools_texture_atlas_spacing->pos = vec2i( 4, 110 );
	
	window_tools_texture_atlas->elements.addCombobox(combobox_texture_atlas_spacing);
	combobox_texture_atlas_spacing->pos = vec2i( 85, 110 );
	
	combobox_texture_atlas_spacing->addOption( 0, "0px", 1 );
	combobox_texture_atlas_spacing->addOption( 1, "1px", 0 );
	combobox_texture_atlas_spacing->addOption( 2, "2px", 0 );
	combobox_texture_atlas_spacing->addOption( 3, "3px", 0 );
	combobox_texture_atlas_spacing->addOption( 4, "4px", 0 );
    
    window_tools_texture_atlas->close();
}