#include "iostream.hpp"

nio::iostream::iostream(const int size_x, const int size_y, const int offset_x, const int offset_y, const unsigned char background_color, const unsigned char foreground_color, const bool drawing_enabled)
	: nio::console(size_x, size_y, offset_x, offset_y, background_color, foreground_color, drawing_enabled)
{
	f = (nio::iostream::fmtflags)(nio::iostream::dec | nio::iostream::right | nio::iostream::fixed | nio::iostream::skipws | nio::iostream::unitbuf);
	s = nio::iostream::goodbit;
	w = 0;
	p = 5;
}

nio::iostream& nio::iostream::operator<<(const char* val)
{
	nio::console::puts(val);
	return *this;
}

// Not working, either prints -0.00000 or crashes emu.
/*nio::iostream& nio::iostream::operator<<(const double val)
{
	char buf[50] = { '\0' };
	char fmtstring[20] = { '\0' };
	
	strcat(fmtstring,"%");
	
	// sprintf flags
	if(f & nio::iostream::left)
		strcat(fmtstring,"-");
	//if(f & nio::iostream::showpos)
	//	strcat(fmtstring,"+");
	
	// sprintf width
	if(w)
		strcat(fmtstring,"*");
	
	// sprintf precision
	if(p)
		strcat(fmtstring,".*");
	
	// sprintf specifiers
	if(f & nio::iostream::fixed)
		strcat(fmtstring,(f & nio::iostream::uppercase) ? "F" : "f");
	else if(f & nio::iostream::scientific)
		strcat(fmtstring,(f & nio::iostream::uppercase) ? "E" : "e");
	else
		strcat(fmtstring,(f & nio::iostream::uppercase) ? "F" : "f");
		
	if(w && !p)
		sprintf(buf,fmtstring,w,val);
	else if(!w && p)
		sprintf(buf,fmtstring,p,val);
	else if(w && p)
		sprintf(buf,fmtstring,w,p,val);
	else
		sprintf(buf,fmtstring,val);

	nio::console::puts(buf);
	return *this;
}*/

nio::iostream& nio::iostream::operator<<(const int val)
{
	char buf[50] = { '\0' };
	char fmtstring[20] = { '\0' };
	
	// Inserted before value
	if(f & nio::iostream::showbase && !(f & nio::iostream::dec))
	{
		if(f & nio::iostream::hex)
			strcat(fmtstring,"0x");
		else
			strcat(fmtstring,"0");
	}
	strcat(fmtstring,"%");
	
	// sprintf flags
	if(f & nio::iostream::left)
		strcat(fmtstring,"-");
	// the "+" / "#" flags are not supported by the Nspire's vsprintf :/
	//if(f & nio::iostream::showpos)
	//	strcat(fmtstring,"+");
	//if(f & nio::iostream::showbase)
	//	strcat(fmtstring,"#");
	
	// sprintf width
	if(w)
		strcat(fmtstring,"*");
	
	// sprintf specifier
	if(f & nio::iostream::dec)
		strcat(fmtstring,"d");
	else if(f & nio::iostream::hex)
		strcat(fmtstring,(f & nio::iostream::uppercase) ? "X" : "x");
	else if(f & nio::iostream::oct)
		strcat(fmtstring,"o");
	else
		strcat(fmtstring,"d");
	
	if(w)
		sprintf(buf,fmtstring,w,val);
	else
		sprintf(buf,fmtstring,val);
	
	nio::console::puts(buf);
	return *this;
}

nio::iostream& nio::iostream::operator<<(const bool val)
{
	if(f & nio::iostream::boolalpha)
	{
		if(val)
			nio::console::puts("true");
		else
			nio::console::puts("false");
	}
	else
	{
		if(val)
			nio::console::putchar('1');
		else
			nio::console::putchar('0');
	}
	return *this;
}

nio::iostream& nio::iostream::operator<<(nio::iostream& (*pf)(nio::iostream&))
{
	return pf(*this);
}

nio::iostream& nio::iostream::operator>>(nio::iostream& (*pf)(nio::iostream&))
{
	return pf(*this);
}

nio::iostream& nio::iostream::operator>>(char* val)
{
	nio::console::gets(val);
	return *this;
}

// Not working, crashes emu. Looks like sscanf has problems with doubles/floats.
/*nio::iostream& nio::iostream::operator>>(double& val)
{
	char buf[50] = { '\0' };
	char fmtstring[20] = { '\0' };
	
	nio::console::getsn(buf,50);
	if(buf[0] == 0)
	{
		clear(eofbit);
		return *this;
	}
	
	if(f & nio::iostream::skipws)
		strcat(fmtstring," ");
	
	strcat(fmtstring,"%lf");
	
	int ret = sscanf(buf,fmtstring,&val);
	if(ret == -1)
	{
		clear(eofbit);
		return *this;
	}
	else if(ret == 0)
	{
		clear(failbit);
		return *this;
	}
	
	return *this;
}*/

nio::iostream& nio::iostream::operator>>(int& val)
{
	char buf[50] = { '\0' };
	char fmtstring[20] = { '\0' };
	
	nio::console::getsn(buf,50);
	if(buf[0] == 0)
	{
		clear(eofbit);
		return *this;
	}
	
	if(f & nio::iostream::skipws)
		strcat(fmtstring," ");
	
	strcat(fmtstring,"%");
	
	// sscanf specifier
	if(f & nio::iostream::dec)
		strcat(fmtstring,"d");
	else if(f & nio::iostream::hex)
		strcat(fmtstring,"x");
	else if(f & nio::iostream::oct)
		strcat(fmtstring,"o");
	else
		strcat(fmtstring,"i");
	
	int ret = sscanf(buf,fmtstring,&val);
	if(ret == -1)
	{
		clear(eofbit);
		return *this;
	}
	else if(ret == 0)
	{
		clear(failbit);
		return *this;
	}
	
	return *this;
}

nio::iostream& nio::iostream::put(char c)
{
	nio::console::putchar(c);
	return *this;
}

nio::iostream& nio::iostream::write(const char* s, streamsize n)
{
	int i;
	for(i = 0; i < n; i++)
		nio::console::putchar(s[i]);
	return *this;
}

nio::iostream& nio::iostream::flush()
{
	nio::console::flush();
	return *this;
}

nio::iostream::fmtflags nio::iostream::flags()
{
	return f;
}

nio::iostream::fmtflags nio::iostream::flags(fmtflags fmtfl)
{
	fmtflags tmp = f;
	f = fmtfl;
	drawing_enabled(f & nio::iostream::unitbuf);
	return tmp;
}

nio::iostream::fmtflags nio::iostream::setf(fmtflags fmtfl)
{
	fmtflags tmp = f;
	f = (nio::iostream::fmtflags)(f | fmtfl);
	drawing_enabled(f & nio::iostream::unitbuf);
	return tmp;
}

nio::iostream::fmtflags nio::iostream::setf(fmtflags fmtfl, fmtflags mask)
{
	fmtflags tmp = f;
	f = (nio::iostream::fmtflags)( ( fmtfl & mask ) | ( f & ~mask ) );
	drawing_enabled(f & nio::iostream::unitbuf);
	return tmp;
}

void nio::iostream::unsetf(fmtflags mask)
{
	f = (nio::iostream::fmtflags)( f & ~mask );
	drawing_enabled(f & nio::iostream::unitbuf);
}

nio::iostream& nio::endl(nio::iostream& ios)
{
	ios.put('\n');
	return ios;
}

nio::iostream& nio::ends(nio::iostream& ios)
{
	ios.put('\0');
	return ios;
}

nio::iostream& nio::flush(nio::iostream& ios)
{
	ios.flush();
	return ios;
}

nio::iostream& nio::dec(nio::iostream& ios)
{
	ios.setf(nio::iostream::dec, nio::iostream::basefield);
	return ios;
}

nio::iostream& nio::hex(nio::iostream& ios)
{
	ios.setf(nio::iostream::hex, nio::iostream::basefield);
	return ios;
}

nio::iostream& nio::oct(nio::iostream& ios)
{
	ios.setf(nio::iostream::oct, nio::iostream::basefield);
	return ios;
}

nio::iostream& nio::boolalpha(nio::iostream& ios)
{
	ios.setf(nio::iostream::boolalpha);
	return ios;
}

nio::iostream& nio::noboolalpha(nio::iostream& ios)
{
	ios.unsetf(nio::iostream::boolalpha);
	return ios;
}

nio::iostream& nio::showbase(nio::iostream& ios)
{
	ios.setf(nio::iostream::showbase);
	return ios;
}

nio::iostream& nio::noshowbase(nio::iostream& ios)
{
	ios.unsetf(nio::iostream::showbase);
	return ios;
}

nio::iostream& nio::showpoint(nio::iostream& ios)
{
	ios.setf(nio::iostream::showpoint);
	return ios;
}

nio::iostream& nio::noshowpoint(nio::iostream& ios)
{
	ios.unsetf(nio::iostream::showpoint);
	return ios;
}

nio::iostream& nio::showpos(nio::iostream& ios)
{
	ios.setf(nio::iostream::showpos);
	return ios;
}

nio::iostream& nio::noshowpos(nio::iostream& ios)
{
	ios.unsetf(nio::iostream::showpos);
	return ios;
}

nio::iostream& nio::unitbuf(nio::iostream& ios)
{
	ios.setf(nio::iostream::unitbuf);
	return ios;
}

nio::iostream& nio::nounitbuf(nio::iostream& ios)
{
	ios.unsetf(nio::iostream::unitbuf);
	return ios;
}

nio::iostream& nio::skipws(nio::iostream& ios)
{
	ios.setf(nio::iostream::skipws);
	return ios;
}

nio::iostream& nio::noskipws(nio::iostream& ios)
{
	ios.unsetf(nio::iostream::skipws);
	return ios;
}

nio::iostream& nio::uppercase(nio::iostream& ios)
{
	ios.setf(nio::iostream::uppercase);
	return ios;
}

nio::iostream& nio::nouppercase(nio::iostream& ios)
{
	ios.unsetf(nio::iostream::uppercase);
	return ios;
}

nio::iostream& nio::internal(nio::iostream& ios)
{
	ios.setf(nio::iostream::internal, nio::iostream::adjustfield);
	return ios;
}

nio::iostream& nio::left(nio::iostream& ios)
{
	ios.setf(nio::iostream::left, nio::iostream::adjustfield);
	return ios;
}

nio::iostream& nio::right(nio::iostream& ios)
{
	ios.setf(nio::iostream::right, nio::iostream::adjustfield);
	return ios;
}

nio::iostream& nio::fixed(nio::iostream& ios)
{
	ios.setf(nio::iostream::fixed, nio::iostream::floatfield);
	return ios;
}

nio::iostream& nio::scientific(nio::iostream& ios)
{
	ios.setf(nio::iostream::scientific, nio::iostream::floatfield);
	return ios;
}

nio::streamsize nio::iostream::precision() const
{
	return p;
}

nio::streamsize nio::iostream::precision(streamsize prec)
{
	streamsize tmp = p;
	p = prec;
	return tmp;
}

nio::streamsize nio::iostream::width() const
{
	return w;
}

nio::streamsize nio::iostream::width(streamsize wide)
{
	streamsize tmp = w;
	w = wide;
	return tmp;
}

nio::iostream::iostate nio::iostream::rdstate() const
{
	return s;
}

void nio::iostream::setstate(nio::iostream::iostate state)
{
	s = (nio::iostream::iostate)(s | state);
}

void nio::iostream::clear(nio::iostream::iostate state)
{
	s = state;
}

bool nio::iostream::good() const
{
	return s == nio::iostream::goodbit;
}

bool nio::iostream::eof() const
{
	return s == nio::iostream::eofbit;
}

bool nio::iostream::fail() const
{
	return s == nio::iostream::failbit || s == nio::iostream::badbit;
}

bool nio::iostream::bad() const
{
	return s == nio::iostream::badbit;
}

bool nio::iostream::operator!() const
{
	return fail();
}