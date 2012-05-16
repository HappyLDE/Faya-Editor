/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Functions
 \********************************************************************/

#ifndef LDE_FUNCTIONS_H
#define LDE_FUNCTIONS_H

#include <string>

// Read and write files capability
#include <sstream>
#include <fstream>

#include <math.h>

#include "LDEvariables.h"
#include "LDEvec2f.h"
#include "LDEvec2i.h"
#include <iostream>

// Finds the next power of two number (used for OpenGL images for example)
LDEuint LDEnextPot( LDEuint value );

// Returns random double between min and max
LDEdouble LDErand(LDEdouble min, LDEdouble max);

// Returns wstring from string (string to wstring)
std::wstring LDEstws(const std::string& s);

// Returns string from wstring (wstring to string)
std::string LDEwsts(const std::wstring& s);

// The awesome PHP function, replace string in string from string
std::string& str_replace(const std::string &search, const std::string &replace, std::string &subject);

// return string number (same as parseFloat)
std::string LDEnts( LDEfloat n );

// return wstring number (same as parseFloat)
std::wstring LDEntws( LDEfloat n );

// Returns string with only the path of file (las slash excluded)
std::string LDEpathOfFile(std::string filename);

// Returns string with the name of file from a given path (extension excluded)
std::string LDEnameOfFile(std::string filename);

// Returns string with the extension of file from a given path (point excluded)
std::string LDEextOfFile(std::string filename);

// Returns float number from given string
LDEfloat LDEstn( std::string name );

// eg: file.open( LDEstc(path+'/'+name+'.'+ext) );
const char *LDEstc( std::string name );

// Returns the distance between two 2D points
LDEfloat LDEdist2f(vec2f &start, vec2f &end);

LDEdouble LDEangle2i( vec2i a, vec2i b );

#endif