/**
 * @file console.c
 * @author  Julian Mackeben aka compu <compujuckel@googlemail.com>
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
 * Console functions
 */

#include <stdarg.h>
#include "../include/nspireio/nspireio.h"
#include "charmap.h"
#include "util.h"

static nio_console* nio_default = NULL;
static unsigned int csl_count = 0;

unsigned char adaptive_cursor[5][6] =
{
	{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}, // block cursor
	{0xF7,0xF3,0x01,0x01,0xF3,0xF7}, // arrow cursor
	{0x83,0xED,0xEE,0xED,0x83,0xFF}, // 'A' cursor
	{0xDF,0xAB,0xAB,0xAB,0xC7,0xFF}, // 'a' cursor
	{0xDB,0x81,0xDB,0xDB,0x81,0xDB}  // '#' cursor
};

void nio_pixel_putc(const int x, const int y, const char ch, const int bgColor, const int textColor)
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

void nio_pixel_puts(const int x, const int y, const char* str, const int bgColor, const int textColor)
{
	int l = strlen(str);
	int i;
	int stop=0;
	int xtemp = x;
	for (i = 0; i < l && !stop; i++)
	{
		nio_pixel_putc(xtemp, y, str[i], bgColor, textColor);
		xtemp += NIO_CHAR_WIDTH;
		if (xtemp >= SCREEN_WIDTH-NIO_CHAR_WIDTH)
		{
			stop=1;
		}
	}
}

void nio_grid_puts(const int offset_x, const int offset_y, const int x, const int y, const char *str, const unsigned char bgColor, const unsigned char textColor)
{
	nio_pixel_puts(offset_x+x*NIO_CHAR_WIDTH,offset_y+y*NIO_CHAR_HEIGHT,str,bgColor,textColor);
}
void nio_grid_putc(const int offset_x, const int offset_y, const int x, const int y, const char ch, const unsigned char bgColor, const unsigned char textColor)
{
	nio_pixel_putc(offset_x+x*NIO_CHAR_WIDTH,offset_y+y*NIO_CHAR_HEIGHT,ch,bgColor,textColor);
}

void nio_vram_pixel_putc(const int x, const int y, const char ch, const int bgColor, const int textColor)
{
	// Put a char in VRAM
	int i, j, pixelOn;
	for(i = 0; i < NIO_CHAR_WIDTH; i++)
	{
		for(j = NIO_CHAR_HEIGHT; j > 0; j--)
		{
			pixelOn = MBCharSet8x6_definition[(unsigned char)ch][i] << j ;
			pixelOn = pixelOn & 0x80 ;
			if (pixelOn) 		nio_vram_pixel_set(x+i,y+NIO_CHAR_HEIGHT-j,textColor);
			else if(!pixelOn) 	nio_vram_pixel_set(x+i,y+NIO_CHAR_HEIGHT-j,bgColor);
		}
	}
}

void nio_vram_pixel_puts(const int x, const int y, const char* str, const int bgColor, const int textColor)
{
	// Put a string in VRAM
	int l = strlen(str);
	int i;
	int stop=0;
	int xtemp = x;
	for (i = 0; i < l && !stop; i++)
	{
		nio_vram_pixel_putc(xtemp, y, str[i], bgColor, textColor);
		xtemp += NIO_CHAR_WIDTH;
		if (xtemp >= SCREEN_WIDTH-NIO_CHAR_WIDTH)
		{
			stop=1;
		}
	}
}

void nio_vram_grid_puts(const int offset_x, const int offset_y, const int x, const int y, const char *str, const unsigned char bgColor, const unsigned char textColor)
{
	nio_vram_pixel_puts(offset_x+x*NIO_CHAR_WIDTH,offset_y+y*NIO_CHAR_HEIGHT,str,bgColor,textColor);
}
void nio_vram_grid_putc(const int offset_x, const int offset_y, const int x, const int y, const char ch, const unsigned char bgColor, const unsigned char textColor)
{
	nio_vram_pixel_putc(offset_x+x*NIO_CHAR_WIDTH,offset_y+y*NIO_CHAR_HEIGHT,ch,bgColor,textColor);
}

bool nio_load(const char* path, nio_console* csl)
{
	nio_console_private *c = *csl = malloc(sizeof(nio_console_private));
	if (!c) goto err2;
	*c = (nio_console_private){0};
	++csl_count;

	FILE* f = fopen(path,"rb");
	if (!f) goto err2;

	fread(&c->cursor_x,sizeof(int),1,f);
	fread(&c->cursor_y,sizeof(int),1,f);

	fread(&c->max_x,sizeof(int),1,f);
	fread(&c->max_y,sizeof(int),1,f);

	fread(&c->offset_x,sizeof(int),1,f);
	fread(&c->offset_y,sizeof(int),1,f);

	fread(&c->default_background_color,sizeof(char),1,f);
	fread(&c->default_foreground_color,sizeof(char),1,f);

	fread(&c->drawing_enabled,sizeof(BOOL),1,f);

	fread(&c->cursor_enabled,sizeof(BOOL),1,f);
	fread(&c->cursor_type,sizeof(int),1,f);
	fread(&c->cursor_line_width,sizeof(int),1,f);
	fread(&c->cursor_custom_data,sizeof(char)*6,1,f);
	fread(&c->cursor_blink_enabled,sizeof(BOOL),1,f);
	fread(&c->cursor_blink_status,sizeof(BOOL),1,f);
	fread(&c->cursor_blink_timestamp,sizeof(BOOL),1,f);
	fread(&c->cursor_blink_duration,sizeof(BOOL),1,f);

	if(feof(f) || ferror(f)) goto err1;

	c->data = malloc(c->max_x*c->max_y);
	if(!c->data) goto err1;
	c->color = malloc(c->max_x*c->max_y*2);
	if(!c->color) goto err1;

	c->input_buf = malloc(sizeof(queue));
	if(!c->input_buf) goto err1;
	queue_init(c->input_buf);

	fread(c->data,sizeof(char),c->max_x*c->max_y,f);
	fread(c->color,sizeof(short),c->max_x*c->max_y,f);

	if(feof(f) || ferror(f)) goto err1;

	if (!nio_scrbuf_init()) goto err1;

	if(c->drawing_enabled)
		nio_fflush(csl);

	if(fclose(f) == EOF) goto err2;

	return true;

err1:
	fclose(f);
err2:
	nio_free(csl);
	return false;
}

bool nio_save(const char* path, const nio_console* csl)
{
	nio_console_private *c = *csl;
	FILE* f = fopen(path,"wb");
	if (!f) return false;

	fwrite(&c->cursor_x,sizeof(int),1,f);
	fwrite(&c->cursor_y,sizeof(int),1,f);

	fwrite(&c->max_x,sizeof(int),1,f);
	fwrite(&c->max_y,sizeof(int),1,f);

	fwrite(&c->offset_x,sizeof(int),1,f);
	fwrite(&c->offset_y,sizeof(int),1,f);

	fwrite(&c->default_background_color,sizeof(char),1,f);
	fwrite(&c->default_foreground_color,sizeof(char),1,f);

	fwrite(&c->drawing_enabled,sizeof(BOOL),1,f);

	fwrite(&c->cursor_enabled,sizeof(BOOL),1,f);
	fwrite(&c->cursor_type,sizeof(int),1,f);
	fwrite(&c->cursor_line_width,sizeof(int),1,f);
	fwrite(&c->cursor_custom_data,sizeof(char)*6,1,f);
	fwrite(&c->cursor_blink_enabled,sizeof(BOOL),1,f);
	fwrite(&c->cursor_blink_status,sizeof(BOOL),1,f);
	fwrite(&c->cursor_blink_timestamp,sizeof(BOOL),1,f);
	fwrite(&c->cursor_blink_duration,sizeof(BOOL),1,f);

	fwrite(c->data,sizeof(char),c->max_x*c->max_y,f);
	fwrite(c->color,sizeof(short),c->max_x*c->max_y,f);

	if(ferror(f)) {
		fclose(f);
		return false;
	}

	if(fclose(f) == EOF) return false;

	return true;
}

void nio_set_default(nio_console* c)
{
	nio_default = c;
}

void nio_set_idle_callback(nio_console* csl, int (*callback)(void*), void* data)
{
	nio_console_private *c = *csl;
	c->idle_callback = callback;
	c->idle_callback_data = data;
}

bool nio_init(nio_console* csl, const int size_x, const int size_y, const int offset_x, const int offset_y, const unsigned char background_color, const unsigned char foreground_color, const BOOL drawing_enabled)
{
	nio_console_private *c = *csl = malloc(sizeof(nio_console_private));
	if (!c) goto err;
	*c = (nio_console_private){0};
	++csl_count;

	c->max_x = size_x;
	c->max_y = size_y;
	
	c->offset_x = offset_x;
	c->offset_y = offset_y;
	
	c->drawing_enabled = drawing_enabled;
	c->default_background_color = background_color;
	c->default_foreground_color = foreground_color;
	
	c->data = malloc(c->max_x*c->max_y);
	if (!c->data) goto err;
	c->color = malloc(c->max_x*c->max_y*2);
	if (!c->color) goto err;
	
	c->input_buf = malloc(sizeof(queue));
	if (!c->input_buf) goto err;
	queue_init(c->input_buf);

	c->cursor_enabled = TRUE;
	c->cursor_blink_enabled = TRUE;
	c->cursor_blink_duration = 1;
	c->cursor_type = 4; // Defaults to "adaptive" cursor
	c->cursor_line_width = 1;
	
	for (unsigned int p = 0; p <= 5; p++)
		c->cursor_custom_data[p] = 0xFF;

	c->history_line = -1;

	if (!nio_scrbuf_init()) goto err;
	nio_clear(csl);

	return true;

err:
	nio_free(csl);
	return false;
}

int nio_fflush(nio_console* csl)
{
	nio_console_private *c = *csl;
	int row, col;
	for(row = 0; row < c->max_y; row++)
		for(col = 0; col < c->max_x; col++)
			nio_vram_csl_drawchar(csl,col,row);

	nio_vram_draw();
	return 0;
}

void nio_clear(nio_console* csl)
{
	nio_console_private *c = *csl;
	unsigned short color = (c->default_background_color << 8) | c->default_foreground_color;
	memset(c->data,0,c->max_x*c->max_y);
	int i;
	for(i = 0; i < c->max_x*c->max_y; i++)
	{
		c->color[i] = color;
	}
	c->cursor_x = 0;
	c->cursor_y = 0;
	if(c->drawing_enabled)
	{
		nio_vram_fill(c->offset_x, c->offset_y, c->max_x*NIO_CHAR_WIDTH, c->max_y*NIO_CHAR_HEIGHT, c->default_background_color);
		
		nio_vram_draw();
	}
}

void nio_scroll(nio_console* csl)
{
	nio_console_private *c = *csl;
	memmove(c->data,c->data+c->max_x,c->max_x*(c->max_y-1));
	memmove(c->color,c->color+c->max_x,c->max_x*(c->max_y-1)*2);
	memset(c->data+(c->max_x*(c->max_y-1)),0,c->max_x);
	memset(c->color+(c->max_x*(c->max_y-1)*2),0,c->max_x*2);
	if (c->drawing_enabled) {
		nio_vram_scroll(c->offset_x, c->offset_y, c->max_x*NIO_CHAR_WIDTH, c->max_y*NIO_CHAR_HEIGHT, NIO_CHAR_HEIGHT, c->default_background_color);
		nio_vram_draw();
	}
	
	if(c->cursor_y > 0)
		c->cursor_y--;
	c->cursor_x = 0;
}

void nio_csl_drawchar(nio_console* csl, const int pos_x, const int pos_y)
{
	nio_console_private *c = *csl;
	char ch = c->data[pos_y*c->max_x+pos_x];
	unsigned short color = c->color[pos_y*c->max_x+pos_x];
	
	char background_color = color >> 8;
	char foreground_color = color;
	
	nio_grid_putc(c->offset_x, c->offset_y, pos_x, pos_y, ch == 0 ? ' ' : ch, background_color, foreground_color);
}

void nio_vram_csl_drawchar(nio_console* csl, const int pos_x, const int pos_y)
{
	nio_console_private *c = *csl;
	char ch = c->data[pos_y*c->max_x+pos_x];
	unsigned short color = c->color[pos_y*c->max_x+pos_x];
	
	unsigned char background_color = color >> 8;
	unsigned char foreground_color = color;
	
	nio_vram_grid_putc(c->offset_x, c->offset_y, pos_x, pos_y, ch == 0 ? ' ' : ch, background_color, foreground_color);
}

void nio_csl_savechar(nio_console* csl, const char ch, const int pos_x, const int pos_y)
{
	nio_console_private *c = *csl;
	unsigned short color = (c->default_background_color << 8) | c->default_foreground_color;
	
	c->data[pos_y*c->max_x+pos_x] = ch;
	c->color[pos_y*c->max_x+pos_x] = color;
}

nio_console* nio_get_default(void)
{
	return nio_default;
}

int nio_getch(nio_console* csl)
{
	nio_console_private *c = *csl;
	char tmp = 0;
	while(tmp == 0)
	{
		while(!any_key_pressed())
		{
		        nio_cursor_blinking_draw(csl);
			if(c->idle_callback)
			{
				if(c->idle_callback(c->idle_callback_data) != 0)
					return 0;
			}
			else
			{
				idle();
			}
		}
		
		nio_cursor_erase(csl);
		int adaptive_cursor_state = 0;
		tmp = nio_ascii_get(&adaptive_cursor_state);
		
		if(c->cursor_type == 4)
			nio_cursor_custom(csl,&adaptive_cursor[adaptive_cursor_state][0]);
	}

	return tmp;
}

int nio__getch(void)
{
	return nio_getch(nio_default);
}

int nio_getche(nio_console* c)
{
	char tmp = nio_getch(c);
	nio_fputc(tmp,c);
	return tmp;
}

int nio__getche(void)
{
	return nio_getche(nio_default);
}

int nio_fputc(int character, nio_console* csl)
{
	nio_console_private *c = *csl;
	// Newline. Increment Y cursor, set X cursor to zero. Scroll if necessary.
	if(character == '\n')
	{
		c->cursor_x = 0;
		c->cursor_y++;
		// Scrolling necessary?
		if(c->cursor_y >= c->max_y)
		{
			nio_scroll(csl);
		} else if(c->drawing_enabled)
			nio_vram_draw();
	}
	// Carriage return. Set X cursor to zero.
	else if(character == '\r')
	{
		c->cursor_x = 0;
	}
	// Backspace. Decrement X cursor.
	else if(character == '\b')
	{
		if(c->cursor_x > 0)
			c->cursor_x--;
	}
	else if(character == '\t')
	{
		// tabs are 8 character long
		c->cursor_x += 8 - c->cursor_x % 8;
		character = ' ';
	}
	// Must be a normal character...
	else
	{
		// Store char.
		nio_csl_savechar(csl,character,c->cursor_x,c->cursor_y);
		
		// Draw it when BOOL draw is true
		if(c->drawing_enabled) {
			nio_csl_drawchar(csl,c->cursor_x,c->cursor_y);
		}
		
		// Increment X cursor. It will be checked for validity next time.
		c->cursor_x++;
	}
	
	// Check if cursor is valid
	if(c->cursor_x >= c->max_x)
	{
		c->cursor_x = 0;
		c->cursor_y++;
	}
	if(c->cursor_y >= c->max_y)
	{
		nio_scroll(csl);
	}
    return character;
}

int nio_putchar(int character)
{
    return nio_fputc(character,nio_default);
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
    va_list arglist;
    va_start(arglist,format);
    if(vsnprintf(buf,1000,format,arglist) < 0)
		exit_with_error(__FUNCTION__,"vsnprintf failed");
    nio_fputs(buf,c);
    va_end(arglist);
    return strlen(buf);
}

int nio_printf(const char *format, ...)
{
    char buf[1000];
    memset(buf,'\0',sizeof(buf));
    va_list arglist;
    va_start(arglist,format);
    if(vsnprintf(buf,1000,format,arglist) < 0)
		exit_with_error(__FUNCTION__,"vsnprintf failed");
    nio_puts(buf);
    va_end(arglist);
    return strlen(buf);
}

void nio_perror(const char* str)
{
    nio_printf("%s%s",str,strerror(errno));
}

void nio_color(nio_console* csl, const unsigned char background_color, const unsigned char foreground_color)
{
	nio_console_private *c = *csl;
	c->default_background_color = background_color;
	c->default_foreground_color = foreground_color;
}

void nio_drawing_enabled(nio_console* csl, const BOOL enable_drawing)
{
	nio_console_private *c = *csl;
	c->drawing_enabled = enable_drawing;
}

int nio_fgetc(nio_console* c)
{
	char tmp[2];
	nio_fgets(tmp,2,c);
	return tmp[0];
}

int nio_getchar(void)
{
    return nio_fgetc(nio_default);
}

char* nio_fgets(char* str, int num, nio_console* csl)
{
	nio_console_private *c = *csl;
	int old_x = c->cursor_x;
	int old_y = c->cursor_y;
	
	int str_pos = 0;
	for(; str_pos < num - 1 && !queue_empty(c->input_buf); str_pos++)
		str[str_pos] = queue_get(c->input_buf);
	
	if(str_pos >= num - 1)
	{
		str[str_pos] = 0;
		return str;
	}
	
	int i = 0, cursor;
	static char char_repeat = 0, tmp = 0;
	while(1)
	{
		nio_cursor_draw(csl);
		c->cursor_blink_status = TRUE;
		nio_cursor_blinking_reset(csl);

		do {
			nio_cursor_blinking_draw(csl);
			char_repeat = tmp;
			tmp = nio_ascii_get(&cursor);
			if (c->cursor_type == 4)
				nio_cursor_custom(csl, &adaptive_cursor[cursor][0]);
		} while(tmp == char_repeat || tmp == 0);
		char_repeat = tmp;
		nio_cursor_erase(csl);

		if(tmp == NIO_KEY_ESC)
		{
			nio_fputc('\n', csl);
			return NULL;
		}
		if(tmp == '\n')
		{
			nio_fputc('\n', csl);
			break;
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
				nio_fputs("\b \b", csl);
				queue_get_top(c->input_buf);
				i--;
			}
		}
		else if(tmp == NIO_KEY_UP || tmp == NIO_KEY_DOWN)
		{
			if(tmp == NIO_KEY_UP && (++c->history_line == HISTORY_LINES || c->history[c->history_line] == NULL))
				--c->history_line;
			else if(tmp == NIO_KEY_DOWN && (--c->history_line <= -1 || c->history[c->history_line] == NULL))
				++c->history_line;
			else if(c->history[c->history_line] != NULL)
			{
				while(i--)
				{
		                        if(c->cursor_x == 0 && c->cursor_y > old_y)
		                        {
		                                c->cursor_y--;
		                                c->cursor_x = c->max_x;
		                        }
		                        if(c->cursor_x > old_x || (c->cursor_x > 0 && c->cursor_y > old_y))
		                        {
		                                nio_fputs("\b \b", csl);
		                                queue_get_top(c->input_buf);
		                        }
				}
				++i;

				const char *line = c->history[c->history_line];
				while(*line && *line != '\n')
				{
					queue_put(c->input_buf, *line);
					nio_fputc(*line++, csl);
					++i;
				}
			}
		}
		else if(tmp == '\t')
		{
			const unsigned int tab_width = 4;
			unsigned int j;
			for(j = 0; j < tab_width; ++j)
			{
				queue_put(c->input_buf, ' ');
				nio_fputc(' ', csl);
			}
			i += tab_width;
		}
		else
		{
			queue_put(c->input_buf, tmp);
			nio_fputc(tmp, csl);
			i++;
		}
	}
	
	for(; str_pos < num - 1 && !queue_empty(c->input_buf); str_pos++)
		str[str_pos] = queue_get(c->input_buf);
	
	str[str_pos] = 0;

	free(c->history[HISTORY_LINES - 1]);	
	unsigned int j;
	for(j = HISTORY_LINES - 1; j > 0; --j)
		c->history[j] = c->history[j - 1];

	c->history[0] = strdup(str);
	c->history_line = -1;
	
	return str;
}

char* nio_gets(char* str)
{
    return nio_getsn(str,50);
}

char* nio_getsn(char* str, int num)
{
	nio_fgets(str,num,nio_default);
	str[strlen(str)] = '\0';
	return str;
}

void nio_free(nio_console* csl)
{
	if (*csl) {
		nio_console_private *c = *csl;
		nio_fflush(csl);
		free(c->data);
		free(c->color);
		free(c->input_buf);
		unsigned int i;
		for(i = 0; i < HISTORY_LINES; ++i)
			free(c->history[i]);

		free(c);
		*csl = NULL;
		--csl_count;
		if (!csl_count)
			nio_scrbuf_free();
	}
}
