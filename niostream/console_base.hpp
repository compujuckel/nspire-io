extern "C"
{
	#include <os.h>
	#include <nspireio.h>
}

#ifndef CONSOLE_BASE_HPP
#define CONSOLE_BASE_HPP

namespace nio
{
	class console_base
	{
	public:
		void clear();
		void scroll();
		void csl_drawchar(const int pos_x, const int pos_y);
		void vram_csl_drawchar(const int pos_x, const int pos_y);
		void csl_savechar(const char ch, const int pos_x, const int pos_y);
		void color(const unsigned char background_color, const unsigned char foreground_color);
		void drawing_enabled(const bool enable_drawing);
		
		console_base(const int size_x, const int size_y, const int offset_x, const int offset_y, const unsigned char background_color, const unsigned char foreground_color, const bool drawing_enabled);
		~console_base();
		
		int flush();
		int putchar(int character);
		int puts(const char* str);
		int getchar();
		char* gets(char* str);
		//int printf(const char* format, ...);
		//void perror(const char* str);
		int _getch();
		int _getche();
		
		/*void cursor_draw();
		void cursor_erase();
		void cursor_blinking_draw();
		void cursor_blinking_reset();
		void cursor_enable(bool enable_cursor);
		void cursor_blinking_enable(bool enable_cursor_blink);
		void cursor_blinking_duration(int duration);
		void cursor_type(int cursor_type);
		void cursor_width(int cursor_width);
		void cursor_custom(unsigned char cursor_data[6]);*/
	private:
		nio_console* c;
	};
}

#endif