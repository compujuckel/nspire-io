/**
 * @file console.h
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
 * This file defines all Nspire I/O functions.
 */

#ifndef CONSOLE_H
#define CONSOLE_H

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
	@param buflen The size that should be used for the internal buffer
	@param ... Additional arguments
*/
void c_swrite(char *format, int buflen, ...);
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
/** @internal */
char shiftKey(char normalc, char shiftc);
/** @internal */
char shiftOrCtrlKey(char normalc, char shiftc, char ctrlc);
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

#endif
