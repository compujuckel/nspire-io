extern "C"
{
	#include <os.h>
}

#ifndef NIO_BASE_HPP
#define NIO_BASE_HPP

namespace nio
{
	typedef int streamsize;
	
	class nio_base
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
		
		enum iostate
		{
			eofbit		= (1u << 0),
			failbit		= (1u << 1),
			badbit		= (1u << 2),
			goodbit		= (1u << 3)
		};
		
		nio_base();
		
		fmtflags flags();
		fmtflags flags(fmtflags fmtfl);
		fmtflags setf(fmtflags fmtl);
		fmtflags setf(fmtflags fmtl, fmtflags mask);
		void unsetf(fmtflags mask);
		
		streamsize precision() const;
		streamsize precision(streamsize prec);
		
		streamsize width() const;
		streamsize width(streamsize wide);
		
		iostate rdstate() const;
		void setstate(iostate state);
		void clear(iostate state);
		bool good() const;
		bool eof() const;
		bool fail() const;
		bool bad() const;
		bool operator!() const;
		
	protected:
		fmtflags f;
		iostate s;
		streamsize w;
		streamsize p;
	};
	
	nio_base& boolalpha(nio_base& ios);
	nio_base& noboolalpha(nio_base& ios);
	nio_base& showbase(nio_base& ios);
	nio_base& noshowbase(nio_base& ios);
	nio_base& showpoint(nio_base& ios);
	nio_base& noshowpoint(nio_base& ios);
	nio_base& showpos(nio_base& ios);
	nio_base& noshowpos(nio_base& ios);
	nio_base& unitbuf(nio_base& ios);
	nio_base& nounitbuf(nio_base& ios);
	nio_base& skipws(nio_base& ios);
	nio_base& noskipws(nio_base& ios);
	nio_base& uppercase(nio_base& ios);
	nio_base& nouppercase(nio_base& ios);
	
	nio_base& dec(nio_base& ios);
	nio_base& hex(nio_base& ios);
	nio_base& oct(nio_base& ios);
	
	nio_base& internal(nio_base& ios);
	nio_base& left(nio_base& ios);
	nio_base& right(nio_base& ios);
	
	nio_base& fixed(nio_base& ios);
	nio_base& scientific(nio_base& ios);
}

#endif