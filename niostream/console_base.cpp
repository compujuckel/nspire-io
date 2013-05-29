#include "console_base.hpp"

void nio::console_base::clear()
{
	nio_clear(c);
}

void nio::console_base::scroll()
{
	nio_scroll(c);
}

void nio::console_base::csl_drawchar(const int pos_x, const int pos_y)
{
	nio_csl_drawchar(c,pos_x,pos_y);
}

void nio::console_base::vram_csl_drawchar(const int pos_x, const int pos_y)
{
	nio_vram_csl_drawchar(c,pos_x,pos_y);
}

void nio::console_base::csl_savechar(const char ch, const int pos_x, const int pos_y)
{
	nio_csl_savechar(c,ch,pos_x,pos_y);
}

void nio::console_base::color(const unsigned char background_color, const unsigned char foreground_color)
{
	nio_color(c,background_color,foreground_color);
}

void nio::console_base::drawing_enabled(const bool enable_drawing)
{
	BOOL enable_drawing_b = enable_drawing ? TRUE : FALSE;
	nio_drawing_enabled(c,enable_drawing_b);
}

nio::console_base::console_base(const int size_x, const int size_y, const int offset_x, const int offset_y, const unsigned char background_color, const unsigned char foreground_color, const bool drawing_enabled)
{
	c = new nio_console;
	BOOL drawing_enabled_b = drawing_enabled ? TRUE : FALSE;
	nio_init(c,size_x,size_y,offset_x,offset_y,background_color,foreground_color,drawing_enabled_b);
}

nio::console_base::~console_base()
{
	delete c;
}

int nio::console_base::flush()
{
	return nio_fflush(c);
}

int nio::console_base::putchar(int character)
{
	return nio_fputc(character,c);
}

int nio::console_base::puts(const char* str)
{
	return nio_fputs(str,c);
}

int nio::console_base::getchar()
{
	return nio_fgetc(c);
}

char* nio::console_base::gets(char* str)
{
	return nio_fgets(str,1000,c);
}

int nio::console_base::_getch()
{
	return nio_getch(c);
}

int nio::console_base::_getche()
{
	return nio_getche(c);
}