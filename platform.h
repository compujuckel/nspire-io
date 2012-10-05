/**
 * @file platform.h
 * @author Julian Mackeben aka compu <compujuckel@googlemail.com>
 * @version 3.0
 *
 * @section LICENSE
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301  USA
 *
 * @section DESCRIPTION
 *
 * Decide which header to use...
 */

// Includes for the different platforms here.

#ifndef PLATFORM_H
#define PLATFORM_H

#define NIO_CHAR_WIDTH 6
#define NIO_CHAR_HEIGHT 8

#ifdef BUILDLIB
	#ifdef _TINSPIRE
		#include "nspire.h"
	#endif
#else
	#ifdef _TINSPIRE
		#include <nspire.h>
	#endif
#endif

// These functions are the same on all platforms...

void nio_pixel_set(const int x, const int y, const unsigned int color);
void nio_vram_pixel_set(const int x, const int y, const unsigned int color);
void nio_vram_draw(void);
unsigned int nio_cursor_clock(void);
char nio_ascii_get(void);

#endif