//
//  Shapes.m
//  Faya Editor
//
//  Created by Dorin Grigore on 3/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Shapes.h"

Shapes::Shapes()
{
    selected = 0;
}

Shapes::~Shapes()
{
    
}

void Shapes::draw()
{
    // The shape (filled)
    glColor3f(0.1,0.1,0.2);
    glBegin(GL_TRIANGLES);
    for ( LDEuint i = 0; i < vertex.size(); ++i )
    {
        glVertex2i( vertex[i].x, vertex[i].y );
    }
    glEnd();
    
    if ( selected )
    {
        glLineWidth(1);
        glColor4f(0,1,0,0.6);
        
        // Wireframe
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        glBegin(GL_TRIANGLES);
        for ( LDEuint i = 0; i < vertex.size(); ++i )
        {
            glVertex2i( vertex[i].x, vertex[i].y );
        }
        glEnd();
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        
        // The path used to create the shape
        glLineWidth(3);
        glColor4f(0,1,1,0.6);
        glBegin(GL_LINE_STRIP);
        for ( LDEuint i = 0; i < path_vertex.size(); ++i )
        {
            glVertex2i( path_vertex[i].x, path_vertex[i].y );
        }
        glEnd();
        
        glLineWidth(1);
    }
    
    glColor3f(1,1,1);
}