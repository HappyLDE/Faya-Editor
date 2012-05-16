/*********************************************************
 *
 * LDE
 *
 * \ vec 2 int
 *
 * *******************************************************/

#ifndef LDE_VEC2I_H
#define LDE_VEC2I_H

#include "LDEvariables.h"

struct vec2i
{
	LDEint x, y;

	void reset();

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

    vec2i operator + ( vec2i value );
    vec2i operator - ( vec2i value );
    
	// return added values
	vec2i operator + ( LDEint value );

	// return susbtracted values
	vec2i operator - ( LDEint value );

	// return mulitplied values
	vec2i operator * ( LDEint value );

	// return divided values
	vec2i operator / ( LDEint value );

	/// Assign local values to given one
	void operator = ( LDEint value );

	/// Assign local values to given ones
	void operator = ( vec2i value );

	vec2i();
	vec2i( LDEint x_, LDEint y_ );
	~vec2i();
};

#endif // LDE_VEC2I_H
