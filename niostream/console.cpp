#include "console.hpp"

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
	nio_fputc(ch,c);
}

void console::write(const char* s, streamsize n)
{
	int i;
	for(i = 0; i < n; i++)
		console::put(s[i]);
}

void console::flush()
{
	nio_fflush(c);
}