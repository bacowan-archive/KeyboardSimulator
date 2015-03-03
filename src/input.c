#include "input.h"

static int cursorLoc = 0;

/*
 * Setup functionality for ncurses.
 */
void set_curses()
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);
}

/*
 * Tear down ncurses
 */
void unset_curses()
{
	keypad(stdscr, false);
	nodelay(stdscr, false);
	nocbreak();
	echo();
	endwin();
}

/*
 * Print a string to the console at the given coordinates.
 * @param y y coordinate to output text to
 * @param x x coordinate to output text to
 * @param str the string to output
 */
void print_string(int y, int x, char* str)
{
	int i = 0;
	int c = str[i];
	
	while(c != '\0')
	{
		move(y,x);
		addch(c);
		i++;
		x++;
		c = str[i];
	}
}

/*
 * Handles what to do when a key is hit: move the cursor, or increment
 * frequency array entry.
 * @param c the key that was hit
 * @param max the maximum distance to move the cursor (the size of the frequency array)
 */
void key_hit(int c, int max)
{
	print_string(11, 5*cursorLoc, "  ");
	if(c==UP && cursorLoc > 0)
		cursorLoc--;
	if(c==DOWN && cursorLoc < max-1)
		cursorLoc++;
	if(c==RIGHT)
		increaseFrequency( (double)0.1, cursorLoc );
	if(c==LEFT)
		increaseFrequency( (double)-0.1, cursorLoc );
		
	char cStr[5] = "";
	sprintf(cStr, "%d", c);
	print_string(20, 20, cStr);
	print_string(cursorLoc+9, 0, " ");
	print_string(cursorLoc+10, 0, ">");
	print_string(cursorLoc+11, 0, " ");
}
