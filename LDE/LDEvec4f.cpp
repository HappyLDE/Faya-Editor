/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * vec 4 float
\********************************************************************/

#include "LDEvec4f.h"

// Constructor : Put all values to zero
vec4f::vec4f()
{
	reset();
}

// Constructor : Take user values
vec4f::vec4f( LDEfloat x_, LDEfloat y_, LDEfloat z_, LDEfloat w_ )
{
	x = x_;
	y = y_;
	z = z_;
	w = w_;
}

// Destructor : Put all values to zero
vec4f::~vec4f()
{
	reset();
}

// Put all values to zero
void vec4f::reset()
{
	x = y = z = w = 0;
}

// return float value
LDEfloat vec4f::value()
{
	return ( x + y + z + w ) / 4.0f;
}

/// Modify local volues with given ones ///////////////////////////

//// Add //////////////////////////////////////////////////////////

// Add to all values this one value
void vec4f::operator += ( LDEfloat value )
{
	x += value;
	y += value;
	z += value;
	w += value;
}

//// Substract //////////////////////////////////////////

// Substract to all values this one value
void vec4f::operator -= ( LDEfloat value )
{
	x -= value;
	y -= value;
	z -= value;
	w -= value;
}

//// Multiply //////////////////////////////////////////

// Multiply to all values this one value
void vec4f::operator *= ( LDEfloat value )
{
	x *= value;
	y *= value;
	z *= value;
	w *= value;
}

//// Subdivide //////////////////////////////////////////

// Subdivide to all values this one value
void vec4f::operator /= ( LDEfloat value )
{
	x /= value;
	y /= value;
	z /= value;
	w /= value;
}

/// return without modifying local values //////////////////

//// ADD ///////////////////////////////////////////////////

// return added values
vec4f vec4f::operator + ( LDEfloat value )
{
	return vec4f( x + value, y + value, z + value, w + value );
}

//// SUBSTRACT /////////////////////////////////////////////

// return substracted values
vec4f vec4f::operator - ( LDEfloat value )
{
	return vec4f( x - value, y - value, z - value, w - value );
}

//// MULTIPLY /////////////////////////////////////////////

// return multiplied values
vec4f vec4f::operator * ( LDEfloat value )
{
	return vec4f( x * value, y * value, z * value, w * value );
}

//// DIVIDE /////////////////////////////////////////////

// return divided values
vec4f vec4f::operator / ( LDEfloat value )
{
	return vec4f( x / value, y / value, z / value, w / value );
}

/// Assign local values to given one ///////////////////////

void vec4f::operator = ( LDEfloat value )
{
	x = y = z = w = value;
}

/// Assign local values to given ones /////////////////////
void vec4f::operator = ( vec4f value )
{
	x = value.x;
	y = value.y;
	z = value.z;
	w = value.w;
}
