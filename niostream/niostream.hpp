extern "C"
{
	#include <os.h>
	#include <nspireio.h>
}

#ifndef NIOSTREAM_HPP
#define NIOSTREAM_HPP

namespace nio
{

	class istream
	{
	public:
		
	private:
		nio_console* c;
	};

	class ostream
	{
	public:
		ostream(nio_console* c);
		~ostream();
		
		ostream& operator<<(const char* val);
		ostream& operator<<(const int val);
		
		nio::ostream& put(char c);
	private:
		nio_console* c;
	};

}

#endif