/**
 * @file screen.c
 * @author Julian Mackeben aka compu <compujucke@googlemail.com>
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
 * Screen functions
 */
#include <os.h>
#include "charmap.h"
#include "nspireio2.h"
 
void setPixel(int x, int y, unsigned int color)
{
	unsigned char *scr = (unsigned char *) SCREEN_BASE_ADDRESS;
	if(x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		scr[y*SCREEN_WIDTH/2+x/2]=x&1? (scr[y*SCREEN_WIDTH/2+x/2]&0xF0)+color : (scr[y*SCREEN_WIDTH/2+x/2]&0x0F)+(color<< 4);
	}
}

void putChar(int x, int y, char ch, int bgColor, int textColor)
{
	int i, j, pixelOn;
	for(i = 0; i < CHAR_WIDTH; i++)
	{
		for(j = CHAR_HEIGHT; j > 0; j--)
		{
			pixelOn = MBCharSet8x6_definition[(unsigned char)ch][i] << j ;
			pixelOn = pixelOn & 0x80 ;
			if (pixelOn) 		setPixel(x+i,y+CHAR_HEIGHT-j,textColor);
			else if(!pixelOn) 	setPixel(x+i,y+CHAR_HEIGHT-j,bgColor);
		}
	}
}
void putStr(int x, int y, char* str, int bgColor, int textColor)
{
	int l = strlen(str);
	int i;
	int stop=0;
	for (i = 0; i < l && !stop; i++)
	{
		putChar(x, y, str[i], bgColor, textColor);
		x += CHAR_WIDTH;
		if (x >= SCREEN_WIDTH-CHAR_WIDTH)
		{
			stop=1;
		}
	}
}
