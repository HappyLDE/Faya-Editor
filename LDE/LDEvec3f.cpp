/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * vec 3 float
\********************************************************************/

#include "LDEvec3f.h"

// Constructor : Put all values to zero
vec3f::vec3f()
{
	reset();
}

// Constructor : Take user values
vec3f::vec3f( LDEfloat x_, LDEfloat y_, LDEfloat z_ )
{
	x = x_;
	y = y_;
	z = z_;
}

// Destructor : Put all values to zero
vec3f::~vec3f()
{
	reset();
}

// Put all values to zero
void vec3f::reset()
{
	x = y = z = 0;
}

// return float value
LDEfloat vec3f::value()
{
	return ( x + y + z ) / 3.0f;
}

/// Modify local volues with given ones ///////////////////////////

//// Add //////////////////////////////////////////////////////////

// Add to all values this one value
void vec3f::operator += ( LDEfloat value )
{
	x += value;
	y += value;
	z += value;
}

//// Substract //////////////////////////////////////////

// Substract to all values this one value
void vec3f::operator -= ( LDEfloat value )
{
	x -= value;
	y -= value;
	z -= value;
}

//// Multiply //////////////////////////////////////////

// Multiply to all values this one value
void vec3f::operator *= ( LDEfloat value )
{
	x *= value;
	y *= value;
	z *= value;
}

//// Subdivide //////////////////////////////////////////

// Subdivide to all values this one value
void vec3f::operator /= ( LDEfloat value )
{
	x /= value;
	y /= value;
	z /= value;
}

/// return without modifying local values //////////////////

//// ADD ///////////////////////////////////////////////////

// return added values
vec3f vec3f::operator + ( LDEfloat value )
{
	return vec3f( x + value, y + value, z + value );
}

//// SUBSTRACT /////////////////////////////////////////////

// return substracted values
vec3f vec3f::operator - ( LDEfloat value )
{
	return vec3f( x - value, y - value, z - value );
}

//// MULTIPLY /////////////////////////////////////////////

// return multiplied values
vec3f vec3f::operator * ( LDEfloat value )
{
	return vec3f( x * value, y * value, z * value );
}

//// DIVIDE /////////////////////////////////////////////

// return divided values
vec3f vec3f::operator / ( LDEfloat value )
{
	return vec3f( x / value, y / value, z / value );
}

/// Assign local values to given one ///////////////////////

void vec3f::operator = ( LDEfloat value )
{
	x = y = z = value;
}

/// Assign local values to given ones /////////////////////
void vec3f::operator = ( vec3f value )
{
	x = value.x;
	y = value.y;
	z = value.z;
}
