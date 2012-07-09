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

void Shapes::addVertex(vec2i pos)
{
    path_vertex.push_back(pos);
    
    selected_vertex = path_vertex.size()-1;
}

void Shapes::triangulate()
{
    // allocate an STL vector to hold the answer.
    Vector2dVector result;
    
    // Invoke the triangulator to triangulate this polygon.
    Triangulate::Process( path_vertex, result );
    
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
            bool    clicked = 0,
            changed_selection = 0;
            
            // If gui isn't on the way
            if ( test_coi )
            {
                // Check for mouse events overall
                for ( LDEuint i = 0; i < mouse.size(); ++i )
                {
                    if ( mouse[i].left && mouse[i].down )
                    {
                        clicked = 1;
                        moving = 0;
                    }
                }
                
                // Keyboard
                for ( LDEuint i = 0; i < input.size(); ++i )
                {
                    // key pressed
                    if ( input[i].key_down )
                    {
                        // G key for moveing
                        if ( input[i].g )
                        {
                            if ( selected_vertex > -1 )
                                moving = 1;
                        }
                        
                        // backspace key for deleting a vertex from the path
                        if ( input[i].backspace )
                        {
                            path_vertex.erase( path_vertex.begin() + selected_vertex );
                            
                            triangulate();
                            
                            selected_vertex = -1;
                        }
                        
                        if ( input[i].lshift )
                            add_to_edge_mode = 1;
                    }
                    else
                    {
                        if ( input[i].lshift )
                            add_to_edge_mode = 0;
                    }
                }
            }
            
            glLineWidth(2);
            glBegin(GL_LINE_STRIP);
            for ( LDEuint i = 0; i < path_vertex.size(); ++i )
            {
                if ( selected_vertex == i )
                    glColor3f(1,0,0);
                else
                    glColor3f(0,1,0);
                
                glVertex2i( path_vertex[i].x, path_vertex[i].y );
            }
            glEnd();
            
            glPointSize(4);
            glLineWidth(1);
            bool already_highlighted = 0;
            for ( LDEuint i = 0; i < path_vertex.size(); ++i )
            {
                glColor3f(1,1,0);
                glBegin(GL_POINTS);
                glVertex2i( path_vertex[i].x, path_vertex[i].y );
                glEnd();
                
                if ( test_coi )
                {
                    
                    if ( cursor.x > path_vertex[i].x - 8 && cursor.x < path_vertex[i].x + 8 &&
                        cursor.y > path_vertex[i].y - 8 && cursor.y < path_vertex[i].y + 8 && !add_to_edge_mode )
                    {
                        glColor3f(1,1,1);
                        LDErectw( path_vertex[i].x - 8, path_vertex[i].y - 8, 16, 16);
                        
                        if ( clicked )
                        {
                            selected_vertex = i;
                            changed_selection = 1;
                        }
                    }
                    
                    // Check every line
                    if ( add_to_edge_mode && !already_highlighted )
                        if ( i )
                        {
                            // Distance from edge and cursor
                            LDEfloat distance = LDEpointLineDist2i( path_vertex[i-1], path_vertex[i], cursor );
                            
                            if ( distance > 0 && distance < 8 )
                            {
                                glLineWidth(3);
                                glColor3f(0, 1, 1);
                                glBegin(GL_LINES);
                                glVertex2i( path_vertex[i-1].x, path_vertex[i-1].y );
                                glVertex2i( path_vertex[i].x, path_vertex[i].y );
                                glEnd();
                                
                                vec2i point_pos = LDEgetPointLineIntersection2i( path_vertex[i-1], path_vertex[i], cursor );
                                
                                glColor3f(0,0,1);
                                LDErect( point_pos.x-4, point_pos.y-4, 8, 8 );
                                
                                if ( clicked )
                                {
                                    path_vertex.insert( path_vertex.begin() + i, point_pos );
                                    selected_vertex = i;
                                    
                                    triangulate();
                                    
                                    add_to_edge_mode = 0;
                                }
                                
                                already_highlighted = 1;
                            }
                        }
                }
            }
            
            if ( selected_vertex > -1 )
            {
                glColor3f(1,0,0);
                glPointSize(8);
                glBegin(GL_POINTS);
                glVertex2i( path_vertex[selected_vertex].x, path_vertex[selected_vertex].y );
                glEnd();
                
                glLineWidth(1);
                glColor3f(1,1,1);
                LDErectw( path_vertex[selected_vertex].x - 4, path_vertex[selected_vertex].y - 4, 8, 8);
            }
            
            // If there are any mouse events
            if ( test_coi )
            {
                for ( LDEuint i = 0; i < mouse.size(); ++i )
                {
                    // If left click
                    if ( mouse[i].left )
                    {
                        // Mouse down click
                        if ( mouse[i].down )
                        {
                            if ( ((selected_vertex == -1 && !path_vertex.size()) || selected_vertex == path_vertex.size()-1) && !changed_selection )
                            {
                                addVertex( cursor );
                                
                                triangulate();
                            }
                        }
                    }
                }
                
                if ( moving )
                {
                    path_vertex[selected_vertex] = cursor;
                    
                    triangulate();
                }
            }
        }
        else
        {
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