#include "console.hpp"

const int nio::MAX_ROWS = NIO_MAX_ROWS;
const int nio::MAX_COLS = NIO_MAX_COLS;

void nio::console::clear()
{
	nio_clear(c);
}

void nio::console::scroll()
{
	nio_scroll(c);
}

void nio::console::csl_drawchar(const int pos_x, const int pos_y)
{
	nio_csl_drawchar(c,pos_x,pos_y);
}

void nio::console::vram_csl_drawchar(const int pos_x, const int pos_y)
{
	nio_vram_csl_drawchar(c,pos_x,pos_y);
}

void nio::console::csl_savechar(const char ch, const int pos_x, const int pos_y)
{
	nio_csl_savechar(c,ch,pos_x,pos_y);
}

void nio::console::color(const unsigned char background_color, const unsigned char foreground_color)
{
	nio_color(c,background_color,foreground_color);
}

void nio::console::drawing_enabled(const bool enable_drawing)
{
	BOOL enable_drawing_b = enable_drawing ? TRUE : FALSE;
	nio_drawing_enabled(c,enable_drawing_b);
}

nio::console::console(const int size_x, const int size_y, const int offset_x, const int offset_y, const unsigned char background_color, const unsigned char foreground_color, const bool drawing_enabled)
{
	c = new nio_console;
	BOOL drawing_enabled_b = drawing_enabled ? TRUE : FALSE;
	nio_init(c,size_x,size_y,offset_x,offset_y,background_color,foreground_color,drawing_enabled_b);
}

nio::console::~console()
{
	delete c;
}

int nio::console::flush()
{
	return nio_fflush(c);
}

int nio::console::putchar(int character)
{
	return nio_fputc(character,c);
}

int nio::console::puts(const char* str)
{
	return nio_fputs(str,c);
}

int nio::console::getchar()
{
	return nio_fgetc(c);
}

char* nio::console::gets(char* str)
{
	return nio_fgets(str,1000,c);
}

int nio::console::_getch()
{
	return nio_getch(c);
}

int nio::console::_getche()
{
	return nio_getche(c);
}

void nio::console::cursor_draw()
{
	nio_cursor_draw(c);
}

void nio::console::cursor_erase()
{
	nio_cursor_erase(c);
}

void nio::console::cursor_blinking_draw()
{
	nio_cursor_blinking_draw(c);
}

void nio::console::cursor_blinking_reset()
{
	nio_cursor_blinking_reset(c);
}

void nio::console::cursor_enable(bool enable_cursor)
{
	BOOL enable_cursor_b = enable_cursor ? TRUE : FALSE;
	nio_cursor_enable(c,enable_cursor_b);
}

void nio::console::cursor_blinking_enable(bool enable_cursor_blink)
{
	BOOL enable_cursor_blink_b = enable_cursor_blink ? TRUE : FALSE;
	nio_cursor_blinking_enable(c,enable_cursor_blink_b);
}

void nio::console::cursor_blinking_duration(int duration)
{
	nio_cursor_blinking_duration(c,duration);
}

void nio::console::cursor_type(int cursor_type)
{
	nio_cursor_type(c,cursor_type);
}

void nio::console::cursor_width(int cursor_width)
{
	nio_cursor_width(c,cursor_width);
}

void nio::console::cursor_custom(unsigned char cursor_data[6])
{
	nio_cursor_custom(c,cursor_data);
}