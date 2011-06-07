/**
 * @file console.c
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
 * Console functions
 */
#include <os.h>
#include "nspireio.h"

#define MAX_ROW 30
#define MAX_COL 53

char	c_buffer[MAX_COL][MAX_ROW];
char	c_bgColor;
char	c_textColor;
int		cursorX;
int		cursorY;

// Functions that can be used without c_init()
void locate(int x, int y, char *str, char bgColor, char textColor)
{
	putStr(x*6,y*8,str,bgColor,textColor);
}
void locatec(int x, int y, char ch, char bgColor, char textColor)
{
	putChar(x*6,y*8,ch,bgColor,textColor);
}

void c_init(char bgColor, char textColor)
{
	c_bgColor	= bgColor;
	c_textColor	= textColor;
	c_clear();
	c_draw();
}
void c_clear(void)
{
	cursorX		= 0;
	cursorY		= 0;
	memset(c_buffer,'\0',sizeof(c_buffer));
}

void c_writec(char ch)
{
	// Check for escape strings first
	if(ch == '\n')
	{
		if(cursorY > MAX_ROW)
		{
			// Scroll down here
			// ****************
			c_clear();
			c_draw();
		}
		else
		{
			cursorX = 0;
			cursorY++;
		}
	}
	else if(ch == '\r')
	{
		cursorX = 0;
	}
	else if(ch == '\b')
	{
		if(cursorX > 0)
		{
			cursorX--;
		}
	}
	else if(ch == '\t')
	{
		int t;
		for(t=5;t<=MAX_COL;t+=5)
		{
			if(cursorX < t)
			{
				cursorX = t;
				break;
			}
		}
	}
	else
	{
		if(cursorX >= MAX_COL)
		{
			if(cursorY > MAX_ROW)
			{
				// Scroll down here
				// ****************
				c_clear();
				c_draw();
			}
			else
			{
				cursorY++;
				cursorX = 0;
			}
		}
		c_buffer[cursorX][cursorY] = ch;
		locatec(cursorX,cursorY,ch,c_bgColor,c_textColor);
		cursorX++;
	}
}

void c_write(char *str)
{
	int len = strlen(str);
	int i;
	for(i = 0; i < len; i++)
	{
		c_writec(str[i]);
	}
}

void c_swrite(char *format, int buflen, ...)
{
	char buf[buflen];
	memset(buf,'\0',sizeof(char)*buflen);
	__builtin_va_list arglist;
	__builtin_va_start(arglist,buflen);
	vsprintf(buf,format,*(char **)&arglist);
	c_write(buf);
	__builtin_va_end(arglist);
}

void c_draw(void)
{
	int row,col;
	for(row = 0; row < MAX_ROW; row++)
	{
		for(col = 0; col < MAX_COL; col++)
		{
			if(c_buffer[col][row] != '\0')
			{
				locatec(col,row,c_buffer[col][row],c_bgColor,c_textColor);
			}
			else
			{
				locatec(col,row,' ',c_bgColor,c_textColor);
			}
		}
	}
}

// Input
BOOL shift = FALSE;
BOOL caps = FALSE;
BOOL ctrl = FALSE;
char shiftKey(char normalc, char shiftc)
{
	if(shift || caps) 
	{
		shift = FALSE;
		return shiftc;
	}
	else return normalc;
}
char shiftOrCtrlKey(char normalc, char shiftc, char ctrlc)
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
char cn_readc(void)
{
	while(1)
	{
		wait_key_pressed();
		
		// Ctrl, Shift, Caps first
		if(isKeyPressed(KEY_NSPIRE_CTRL))
		{
			if(ctrl) ctrl = FALSE;
			else ctrl = TRUE;
		}
		if(isKeyPressed(KEY_NSPIRE_SHIFT) || isKeyPressed(KEY_NSPIRE_CAPS))
		{
			if(ctrl)
			{
				ctrl = FALSE;
				shift = FALSE;
				caps = TRUE;
			}
			else if(caps) caps = FALSE;
			else if(shift) shift = FALSE;
			else shift = TRUE;
		}
		
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
		if(isKeyPressed(KEY_NSPIRE_DEL)||isKeyPressed(KEY_NSPIRE_CLEAR))	return '\b';
		if(isKeyPressed(KEY_NSPIRE_RET))									return '\n';
		if(isKeyPressed(KEY_NSPIRE_TAB))									return '\t';
	}
}
char c_readc(void)
{
	char tmp = cn_readc();
	c_writec(tmp);
	return tmp;
}

int c_read(char* str)
{
	char tmp;
	int i = 0;
	int oldCursorX = cursorX;
	int oldCursorY = cursorY;
	while(1)
	{
		tmp = cn_readc();
		if(tmp == '\n')
		{
			str[i] = '\0';
			return (i>0)?1:0;
		}
		else if(tmp == '\b')
		{
			if(cursorX == 0 && cursorY > oldCursorY && i > 0)
			{
				cursorY--;
				cursorX = MAX_COL;
			}
			if((cursorX > oldCursorX || (cursorX > 0 && cursorY > oldCursorY)) && i > 0)
			{
				c_write("\b \b");
				i--;
			}
		}
		else if(tmp == '\0')
		{
			return 0;
		}
		else
		{
			str[i] = tmp;
			c_writec(tmp);
			i++;
		}
	}
}
