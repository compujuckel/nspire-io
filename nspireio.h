/**
 * @file nspireio.h
 * @author  Julian Mackeben aka compu <compujuckel@googlemail.com>
 * @version 0.1
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
 * Public header file for use in your programs when linked with -lnspireio.
 */
#include <os.h>

#ifndef NSPIREIO_H
#define NSPIREIO_H

/* console.h */

/** ONLY FOR USE WITH RSHELL: Call this function at the beginning of your program / replacement of c_init */
void rshell_load(void);

/** ONLY FOR USE WITH RSHELL: Call this function at the end of your program */
void rshell_save(void);

/** Needs to be called once before the I/O functions can be used
	@param bgColor		Console background color
	@param textColor	Console text color
*/
void c_init(char bgColor, char textColor);

/** Prints the console buffer to the screen. */
void c_draw(void);

/** Clears the console buffer. */
void c_clear(void);

/**	Writes a char to the console.
	@param ch The character to write
*/
void c_writec(char ch);

/**	Writes a string to the console.
	@param str The string to write
*/
void c_write(char *str);

/**	Writes a formatted string to the console.
	@param format The string to write. It can contain format tags.
	@param ... Additional arguments
*/
void c_swrite(char *format, ...);

/**	Reads a character from the keypad and does NOT write it to the console.
	@return The char that has been read. If it is 0, the input has been aborted.
*/
char cn_readc(void);

/**	Reads a character from the keypad and writes it to the console.
	@return The char that has been read. If it is 0, the input has been aborted.
*/
char c_readc(void);

/** Reads a string from the keypad and writes it to the console.
	@param str String where the read string will be saved in
	@return 1 on success, 0 on failure (user abort)
*/
int  c_read(char* str);

/** Draws a string to the screen without using the console buffer.
	@param x Column (x*6)
	@param y Row (y*8)
	@param str String to write
	@param bgColor background color of the string
	@param textColor text color
*/
void locate(int x, int y, char *str, char bgColor, char textColor);

/** Draws a char to the screen without using the console buffer.
	@param x Column (x*6)
	@param y Row (y*8)
	@param ch character to write
	@param bgColor background color of the string
	@param textColor text color
*/
void locatec(int x, int y, char ch, char bgColor, char textColor);

/* screen.h */

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

/* registry.h */

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

#endif