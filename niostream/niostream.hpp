extern "C"
{
	#include <os.h>
}

#ifdef BUILDLIB
	extern "C"
	{
		#include <nspireio.h>
	}
	#include "console_base.hpp"
#else
	#include <niostream/console_base.hpp>
#endif

#ifndef NIOSTREAM_HPP
#define NIOSTREAM_HPP

namespace nio
{
	class niostream : private console_base
	{
	public:
		niostream& operator<<(const char* val);
		niostream& operator<<(const int val);
		
		niostream& put(char c);
		niostream& write(const char* s, int n);
		
		niostream& flush();
	};
}

#endif