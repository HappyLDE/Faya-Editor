//
//  OpenGLView.m
//  Faya Editor
//
//  Created by Dorin Grigore on 6/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "OpenGLView.h"

#include "tree.hh"

using namespace std;

LDEint  FAYA_VERSION = 1,
        num_selected_sprites = 0;

LDEfloat transf_tool_rot = 0;
vec2i   transf_tool_pos,
        transf_tool_size;
LDEtransf_tool transf_tool;

vec2i camera_pos;
LDEfloat camera_zoom = 1;
LDEuint editor_mode = 0; // 0 vector   1 atlas    2 sprites

std::vector<VectorPaths>::iterator path_itr_selected;
vector<VectorPaths>paths;
vector<Shapes>shapes;
vector<Spritesheet>spritesheets; /// These are the big images containing small images as sheets
                                 /// AND it's won sprite batch node
vector<LDEuint>spritesheets_zorder;

vec2i sprite_drag_size_temp;
Sprite sprite_drag; // When we drag a sprite from window to world, use this to show it

LDEcamera camera, camera2D;
LDE app;
LDEgui gui;

string  project_path,
project_name;

vector<TextureAtlasCreation_item>texture_atlas_creation_item;

LDEfloat texture_atlas_zoom;
LDEldet texture_atlas_bg,
texture_shadow;

vec2i texture_atlas_pos = vec2i( 10, 10 );
vec2i texture_atlas_size = vec2i( 512, 256 );
vec2i texture_atlas_uv; // Background damier

// Hmm
#include "load_gui_theme.h"
#include "init_gui.h"

void saveFile(string filename)
{
    project_path = LDEpathOfFile(filename);
    project_name = LDEnameOfFile(filename);
    
    ofstream file;
    
    file.open(filename.c_str());
    
    // File Version
    file.write( (char*)&FAYA_VERSION, sizeof(LDEint) );
    
    // Editor behavior
    file.write( (char*)&app.size.x, sizeof(LDEint) );
    file.write( (char*)&app.size.y, sizeof(LDEint) );
    
    file.write( (char*)&camera_pos.x, sizeof(LDEfloat) );
    file.write( (char*)&camera_pos.y, sizeof(LDEfloat) );
    file.write( (char*)&camera_zoom, sizeof(LDEfloat) );
    
    file.write( (char*)&editor_mode, sizeof(bool) );
    
    // Project data
    LDEuint paths_size = paths.size();
    file.write( (char*)&paths_size, sizeof(LDEuint) );
    
    for ( LDEuint i = 0; i < paths_size; ++i )
    {
        file.write( (char*)&paths[i].selected_vertex, sizeof(LDEint) );
        file.write( (char*)&paths[i].active, sizeof(bool) );
        
        LDEuint vertex_size = paths[i].vertex.size();
        file.write( (char*)&vertex_size, sizeof(LDEuint) );
        
        for ( LDEuint v = 0; v < vertex_size; ++v )
        {
            file.write( (char*)&paths[i].vertex[v].x, sizeof(LDEint) );
            file.write( (char*)&paths[i].vertex[v].y, sizeof(LDEint) );
        }
    }
}

void openFile(string filename)
{
    project_path = LDEpathOfFile(filename);
    project_name = LDEnameOfFile(filename);
    
    ifstream file;
    
    file.open(filename.c_str());
    
    LDEint read_FAYA_VERSION = 0;
    
    // File Version
    file.read( (char*)&read_FAYA_VERSION, sizeof(LDEint) );
    
    // Editor behavior
    file.read( (char*)&app.size.x, sizeof(LDEint) );
    file.read( (char*)&app.size.y, sizeof(LDEint) );
    
    //[[self window] setContentSize:NSMakeSize(app.size.x,app.size.y)];
    
    file.read( (char*)&camera_pos.x, sizeof(LDEfloat) );
    file.read( (char*)&camera_pos.y, sizeof(LDEfloat) );
    file.read( (char*)&camera_zoom, sizeof(LDEfloat) );
    
    file.read( (char*)&editor_mode, sizeof(bool) );
    
    switchEditorMode( editor_mode );
    
    paths.erase( paths.begin(), paths.end() );
    list_vector_paths->erase();
    
    // Project data
    LDEuint paths_size = 0;
    file.read( (char*)&paths_size, sizeof(LDEuint) );
    
    if ( paths_size )
    {
        button_vector_paths_delete->unlock();
        
        for ( LDEuint i = 0; i < paths_size; ++i )
        {
            VectorPaths path_temp;
            paths.push_back(path_temp);
            
            LDEuint path_id = paths.size()-1;
            
            list_vector_paths->addItem(path_id, "Path "+LDEnts(path_id) );
            
            file.read( (char*)&paths[path_id].selected_vertex, sizeof(LDEint) );
            file.read( (char*)&paths[path_id].active, sizeof(bool) );
            
            //if ( paths[path_id].active )
            //    list_vector_paths->select( path_id, 0 );
            
            LDEuint vertex_size = 0;
            file.read( (char*)&vertex_size, sizeof(LDEuint) );
            
            for ( LDEuint v = 0; v < vertex_size; ++v )
            {
                vec2i vertex_pos;
                
                file.read( (char*)&vertex_pos.x, sizeof(LDEint) );
                file.read( (char*)&vertex_pos.y, sizeof(LDEint) );
                
                paths[path_id].addVertex( vertex_pos );
            }
        }
    }
}

void switchEditorMode(LDEuint mode)
{
    // If we change mode and were in spritesheet creationmode
    if ( editor_mode == 1 && mode != 1 )
    {
        texture_atlas_creation_item.erase( texture_atlas_creation_item.begin(), texture_atlas_creation_item.end() );
        list_texture_atlas_sprites->erase();
		button_texture_atlas_sprites_delete->lock();
    }
    
    switch ( mode )
    {
            // go to Vector Mode
        case 0:
        {
            window_tools_texture_atlas->close();
            window_texture_atlas_sprites_list->close();
            window_texture_atlas->close();
            window_spritesheets->close();
            window_sprites_list->close();
            
            window_shapes_list->close();
            
            window_tools_vector->open();
            window_vector_paths_list->open();
            
            editor_mode = 0;
            
            combobox_editor_mode->select(0);
            
            break;
        }
            
            // go to Spritesheet Mode
        case 1:
        {
            window_tools_vector->close();
            window_vector_paths_list->close();
            window_spritesheets->close();
            window_sprites_list->close();
            
            window_shapes_list->close();
            
            window_tools_texture_atlas->open();
            window_texture_atlas_sprites_list->open();
            window_texture_atlas->open();
            
            editor_mode = 1;
            
            combobox_editor_mode->select(1);
            
            break;
        }
            
            // go to World Edit Mode
        case 2:
        {
            window_tools_texture_atlas->close();
            window_texture_atlas_sprites_list->close();
            window_texture_atlas->close();
            
            window_tools_vector->close();
            window_vector_paths_list->close();
            
            window_shapes_list->close();
            
            window_spritesheets->open();
            window_sprites_list->open();
            editor_mode = 2;
            
            combobox_editor_mode->select(2);
            
            break;
        }
            
            // go to shapes management
        case 3:
        {
            window_tools_texture_atlas->close();
            window_texture_atlas_sprites_list->close();
            window_texture_atlas->close();
            
            window_tools_vector->close();
            window_vector_paths_list->close();
            
            window_spritesheets->close();
            window_sprites_list->close();
            
            window_shapes_list->open();
            
            combobox_editor_mode->select(3);
            
            break;
        }
    }
}

// This draw (on the gui window) the spritesheet's list of frames (small images)
void drawable_spritesheets_scene(vec2i mypos, vec2i mysize, bool mytest_coi, LDEfloat myframetime )
{
    // If window is on top : interact with mouse
    if ( mytest_coi && app.mouse.size() )
    {
        LDEfloat scroll_y = 0;
        
        // For any mouse event
        for ( LDEuint i = 0; i < app.mouse.size(); ++i )
        {
            // Scroll
            if ( app.mouse[i].scroll_y != 0 )
                scroll_y += app.mouse[i].scroll_y;
            
            // Swipe
            if ( app.mouse[i].swipe_y != 0 )
            {
                if ( app.mouse[i].swipe_y == -1 )
                    scrollbar_spritesheets->setPercent( 0 );
                else
                    scrollbar_spritesheets->setPercent( 1 );
            }
        }
        
        if ( scroll_y != 0 )
        {
            LDEfloat percent_y = scrollbar_spritesheets->percent + (scroll_y / 100);
            
            if ( percent_y > 1 )
                percent_y = 1;
            else if ( percent_y < 0 )
                percent_y = 0;
            
            scrollbar_spritesheets->setPercent( percent_y );
        }
    }
    
    glEnable(GL_SCISSOR_TEST);
	glEnable(GL_TEXTURE_2D);
	glScissor( mypos.x, app.size.y - (mypos.y+mysize.y), mysize.x, mysize.y );
	
	glPushMatrix();
    glTranslatef( mypos.x, mypos.y - scrollbar_spritesheets->scroll_amount, 0);
    
    // If spritesheets exists
	if ( spritesheets.size() )
    {
        LDEuint i = combobox_spritesheets->key();
        
        spritesheets[i].window_pos.x = mypos.x;
        spritesheets[i].window_pos.y = mypos.y - scrollbar_spritesheets->scroll_amount;
        spritesheets[i].cursor_pos = app.cursor;
        spritesheets[i].test_coi = mytest_coi;
        spritesheets[i].mouse = app.mouse;
        spritesheets[i].draw();
        
        // If we are using one of the spritesheet's frame on this window
        if ( spritesheets[i].used )
        {
            // Stop moving the window
            window_spritesheets->move = 0;
            
            // If we are actually draging the sprite, show one temporary sprite under the cursor
            if ( spritesheets[i].selected > -1 && spritesheets[i].mouse_down )
            {
                sprite_drag.image_id = spritesheets[i].image.id;
                sprite_drag.image_size = spritesheets[i].image.size;
                sprite_drag.name = spritesheets[i].frames[spritesheets[i].selected].name;
                sprite_drag.texture_uv = vec4i( spritesheets[i].frames[spritesheets[i].selected].pos.x, spritesheets[i].frames[spritesheets[i].selected].pos.y,
                                               spritesheets[i].frames[spritesheets[i].selected].size.x, spritesheets[i].frames[spritesheets[i].selected].size.y );
                sprite_drag.size = spritesheets[i].frames[spritesheets[i].selected].size;
                sprite_drag.size_100 = spritesheets[i].frames[spritesheets[i].selected].size_100;
                
                spritesheets[i].spriteBatchNode.deselect();
            }
        }
        
        //////////////////////////////////////////////////////////////////////////////////////////
        //////////////// Ajout d'un sprite dans le monde /////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////
        if ( sprite_drag.size.x && !spritesheets[i].mouse_down )
        {
            // If we release the drag on the world (not on any gui window), create the sprite!
            if ( gui.unused )
            {
                sprite_drag.pos.x = (LDEfloat)(app.cursor.x)/camera_zoom - camera_pos.x;
                sprite_drag.pos.y = (LDEfloat)(app.cursor.y)/camera_zoom - camera_pos.y;
                sprite_drag.offset = sprite_drag.size/2;
                sprite_drag.selected = 1;
                
                // Update sprite properties panel
                editbox_sprite_pos_x->name = LDEnts(sprite_drag.pos.x);
                editbox_sprite_pos_y->name = LDEnts(-sprite_drag.pos.y);
                
                editbox_sprite_ap_x->name = LDEnts(sprite_drag.offset.x);
                editbox_sprite_ap_y->name = LDEnts(sprite_drag.offset.y);
                
                editbox_sprite_size_x->name = LDEnts(sprite_drag.size.x);
                editbox_sprite_size_y->name = LDEnts(sprite_drag.size.y);
                
                transf_tool_pos = sprite_drag.pos;
                transf_tool_size = sprite_drag.size;
                transf_tool_rot = 0;
                
                // Add the sprite in the world
                spritesheets[i].spriteBatchNode.sprites.push_back( sprite_drag );
                
                LDEint sprite_id = spritesheets[i].spriteBatchNode.sprites.size()-1;
                tree<LDEgui_list_item>::iterator item_sprite = list_sprites->addItemTo( spritesheets[i].item_group, sprite_id, sprite_drag.name+LDEnts(sprite_id) );
                
                item_sprite->item_group_parent = spritesheets[i].item_group;
                item_sprite->can_move = 3; // Can only move within the item_group_parent folder (can not be dragged outside)
                
                // Move it on top
                tree<LDEgui_list_item>::sibling_iterator item_sprite_to = list_sprites->items_tree.begin(spritesheets[i].item_group);
                list_sprites->items_tree.move_before( item_sprite_to, item_sprite );
                
                list_sprites->select( item_sprite, 0);
                
                transf_tool.reset();
            }
            
            sprite_drag.image_id = 0;
            sprite_drag.image_size.reset();
            sprite_drag.texture_uv.reset();
            sprite_drag.size.reset();
        }
    }
	
	glPopMatrix();
	
	glDisable(GL_SCISSOR_TEST);
    glColor3f(1,1,1);
}

void drawable_texture_atlas_scene(vec2i mypos, vec2i mysize, bool mytest_coi, LDEfloat myframetime )
{
	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_TEXTURE_2D);
	glScissor( mypos.x, app.size.y - (mypos.y+mysize.y), mysize.x, mysize.y );
	
	glPushMatrix();
	
	glTranslatef( texture_atlas_pos.x + mypos.x, texture_atlas_pos.y + mypos.y, 0 );
	
	glBindTexture(GL_TEXTURE_2D, texture_shadow.id);
	LDEcustomrectp( texture_shadow.size,
                   vec4i( -6, -6, (texture_atlas_size.x*texture_atlas_zoom)+12, (texture_atlas_size.y*texture_atlas_zoom)+12 ),
                   vec4i( 12, 12, 12, 12) );
	
	glScalef( texture_atlas_zoom, texture_atlas_zoom, 0 );
	
	// Damier
	glBindTexture(GL_TEXTURE_2D, texture_atlas_bg.id);
	texture_atlas_uv = vec2i( texture_atlas_size.x/texture_atlas_bg.size.x, texture_atlas_size.y/texture_atlas_bg.size.y );
	LDErectuv(	texture_atlas_uv.y, 0,
              texture_atlas_uv.y, texture_atlas_uv.x,
              0, texture_atlas_uv.x,
              0, 0,
              0, 0, texture_atlas_size.x, texture_atlas_size.y );
    
	for ( LDEuint i = 0; i < texture_atlas_creation_item.size(); ++i )
	{
		glBindTexture(GL_TEXTURE_2D, texture_atlas_creation_item[i].image.id);
		LDErect( texture_atlas_creation_item[i].pos.x, texture_atlas_creation_item[i].pos.y, texture_atlas_creation_item[i].image.size_gl.x, texture_atlas_creation_item[i].image.size_gl.y );
        
		if ( texture_atlas_creation_item[i].selected )
		{
			/// Traits, marges
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_LINE_STIPPLE);
			glLineStipple(2, 0xCCCC);
			glColor4f(1,1,1,0.5);
			//LDErectw(real_pos.x, real_pos.y, texture_atlas_images[i].size_gl.x, texture_atlas_images[i].size_gl.y);
			LDErectw( texture_atlas_creation_item[i].pos.x, texture_atlas_creation_item[i].pos.y, texture_atlas_creation_item[i].image.size.x, texture_atlas_creation_item[i].image.size.y);
			//LDErectw(real_pos.x + texture_atlas_images[i].cropped_left, real_pos.y + texture_atlas_images[i].cropped_top, texture_atlas_images[i].size.x - (texture_atlas_images[i].cropped_left+texture_atlas_images[i].cropped_right), texture_atlas_images[i].size.y - (texture_atlas_images[i].cropped_top+texture_atlas_images[i].cropped_bottom));
			glDisable(GL_LINE_STIPPLE);
			glEnable(GL_TEXTURE_2D);
			glColor3f(1,1,1);
		}
	}
	
	glPopMatrix();
	
	glDisable(GL_SCISSOR_TEST);
	
	glColor3f(1,1,1);
}

@implementation OpenGLView

-(BOOL) acceptsFirstResponder
{
    return YES;
}

-(void) keyDown:(NSEvent *)theEvent
{
    LDEinput input_temp;
    input_temp.characters = [[theEvent characters] UTF8String];
    input_temp.key_down = 1;

    switch ([theEvent keyCode])
    {
        case 5: input_temp.g = 1;  break; // G key
        case 36: input_temp.characters = ""; input_temp.enter = 1;  break; // Enter/Return key
        case 48: input_temp.characters = ""; input_temp.tab = 1;  break; // Enter
        case 51: input_temp.characters = ""; input_temp.backspace = 1;  break; // Backspace
        case 53: input_temp.characters = ""; input_temp.esc = 1;  break; // Escape key
        case 123: input_temp.characters = ""; input_temp.left = 1;  break; // Left arrow key
        case 124: input_temp.characters = ""; input_temp.right = 1;  break; // Right arrow key
        case 125: input_temp.characters = ""; input_temp.down = 1;  break; // Down arrow key
        case 126: input_temp.characters = ""; input_temp.up = 1;  break; // Up arrow key
    }
    
    app.input.push_back(input_temp);
}

-(void) keyUp:(NSEvent *)theEvent
{
    LDEinput input_temp;
    input_temp.characters = [[theEvent characters] UTF8String];
    input_temp.key_down = 0;
    
    switch ([theEvent keyCode])
    {
        case 5: input_temp.g = 1;  break; // G key
        case 36: input_temp.characters = ""; input_temp.enter = 1;  break; // Enter/Return key
        case 48: input_temp.characters = ""; input_temp.tab = 1;  break; // Enter
        case 51: input_temp.characters = ""; input_temp.backspace = 1;  break; // Backspace
        case 53: input_temp.characters = ""; input_temp.esc = 1;  break; // Escape key
        case 123: input_temp.characters = ""; input_temp.left = 1;  break; // Left arrow key
        case 124: input_temp.characters = ""; input_temp.right = 1;  break; // Right arrow key
        case 125: input_temp.characters = ""; input_temp.down = 1;  break; // Down arrow key
        case 126: input_temp.characters = ""; input_temp.up = 1;  break; // Up arrow key
    }
    
    app.input.push_back(input_temp);
}

- (void)mouseDown:(NSEvent *)theEvent
{
	LDEmouse_event mouse_event;
	mouse_event.cursor_pos = app.cursor;
    mouse_event.left = 1;
	mouse_event.down = 1;
	app.mouse.push_back( mouse_event );
}

- (void)mouseUp:(NSEvent *)theEvent
{
	LDEmouse_event mouse_event;
	mouse_event.cursor_pos = app.cursor;
    mouse_event.left = 1;
	mouse_event.down = 0;
	app.mouse.push_back( mouse_event );
}

- (void)magnifyWithEvent:(NSEvent *)event
{
	LDEmouse_event mouse_event;
	//mouse_event.cursor_pos = app.cursor;
    mouse_event.scroll_z = [event deltaZ];
	app.mouse.push_back( mouse_event );
	
	//[event magnification];
}

- (void)scrollWheel:(NSEvent *)event
{
	LDEmouse_event mouse_event;
	//mouse_event.cursor_pos = app.cursor;
    mouse_event.scroll_x = -[event deltaX];
    mouse_event.scroll_y = -[event deltaY];
	app.mouse.push_back( mouse_event );
}

- (void)swipeWithEvent:(NSEvent *)event
{
	LDEmouse_event mouse_event;
	//mouse_event.cursor_pos = app.cursor;
    mouse_event.swipe_x = -[event deltaX];
    mouse_event.swipe_y = -[event deltaY];
	app.mouse.push_back( mouse_event );
}

- (void)mouseMoved:(NSEvent *)event
{	
    NSPoint eventLocation = [event locationInWindow];
	
    NSPoint center = [self convertPoint:eventLocation fromView:nil];
	
	app.cursor.x = center.x;
	app.cursor.y = app.size.y - center.y;
	
	//cout << app.cursor.x << " " << app.cursor.y << "\n";
}

- (void)mouseDragged:(NSEvent *)event
{
    NSPoint eventLocation = [event locationInWindow];
	
    NSPoint center = [self convertPoint:eventLocation fromView:nil];
	
	app.cursor.x = center.x;
	app.cursor.y = app.size.y - center.y;
	
	//cout << app.cursor.x << " " << app.cursor.y << "\n";
}

- (void)reshape
{
    NSRect bounds = [self bounds];
	app.size.x = bounds.size.width;
	app.size.y = bounds.size.height;
	
	//LDEhinit = app.size.y;
	//LDEwinit = app.size.x;
	
	[super setNeedsDisplay:YES];
    [[self openGLContext] update];
	
    glViewport(0, 0, app.size.x, app.size.y);
}

- (void)flagsChanged:(NSEvent *)event
{
    //cout<<[event keyCode]<<"\n";
    
	// if left or right SHIFT key
	switch ([event keyCode])
	{
        case 55:
        {
            LDEinput input_temp;
            input_temp.lcmd = 1;
            input_temp.key_down = app.input_lcmd = ([event modifierFlags] & NSCommandKeyMask) != 0;
            app.input.push_back( input_temp );
            break;
        }
            
        case 56:
        {
            LDEinput input_temp;
            input_temp.lshift = 1;
            input_temp.key_down = ([event modifierFlags] & NSShiftKeyMask) != 0;
            app.input.push_back( input_temp );
            break;
        }
            
        case 59:
        {
            LDEinput input_temp;
            input_temp.lctrl = 1;
            input_temp.key_down = ([event modifierFlags] & NSControlKeyMask) != 0;
            app.input.push_back( input_temp );
            break;
        }
            
        case 60:
        {
            LDEinput input_temp;
            input_temp.rshift = 1;
            input_temp.key_down = ([event modifierFlags] & NSShiftKeyMask) != 0;
            app.input.push_back( input_temp );
            break;
        }
	}
}

/*- (id)initWithFrame:(NSRect)frame
 {
 self = [super initWithFrame:frame];
 if (self)
 {
 // Init code here
 NSTimer *timer = [[NSTimer scheduledTimerWithTimeInterval : 0.01f
 target : self
 selector : @selector( display )
 userInfo : nil
 repeats : YES]
 retain];
 
 [[NSRunLoop currentRunLoop] addTimer:timer forMode:NSEventTrackingRunLoopMode];
 }
 
 return self;
 }*/

-(void) awakeFromNib
{
    [[self window] setAcceptsMouseMovedEvents:YES];
    
    /*// Init code here
     NSTimer *timer = [[NSTimer scheduledTimerWithTimeInterval : 0.01f
     target : self
     selector : @selector( display )
     userInfo : nil
     repeats : YES]
     retain];
     
     [[NSRunLoop currentRunLoop] addTimer:timer forMode:NSEventTrackingRunLoopMode];*/
}

-(void) prepareOpenGL
{
    app.init(1217,650,L"LDE Faya Editor");
	camera2D.mode = 1;
	camera2D.window = app.size;
    
    camera_pos = vec2i( 200, app.size.y / 2 );
    
	// Where are the ressources located
	NSString *cheminRessource = [NSString stringWithFormat:@"%@/",[[NSBundle mainBundle]bundlePath]];
	string path = [cheminRessource UTF8String];
	
	// Chargement du thème de l'interface utilisateur
    load_gui_theme( path+"Contents/Resources/" );
	
    // Initialisaiton de la GUI
    init_gui();
    
    NSTimer *timer = [[NSTimer scheduledTimerWithTimeInterval : 0.01f
                                                       target : self
                                                     selector : @selector( display )
                                                     userInfo : nil
                                                      repeats : YES]
                                                        retain];
    
    [[NSRunLoop currentRunLoop] addTimer:timer forMode:NSEventTrackingRunLoopMode];
}

- (void)drawRect:(NSRect)dirtyRect
{
    // Drawing code here.
    glClear(GL_COLOR_BUFFER_BIT);
    
    for ( LDEuint i = 0; i < app.input.size(); ++i )
    {
        if ( app.input_lcmd && app.input[i].s )
        {
            if ( project_path.size() && project_name.size() )
                saveFile( project_path+"/"+project_name+".feproj" );
        }
    }
    
    for ( LDEuint i = 0; i < app.mouse.size(); ++i )
    {
        if ( gui.unused )
        {
            if (app.mouse[i].scroll_x || app.mouse[i].scroll_y )
            {
                camera_pos.x -= (app.mouse[i].scroll_x * 3) / camera_zoom;
                camera_pos.y -= (app.mouse[i].scroll_y * 3) / camera_zoom;
            }
            
            if ( app.mouse[i].scroll_z )
            {
                camera_zoom += (app.mouse[i].scroll_z / 1000) * camera_zoom;
                
                if ( camera_zoom < 0.01f )
                    camera_zoom = 0.01f;
                
                combobox_editor_zoom->button.name = LDEnts(round(camera_zoom*100))+"%";
            }
        }
    }
    
    // If we changed the zoom of the scene from the combobox
    if ( combobox_editor_zoom->changed )
    {
        camera_zoom = (LDEfloat)combobox_editor_zoom->key() / 100;
        
        camera_pos.x = 150;
        camera_pos.y = 150;
    }
    
    /// CAMERA 2D ///
    camera2D.set();
    camera2D.window = app.size;
    
    for ( LDEint i = 0; i < 100; i += 5 )
    {
        gui.font_elements->setText( LDEnts(i)+"m");
        
        gui.font_elements->setPos( ((camera_pos.x + (i * PTM_RATIO) - (gui.font_elements->size.x/2))+3)*camera_zoom,camera_pos.y*camera_zoom);
        gui.font_elements->draw();
        
        gui.font_elements->setPos( ((camera_pos.x - gui.font_elements->size.x)*camera_zoom)-(10/camera_zoom), (camera_pos.y - (i * PTM_RATIO) - (10/camera_zoom))*camera_zoom );
        gui.font_elements->draw();
        
        gui.font_elements->setText( LDEnts(-i)+"m");
        
        gui.font_elements->setPos( ((camera_pos.x - gui.font_elements->size.x)*camera_zoom)-(10/camera_zoom), (camera_pos.y + (i * PTM_RATIO) - (10/camera_zoom))*camera_zoom );
        gui.font_elements->draw();
    }
    
    glPushMatrix();
    glScalef(camera_zoom, camera_zoom, 0);
    glTranslatef(camera_pos.x,camera_pos.y,0);
    
    glEnable(GL_TEXTURE_2D);
    bool selection_changed = 0;
    // Draw all the world sprites
    for ( LDEuint i = 0; i < spritesheets_zorder.size(); ++i )
    {
        LDEuint sps_id = /*spritesheets_zorder.size() - 1 - */spritesheets_zorder[i];
        
        spritesheets[sps_id].spriteBatchNode.cursor = app.cursor;
        spritesheets[sps_id].spriteBatchNode.camera_pos = camera_pos;
        spritesheets[sps_id].spriteBatchNode.camera_zoom = camera_zoom;
        spritesheets[sps_id].spriteBatchNode.mouse = app.mouse;
        spritesheets[sps_id].spriteBatchNode.input = app.input;
        spritesheets[sps_id].spriteBatchNode.test_coi = gui.unused && !transf_tool.hover;
        spritesheets[sps_id].spriteBatchNode.draw();
        
        if ( spritesheets[sps_id].spriteBatchNode.changed )
            selection_changed = 1;
        
        /*if ( sps_id )
            if ( spritesheets[sps_id].spriteBatchNode.getNumSelected() )
                spritesheets[sps_id-1].spriteBatchNode.unselectAll();*/
    }
    
    //// IF SELECTION CHANGED FROM WORLD SPRITES (new selected or unselected)
    if ( selection_changed )
    {
        list_sprites->deselect();
        num_selected_sprites = 0;
        transf_tool_rot = 0;

        vec2i min( 999999999, 999999999), max( -999999999, -999999999), pos_temp;
        
        // For every spritesheet folder in the list
        tree<LDEgui_list_item>::sibling_iterator item_itr_sibling = list_sprites->items_tree.begin();
        while ( item_itr_sibling != list_sprites->items_tree.end() )
        {
            //cout<<"folder:"<<item_itr_sibling->button.name<<"\n";
            
            pos_temp = spritesheets[item_itr_sibling->key].spriteBatchNode.getTransfPos();
            
            if ( pos_temp.x != 0 && pos_temp.y != 0 )
            {
                /// MIN
                if ( min.x > pos_temp.x )
                    min.x = pos_temp.x;
                
                if ( min.y > pos_temp.y )
                    min.y = pos_temp.y;
                
                
                /// MAX
                if ( max.x < pos_temp.x )
                    max.x = pos_temp.x;
                
                if ( max.y < pos_temp.y )
                    max.y = pos_temp.y;
            }
            
            // For every sprites in the spritesheet folder
            tree<LDEgui_list_item>::iterator item_itr = list_sprites->items_tree.begin(item_itr_sibling);
            while ( item_itr != list_sprites->items_tree.end(item_itr_sibling) )
            {
                if ( item_itr->type == 0 )
                {
                    //cout<<"sprite:"<<item_itr->button.name<<"\n";

                    if ( spritesheets[item_itr_sibling->key].spriteBatchNode.sprites[item_itr->key].selected )
                    {
                        transf_tool_rot = spritesheets[item_itr_sibling->key].spriteBatchNode.sprites[item_itr->key].rot;
                        transf_tool_size = spritesheets[item_itr_sibling->key].spriteBatchNode.sprites[item_itr->key].size;
                        
                        list_sprites->select(item_itr, 1);
                        list_sprites->changed_selection = 0;
                        
                        ++num_selected_sprites;
                    }
                }
                
                ++item_itr;
            }
            
            ++item_itr_sibling;
        }
        
        if ( num_selected_sprites > 1 )
        {
            transf_tool_rot = 0;
            transf_tool_size = 0;
        }
        
        transf_tool.rot_offset = -transf_tool_rot;
        
        transf_tool_pos = vec2i( min.x + ((max.x - min.x)/2), min.y + ((max.y - min.y)/2) );
        
        editbox_sprite_pos_x->name = LDEnts(transf_tool_pos.x);
        editbox_sprite_pos_y->name = LDEnts(-transf_tool_pos.y);
        
        editbox_sprite_size_x->name = LDEnts(transf_tool_size.x);
        editbox_sprite_size_y->name = LDEnts(transf_tool_size.y);
        
        editbox_sprite_ap_x->name = LDEnts(transf_tool_size.x/2);
        editbox_sprite_ap_y->name = LDEnts(transf_tool_size.y/2);
        
        editbox_sprite_rot->name = LDEnts( transf_tool_rot );
    }
    
    glDisable(GL_TEXTURE_2D);
    
    for ( LDEuint i = 0; i < shapes.size(); ++i )
    {
        shapes[i].draw();
    }
    
    glColor4d(1, 1, 1, 0.4);
    
    glBegin(GL_LINES);
    glVertex2i(0, 0);
    glVertex2i(0, -1000*PTM_RATIO);
    
    glVertex2i(0, 0);
    glVertex2i(1000*PTM_RATIO, 0);
    glEnd();
    
    glBegin(GL_LINES);
    for ( LDEuint i = 0; i < 100; ++i )
    {
        glVertex2i(i*PTM_RATIO, 0);
        glVertex2i(i*PTM_RATIO, 10);
    }
    
    for ( LDEuint i = 0; i < 100; ++i )
    {
        glVertex2i(-10, -i*PTM_RATIO);
        glVertex2i(0, -i*PTM_RATIO);
    }
    glEnd();
    
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1,0x0101);
    glColor4d(1, 1, 1, 0.2);
    glBegin(GL_LINES);
    for ( LDEuint i = 0; i < 100; ++i )
    {
        glVertex2i(i*PTM_RATIO,1000*PTM_RATIO);
        glVertex2i(i*PTM_RATIO,-1000*PTM_RATIO);
        
        glVertex2i(0, -i*PTM_RATIO);
        glVertex2i(1000*PTM_RATIO, -i*PTM_RATIO);
    }
    glEnd();
    
    glColor4d(1, 1, 1, 0.3);
    glBegin(GL_LINES);
    for ( LDEuint i = 0; i < 100; i += 5 )
    {
        glVertex2i(i*PTM_RATIO,1000*PTM_RATIO);
        glVertex2i(i*PTM_RATIO,-1000*PTM_RATIO);
        
        glVertex2i(0, -i*PTM_RATIO);
        glVertex2i(1000*PTM_RATIO, -i*PTM_RATIO);
    }
    glEnd();
    
    glColor4d(1, 0, 0, 0.5);
    glLineWidth(2);
    glLineStipple(1,0x00FF);
    glBegin(GL_LINE_STRIP);
    glVertex2i(0, 0);
    glVertex2i(0, -640);
    glVertex2i(960, -640);
    glVertex2i(960, 0);
    glVertex2i(0, 0);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    
    glColor3f(1, 1, 1);
    
    for ( LDEuint i = 0; i < paths.size(); ++i )
    {
        paths[i].draw();
    }
    
    glPopMatrix();
    
    glEnable(GL_TEXTURE_2D);
    
    if ( num_selected_sprites )
    {
        transf_tool.cursor = app.cursor;
        transf_tool.mouse = app.mouse;
        transf_tool.test_coi = gui.unused;
        transf_tool.draw( vec2i( (transf_tool_pos.x + camera_pos.x) * camera_zoom, (transf_tool_pos.y + camera_pos.y) * camera_zoom ) );

        if ( transf_tool.changed )
        {
            for ( LDEuint i = 0; i < spritesheets.size(); ++i )
            {
                spritesheets[i].spriteBatchNode.applyPosOffset();
                
                for ( LDEuint s = 0; s < spritesheets[i].spriteBatchNode.sprites.size(); ++s )
                {
                    spritesheets[i].spriteBatchNode.sprites[s].init_dist = 0;
                }
            }
            
            transf_tool.rot_offset = -transf_tool_rot;
        }

        if ( transf_tool.hover_arrow_right || transf_tool.hover_arrow_bottom || transf_tool.hover_circle )
        {   
            vec2i new_pos( round( (LDEfloat)transf_tool.pos.x / camera_zoom ) - camera_pos.x, round( (LDEfloat)transf_tool.pos.y / camera_zoom ) - camera_pos.y );
            vec2i pos_offset( (LDEfloat)(transf_tool.pos.x - transf_tool.pos_old.x) / camera_zoom, (LDEfloat)(transf_tool.pos.y - transf_tool.pos_old.y) / camera_zoom );
            
            for ( LDEuint i = 0; i < spritesheets.size(); ++i )
            {
                spritesheets[i].spriteBatchNode.showPosOffset( pos_offset );
            }
            
            transf_tool_pos = new_pos;
            
            editbox_sprite_pos_x->name = LDEnts(transf_tool_pos.x);
            editbox_sprite_pos_y->name = LDEnts(-transf_tool_pos.y);
        }
        else if ( transf_tool.hover_rotate )
        {
            vec2i new_pos( ((LDEfloat)transf_tool.pos.x / camera_zoom ) - camera_pos.x, ( (LDEfloat)transf_tool.pos.y / camera_zoom ) - camera_pos.y );
            
            for ( LDEuint i = 0; i < spritesheets.size(); ++i )
            {
                // Si plusieurs sprites sont sélectionnés
                if ( num_selected_sprites > 1 )
                {
                    for ( LDEuint s = 0; s < spritesheets[i].spriteBatchNode.sprites.size(); ++s )
                    {
                        if ( spritesheets[i].spriteBatchNode.sprites[s].selected )
                        {
                            if ( !spritesheets[i].spriteBatchNode.sprites[s].init_dist )
                            {
                                spritesheets[i].spriteBatchNode.sprites[s].dist = LDEdist2f( vec2f(new_pos), vec2f(spritesheets[i].spriteBatchNode.sprites[s].pos) );
                                spritesheets[i].spriteBatchNode.sprites[s].rot_offset = LDEangle2i( new_pos, spritesheets[i].spriteBatchNode.sprites[s].pos );
                                spritesheets[i].spriteBatchNode.sprites[s].rot_self_offset = spritesheets[i].spriteBatchNode.sprites[s].rot;
                                
                                // bs code
                                spritesheets[i].spriteBatchNode.sprites[s].pos = vec2i( new_pos.x + (sin(-LDEdegtorad(transf_tool.rot-spritesheets[i].spriteBatchNode.sprites[s].rot_offset)) * spritesheets[i].spriteBatchNode.sprites[s].dist),
                                                                                        new_pos.y + (cos(-LDEdegtorad(transf_tool.rot-spritesheets[i].spriteBatchNode.sprites[s].rot_offset)) * spritesheets[i].spriteBatchNode.sprites[s].dist) );
                                
                                spritesheets[i].spriteBatchNode.sprites[s].rot_offset = LDEangle2i( new_pos, spritesheets[i].spriteBatchNode.sprites[s].pos );
                                // fin bs code
                                
                                spritesheets[i].spriteBatchNode.sprites[s].init_dist = 1;
                            }
                            
                            spritesheets[i].spriteBatchNode.sprites[s].rot = transf_tool.rot + spritesheets[i].spriteBatchNode.sprites[s].rot_self_offset;
                            
                            spritesheets[i].spriteBatchNode.sprites[s].pos = vec2i( new_pos.x + (sin(-LDEdegtorad(transf_tool.rot-spritesheets[i].spriteBatchNode.sprites[s].rot_offset)) * spritesheets[i].spriteBatchNode.sprites[s].dist),
                                                                                    new_pos.y + (cos(-LDEdegtorad(transf_tool.rot-spritesheets[i].spriteBatchNode.sprites[s].rot_offset)) * spritesheets[i].spriteBatchNode.sprites[s].dist) );
                        }
                    }
                }
                // Si un seul sprite est sélectionné, appliquer la rotation réelle
                else
                    spritesheets[i].spriteBatchNode.setRotation( transf_tool.rot );
            }
            
            transf_tool_rot = transf_tool.rot;
            editbox_sprite_rot->name = LDEnts( transf_tool_rot );
        }
        else if ( transf_tool.hover_square_right )
        {
            if ( !transf_tool.init_change )
            {
                transf_tool.old_size = transf_tool_size.x;
                
                transf_tool.init_change = 1;
            }
            
            vec2i new_size;
            
            new_size.x = ((LDEfloat)transf_tool.size / camera_zoom) + transf_tool.old_size;
            
            for ( LDEuint i = 0; i < spritesheets.size(); ++i )
            {
                // Si plusieurs sprites sont sélectionnés
                if ( num_selected_sprites > 1 )
                {
                    
                }
                else
                    new_size.y = spritesheets[i].spriteBatchNode.setSizeX( new_size.x, checkbox_sprite_size_keep_ratio->checked );
            }
            
            transf_tool_size = new_size;
            
            editbox_sprite_size_x->name = LDEnts( new_size.x );
            
            if ( checkbox_sprite_size_keep_ratio->checked )
                editbox_sprite_size_y->name = LDEnts(new_size.y);
        }
        else if ( transf_tool.hover_square_bottom )
        {
            if ( !transf_tool.init_change )
            {
                transf_tool.old_size = transf_tool_size.y;
                
                transf_tool.init_change = 1;
            }
            
            vec2i new_size;
            
            new_size.y = ((LDEfloat)transf_tool.size / camera_zoom) + transf_tool.old_size;
            
            for ( LDEuint i = 0; i < spritesheets.size(); ++i )
            {
                // Si plusieurs sprites sont sélectionnés
                if ( num_selected_sprites > 1 )
                {
                    
                }
                else
                    new_size.x = spritesheets[i].spriteBatchNode.setSizeY( new_size.y, checkbox_sprite_size_keep_ratio->checked );
            }
            
            transf_tool_size = new_size;
            
            editbox_sprite_size_y->name = LDEnts( new_size.y );
            
            if ( checkbox_sprite_size_keep_ratio->checked )
                editbox_sprite_size_x->name = LDEnts(new_size.x);
        }
    }

    glLineWidth(1);
    
    // Vector Mode
    if ( editor_mode == 0 )
    {
        if ( gui.unused )
        {
            for ( LDEuint i = 0; i < app.mouse.size(); ++i )
            {
                if ( app.mouse[i].left )
                {
                    if ( app.mouse[i].down )
                    {
                        //cout << "left mouse button down\n";
                        //mouse_overall_down = 1;
                        
                        if ( paths.size() && list_vector_paths->num_selected )
                        {
                            vec2i vertex_pos;
                            
                            vertex_pos.x = (app.mouse[i].cursor_pos.x/camera_zoom) - camera_pos.x;
                            vertex_pos.y = (app.mouse[i].cursor_pos.y/camera_zoom) - camera_pos.y;
                            
                            path_itr_selected->addVertex( vertex_pos );
                        }
                    }
                }
            }
        }
        
        
        ////////// CREATION D'UN NOUVEAU PATH ////////////
        if ( button_path_new->click )
        {
            // Unselect the previously selected path
            if ( path_itr_selected != paths.end() )
                path_itr_selected->active = 0;
            
            VectorPaths path_temp;
            paths.push_back(path_temp);
            
            LDEuint path_id = paths.size()-1;
            
            path_itr_selected = paths.begin() + path_id;
            
            tree<LDEgui_list_item>::iterator item_path = list_vector_paths->addItem( path_id, "Path "+LDEnts(path_id) );
            list_vector_paths->select( item_path, 0);
            
            path_itr_selected->active = 1;
            
            button_vector_paths_delete->unlock();
        }
        
        ///////// Si la selection a changé (depuis la fenêtre list of paths)
        if ( list_vector_paths->changed_selection )
        {
            tree<LDEgui_list_item>::iterator item_itr = list_vector_paths->items_tree.begin();
            while ( item_itr != list_vector_paths->items_tree.end() )
            {
                if ( item_itr->selected )
                {
                    
                    //path_selected_id = item_itr->key;
                    break;
                }
                
                ++item_itr;
            }
        }
        
        if ( button_vector_paths_delete->click && list_vector_paths->num_selected )
        {
            paths.erase( path_itr_selected );
            
            tree<LDEgui_list_item>::iterator item_itr = list_vector_paths->items_tree.begin();
            while ( item_itr != list_vector_paths->items_tree.end() )
            {
                if ( item_itr->selected )
                {
                    list_vector_paths->items_tree.erase( item_itr );
                    break;
                }
                
                ++item_itr;
            }
            
            if ( !paths.size() )
            {
                button_vector_paths_delete->lock();
            }
        }
        
        if ( button_path_end->click )
        {
            path_itr_selected->active = 0;
            
            list_vector_paths->deselect();
        }
        
        // Make a triangulated shape from this path!
        if ( button_path_triangulate->click )
        {
            if ( path_itr_selected->vertex.size() > 2 )
            {
                // Unselect all shapes
                for ( LDEuint i = 0; i < shapes.size(); ++i )
                {
                    shapes[i].selected = 0;
                }
                
                tree<LDEgui_list_item>::iterator item_itr = list_vector_paths->items_tree.begin();
                while ( item_itr != list_vector_paths->items_tree.end() )
                {
                    if ( item_itr->selected )
                    {
                        list_vector_paths->items_tree.erase( item_itr );
                        break;
                    }

                    ++item_itr;
                }
                
                path_itr_selected->active = 0;
                list_vector_paths->deselect();
                
                Shapes shape_temp;
                shape_temp.path_vertex = path_itr_selected->vertex;
                
                // allocate an STL vector to hold the answer.
                
                Vector2dVector result;
                
                //  Invoke the triangulator to triangulate this polygon.
                Triangulate::Process( path_itr_selected->vertex,result);
                
                shape_temp.vertex = result;
                shape_temp.selected = 1;
                
                shapes.push_back( shape_temp );
                
                LDEuint shape_id = shapes.size()-1;
                
                tree<LDEgui_list_item>::iterator item_list = list_shapes->addItem( shape_id, "Shape"+LDEnts(shape_id) );
                list_shapes->select( item_list, 0 );
                
                paths.erase( path_itr_selected );
                
                // Go to shapes management
                switchEditorMode(3);
            }
        }
        
        if ( !window_vector_paths_list->closed )
        {
            if ( window_vector_paths_list->button_resize.pressed )
            {
                list_vector_paths->size.x = window_vector_paths_list->size.x;
                list_vector_paths->size.y = window_vector_paths_list->size.y-60;
                
                button_vector_paths_delete->pos.y = window_vector_paths_list->size.y-54;
            }
        }
        
        //
        //
    }
    else if ( editor_mode == 1 )
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////                        TEXTURE ATLAS CREATION                        //////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        if ( !window_texture_atlas_sprites_list->closed )
        {
            if ( window_texture_atlas_sprites_list->button_resize.pressed )
            {
                list_texture_atlas_sprites->size.x = window_texture_atlas_sprites_list->size.x;
                list_texture_atlas_sprites->size.y = window_texture_atlas_sprites_list->size.y-60;
                
                button_texture_atlas_sprites_delete->pos.y = window_texture_atlas_sprites_list->size.y-54;
            }
            
            /*if ( list_texture_atlas_sprites->changed )	
            {
                LDEuint num_selected = 0;
                for ( LDEuint i = 0; i < list_texture_atlas_sprites->item.size(); ++i )
                {
                    texture_atlas_creation_item[list_texture_atlas_sprites->item[i].key].selected = list_texture_atlas_sprites->item[i].selected;
                    
                    if ( list_texture_atlas_sprites->item[i].selected )
                        ++num_selected;
                }
                
                if ( num_selected == 1 )
                    button_texture_atlas_sprites_delete->unlock();
                else
                    button_texture_atlas_sprites_delete->lock();
                
            }
            
            if ( button_texture_atlas_sprites_delete->click )
            {
                for ( LDEuint i = 0; i < list_texture_atlas_sprites->item.size(); ++i )
                {
                    if ( list_texture_atlas_sprites->item[i].selected )
                    {
                        glDeleteTextures(1, &texture_atlas_creation_item[list_texture_atlas_sprites->item[i].key].image.id);
                        texture_atlas_creation_item.erase( texture_atlas_creation_item.begin()+list_texture_atlas_sprites->item[i].key );
                        list_texture_atlas_sprites->remove( i );
                    }	
                }
            }*/
        }
        
        if ( !window_texture_atlas->closed )
        {
            if ( window_texture_atlas->button_resize.pressed )
            {
                combobox_texture_atlas_zoom->pos.x = window_texture_atlas->size.x - combobox_texture_atlas_zoom->size.x - 20;
                
                scrollbar_texture_atlas->pos.x = window_texture_atlas->size.x - 16;
                scrollbar_texture_atlas->size.y = window_texture_atlas->size.y-43;
                
                scrollbar_texture_atlas_horizontal->pos.y = window_texture_atlas->size.y-43;
                scrollbar_texture_atlas_horizontal->size.x = window_texture_atlas->size.x - 16;
                
                drawable_texture_atlas->size = vec2i( window_texture_atlas->size.x - 16, window_texture_atlas->size.y - 43 );
            }
            
            if ( combobox_texture_atlas_zoom->changed )
            {
                texture_atlas_zoom = (LDEfloat)combobox_texture_atlas_zoom->key() / 100;
                
                scrollbar_texture_atlas->scroll_height = (texture_atlas_size.y*texture_atlas_zoom)+20;
                scrollbar_texture_atlas_horizontal->scroll_height = (texture_atlas_size.x*texture_atlas_zoom)+20;
                scrollbar_texture_atlas->setPercent(0);
                scrollbar_texture_atlas_horizontal->setPercent(0);
            }	
            
            if ( drawable_texture_atlas->test_coi )
            {
                LDEfloat scroll_x = 0,
                scroll_y = 0;
                
                // Trackpad interacting
                for ( LDEuint i = 0; i < app.mouse.size(); ++i )
                {
                    // Scroll
                    if ( app.mouse[i].scroll_x != 0 )
                        scroll_x += app.mouse[i].scroll_x;
                    
                    if ( app.mouse[i].scroll_y != 0 )
                        scroll_y += app.mouse[i].scroll_y;
                    
                    
                    // Swipe
                    if ( app.mouse[i].swipe_x != 0 )
                    {
                        if ( app.mouse[i].swipe_x == -1 )
                            scrollbar_texture_atlas_horizontal->setPercent( 0 );
                        else
                            scrollbar_texture_atlas_horizontal->setPercent( 1 );
                    }
                    else if ( app.mouse[i].swipe_y != 0 )
                    {
                        if ( app.mouse[i].swipe_y == -1 )
                            scrollbar_texture_atlas->setPercent( 0 );
                        else
                            scrollbar_texture_atlas->setPercent( 1 );
                    }
                    
                    // Zoom
                    if ( app.mouse[i].scroll_z != 0 )
                    {
                        LDEfloat zoom_value = app.mouse[i].scroll_z * (texture_atlas_zoom/400);
                        texture_atlas_zoom += zoom_value;
                        
                        if ( texture_atlas_zoom < 0.2 )
                            texture_atlas_zoom = 0.2;
                        else if ( texture_atlas_zoom > 10 )
                            texture_atlas_zoom = 10;
                        
                        scrollbar_texture_atlas->scroll_height = (texture_atlas_size.y*texture_atlas_zoom)+20;
                        scrollbar_texture_atlas_horizontal->scroll_height = (texture_atlas_size.x*texture_atlas_zoom)+20;
                        scrollbar_texture_atlas->setPercent(0);
                        scrollbar_texture_atlas_horizontal->setPercent(0);
                        
                        combobox_texture_atlas_zoom->button.name = LDEnts(round(texture_atlas_zoom*100))+"%";
                        
                        texture_atlas_pos = vec2i( 10, 10 );
                        
                        //texture_atlas_pos.x = (-scrollbar_texture_atlas_horizontal->scroll_amount + 10) - window_texture_atlas->cursor_inside.x;
                    }
                }
                
                if ( scroll_x != 0 )
                {
                    LDEfloat percent_x = scrollbar_texture_atlas_horizontal->percent + (scroll_x / 100);
                    
                    if ( percent_x > 1 )
                        percent_x = 1;
                    else if ( percent_x < 0 )
                        percent_x = 0;
                    
                    scrollbar_texture_atlas_horizontal->setPercent( percent_x );
                }
                
                if ( scroll_y != 0 )
                {
                    LDEfloat percent_y = scrollbar_texture_atlas->percent + (scroll_y / 100);
                    
                    if ( percent_y > 1 )
                        percent_y = 1;
                    else if ( percent_y < 0 )
                        percent_y = 0;
                    
                    scrollbar_texture_atlas->setPercent( percent_y );
                }
            }
            
            if ( scrollbar_texture_atlas->changed )
                texture_atlas_pos.y = -scrollbar_texture_atlas->scroll_amount + 10;
            if ( scrollbar_texture_atlas_horizontal->changed )
                texture_atlas_pos.x = -scrollbar_texture_atlas_horizontal->scroll_amount + 10;
        }
        // Shapes management mode
        else if ( editor_mode == 3 )
        {
            if ( !window_shapes_list->closed )
            {
                
            }
        }
        
        
        for ( LDEuint i = 0; i < app.mouse.size(); ++i )
        {
            if ( app.mouse[i].left )
            {
                if ( !app.mouse[i].down )
                {
                    //cout << "left mouse button down\n";
                    //mouse_overall_down = 0;
                }
            }
        }
	}
    
    ////////// File browser
    if ( !window_tools_texture_atlas->closed )
    {
        if ( button_texture_atlas_import_images->click )
        {
            // Create the File Open Dialog class.
            NSOpenPanel* openDlg = [NSOpenPanel openPanel];
            
            [openDlg setCanChooseFiles:YES];
            [openDlg setCanChooseDirectories:YES];
            [openDlg setAllowsMultipleSelection:YES];
            
            NSArray *fileTypes = [NSArray arrayWithObjects:
                                  @"jpg",
                                  @"jpeg",
                                  @"png",
                                  @"gif",
                                  NSFileTypeForHFSTypeCode('TEXT'),
                                  nil];
            
            [openDlg setAllowedFileTypes:fileTypes];
            
            // Display the dialog.  If the OK button was pressed,
            // process the files.
            if ( [openDlg runModal] == NSOKButton )
            {
                // Get an array containing the full filenames of all
                // files and directories selected.
                NSArray* files = [openDlg URLs];
                
                // Loop through all the files and process them.
                for( LDEuint i = 0; i < [files count]; ++i )
                {
                    NSString* fileName = [[files objectAtIndex:i] path];
                    
                    TextureAtlasCreation_item texture_atlas_creation_item_temp;
                    
                    texture_atlas_creation_item_temp.image.load( [fileName UTF8String] );
                    
                    if ( texture_atlas_creation_item_temp.image.size.x && texture_atlas_creation_item_temp.image.size.y )
                    {
                        texture_atlas_creation_item_temp.image.crop( texture_atlas_creation_item_temp.image.getEmptyPixels() );
                        
                        if ( texture_atlas_creation_item_temp.image.size.y > texture_atlas_size.y )
                            texture_atlas_size.y = LDEnextPot( texture_atlas_creation_item_temp.image.size.y );
                        
                        if ( texture_atlas_creation_item_temp.image.size.x > texture_atlas_size.x )
                            texture_atlas_size.x = LDEnextPot( texture_atlas_creation_item_temp.image.size.x );
						
                        scrollbar_texture_atlas->scroll_height = (texture_atlas_size.y*texture_atlas_zoom)+20;
                        scrollbar_texture_atlas_horizontal->scroll_height = (texture_atlas_size.x*texture_atlas_zoom)+20;
						
                        list_texture_atlas_sprites->addItem( texture_atlas_creation_item.size(), texture_atlas_creation_item_temp.image.model_name );
						
                        texture_atlas_creation_item_temp.image.opengl(2);
                        
                        texture_atlas_creation_item.push_back( texture_atlas_creation_item_temp );
                    }
                }
            }
        }
        
        ///////////// Save the small images to spritesheet /////////////////
        if ( button_texture_atlas_save->click && texture_atlas_creation_item.size() && combobox_texture_atlas_width->button.text_color.y )
        {
            Spritesheet spritframe_temp;
            
            spritframe_temp.image.create(texture_atlas_size.x, texture_atlas_size.y, 4);
            
            vec2i pos_window(5, 5);
            
            for ( LDEuint i = 0; i < texture_atlas_creation_item.size(); ++i )
            {
                spritframe_temp.image.copyMerge( texture_atlas_creation_item[i].image, texture_atlas_creation_item[i].pos );
                
                Spritesheet_frame frame_temp;
                
                frame_temp.pos_window = pos_window;
                frame_temp.pos = texture_atlas_creation_item[i].pos;
                frame_temp.size = texture_atlas_creation_item[i].image.size;
                
                // Let's calculate the thumbnail's size
                LDEfloat ratio = 0;
                
                // Si la largeur est plus grande que la hauteur
                if ( frame_temp.size.x > frame_temp.size.y )
                {
                    // Déterminer le ratio
                    ratio = (LDEfloat)100 / frame_temp.size.x;
                    
                    frame_temp.size_100.x = 100;
                    
                    frame_temp.size_100.y = (LDEint)frame_temp.size.y * ratio;
                }
                // Sinon, si la hauteur est plus grande que la largeur
                else
                {
                    // Déterminer le ratio
                    ratio = (LDEfloat)100 / frame_temp.size.y;
                    
                    frame_temp.size_100.y = 100;
                    
                    frame_temp.size_100.x = (LDEint)frame_temp.size.x * ratio;
                }
                
                frame_temp.margin = vec2i( 50 - frame_temp.size_100.x / 2, 50 - frame_temp.size_100.y / 2 );
                
                frame_temp.name = texture_atlas_creation_item[i].image.model_name;
                
                spritframe_temp.frames.push_back( frame_temp );
                
                pos_window.x += 105; // width 100px
                
                if ( pos_window.x > window_spritesheets->size.x - 116 )
                {
                    pos_window.x = 5;
                    pos_window.y += 105; // height 100px
                }
            }
            
            scrollbar_spritesheets->scroll_height = pos_window.y + 100;
            
            spritframe_temp.image.opengl(2);
            
            spritesheets.push_back( spritframe_temp );
            
            LDEuint spritesheet_id = spritesheets.size()-1;
            spritesheets_zorder.push_back( spritesheet_id );
            
            string spritesheet_name = "SpriteSheet"+LDEnts( spritesheet_id+1 );
            
            combobox_spritesheets->addOption( spritesheet_id, spritesheet_name, 1 );
            spritesheets[spritesheet_id].item_group = list_sprites->addGroup( spritesheet_name );
            
            spritesheets[spritesheet_id].item_group->can_move = 1;
            spritesheets[spritesheet_id].item_group->key = spritesheet_id;
            
            tree<LDEgui_list_item>::sibling_iterator item_group_to = list_sprites->items_tree.begin();
            list_sprites->items_tree.move_before( item_group_to, spritesheets[spritesheet_id].item_group );
            
            // When spritesheet saved, go to World Edit Mode
            switchEditorMode(2);
        }
        
        // Launch 2D bin packing (rectangle packing in a bigger rectangle)
        if ( button_texture_atlas_spread->click && texture_atlas_creation_item.size() )
        {
            std::sort(texture_atlas_creation_item.begin(), texture_atlas_creation_item.end(), TextureAtlasCreation_item());
            
            vec4i *atlas_plane = new vec4i(0,0,texture_atlas_size.x,texture_atlas_size.y);
            LDErectpack *texture_atlas_creation_rectpack = new LDErectpack( atlas_plane );
            
            list_texture_atlas_sprites->erase();
            
            bool filled_successfully = 1;
            
            for ( LDEuint i = 0; i < texture_atlas_creation_item.size(); ++i )
            {
                texture_atlas_creation_item[i].selected = 0;
                list_texture_atlas_sprites->addItem( i, texture_atlas_creation_item[i].image.model_name );
                
                vec4i *imageRectangle = new vec4i(0,0,texture_atlas_creation_item[i].image.size.x,texture_atlas_creation_item[i].image.size.y);
                vec4i *resultRect = NULL;
                resultRect = texture_atlas_creation_rectpack->insert(imageRectangle, combobox_texture_atlas_spacing->key() );
                
                if ( resultRect != NULL )
                {
                    texture_atlas_creation_item[i].pos.x = resultRect->x;
                    texture_atlas_creation_item[i].pos.y = resultRect->y;
                }
                else
                    filled_successfully = 0;
            }
            
            delete atlas_plane;
            atlas_plane = NULL;
            
            delete texture_atlas_creation_rectpack;
            texture_atlas_creation_rectpack = NULL;
            
            button_texture_atlas_sprites_delete->lock();
            
            if ( filled_successfully )
            {
                combobox_texture_atlas_width->button.text_color = vec3f(1,1,1);
                combobox_texture_atlas_height->button.text_color = vec3f(1,1,1);
                combobox_texture_atlas_spacing->button.text_color = vec3f(1,1,1);
            }
            else
            {
                combobox_texture_atlas_width->button.text_color = vec3f(1,0,0);
                combobox_texture_atlas_height->button.text_color = vec3f(1,0,0);
                combobox_texture_atlas_spacing->button.text_color = vec3f(1,0,0);
            }
        }
        
        if ( combobox_texture_atlas_width->changed )
        {
            texture_atlas_size.x = combobox_texture_atlas_width->key();
            
            scrollbar_texture_atlas_horizontal->scroll_height = (texture_atlas_size.x*texture_atlas_zoom)+20;
            scrollbar_texture_atlas_horizontal->setPercent(0);
        }
        else if ( combobox_texture_atlas_height->changed )
        {
            texture_atlas_size.y = combobox_texture_atlas_height->key();
            
            scrollbar_texture_atlas->scroll_height = (texture_atlas_size.y*texture_atlas_zoom)+20;
            scrollbar_texture_atlas->setPercent(0);
        }
    }
    
    ////////// Sprites Windows
    if ( !window_spritesheets->closed )
    {
        // Resize behaviour
        if ( window_spritesheets->button_resize.pressed )
        {
            drawable_spritesheets->size = vec2i( window_spritesheets->size.x - 16, window_spritesheets->size.y - 43 );
            
            scrollbar_spritesheets->pos.x = window_spritesheets->size.x - 16;
            scrollbar_spritesheets->size.y = window_spritesheets->size.y-43;
            
            for ( LDEuint i = 0; i < spritesheets.size(); ++i )
            {
                vec2i pos_window(5, 5);
                
                for ( LDEuint s = 0; s < spritesheets[i].frames.size(); ++s )
                {
                    spritesheets[i].frames[s].pos_window = pos_window;
                    
                    pos_window.x += 105; // width 100px
                    
                    if ( pos_window.x > window_spritesheets->size.x - 116 )
                    {
                        pos_window.x = 5;
                        pos_window.y += 105; // height 100px
                    }
                }
                
                scrollbar_spritesheets->scroll_height = pos_window.y;
                
                if ( pos_window.x != 5 )
                    scrollbar_spritesheets->scroll_height += 100;
            }
        }
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////                              WORLD EDIT                              //////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // If the window sprites list is not closed
    if ( !window_sprites_list->closed )
    {
        // Resize behaviour
        if ( window_sprites_list->button_resize.pressed )
        {
            list_sprites->size.x = window_sprites_list->size.x;
            list_sprites->size.y = window_sprites_list->size.y-157;
            
            text_sprite_pos->pos = vec2i( 15, window_sprites_list->size.y-150 );
            editbox_sprite_pos_x->pos = vec2i( 75, window_sprites_list->size.y-153 );
            editbox_sprite_pos_y->pos = vec2i( 145, window_sprites_list->size.y-153 );
            text_sprite_ap->pos = vec2i( 15, window_sprites_list->size.y-125 );
            editbox_sprite_ap_x->pos = vec2i( 75, window_sprites_list->size.y-128 );
            editbox_sprite_ap_y->pos = vec2i( 145, window_sprites_list->size.y-128 );
            text_sprite_rot->pos = vec2i( 10, window_sprites_list->size.y-100 );
            editbox_sprite_rot->pos = vec2i( 75, window_sprites_list->size.y-103 );
            text_sprite_opacity->pos = vec2i( 20, window_sprites_list->size.y-75 );
            editbox_sprite_opacity->pos = vec2i( 75, window_sprites_list->size.y-78 );
            text_sprite_size->pos = vec2i( 5, window_sprites_list->size.y-50 );
            editbox_sprite_size_x->pos = vec2i( 75, window_sprites_list->size.y-53 );
            editbox_sprite_size_y->pos = vec2i( 145, window_sprites_list->size.y-53 );
            checkbox_sprite_size_keep_ratio->pos = vec2i( 200, window_sprites_list->size.y-49 );
        }
        
        /////////////// CHANGING SELECTION OF SPRITES ///////////////
        if ( list_sprites->changed_selection )
        {
            num_selected_sprites = 0;
            transf_tool_rot = 0;
            
            // For every spritesheet folder in the list
            tree<LDEgui_list_item>::sibling_iterator item_itr_sibling = list_sprites->items_tree.begin();
            while ( item_itr_sibling != list_sprites->items_tree.end() )
            {
                //cout<<"folder:"<<item_itr_sibling->button.name<<"\n";
                
                // For every sprites in the spritesheet folder
                tree<LDEgui_list_item>::iterator item_itr = list_sprites->items_tree.begin(item_itr_sibling);
                while ( item_itr != list_sprites->items_tree.end(item_itr_sibling) )
                {
                    if ( item_itr->type == 0 )
                    {
                        //cout<<"sprite:"<<item_itr->button.name<<"\n";
                        
                        spritesheets[item_itr_sibling->key].spriteBatchNode.sprites[item_itr->key].selected = item_itr->selected;
                        
                        if ( item_itr->selected )
                        {
                            transf_tool_rot = spritesheets[item_itr_sibling->key].spriteBatchNode.sprites[item_itr->key].rot;
                            transf_tool_size = spritesheets[item_itr_sibling->key].spriteBatchNode.sprites[item_itr->key].size;
                            
                            ++num_selected_sprites;
                        }
                    }
                    
                    ++item_itr;
                }
                
                ++item_itr_sibling;
            }
            
            vec2i min( 999999999, 999999999), max( -999999999, -999999999), pos_temp;
            
            // For every spritesheet folder in the list
            item_itr_sibling = list_sprites->items_tree.begin();
            while ( item_itr_sibling != list_sprites->items_tree.end() )
            {
                //cout<<"folder:"<<item_itr_sibling->button.name<<"\n";
                
                pos_temp = spritesheets[item_itr_sibling->key].spriteBatchNode.getTransfPos();
                
                if ( pos_temp.x != 0 && pos_temp.y != 0 )
                {
                    /// MIN
                    if ( min.x > pos_temp.x )
                        min.x = pos_temp.x;
                    
                    if ( min.y > pos_temp.y )
                        min.y = pos_temp.y;
                    
                    
                    /// MAX
                    if ( max.x < pos_temp.x )
                        max.x = pos_temp.x;
                    
                    if ( max.y < pos_temp.y )
                        max.y = pos_temp.y;
                }
                
                ++item_itr_sibling;
            }
            
            if ( num_selected_sprites > 1 )
            {
                transf_tool_rot = 0;
                transf_tool_size = 0;
            }
            
            transf_tool.rot_offset = -transf_tool_rot;
            
            transf_tool_pos = vec2i( min.x + ((max.x - min.x)/2), min.y + ((max.y - min.y)/2) );
            
            editbox_sprite_pos_x->name = LDEnts(transf_tool_pos.x);
            editbox_sprite_pos_y->name = LDEnts(-transf_tool_pos.y);
            
            editbox_sprite_size_x->name = LDEnts(transf_tool_size.x);
            editbox_sprite_size_y->name = LDEnts(transf_tool_size.y);
            
            editbox_sprite_ap_x->name = LDEnts(transf_tool_size.x/2);
            editbox_sprite_ap_y->name = LDEnts(transf_tool_size.y/2);
            
            editbox_sprite_rot->name = LDEnts( transf_tool_rot );
        }
        
        /////////////// CHANGING ZORDER OF SpriteSheets and Sprites ///////////////
        if ( list_sprites->changed_order )
        {
            vector<LDEuint>spritesheet_zorder_temp;
            spritesheet_zorder_temp.reserve( spritesheets_zorder.size() );
            
            tree<LDEgui_list_item>::iterator item_itr_sprite, item_itr_sprite_begin;
            
            tree<LDEgui_list_item>::sibling_iterator item_itr_sibling = list_sprites->items_tree.end();
            --item_itr_sibling;

            tree<LDEgui_list_item>::sibling_iterator item_itr_sibling_begin = list_sprites->items_tree.begin();
            --item_itr_sibling_begin;
            
            // For every spritesheet folder (backwards)
            while ( item_itr_sibling != item_itr_sibling_begin )
            {
                //cout<<"folder:"<<item_itr_sibling->button.name<<"\n";
                
                LDEuint num_sprites = spritesheets[item_itr_sibling->key].spriteBatchNode.sprites.size();
                
                std::vector<Sprite>sprites_temp;
                sprites_temp.reserve( num_sprites );
                
                item_itr_sprite = list_sprites->items_tree.end(item_itr_sibling);
                --item_itr_sprite;
                item_itr_sprite_begin = list_sprites->items_tree.begin(item_itr_sibling);
                --item_itr_sprite_begin;
                while ( item_itr_sprite != item_itr_sprite_begin )
                {
                    if ( item_itr_sprite->type == 0 )
                    {
                        //cout<<"sprite:"<<item_itr_sprite->button.name<<"\n";
                        
                        sprites_temp.push_back( spritesheets[item_itr_sibling->key].spriteBatchNode.sprites[item_itr_sprite->key] );                     
                        item_itr_sprite->key = sprites_temp.size() - 1;
                    }
                    
                    --item_itr_sprite;
                }
                
                spritesheets[item_itr_sibling->key].spriteBatchNode.sprites = sprites_temp;
                
                spritesheet_zorder_temp.push_back(item_itr_sibling->key);
                
                --item_itr_sibling;
            }
            
            spritesheets_zorder = spritesheet_zorder_temp;
        }
        
        ///////// Sprite properties panel /////////
        
        // Position editboxes
        if ( editbox_sprite_pos_x->changed || editbox_sprite_pos_y->changed )
        {
            vec2i new_position;
            
            // X pos
            if ( editbox_sprite_pos_x->name.length() )
            {
                new_position.x = LDEstn( editbox_sprite_pos_x->name = str_replace(",", ".", editbox_sprite_pos_x->name) );
                
                editbox_sprite_pos_x->name = LDEnts(new_position.x);
            }
            else
                editbox_sprite_pos_x->name = "0";
            
            // Y pos
            if ( editbox_sprite_pos_y->name.length() )
            {
                new_position.y = -LDEstn( editbox_sprite_pos_y->name = str_replace(",", ".", editbox_sprite_pos_y->name) );
                
                editbox_sprite_pos_y->name = LDEnts(-new_position.y);
            }
            else
                editbox_sprite_pos_y->name = "0";
            
            for ( LDEuint i = 0; i < spritesheets.size(); ++i )
            {
                spritesheets[i].spriteBatchNode.setPosition( new_position );
                
                transf_tool_pos = new_position;
                transf_tool.pos = new_position;
            }
        }
        
        // Anchor point editboxes
        if ( editbox_sprite_ap_x->changed || editbox_sprite_ap_y->changed )
        {
            vec2i new_ap;
            
            // X pos
            if ( editbox_sprite_ap_x->name.length() )
            {
                new_ap.x = LDEstn( editbox_sprite_ap_x->name = str_replace(",", ".", editbox_sprite_ap_x->name) );
                
                editbox_sprite_ap_x->name = LDEnts(new_ap.x);
            }
            else
                editbox_sprite_ap_x->name = "0";
            
            // Y pos
            if ( editbox_sprite_ap_y->name.length() )
            {
                new_ap.y = LDEstn( editbox_sprite_ap_y->name = str_replace(",", ".", editbox_sprite_ap_y->name) );
                
                editbox_sprite_ap_y->name = LDEnts(new_ap.y);
            }
            else
                editbox_sprite_ap_y->name = "0";
            
            for ( LDEuint i = 0; i < spritesheets.size(); ++i )
            {
                spritesheets[i].spriteBatchNode.test_coi = 0;
                spritesheets[i].spriteBatchNode.setOffset( new_ap );
            }
        }

        // Size X editbox
        if ( editbox_sprite_size_x->changed )
        {
            vec2i new_size;
            
            // X size
            if ( editbox_sprite_size_x->name.length() )
            {
                new_size.x = LDEstn( editbox_sprite_size_x->name = str_replace(",", ".", editbox_sprite_size_x->name) );
                
                editbox_sprite_size_x->name = LDEnts(new_size.x);
            }
            else
                editbox_sprite_size_x->name = "100";
            
            for ( LDEuint i = 0; i < spritesheets.size(); ++i )
            {
                new_size.y = spritesheets[i].spriteBatchNode.setSizeX( new_size.x, checkbox_sprite_size_keep_ratio->checked );
            }
            
            editbox_sprite_size_y->name = LDEnts(new_size.y);
        }
        
        // Size Y editbox
        if ( editbox_sprite_size_y->changed )
        {
            vec2i new_size;
            
            // Y size
            if ( editbox_sprite_size_y->name.length() )
            {
                new_size.y = LDEstn( editbox_sprite_size_y->name = str_replace(",", ".", editbox_sprite_size_y->name) );
                
                editbox_sprite_size_y->name = LDEnts(new_size.y);
            }
            else
                editbox_sprite_size_y->name = "100";
            
            for ( LDEuint i = 0; i < spritesheets.size(); ++i )
            {
                new_size.y = spritesheets[i].spriteBatchNode.setSizeY( new_size.y, checkbox_sprite_size_keep_ratio->checked );
            }
            
            editbox_sprite_size_x->name = LDEnts(new_size.x);
        }
        
        //
        if ( editbox_sprite_rot->changed )
        {
            LDEfloat new_rot = 0;
            
            // Y size
            if ( editbox_sprite_rot->name.length() )
            {
                new_rot = LDEstn( editbox_sprite_rot->name = str_replace(",", ".", editbox_sprite_rot->name) );
                
                editbox_sprite_rot->name = LDEnts(new_rot);
            }
            else
                editbox_sprite_rot->name = "0";
            
            for ( LDEuint i = 0; i < spritesheets.size(); ++i )
            {
                spritesheets[i].spriteBatchNode.setRotation( new_rot );
            }
        }
        
        //
        if ( editbox_sprite_opacity->changed )
        {
            LDEfloat new_opacity = 0;
            
            // Y size
            if ( editbox_sprite_opacity->name.length() )
            {
                new_opacity = LDEstn( editbox_sprite_opacity->name = str_replace(",", ".", editbox_sprite_opacity->name) );
                
                editbox_sprite_opacity->name = LDEnts(new_opacity);
            }
            else
                editbox_sprite_opacity->name = "1";
            
            for ( LDEuint i = 0; i < spritesheets.size(); ++i )
            {
                spritesheets[i].spriteBatchNode.setOpacity( new_opacity );
            }
        }
    }
    
    // Les boutons en haut (leurs actions quand on les clique !)
    pannel_menu->size.x = app.size.x;
    combobox_editor_mode->pos = vec2i( pannel_menu->size.x - combobox_editor_mode->size.x - 20, 2 );
    
    if ( combobox_editor_mode->changed )
    {
        switchEditorMode( combobox_editor_mode->key() );
    }
    
    if ( menu_button_save->click )
    {
        NSSavePanel *savePanel = [NSSavePanel savePanel];
        
        [savePanel setTitle:@"Enregistrer le projet"];
        [savePanel setNameFieldStringValue:@"projet.feproj"];
        
        if ([savePanel runModal] == NSOKButton)
        {
            string filename = [[[savePanel URL] path] UTF8String];
            
            saveFile(filename);
        }
    }
    
    if ( menu_button_open->click )
    {
        NSOpenPanel *openPanel = [NSOpenPanel openPanel];
        
        if ( [openPanel runModal] == NSOKButton )
        {
            string filename = [[[openPanel URL] path] UTF8String];
            
            openFile(filename);
        }
    }
    
    ////////// EXPORT FOR IPHONE ////////////
    if ( menu_button_export->click )
    {    
        NSSavePanel *savePanel = [NSSavePanel savePanel];
        
        [savePanel setTitle:@"Export data"];
        [savePanel setNameFieldStringValue:@"projet.fedata"];
        
        if ([savePanel runModal] == NSOKButton)
        {
            string filename = [[[savePanel URL] path] UTF8String];
            
            ofstream file;
            
            file.open(filename.c_str());
            
            // Project data
            LDEuint paths_size = paths.size();
            file.write( (char*)&paths_size, sizeof(LDEuint) );
            
            for ( LDEuint i = 0; i < paths_size; ++i )
            {
                LDEuint vertex_size = paths[i].vertex.size();
                file.write( (char*)&vertex_size, sizeof(LDEuint) );
                
                for ( LDEuint v = 0; v < vertex_size; ++v )
                {
                    file.write( (char*)&paths[i].vertex[v].x, sizeof(LDEint) );
                    file.write( (char*)&paths[i].vertex[v].y, sizeof(LDEint) );
                }
            }
        }
    }

    //glRotatef( ++rot_temp, 0, 0, 1 );
    
    /// Draw the GUI by passing cursor position and mouse inputs
    gui.input = app.input;
    gui.mouse = app.mouse;
    gui.app_size = app.size;
    
    gui.draw( app.cursor, 0.01 );
    
    if ( sprite_drag.size.x )
    {
        sprite_drag_size_temp = sprite_drag.size_100;
        
        if ( gui.unused )
        {
            sprite_drag_size_temp = sprite_drag.size;
            
            sprite_drag_size_temp.x = (LDEfloat)sprite_drag_size_temp.x * camera_zoom;
            sprite_drag_size_temp.y = (LDEfloat)sprite_drag_size_temp.y * camera_zoom;
        }
        
        glBindTexture(GL_TEXTURE_2D, sprite_drag.image_id );
        LDErectp( sprite_drag.image_size,
                 vec4i( sprite_drag.texture_uv.x, sprite_drag.texture_uv.y, sprite_drag.texture_uv.z, sprite_drag.texture_uv.w),
                 vec4i( app.cursor.x - sprite_drag_size_temp.x/2, app.cursor.y - sprite_drag_size_temp.y/2, sprite_drag_size_temp.x, sprite_drag_size_temp.y) );
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1,0x0101);
        glColor3f( 0, 1, 0 );
        LDErectw( app.cursor.x - sprite_drag_size_temp.x/2, app.cursor.y - sprite_drag_size_temp.y/2, sprite_drag_size_temp.x, sprite_drag_size_temp.y );
        glColor3f(1,1,1);
        glDisable(GL_LINE_STIPPLE);
        glEnable(GL_TEXTURE_2D);
    }

	app.mouse.erase( app.mouse.begin(), app.mouse.end() );
	app.input.erase( app.input.begin(), app.input.end() );
    
    glFlush();
}

@end
