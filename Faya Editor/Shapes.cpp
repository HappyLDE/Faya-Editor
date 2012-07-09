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
    assign_selected = 0;
    test_coi = 0;
    edit_mode = 0;
    selected_vertex = -1;
    add_to_edge_mode = 0;
    moving = 0;
    assign_selected = 0;
    can_change_selected = 0;
}

Shapes::~Shapes()
{
    
}

void Shapes::triangulate()
{
    // allocate an STL vector to hold the answer.
    Vector2dVector result;
    
    // Invoke the triangulator to triangulate this polygon.
    Triangulate::Process( path.vertex, result );
    
    // Pass in the triangulated shape's vertices
    vertex = result;
}

void Shapes::drawEditMode()
{
    if ( selected )
    {
        glLineWidth(1);
        glColor4f(0,1,0,0.6);
        
        // Wireframe
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        glBegin(GL_TRIANGLES);
        for ( LDEuint i = 0; i < vertex.size(); i += 3 )
        {
            glVertex2i( vertex[i].x, vertex[i].y );
            glVertex2i( vertex[i+1].x, vertex[i+1].y );
            glVertex2i( vertex[i+2].x, vertex[i+2].y );
        }
        glEnd();
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        
        if ( edit_mode )
        {
            path.input = input;
            path.mouse = mouse;
            path.test_coi = test_coi;
            path.cursor = cursor;
            path.draw();
            
            if ( path.changed )
                triangulate();
        }
        else
        {
            glLineWidth(3);
            glColor4f(0,1,1,0.6);
            glBegin(GL_LINE_STRIP);
            for ( LDEuint i = 0; i < path.vertex.size(); ++i )
            {
                glVertex2i(path.vertex[i].x, path.vertex[i].y);
            }
            glEnd();
            glLineWidth(1);
        }
    }
    
    glColor3f(1,1,1);
}

void Shapes::draw()
{
    // The shape (filled)
    glColor3f(color.x,color.y,color.z);
    
    bool inside = 0;
         assign_selected = 0;
    
    glBegin(GL_TRIANGLES);
    for ( LDEuint i = 0; i < vertex.size(); i += 3 )
    {
        // If left clicked on that one
        if ( test_coi && can_change_selected )
        for ( LDEuint inp = 0; inp < mouse.size(); ++inp )
        {
            if ( mouse[inp].left && mouse[inp].down )
            {
                assign_selected = 1;
                
                if ( Triangulate::InsideTriangle( vertex[i].x, vertex[i].y,
                                                  vertex[i+1].x, vertex[i+1].y,
                                                  vertex[i+2].x, vertex[i+2].y,
                                                  cursor.x, cursor.y) )
                {
                    
                    inside = 1;
                }
            }
        }
        
        glVertex2i( vertex[i].x, vertex[i].y );
        glVertex2i( vertex[i+1].x, vertex[i+1].y );
        glVertex2i( vertex[i+2].x, vertex[i+2].y );
    }
    glEnd();

    if ( assign_selected )
        selected = inside;
}