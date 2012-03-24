#include <os.h>

#ifndef NSPIREIO2_H
#define NSPIREIO2_H

struct nio_console
{
	char* data;
	char* color;
	int cursor_x;
	int cursor_y;
	int max_x;
	int max_y;
	int offset_x;
	int offset_y;
	char default_background_color;
	char default_foreground_color;
};
typedef struct nio_console nio_console;

/** Draws a pixel to the screen.
	@param x X coordinate
	@param y Y coordinate
	@param color Pixel color
*/
void setPixel(int x, int y, unsigned int color);

/** Draws a char to the screen using the charmap.
	@param x X coordinate
	@param y Y coordinate
	@param ch Char to draw
	@param bgColor Background color of the character
	@param textColor Color of the character
*/
void putChar(int x, int y, char ch, int bgColor, int textColor);

/** Draws a string to the screen using the charmap.
	@param x X coordinate
	@param y Y coordinate
	@param str String to draw
	@param bgColor Background color of the character
	@param textColor Color of the character
*/
void putStr(int x, int y, char* str, int bgColor, int textColor);

/** Draws a string to the screen
	@param offset_x x offset (pixel)
	@param offset_y y offset (pixel)
	@param x Column
	@param y Row
	@param str String
	@param bgColor Background color
	@param textColor Text color
*/
void nio_drawstr(int offset_x, int offset_y, int x, int y, char *str, char bgColor, char textColor);

/** Draws a char to the screen
	@param offset_x x offset (pixel)
	@param offset_y y offset (pixel)
	@param x Column
	@param y Row
	@param ch String
	@param bgColor Background color
	@param textColor Text color
*/
void nio_drawch(int offset_x, int offset_y, int x, int y, char ch, char bgColor, char textColor);

/** Reads a char from the keyboard
	@return ASCII char
*/
char nio_getch(void);

/** Initializes a console.
	@param c Console
	@param size_x Number of columns
	@param size_y Number of rows
	@param offset_x x offset (pixel)
	@param offset_y y offset (pixel)
	@param background_color Default background color
	@param foreground_color Default foreground color
*/
void nio_InitConsole(nio_console* c, int size_x, int size_y, int offset_x, int offset_y, char background_color, char foreground_color);

/** Draws a console to the screen.
	@param c Console
*/
void nio_DrawConsole(nio_console* c);

/** Draws a char from a console to the screen.
	@param c Console
	@param pos_x Column
	@param pos_y Row
*/
void nio_DrawChar(nio_console* c, int pos_x, int pos_y);

/** Saves a char in a console.
	@param c Console
	@param ch char to be stored
	@param pos_x Column
	@param pos_y Row
*/
void nio_SetChar(nio_console* c, char ch, int pos_x, int pos_y);

/** Prints a char in a console.
	@param c Console
	@param ch Char
	@param draw When this is true, the char will be drawn to the screen, false: just save it
*/
void nio_PrintChar(nio_console* c, char ch, BOOL draw);

/** Prints a string in a console.
	@param c Console
	@param str String
	@param draw When this is true, the char will be drawn to the screen, false: just save it
*/
void nio_PrintStr(nio_console* c, char* str, BOOL draw);

/** Sets the Foreground/Background color.
	@param c Console
	@param background_color Background color
	@param foreground_color Foreground color
*/
void nio_SetColor(nio_console* c, char background_color, char foreground_color);

/** Frees the allocated memory.
	@param c Console
*/
void nio_CleanUp(nio_console* c);

#endif