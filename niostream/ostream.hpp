extern "C"
{
	#include <os.h>
	#include <nspireio.h>
}

#ifndef OSTREAM_HPP
#define OSTREAM_HPP

namespace nio
{
	class ostream
	{
	public:
		ostream(nio_console* c);
		~ostream();
		
		ostream& operator<<(const char* val);
		ostream& operator<<(const int val);
		
		nio::ostream& put(char c);
		nio::ostream& write(const char* s, int n);
		
		nio::ostream& flush();
	private:
		nio_console* c;
	};
}

#endif