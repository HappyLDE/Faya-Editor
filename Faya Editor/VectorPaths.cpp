#include "VectorPaths.h"

VectorPaths::VectorPaths()
{
    selected = -1;
    active = 0;
}

VectorPaths::~VectorPaths()
{
    selected = -1;
    vertex.erase( vertex.begin(), vertex.end() );
    active = 0;
}

void VectorPaths::addVertex(vec2i pos)
{
    vertex.push_back(pos);
    
    selected = vertex.size()-1;
}

void VectorPaths::draw()
{
    if ( active )
    {
        glLineWidth(2);
        glBegin(GL_LINE_STRIP);
        for ( LDEuint i = 0; i < vertex.size(); ++i )
        {
            if ( selected == i )
                glColor3f(1,0,0);
            else
                glColor3f(0,1,0);
            
            glVertex2i( vertex[i].x, vertex[i].y );
        }
        glEnd();
        
        glColor3f(1,1,0);
        glPointSize(4);
        glBegin(GL_POINTS);
        for ( LDEuint i = 0; i < vertex.size(); ++i )
        {
            glVertex2i( vertex[i].x, vertex[i].y );
        }
        glEnd();
        
        if ( selected > -1 )
        {
            glColor3f(1,0,0);
            glPointSize(8);
            glBegin(GL_POINTS);
            glVertex2i( vertex[selected].x, vertex[selected].y );
            glEnd();
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