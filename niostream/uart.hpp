extern "C" {
	#include <os.h>
	#ifdef BUILDLIB
		#include <nspireio.h>
	#endif
}

#include <ios_base.ipp>

#ifndef UART_HPP
#define UART_HPP

namespace nio
{
	class uart : public ios_base<uart>
	{
	public:
		uart();
		bool ready();
		
		virtual void put(char ch);
		virtual void write(const char* s, streamsize n);
		virtual void flush();
		
		virtual int gcount() const;
		virtual char get();
		virtual void get(char& c);
		virtual void get(char* s, streamsize n);
		virtual void getline(char* s, streamsize n);
	};
}

#endif
