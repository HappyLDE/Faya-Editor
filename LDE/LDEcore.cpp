/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Core
\********************************************************************/

#include "LDEcore.h"

LDE::LDE()
{
	working = 1;

    ft = 0.1f,
    last_ft = 0.1f;
    
    input_lcmd = 0;
    input_rcmd = 0;
}

LDE::~LDE()
{

}

void LDE::stop()
{
	working = 0;
}

LDEdouble LDE::getTicks()
{
	return 0;
}

LDEint LDE::init( LDEuint myWidth, LDEuint myHeight, wstring title )
{
	size.x = myWidth;
	size.y = myHeight;
	
	//out<<"Initializing Open Graphics Library\n";
	//cout<<"Initializing Open Graphics Library\n";
    glShadeModel(GL_SMOOTH);
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

    /// set up fog /////////////
    //GLfloat fogColor[4]= {0.4f, 0.7f, 0.9f, 1.0f};		// Fog Color

    //glFogi(GL_FOG_MODE, GL_LINEAR );		// Fog Mode
    //glFogfv(GL_FOG_COLOR, fogColor);			// Set Fog Color
    //glFogf(GL_FOG_DENSITY, 0.35f);				// How Dense Will The Fog Be
    //glHint(GL_FOG_HINT, GL_DONT_CARE);			// Fog Hint Value
    //glFogf(GL_FOG_START, 1.0f);				// Fog Start Depth
    //glFogf(GL_FOG_END, 1000.0f);				// Fog End Depth
    //glEnable(GL_FOG);					// Enables GL_FOG

    //glClearDepth(1.0f);
    //glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR);
	glEnable(GL_TEXTURE_2D);
    glDepthFunc(GL_LEQUAL);
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    /// OpenLG 0 light
	//glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHTING);

    //LDEfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    //LDEfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
    //LDEfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };

    //glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    //glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	//glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_NORMAL_ARRAY);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//


    #if defined(LDE_OBJ) || defined(LDE_LDEM)
        out<<"Initializing The OpenGL Extension Wrangler Library\n";
        cout<<"Initializing The OpenGL Extension Wrangler Library\n";
        //glewInit();
    #endif

    #if defined(LDE_IMG) || defined(LDE_OBJ)
        out<<"Initializing Developer's Image Library\n";
        cout<<"Initializing Developer's Image Library\n";
        //ilInit();
        //ilEnable(IL_ORIGIN_SET);
        //ilSetInteger(IL_FORMAT_MODE, IL_RGBA);
        //ilEnable(IL_FORMAT_SET);
    #endif

    last_ft = getTicks();
    // ft = getTicks() - last_ft;

    return true;
}

LDEfloat LDE::fps()
{
    return 1.f / ft; // ft = frame time
}

bool LDE::run( void (*scene3D)() )
{
	while( working )
	{
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		// User specified scene
		scene3D();
		
        ft = getTicks() - last_ft;
        last_ft = getTicks();
	}

	return true;
}
