//
//  OpenGLView.h
//  Faya Editor
//
//  Created by Dorin Grigore on 6/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#include "LDE.h"
#include "TextureAtlasCreation_item.h"
#include "Spritesheet.h"
#include "Vector.h"
#include "SpriteBatchNode.h"
#include "import_v1.h"

// Pixel to Meter Ratio
#define PTM_RATIO 64

void switchEditorMode( LDEuint mode );
void saveFile( std::string filename );
void openFile( std::string filename );

void drawable_texture_atlas_scene(vec2i mypos, vec2i mysize, bool mytest_coi, LDEfloat myframetime );
void drawable_spritesheets_scene(vec2i mypos, vec2i mysize, bool mytest_coi, LDEfloat myframetime );

@interface OpenGLView : NSOpenGLView

-(void) prepareOpenGL;

@end
