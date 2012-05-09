/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * vec 2 double
\********************************************************************/

#ifndef LDE_VEC2D_H
#define LDE_VEC2D_H

#include "LDEvariables.h"

struct vec2d
{
	LDEdouble x, y;

	void		reset();

	// Value
	LDEdouble	value();	// float

	/// Modify local volues with given one

	// Add to all values this one value
	void operator += ( LDEdouble value );

	// Substract to all values this one value
	void operator -= ( LDEdouble value );

	// Multiply all values with this one
	void operator *= ( LDEdouble value );

	// Subtivide all values with this one
	void operator /= ( LDEdouble value );

	/// Return value with given one without modifying local values

	// return added values
	vec2d operator + ( LDEdouble value );

	// return susbtracted values
	vec2d operator - ( LDEdouble value );

	// return mulitplied values
	vec2d operator * ( LDEdouble value );

	// return divided values
	vec2d operator / ( LDEdouble value );

	/// Assign local values to given one
	void operator = ( LDEdouble value );

	/// Assign local values to given ones
	void operator = ( vec2d value );

	vec2d();
	vec2d( LDEdouble x_, LDEdouble y_ );
	~vec2d();
};

#endif // LDE_VEC2D_H
