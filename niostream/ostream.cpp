#include "ostream.hpp"

nio::ostream::ostream(nio_console* c)
{
	this->c = c;
}

nio::ostream::~ostream()
{

}

nio::ostream& nio::ostream::operator<<(const char* val)
{
	nio_fputs(val,c);
	return *this;
}

nio::ostream& nio::ostream::operator<<(const int val)
{
	nio_fprintf(c,"%d",val);
	return *this;
}

nio::ostream& nio::ostream::put(char c)
{
	nio_fputc(c,this->c);
	return *this;
}

nio::ostream& nio::ostream::write(const char* s, int n)
{
	int i;
	for(i = 0; i < n; i++)
		nio_fputc(s[i],c);
	return *this;
}

nio::ostream& nio::ostream::flush()
{
	nio_fflush(c);
	return *this;
}