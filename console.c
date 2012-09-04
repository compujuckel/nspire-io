/**
 * @file console.c
 * @author  Julian Mackeben aka compu <compujuckel@googlemail.com>
 * @version 2.0
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
 * Console functions
 */
#include "nspireio2.h"
#include <os.h>

nio_console* nio_default = NULL;

void nio_grid_puts(const int offset_x, const int offset_y, const int x, const int y, const char *str, const char bgColor, const char textColor)
{
	nio_pixel_puts(offset_x+x*6,offset_y+y*8,str,bgColor,textColor);
}
void nio_grid_putc(const int offset_x, const int offset_y, const int x, const int y, const char ch, const char bgColor, const char textColor)
{
	nio_pixel_putc(offset_x+x*6,offset_y+y*8,ch,bgColor,textColor);
}

void nio_use_stdio(void)
{
    nio_default = malloc(sizeof(nio_console));
    nio_init(nio_default,53,30,0,0,WHITE,BLACK,TRUE);
}

void nio_free_stdio(void)
{
    nio_free(nio_default);
}

void nio_load(const char* path, nio_console* c)
{
	FILE* f = fopen(path,"rb");
	
	fread(&c->cursor_x,sizeof(int),1,f);
	fread(&c->cursor_y,sizeof(int),1,f);
	
	fread(&c->max_x,sizeof(int),1,f);
	fread(&c->max_y,sizeof(int),1,f);
	
	fread(&c->offset_x,sizeof(int),1,f);
	fread(&c->offset_y,sizeof(int),1,f);
	
	fread(&c->default_background_color,sizeof(char),1,f);
	fread(&c->default_foreground_color,sizeof(char),1,f);
	
	fread(&c->drawing_enabled,sizeof(BOOL),1,f);
	
	c->data = malloc(c->max_x*c->max_y);
	c->color = malloc(c->max_x*c->max_y);
	
	fread(c->data,sizeof(char),c->max_x*c->max_y,f);
	fread(c->color,sizeof(char),c->max_x*c->max_y,f);
	
	fclose(f);
}

void nio_save(const char* path, const nio_console* c)
{
	FILE* f = fopen(path,"wb");
	
	fwrite(&c->cursor_x,sizeof(int),1,f);
	fwrite(&c->cursor_y,sizeof(int),1,f);
	
	fwrite(&c->max_x,sizeof(int),1,f);
	fwrite(&c->max_y,sizeof(int),1,f);
	
	fwrite(&c->offset_x,sizeof(int),1,f);
	fwrite(&c->offset_y,sizeof(int),1,f);
	
	fwrite(&c->default_background_color,sizeof(char),1,f);
	fwrite(&c->default_foreground_color,sizeof(char),1,f);
	
	fwrite(&c->drawing_enabled,sizeof(BOOL),1,f);
	
	fwrite(c->data,sizeof(char),c->max_x*c->max_y,f);
	fwrite(c->color,sizeof(char),c->max_x*c->max_y,f);
	
	fclose(f);
}

void nio_set_default(nio_console* c)
{
    nio_default = c;
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
char nio_getch(void)
{
	while(1)
	{
		//wait_key_pressed();
		while (!any_key_pressed())
			idle();
		
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
		#ifdef KEY_NSPIRE_CLEAR // Keep better Ndless 2 compatibility (clickpad)
		if(isKeyPressed(KEY_NSPIRE_DEL)
		 ||isKeyPressed(KEY_NSPIRE_CLEAR))		return '\b';
		#else
		if(isKeyPressed(KEY_NSPIRE_DEL))		return '\b';
		#endif
		if(isKeyPressed(KEY_NSPIRE_RET))		return '\n';
		if(isKeyPressed(KEY_NSPIRE_TAB))		return '\t';
	}
}

void nio_init(nio_console* c, const int size_x, const int size_y, const int offset_x, const int offset_y, const char background_color, const char foreground_color, const BOOL drawing_enabled)
{
	c->max_x = size_x;
	c->max_y = size_y;
	c->offset_x = offset_x;
	c->offset_y = offset_y;
	c->cursor_x = 0;
	c->cursor_y = 0;
	c->drawing_enabled = drawing_enabled;
	c->default_background_color = background_color;
	c->default_foreground_color = foreground_color;
	c->data = malloc(c->max_x*c->max_y);
	c->color = malloc(c->max_x*c->max_y);
	nio_clear(c);
}

int nio_fflush(nio_console* c)
{
	int row, col;
	for(row = 0; row < c->max_y; row++)
	{
		for(col = 0; col < c->max_x; col++)
		{
			nio_csl_drawchar(c,col,row);
		}
	}
    return 0;
}

void nio_clear(nio_console* c)
{
	char color = (c->default_background_color << 4) | c->default_foreground_color;
	memset(c->data,0,c->max_x*c->max_y);
	memset(c->color,color,c->max_x*c->max_y);
	c->cursor_x = 0;
	c->cursor_y = 0;
	if(c->drawing_enabled)
		nio_fflush(c);
}

void nio_scroll(nio_console* c)
{
	char* temp;
	temp = malloc(c->max_x*c->max_y);
	
	memset(temp,0,c->max_x*c->max_y);
	memcpy(temp,c->data+c->max_x,c->max_x*(c->max_y-1));
	memcpy(c->data,temp,c->max_x*c->max_y);
	
	char color = (c->default_background_color << 4) | c->default_foreground_color;
	memset(temp,color,c->max_x*c->max_y);
	memcpy(temp,c->color+c->max_x,c->max_x*(c->max_y-1));
	memcpy(c->color,temp,c->max_x*c->max_y);
	
	if(c->cursor_y > 0)
		c->cursor_y--;
	c->cursor_x = 0;
	
	free(temp);
}

void nio_csl_drawchar(nio_console* c, const int pos_x, const int pos_y)
{
	char ch = c->data[pos_y*c->max_x+pos_x];
	char color = c->color[pos_y*c->max_x+pos_x];
	
	char background_color = (color & 0xF0) >> 4;
	char foreground_color = color & 0x0F;
	
	nio_grid_putc(c->offset_x, c->offset_y, pos_x, pos_y, ch == 0 ? ' ' : ch, background_color, foreground_color);
}

void nio_csl_savechar(nio_console* c, const char ch, const int pos_x, const int pos_y)
{
	char color = (c->default_background_color << 4) | c->default_foreground_color;
	
	c->data[pos_y*c->max_x+pos_x] = ch;
	c->color[pos_y*c->max_x+pos_x] = color;
}

char nio_fputc(char ch, nio_console* c)
{
	// Newline. Increment Y cursor, set X cursor to zero. Scroll if necessary.
	if(ch == '\n')
	{
		c->cursor_x = 0;
		c->cursor_y++;
		// Scrolling necessary?
		if(c->cursor_y >= c->max_y)
		{
			nio_scroll(c);
			if(c->drawing_enabled)
				nio_fflush(c);
		}
	}
	// Carriage return. Set X cursor to zero.
	else if(ch == '\r')
	{
		c->cursor_x = 0;
	}
	// Backspace. Decrement X cursor.
	else if(ch == '\b')
	{
		if(c->cursor_x > 0)
			c->cursor_x--;
	}
	else if(ch == '\t')
	{
		// tabs are 8 character long
		c->cursor_x += (9-1) - c->cursor_x % 8;
		ch = ' ';
	}
	// Must be a normal character...
	else
	{
		// Check if the cursor is valid
		if(c->cursor_x >= c->max_x)
		{
			c->cursor_x = 0;
			c->cursor_y++;
		}
		if(c->cursor_y >= c->max_y)
		{
			nio_scroll(c);
			if(c->drawing_enabled)
				nio_fflush(c);
		}
		// Then store it.
		nio_csl_savechar(c,ch,c->cursor_x,c->cursor_y);
		
		// Draw it when BOOL draw is true
		if(c->drawing_enabled) nio_csl_drawchar(c,c->cursor_x,c->cursor_y);
		
		// Increment X cursor. It will be checked for validity next time.
		c->cursor_x++;
	}
    return ch;
}

char nio_putchar(const char ch)
{
    return nio_fputc(ch,nio_default);
}

int nio_fputs(const char* str, nio_console* c)
{
	int len = strlen(str);
	int i;
	for(i = 0; i < len; i++)
	{
		nio_fputc(str[i], c);
	}
    return 1;
}

int nio_puts(const char* str)
{
    return nio_fputs(str,nio_default);
}

int nio_fprintf(nio_console* c, const char *format, ...)
{
    char buf[1000];
    memset(buf,'\0',sizeof(buf));
    __builtin_va_list arglist;
    __builtin_va_start(arglist,format);
    vsprintf(buf,format,*(char **)&arglist);
    nio_fputs(buf,c);
    __builtin_va_end(arglist);
    return strlen(buf);
}

int nio_printf(const char *format, ...)
{
    char buf[1000];
    memset(buf,'\0',sizeof(buf));
    __builtin_va_list arglist;
    __builtin_va_start(arglist,format);
    vsprintf(buf,format,*(char **)&arglist);
    nio_puts(buf);
    __builtin_va_end(arglist);
    return strlen(buf);
}

// This implementation won't work...
/*int nio_vfprintf(nio_console* c, const char* format, va_list* arglist)
{
    char buf[1000];
    memset(buf,'\0',sizeof(buf));
    vsprintf(buf,format,arglist);
    nio_fputs(buf,c);
    return strlen(buf);
}

int nio_fprintf(nio_console* c, const char* format, ...)
{
	va_list arglist;
	va_start(arglist,format);
	int ret = nio_vfprintf(c,format,&arglist);
	va_end(arglist);
    return ret;
}

int nio_printf(const char* format, ...)
{
    va_list arglist;
	va_start(arglist,format);
	int ret = nio_vfprintf(nio_default,format,&arglist);
	va_end(arglist);
    return ret;
}*/

void nio_color(nio_console* c, const char background_color, const char foreground_color)
{
	c->default_background_color = background_color;
	c->default_foreground_color = foreground_color;
}

void nio_drawing_enabled(nio_console* c, const BOOL enable_drawing)
{
	c->drawing_enabled = enable_drawing;
}

char nio_fgetc(nio_console* c)
{
	char ch = nio_getch();
	nio_fputc(ch,c);
	return ch;
}

char nio_getchar(void)
{
    return nio_fgetc(nio_default);
}

char* nio_fgets(char* str, int num, nio_console* c) // TODO: Do not ignore num
{
	char tmp;
	int old_x = c->cursor_x;
	int old_y = c->cursor_y;
	
	int i = 0;
	while(1)
	{
		wait_no_key_pressed();
		tmp = nio_getch();
		if(tmp == '\n')
		{
			str[i] = '\0';
			nio_fputc('\n', c);
			return i > 0 ? str : NULL;
		}
		else if(tmp == '\b')
		{
			if(c->cursor_x == 0 && c->cursor_y > old_y && i > 0)
			{
				c->cursor_y--;
				c->cursor_x = c->max_x;
			}
			if((c->cursor_x > old_x || (c->cursor_x > 0 && c->cursor_y > old_y )) && i > 0)
			{
				nio_fputs("\b \b", c);
				i--;
			}
		}
		else if(tmp == '\0')
		{
			str[0] = '\0';
			nio_fputc('\n',c);
			return NULL;
		}
		else
		{
			str[i] = tmp;
			nio_fputc(tmp, c);
			i++;
		}
	}
}

char* nio_gets(char* str)
{
    return nio_fgets(str,1000,nio_default); // using 1000 as default here
}

void nio_free(nio_console* c)
{
	free(c->data);
	free(c->color);
}