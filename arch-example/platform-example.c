/**
 * @file platform-example.c
 * @author Julian Mackeben aka compu <compujuckel@googlemail.com>
 * @version 3.1
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
 * Example platform source.
 */

#include <nspireio/platform.h>
#include "charmap.h"

unsigned short getPaletteColor(unsigned int color)
{
	unsigned short palette[16] = {0x0000, 0xa800, 0x0540, 0xaaa0, 0x0015, 0xa815, 0x0555, 0xad55,
					0x5aab, 0xfaab, 0x5feb, 0xffeb, 0x5abf, 0xfabf, 0x5fff, 0xffff};
	int rbtable[6] = {0,6,12,18,24,31};
	int gtable[6] = {0,12,25,37,50,63};
        unsigned int c = color;
        unsigned int d;
        if(c < 16)
        {
                return palette[c];
        }
        else if(c < 232)
        {
                d = c-16;
                return (rbtable[d/36]<<11)+(gtable[(d/6)%6]<<5)+rbtable[d%6];
        }
        else if(c < 256)
        {
                d = c-232;
                return ((d+1)<<11)+((d*2+2)<<5)+(d+1);
        }
	return 0;
}

void nio_pixel_set(const int x, const int y, const unsigned int color)
{
	// Put a pixel to the screen directly
	// Remember to use getPaletteColor(color), otherwise our defines like NIO_COLOR_BLACK won't work
}

void nio_vram_pixel_set(const int x, const int y, const unsigned int color)
{
	// Put a pixel in VRAM
}

void nio_vram_draw(void)
{
	// Draw VRAM to screen
}

char nio_ascii_get(void)
{
	// Return an ascii char.
	// 0 = user abort (e.g. ESC)
	// 1 = No key pressed (use this for modifier keys like shift)
}
