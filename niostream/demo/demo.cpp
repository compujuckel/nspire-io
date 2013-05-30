#include <niostream/niostream.hpp>

int main(void)
{
	nio::niostream csl(nio::MAX_COLS,nio::MAX_ROWS,0,0,nio::COLOR_WHITE,nio::COLOR_BLACK,true);
	
	csl << "LOL";
	
	wait_key_pressed();
	return 0;
}