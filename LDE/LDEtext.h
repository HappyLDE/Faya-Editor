/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * TEXT without the needing to load file
\********************************************************************/

#ifndef LDE_TEXT_H
#define LDE_TEXT_H

#include <OpenGL/gl.h>

#include <string>

using namespace std;

#include "LDEvariables.h"

// default FONT
const LDEubyte LDE_DEFAULT_FONT[] [12]= {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd8, 0xd8, 0x90, 0x48, 0x00},	//  "
										 {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	//" "
										 {0x00, 0x00, 0x00, 0x20, 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00},	//  !
										 {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x48, 0xd8, 0xd8, 0x00},	//  "
										 {0x00, 0x00, 0x00, 0x50, 0x50, 0xfc, 0x28, 0x28, 0xfc, 0x28, 0x28, 0x00},	//  #
										 {0x00, 0x00, 0x20, 0x70, 0xa8, 0x28, 0x30, 0x60, 0xa0, 0xa8, 0x70, 0x20},	//  $
										 {0x00, 0x00, 0x00, 0x88, 0x94, 0x54, 0x28, 0x50, 0xa8, 0xa4, 0x44, 0x00},	//  %
										 {0x00, 0x00, 0x00, 0x74, 0x88, 0x94, 0xa0, 0x40, 0x80, 0x90, 0x60, 0x00},	//  &
										 {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x10, 0x30, 0x30, 0x00},	//  '
										 {0x08, 0x10, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0x10, 0x08},	//  (
										 {0x40, 0x20, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x10, 0x10, 0x20, 0x40},	//  )
										 {0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xa8, 0x70, 0x70, 0xa8, 0x20, 0x00},	//  *
										 {0x00, 0x00, 0x00, 0x20, 0x20, 0xf8, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00},	//  +
										 {0x00, 0x20, 0x10, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	//  ,
										 {0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	//  -
										 {0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	//  .
										 {0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x20, 0x10, 0x10, 0x08, 0x08, 0x00},	//  /
										 {0x00, 0x00, 0x00, 0x70, 0x88, 0x88, 0xc8, 0xa8, 0x98, 0x88, 0x70, 0x00},	//  0
										 {0x00, 0x00, 0x00, 0xf8, 0x20, 0x20, 0x20, 0x20, 0xa0, 0x60, 0x20, 0x00},	//  1
										 {0x00, 0x00, 0x00, 0xf8, 0x80, 0x40, 0x20, 0x10, 0x08, 0x88, 0x70, 0x00},	//  2
										 {0x00, 0x00, 0x00, 0x70, 0x88, 0x08, 0x08, 0x30, 0x08, 0x88, 0x70, 0x00},	//  3
										 {0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0xf8, 0x90, 0x50, 0x30, 0x10, 0x00},	//  4
										 {0x00, 0x00, 0x00, 0xf0, 0x08, 0x08, 0x88, 0xf0, 0x80, 0x80, 0xf8, 0x00},	//  5
										 {0x00, 0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0xf0, 0x80, 0x40, 0x30, 0x00},	//  6
										 {0x00, 0x00, 0x00, 0x20, 0x20, 0x20, 0x10, 0x10, 0x08, 0x88, 0xf8, 0x00},	//  7
										 {0x00, 0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x70, 0x88, 0x88, 0x70, 0x00},	//  8
										 {0x00, 0x00, 0x00, 0x60, 0x10, 0x08, 0x78, 0x88, 0x88, 0x88, 0x70, 0x00},	//  9
										 {0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00},	//  :
										 {0x00, 0x20, 0x10, 0x30, 0x30, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00},	//  ;
										 {0x00, 0x00, 0x00, 0x0c, 0x30, 0xc0, 0x30, 0x0c, 0x00, 0x00, 0x00, 0x00},	//  <
										 {0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00},	//  =
										 {0x00, 0x00, 0x00, 0xc0, 0x30, 0x0c, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00},	//  >
										 {0x00, 0x00, 0x00, 0x20, 0x00, 0x20, 0x20, 0x10, 0x08, 0x88, 0x70, 0x00},	//  ?
										 {0x00, 0x00, 0x00, 0x38, 0x40, 0x98, 0xa8, 0xa8, 0x98, 0x48, 0x30, 0x00},	//  @
										 {0x00, 0x00, 0x00, 0x88, 0x88, 0xf8, 0x50, 0x50, 0x20, 0x20, 0x20, 0x00},	//  A
										 {0x00, 0x00, 0x00, 0xf0, 0x88, 0x88, 0x88, 0xf0, 0x88, 0x88, 0xf8, 0x00},	//  B
										 {0x00, 0x00, 0x00, 0x70, 0x88, 0x80, 0x80, 0x80, 0x80, 0x88, 0x70, 0x00},	//  C
										 {0x00, 0x00, 0x00, 0xe0, 0x90, 0x88, 0x88, 0x88, 0x88, 0x90, 0xe0, 0x00},	//  D
										 {0x00, 0x00, 0x00, 0xf8, 0x80, 0x80, 0x80, 0xf0, 0x80, 0x80, 0xf8, 0x00},	//  E
										 {0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0xf0, 0x80, 0x80, 0xf8, 0x00},	//  F
										 {0x00, 0x00, 0x00, 0x70, 0x88, 0x88, 0x98, 0x80, 0x80, 0x88, 0x70, 0x00},	//  G
										 {0x00, 0x00, 0x00, 0x88, 0x88, 0x88, 0x88, 0xf8, 0x88, 0x88, 0x88, 0x00},	//  H
										 {0x00, 0x00, 0x00, 0x70, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00},	//  I
										 {0x00, 0x00, 0x00, 0x70, 0x88, 0x88, 0x08, 0x08, 0x08, 0x08, 0x78, 0x00},	//  J
										 {0x00, 0x00, 0x00, 0x88, 0x90, 0xa0, 0xc0, 0xc0, 0xa0, 0x90, 0x88, 0x00},	//  K
										 {0x00, 0x00, 0x00, 0xf8, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00},	//  L
										 {0x00, 0x00, 0x00, 0x88, 0x88, 0x88, 0x88, 0xa8, 0xd8, 0xd8, 0x88, 0x00},	//  M
										 {0x00, 0x00, 0x00, 0x88, 0x98, 0x98, 0xa8, 0xa8, 0xc8, 0xc8, 0x88, 0x00},	//  N
										 {0x00, 0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00},	//  O
										 {0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0xf0, 0x88, 0x88, 0x88, 0xf0, 0x00},	//  P
										 {0x00, 0x0c, 0x10, 0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00},	//  Q
										 {0x00, 0x00, 0x00, 0x88, 0x90, 0xa0, 0xf0, 0x88, 0x88, 0x88, 0xf0, 0x00},	//  R
										 {0x00, 0x00, 0x00, 0x70, 0x88, 0x08, 0x08, 0x70, 0x80, 0x88, 0x70, 0x00},	//  S
										 {0x00, 0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xf8, 0x00},	//  T
										 {0x00, 0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x00},	//  U
										 {0x00, 0x00, 0x00, 0x20, 0x20, 0x50, 0x50, 0x88, 0x88, 0x88, 0x88, 0x00},	//  V
										 {0x00, 0x00, 0x00, 0x50, 0x50, 0x50, 0xa8, 0xa8, 0xa8, 0x88, 0x88, 0x00},	//  W
										 {0x00, 0x00, 0x00, 0x88, 0x88, 0x50, 0x20, 0x20, 0x50, 0x88, 0x88, 0x00},	//  X
										 {0x00, 0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x50, 0x50, 0x88, 0x88, 0x00},	//  Y
										 {0x00, 0x00, 0x00, 0xf8, 0x80, 0x40, 0x20, 0x20, 0x10, 0x08, 0xf8, 0x00},	//  Z
										 {0x38, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x38, 0x00},	//  [
										 {0x00, 0x00, 0x00, 0x08, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x00},	//  \               */
										 {0x70, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x70, 0x00},	//  ]
										 {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x50, 0x50, 0x20, 0x20, 0x00},	//  ^
										 {0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	//  _
										 {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x20, 0x00, 0x00},	//  `
										 {0x00, 0x00, 0x00, 0x68, 0x98, 0x88, 0x88, 0x88, 0x78, 0x00, 0x00, 0x00},	//  a
										 {0x00, 0x00, 0x00, 0xf0, 0x88, 0x88, 0x88, 0xc8, 0xb0, 0x80, 0x80, 0x00},	//  b
										 {0x00, 0x00, 0x00, 0x70, 0x88, 0x80, 0x80, 0x88, 0x70, 0x00, 0x00, 0x00},	//  c
										 {0x00, 0x00, 0x00, 0x68, 0x98, 0x88, 0x88, 0x88, 0x78, 0x08, 0x08, 0x00},	//  d
										 {0x00, 0x00, 0x00, 0x70, 0x88, 0x80, 0xf8, 0x88, 0x70, 0x00, 0x00, 0x00},	//  e
										 {0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0xf0, 0x40, 0x30, 0x00},	//  f
										 {0x00, 0x70, 0x08, 0x68, 0x98, 0x88, 0x88, 0x88, 0x78, 0x00, 0x00, 0x00},	//  g
										 {0x00, 0x00, 0x00, 0x88, 0x88, 0x88, 0x88, 0xc8, 0xb0, 0x80, 0x80, 0x00},	//  h
										 {0x00, 0x00, 0x00, 0x30, 0x20, 0x20, 0x20, 0x20, 0x60, 0x00, 0x20, 0x00},	//  i
										 {0x00, 0xe0, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x70, 0x00, 0x10, 0x00},	//  j
										 {0x00, 0x00, 0x00, 0x88, 0x90, 0xa0, 0xc0, 0xa0, 0x90, 0x80, 0x80, 0x00},	//  k
										 {0x00, 0x00, 0x00, 0x30, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00},	//  l
										 {0x00, 0x00, 0x00, 0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0xd0, 0x00, 0x00, 0x00},	//  m
										 {0x00, 0x00, 0x00, 0x88, 0x88, 0x88, 0x88, 0xc8, 0xb0, 0x00, 0x00, 0x00},	//  n
										 {0x00, 0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00, 0x00},	//  o
										 {0x00, 0x80, 0x80, 0xf0, 0x88, 0x88, 0x88, 0xc8, 0xb0, 0x00, 0x00, 0x00},	//  p
										 {0x00, 0x08, 0x08, 0x68, 0x98, 0x88, 0x88, 0x88, 0x78, 0x00, 0x00, 0x00},	//  q
										 {0x00, 0x00, 0x00, 0xe0, 0x40, 0x40, 0x40, 0x60, 0xd8, 0x00, 0x00, 0x00},	//  r
										 {0x00, 0x00, 0x00, 0x70, 0x88, 0x10, 0x60, 0x88, 0x70, 0x00, 0x00, 0x00},	//  s
										 {0x00, 0x00, 0x00, 0x30, 0x48, 0x40, 0x40, 0x40, 0xf0, 0x40, 0x40, 0x00},	//  t
										 {0x00, 0x00, 0x00, 0x68, 0x98, 0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00},	//  u
										 {0x00, 0x00, 0x00, 0x20, 0x20, 0x50, 0x50, 0x88, 0x88, 0x00, 0x00, 0x00},	//  v
										 {0x00, 0x00, 0x00, 0x50, 0x50, 0xa8, 0xa8, 0x88, 0x88, 0x00, 0x00, 0x00},	//  w
										 {0x00, 0x00, 0x00, 0x88, 0x50, 0x20, 0x20, 0x50, 0x88, 0x00, 0x00, 0x00},	//  x
										 {0x00, 0x80, 0x40, 0x20, 0x20, 0x50, 0x50, 0x88, 0x88, 0x00, 0x00, 0x00},	//  y
										 {0x00, 0x00, 0x00, 0xf8, 0x80, 0x40, 0x20, 0x10, 0xf8, 0x00, 0x00, 0x00},	//  z
										 {0x18, 0x20, 0x20, 0x20, 0x20, 0xc0, 0x20, 0x20, 0x20, 0x20, 0x18, 0x00},	//  {
										 {0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20},	//  |
										 {0xc0, 0x20, 0x20, 0x20, 0x20, 0x18, 0x20, 0x20, 0x20, 0x20, 0xc0, 0x00},	//  }
										 {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x98, 0x64, 0x00, 0x00, 0x00, 0x00}}; //  ~


void LDEtext( LDEuint x, LDEuint y, string characters );

#endif // LDE_TEXT_H
