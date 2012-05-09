/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Scene Gamera
\********************************************************************/

#include "LDEcamera.h"

LDEcamera::LDEcamera()
{
    dist = 0;

    mode = 0;

    persp = 45.0f;

    start_draw = 0.1f;
    end_draw = 1000.0f;
}

LDEcamera::~LDEcamera()
{

}

void LDEcamera::moveForward( LDEfloat step )
{
    pos.x -= (LDEfloat)sin(-rot.y * PI/180) * step;
    pos.z -= (LDEfloat)cos(-rot.y * PI/180) * step;
    pos.y -= (LDEfloat)tan( rot.x * PI/180) * step;
}

void LDEcamera::moveSide( LDEfloat step )
{
    pos.x += (LDEfloat)sin(-rot.y * 0.0174532925f - 1.570796325f) * step;
    pos.z += (LDEfloat)cos(-rot.y * 0.0174532925f - 1.570796325f) * step;
}

void LDEcamera::moveUpward( LDEfloat step )
{
    pos.y -= (LDEfloat)tan(-rot.x * 0.0174532925f - 1.570796325f) * step;
    pos.x += (LDEfloat)sin(-rot.y * PI/180) * step;
    pos.z += (LDEfloat)cos(-rot.y * PI/180) * step;
}

void LDEcamera::set()
{
    if ( mode )
    {
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D( 0, window.x, window.y, 0 );

        glDisable( GL_COLOR );

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);
        glDisable(GL_CULL_FACE);
    }
    else
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective( persp,(LDEfloat)window.x/window.y, start_draw, end_draw );
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glEnable( GL_COLOR );

        glTranslatef(0,0,-dist);
        glRotatef(rot.x,1,0,0);
        glRotatef(rot.y,0,1,0);
        glRotatef(rot.z,0,0,1);
        glTranslatef(-pos.x,-pos.y,-pos.z);

        glDisable(GL_BLEND);
        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
    }
}
