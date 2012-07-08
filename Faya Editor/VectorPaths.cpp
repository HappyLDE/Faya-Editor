#include "VectorPaths.h"

VectorPaths::VectorPaths()
{
    selected_vertex = -1;
    active = 0;
    moving = 0;
    test_coi = 0;
    add_to_edge_mode = 0;
}

VectorPaths::~VectorPaths()
{
    selected_vertex = -1;
    vertex.erase( vertex.begin(), vertex.end() );
    active = 0;
}

void VectorPaths::addVertex(vec2i pos)
{
    vertex.push_back(pos);
    
    selected_vertex = vertex.size()-1;
}

void VectorPaths::draw()
{
    if ( active )
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
                        vertex.erase( vertex.begin() + selected_vertex );
                        
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
        for ( LDEuint i = 0; i < vertex.size(); ++i )
        {
            if ( selected_vertex == i )
                glColor3f(1,0,0);
            else
                glColor3f(0,1,0);
            
            glVertex2i( vertex[i].x, vertex[i].y );
        }
        glEnd();
        
        glPointSize(4);
        glLineWidth(1);
        bool already_highlighted = 0;
        for ( LDEuint i = 0; i < vertex.size(); ++i )
        {
            glColor3f(1,1,0);
            glBegin(GL_POINTS);
            glVertex2i( vertex[i].x, vertex[i].y );
            glEnd();
            
            if ( test_coi )
            {
                if ( cursor.x > vertex[i].x - 8 && cursor.x < vertex[i].x + 8 &&
                     cursor.y > vertex[i].y - 8 && cursor.y < vertex[i].y + 8 )
                {
                    glColor3f(1,1,1);
                    LDErectw( vertex[i].x - 8, vertex[i].y - 8, 16, 16);
                    
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
                    if ( LDEpointLineDist2i( vertex[i-1], vertex[i], cursor ) < 8 )
                    {
                        glLineWidth(3);
                        glColor3f(0, 1, 1);
                        glBegin(GL_LINES);
                            glVertex2i( vertex[i-1].x, vertex[i-1].y );
                            glVertex2i( vertex[i].x, vertex[i].y );
                        glEnd();
                        
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
            glVertex2i( vertex[selected_vertex].x, vertex[selected_vertex].y );
            glEnd();
            
            glLineWidth(1);
            glColor3f(1,1,1);
            LDErectw( vertex[selected_vertex].x - 4, vertex[selected_vertex].y - 4, 8, 8);
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
                        if ( ((selected_vertex == -1 && !vertex.size()) || selected_vertex == vertex.size()-1) && !changed_selection )
                        {
                            addVertex( cursor );
                        }
                    }
                }
            }
            
            if ( moving )
                vertex[selected_vertex] = cursor;
        }
    }
    else
    {
        glLineWidth(1);
        glColor4f(0,1,0,0.6);
        
        glBegin(GL_LINE_STRIP);
        for ( LDEuint i = 0; i < vertex.size(); ++i )
        {
            glVertex2i( vertex[i].x, vertex[i].y );
        }
        glEnd();
    }
    
    glColor3f(1,1,1);
    glLineWidth(1);
}