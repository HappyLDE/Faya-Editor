/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Browse folders and files
\********************************************************************/

#ifndef LDE_DIRECTORY_H
#define LDE_DIRECTORY_H

#include <string>
#include <vector>

using namespace std;

#include "LDEvariables.h"

struct LDEdirectory_folder
{
    string  name;

    LDEdirectory_folder();
    ~LDEdirectory_folder();
};

struct LDEdirectory_file
{
    string  name,
            ext;    // extension

    LDEuint size;

    LDEdirectory_file();
    ~LDEdirectory_file();
};

class LDEdirectory
{
    public:

	NSFileManager *fileManager; 
	
    vector<LDEdirectory_folder>folder;
    vector<LDEdirectory_file>file;

    void open( string path );

    LDEdirectory();
    ~LDEdirectory();
};

#endif // LDE_DIRECTORY_H
