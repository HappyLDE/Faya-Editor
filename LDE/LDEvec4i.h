/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * vec 4 int
\********************************************************************/


#ifndef LDE_VEC4I_H
#define LDE_VEC4I_H

#include "LDEvariables.h"

struct vec4i
{
	LDEint x, y, z, w;

	void		reset();

	// Value
	LDEint	value();	// float

	/// Modify local volues with given one

	// Add to all values this one value
	void operator += ( LDEint value );

	// Substract to all values this one value
	void operator -= ( LDEint value );

	// Multiply all values with this one
	void operator *= ( LDEint value );

	// Subtivide all values with this one
	void operator /= ( LDEint value );

	/// Return value with given one without modifying local values

	// return added values
	vec4i operator + ( LDEint value );

	// return susbtracted values
	vec4i operator - ( LDEint value );

	// return mulitplied values
	vec4i operator * ( LDEint value );

	// return divided values
	vec4i operator / ( LDEint value );

	/// Assign local values to given one
	void operator = ( LDEint value );

	/// Assign local values to given ones
	void operator = ( vec4i value );

	vec4i();
	vec4i( LDEint x_, LDEint y_, LDEint z_, LDEint w_ );
	~vec4i();
};

#endif // LDE_VEC4I_H
