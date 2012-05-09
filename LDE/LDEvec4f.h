/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * vec 4 float
\********************************************************************/


#ifndef LDE_VEC4F_H
#define LDE_VEC4F_H

#include "LDEvariables.h"

struct vec4f
{
	LDEfloat x, y, z, w;

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
	vec4f operator + ( LDEfloat value );

	// return susbtracted values
	vec4f operator - ( LDEfloat value );

	// return mulitplied values
	vec4f operator * ( LDEfloat value );

	// return divided values
	vec4f operator / ( LDEfloat value );

	/// Assign local values to given one
	void operator = ( LDEfloat value );

	/// Assign local values to given ones
	void operator = ( vec4f value );

	vec4f();
	vec4f( LDEfloat x_, LDEfloat y_, LDEfloat z_, LDEfloat w_ );
	~vec4f();
};

#endif // LDE_vec4f_H
