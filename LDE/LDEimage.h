/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Images loader
\********************************************************************/

#ifndef LDE_IMAGE_H
#define LDE_IMAGE_H

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include <iostream>
#include <string>
// Read and write files capability
#include <sstream>
#include <fstream>

#include "LDEvariables.h"
#include "LDEfunctions.h"

#include "LDEvec2i.h"
#include "LDEvec4i.h"

class LDEimage
{
	public:
    LDEuint bpp, id, loaded;
    LDEubyte *data;

	vec2i	size,
			size_gl;
	
	LDEuint cropped_top,
			cropped_bottom,
			cropped_left,
			cropped_right;
	
    std::string model_format, model_path, model_name;

	// create an empty place for new texture
    bool create( LDEuint width, LDEuint height, LDEuint bpp_ );
    void deleteLocalData();
	void reset();

	vec4i getEmptyPixels();
	void  crop( vec4i emptyPixels );
    void  copyMerge( LDEimage &source, vec2i cp_pos );
	LDEint nextPot( LDEint value );
	bool isPot();
	void setPixel( LDEuint x, LDEuint y, LDEubyte r, LDEubyte g, LDEubyte b, LDEubyte a );
	void getPixel( LDEuint x, LDEuint y, LDEubyte *r, LDEubyte *g, LDEubyte *b, LDEubyte *a );
    LDEuint load( std::string path );
    LDEuint opengl( LDEuint mode );
	void save( std::string path );
    bool savePNG( std::string path );
    
	LDEimage();
	~LDEimage();
};

#endif // LDE_IMAGE_H
