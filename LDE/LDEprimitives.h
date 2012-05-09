/*
 *  LDEprimitives.h
 *  Faya Editor
 *
 *  Created by Dorin Grigore on 25/07/11.
 *  Copyright 2011 Power Watt. All rights reserved.
 *
 */

#ifndef LDE_PRIMITIVES_H
#define LDE_PRIMITIVES_H

// Open Graphics Library
#include <OpenGL/gl.h>

#include "LDEvariables.h"
#include "LDEvec2i.h"
#include "LDEvec4i.h"

void LDErectw(LDEint x, LDEint y, LDEint w, LDEint h);
void LDErectuv( LDEfloat uva, LDEfloat uvb, LDEfloat uvc, LDEfloat uvd, LDEfloat uve, LDEfloat uvf, LDEfloat uvg, LDEfloat uvh, LDEint x, LDEint y, LDEint w, LDEint h );
void LDErect( LDEint x, LDEint y, LDEint w, LDEint h );
void LDErectp( vec2i texture_size, vec4i texture_coord, vec4i conf );
void LDEcustomrectp( vec2i texture_size, vec4i config, vec4i uv );

#endif