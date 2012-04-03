/**
 * @file nspireio2.h
 * @author  Julian Mackeben aka compu <compujuckel@googlemail.com>
 * @version 2.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * Nspire I/O 2.0 header file
 */
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
	BOOL drawing_enabled;
};
typedef struct nio_console nio_console;

/** Loads a console to flash storage.
	@param path File path
	@param c Console
*/
void nio_load(char* path, nio_console* c);

/** Saves a console to flash storage.
	@param path File path
	@param c Console
*/
void nio_save(char* path, nio_console* c);

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

/** Scrolls the console one line down.
	@param c Console
*/
void nio_ScrollDown(nio_console* c);

/** Clears a console.
	@param c Console
*/
void nio_Clear(nio_console* c);

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
*/
void nio_PrintChar(nio_console* c, char ch);

/** Enables immediate drawing when a character is written to the console.
	@param c Console
	@param drawing_enabled When this is true, a char will be immediately drawn to the screen, false: just save it
*/
void nio_EnableDrawing(nio_console* c, BOOL drawing_enabled);

/** Prints a string in a console.
	@param c Console
	@param str String
*/
void nio_PrintStr(nio_console* c, char* str);

/** Prints a formatted string to a console.
	@param c Console
	@param format Format string
	@param ... Additional arguments
*/
void nio_printf(nio_console* c, char *format, ...);

/** Reads a char and prints it to the console.
	@param c Console
	@return ASCII char
*/
char nio_GetChar(nio_console* c);

/** Reads a string and prints it to the console.
	@param c Console
	@param str String destination
*/
int nio_GetStr(nio_console* c, char* str);

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

/** Stores binary data in a file.
	@param dataptr Pointer to the data to be stored
	@param size Length in bytes
	@param regpath Path to file
	@return 0 on success, -1 on failure
*/
int reg_store(void* dataptr, size_t size, char* regpath);

/** Reads binary data from a file.
	@param regpath Path to file
	@return Pointer to the data, NULL on failure
*/
void* reg_get(char* regpath);

/** Checks if there is data available at the serial port.
	@return TRUE if new data is available.
*/
BOOL uart_ready(void);

/** Gets a char from RS232.
	@return Char
*/
char uart_getc(void);

/** Gets a line (ended with \n) from RS232.
	@return Destination
*/
void uart_getline(char* dest);

/** Puts a char to RS232.
	@param c Char
*/
void uart_putc(char c);

/** Puts a string to RS232.
	@param str String
*/
void uart_puts(const char *str);

/** Puts a formatted string to RS232.
	@param format Format string
	@param ... Additional arguments
*/
void uart_printf(char *format, ...);


#endif