/**********************************************************************/
/************ HEADER FILE FOR TRIANGULATE.H ***************************/
/**********************************************************************/


#ifndef TRIANGULATE_H
#define TRIANGULATE_H

#include "LDEvariables.h"
#include "LDEvec2i.h"
#include <vector>  // Include STL vector class.

// Typedef an STL vector of vertices which are used to represent
// a polygon/contour and a series of triangles.
typedef std::vector< vec2i > Vector2dVector;

class Triangulate
{
public:
    
    // triangulate a contour/polygon, places results in STL vector
    // as series of triangles.
    static bool Process(const Vector2dVector &contour,
                        Vector2dVector &result);
    
    // compute area of a contour/polygon
    static LDEfloat Area(const Vector2dVector &contour);
    
    // decide if point Px/Py is inside triangle defined by
    // (Ax,Ay) (Bx,By) (Cx,Cy)
    static bool InsideTriangle(LDEfloat Ax, LDEfloat Ay,
                               LDEfloat Bx, LDEfloat By,
                               LDEfloat Cx, LDEfloat Cy,
                               LDEfloat Px, LDEfloat Py);
    
    
private:
    static bool Snip(const Vector2dVector &contour,int u,int v,int w,int n,int *V);
    
};


#endif