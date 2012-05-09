/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * TEXT without the needing to load file
\********************************************************************/

#include "LDEtext.h"

void LDEtext( LDEuint x, LDEuint y, string characters )
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glRasterPos2i(x,y+12);
    for( LDEuint i = 0; i < characters.size(); ++i )
    glBitmap(6, 12, 0.0, 0.0, 7, 0.0, LDE_DEFAULT_FONT[characters[i]-31] );
}
