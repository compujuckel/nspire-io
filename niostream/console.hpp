extern "C"
{
	#include <os.h>
	#ifdef BUILDLIB
		#include <nspireio.h>
	#endif
}

#ifndef CONSOLE_HPP
#define CONSOLE_HPP

namespace nio
{
	enum
	{
		COLOR_BLACK,
		COLOR_RED,
		COLOR_GREEN,
		COLOR_YELLOW,
		COLOR_BLUE,
		COLOR_MAGENTA,
		COLOR_CYAN,
		COLOR_GRAY,
		COLOR_LIGHTBLACK,
		COLOR_LIGHTRED,
		COLOR_LIGHTGREEN,
		COLOR_LIGHTYELLOW,
		COLOR_LIGHTBLUE,
		COLOR_LIGHTMAGENTA,
		COLOR_LIGHTCYAN,
		COLOR_WHITE
	};
	
	enum
	{
		CURSOR_BLOCK,
		CURSOR_UNDERSCORE,
		CURSOR_VERTICAL,
		CURSOR_CUSTOM,
		CURSOR_ADAPTIVE
	};
	
	extern const int MAX_ROWS;
	extern const int MAX_COLS;
	
	class console
	{
	public:
		void clear();
		void scroll();
		void csl_drawchar(const int pos_x, const int pos_y);
		void vram_csl_drawchar(const int pos_x, const int pos_y);
		void csl_savechar(const char ch, const int pos_x, const int pos_y);
		void color(const unsigned char background_color, const unsigned char foreground_color);
		void drawing_enabled(const bool enable_drawing);
		
		console(const int size_x, const int size_y, const int offset_x, const int offset_y, const unsigned char background_color, const unsigned char foreground_color, const bool drawing_enabled);
		~console();
		
		int flush();
		int putchar(int character);
		int puts(const char* str);
		int getchar();
		char* gets(char* str);
		//int printf(const char* format, ...);
		//void perror(const char* str);
		int _getch();
		int _getche();
		
		void cursor_draw();
		void cursor_erase();
		void cursor_blinking_draw();
		void cursor_blinking_reset();
		void cursor_enable(bool enable_cursor);
		void cursor_blinking_enable(bool enable_cursor_blink);
		void cursor_blinking_duration(int duration);
		void cursor_type(int cursor_type);
		void cursor_width(int cursor_width);
		void cursor_custom(unsigned char cursor_data[6]);
	private:
		#ifdef BUILDLIB
			nio_console* c;
		#endif
	};
}

#endif