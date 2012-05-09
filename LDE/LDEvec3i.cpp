/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * vec 3 float
\********************************************************************/

#include "LDEvec3i.h"

// Constructor : Put all values to zero
vec3i::vec3i()
{
	reset();
}

// Constructor : Take user values
vec3i::vec3i( LDEint x_, LDEint y_, LDEint z_ )
{
	x = x_;
	y = y_;
	z = z_;
}

// Destructor : Put all values to zero
vec3i::~vec3i()
{
	reset();
}

// Put all values to zero
void vec3i::reset()
{
	x = y = z = 0;
}

// return float value
LDEint vec3i::value()
{
	return ( x + y + z ) / 3;
}

/// Modify local volues with given ones ///////////////////////////

//// Add //////////////////////////////////////////////////////////

// Add to all values this one value
void vec3i::operator += ( LDEint value )
{
	x += value;
	y += value;
	z += value;
}

//// Substract //////////////////////////////////////////

// Substract to all values this one value
void vec3i::operator -= ( LDEint value )
{
	x -= value;
	y -= value;
	z -= value;
}

//// Multiply //////////////////////////////////////////

// Multiply to all values this one value
void vec3i::operator *= ( LDEint value )
{
	x *= value;
	y *= value;
	z *= value;
}

//// Subdivide //////////////////////////////////////////

// Subdivide to all values this one value
void vec3i::operator /= ( LDEint value )
{
	x /= value;
	y /= value;
	z /= value;
}

/// return without modifying local values //////////////////

//// ADD ///////////////////////////////////////////////////

// return added values
vec3i vec3i::operator + ( LDEint value )
{
	return vec3i( x + value, y + value, z + value );
}

//// SUBSTRACT /////////////////////////////////////////////

// return substracted values
vec3i vec3i::operator - ( LDEint value )
{
	return vec3i( x - value, y - value, z - value );
}

//// MULTIPLY /////////////////////////////////////////////

// return multiplied values
vec3i vec3i::operator * ( LDEint value )
{
	return vec3i( x * value, y * value, z * value );
}

//// DIVIDE /////////////////////////////////////////////

// return divided values
vec3i vec3i::operator / ( LDEint value )
{
	return vec3i( x / value, y / value, z / value );
}

/// Assign local values to given one ///////////////////////

void vec3i::operator = ( LDEint value )
{
	x = y = z = value;
}

/// Assign local values to given ones /////////////////////
void vec3i::operator = ( vec3i value )
{
	x = value.x;
	y = value.y;
	z = value.z;
}
