#include <niostream/iostream.hpp>

int main(void)
{
	nio::iostream csl(nio::MAX_COLS,nio::MAX_ROWS,0,0,nio::COLOR_WHITE,nio::COLOR_BLACK,true);
	
	csl << 123 << nio::endl;
	csl << nio::hex << 123 << nio::endl;
	csl << nio::oct << 123 << nio::endl;
	
	wait_key_pressed();
	return 0;
}