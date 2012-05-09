/*********************************************************
 *
 * LDE INPUT
 *
 * *******************************************************/

#include "LDEinput.h"

LDEinput::LDEinput()
{	
    esc = 0,              // ESCAPE key
		f1 = 0, f2 = 0, f3 = 0, f4 = 0, f5 = 0, f6 = 0, f7 = 0, f8 = 0,
		f9 = 0, f10 = 0, f11 = 0, f12 = 0, f13 = 0, f14 = 0, f15 = 0, // F keys
		kp0 = 0, kp1 = 0, kp2 = 0, kp3 = 0, kp4 = 0, kp5 = 0, kp6 = 0, kp7 = 0, kp8 = 0, kp9 = 0,                   // right numbers
		u0 = 0, u1 = 0, u2 = 0, u3 = 0, u4 = 0, u5 = 0, u6 = 0, u7 = 0, u8 = 0, u9 = 0,         // up numbers
		insert = 0, home = 0, pageup = 0, pagedown = 0, end = 0, del = 0,                // OS keys
		up = 0, down = 0, left = 0, right = 0,                                            // keyboard arrows
		a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0, i = 0, j = 0, k = 0, l = 0, m = 0, // letter keys
		n = 0, o = 0, p = 0, q = 0, r = 0, s = 0, t = 0, u = 0, v = 0, w = 0, x = 0, y = 0, z = 0, // letter keys
		tab = 0,             //
		enter = 0,           // enter
		enter2 = 0,          // enter2
		space = 0,            //
		plus = 0, minus = 0,   // plus & minux keys (right)
		rshift = 0, lshift = 0,// Shift keys on right & left
		ralt = 0, lalt = 0,    // Alt keys on right & left
		rctrl = 0, lctrl = 0,  // Ctrl keys on right & left
        lcmd = 0, rcmd = 0,
		mb1 = 0, mb2 = 0, mb3 = 0, // Mouse buttons, left = 1, roulette = 2, right = 3
		backspace = 0,        //
		divide = 0, multiply = 0, // divide key
		mode = 0,             // ???
		point = 0,            // point key, near enter2
		numlock = 0,          //
		caps = 0,             //
		key_down = 0, //
		menu = 0,
		printscr = 0,
		decimal = 0,
		capslock = 0;         //
}
LDEinput::~LDEinput()
{

}

