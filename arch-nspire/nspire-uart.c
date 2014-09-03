/**
 * @file uart.c
 * @author Julian Mackeben aka compu <compujuckel@googlemail.com>
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
 * Alternative functions for serial communication, no clock on the screen.
 */

#include <stdarg.h>
#include <nspireio/platform.h>

BOOL uart_ready(void)
{
	volatile unsigned *line_status_reg = IO(0x90020014,0x90020018);
	return is_classic ? *line_status_reg & 0b1 : !(*line_status_reg & 0b10);
}

char uart_getchar(void)
{
	volatile unsigned *recv_buffer_reg = (unsigned*)0x90020000;
	while(!uart_ready())
		idle();
	char tmp = *recv_buffer_reg;
	uart_putchar(tmp);
	return tmp;
}

char* uart_getsn(char* str, int num)
{
	int i;
	for(i = 0; i < num-1; i++)
	{
		char c = uart_getchar();
		str[i] = c;
		if(c == '\b')
		{
			uart_puts(" \b");
			i -= 2;
		}
		else if(c == '\r')
		{
			str[i] = 0;
			uart_putchar('\n');
			return str;
		}
	}
	str[num] = 0;
	return str;
}

char* uart_gets(char* str)
{
	return uart_getsn(str,50);
}

char uart_putchar(char character)
{
	volatile unsigned *line_status_reg = IO(0x90020014,0x90020018);
	volatile unsigned *xmit_holding_reg = (unsigned*)0x90020000;
	if(is_classic)
	{
		while(!(*line_status_reg & 0b100000)) // wait for empty xmit holding reg
			idle();
	}
	else
	{
		while(!(*line_status_reg & 0b10000000))
			idle();
	}
	*xmit_holding_reg = character;
    return character;
}

int uart_puts(const char *str)
{
	while(*str) {
		uart_putchar(*str++);
	}
    return 1;
}

void uart_printf(char *format, ...)
{
	char buf[256];
	memset(buf,'\0',256);
	va_list arglist;
	va_start(arglist,format);
	vsprintf(buf,format,arglist);
	uart_puts(buf);
	va_end(arglist);
}
