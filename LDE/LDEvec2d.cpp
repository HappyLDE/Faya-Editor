/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * vec 2 double
\********************************************************************/

#include "LDEvec2d.h"

// Constructor : Put all values to zero
vec2d::vec2d()
{
	reset();
}

// Constructor : Take user values
vec2d::vec2d( LDEdouble x_, LDEdouble y_ )
{
	x = x_;
	y = y_;
}

// Destructor : Put all values to zero
vec2d::~vec2d()
{
	reset();
}

// Put all values to zero
void vec2d::reset()
{
	x = y = 0;
}

// return float value
LDEdouble vec2d::value()
{
	return ( x + y ) / 2.0f;
}

/// Modify local volues with given ones ///////////////////////////

//// Add //////////////////////////////////////////////////////////

// Add to all values this one value
void vec2d::operator += ( LDEdouble value )
{
	x += value;
	y += value;
}

//// Substract //////////////////////////////////////////

// Substract to all values this one value
void vec2d::operator -= ( LDEdouble value )
{
	x -= value;
	y -= value;
}

//// Multiply //////////////////////////////////////////

// Multiply to all values this one value
void vec2d::operator *= ( LDEdouble value )
{
	x *= value;
	y *= value;
}

//// Subdivide //////////////////////////////////////////

// Subdivide to all values this one value
void vec2d::operator /= ( LDEdouble value )
{
	x /= value;
	y /= value;
}

/// return without modifying local values //////////////////

//// ADD ///////////////////////////////////////////////////

// return added values
vec2d vec2d::operator + ( LDEdouble value )
{
	return vec2d( x + value, y + value );
}

//// SUBSTRACT /////////////////////////////////////////////

// return substracted values
vec2d vec2d::operator - ( LDEdouble value )
{
	return vec2d( x - value, y - value );
}

//// MULTIPLY /////////////////////////////////////////////

// return multiplied values
vec2d vec2d::operator * ( LDEdouble value )
{
	return vec2d( x * value, y * value );
}

//// DIVIDE /////////////////////////////////////////////

// return divided values
vec2d vec2d::operator / ( LDEdouble value )
{
	return vec2d( x / value, y / value );
}

/// Assign local values to given one ///////////////////////

void vec2d::operator = ( LDEdouble value )
{
	x = y = value;
}

/// Assign local values to given ones /////////////////////
void vec2d::operator = ( vec2d value )
{
	x = value.x;
	y = value.y;
}
