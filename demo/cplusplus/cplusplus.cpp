/**
 * @file cplusplus.cpp
 * @author  Julian Mackeben aka compu <compujuckel@googlemail.com>
 * @version 3.1
 *
 * @section LICENSE
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301  USA
 *
 * @section DESCRIPTION
 *
 * C++ demo
 */

#include <nspireio/console.hpp>
#include <nspireio/uart.hpp>

#ifndef NIO_TEST_UART
#define NIO_TEST_UART 0
#endif

int main(void)
{
	clrscr();
	#if NIO_TEST_UART == 1
	nio::uart u;
	#endif
	nio::console c;
	
	int num = 123;
	
	c.foreground_color(nio::COLOR_LIGHTRED);
	char test[] = "Nspire I/O C++ test";
	c << test << nio::endl;
	c.foreground_color(nio::COLOR_BLACK);
	c << "dec: " << num << " hex: " << nio::hex << num << " oct: " << nio::oct << num << nio::endl;
	c << "showbase" << nio::endl;
	
	c.setf(console::showbase);
	c.setf(console::dec, console::basefield);
	
	c << "dec: " << num << " hex: " << nio::hex << num << " oct: " << nio::oct << num << nio::endl;
	c << "uppercase: " << nio::hex << nio::uppercase << num << nio::endl;
	
	c.unsetf(console::uppercase);
	c.setf(console::dec, console::basefield);
	
	c << "bool: " << true << ", " << false << nio::endl;
	c << "boolalpha" << nio::boolalpha << nio::endl;
	c << "bool: " << true << ", " << false << nio::endl;
	
	c.width(10);
	
	c << "width" << nio::endl;
	c << "\"" << num << "\"" << nio::endl;
	c << "left" << nio::left << nio::endl;
	c << "\"" << num << "\"" << nio::endl;
	
	c.width(0);
	
	c << "unitbuf test. Press any key" << nio::endl;
	c.unsetf(console::unitbuf);
	c << "This should be visible AFTER you pressed a key." << nio::endl;
	wait_key_pressed();
	c.flush();
	c.setf(console::unitbuf);
	
	char input[50];
	c << "Enter string: ";
	c >> input;
	if(c.gcount() == 0)
		c << "You did not enter anything!" << nio::endl;
	else
		c << "You entered (" << c.gcount() << " chars): " << input << nio::endl;
	
	c << "Enter number: ";
	c >> num;
	c << "You entered " << num << nio::endl;
	
	bool b;
	c << "Enter bool (1/true/yes): ";
	c >> b;
	c << "You entered " << b << nio::endl;
	
	#if NIO_TEST_UART == 1
	u << "Enter string: ";
	u >> input;
	if(u.gcount() == 0)
		u << "You did not enter anything!" << nio::endl;
	else
		u << "You entered (" << u.gcount() << " chars): " << input << nio::endl;
	#endif
	
	wait_key_pressed();
	return 0;
}