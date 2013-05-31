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
	typedef int streamsize;
	
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
			
			adjustfield	= internal | left | right,
			basefield	= dec | hex | oct,
			floatfield	= fixed | scientific
		};
		
		iostream(const int size_x, const int size_y, const int offset_x, const int offset_y, const unsigned char background_color, const unsigned char foreground_color, const bool drawing_enabled);
	
		iostream& operator<<(const char* val);
		iostream& operator<<(const int val);
		iostream& operator<<(const bool val);
		iostream& operator<<(iostream& (*pf)(iostream&));
		
		iostream& put(char c);
		iostream& write(const char* s, streamsize n);
		iostream& flush();
		
		fmtflags flags();
		fmtflags flags(fmtflags fmtfl);
		fmtflags setf(fmtflags fmtl);
		fmtflags setf(fmtflags fmtl, fmtflags mask);
		void unsetf(fmtflags mask);
		
		streamsize width() const;
		streamsize width(streamsize wide);
	private:
		fmtflags f;
		streamsize w;
	};
	
	iostream& endl(iostream& ios);
	iostream& ends(iostream& ios);
	iostream& flush(iostream& ios);
	
	iostream& boolalpha(iostream& ios);
	iostream& noboolalpha(iostream& ios);
	iostream& showbase(iostream& ios);
	iostream& noshowbase(iostream& ios);
	iostream& showpoint(iostream& ios);
	iostream& noshowpoint(iostream& ios);
	iostream& showpos(iostream& ios);
	iostream& noshowpos(iostream& ios);
	
	iostream& dec(iostream& ios);
	iostream& hex(iostream& ios);
	iostream& oct(iostream& ios);
	
	iostream& internal(iostream& ios);
	iostream& left(iostream& ios);
	iostream& right(iostream& ios);
}

#endif
