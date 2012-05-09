/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * FONT
\********************************************************************/

#include "LDEldef.h"

wchar_t LDEfont_default_charset[] =
{
     31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,
     44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,
     57,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,
     70,  71,  72,  73,  74,  75,  76,  77,  78,  79,  80,  81,  82,
     83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,
     96,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108,
    109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121,
    122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134,
    135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147,
    148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160,
    161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173,
    174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
    187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199,
    200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212,
    213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225,
    226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238,
    239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251,
    252, 253, 254, 255, 0
};

LDEfont_character::LDEfont_character()
{
    top = 0;
    left = 0;
    advance = 0;
}

LDEfont_character::~LDEfont_character()
{

}

/// /////////////

LDEldef::LDEldef()
{
    pos.reset();
	
	loaded = 0;
}

LDEldef::~LDEldef()
{

}

void LDEldef::setPos( LDEint x, LDEint y )
{
    pos.x = x;
    pos.y = y;
}

void LDEldef::draw()
{
    glListBase( base );
	glBindTexture(GL_TEXTURE_2D, ldet.id);

	glPushMatrix();
	glTranslatef( pos.x, pos.y + char_size, 0 );

	glCallLists( name.size(), GL_UNSIGNED_BYTE, name.c_str() );

	glPopMatrix();
}

void LDEldef::setText( string text )
{
	if ( loaded )
	{
		name = text;

		size.reset();

		for( LDEuint i = 0; i < name.size(); ++i )
		{
			LDEuint pointer = i;//name[i] - 31; // à corriger xD

			size.x += (LDEint)character[pointer].advance;

			//step_back.x += (character[pointer].size.x / 2) + (character[pointer].advance/2);

			//cout<<character[pointer].advance<<std::endl;

			if ( size.y < character[pointer].size.y )
				 size.y = character[pointer].size.y;
		}
	}
}

void LDEldef::load( string path )
{
    ifstream file;

	file.open( path.c_str(), ios::in | ios::binary );

    if ( file.is_open() )
    {
        file.read( (char*)&ldet.w, sizeof(LDEuint) );

        ldet.create( ldet.w, ldet.w, 2 );

        file.read( reinterpret_cast<char*>(&ldet.data[0]), 2*ldet.w*ldet.w );
        ldet.opengl(0);

        file.read( (char*)&char_size, sizeof(LDEuint) );

        LDEuint numCharacters = 0;
        file.read( (char*)&numCharacters, sizeof(LDEuint) );

        // Let's create OpenGL Display List for later use
        base = glGenLists( numCharacters );

        // Let's just use our default charset dudes
        charset = LDEfont_default_charset;

        glPushMatrix();

        // Loop for every char in the charset
        for ( LDEuint i = 0; i < numCharacters; ++i )
        {
            LDEfont_character character_temp;

            file.read( (char*)&character_temp.left, sizeof(LDEint) );
            file.read( (char*)&character_temp.top, sizeof(LDEint) );

            file.read( (char*)&character_temp.size.x, sizeof(LDEint) );
            file.read( (char*)&character_temp.size.y, sizeof(LDEint) );

            file.read( (char*)&character_temp.uv.x, sizeof(LDEfloat) );
            file.read( (char*)&character_temp.uv.y, sizeof(LDEfloat) );
            file.read( (char*)&character_temp.uv.z, sizeof(LDEfloat) );
            file.read( (char*)&character_temp.uv.w, sizeof(LDEfloat) );

            file.read( (char*)&character_temp.advance, sizeof(LDEfloat) );

            character.push_back( character_temp );

            // Get the current character to generate
            current_char = charset[i];

            glNewList( base + current_char, GL_COMPILE );

            glPushMatrix();
            glTranslatef( character_temp.left + correction.x, -character_temp.top + correction.y, 0.f );

                glBegin(GL_QUADS);
                    glTexCoord2f( character_temp.uv.x, character_temp.uv.w );		glVertex2i(                     0, 0 );
                    glTexCoord2f( character_temp.uv.z, character_temp.uv.w ); 		glVertex2i( character_temp.size.x, 0 );
                    glTexCoord2f( character_temp.uv.z, character_temp.uv.y ); 		glVertex2i( character_temp.size.x, character_temp.size.y );
                    glTexCoord2f( character_temp.uv.x, character_temp.uv.y ); 		glVertex2i(    		            0, character_temp.size.y );
                glEnd();
            glPopMatrix();

            glTranslatef( character_temp.advance ,0.f, 0.f);

            glEndList();
        }

        glPopMatrix();

        file.close();
		loaded = 1;
    }
	else
	{
		loaded = 0;
		cout << " ! Error loading LDEldef font \""<<path<<"\"\n";
	}

}
