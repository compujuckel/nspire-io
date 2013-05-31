#include "iostream.hpp"

nio::iostream::iostream(const int size_x, const int size_y, const int offset_x, const int offset_y, const unsigned char background_color, const unsigned char foreground_color, const bool drawing_enabled)
	: nio::console(size_x, size_y, offset_x, offset_y, background_color, foreground_color, drawing_enabled)
{
	f = (nio::iostream::fmtflags)(nio::iostream::dec | nio::iostream::left | nio::iostream::fixed);
}

nio::iostream& nio::iostream::operator<<(const char* val)
{
	nio::console::puts(val);
	return *this;
}

nio::iostream& nio::iostream::operator<<(const int val)
{
	char buf[20] = { '\0' };
	char fmtstring[20] = { '\0' };
	
	// Inserted before value
	if(f & nio::iostream::showbase)
	{
		strcat(fmtstring,"0");
		if(f & nio::iostream::dec)
			strcat(fmtstring,"d");
		else if(f & nio::iostream::hex)
			strcat(fmtstring,"x");
		else if(f & nio::iostream::oct)
			strcat(fmtstring,"o");
		else
			strcat(fmtstring,"d");
	}
	strcat(fmtstring,"%");
	
	// sprintf flags
	if(f & nio::iostream::showpos)
		strcat(fmtstring,"+");
	
	// sprintf specifier
	if(f & nio::iostream::dec)
		strcat(fmtstring,"d");
	else if(f & nio::iostream::hex)
		strcat(fmtstring,"x");
	else if(f & nio::iostream::oct)
		strcat(fmtstring,"o");
	else
		strcat(fmtstring,"d");
	
	sprintf(buf,fmtstring,val);
	nio::console::puts(buf);
	return *this;
}

nio::iostream& nio::iostream::operator<<(nio::iostream& (*pf)(nio::iostream&))
{
	return pf(*this);
}

nio::iostream& nio::iostream::put(char c)
{
	nio::console::putchar(c);
	return *this;
}

nio::iostream& nio::iostream::write(const char* s, int n)
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
	return tmp;
}

nio::iostream::fmtflags nio::iostream::setf(fmtflags fmtfl)
{
	fmtflags tmp = f;
	f = (nio::iostream::fmtflags)(f | fmtfl);
	return tmp;
}

nio::iostream::fmtflags nio::iostream::setf(fmtflags fmtfl, fmtflags mask)
{
	fmtflags tmp = f;
	f = (nio::iostream::fmtflags)( ( fmtfl & mask ) | ( f & ~mask ) );
	return tmp;
}

void nio::iostream::unsetf(fmtflags mask)
{
	f = (nio::iostream::fmtflags)( f & ~mask );
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