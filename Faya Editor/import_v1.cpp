#include "import_v1.h"

using namespace std;

// This function will be removed
void loadScene( string filename )
{
    ifstream file;
    
    file.open(filename.c_str());
    
    LDEint read_FAYA_VERSION = 0;
    
    // File Version
    file.read( (char*)&read_FAYA_VERSION, sizeof(LDEint) );
    
    // Editor behavior
    /*file.read( (char*)&app.size.x, sizeof(LDEint) );
    file.read( (char*)&app.size.y, sizeof(LDEint) );

    //[[self window] setContentSize:NSMakeSize(app.size.x,app.size.y)];

    file.read( (char*)&camera_pos.x, sizeof(LDEfloat) );
    file.read( (char*)&camera_pos.y, sizeof(LDEfloat) );
    file.read( (char*)&camera_zoom, sizeof(LDEfloat) );

    file.read( (char*)&editor_mode, sizeof(bool) );

    switchEditorMode( editor_mode );

    paths.erase( paths.begin(), paths.end() );
    list_vector_paths->erase();
    list_vector_paths->selected = -1;

    // Project data
    LDEuint paths_size = 0;
    file.read( (char*)&paths_size, sizeof(LDEuint) );

    if ( paths_size )
    {
        button_vector_paths_delete->unlock();

        for ( LDEuint i = 0; i < paths_size; ++i )
        {
            VectorPaths path_temp;
            paths.push_back(path_temp);
            
            LDEuint path_id = paths.size()-1;
            
            list_vector_paths->addItem(path_id, "Path "+LDEnts(path_id) );
            
            file.read( (char*)&paths[path_id].selected, sizeof(LDEint) );
            file.read( (char*)&paths[path_id].active, sizeof(bool) );
            
            if ( paths[path_id].active )
                list_vector_paths->select( path_id, 0 );
            
            LDEuint vertex_size = 0;
            file.read( (char*)&vertex_size, sizeof(LDEuint) );
            
            for ( LDEuint v = 0; v < vertex_size; ++v )
            {
                vec2i vertex_pos;
                
                file.read( (char*)&vertex_pos.x, sizeof(LDEint) );
                file.read( (char*)&vertex_pos.y, sizeof(LDEint) );
                
                paths[path_id].addVertex( vertex_pos );
            }
        }
    }*/
}