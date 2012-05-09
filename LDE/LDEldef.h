/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * FONT
\********************************************************************/

#ifndef LDE_LDEF_H
#define LDE_LDEF_H

#include <OpenGL/gl.h>

#include <string>
#include <vector>

// Read and write files capability
#include <sstream>
#include <fstream>

using namespace std;

#include "LDEvariables.h"
#include "LDEvec2i.h"
#include "LDEvec4f.h"

#include "LDEldet.h"

#include "LDEfunctions.h"

struct LDEfont_character
{
    LDEfont_character();
    ~LDEfont_character();

    vec4f   uv;

    LDEfloat advance;

    vec2i   size;

    LDEint  top,
            left;
};

struct LDEldef
{
	LDEldef();
	~LDEldef();

	string  name;

    vector<LDEfont_character>character;

    LDEuint base;

    LDEuint char_size;

    vec2i   size,
            pos,
            step_back,
			correction;

	bool	loaded;
    wchar_t	current_char;

	wstring	charset;

    LDEldet ldet;

    void    setText( string text );

	void    draw();

    void    setPos( LDEint x_, LDEint y_ );
	void    load( string path );
};

#endif // LDE_LDEF_H
