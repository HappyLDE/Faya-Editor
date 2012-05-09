/*
 *  TextureAtlasCreation_item.h
 *  Faya Editor
 *
 *  Created by Dorin Grigore on 14/08/11.
 *  Copyright 2011 Power Watt. All rights reserved.
 *
 */

#include "LDEimage.h"

struct TextureAtlasCreation_item
{
	LDEimage image;
	
	vec2i pos;
	
	bool selected;
	bool operator()(TextureAtlasCreation_item const &a, TextureAtlasCreation_item const &b) const;
	
	TextureAtlasCreation_item();
	~TextureAtlasCreation_item();
};