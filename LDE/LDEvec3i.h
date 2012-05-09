/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * vec 3 int
\********************************************************************/


#ifndef LDE_VEC3I_H
#define LDE_VEC3I_H

#include "LDEvariables.h"

struct vec3i
{
	LDEint x, y, z;

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
	vec3i operator + ( LDEint value );

	// return susbtracted values
	vec3i operator - ( LDEint value );

	// return mulitplied values
	vec3i operator * ( LDEint value );

	// return divided values
	vec3i operator / ( LDEint value );

	/// Assign local values to given one
	void operator = ( LDEint value );

	/// Assign local values to given ones
	void operator = ( vec3i value );

	vec3i();
	vec3i( LDEint x_, LDEint y_, LDEint z_ );
	~vec3i();
};

#endif // LDE_VEC3I_H
