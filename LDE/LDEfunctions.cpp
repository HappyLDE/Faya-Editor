/*
 *  LDEfunctions.cpp
 *  Faya Editor
 *
 *  Created by Dorin Grigore on 25/07/11.
 *  Copyright 2011 Power Watt. All rights reserved.
 *
 */

#include "LDEfunctions.h"

using namespace std;

// Finds the next power of two number (used for OpenGL images for example)
LDEuint LDEnextPot( LDEuint value )
{
	for ( LDEuint i = 2; i <= 8192; i *= 2 )
	{
		if ( i > value )
		{
			value = i;
			break;
		}
	}
	
	return value;
}

// Returns random double between min and max
LDEdouble LDErand(LDEdouble min, LDEdouble max)
{
	return (LDEdouble) (min + ((LDEfloat) rand() / RAND_MAX * (max - min + 1.0)));
}

// Returns string with only the path of file (las slash excluded)
std::string LDEpathOfFile(std::string filename)
{
    return filename.substr( 0, filename.rfind("/") );
}

// Returns string with the name of file from a given path (extension excluded)
std::string LDEnameOfFile(std::string filename)
{
    string name_with_ext = filename.substr( filename.rfind("/") + 1 );

    return name_with_ext.substr( 0, name_with_ext.rfind(".") );
}

// Returns string with the extension of file from a given path (point excluded)
std::string LDEextOfFile(std::string filename)
{
    string name_with_ext = filename.substr( filename.rfind("/") + 1 );

    return name_with_ext.substr( name_with_ext.rfind(".")+1 );
}

// Returns wstring from string (string to wstring)
std::wstring LDEstws(const std::string& s)
{
    std::wstring temp(s.length(),L' ');
    std::copy(s.begin(), s.end(), temp.begin());
    return temp;
}

// Returns string from wstring (wstring to string)
std::string LDEwsts(const std::wstring& s)
{
    std::string temp(s.length(), ' ');
    std::copy(s.begin(), s.end(), temp.begin());
    return temp;
}

// The awesome PHP function, replace string in string from string
string& str_replace(const string &search, const string &replace, string &subject)
{
    string buffer;
	
    int sealeng = search.length();
    int strleng = subject.length();
	
    if (sealeng==0)
        return subject;//no change
	
    for(int i=0, j=0; i<strleng; j=0 )
    {
        while (i+j<strleng && j<sealeng && subject[i+j]==search[j])
            j++;
        if (j==sealeng)//found 'search'
        {
            buffer.append(replace);
            i+=sealeng;
        }
        else
        {
            buffer.append( &subject[i++], 1);
        }
    }
    subject = buffer;
    return subject;
}

// return string number (same as parseFloat)
string LDEnts( LDEfloat n )
{
    stringstream ss;
    ss << n;
    return ss.str();
}

// return wstring number (same as parseFloat)
wstring LDEntws( LDEfloat n )
{
    stringstream ss;
    ss << n;
    return LDEstws(ss.str());
}

// Returns float number from given string
LDEfloat LDEstn( string name )
{
    LDEfloat temp = 0;
    istringstream iss( name );
    iss>>temp;
    return temp;
}

// this function is only useful when you want to compose a full filepath from strings
// eg: file.open( LDEstc(path+'/'+name+'.'+ext) );
const char *LDEstc( string name )
{
	return name.c_str();
}

// Returns the distance between two 2D points
LDEfloat LDedist2f(vec2f &start, vec2f &end)
{
	return sqrtf( ((start.x - end.x)*(start.x - end.x)) + ((start.y - end.y)*(start.y - end.y)) );
}