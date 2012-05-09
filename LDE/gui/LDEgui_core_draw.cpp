/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Scene Gamera
\********************************************************************/

#include "LDEgui_core.h"

void LDEgui::draw( vec2i cursor, LDEfloat frametime )
{
    unused = 1;
    focus_window = 0;
    focus_menu = 0;
	
    if ( menu.button.size() )
    {
		if ( cursor.x > menu.pos.x &&
			 cursor.x < menu.pos.x + menu.size.x &&
			 cursor.y > menu.pos.y &&
			 cursor.y < menu.pos.y + menu.size.y )
        {
			menu.coi = 1;
            focus_menu = 1;
		}
		else
			menu.coi = 0;
    }
	
    for ( LDEuint i = 0; i < window.size(); ++i )
    {
		if ( !window[i]->closed )
		{
			window[i]->elements.input = input;
			window[i]->elements.mouse = mouse;
			window[i]->mouse = mouse;
			window[i]->app_size = app_size;
			
			window[i]->focus = 0;

			if ( focus_menu )
				window[i]->coi = 0;
			else
				window[i]->cursorOnIt( cursor );
			
			// Is this window on top of the others ?
			if ( i == window.size()-1 )
				window[i]->on_top = 1;
			else
				window[i]->on_top = 0;

			// mouse clicks
			for ( LDEuint m = 0; m < mouse.size(); ++m )
			{
				if ( mouse[m].left && mouse[m].down )
				{
					if ( window[i]->coi )
					{
						// Cursor's position on the  window
						window[i]->pos_temp.x = cursor.x - window[i]->pos.x;
						window[i]->pos_temp.y = cursor.y - window[i]->pos.y;
						
						window[i]->clicked_away = 0;
						
						//if ( !focus_menu )
						//	window[i]->focus = 1;
						
						window[i]->wait = 1;
						
						focus_window = 1;
					}
					else
						window[i]->clicked_away = 1;
				}
				
				if ( mouse[m].left && !mouse[m].down )
				{
					window[i]->wait = 0;
					window[i]->move = 0;
				}
			}

			// If the cursor is on the window
			if ( window[i]->coi )
			{
				unused = 0;

				window[i]->focus = 1;
				
				// cette boucle est trop abusive
				for ( LDEuint u = 0; u < i; ++u )
					window[u]->focus = 0;	// les autres bases n'ont plus le focus
			}
		}
    }

    /// ///////// DRAW ////////////////// //////////////////////////////////////////////////////
	
    // pannels tests
    for ( LDEuint i = 0; i < pannel.size(); ++i )
    {
		pannel[i]->elements.mouse = mouse;
		
        pannel[i]->focus = 0;

        pannel[i]->cursorOnIt( cursor );

		// mouse clicks
		for ( LDEuint m = 0; m < mouse.size(); ++m )
		{
			if ( mouse[m].left && mouse[m].down )
			{
				if ( !pannel[i]->coi )
					pannel[i]->clicked_away = 1;
				else
					pannel[i]->clicked_away = 0;
			}
			
			if ( mouse[m].left && !mouse[m].down )
			{
				pannel[i]->wait = 0;
			}
		}

        // If the cursor is on the pannel
        if ( pannel[i]->coi )
        {
            if ( !focus_window && !focus_menu )
                pannel[i]->focus = 1;

            pannel[i]->wait = 1;

            unused = 0;

            // cette boucle est trop abusive
            for ( LDEuint u = 0; u < i; ++u )
                pannel[u]->focus = 0;	// les autres bases n'ont plus le focus
        }
    }

    // Draw Pannels, zorder is creation order
    for ( LDEuint i = 0; i < pannel.size(); ++i )
    {
        pannel[i]->draw( cursor, frametime );
    }

    /// DRAW WINDOWS
    for ( LDEuint i = 0; i < window.size(); ++i )
    {
		if ( !window[i]->closed )
		{
			if ( window[i]->bringOnTop )
			{
				window[i]->bringOnTop = 0;
				
				LDEgui_window *window_temp = window[i];
				window.erase( window.begin() + i );
				window.push_back( window_temp );
			}
			
			if ( window[i]->on_top && !window[i]->clicked_away )
				glBindTexture(GL_TEXTURE_2D, window[i]->texture->id);
			else
			{
				glBindTexture(GL_TEXTURE_2D, window[i]->texture_inactive->id );
			}
			
			// mouse clicks
			for ( LDEuint m = 0; m < mouse.size(); ++m )
			{
				if ( mouse[m].left && mouse[m].down )
				{
					// If window is not on top and we clicked, bring it on top
					if ( window[i]->focus && !window[i]->clicked_away )
					{
						LDEgui_window *window_temp = window[i];
						window.erase( window.begin() + i );
						window.push_back( window_temp );
						
						if ( window[i]->wait )
							window[i]->move = 1;
					}
				}
				
				if ( mouse[m].left && !mouse[m].down )
				{
					window[i]->move = 0;
				}
			}

			if ( window[i]->move && window[i]->can_move && !window[i]->button_resize.pressed )
			{
				window[i]->pos.x = cursor.x - window[i]->pos_temp.x;
				window[i]->pos.y = cursor.y - window[i]->pos_temp.y;
			}
			
			window[i]->draw( cursor, frametime );
		}
    }
    
    if ( close_menu )
    {
        for ( LDEuint i = 0; i < menu.button.size(); ++i )
        {
            menu.button[i]->test_coi = focus_menu;
			menu.button[i]->mouse = mouse;
            menu.button[i]->draw( cursor, frametime );
        }
        
        menu.close();
        close_menu = 0;
    }
    
    if ( menu.button.size() )
    {
		menu.changed = 0;
		
		glBindTexture(GL_TEXTURE_2D, texture_pannel->id);
        LDEcustomrectp( texture_pannel->size, vec4i(menu.pos.x - 21, menu.pos.y - 25, menu.size.x + 42, menu.size.y + 50), vec4i(30,30,30,30) );
		
        if ( menu.selected > -1 )
            if ( menu.button[menu.selected]->transp < 0.6 )
                menu.button[menu.selected]->transp = 0.6;
        
        for ( LDEuint i = 0; i < menu.button.size(); ++i )
        {
            menu.button[i]->x = menu.pos.x + menu.button[i]->pos.x;
            menu.button[i]->y = menu.pos.y + menu.button[i]->pos.y;
            menu.button[i]->test_coi = focus_menu;
			menu.button[i]->mouse = mouse;
			
            menu.button[i]->draw( cursor, frametime );
			
			if ( menu.button[i]->click )
			{
				menu.selected = i;
                close_menu = 1;
				menu.changed = 1;
				break;
			}
        }
		
		// mouse clicks
		for ( LDEuint m = 0; m < mouse.size(); ++m )
		{
			if ( mouse[m].left && mouse[m].down && !menu.coi )
			{
				menu.close();
			}
		}
    }
}
