#include <console.hpp>

int main(void)
{
	nio::console c;
	
	c << "hello" << nio::endl << 123;
	
	wait_key_pressed();
	return 0;
}