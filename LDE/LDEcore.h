/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Core
\********************************************************************/

#ifndef LDE_H
#define LDE_H

#include <string>
#include <vector>

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

using namespace std;

#include "LDEvariables.h"
#include "LDEvec2i.h"
#include "LDEvec2f.h"

#include "LDEinput.h"

class LDE
{
	public:
	//ofstream	out;

	vector<LDEmouse_event>mouse; // list of mouse events in one frame
	vector<LDEinput>input;
    bool input_lcmd,
         input_rcmd;
	
	vec2i		cursor,
				size;
	vec2f		cursor_force;

    LDEdouble   ft,
                last_ft;

    LDEfloat    fps();

	bool		working;	// if true then app is running

	LDEint		init( LDEuint myWidth, LDEuint myHeight, wstring title );

    LDEdouble	getTicks();

	void		stop();
	bool		run( void (*scene)() );

	LDE();
	~LDE();
};

#endif // LDE_H
