/*
 *  LDEprimitives.cpp
 *  Faya Editor
 *
 *  Created by Dorin Grigore on 25/07/11.
 *  Copyright 2011 Power Watt. All rights reserved.
 *
 */

#include "LDEprimitives.h"

void LDErectw(LDEint x, LDEint y, LDEint w, LDEint h)
{
	++x;
	--w;
	--h;
    glBegin(GL_LINE_STRIP);
	glVertex2i(x+w,y);
	glVertex2i(x,y);
	glVertex2i(x,y+h);
	glVertex2i(x+w,y+h);
	glVertex2i(x+w,y);
    glEnd();
}

// draw a rectangle
void LDErectuv( LDEfloat uva, LDEfloat uvb, LDEfloat uvc, LDEfloat uvd, LDEfloat uve, LDEfloat uvf, LDEfloat uvg, LDEfloat uvh, LDEint x, LDEint y, LDEint w, LDEint h )
{
    glBegin(GL_QUADS);
	glTexCoord2f(uva,uvb); glVertex2i(w + x,    y);
	glTexCoord2f(uvc,uvd); glVertex2i(    x,    y);
	glTexCoord2f(uve,uvf); glVertex2i(    x,h + y);
	glTexCoord2f(uvg,uvh); glVertex2i(w + x,h + y);
    glEnd();
}

// draw a rectangle
void LDErect( LDEint x, LDEint y, LDEint w, LDEint h )
{
    glBegin(GL_QUADS);
	glTexCoord2i( 0,1); glVertex2i(w + x,    y);
	glTexCoord2i(-1,1); glVertex2i(    x,    y);
	glTexCoord2i(-1,0); glVertex2i(    x,h + y);
	glTexCoord2i( 0,0); glVertex2i(w + x,h + y);
    glEnd();
}

// draw a rectangle with pixel coordinates
void LDErectp( vec2i texture_size, vec4i texture_coord, vec4i conf )
{
	// Calculate texture coordinates
	LDEfloat uv_start_x = -( 1.f - (LDEfloat)texture_coord.x / texture_size.x ),
	uv_start_y = 1.f - ( (LDEfloat)texture_coord.y / texture_size.y ),
	uv_end_x = -( (LDEfloat)(texture_size.x - (texture_coord.z+texture_coord.x)) / texture_size.x ),
	uv_end_y = ( (LDEfloat)(texture_size.y - (texture_coord.w+texture_coord.y)) / texture_size.y );
	
	glBegin(GL_QUADS);
	glTexCoord2f( uv_end_x, 	uv_start_y ); 						glVertex2i( conf.z+conf.x, conf.y );
	glTexCoord2f( uv_start_x, 	uv_start_y ); 						glVertex2i( conf.x, conf.y );
	glTexCoord2f( uv_start_x, 	uv_end_y );  						glVertex2i( conf.x, conf.w+conf.y );
	glTexCoord2f( uv_end_x,		uv_end_y ); 						glVertex2i( conf.z+conf.x, conf.w+conf.y );
	glEnd();
}

void LDEcustomrectp( vec2i texture_size, vec4i config, vec4i uv )
{
	// Up
	LDErectp( texture_size, vec4i( uv.x, 0, texture_size.x - ( uv.z + uv.x ), uv.y ),
			 vec4i( config.x + uv.x, config.y, config.z - ( uv.x + uv.z ), uv.y ) );
	
	// Down
	LDErectp( texture_size, vec4i( uv.x, texture_size.y - uv.w, texture_size.x - ( uv.z + uv.x ), uv.w ),
			 vec4i( config.x + uv.x, config.y + config.w - uv.w, config.z - ( uv.x + uv.z ), uv.w ) );
	
	// Middle
	LDErectp( texture_size, vec4i( uv.x, uv.y, texture_size.x - ( uv.z + uv.x ), texture_size.y - ( uv.y + uv.w ) ),
			 vec4i( config.x + uv.x, config.y + uv.y, config.z - ( uv.x + uv.z ), config.w - ( uv.y + uv.w ) ) );
	
	// Left
	LDErectp( texture_size, vec4i( 0, uv.y, uv.x, texture_size.y - ( uv.y + uv.w ) ),
			 vec4i( config.x, config.y + uv.y, uv.x, config.w - ( uv.y + uv.w ) ) );
	
	// Right
	LDErectp( texture_size, vec4i( texture_size.x - uv.z, uv.y, uv.z, texture_size.y - ( uv.y + uv.w ) ),
			 vec4i( config.x + config.z - uv.z, config.y + uv.y, uv.z, config.w - ( uv.y + uv.w ) ) );
	
	// Up_Left
	LDErectp( texture_size, vec4i( 0, 0, uv.x, uv.y ),
			 vec4i( config.x, config.y, uv.x, uv.y ) );
	
	// Down_Left
	LDErectp( texture_size, vec4i( 0, texture_size.y - uv.w, uv.x, uv.w ),
			 vec4i( config.x, config.y + config.w - uv.w, uv.x, uv.w ) );
	
	// Up_Right
	LDErectp( texture_size, vec4i( texture_size.x - uv.z, 0, uv.z, uv.y ),
			 vec4i( config.x + config.z - uv.z, config.y, uv.z, uv.y ) );
	
	// Down_Right
	LDErectp( texture_size, vec4i( texture_size.x - uv.z, texture_size.y - uv.w, uv.z, uv.w ),
			 vec4i( config.x + config.z - uv.z, config.y + config.w - uv.w, uv.z , uv.w ) );
	
}