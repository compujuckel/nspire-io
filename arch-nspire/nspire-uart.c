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

#include <nspireio/platform.h>

BOOL uart_ready(void)
{
	volatile unsigned *line_status_reg = IO(0x90020014,0x90020018);
	return is_classic ? *line_status_reg & 0b1 : !(*line_status_reg & 0b10);
}

char uart_getchar(void)
{
	volatile unsigned *line_status_reg = IO(0x90020014,0x90020018);
	volatile unsigned *recv_buffer_reg = (unsigned*)0x90020000;
	if(is_classic)
		while(!(*line_status_reg & 0b1));
	else
		while(*line_status_reg &0b10);
	return *recv_buffer_reg;
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
	volatile unsigned *line_status_reg = IO(0x90020014,0x90020018);
	volatile unsigned *xmit_holding_reg = (unsigned*)0x90020000;
	if(is_classic)
		while(!(*line_status_reg & 0b100000)); // wait for empty xmit holding reg
	else
		while(!(*line_status_reg & 0b10000000)); // According to PL011 docs bit 7 is set when transmit reg is empty... I didn't notice this for over a half year o_O
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
	__builtin_va_list arglist;
	__builtin_va_start(arglist,format);
	vsprintf(buf,format,*(char **)&arglist);
	uart_puts(buf);
	__builtin_va_end(arglist);
}