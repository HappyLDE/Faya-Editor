/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * // Parse variablies in a text file
\********************************************************************/

#ifndef LDE_PARSER_H
#define LDE_PARSER_H

#include <string>

// Read and write files capability
#include <sstream>
#include <fstream>

using namespace std;

class LDEparser
{
    public:

    void load( string name );

    ifstream file;

    string  line,
            word;

    istringstream iss;

    bool getLine();
    bool getWord();

    LDEparser();
    ~LDEparser();
};

#endif // LDE_PARSER_H
