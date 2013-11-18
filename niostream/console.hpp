extern "C" {
	#include <os.h>
	#ifdef BUILDLIB
		#include <nspireio.h>
	#endif
}

#include <ios_base.ipp>

#ifndef CONSOLE_HPP
#define CONSOLE_HPP

namespace nio
{
	enum color
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
	
	enum cursor
	{
		CURSOR_BLOCK,
		CURSOR_UNDERSCORE,
		CURSOR_VERTICAL,
		CURSOR_CUSTOM,
		CURSOR_ADAPTIVE
	};
	
	extern const int MAX_ROWS;
	extern const int MAX_COLS;
	
	class console : public ios_base<console>
	{
	public:
		console(const int size_x = MAX_COLS, const int size_y = MAX_ROWS, const int offset_x = 0, const int offset_y = 0, enum color background_color = COLOR_WHITE, enum color foreground_color = COLOR_BLACK, const bool drawing_enabled = true);
		~console();
		
		void csl_clear();
		void scroll();
		void csl_drawchar(const int pos_x, const int pos_y);
		void vram_csl_drawchar(const int pos_x, const int pos_y);
		void csl_savechar(const char ch, const int pos_x, const int pos_y);
		void color(enum color background_color, enum color foreground_color);
		void drawing_enabled(const bool enable_drawing);
		
		virtual void put(char ch);
		virtual void write(const char* s, streamsize n);
		virtual void flush();
	private:
		#ifdef BUILDLIB
		nio_console* c;
		#endif
	};
}

#endif