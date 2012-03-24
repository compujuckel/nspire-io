/**
 * @file ConsoleDemo.c
 * @author  Julian Mackeben aka compu <compujuckel@googlemail.com>
 * @version 2.0
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
#include <nspireio2.h>

int main(void)
{
	wait_no_key_pressed();
	
	nio_console c;
	nio_InitConsole(&c,53,30,0,0,15,0);
	nio_DrawConsole(&c);
	
	while(1)
	{
		nio_PrintStr(&c,"Enter some text:",TRUE);
		
		char str[50];
		if(nio_GetStr(&c,str))
		{
			nio_PrintStr(&c,"Your text was: ",TRUE);
			nio_PrintStr(&c,str,TRUE);
		}
		else
		{
			nio_PrintStr(&c,"ENTER. SOME. TEXT.",TRUE);
			break;
		}
	}
	/*int i, j;
	for(i = 0; i < 16; i++)
	{
		for(j = 15; j >= 0; j--)
		{
			nio_SetColor(&c, i, j);
			nio_PrintChar(&c,'x',TRUE);
		}
		nio_PrintChar(&c,'\n',TRUE);
	}*/
	
	nio_CleanUp(&c);
	wait_key_pressed();
	return 0;
}
