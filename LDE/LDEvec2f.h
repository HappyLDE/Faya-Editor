/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * vec 2 float
\********************************************************************/

#ifndef LDE_VEC2F_H
#define LDE_VEC2F_H

#include "LDEvariables.h"
#include "LDEvec2i.h"

struct vec2f
{
	LDEfloat x, y;

	void		reset();

	// Value
	LDEfloat	value();	// float

	/// Modify local volues with given one

	// Add to all values this one value
	void operator += ( LDEfloat value );

	// Substract to all values this one value
	void operator -= ( LDEfloat value );

	// Multiply all values with this one
	void operator *= ( LDEfloat value );

	// Subtivide all values with this one
	void operator /= ( LDEfloat value );

	/// Return value with given one without modifying local values

	// return added values
	vec2f operator + ( LDEfloat value );

	// return susbtracted values
	vec2f operator - ( LDEfloat value );

	// return mulitplied values
	vec2f operator * ( LDEfloat value );

	// return divided values
	vec2f operator / ( LDEfloat value );

	/// Assign local values to given one
	void operator = ( LDEfloat value );

	/// Assign local values to given ones
	void operator = ( vec2f value );

	vec2f();
    vec2f( vec2i const &pos );
    vec2f( vec2f const &pos );
	vec2f( LDEfloat x_, LDEfloat y_ );
	~vec2f();
};

#endif // LDE_VEC2F_H
