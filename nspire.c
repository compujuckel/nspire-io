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

#include "nspireio-platform.h"

void* scrbuf = NULL;
void* scrbuf_original = NULL;

void nio_scrbuf_flip()
{
	/*void* temp = SCREEN_BASE_ADDRESS;
	*(volatile unsigned**)0xC0000010 = scrbuf;
	scrbuf = temp;*/
	memcpy(SCREEN_BASE_ADDRESS,scrbuf,SCREEN_BYTES_SIZE);
}

void nio_scrbuf_init()
{
	//scrbuf_original = SCREEN_BASE_ADDRESS;
	scrbuf = malloc(SCREEN_BYTES_SIZE);
	memset(scrbuf,0xFF,SCREEN_BYTES_SIZE);
}

void nio_scrbuf_clear()
{
	memset(scrbuf,0xFF,SCREEN_BYTES_SIZE);
}

void nio_scrbuf_free()
{
	/*if(scrbuf == scrbuf_original)
		nio_scrbuf_flip();
	*(volatile unsigned**)0xC0000010 = scrbuf_original;*/
	free(scrbuf);
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
void nio_pixel_set(int x, int y, unsigned int color)
{
    unsigned short c = getPaletteColor(color);
	
	void* screen = scrbuf ? scrbuf : SCREEN_BASE_ADDRESS;
	
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
        return;

    // 4 bpp
    if (!has_colors || !lcd_isincolor())
    {
        unsigned char* p = (unsigned char*)(screen + ((x >> 1) + (y << 7) + (y << 5)));
        *p = (x & 1) ? ((*p & 0xF0) | getBW(c)) : ((*p & 0x0F) | (getBW(c) << 4));
    }
    // 16 bpp
    else
    {
        unsigned char* ptr = screen + sizeof(uint16_t) * (x + SCREEN_WIDTH * y);
        *(unsigned short*)ptr = c;
    }
}

// Disable VRAM support at the moment. There are issues with consoles that are not fullscreen and VRAM has not really any pros.
#ifdef NIO_ENABLE_VRAM

void* VRAM = NULL;

void nio_vram_pixel_set(const int x, const int y, const unsigned int color)
{
	if(VRAM == NULL)
	{
		VRAM = malloc(SCREEN_BYTES_SIZE);
		memcpy(VRAM,SCREEN_BASE_ADDRESS,SCREEN_BYTES_SIZE);
	}
	
	unsigned short c = getPaletteColor(color);
	
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
        return;

    // 4 bpp
    if (!has_colors || !lcd_isincolor())
    {
        unsigned char* p = (unsigned char*)(VRAM + ((x >> 1) + (y << 7) + (y << 5)));
        *p = (x & 1) ? ((*p & 0xF0) | getBW(c)) : ((*p & 0x0F) | (getBW(c) << 4));
    }
    // 16 bpp
    else
    {
        unsigned char *scr_base = VRAM;
        unsigned char *ptr;
        ptr = scr_base + sizeof(uint16_t) * (x + SCREEN_WIDTH * y);
        *(unsigned short*)ptr = c;
    }
}

void nio_vram_draw(void)
{
	memcpy(SCREEN_BASE_ADDRESS,VRAM,SCREEN_BYTES_SIZE);
}

#else

void nio_vram_pixel_set(const int x, const int y, const unsigned int color)
{
	nio_pixel_set(x,y,color);
}

void nio_vram_draw(void)
{

}

#endif // NIO_ENABLE_VRAM

unsigned int nio_cursor_clock(void) {
    return *(volatile unsigned*)0x90090000;
}

BOOL shift = FALSE;
BOOL caps = FALSE;
BOOL ctrl = FALSE;
static char shiftKey(const char normalc, const char shiftc)
{
	if(shift || caps) 
	{
		shift = FALSE;
		return shiftc;
	}
	else return normalc;
}
static char shiftOrCtrlKey(const char normalc, const char shiftc, const char ctrlc)
{
	if(shift || caps)
	{
		shift = FALSE;
		return shiftc;
	}
	else if(ctrl)
	{
		ctrl = FALSE;
		return ctrlc;
	}
	else return normalc;
}

char nio_ascii_get(int* adaptive_cursor_state)
{
	// Ctrl, Shift, Caps first
	if(isKeyPressed(KEY_NSPIRE_CTRL))
	{
		if(ctrl)
		{
			ctrl = FALSE;
			*adaptive_cursor_state = 0;
		}
		else
		{
			ctrl = TRUE;
			*adaptive_cursor_state = 4;
		}
		return 1; // Indicates that no key has been pressed - the cursor will continue flashing.
	}
	if(isKeyPressed(KEY_NSPIRE_SHIFT))
	{
		if(ctrl)
		{
			ctrl = FALSE;
			shift = FALSE;
			caps = TRUE;
			*adaptive_cursor_state = 2;
		}
		else if(caps)
		{
			caps = FALSE;
			*adaptive_cursor_state = 0;
		}
		else if(shift)
		{
			shift = FALSE;
			*adaptive_cursor_state = 0;
		}
		else
		{
			shift = TRUE;
			*adaptive_cursor_state = 1;
		}
		return 1;
	}
	
	if(caps)
		*adaptive_cursor_state = 2;
	
	if(isKeyPressed(KEY_NSPIRE_ESC)) return 0;
	
	// Characters
	if(isKeyPressed(KEY_NSPIRE_A)) return shiftKey('a','A');
	if(isKeyPressed(KEY_NSPIRE_B)) return shiftKey('b','B');
	if(isKeyPressed(KEY_NSPIRE_C)) return shiftKey('c','C');
	if(isKeyPressed(KEY_NSPIRE_D)) return shiftKey('d','D');
	if(isKeyPressed(KEY_NSPIRE_E)) return shiftKey('e','E');
	if(isKeyPressed(KEY_NSPIRE_F)) return shiftKey('f','F');
	if(isKeyPressed(KEY_NSPIRE_G)) return shiftKey('g','G');
	if(isKeyPressed(KEY_NSPIRE_H)) return shiftKey('h','H');
	if(isKeyPressed(KEY_NSPIRE_I)) return shiftKey('i','I');
	if(isKeyPressed(KEY_NSPIRE_J)) return shiftKey('j','J');
	if(isKeyPressed(KEY_NSPIRE_K)) return shiftKey('k','K');
	if(isKeyPressed(KEY_NSPIRE_L)) return shiftKey('l','L');
	if(isKeyPressed(KEY_NSPIRE_M)) return shiftKey('m','M');
	if(isKeyPressed(KEY_NSPIRE_N)) return shiftKey('n','N');
	if(isKeyPressed(KEY_NSPIRE_O)) return shiftKey('o','O');
	if(isKeyPressed(KEY_NSPIRE_P)) return shiftKey('p','P');
	if(isKeyPressed(KEY_NSPIRE_Q)) return shiftKey('q','Q');
	if(isKeyPressed(KEY_NSPIRE_R)) return shiftKey('r','R');
	if(isKeyPressed(KEY_NSPIRE_S)) return shiftKey('s','S');
	if(isKeyPressed(KEY_NSPIRE_T)) return shiftKey('t','T');
	if(isKeyPressed(KEY_NSPIRE_U)) return shiftKey('u','U');
	if(isKeyPressed(KEY_NSPIRE_V)) return shiftKey('v','V');
	if(isKeyPressed(KEY_NSPIRE_W)) return shiftKey('w','W');
	if(isKeyPressed(KEY_NSPIRE_X)) return shiftKey('x','X');
	if(isKeyPressed(KEY_NSPIRE_Y)) return shiftKey('y','Y');
	if(isKeyPressed(KEY_NSPIRE_Z)) return shiftKey('z','Z');
	
	// Numbers
	if(isKeyPressed(KEY_NSPIRE_0)) return '0';
	if(isKeyPressed(KEY_NSPIRE_1)) return '1';
	if(isKeyPressed(KEY_NSPIRE_2)) return '2';
	if(isKeyPressed(KEY_NSPIRE_3)) return '3';
	if(isKeyPressed(KEY_NSPIRE_4)) return '4';
	if(isKeyPressed(KEY_NSPIRE_5)) return '5';
	if(isKeyPressed(KEY_NSPIRE_6)) return '6';
	if(isKeyPressed(KEY_NSPIRE_7)) return '7';
	if(isKeyPressed(KEY_NSPIRE_8)) return '8';
	if(isKeyPressed(KEY_NSPIRE_9)) return '9';
	
	// Symbols
	if(isKeyPressed(KEY_NSPIRE_COMMA))		return shiftKey(',',';');
	if(isKeyPressed(KEY_NSPIRE_PERIOD)) 	return shiftKey('.',':');
	if(isKeyPressed(KEY_NSPIRE_COLON))		return ':';
	if(isKeyPressed(KEY_NSPIRE_LP))			return shiftOrCtrlKey('(','[',']');
	if(isKeyPressed(KEY_NSPIRE_RP))			return shiftOrCtrlKey(')','{','}');
	if(isKeyPressed(KEY_NSPIRE_SPACE))		return shiftKey(' ','_');
	if(isKeyPressed(KEY_NSPIRE_DIVIDE))		return shiftKey('/','\\');
	if(isKeyPressed(KEY_NSPIRE_MULTIPLY))	return shiftKey('*','\"');
	if(isKeyPressed(KEY_NSPIRE_MINUS))		return shiftKey('-','_');
	if(isKeyPressed(KEY_NSPIRE_NEGATIVE))	return shiftKey('-','_');
	if(isKeyPressed(KEY_NSPIRE_PLUS))		return '+';
	if(isKeyPressed(KEY_NSPIRE_EQU))		return '=';
	if(isKeyPressed(KEY_NSPIRE_LTHAN))		return '<';
	if(isKeyPressed(KEY_NSPIRE_GTHAN))		return '>';
	if(isKeyPressed(KEY_NSPIRE_QUOTE))		return '\"';
	if(isKeyPressed(KEY_NSPIRE_APOSTROPHE))	return '\'';
	if(isKeyPressed(KEY_NSPIRE_QUES))		return shiftKey('?','!');
	if(isKeyPressed(KEY_NSPIRE_QUESEXCL))	return shiftKey('?','!');
	if(isKeyPressed(KEY_NSPIRE_BAR))		return '|';
	if(isKeyPressed(KEY_NSPIRE_EXP))		return '^';
	if(isKeyPressed(KEY_NSPIRE_ENTER))		return shiftKey('\n','~');
	if(isKeyPressed(KEY_NSPIRE_SQU))		return '²';
	
	// Special chars
	#ifdef KEY_NSPIRE_CLEAR // Keep better Ndless 2 compatibility (clickpad)
	if(isKeyPressed(KEY_NSPIRE_DEL)
	 ||isKeyPressed(KEY_NSPIRE_CLEAR))		return '\b';
	#else
	if(isKeyPressed(KEY_NSPIRE_DEL))		return '\b';
	#endif
	if(isKeyPressed(KEY_NSPIRE_RET))		return '\n';
	if(isKeyPressed(KEY_NSPIRE_TAB))		return '\t';
	
	return 0;
}
