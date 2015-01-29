/**
 * @file splitscreen.c
 * @author  Julian Mackeben aka compu <compujuckel@googlemail.com>
 * @version 3.1
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
 * Splitscreen demo
 */
#include <nspireio/nspireio.h>

int main(void)
{
	
	wait_no_key_pressed();
	
	nio_console c1;
	// 53 columns, 15 rows. 0px offset for x/y. Background color 15 (white), foreground color 0 (black)
	nio_init(&c1,53,15,0,0,NIO_COLOR_WHITE,NIO_COLOR_BLACK,TRUE);
	
	nio_console c2;
	nio_init(&c2,53,15,0,15*8,NIO_COLOR_BLACK,NIO_COLOR_WHITE,TRUE);
	
	// Just showing printf
	nio_fprintf(&c1,"%s build at %s, %s\n",__FILE__,__DATE__,__TIME__);
	
	while(1)
	{
		char text[100];
		// If no text was entered, exit
		if(!nio_fgets(text,100,&c1))
			break;
		// Write the text into 2nd console
		nio_fprintf(&c2,"%s\n",text);
	}
	
	nio_free(&c1);
	nio_free(&c2);

	return 0;
}
