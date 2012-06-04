/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * LDE texture
\********************************************************************/

#include "LDEldet.h"

using namespace std;

LDEldet::LDEldet()
{

}

LDEldet::LDEldet( string name, LDEuint filter )
{
    load( name );
    opengl( filter );
}

// destructor
LDEldet::~LDEldet()
{
    //erase();
}

// create an empty place for new texture
bool LDEldet::create( LDEuint width, LDEuint height, LDEuint bpp_ )
{
    //set the member variables
    size.x = w = width;
    size.y = h = height;
    bpp = bpp_;

    //allocate memory
    data = new LDEubyte[ w*h*bpp ];

    loaded = true;

    if( !data )
    {
        //cout<<"Out of memory for image memory allocation.";
        loaded = false;
    }

    //set the loaded flag
    return loaded;
}

void LDEldet::readScenePixels( LDEint x, LDEint y, LDEint w, LDEint h )
{
    glReadPixels( x, y - h, w, h, ( bpp == 3 ? GL_RGB : GL_RGBA ), GL_UNSIGNED_BYTE, data );
}

void LDEldet::resize( LDEuint width, LDEuint height )
{
/*
    LDEubyte *old_data = data;

    delete[] data;

		data = new LDEubyte[w*h*bpp];

		// Copy the old pixel buffer into the new one
		for (unsigned int i = 0; i < std::min(width, w); ++i )
		for (unsigned int j = 0; j < std::min(height, h); ++j )
		data[i + j * width] = old_data[i + j * w];

		size.x = w = width;
		size.y = h = height;
*/
}

bool LDEldet::load( string path )
{
    ifstream file;

	file.open( path.c_str(), ios::in | ios::binary );

	//cout << " >>>>> "<<path<<" <<<<<\n";
	
		if ( file.is_open() )
		{
			file.read( (char*)&w, sizeof(LDEuint) );
            file.read( (char*)&h, sizeof(LDEuint) );
            file.read( (char*)&bpp, sizeof(LDEuint) );

			size.x = w;
			size.y = h;

            data = new LDEubyte[ bpp*w*h ];

            /*uLongf zl = bpp*w*h;
            LDEubyte *data_compressed = new LDEubyte[zl];

            file.read( reinterpret_cast<char*>(&data_compressed[0]), zl );

            int test = uncompress( data, &zl, data_compressed, zl );*/

			file.read( reinterpret_cast<char*>(&data[0]), bpp*w*h );

			//if ( test ) LDEcout<<zError(test)<<" "<<test;
            loaded = 1;

			file.close();
		}
		else
		{
			loaded = 0;
			cout<<" ! Error loading ldet \""<<path<<"\" file.\n";
		}

		return loaded;
}

// get color pixel at point
void LDEldet::getPixel( LDEuint x, LDEuint y, unsigned char* red, unsigned char* green, unsigned char* blue )
{
    if ( (x < w) && (y < h) )
	    {
	        *red   = data[ ((y*h)+x)*bpp   ];
	        *green = data[ ((y*h)+x)*bpp+1 ];
	        *blue  = data[ ((y*h)+x)*bpp+2 ];
	    }
}

// set color pixel at point
void LDEldet::setPixel( LDEuint x, LDEuint y, unsigned char red, unsigned char green, unsigned char blue )
{
    if ( (x < w) && (y < h) )
	    {
	        data[ ((y*h)+x)*bpp   ] = red;
	        data[ ((y*h)+x)*bpp+1 ] = green;
	        data[ ((y*h)+x)*bpp+2 ] = blue;
	    }
}

// set color pixel & alpha at point
void LDEldet::setPixel( LDEuint x, LDEuint y, unsigned char light, unsigned int alpha )
{
    if ( (x < w) && (y < h) )
	    {
	        data[ ((y*h)+x)*bpp   ] = light;
	        data[ ((y*h)+x)*bpp+1 ] = alpha;
	    }
}

// create the OpenGL texture and return it's ID
LDEuint LDEldet::opengl( LDEuint mode )
{
    if ( loaded )
    {
	        glGenTextures(1, &id);
	        glBindTexture(GL_TEXTURE_2D,id);

			if ( bpp == 2 )
			{
			    gluBuild2DMipmaps(GL_TEXTURE_2D,
			                      bpp,    // bpp
			                      w,      // largeur
			                      h,      // hauteur
			                      GL_LUMINANCE_ALPHA, // type
			                      GL_UNSIGNED_BYTE, //
			                      data);
			}
			else
			{
			    gluBuild2DMipmaps(GL_TEXTURE_2D,
			                      bpp,    // bpp
			                      w,      // largeur
			                      h,      // hauteur
			                      ( bpp == 3 ? GL_RGB : GL_RGBA ),// type
			                      GL_UNSIGNED_BYTE, //
			                      data);
			}

	        // filter
	        switch ( mode )
	        {
	            case LDET_NO_FILTER:
	            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	            break;

	            case LDET_LINEAR:
	            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	            break;

	            case LDET_BILINEAR:
	            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	            break;

	            case LDET_TRILINEAR:
	            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	            break;
	        }
	        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	        glBindTexture( GL_TEXTURE_2D, 0 );
    }



		return this->id;
}

// get height at point
LDEubyte LDEldet::getHeight( LDEuint x, LDEint z, LDEint lod )
{
    //x *= lod;
    //z *= lod;
    return data[ ((x + ( z * w ) ) * bpp) ];
}

// free stuff
void LDEldet::erase()
{
    if ( loaded )
	{
		h   = 0;    // height
		w   = 0;    // width
		bpp = 0;    // bits per pixel
		this->id  = 0;    // id
		loaded = 0; //
		size.reset();
		
		if ( data != NULL )
		{
			delete []data; // the image data
			data = NULL;
		}
	}
}
