/**
 * @file screen.h
 * @author  Julian Mackeben aka compu <compujucke@googlemail.com>
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
 * This file defines all screen functions.
 */
#ifndef SCREEN_H
#define SCREEN_H

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

#endif /* SCREEN_H */
