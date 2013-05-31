#include <niostream/iostream.hpp>

int main(void)
{
	nio::iostream csl(nio::MAX_COLS,nio::MAX_ROWS,0,0,nio::COLOR_WHITE,nio::COLOR_BLACK,true);
	
	csl << nio::showbase << 123 << nio::endl;
	csl << nio::uppercase << nio::hex << 123 << nio::endl;
	csl << nio::oct << 123 << nio::endl;
	csl << true << nio::endl;
	csl << nio::boolalpha << true << nio::endl;
	csl.width(10);
	csl << nio::noshowbase << 123 << "$" << nio::endl;
	csl << nio::left << 123 << "$" << nio::endl;
	
	wait_key_pressed();
	return 0;
}