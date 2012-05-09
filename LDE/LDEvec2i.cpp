/*********************************************************
 *
 * LDE vec 2 int
 *
 * *******************************************************/

#include "LDEvec2i.h"

// Constructor : Put all values to zero
vec2i::vec2i()
{
	reset();
}

// Constructor : Take user values
vec2i::vec2i( LDEint x_, LDEint y_ )
{
	x = x_;
	y = y_;
}

// Destructor : Put all values to zero
vec2i::~vec2i()
{
	reset();
}

// Put all values to zero
void vec2i::reset()
{
	x = y = 0;
}

// return int value
LDEint vec2i::value()
{
	return ( x + y ) / 2;
}

/// Modify local volues with given ones ///////////////////////////

//// Add //////////////////////////////////////////////////////////

// Add to all values this one value
void vec2i::operator += ( LDEint value )
{
	x += value;
	y += value;
}

//// Substract //////////////////////////////////////////

// Substract to all values this one value
void vec2i::operator -= ( LDEint value )
{
	x -= value;
	y -= value;
}

//// Multiply //////////////////////////////////////////

// Multiply to all values this one value
void vec2i::operator *= ( LDEint value )
{
	x *= value;
	y *= value;
}

//// Subdivide //////////////////////////////////////////

// Subdivide to all values this one value
void vec2i::operator /= ( LDEint value )
{
	x /= value;
	y /= value;
}

/// return without modifying local values //////////////////

//// ADD ///////////////////////////////////////////////////

// return added values
vec2i vec2i::operator + ( LDEint value )
{
	return vec2i( x + value, y + value );
}

//// SUBSTRACT /////////////////////////////////////////////

// return substracted values
vec2i vec2i::operator - ( LDEint value )
{
	return vec2i( x - value, y - value );
}

//// MULTIPLY /////////////////////////////////////////////

// return multiplied values
vec2i vec2i::operator * ( LDEint value )
{
	return vec2i( x * value, y * value );
}

//// DIVIDE /////////////////////////////////////////////

// return divided values
vec2i vec2i::operator / ( LDEint value )
{
	return vec2i( x / value, y / value );
}

/// Assign local values to given one ///////////////////////
void vec2i::operator = ( LDEint value )
{
	x = y = value;
}

/// Assign local values to given ones /////////////////////
void vec2i::operator = ( vec2i value )
{
	x = value.x;
	y = value.y;
}
