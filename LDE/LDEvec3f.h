/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * vec 3 float
\********************************************************************/


#ifndef LDE_VEC3F_H
#define LDE_VEC3F_H

#include "LDEvariables.h"

struct vec3f
{
	LDEfloat x, y, z;

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
	vec3f operator + ( LDEfloat value );

	// return susbtracted values
	vec3f operator - ( LDEfloat value );

	// return mulitplied values
	vec3f operator * ( LDEfloat value );

	// return divided values
	vec3f operator / ( LDEfloat value );

	/// Assign local values to given one
	void operator = ( LDEfloat value );

	/// Assign local values to given ones
	void operator = ( vec3f value );

	vec3f();
	vec3f( LDEfloat x_, LDEfloat y_, LDEfloat z_ );
	~vec3f();
};

#endif // LDE_VEC3F_H
