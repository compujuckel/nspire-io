extern "C"
{
	#include <os.h>
}
#ifdef BUILDLIB
	#include "console.hpp"
	#include "nio_base.hpp"
#else
	#include <niostream/console.hpp>
	#include <niostream/nio_base.hpp>
#endif

#ifndef IOSTREAM_HPP
#define IOSTREAM_HPP

namespace nio
{
	class iostream : private console, public nio_base
	{
	public:	
		iostream(const int size_x, const int size_y, const int offset_x, const int offset_y, const unsigned char background_color, const unsigned char foreground_color, const bool drawing_enabled);
	
		iostream& operator<<(const char* val);
		iostream& operator<<(const double val);
		iostream& operator<<(const int val);
		iostream& operator<<(const bool val);
		iostream& operator<<(iostream& (*pf)(iostream&));
		iostream& operator<<(nio_base& (*pf)(nio_base&));
		
		iostream& put(char c);
		iostream& write(const char* s, streamsize n);
		iostream& flush();
		
		iostream& operator>>(char* val);
		//iostream& operator>>(double& val);
		iostream& operator>>(int& val);
		iostream& operator>>(bool& val);
		iostream& operator>>(iostream& (*pf)(iostream&));
		iostream& operator>>(nio_base& (*pf)(nio_base&));
	};
	
	iostream& endl(iostream& ios);
	iostream& ends(iostream& ios);
	iostream& flush(iostream& ios);
}

#endif
