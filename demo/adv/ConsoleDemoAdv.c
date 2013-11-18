/**
 * @file ConsoleDemoAdv.c
 * @author  Julian Mackeben aka compu <compujuckel@googlemail.com>
 * @author Albert Huang aka alberthrocks <alberthrocks.public@gmail.com>
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
 * A more complex demo program showing the cursor functions of NspireIO.
 */
#include <nspireio/nspireio.h>

int main(void)
{
	wait_no_key_pressed();
	
	// Initialize console 1.
	nio_console c1;
	
	nio_init(&c1,NIO_MAX_COLS,NIO_MAX_ROWS,0,0,NIO_COLOR_BLACK,NIO_COLOR_WHITE,TRUE);
	nio_set_default(&c1);
	nio_fflush(&c1);
	
	// Just showing printf
	nio_printf("%s built at %s, %s\n",__FILE__,__DATE__,__TIME__);
	nio_printf("By Albert \"alberthrocks\" Huang\n");
	nio_printf("Original code by Julian \"compu\" Mackeben\n\n");
	nio_printf("For help with this awesome console, type \"help\"!\n\n");
	while(1)
	{
		char text[100];
		nio_printf("> ");
		// If no text was entered, exit
		if(!nio_getsn(text,100))
			continue;
		
		// Check for interesting text
		if (!strcmp(text, "help")) {
			nio_printf("ConsoleDemo+ Help\n");
			nio_printf("  setcursor cursor\n");
			nio_printf("    Set the cursor type.\n");
			nio_printf("    cursor can be from 0-3, where:\n");
			nio_printf("      0 is a block cursor\n");
			nio_printf("      1 is an underscore cursor\n");
			nio_printf("      2 is a verical bar cursor\n");
			nio_printf("      3 is a custom cursor\n");
			nio_printf("  setcursorwidth\n");
			nio_printf("    Set the cursor width.\n");
			nio_printf("  loadterm\n");
			nio_printf("    Load the current terminal state.\n");
			nio_printf("  saveterm\n");
			nio_printf("    Save the current terminal state.\n");
			nio_printf("  delsaveterm\n");
			nio_printf("    Delete the saved terminal state.\n");
			nio_printf("  clear\n");
			nio_printf("    Clear the console.\n");
			nio_printf("  exit\n");
			nio_printf("    Exit this console.\n");
		}
		
		if (!strcmp(text, "setcursor 0")) {
			nio_cursor_type(&c1, NIO_CURSOR_BLOCK);
			nio_printf(" Cursor type is now set to block cursor.\n");
		}
		if (!strcmp(text, "setcursor 1")) {
			nio_cursor_type(&c1, NIO_CURSOR_UNDERSCORE);
			nio_printf(" Cursor type is now set to underscore cursor.\n");
		}
		if (!strcmp(text, "setcursor 2")) {
			nio_cursor_type(&c1, NIO_CURSOR_VERTICAL);
			nio_printf(" Cursor type is now set to vertical bar cursor.\n");
		}
		if (!strcmp(text, "setcursor 3")) {
			const char cursor[6] = {0x38,0x42,0x41,0x42,0x38,0xFF};
			nio_cursor_type(&c1, NIO_CURSOR_CUSTOM);
			nio_cursor_custom(&c1, (unsigned char*) cursor);
			nio_printf(" Cursor type is now set to custom cursor.\n");
		}
		
		if (!strcmp(text, "setcursorwidth")) {
			nio_printf("Specify cursor width: ");
			char num[10];
			nio_getsn(num,10);
			nio_cursor_width(&c1, atoi(num));
		}
		
		if (!strcmp(text, "loadterm")) {
			nio_clear(&c1);
			nio_load("nio_consoledemoadv.sav", &c1);
		}
		
		if (!strcmp(text, "clear")) {
			nio_clear(&c1);
		}
		
		if (!strcmp(text, "saveterm")) {
			nio_save("nio_consoledemoadv.sav", &c1);
			nio_printf(" Saved terminal state to nio_consoledemoadv.sav.\n");
		}
		
		if (!strcmp(text, "delsaveterm")) {
			if (!unlink("nio_consoledemoadv.sav")) {
				nio_printf(" Removed old terminal state: nio_consoledemoadv.sav.\n");
			} else {
				nio_printf(" No old terminal state file found.\n");
			}
		}
		
		if (!strcmp(text, "exit")) break;
	}
	
	nio_free(&c1);
	
	//if(has_colors)
	//	lcd_incolor();
		
	return 0;
}
