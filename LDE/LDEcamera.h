/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Scene Gamera
\********************************************************************/

#ifndef LDE_CAMERA_H
#define LDE_CAMERA_H

#define PI 3.1415926535897932384626433832795f

#include <math.h>

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include "LDEvariables.h"
#include "LDEvec2i.h"
#include "LDEvec3f.h"

class LDEcamera
{
    public:
    vec3f   rot,
            pos;

    bool    mode;

    vec2i   window; // contains window size

    LDEfloat dist, start_draw, end_draw, persp;

    void set();

    void moveForward( LDEfloat step );
    void moveSide( LDEfloat step );
    void moveUpward( LDEfloat step );

    LDEcamera();
    ~LDEcamera();
};

#endif // LDE_CAMERA_H
