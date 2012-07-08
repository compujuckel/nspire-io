/**
 * @file ConsoleDemo.c
 * @author  Julian Mackeben aka compu <compujuckel@googlemail.com>
 * @version 2.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301  USA
 *
 * @section DESCRIPTION
 *
 * A simple demo program showing some of the I/O functions.
 */
#include <os.h>
#include <nspireio2.h>

int main(void)
{
	if(has_colors)
		lcd_ingray();
	
	wait_no_key_pressed();
	
	// Initialize console 1.
	nio_console c1;
	// 53 columns, 15 rows. 0px offset for x/y. Background color 15 (white), foreground color 0 (black)
	nio_InitConsole(&c1,53,15,0,0,15,0);
	nio_DrawConsole(&c1);
	
	nio_console c2;
	nio_InitConsole(&c2,53,15,0,15*8,0,15);
	nio_DrawConsole(&c2);
	
	// Just showing printf
	nio_printf(&c1,"%s build at %s, %s\n",__FILE__,__DATE__,__TIME__);
	
	while(1)
	{
		char text[100];
		// If no text was entered, exit
		if(!nio_GetStr(&c1,text))
			break;
		// Write the text into 2nd console
		nio_printf(&c2,"%s\n",text);
	}
	
	
	
	nio_CleanUp(&c1);
	nio_CleanUp(&c2);
	
	if(has_colors)
		lcd_incolor();
		
	return 0;
}
