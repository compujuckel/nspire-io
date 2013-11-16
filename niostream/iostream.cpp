#include "iostream.hpp"

nio::iostream::iostream(const int size_x, const int size_y, const int offset_x, const int offset_y, const unsigned char background_color, const unsigned char foreground_color, const bool drawing_enabled)
	: nio::console(size_x, size_y, offset_x, offset_y, background_color, foreground_color, drawing_enabled)
	, nio::nio_base()
{

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

nio::iostream& nio::iostream::operator<<(nio::nio_base& (*pf)(nio::nio_base&))
{
	pf(*this);
	return *this;
}

nio::iostream& nio::iostream::operator>>(nio::iostream& (*pf)(nio::iostream&))
{
	return pf(*this);
}

nio::iostream& nio::iostream::operator>>(nio::nio_base& (*pf)(nio::nio_base&))
{
	pf(*this);
	return *this;
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
		nio_base::clear(eofbit);
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
		nio_base::clear(eofbit);
		return *this;
	}
	else if(ret == 0)
	{
		nio_base::clear(failbit);
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
