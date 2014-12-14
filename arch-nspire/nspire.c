/**
 * @file nspire.c
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
 * Functions for Nspire platform
 */

#include "../include/nspireio/platform.h"
#include "../include/nspireio/nspireio.h"
#include "../common/util.h"

void* scrbuf = NULL;

void nio_scrbuf_flip()
{
	memcpy(SCREEN_BASE_ADDRESS,scrbuf,SCREEN_BYTES_SIZE);
}

void nio_scrbuf_init()
{
	if(scrbuf == NULL)
	{
		scrbuf = malloc(SCREEN_BYTES_SIZE);
		if(scrbuf == NULL)
			exit_with_error(__FUNCTION__,"malloc failed");
		memcpy(scrbuf,SCREEN_BASE_ADDRESS,SCREEN_BYTES_SIZE);
	}
}

void nio_scrbuf_clear()
{
	memset(scrbuf,0xFF,SCREEN_BYTES_SIZE);
}

void nio_scrbuf_free()
{
	free(scrbuf);
	scrbuf = NULL;
}

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

// by totorigolo
void nio_pixel_set(unsigned int x, unsigned int y, unsigned int c)
{
	if (x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
		return;
	
	c = getPaletteColor(c);

	if(lcd_isincolor())
	{
		unsigned short* ptr = SCREEN_BASE_ADDRESS + sizeof(uint16_t) * (x + SCREEN_WIDTH * y);
		*ptr = c;
	}
	else
	{
		c = getBW(c);
		unsigned char* p = (unsigned char*)(SCREEN_BASE_ADDRESS + ((x >> 1) + (y << 7) + (y << 5)));
		*p = (x & 1) ? ((*p & 0xF0) | c) : ((*p & 0x0F) | (c << 4));
	}
}

void nio_vram_pixel_set(const unsigned int x, const unsigned int y, const unsigned int color)
{
	nio_pixel_set(x,y,color);
}

void nio_vram_fill(unsigned int color)
{
	color = getPaletteColor(color);
	if(!lcd_isincolor())
	{
		color = getBW(color);
		memset(SCREEN_BASE_ADDRESS, color | (color << 4), SCREEN_BYTES_SIZE);
	}
	else
	{
		color = color | (color << 16);
		unsigned int *start = SCREEN_BASE_ADDRESS, *end = start + (SCREEN_BYTES_SIZE / sizeof(*start));
		while(start < end)
			*start++ = color;
	}
}

void nio_vram_draw(void)
{}

unsigned int nio_cursor_clock(void) {
    return *(volatile unsigned*)0x90090000;
}

#define SHIFTCTRL(x, y, z) (ctrl ? (z) : shift ? (y) : (x))
#define SHIFT(x, y) SHIFTCTRL(x, y, 0)
#define NORMAL(x) SHIFT(x, 0)

char nio_ascii_get(int* adaptive_cursor_state)
{
	BOOL ctrl = isKeyPressed(KEY_NSPIRE_CTRL);
	BOOL shift = isKeyPressed(KEY_NSPIRE_SHIFT);

	*adaptive_cursor_state = SHIFTCTRL(0, 1, 4);
	
	if(isKeyPressed(KEY_NSPIRE_ESC)) return NIO_KEY_ESC;
	
	// Characters
	if(isKeyPressed(KEY_NSPIRE_A)) return SHIFT('a','A');
	if(isKeyPressed(KEY_NSPIRE_B)) return SHIFT('b','B');
	if(isKeyPressed(KEY_NSPIRE_C)) return SHIFT('c','C');
	if(isKeyPressed(KEY_NSPIRE_D)) return SHIFT('d','D');
	if(isKeyPressed(KEY_NSPIRE_E)) return SHIFT('e','E');
	if(isKeyPressed(KEY_NSPIRE_F)) return SHIFT('f','F');
	if(isKeyPressed(KEY_NSPIRE_G)) return SHIFT('g','G');
	if(isKeyPressed(KEY_NSPIRE_H)) return SHIFT('h','H');
	if(isKeyPressed(KEY_NSPIRE_I)) return SHIFT('i','I');
	if(isKeyPressed(KEY_NSPIRE_J)) return SHIFT('j','J');
	if(isKeyPressed(KEY_NSPIRE_K)) return SHIFT('k','K');
	if(isKeyPressed(KEY_NSPIRE_L)) return SHIFT('l','L');
	if(isKeyPressed(KEY_NSPIRE_M)) return SHIFT('m','M');
	if(isKeyPressed(KEY_NSPIRE_N)) return SHIFT('n','N');
	if(isKeyPressed(KEY_NSPIRE_O)) return SHIFT('o','O');
	if(isKeyPressed(KEY_NSPIRE_P)) return SHIFT('p','P');
	if(isKeyPressed(KEY_NSPIRE_Q)) return SHIFT('q','Q');
	if(isKeyPressed(KEY_NSPIRE_R)) return SHIFT('r','R');
	if(isKeyPressed(KEY_NSPIRE_S)) return SHIFT('s','S');
	if(isKeyPressed(KEY_NSPIRE_T)) return SHIFT('t','T');
	if(isKeyPressed(KEY_NSPIRE_U)) return SHIFT('u','U');
	if(isKeyPressed(KEY_NSPIRE_V)) return SHIFT('v','V');
	if(isKeyPressed(KEY_NSPIRE_W)) return SHIFT('w','W');
	if(isKeyPressed(KEY_NSPIRE_X)) return SHIFT('x','X');
	if(isKeyPressed(KEY_NSPIRE_Y)) return SHIFT('y','Y');
	if(isKeyPressed(KEY_NSPIRE_Z)) return SHIFT('z','Z');
	
	// Numbers
	if(isKeyPressed(KEY_NSPIRE_0)) return NORMAL('0');
	if(isKeyPressed(KEY_NSPIRE_1)) return NORMAL('1');
	if(isKeyPressed(KEY_NSPIRE_2)) return NORMAL('2');
	if(isKeyPressed(KEY_NSPIRE_3)) return NORMAL('3');
	if(isKeyPressed(KEY_NSPIRE_4)) return NORMAL('4');
	if(isKeyPressed(KEY_NSPIRE_5)) return NORMAL('5');
	if(isKeyPressed(KEY_NSPIRE_6)) return NORMAL('6');
	if(isKeyPressed(KEY_NSPIRE_7)) return NORMAL('7');
	if(isKeyPressed(KEY_NSPIRE_8)) return NORMAL('8');
	if(isKeyPressed(KEY_NSPIRE_9)) return NORMAL('9');
	
	// Symbols
	if(isKeyPressed(KEY_NSPIRE_COMMA))		return SHIFT(',',';');
	if(isKeyPressed(KEY_NSPIRE_PERIOD)) 	return SHIFT('.',':');
	if(isKeyPressed(KEY_NSPIRE_COLON))		return NORMAL(':');
	if(isKeyPressed(KEY_NSPIRE_LP))			return SHIFTCTRL('(','[',']');
	if(isKeyPressed(KEY_NSPIRE_RP))			return SHIFTCTRL(')','{','}');
	if(isKeyPressed(KEY_NSPIRE_SPACE))		return SHIFT(' ','_');
	if(isKeyPressed(KEY_NSPIRE_DIVIDE))		return SHIFT('/','\\');
	if(isKeyPressed(KEY_NSPIRE_MULTIPLY))	return SHIFT('*','\"');
	if(isKeyPressed(KEY_NSPIRE_MINUS))		return SHIFTCTRL('-','<', '_');
	if(isKeyPressed(KEY_NSPIRE_NEGATIVE))	return SHIFT('-','_');
	if(isKeyPressed(KEY_NSPIRE_PLUS))		return SHIFT('+', '>');
	if(isKeyPressed(KEY_NSPIRE_EQU))		return SHIFT('=', '|');
	if(isKeyPressed(KEY_NSPIRE_LTHAN))		return NORMAL('<');
	if(isKeyPressed(KEY_NSPIRE_GTHAN))		return NORMAL('>');
	if(isKeyPressed(KEY_NSPIRE_QUOTE))		return NORMAL('\"');
	if(isKeyPressed(KEY_NSPIRE_APOSTROPHE))	return NORMAL('\'');
	if(isKeyPressed(KEY_NSPIRE_QUES))		return SHIFT('?','!');
	if(isKeyPressed(KEY_NSPIRE_QUESEXCL))	return SHIFT('?','!');
	if(isKeyPressed(KEY_NSPIRE_BAR))		return NORMAL('|');
	if(isKeyPressed(KEY_NSPIRE_EXP))		return NORMAL('^');
	if(isKeyPressed(KEY_NSPIRE_EE))		return SHIFTCTRL('&','%', '@');
	if(isKeyPressed(KEY_NSPIRE_ENTER))		return SHIFT('\n','~');
	
	// Special chars
	if(isKeyPressed(KEY_NSPIRE_DEL))		return '\b';
	if(isKeyPressed(KEY_NSPIRE_RET))		return '\n';
	if(isKeyPressed(KEY_NSPIRE_TAB))		return '\t';
	if(isKeyPressed(KEY_NSPIRE_UP))			return NIO_KEY_UP;
	if(isKeyPressed(KEY_NSPIRE_DOWN))		return NIO_KEY_DOWN;
	
	return 0;
}
