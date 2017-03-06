/**
 * @file console.cpp
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
 * C++ console wrapper
 */

#include "../../include/nspireio/console.hpp"

const int nio::MAX_ROWS = NIO_MAX_ROWS;
const int nio::MAX_COLS = NIO_MAX_COLS;

using namespace nio;

console::console(const int size_x, const int size_y, const int offset_x, const int offset_y, enum color background_color, enum color foreground_color, const bool drawing_enabled)
{
	c = new nio_console;
	bool drawing_enabled_b = drawing_enabled ? true : false;
	nio_init(c,size_x,size_y,offset_x,offset_y,background_color,foreground_color,drawing_enabled_b);
	
	f = (fmtflags)(dec | right | fixed | skipws | (drawing_enabled_b ? unitbuf : 0) );
	s = goodbit;
	w = 0;
	p = 5;
	count = 0;
}

console::console(const char* path)
{
	nio_load(path,c);
	
	f = (fmtflags)(dec | right | fixed | skipws | ((*c)->drawing_enabled == true ? unitbuf : 0) );
	s = goodbit;
	w = 0;
	p = 5;
	count = 0;
}

console::~console()
{
	delete c;
}

void console::cls()
{
	nio_clear(c);
}

void console::save(const char* path)
{
	nio_save(path,c);
}

void console::scroll()
{
	nio_scroll(c);
}

void console::csl_drawchar(const int pos_x, const int pos_y)
{
	nio_csl_drawchar(c,pos_x,pos_y);
}

void console::vram_csl_drawchar(const int pos_x, const int pos_y)
{
	nio_vram_csl_drawchar(c,pos_x,pos_y);
}

void console::csl_savechar(const char ch, const int pos_x, const int pos_y)
{
	nio_csl_savechar(c,ch,pos_x,pos_y);
}

void console::color(enum color background_color, enum color foreground_color)
{
	nio_color(c,background_color,foreground_color);
}

color console::foreground_color() const
{
	return (enum color)(*c)->default_foreground_color;
}

void console::foreground_color(enum color clr)
{
	(*c)->default_foreground_color = clr;
}

enum color console::background_color() const
{
	return (enum color)(*c)->default_background_color;
}

void console::background_color(enum color clr)
{
	(*c)->default_background_color = clr;
}

void console::drawing_enable(const bool enable_drawing)
{
	bool enable_drawing_b = enable_drawing ? true : false;
	nio_drawing_enabled(c,enable_drawing_b);
}

void console::cursor_enable(const bool enable_cursor)
{
	bool enable_cursor_b = enable_cursor ? true : false;
	nio_cursor_enable(c,enable_cursor_b);
}

void console::cursor_type(enum cursor crsr)
{
	nio_cursor_type(c,crsr);
}

void console::cursor_width(int width)
{
	nio_cursor_width(c,width);
}

void console::cursor_custom(unsigned char cursor_data[6])
{
	nio_cursor_custom(c,cursor_data);
}

void console::put(char ch)
{
	nio_drawing_enabled(c,(f & unitbuf) ? true : false);
	nio_fputc(ch,c);
}

void console::write(const char* s, streamsize n)
{
	int i;
	for(i = 0; i < n; i++)
		put(s[i]);
}

void console::flush()
{
	nio_fflush(c);
}

streamsize console::gcount() const
{
	return count;
}

int console::get()
{
	int tmp = nio_fgetc(c);
	count = tmp != 0 ? 1 : 0;
	return tmp;
}

void console::get(int& ch)
{
	ch = nio_fgetc(c);
	count = ch != 0 ? 1 : 0;
}

void console::get(char* s, streamsize n)
{
	size_t len = 0;
	if (nio_fgets(s,n,c))
	{
		len = strlen(s);
		if (len && s[--len] == '\n')
			s[len] = '\0';
	}
	count = len;
}

void console::getline(char* s, streamsize n)
{
	get(s,n);
}
