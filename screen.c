/**
 * @file screen.c
 * @author Julian Mackeben aka compu <compujucke@googlemail.com>
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
 * Screen functions
 */
#include <os.h>
#include "charmap.h"
#include "nspireio.h"
 
void nio_pixel_set(int x, int y, unsigned int color)
{
	unsigned char *scr = (unsigned char *) SCREEN_BASE_ADDRESS;
	if(x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		scr[y*SCREEN_WIDTH/2+x/2]=x&1? (scr[y*SCREEN_WIDTH/2+x/2]&0xF0)+color : (scr[y*SCREEN_WIDTH/2+x/2]&0x0F)+(color<< 4);
	}
}

void nio_pixel_putc(int x, int y, char ch, int bgColor, int textColor)
{
	int i, j, pixelOn;
	for(i = 0; i < NIO_CHAR_WIDTH; i++)
	{
		for(j = NIO_CHAR_HEIGHT; j > 0; j--)
		{
			pixelOn = MBCharSet8x6_definition[(unsigned char)ch][i] << j ;
			pixelOn = pixelOn & 0x80 ;
			if (pixelOn) 		nio_pixel_set(x+i,y+NIO_CHAR_HEIGHT-j,textColor);
			else if(!pixelOn) 	nio_pixel_set(x+i,y+NIO_CHAR_HEIGHT-j,bgColor);
		}
	}
}
void nio_pixel_puts(int x, int y, char* str, int bgColor, int textColor)
{
	int l = strlen(str);
	int i;
	int stop=0;
	for (i = 0; i < l && !stop; i++)
	{
		nio_pixel_putc(x, y, str[i], bgColor, textColor);
		x += NIO_CHAR_WIDTH;
		if (x >= SCREEN_WIDTH-NIO_CHAR_WIDTH)
		{
			stop=1;
		}
	}
}
