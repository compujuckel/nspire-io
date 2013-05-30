#include <niostream/console_base.hpp>

int main(void)
{
	nio::console_base csl(nio::MAX_COLS,nio::MAX_ROWS,0,0,nio::COLOR_WHITE,nio::COLOR_BLACK,true);
	
	csl.puts("LOL");
	
	wait_key_pressed();
	return 0;
}