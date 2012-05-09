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

// retourne un nombre alÈatoire entre minimum et maximum
LDEdouble LDErand(LDEdouble min, LDEdouble max)
{
	return (LDEdouble) (min + ((LDEfloat) rand() / RAND_MAX * (max - min + 1.0)));
}

std::string LDEpathOfFile(std::string filename)
{
    return filename.substr( 0, filename.rfind("/") );
}

std::string LDEnameOfFile(std::string filename)
{
    string name_with_ext = filename.substr( filename.rfind("/") + 1 );

    return name_with_ext.substr( 0, name_with_ext.rfind(".") );
}

std::string LDEextOfFile(std::string filename)
{
    string name_with_ext = filename.substr( filename.rfind("/") + 1 );

    return name_with_ext.substr( name_with_ext.rfind(".")+1 );
}

std::wstring StringToWString(const std::string& s)
{
    std::wstring temp(s.length(),L' ');
    std::copy(s.begin(), s.end(), temp.begin());
    return temp;
}

std::string WStringToString(const std::wstring& s)
{
    std::string temp(s.length(), ' ');
    std::copy(s.begin(), s.end(), temp.begin());
    return temp;
}

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

// number to string
string LDEnts( LDEfloat n )
{
    stringstream ss;
    ss << n;
    return ss.str();
}

// number to wstring
wstring LDEntws( LDEfloat n )
{
    stringstream ss;
    ss << n;
    return StringToWString(ss.str());
}

// string to number
LDEfloat LDEstn( string name )
{
    LDEfloat temp = 0;
    istringstream iss( name );
    iss>>temp;
    return temp;
}

// string to char ( if we deal with situations like string+string+string to char
const char *LDEstc( string name )
{
	return name.c_str();
}

LDEfloat LDedist2f(vec2f &start, vec2f &end)
{
	return sqrtf( ((start.x - end.x)*(start.x - end.x)) + ((start.y - end.y)*(start.y - end.y)) );
}