/**
 * @file nspireio2.h
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
 * Nspire I/O 2.0 header file
 */
#include <os.h>

#ifndef NSPIREIO2_H
#define NSPIREIO2_H

#define nio_getc nio_fgetc
#define nio_putc nio_fputc

/** Console structure. */
struct nio_console
{
	char* data; /**< Data pointer */
	char* color; /**< Color pointer */
	int cursor_x; /**< Current X position */
	int cursor_y; /**< Current Y position */
	int max_x; /**< Column count */
	int max_y; /**< Row count */
	int offset_x; /**< X pixel offset */
	int offset_y; /**< Y pixel offset */
	char default_background_color; /**< Color that will be used as default background */
	char default_foreground_color; /**< Color that will be used as default foreground */
	BOOL drawing_enabled; /**< Automatically draw any new text to the screen */
};
typedef struct nio_console nio_console;

// Own functions
void nio_grid_puts(const int offset_x, const int offset_y, const int x, const int y, const char *str, const char bgColor, const char textColor);
void nio_grid_putc(const int offset_x, const int offset_y, const int x, const int y, const char ch, const char bgColor, const char textColor);
void nio_load(const char* path, nio_console* c);
void nio_save(const char* path, const nio_console* c);
void nio_set_default(nio_console* c);
void nio_clear(nio_console* c);
void nio_scroll(nio_console* c);
void nio_csl_drawchar(nio_console* c, const int pos_x, const int pos_y);
void nio_csl_savechar(nio_console* c, const char ch, const int pos_x, const int pos_y);
char nio_getch(void);
void nio_color(nio_console* c, const char background_color, const char foreground_color);
void nio_drawing_enabled(nio_console* c, const BOOL enable_drawing);
void nio_init(nio_console* c, const int size_x, const int size_y, const int offset_x, const int offset_y, const char background_color, const char foreground_color);
void nio_free(nio_console* c);
void nio_use_stdio(void);
void nio_free_stdio(void);

// stdio.h
int nio_fflush(nio_console* c);
char nio_fputc(char ch, nio_console* c);
char nio_putchar(const char ch);
int nio_fputs(const char* str, nio_console* c);
int nio_puts(const char* str);
char nio_fgetc(nio_console* c);
char nio_getchar(void);
char* nio_fgets(char* str, int num, nio_console* c);
char* nio_gets(char* str);
//int nio_vfprintf(nio_console* c, const char* format, va_list* arglist);
int nio_fprintf(nio_console* c, const char* format, ...);
int nio_printf(const char* format, ...);

// Add #define NIO_KEEP_COMPATIBILITY in your code to make Nspire I/O backwards compatible to 2.0
#ifdef NIO_KEEP_COMPATIBILITY
#define nio_InitConsole             nio_init
#define nio_DrawConsole             nio_fflush
#define nio_Clear                   nio_clear
#define nio_PrintChar(a,b)          nio_fputc(b,a)
#define nio_EnableDrawing           nio_drawing_enabled
#define nio_PrintStr(a,b)           nio_fputs(b,a)
#define nio_GetChar                 nio_fgetc
#define nio_GetStr(a,b)             nio_fgets(b,1000,a)
#define nio_SetColor                nio_color
#define nio_CleanUp                 nio_free
#define setPixel                    nio_pixel_set
#define putChar                     nio_pixel_putc
#define putStr                      nio_pixel_puts
#define nio_drawstr                 nio_grid_puts
#define nio_drawch                  nio_grid_putc
#define nio_ScrollDown              nio_scroll
#define nio_DrawChar                nio_csl_drawchar
#define nio_SetChar                 nio_csl_savechar
#define nio_printf                  nio_fprintf
#endif

#ifdef NIO_REPLACE_STDIO
#define putchar                     nio_putchar
#define puts                        nio_puts
#define getchar                     nio_getchar
#define gets                        nio_gets
#define printf                      nio_printf
#endif

#endif