/**
 * @file tests.c
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
 * Tests a lot of nspireio functions
 */

#include <nspireio/nspireio.h>

#ifndef NIO_TEST_UART
#define NIO_TEST_UART 0
#endif

int main(void)
{
	assert_ndless_rev(874);
	
	nio_console csl;
	nio_init(&csl,NIO_MAX_COLS,NIO_MAX_ROWS,0,0,NIO_COLOR_WHITE,NIO_COLOR_BLACK,TRUE);
	nio_set_default(&csl);
	nio_color(&csl,NIO_COLOR_BLACK,NIO_COLOR_WHITE);
	nio_puts("Nspire I/O testing tool");
	nio_color(&csl,NIO_COLOR_WHITE,NIO_COLOR_BLACK);
	nio_printf("Compiled %s %s\n",__DATE__,__TIME__);
	nio_puts("Press any key to flush console...");
	nio_drawing_enabled(&csl,FALSE);
	nio_putchar('A');
	nio_fputc('a',&csl);
	nio_putchar('\n');
	nio_puts("Color palette test:");
	int i, j;
	for(i = 0; i < 16; i++)
	{
		for(j = 0; j < 16; j++)
		{
			nio_color(&csl,i,j);
			nio_putchar('X');
		}
		nio_putchar('\n');
	}
	nio_color(&csl,NIO_COLOR_WHITE,NIO_COLOR_BLACK);
	nio_puts("This line is too long for the Nspire's screen so we have to continue it on the next line...");
	wait_key_pressed();
	nio_fflush(&csl);
	nio_drawing_enabled(&csl,TRUE);
	nio_puts("Enter text:");
	char input[100] = {0};
	nio_getsn(input,100);
	nio_printf("Your text was:\n%s\n",input);
	nio_puts("Enter a number: ");
	int num;
	if(nio_scanf("%d",&num) == 1)
		nio_printf("Your number was: %d\n",num);
	else
		nio_puts("You did not enter a number!");
	errno = 1;
	nio_perror("Error test");
	nio_puts("Saving console. Press any key...");
	nio_save("/documents/nio_tests.tns",&csl);
	wait_key_pressed();
	nio_free(&csl);
	nio_load("/documents/nio_tests.tns",&csl);
	nio_puts("If the text above is the same, everything is OK");
	
	#if NIO_TEST_UART == 1
	nio_puts("Testing UART...\n");
	uart_puts("Nspire I/O testing tool\n");
	uart_printf("Compiled %s %s\n",__DATE__,__TIME__);
	
	uart_puts("Enter text: ");
	uart_getsn(input,100);
	uart_printf("Your text was: %s\n",input);
	#endif
	
	nio_puts("Tests finished.");
	nio_free(&csl);
	wait_key_pressed();
	
	return 0;
}
