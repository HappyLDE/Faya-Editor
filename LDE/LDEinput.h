/*********************************************************
 *
 * LDE
 *
 * \ Input
 *
 * *******************************************************/

#ifndef LDE_INPUT_H
#define LDE_INPUT_H

#include <string>

#include "LDEvec2i.h"
#include "LDEmouse_event.h"

struct LDEinput
{
    bool	esc,              // ESCAPE key
            f1, f2, f3, f4, f5, f6, f7, f8,
            f9, f10, f11, f12, f13, f14, f15, // F keys
            kp0, kp1, kp2, kp3, kp4, kp5, kp6, kp7, kp8, kp9,                   // right numbers
            u0, u1, u2, u3, u4, u5, u6, u7, u8, u9,         // up numbers
            insert, home, pageup, pagedown, end, del,                // OS keys
            up, down, left, right,                                            // keyboard arrows
            a, b, c, d, e, f, g, h, i, j, k, l, m, // letter keys
            n, o, p, q, r, s, t, u, v, w, x, y, z, // letter keys
            tab,             //
            enter,           // enter
            enter2,          // enter2
            space,            //
            plus, minus,   // plus & minux keys (right)
            rshift, lshift,// Shift keys on right & left
            ralt, lalt,    // Alt keys on right & left
            rctrl, lctrl,  // Ctrl keys on right & left
            lcmd, rcmd, // Control, Cmd or Windows button
            mb1,
            mb2,
            mb3, //
            backspace,        //
            divide, multiply, // divide key
            mode,             // ???
            point,            // point key, near enter2
            numlock,          //
            caps,             //
            key_down, //
            menu,
            printscr,
            decimal,
			capslock;         //

    std::string characters;
	
    LDEinput();
    ~LDEinput();
};

#endif // LDE_INPUT_H
