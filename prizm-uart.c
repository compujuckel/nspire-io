/**
 * @file uart.c
 * @author Julien Savard aka Juju <juju2143@gmail.com>
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

#include "nspireio-platform.h"

BOOL uart_ready(void)
{
	return (Serial_IsOpen()==1) ? TRUE : FALSE;
}

char uart_getchar(void)
{
	char out;
	Serial_ReadSingle(&out);
	return out;
}

char* uart_gets(char* str)
{
	int i = 0;
	while(1)
	{
		char c = uart_getchar();
		str[i++] = c;
		if(c == '\n')
		{
			str[i] = 0;
			return str;
		}
	}
}

char uart_putchar(char character)
{
	Serial_WriteSingle(character);
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
	__builtin_va_list arglist;
	__builtin_va_start(arglist,format);
	vsprintf(buf,format,*(char **)&arglist);
	uart_puts(buf);
	__builtin_va_end(arglist);
}
