#include <niostream/iostream.hpp>

int main(void)
{
	clrscr();	
	nio::iostream csl(nio::MAX_COLS,nio::MAX_ROWS,0,0,nio::COLOR_WHITE,nio::COLOR_BLACK,true);
	
	csl << "niostream tests (built " << __DATE__ << " " << __TIME__ << ")" << nio::endl;
	
	csl << "boolean (noboolalpha): " << nio::noboolalpha << true << "," << false << nio::endl;
	csl << "boolean (boolalpha): " << nio::boolalpha << true << "," << false << nio::endl;
	
	csl << "int (noshowbase/dec): " << nio::noshowbase << 123 << nio::endl;
	csl << "int (showbase/dec): " << nio::showbase << 123 << nio::endl;
	csl << "int (showbase/hex): " << nio::hex << 123 << nio::endl;
	csl << "int (showbase/uppercase/hex): " << nio::uppercase << 123 << nio::nouppercase << nio::endl;
	csl << "int (showbase/oct): " << nio::oct << 123 << nio::endl;
	
	//csl.unsetf(nio::iostream::showbase);
	//csl.setf(nio::iostream::dec, nio::iostream::basefield);
	
	csl.width(10);
	csl << "width: " << 123 << "." << nio::endl;
	csl << "width (left): " << nio::left << 123 << "." << nio::endl;
	csl.width(0);
	
	char string[50];
	csl << "Enter string: ";
	csl >> string;
	
	csl << "You entered: " << string << nio::endl;
	
	int num;
	csl << "Enter number: ";
	csl >> num;
	csl << "You entered: " << num << nio::endl;
	
	csl << "Enter hex number: ";
	csl >> nio::hex >> num;
	csl << "You entered: " << num << " (dec: " << nio::dec << num << ")" << nio::endl;
	
	csl << "Enter oct number: ";
	csl >> nio::oct >> num;
	csl << "You entered: " << num << " (dec: " << nio::dec << num << ")" << nio::endl;
	
	csl << "unitbuf test, press any key" << nio::endl;
	csl << nio::nounitbuf << "this text should be visible after you pressed a key" << nio::endl;
	wait_key_pressed();
	csl.flush();
	
	wait_key_pressed();
	return 0;
}