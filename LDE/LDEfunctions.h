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

#include <iostream>

LDEdouble LDErand(LDEdouble min, LDEdouble max);

std::wstring StringToWString(const std::string& s);

std::string WStringToString(const std::wstring& s);

std::string& str_replace(const std::string &search, const std::string &replace, std::string &subject);

std::string LDEnts( LDEfloat n );

std::wstring LDEntws( LDEfloat n );

std::string LDEpathOfFile(std::string filename);
std::string LDEnameOfFile(std::string filename);
std::string LDEextOfFile(std::string filename);

LDEfloat LDEstn( std::string name );

const char *LDEstc( std::string name );

LDEfloat LDEdist2f(vec2f &start, vec2f &end);

LDEuint LDEnextPot( LDEuint value );

#endif