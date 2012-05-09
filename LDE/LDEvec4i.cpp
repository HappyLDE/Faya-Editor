/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * vec 3 float
\********************************************************************/

#include "LDEvec4i.h"

// Constructor : Put all values to zero
vec4i::vec4i()
{
	reset();
}

// Constructor : Take user values
vec4i::vec4i( LDEint x_, LDEint y_, LDEint z_, LDEint w_ )
{
	x = x_;
	y = y_;
	z = z_;
	w = w_;
}

// Destructor : Put all values to zero
vec4i::~vec4i()
{
	reset();
}

// Put all values to zero
void vec4i::reset()
{
	x = y = z = w = 0;
}

// return float value
LDEint vec4i::value()
{
	return ( x + y + z + w ) / 4;
}

/// Modify local volues with given ones ///////////////////////////

//// Add //////////////////////////////////////////////////////////

// Add to all values this one value
void vec4i::operator += ( LDEint value )
{
	x += value;
	y += value;
	z += value;
	w += value;
}

//// Substract //////////////////////////////////////////

// Substract to all values this one value
void vec4i::operator -= ( LDEint value )
{
	x -= value;
	y -= value;
	z -= value;
	w -= value;
}

//// Multiply //////////////////////////////////////////

// Multiply to all values this one value
void vec4i::operator *= ( LDEint value )
{
	x *= value;
	y *= value;
	z *= value;
	w *= value;
}

//// Subdivide //////////////////////////////////////////

// Subdivide to all values this one value
void vec4i::operator /= ( LDEint value )
{
	x /= value;
	y /= value;
	z /= value;
	w /= value;
}

/// return without modifying local values //////////////////

//// ADD ///////////////////////////////////////////////////

// return added values
vec4i vec4i::operator + ( LDEint value )
{
	return vec4i( x + value, y + value, z + value, w + value );
}

//// SUBSTRACT /////////////////////////////////////////////

// return substracted values
vec4i vec4i::operator - ( LDEint value )
{
	return vec4i( x - value, y - value, z - value, w - value );
}

//// MULTIPLY /////////////////////////////////////////////

// return multiplied values
vec4i vec4i::operator * ( LDEint value )
{
	return vec4i( x * value, y * value, z * value, w * value );
}

//// DIVIDE /////////////////////////////////////////////

// return divided values
vec4i vec4i::operator / ( LDEint value )
{
	return vec4i( x / value, y / value, z / value, z / value );
}

/// Assign local values to given one ///////////////////////

void vec4i::operator = ( LDEint value )
{
	x = y = z = w = value;
}

/// Assign local values to given ones /////////////////////
void vec4i::operator = ( vec4i value )
{
	x = value.x;
	y = value.y;
	z = value.z;
	w = value.w;
}
