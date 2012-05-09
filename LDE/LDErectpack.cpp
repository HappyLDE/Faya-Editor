/*
 *  LDErectpack.cpp
 *  Faya Editor
 *
 *  Created by Dorin Grigore on 19/08/11.
 *  Copyright 2011 Power Watt. All rights reserved.
 *
 */

#include "LDErectpack.h"

////////
LDErectpack::LDErectpack(vec4i * binRectangle)
{
	this->binRectangle = binRectangle;
	leftChild = NULL;
	rightChild = NULL;
	filled = false;
}

LDErectpack::~LDErectpack()
{
	
}

vec4i * LDErectpack::insert(vec4i * inputRectangle, LDEuint spacing)
{
	if(leftChild != NULL || rightChild != NULL)
	{
		vec4i * leftRectangle = leftChild->insert(inputRectangle, spacing);
		if(leftRectangle == NULL)
		{
			return rightChild->insert(inputRectangle, spacing);
		}
		return leftRectangle;
	}
	else
	{
		if(filled || inputRectangle->z > binRectangle->z || inputRectangle->w > binRectangle->w)
		{
			return NULL;
		}
		
		if(inputRectangle->z == binRectangle->z && inputRectangle->w == binRectangle->w)
		{
			filled = true;
			return binRectangle;
		}
		
		int widthDifference = binRectangle->z - inputRectangle->z;
		int heightDifference = binRectangle->w - inputRectangle->w;
		
		vec4i * leftRectangle = new vec4i(*binRectangle);
		vec4i * rightRectangle = new vec4i(*binRectangle);
		
		if(widthDifference > heightDifference)
		{
			leftRectangle->z = inputRectangle->z;
			rightRectangle->x += inputRectangle->z + spacing;
			rightRectangle->z -= inputRectangle->z + spacing;
		}
		else
		{
			leftRectangle->w = inputRectangle->w;
			rightRectangle->y += inputRectangle->w + spacing;
			rightRectangle->w -= inputRectangle->w + spacing;
		}
		
		leftChild = new LDErectpack(leftRectangle);
		rightChild = new LDErectpack(rightRectangle);
		
		return leftChild->insert(inputRectangle, spacing);
	}
}