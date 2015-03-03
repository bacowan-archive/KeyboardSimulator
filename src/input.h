#ifndef _INPUTH_
#define _INPUTH_

// Includes
#include <ncurses.h>
#include "data.h"

// Definitions
#define ESC 27
#define LEFT 260
#define RIGHT 261
#define UP 259
#define DOWN 258

// Structures


// Prototypes
void set_curses();
void unset_curses();
void print_string(int y, int x, char* str);
void key_hit(int c, int max);

#endif
