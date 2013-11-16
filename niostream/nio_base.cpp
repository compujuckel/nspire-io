#include "nio_base.hpp"

nio::nio_base::nio_base()
{
	f = (nio::nio_base::fmtflags)(nio::nio_base::dec | nio::nio_base::right | nio::nio_base::fixed | nio::nio_base::skipws | nio::nio_base::unitbuf);
	s = nio::nio_base::goodbit;
	w = 0;
	p = 5;
}

nio::nio_base::fmtflags nio::nio_base::flags()
{
	return f;
}

nio::nio_base::fmtflags nio::nio_base::flags(fmtflags fmtfl)
{
	fmtflags tmp = f;
	f = fmtfl;
	return tmp;
}

nio::nio_base::fmtflags nio::nio_base::setf(fmtflags fmtfl)
{
	fmtflags tmp = f;
	f = (nio::nio_base::fmtflags)(f | fmtfl);
	return tmp;
}

nio::nio_base::fmtflags nio::nio_base::setf(fmtflags fmtfl, fmtflags mask)
{
	fmtflags tmp = f;
	f = (nio::nio_base::fmtflags)( ( fmtfl & mask ) | ( f & ~mask ) );
	return tmp;
}

void nio::nio_base::unsetf(fmtflags mask)
{
	f = (nio::nio_base::fmtflags)( f & ~mask );
}

nio::nio_base& nio::dec(nio::nio_base& ios)
{
	ios.setf(nio::nio_base::dec, nio::nio_base::basefield);
	return ios;
}

nio::nio_base& nio::hex(nio::nio_base& ios)
{
	ios.setf(nio::nio_base::hex, nio::nio_base::basefield);
	return ios;
}

nio::nio_base& nio::oct(nio::nio_base& ios)
{
	ios.setf(nio::nio_base::oct, nio::nio_base::basefield);
	return ios;
}

nio::nio_base& nio::boolalpha(nio::nio_base& ios)
{
	ios.setf(nio::nio_base::boolalpha);
	return ios;
}

nio::nio_base& nio::noboolalpha(nio::nio_base& ios)
{
	ios.unsetf(nio::nio_base::boolalpha);
	return ios;
}

nio::nio_base& nio::showbase(nio::nio_base& ios)
{
	ios.setf(nio::nio_base::showbase);
	return ios;
}

nio::nio_base& nio::noshowbase(nio::nio_base& ios)
{
	ios.unsetf(nio::nio_base::showbase);
	return ios;
}

nio::nio_base& nio::showpoint(nio::nio_base& ios)
{
	ios.setf(nio::nio_base::showpoint);
	return ios;
}

nio::nio_base& nio::noshowpoint(nio::nio_base& ios)
{
	ios.unsetf(nio::nio_base::showpoint);
	return ios;
}

nio::nio_base& nio::showpos(nio::nio_base& ios)
{
	ios.setf(nio::nio_base::showpos);
	return ios;
}

nio::nio_base& nio::noshowpos(nio::nio_base& ios)
{
	ios.unsetf(nio::nio_base::showpos);
	return ios;
}

nio::nio_base& nio::unitbuf(nio::nio_base& ios)
{
	ios.setf(nio::nio_base::unitbuf);
	return ios;
}

nio::nio_base& nio::nounitbuf(nio::nio_base& ios)
{
	ios.unsetf(nio::nio_base::unitbuf);
	return ios;
}

nio::nio_base& nio::skipws(nio::nio_base& ios)
{
	ios.setf(nio::nio_base::skipws);
	return ios;
}

nio::nio_base& nio::noskipws(nio::nio_base& ios)
{
	ios.unsetf(nio::nio_base::skipws);
	return ios;
}

nio::nio_base& nio::uppercase(nio::nio_base& ios)
{
	ios.setf(nio::nio_base::uppercase);
	return ios;
}

nio::nio_base& nio::nouppercase(nio::nio_base& ios)
{
	ios.unsetf(nio::nio_base::uppercase);
	return ios;
}

nio::nio_base& nio::internal(nio::nio_base& ios)
{
	ios.setf(nio::nio_base::internal, nio::nio_base::adjustfield);
	return ios;
}

nio::nio_base& nio::left(nio::nio_base& ios)
{
	ios.setf(nio::nio_base::left, nio::nio_base::adjustfield);
	return ios;
}

nio::nio_base& nio::right(nio::nio_base& ios)
{
	ios.setf(nio::nio_base::right, nio::nio_base::adjustfield);
	return ios;
}

nio::nio_base& nio::fixed(nio::nio_base& ios)
{
	ios.setf(nio::nio_base::fixed, nio::nio_base::floatfield);
	return ios;
}

nio::nio_base& nio::scientific(nio::nio_base& ios)
{
	ios.setf(nio::nio_base::scientific, nio::nio_base::floatfield);
	return ios;
}

nio::streamsize nio::nio_base::precision() const
{
	return p;
}

nio::streamsize nio::nio_base::precision(streamsize prec)
{
	streamsize tmp = p;
	p = prec;
	return tmp;
}

nio::streamsize nio::nio_base::width() const
{
	return w;
}

nio::streamsize nio::nio_base::width(streamsize wide)
{
	streamsize tmp = w;
	w = wide;
	return tmp;
}

nio::nio_base::iostate nio::nio_base::rdstate() const
{
	return s;
}

void nio::nio_base::setstate(nio::nio_base::iostate state)
{
	s = (nio::nio_base::iostate)(s | state);
}

void nio::nio_base::clear(nio::nio_base::iostate state)
{
	s = state;
}

bool nio::nio_base::good() const
{
	return s == nio::nio_base::goodbit;
}

bool nio::nio_base::eof() const
{
	return s == nio::nio_base::eofbit;
}

bool nio::nio_base::fail() const
{
	return s == nio::nio_base::failbit || s == nio::nio_base::badbit;
}

bool nio::nio_base::bad() const
{
	return s == nio::nio_base::badbit;
}

bool nio::nio_base::operator!() const
{
	return fail();
}