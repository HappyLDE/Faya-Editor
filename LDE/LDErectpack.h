/*
 *  LDErectpack.h
 *  Faya Editor
 *
 *  Created by Dorin Grigore on 19/08/11.
 *  Copyright 2011 Power Watt. All rights reserved.
 *
 */

#ifndef LDE_RECT_PACK_H
#define LDE_RECT_PACK_H

#include <string>

using namespace std;

#include "LDEvec4i.h"

struct LDErectpack
{
	vec4i * binRectangle;
	LDErectpack * leftChild;
	LDErectpack * rightChild;
	
	bool filled;
	
	vec4i * insert(vec4i * inputRectangle, LDEuint spacing);
	
	LDErectpack(vec4i * binRectangle);
	~LDErectpack();
};

#endif