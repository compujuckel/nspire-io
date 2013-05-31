extern "C"
{
	#include <os.h>
}
#ifdef BUILDLIB
	#include "console.hpp"
#else
	#include <niostream/console.hpp>
#endif

#ifndef IOSTREAM_HPP
#define IOSTREAM_HPP

namespace nio
{
	class iostream : private console
	{
	public:
		enum fmtflags
		{
			boolalpha	= (1u <<  0),
			showbase	= (1u <<  1),
			showpoint	= (1u <<  2),
			showpos		= (1u <<  3),
			skipws		= (1u <<  4),
			unitbuf		= (1u <<  5),
			uppercase	= (1u <<  6),
			dec			= (1u <<  7),
			hex			= (1u <<  8),
			oct			= (1u <<  9),
			fixed		= (1u << 10),
			scientific	= (1u << 11),
			internal	= (1u << 12),
			left		= (1u << 13),
			right		= (1u << 14),
			
			adjustfield	= left | right | internal,
			basefield	= dec | hex | oct,
			floatfield	= fixed | scientific
		};
		
		iostream(const int size_x, const int size_y, const int offset_x, const int offset_y, const unsigned char background_color, const unsigned char foreground_color, const bool drawing_enabled);
	
		iostream& operator<<(const char* val);
		iostream& operator<<(const int val);
		iostream& operator<<(iostream& (*pf)(iostream&));
		
		iostream& put(char c);
		iostream& write(const char* s, int n);
		iostream& flush();
		
		fmtflags flags();
		fmtflags flags(fmtflags fmtfl);
		fmtflags setf(fmtflags fmtl);
		fmtflags setf(fmtflags fmtl, fmtflags mask);
		void unsetf(fmtflags mask);
	private:
		fmtflags f;
	};
	
	iostream& endl(iostream& s);
	iostream& ends(iostream& s);
	iostream& flush(iostream& s);
	iostream& dec(iostream& s);
	iostream& hex(iostream& s);
	iostream& oct(iostream& s);
}

#endif
