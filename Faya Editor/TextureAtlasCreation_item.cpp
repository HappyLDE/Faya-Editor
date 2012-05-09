/*
 *  TextureAtlasCreation_item.cpp
 *  Faya Editor
 *
 *  Created by Dorin Grigore on 14/08/11.
 *  Copyright 2011 Power Watt. All rights reserved.
 *
 */

#include "TextureAtlasCreation_item.h"

TextureAtlasCreation_item::TextureAtlasCreation_item()
{
	selected = 0;
}

TextureAtlasCreation_item::~TextureAtlasCreation_item()
{
    
}

bool TextureAtlasCreation_item::operator()(TextureAtlasCreation_item const &a, TextureAtlasCreation_item const &b) const
{
	return a.image.size.x > b.image.size.x;
}