#include "niostream.hpp"

nio::niostream& nio::niostream::operator<<(const char* val)
{
	nio::console_base::puts(val);
	return *this;
}

/*nio::ostream& nio::ostream::operator<<(const int val)
{
	nio_fprintf(c,"%d",val);
	return *this;
}*/

nio::niostream& nio::niostream::put(char c)
{
	nio::console_base::putchar(c);
	return *this;
}

nio::niostream& nio::niostream::write(const char* s, int n)
{
	int i;
	for(i = 0; i < n; i++)
		nio::console_base::putchar(s[i]);
	return *this;
}

nio::niostream& nio::niostream::flush()
{
	nio::console_base::flush();
	return *this;
}