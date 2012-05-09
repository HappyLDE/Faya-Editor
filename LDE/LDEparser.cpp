/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * // Parse variablies in a text file
\********************************************************************/

#include "LDEparser.h"

LDEparser::LDEparser()
{

}

LDEparser::~LDEparser()
{

}

bool LDEparser::getLine()
{
    word.erase( word.begin(), word.end() );

    // Delete old line
    line.erase( line.begin(), line.end() );

    // Get the new line
    getline(file,line);

    // update it
    iss.clear();
    iss.str( line );

    // say if there was a new line
    return  line.size() ? 1 : 0;
}

bool LDEparser::getWord()
{
    return  iss>>word ? 1 : 0;
}

void LDEparser::load( string name )
{
	if ( name.substr( 0, 1 ) == "/" )
        file.open( name.substr( 1, name.size()-1 ).c_str() );
	else
        file.open( name.c_str() );
}
