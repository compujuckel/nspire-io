extern "C" {
	#include <os.h>
}

#ifndef IOS_BASE_HPP
#define IOS_BASE_HPP

namespace nio
{
	typedef int streamsize;
	
	template<class T>
	class ios_base
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
			basefield 	= dec | oct | hex,
			floatfield	= scientific | fixed
		};
		
		enum iostate
		{
			eofbit		= (1u <<  0),
			failbit		= (1u <<  1),
			badbit		= (1u <<  2),
			goodbit		= (1u <<  3)
		};
		
		fmtflags flags() const;
		fmtflags flags(fmtflags fmtfl);
		
		fmtflags setf(fmtflags fmtl);
		fmtflags setf(fmtflags fmtl, fmtflags mask);
		
		void unsetf(fmtflags mask);
		
		streamsize precision() const;
		streamsize precision(streamsize prec);
		
		streamsize width() const;
		streamsize width(streamsize wide);
		
		bool good() const;
		bool eof() const;
		bool fail() const;
		bool bad() const;
		bool operator!() const;
		
		iostate rdstate() const;
		void setstate(iostate state);
		void clear(iostate state = goodbit);
		
		virtual void put(char ch) = 0;
		virtual void write(const char* s, streamsize n) = 0;
		virtual void flush() = 0;
		
		T& operator<<(const char* val);
		T& operator<<(const int val);
		
	protected:
		iostate s;
		fmtflags f;
		streamsize p;
		streamsize w;
	};
}

#endif