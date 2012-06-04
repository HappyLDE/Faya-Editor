/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Images loader
\********************************************************************/

#include "LDEimage.h"

using namespace std;

// Constructor
LDEimage::LDEimage()
{
	bpp = 0;
	this->id = 0;
	loaded = 0;
	
	cropped_top = 0,
	cropped_bottom = 0,
	cropped_left = 0,
	cropped_right = 0;
}

void LDEimage::reset()
{
	bpp = 0;
	this->id = 0;
	loaded = 0;
	
	cropped_top = 0,
	cropped_bottom = 0,
	cropped_left = 0,
	cropped_right = 0;
	size.reset();
}

// Destructor
LDEimage::~LDEimage()
{
	//deleteLocalData();
	//reset();
}

// create an empty place for new texture
bool LDEimage::create( LDEuint width, LDEuint height, LDEuint bpp_ )
{
	//set the member variables
	size.x = width;
	size.y = height;
	bpp = bpp_;

	//allocate memory
	data = new LDEubyte[ size.x*size.y*bpp ];

	if( data )
	{
		for ( LDEuint i = 0; i < size.x*size.y*bpp; ++i )
        {
            data[i] = 0;
        }
	}
    else
    {
        //cout<<"Error : out of memory";
        loaded = 0;
    }

	//set the loaded flag
	loaded = 1;

	return loaded;
}

void LDEimage::deleteLocalData()
{
	if ( data != NULL )
	{
		delete []data;
		data = NULL;
	}
}

// get rgba pixel at point
void LDEimage::getPixel( LDEuint x, LDEuint y, LDEubyte *r, LDEubyte *g, LDEubyte *b, LDEubyte *a )
{
    if ( x <= size.x && y <= size.y )
	{
		*r = data[ ((y*size.x)+x)*bpp   ];
		*g = data[ ((y*size.x)+x)*bpp+1 ];
		*b = data[ ((y*size.x)+x)*bpp+2 ];
		
		if ( bpp == 4 )
			*a = data[ ((y*size.x)+x)*bpp+3 ];
	}
}

// set rgba pixel at point
void LDEimage::setPixel( LDEuint x, LDEuint y, LDEubyte r, LDEubyte g, LDEubyte b, LDEubyte a )
{
    if ( x <= size.x && y <= size.y )
	{
		data[ ((y*size.x)+x)*bpp   ] = r;
		data[ ((y*size.x)+x)*bpp+1 ] = g;
		data[ ((y*size.x)+x)*bpp+2 ] = b;
		
		if ( bpp == 4 )
			data[ ((y*size.x)+x)*bpp+3 ] = a;
	}
}

LDEuint LDEimage::load( string path )
{
	model_path = path.substr( 0, path.rfind("/") );
	model_name = path.substr( path.rfind("/")+1, path.rfind(".")-(path.rfind("/")+1) );
	model_format = path.substr( path.rfind(".")+1, path.length()-path.rfind(".")+1 );
	
	NSString *path_objc = [NSString stringWithCString:path.c_str() encoding:NSUTF8StringEncoding];

	NSBitmapImageRep *rep = [NSBitmapImageRep imageRepWithContentsOfFile:path_objc];
	
	if ( rep != nil )
	{
		size.x = [rep pixelsWide];
		size.y = [rep pixelsHigh];
		size_gl = size;
		
		bpp = ( [rep bitsPerPixel] == 32 ? 4 : 3 );

		data = new LDEubyte[size.x*size.y*bpp];

		LDEubyte *flipped_data = [rep bitmapData];
		
		LDEint bytesPerRow = [rep bytesPerRow];
		for ( LDEuint i = 0; i < size.y; ++i )
		{
			bcopy((flipped_data + bytesPerRow * i), (data + bytesPerRow * (size.y - i - 1)), bytesPerRow);
		}
		
		loaded = 1;
	}
	else
	{
		cout << " ! Error loading image \""<<model_path<<"/"<<model_name<<"."<<model_format<<"\"\n";
		
		loaded = 0;
	}
	
	return loaded;
}

bool LDEimage::isPot()
{
	bool	x_is_pot = 0,
			y_is_pot = 0;

	for ( LDEuint i = 2; i <= 8192; i *= 2 )
	{
		if ( size.x == i )
			x_is_pot = 1;
		
		if ( size.y == i )
			y_is_pot = 1;
	}
	
	return (x_is_pot && y_is_pot);
}

LDEint LDEimage::nextPot( LDEint value )
{
	for ( LDEuint i = 2; i <= 8192; i *= 2 )
	{
		if ( i > value )
		{
			value = i;
			break;
		}
	}
	
	return value;
}

vec4i LDEimage::getEmptyPixels()
{
	vec4i emptyPixels;

	// Only check for empty pixels if we have ALPHA (transparency)
	if ( bpp == 4 )
	{
		LDEuint position_gl = 0;
		bool foundPixel = 0;
		bool foundPixelLeft = 0;
		
		// De gauche à droite
		for ( LDEuint x = 0; x < size.x; ++x )
		{
			foundPixel = 0;
			
			for ( LDEuint y = 0; y < size.y; ++y )
			{
				position_gl = (x+(y*size.x))*4;

				if ( (LDEuint)data[position_gl+3] )
					foundPixel = 1;
			}
			
			if ( !foundPixelLeft && !foundPixel )
			{
				++emptyPixels.x;
			}
			else if ( !foundPixelLeft && foundPixel )
			{
				foundPixelLeft = 1;
			}

			if ( foundPixelLeft && !foundPixel )
				++emptyPixels.z;
			
			if ( foundPixelLeft && foundPixel )
				emptyPixels.z = 0;
		}
		
		foundPixel = 0;
		foundPixelLeft = 0;
		// De gauche à droite
		for ( LDEuint y = 0; y < size.y; ++y )
		{
			foundPixel = 0;
			
			for ( LDEuint x = 0; x < size.x; ++x )
			{
				position_gl = (x+(y*size.x))*4;

				if ( (LDEuint)data[position_gl+3] )
					foundPixel = 1;
			}
			
			if ( !foundPixelLeft && !foundPixel )
			{
				++emptyPixels.w;
			}
			else if ( !foundPixelLeft && foundPixel )
			{
				foundPixelLeft = 1;
			}
			
			if ( foundPixelLeft && !foundPixel )
				++emptyPixels.y;
			
			if ( foundPixelLeft && foundPixel )
				emptyPixels.y = 0;
		}
		
		cropped_bottom = emptyPixels.w;
		cropped_top = emptyPixels.y;
		
		cropped_left = emptyPixels.x;
		cropped_right = emptyPixels.z;
		
		emptyPixels.z = size.x - (cropped_left+cropped_right);
		emptyPixels.w = size.y - (cropped_top+cropped_bottom);
	}
	
	return emptyPixels;
}

void LDEimage::copyMerge( LDEimage &source, vec2i cp_pos )
{
    LDEint pos_top = size.y - source.size.y;
    
    for ( LDEuint x = 0; x < source.size.x; ++x )
    for ( LDEuint y = 0; y < source.size.y; ++y )
    {
        LDEuint p = ((x+cp_pos.x)+(((y+pos_top)-cp_pos.y)*size.x))*bpp; // position actual data
        LDEuint p_source = (x+(y*source.size.x))*source.bpp; // Position source data
        
        data[p] = source.data[p_source];        // Red
        data[p+1] = source.data[p_source+1];    // Green
        data[p+2] = source.data[p_source+2];	// Blue
        
        if ( bpp == 4 )
            data[p+3] = source.data[p_source+3];	// Alpha (Transparency)
    }
}

void LDEimage::crop( vec4i emptyPixels )
{
	//if ( emptyPixels.z != size.x && emptyPixels.w != size.y )
	{
		LDEubyte *new_data = new LDEubyte[emptyPixels.z*emptyPixels.w*bpp];

        LDEint pos_top = size.y-(emptyPixels.w+emptyPixels.y);
        
		for ( LDEuint x = 0; x < emptyPixels.z; ++x )
		for ( LDEuint y = 0; y < emptyPixels.w; ++y )
		{
            LDEuint p = (x+(y*emptyPixels.z))*bpp; // Position actual data
            LDEuint p_source = ((x+emptyPixels.x)+((y+pos_top)*size.x))*bpp; // Position source data
            
			new_data[p]   = data[p_source];      // Red
			new_data[p+1] = data[p_source+1];	// Green
			new_data[p+2] = data[p_source+2];	// Blue
			
			if ( bpp == 4 )
				new_data[p+3] = data[p_source+3];	// Alpha (Transparency)
		}
		
		delete []data;
		data = NULL;
		
		size.x = emptyPixels.z;
		size.y = emptyPixels.w;
		size_gl = size;
		data = new LDEubyte[size.x*size.y*bpp];
		
        for ( LDEuint i = 0; i < size.x*size.y*bpp; ++i )
        {
            data[i] = new_data[i];
        }
		
		delete []new_data;
		new_data = NULL;
		
		//cout<<"Cropped image \""<<model_name<<"."<<model_format<<"\" to x"<<emptyPixels.x<<" y"<<emptyPixels.y<<" w"<<emptyPixels.z<<" h"<<emptyPixels.w<<"\n";
        
        emptyPixels.reset();
	}
}

LDEuint LDEimage::opengl( LDEuint mode )
{
	if ( loaded )
	{
		bool is_pot = isPot();
		
		glGenTextures( 1, &id );
		glBindTexture( GL_TEXTURE_2D, id );

		if ( is_pot )
		{
			gluBuild2DMipmaps(GL_TEXTURE_2D,
							  bpp,    // bpp
							  size.x,      // largeur
							  size.y,      // hauteur
							  ( bpp == 3 ? GL_RGB : GL_RGBA ), // type
							  GL_UNSIGNED_BYTE, //
							  data ); // contains image data
		}
		else
		{
            LDEubyte *data_gl;

            size_gl.x = nextPot( size.x );
            size_gl.y = nextPot( size.y );
            
            data_gl = new LDEubyte[size_gl.x*size_gl.y*bpp];
            
            for ( LDEuint i = 0; i < size_gl.x*size_gl.y*bpp; ++i )
                data_gl[i] = 0;
            
            LDEuint y_offset = size_gl.y - size.y;
            
            for ( LDEuint x = 0; x < size_gl.x; ++x )
            for ( LDEuint y = 0; y < size_gl.y; ++y )
            {
                if ( x < size.x && y < size.y )
                {
                    LDEuint position_gl = (x+((y+y_offset)*size_gl.x))*bpp;
                    LDEuint position = (x+(y*size.x))*bpp;
                    
                    data_gl[position_gl]   = data[position];	// Red
                    data_gl[position_gl+1] = data[position+1];	// Green
                    data_gl[position_gl+2] = data[position+2];	// Blue
                    
                    if ( bpp == 4 )
                        data_gl[position_gl+3] = data[position+3];	// Alpha (Transparency)
                }
            }
            
            //cout<<"Resized for OpenGL \""<<model_name<<"."<<model_format<<"\" from "<<size.x<<"x"<<size.y<<"px to "<<size_gl.x<<"x"<<size_gl.y<<"px\n";
            
			gluBuild2DMipmaps(GL_TEXTURE_2D,
							  bpp,    // bpp
							  size_gl.x,      // largeur
							  size_gl.y,      // hauteur
							  GL_RGBA, // type
							  GL_UNSIGNED_BYTE, //
							  data_gl ); // contains image data
			
			delete []data_gl;
			data_gl = NULL;
		}

		// filter
		switch ( mode )
		{
			case 0:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			break;

			case 1:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			break;

			case 2:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
			break;

			case 3:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
			break;
		}

		//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		glBindTexture( GL_TEXTURE_2D, 0 ); // unbind the texture for now
	}

	return id;
}

// LDET save
void LDEimage::save( string path )
{
	ofstream file;

	if ( path.substr( 0, 1 ) == "/" )
	file.open( path.substr( 1, path.size()-1 ).c_str(), ios::out | ios::binary );
	else
	file.open( path.c_str(), ios::out | ios::binary );

	if ( file.is_open() )
	{
		file.write( (char*)&size.x, sizeof(LDEuint) );
		file.write( (char*)&size.y, sizeof(LDEuint) );
		file.write( (char*)&bpp, sizeof(LDEuint) );

		//ilSetInteger(IL_FORMAT_MODE, (bpp == 3 ? IL_RGB : IL_RGBA) );

		/*uLongf zl = w*h*bpp;
		LDEubyte *data_compressed = new LDEubyte[zl];
		compress2( data_compressed, &zl, ilGetData(), w*h*bpp, 9 );
		file.write(reinterpret_cast<char*>(&data_compressed[0]), zl );*/

		file.write( reinterpret_cast<char*>(&data[0]), size.x*size.y*bpp*sizeof(LDEubyte) );

		file.close();
	}
	else
	{
		//cout<<"Error creating \'"+path+"\' file."<<std::endl;
	}
}
