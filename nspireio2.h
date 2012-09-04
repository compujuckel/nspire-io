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


/** Draws a string to the screen on the given position.
	@param offset_x x offset in px
	@param offset_y y offset in px
	@param x x position in columns (px*6)
	@param y y position in rows (px*8)
	@param str String
	@param bgColor Background color
	@param textColor text color
*/
void nio_grid_puts(const int offset_x, const int offset_y, const int x, const int y, const char *str, const char bgColor, const char textColor);

/** Draws a char to the screen on the given position.
	@param offset_x x offset in px
	@param offset_y y offset in px
	@param x x position in columns (px*6)
	@param y y position in rows (px*8)
	@param c Char
	@param bgColor Background color
	@param textColor text color
*/
void nio_grid_putc(const int offset_x, const int offset_y, const int x, const int y, const char ch, const char bgColor, const char textColor);

/** Loads a console from a file on flash storage.
    @param path File path
	@param c Console
*/
void nio_load(const char* path, nio_console* c);

/** Saves a console to a file in flash storage.
	@param path File path
	@param c Console
*/
void nio_save(const char* path, const nio_console* c);

/** Sets a default console that will be used for all functions without console argument, e.g. nio_puts()
	@param c Console
*/
void nio_set_default(nio_console* c);

/** Clears a console.
	@param c Console
*/
void nio_clear(nio_console* c);

/** Scrolls a console one line down.
	@param c Console
*/
void nio_scroll(nio_console* c);

/** Draws a char from the console to the screen. For internal use.
	@param c Console
	@param pos_x x position
	@param pos_y y position
*/
void nio_csl_drawchar(nio_console* c, const int pos_x, const int pos_y);

/** Saves a char in a console without drawing it. For internal use.
	@param c Console
	@param ch Char
	@param pos_x x position
	@param pos_y y position
*/
void nio_csl_savechar(nio_console* c, const char ch, const int pos_x, const int pos_y);

/** Immediately gets a char from the keyboard.
	@return Char
*/
char nio_getch(void);

/** Sets the background- and text color of a console. Possible values are 0-15.
	@param c Console
	@param background_color Background color
	@param foreground_color Text color
*/
void nio_color(nio_console* c, const char background_color, const char foreground_color);

/** Changes the drawing behavior of a console.
	@param c Console
	@param enable_drawing If this is true, a console will automatically be updated if text is written to it.
*/
void nio_drawing_enabled(nio_console* c, const BOOL enable_drawing);

/** Initializes a console.
	@param c Console
	@param size_x console width
	@param size_y console height
	@param offset_x x position
	@param offset_y y position
	@param background_color Background color
	@param foreground_color Text color
    @param drawing_enabled See nio_enable_drawing()
*/
void nio_init(nio_console* c, const int size_x, const int size_y, const int offset_x, const int offset_y, const char background_color, const char foreground_color, const BOOL drawing_enabled);

/** Uninitializes a console. This should always be called before the program ends.
	@param c Console
*/
void nio_free(nio_console* c);

/** For use with NIO_REPLACE_STDIO. Use at the beginning of your program.
*/
void nio_use_stdio(void);

/** For use with NIO_REPLACE_STDIO. Use at the end of your program.
*/
void nio_free_stdio(void);

/** See [fflush](http://www.cplusplus.com/reference/clibrary/cstdio/fflush/)
	\note This is useful for consoles with enable_drawing set to false. Using this function will result in the console being drawn.
*/
int nio_fflush(nio_console* c);

/** See [fputc](http://www.cplusplus.com/reference/clibrary/cstdio/fputc/)
*/
char nio_fputc(char ch, nio_console* c);

/** See [putchar](http://www.cplusplus.com/reference/clibrary/cstdio/putchar/)
*/
char nio_putchar(const char ch);

/** See [fputs](http://www.cplusplus.com/reference/clibrary/cstdio/fputs/)
*/
int nio_fputs(const char* str, nio_console* c);

/** See [puts](http://www.cplusplus.com/reference/clibrary/cstdio/puts/)
*/
int nio_puts(const char* str);

/** See [fgetc](http://www.cplusplus.com/reference/clibrary/cstdio/fgetc)
*/
char nio_fgetc(nio_console* c);

/** See [getchar](http://www.cplusplus.com/reference/clibrary/cstdio/getchar)
*/
char nio_getchar(void);

/** See [fgets](http://www.cplusplus.com/reference/clibrary/cstdio/fgets/)
    \todo Do not ignore num
*/
char* nio_fgets(char* str, int num, nio_console* c);

/** See [gets](http://www.cplusplus.com/reference/clibrary/cstdio/gets/)
*/
char* nio_gets(char* str);

//int nio_vfprintf(nio_console* c, const char* format, va_list* arglist);

/** See [fprintf](http://www.cplusplus.com/reference/clibrary/cstdio/fprintf/)
*/
int nio_fprintf(nio_console* c, const char* format, ...);

/** See [printf](http://www.cplusplus.com/reference/clibrary/cstdio/printf/)
*/
int nio_printf(const char* format, ...);

/** See [perror](http://www.cplusplus.com/reference/clibrary/cstdio/perror/)
*/
void nio_perror(const char* str);

// Macro of nio_fgetc
#define nio_getc nio_fgetc

// Macro of nio_fputc
#define nio_putc nio_fputc

/** Stores binary data in a file.
	@param dataptr Pointer to the data to be stored
	@param size Length in bytes
	@param regpath Path to file
	@return 0 on success, -1 on failure
*/
int reg_store(void* dataptr, size_t size, char* regpath);

/** Reads binary data from a file.
	@param regpath Path to file
	@return Pointer to the data, NULL on failure
*/
void* reg_get(char* regpath);

/** Checks if there is data available at the serial port.
	@return TRUE if new data is available.
*/
BOOL uart_ready(void);

/** See [getchar](http://www.cplusplus.com/reference/clibrary/cstdio/getchar/)
	@return Char
*/
char uart_getchar(void);

/** See [gets](http://www.cplusplus.com/reference/clibrary/cstdio/gets/)
	@return Destination
*/
char* uart_gets(char* str);

/** See [putchar](http://www.cplusplus.com/reference/clibrary/cstdio/putchar/)
	@param c Char
*/
char uart_putchar(char character);

/** See [puts](http://www.cplusplus.com/reference/clibrary/cstdio/puts/)
    \note This DOES NOT append a newline (\\n) character.
	@param str String
*/
int uart_puts(const char *str);

/** See [printf](http://www.cplusplus.com/reference/clibrary/cstdio/printf/)
*/
void uart_printf(char *format, ...);

#define NIO_MAX_ROWS 30
#define NIO_MAX_COLS 53

#ifdef NIO_KEEP_COMPATIBILITY
#define nio_InitConsole(a,b,c,d,e,f,g)  nio_init(a,b,c,d,e,f,g,TRUE)
#define nio_DrawConsole                 nio_fflush
#define nio_Clear                       nio_clear
#define nio_PrintChar(a,b)              nio_fputc(b,a)
#define nio_EnableDrawing               nio_drawing_enabled
#define nio_PrintStr(a,b)               nio_fputs(b,a)
#define nio_GetChar                     nio_fgetc
#define nio_GetStr(a,b)                 nio_fgets(b,1000,a)
#define nio_SetColor                    nio_color
#define nio_CleanUp                     nio_free
#define setPixel                        nio_pixel_set
#define putChar                         nio_pixel_putc
#define putStr                          nio_pixel_puts
#define nio_drawstr                     nio_grid_puts
#define nio_drawch                      nio_grid_putc
#define nio_ScrollDown                  nio_scroll
#define nio_DrawChar                    nio_csl_drawchar
#define nio_SetChar                     nio_csl_savechar
#define nio_printf                      nio_fprintf

#define uart_putc                       uart_putchar
#define uart_getc                       uart_getchar
#endif

#ifdef NIO_REPLACE_STDIO
#define putchar                         nio_putchar
#define puts                            nio_puts
#define getchar                         nio_getchar
#define gets                            nio_gets
#define printf                          nio_printf
#define perror                          nio_perror
#endif

#ifdef UART_REPLACE_STDIO
#define putchar                         uart_putchar
#define puts                            uart_puts
#define getchar                         uart_getchar
#define gets                            uart_gets
#define printf                          uart_printf
#endif

#endif