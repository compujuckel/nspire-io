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

#include <nspireio/console.hpp>

const int nio::MAX_ROWS = NIO_MAX_ROWS;
const int nio::MAX_COLS = NIO_MAX_COLS;

using namespace nio;

console::console(const int size_x, const int size_y, const int offset_x, const int offset_y, enum color background_color, enum color foreground_color, const bool drawing_enabled)
{
	c = new nio_console;
	BOOL drawing_enabled_b = drawing_enabled ? TRUE : FALSE;
	nio_init(c,size_x,size_y,offset_x,offset_y,background_color,foreground_color,drawing_enabled_b);
	
	f = (fmtflags)(dec | right | fixed | skipws | (drawing_enabled_b ? unitbuf : 0) );
	s = goodbit;
	w = 0;
	p = 5;
	count = 0;
}

console::~console()
{
	delete c;
}

void console::csl_clear()
{
	nio_clear(c);
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

void console::drawing_enabled(const bool enable_drawing)
{
	BOOL enable_drawing_b = enable_drawing ? TRUE : FALSE;
	nio_drawing_enabled(c,enable_drawing_b);
}

void console::put(char ch)
{
	nio_drawing_enabled(c,(f & unitbuf) ? TRUE : FALSE);
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

char console::get()
{
	char tmp = nio_fgetc(c);
	count = tmp != 0 ? 1 : 0;
	return tmp;
}

void console::get(char& ch)
{
	ch = nio_fgetc(c);
	count = ch != 0 ? 1 : 0;
}

void console::get(char* s, streamsize n)
{
	nio_fgets(s,n,c);
	count = strlen(s);
}

void console::getline(char* s, streamsize n)
{
	get(s,n);
}