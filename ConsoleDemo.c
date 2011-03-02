/**
 * @file ConsoleDemo.c
 * @author  Julian Mackeben aka compu <compujuckel@googlemail.com>
 * @version 0.1
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * A simple demo program showing some of the I/O functions.
 */
#include <os.h>
#include "screen.h"
#include "console.h"

int main(void)
{
	clrscr();
	c_init(0x0,0xF);
	c_swrite("Demo: %s built at %s %s\n\n",50,__FILE__,__DATE__,__TIME__);
	c_write("Features\n");
	c_write("\t* Formatted text output\n");
	c_write("\t* Char/String input\n");
	c_write("\n\nInput a string: ");
	char buffer[50];
	if(c_read(buffer)) c_swrite("\nYour text was: %s",50,buffer);
	else c_write("\nYou didn't write a string...");
	wait_key_pressed();
	return 0;
}
