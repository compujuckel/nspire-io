#include "niostream.hpp"

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

int main(void)
{
	nio_console csl;
	nio_init(&csl,NIO_MAX_COLS,NIO_MAX_ROWS,0,0,WHITE,BLACK,TRUE);
	
	nio::ostream cout(&csl);
	cout << "Hello World!";
	cout << 123;
	cout.put('X');
	
	wait_key_pressed();
	return 0;
}