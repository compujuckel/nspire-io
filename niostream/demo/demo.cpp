#include <console.hpp>

int main(void)
{
	nio::console c;
	
	c.width(10);
	c << ":" << 123 << ":";
	
	
	wait_key_pressed();
	return 0;
}