/**
 * @file ConsoleDemoAdv.c
 * @author  Julian Mackeben aka compu <compujuckel@googlemail.com>
 * @author Albert Huang aka alberthrocks <alberthrocks.public@gmail.com>
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
 * A more complex demo program showing the cursor functions of NspireIO.
 */
#include <os.h>
#define NIO_KEEP_COMPATIBILITY
#include "../nspireio2.h"

int main(void)
{
	if(has_colors)
		lcd_ingray();
	
	wait_no_key_pressed();
	
	// Initialize console 1.
	nio_console c1;
	// 53 columns, 15 rows. 0px offset for x/y. Background color 15 (white), foreground color 0 (black)
	nio_InitConsole(&c1,53,30,0,0,0,15);
	nio_DrawConsole(&c1);
	
	// Just showing printf
	nio_printf(&c1,"%s built at %s, %s\n",__FILE__,__DATE__,__TIME__);
	nio_printf(&c1,"By Albert \"alberthrocks\" Huang\n");
	nio_printf(&c1,"Original code by Julian \"compu\" Mackeben\n\n");
	nio_printf(&c1,"For help with this awesome console, type \"help\"!\n\n");
	while(1)
	{
		char text[100];
		nio_printf(&c1, "> ");
		// If no text was entered, exit
		if(!nio_GetStr(&c1,text))
			continue;
		
		// Check for interesting text
		if (!strcmp(text, "help")) {
			nio_printf(&c1, "ConsoleDemo+ Help\n");
			nio_printf(&c1, "  setcursor cursor\n");
			nio_printf(&c1, "    Set the cursor type.\n");
			nio_printf(&c1, "    cursor can be from 0-3, where:\n");
			nio_printf(&c1, "      0 is a block cursor\n");
			nio_printf(&c1, "      1 is an underscore cursor\n");
			nio_printf(&c1, "      2 is a verical bar cursor\n");
			nio_printf(&c1, "      3 is a custom cursor\n");
			nio_printf(&c1, "  setcursorwidth\n");
			nio_printf(&c1, "    Set the cursor width.\n");
			nio_printf(&c1, "  loadterm\n");
			nio_printf(&c1, "    Load the current terminal state.\n");
			nio_printf(&c1, "  saveterm\n");
			nio_printf(&c1, "    Save the current terminal state.\n");
			nio_printf(&c1, "  delsaveterm\n");
			nio_printf(&c1, "    Delete the saved terminal state.\n");
			nio_printf(&c1, "  clear\n");
			nio_printf(&c1, "    Clear the console.\n");
			nio_printf(&c1, "  exit\n");
			nio_printf(&c1, "    Exit this console.\n");
		}
		
		if (!strcmp(text, "setcursor 0")) {
			nio_SetCursorType(&c1, NIO_CURSOR_BLOCK);
			nio_printf(&c1, " Cursor type is now set to block cursor.\n");
		}
		if (!strcmp(text, "setcursor 1")) {
			nio_SetCursorType(&c1, NIO_CURSOR_UNDERSCORE);
			nio_printf(&c1, " Cursor type is now set to underscore cursor.\n");
		}
		if (!strcmp(text, "setcursor 2")) {
			nio_SetCursorType(&c1, NIO_CURSOR_VERTICAL);
			nio_printf(&c1, " Cursor type is now set to vertical bar cursor.\n");
		}
		if (!strcmp(text, "setcursor 3")) {
			const char cursor[6] = {0x38,0x42,0x41,0x42,0x38,0xFF};
			nio_SetCursorType(&c1, NIO_CURSOR_CUSTOM);
			nio_SetCursorCustom(&c1, (unsigned char*) cursor);
			nio_printf(&c1, " Cursor type is now set to custom cursor.\n");
		}
		
		if (!strcmp(text, "setcursorwidth")) {
			nio_printf(&c1, "Specify cursor width: ");
			char num[10];
			nio_GetStr(&c1, num);
			nio_SetCursorWidth(&c1, atoi(num));
		}
		
		if (!strcmp(text, "loadterm")) {
			nio_Clear(&c1);
			nio_load("nio_consoledemoadv.sav", &c1);
		}
		
		if (!strcmp(text, "clear")) {
			nio_Clear(&c1);
		}
		
		if (!strcmp(text, "saveterm")) {
			nio_save("nio_consoledemoadv.sav", &c1);
			nio_printf(&c1, " Saved terminal state to nio_consoledemoadv.sav.\n");
		}
		
		if (!strcmp(text, "delsaveterm")) {
			if (!unlink("nio_consoledemoadv.sav")) {
				nio_printf(&c1, " Removed old terminal state: nio_consoledemoadv.sav.\n");
			} else {
				nio_printf(&c1, " No old terminal state file found.\n");
			}
		}
		
		if (!strcmp(text, "exit")) break;
	}
	
	nio_CleanUp(&c1);
	
	if(has_colors)
		lcd_incolor();
		
	return 0;
}
