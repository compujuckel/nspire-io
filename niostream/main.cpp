#include "console_base.hpp"

int main(void)
{
	nio::console_base csl(NIO_MAX_COLS,NIO_MAX_ROWS,0,0,WHITE,BLACK,true);
	
	csl.puts("LOL");
	
	wait_key_pressed();
	return 0;
}