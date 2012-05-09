/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * vec 2 float
\********************************************************************/

#include "LDEvec2f.h"

// Constructor : Put all values to zero
vec2f::vec2f()
{
	reset();
}

// Constructor : Take user values
vec2f::vec2f( LDEfloat x_, LDEfloat y_ )
{
	x = x_;
	y = y_;
}

// Destructor : Put all values to zero
vec2f::~vec2f()
{
	reset();
}

// Put all values to zero
void vec2f::reset()
{
	x = y = 0;
}

// return float value
LDEfloat vec2f::value()
{
	return ( x + y ) / 2.0f;
}

/// Modify local volues with given ones ///////////////////////////

//// Add //////////////////////////////////////////////////////////

// Add to all values this one value
void vec2f::operator += ( LDEfloat value )
{
	x += value;
	y += value;
}

//// Substract //////////////////////////////////////////

// Substract to all values this one value
void vec2f::operator -= ( LDEfloat value )
{
	x -= value;
	y -= value;
}

//// Multiply //////////////////////////////////////////

// Multiply to all values this one value
void vec2f::operator *= ( LDEfloat value )
{
	x *= value;
	y *= value;
}

//// Subdivide //////////////////////////////////////////

// Subdivide to all values this one value
void vec2f::operator /= ( LDEfloat value )
{
	x /= value;
	y /= value;
}

/// return without modifying local values //////////////////

//// ADD ///////////////////////////////////////////////////

// return added values
vec2f vec2f::operator + ( LDEfloat value )
{
	return vec2f( x + value, y + value );
}

//// SUBSTRACT /////////////////////////////////////////////

// return substracted values
vec2f vec2f::operator - ( LDEfloat value )
{
	return vec2f( x - value, y - value );
}

//// MULTIPLY /////////////////////////////////////////////

// return multiplied values
vec2f vec2f::operator * ( LDEfloat value )
{
	return vec2f( x * value, y * value );
}

//// DIVIDE /////////////////////////////////////////////

// return divided values
vec2f vec2f::operator / ( LDEfloat value )
{
	return vec2f( x / value, y / value );
}

/// Assign local values to given one ///////////////////////

void vec2f::operator = ( LDEfloat value )
{
	x = y = value;
}

/// Assign local values to given ones /////////////////////
void vec2f::operator = ( vec2f value )
{
	x = value.x;
	y = value.y;
}
