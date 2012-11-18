/**
 * @file prizm.c
 * @author Julien Savard aka Juju <juju2143@gmail.com>
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
 * Prizm-specific source.
 */

#include "nspireio-platform.h"

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
	unsigned short *scr = VRAM;
	if(x >= 0 && x < LCD_WIDTH_PX && y >= 0 && y < LCD_HEIGHT_PX)
	{
		Bdisp_SetPoint_DD(x, y, getPaletteColor(color));
	}
}

void nio_vram_pixel_set(const int x, const int y, const unsigned int color)
{
	// Put a pixel in VRAM
	unsigned short *scr = VRAM;
	if(x >= 0 && x < LCD_WIDTH_PX && y >= 0 && y < LCD_HEIGHT_PX)
	{
		scr[y*LCD_WIDTH_PX+x] = getPaletteColor(color);
	}
}

void nio_vram_draw(void)
{
	// Draw VRAM to screen
	Bdisp_PutDisp_DD();
}

unsigned int nio_cursor_clock(void)
{
	return RTC_GetTicks()/128;
}

#define KEY_COUNT 50
char keyTable[KEY_COUNT][8]=
{
        {79,1      ,1      ,1      ,1      ,1      ,1      ,1      },//F1
        {69,1      ,1      ,1      ,1      ,1      ,1      ,1      },//F2
        {59,1      ,1      ,1      ,1      ,1      ,1      ,1      },//F3
        {49,1      ,1      ,1      ,1      ,1      ,1      ,1      },//F4
        {39,1      ,1      ,1      ,1      ,1      ,1      ,1      },//F5
        {29,1      ,1      ,1      ,1      ,1      ,1      ,1      },//F6
        {78,1      ,1      ,1      ,1      ,1      ,1      ,1      },//shift
        {68,1      ,1      ,1      ,1      ,1      ,1      ,1      },//optn
        {58,1      ,1      ,1      ,1      ,1      ,1      ,1      },//vars
        {48,0      ,0      ,0      ,0      ,0      ,0      ,0      },//menu
        {38,'\2'   ,'\2'   ,'\2'   ,'\2'   ,'\2'   ,'\2'   ,'\2'   },//left
        {28,'\20'  ,'\20'  ,'\20'  ,'\20'  ,'\20'  ,'\20'  ,'\20'  },//up
        {77,1      ,1      ,1      ,1      ,1      ,1      ,1      },//alpha
        {67,1      ,1      ,1      ,1      ,1      ,1      ,1      },//x^2
        {57,1      ,1      ,1      ,1      ,1      ,1      ,1      },//^
        {47,'\33'  ,'\33'  ,'\33'  ,'\33'  ,'\33'  ,'\33'  ,'\33'  },//exit
        {37,'\16'  ,'\16'  ,'\16'  ,'\16'  ,'\16'  ,'\16'  ,'\16'  },//down
        {27,'\6'   ,'\6'   ,'\6'   ,'\6'   ,'\6'   ,'\6'   ,'\6'   },//right
        {76,1      ,'A'    ,1      ,'a'    ,'\1'   ,1      ,1      },//x,t
        {66,1      ,'B'    ,1      ,'b'    ,'\2'   ,1      ,1      },//log
        {56,1      ,'C'    ,1      ,'c'    ,'\3'   ,1      ,1      },//ln
        {46,1      ,'D'    ,1      ,'d'    ,'\4'   ,1      ,1      },//sin
        {36,1      ,'E'    ,1      ,'e'    ,'\5'   ,1      ,1      },//cos
        {26,1      ,'F'    ,1      ,'f'    ,'\6'   ,1      ,1      },//tan
        {75,1      ,'G'    ,1      ,'g'    ,'\7'   ,1      ,1      },//a/b/c
        {65,'\t'   ,'H'    ,1      ,'h'    ,'\10'  ,1      ,1      },//F-D
        {55,'('    ,'I'    ,1      ,'i'    ,'\11'  ,1      ,1      },//(
        {45,')'    ,'J'    ,1      ,'j'    ,'\12'  ,1      ,1      },//)
        {35,','    ,'K'    ,1      ,'k'    ,'\13'  ,1      ,1      },//,
        {25,1      ,'L'    ,1      ,'l'    ,'\14'  ,1      ,1      },//->
        {74,'7'    ,'M'    ,'&'    ,'m'    ,'\15'  ,1      ,1      },//7
        {64,'8'    ,'N'    ,1      ,'n'    ,'\16'  ,1      ,1      },//8
        {54,'9'    ,'O'    ,1      ,'o'    ,'\17'  ,1      ,1      },//9
        {44,'\b'   ,'\b'   ,'\b'   ,'\b'   ,'\b'   ,'\b'   ,'\b'   },//del
        {10,'\3'   ,'\3'   ,'\3'   ,'\3'   ,'\3'   ,'\3'   ,'\3'   },//ac
        {73,'4'    ,'P'    ,'$'    ,'p'    ,'\20'  ,1      ,1      },//4
        {63,'5'    ,'Q'    ,'%'    ,'q'    ,'\21'  ,1      ,1      },//5
        {53,'6'    ,'R'    ,'^'    ,'r'    ,'\22'  ,1      ,1      },//6
        {43,'*'    ,'S'    ,'{'    ,'s'    ,'\23'  ,1      ,1      },//*
        {33,'/'    ,'T'    ,'}'    ,'t'    ,'\24'  ,1      ,1      },///
        {72,'1'    ,'U'    ,'!'    ,'u'    ,'\25'  ,1      ,1      },//1
        {62,'2'    ,'V'    ,'@'    ,'v'    ,'\26'  ,1      ,1      },//2
        {52,'3'    ,'W'    ,'#'    ,'w'    ,'\27'  ,1      ,1      },//3
        {42,'+'    ,'X'    ,'['    ,'x'    ,'\30'  ,1      ,1      },//+
        {32,'-'    ,'Y'    ,']'    ,'y'    ,'\31'  ,1      ,1      },//-
        {71,'0'    ,'Z'    ,1      ,'z'    ,'\32'  ,1      ,1      },//0
        {61,'.'    ,' '    ,'='    ,' '    ,1      ,1      ,1      },//.
        {51,'?'    ,'\"'   ,1      ,1      ,1      ,1      ,1      },//exp
        {41,'_'    ,';'    ,':'    ,'-'    ,1      ,1      ,1      },//(-)
        {31,'\n'   ,'\n'   ,'\n'   ,'\n'   ,'\n'   ,'\n'   ,'\n'   },//exe
};

const unsigned short* keyboard_register = (unsigned short*)0xA44B0000;
unsigned short lastkey[8];
unsigned short holdkey[8];

void keyupdate(void)
{
	memcpy(holdkey, lastkey, sizeof(unsigned short)*8);
	memcpy(lastkey, keyboard_register, sizeof(unsigned short)*8);
}
int keydownlast(int basic_keycode)
{
        int row, col, word, bit;
        row = basic_keycode%10;
        col = basic_keycode/10-1;
        word = row>>1;
        bit = col + 8*(row&1);
        return (0 != (lastkey[word] & 1<<bit));
}
int keydownhold(int basic_keycode)
{
        int row, col, word, bit;
        row = basic_keycode%10;
        col = basic_keycode/10-1;
        word = row>>1;
        bit = col + 8*(row&1);
        return (0 != (holdkey[word] & 1<<bit));
}
int isKeyPressed(int basic_keycode)
{
        return (keydownlast(basic_keycode) && !keydownhold(basic_keycode));
}

void wait_key_pressed(void)
{
	while(any_key_pressed());
}
void wait_no_key_pressed(void)
{
	while(!any_key_pressed());
}
BOOL any_key_pressed(void)
{
	keyupdate();
	int i = 0;
	while(i<KEY_COUNT)
	{
		if(isKeyPressed(keyTable[i][0]))
		{
			return TRUE;
		}
	}
	return FALSE;
}

// 1: normal
// 2: upper
// 3: shift
// 4: lower
// 5: ctrl
int keystate = 1;
BOOL shift = FALSE;
BOOL caps = FALSE;
BOOL ctrl = FALSE;

char nio_ascii_get(int* adaptive_cursor_state)
{
	// Return an ascii char.
	// 0 = user abort (e.g. ESC)
	// 1 = No key pressed (use this for modifier keys like shift)

	int i = 0;

	keyupdate();

	// Ctrl, Shift, Caps first
	if(isKeyPressed(KEY_PRGM_ALPHA))
	{
		if(ctrl)
		{
			ctrl = FALSE;
			keystate = 1;
			*adaptive_cursor_state = 0;
		}
		else
		{
			ctrl = TRUE;
			keystate = 4;
			*adaptive_cursor_state = 3;
		}
		return 1; // Indicates that no key has been pressed - the cursor will continue flashing.
	}
	if(isKeyPressed(KEY_PRGM_SHIFT))
	{
		if(ctrl)
		{
			ctrl = FALSE;
			shift = FALSE;
			caps = TRUE;
			keystate = 2;
			*adaptive_cursor_state = 2;
		}
		else if(caps)
		{
			caps = FALSE;
			keystate = 1;
			*adaptive_cursor_state = 0;
		}
		else if(shift)
		{
			shift = FALSE;
			keystate = 1;
			*adaptive_cursor_state = 0;
		}
		else
		{
			shift = TRUE;
			keystate = 3;
			*adaptive_cursor_state = 1;
		}
		return 1;
	}
	
	if(caps)
	{
		keystate = 2;
		*adaptive_cursor_state = 2;
	}

	while(i<KEY_COUNT)
	{
		if(isKeyPressed(keyTable[i][0]))
		{
			return keyTable[i][keystate];
		}
	}
}
