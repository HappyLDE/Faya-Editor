/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * LDE texture
\********************************************************************/

#ifndef LDE_LDET_H
#define LDE_LDET_H

#define LDET_NO_FILTER 0
#define LDET_LINEAR 1
#define LDET_BILINEAR 2
#define LDET_TRILINEAR 3
#define LDET_ANISOTROPIC 4

#include <iostream>

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include <string>

// Read and write files capability
#include <sstream>
#include <fstream>

using namespace std;

#include "LDEvariables.h"
#include "LDEvec2i.h"

//#include "LDEfunctions.h"

class LDEldet
{
    public:

    LDEldet();  // constructor
	LDEldet( string name, LDEuint filter ); // constructor
	~LDEldet();

    LDEubyte *data;
    LDEuint h, w, bpp, id, loaded;

	vec2i size;

    // create an empty place for new texture
    bool create( LDEuint width, LDEuint height, LDEuint bpp_ );
    void readScenePixels( LDEint x, LDEint y, LDEint w, LDEint h );
    void resize( LDEuint width, LDEuint height );

    // load image from file
    bool load( string path );

    // get color pixel at point
	void getPixel( LDEuint x, LDEuint y, unsigned char* red, unsigned char* green, unsigned char* blue );

	// set color pixel at point
	void setPixel( LDEuint x, LDEuint y, unsigned char red, unsigned char green, unsigned char blue );

	// set color pixel & alpha at point
	void setPixel( LDEuint x, LDEuint y, unsigned char light, unsigned int alpha );

	// create the OpenGL texture and return it's ID
    LDEuint opengl( LDEuint mode );

    LDEubyte getHeight( LDEuint x, LDEint z, LDEint lod );

    // free stuff
    void erase();
};

#endif // LDE_LDET_H
