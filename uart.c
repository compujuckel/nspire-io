/**
 * @file uart.c
 * @author Julian Mackeben aka compu <compujucke@googlemail.com>
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
 * Alternative functions for serial communication, no clock on the screen.
 */
#include <os.h>
#include "nspireio2.h"

BOOL n_ready(void)
{
	volatile unsigned *line_status_reg = is_classic ? (unsigned*)0x90020014 : (unsigned*)0x90020018;
	return *line_status_reg & 0b1;
}

char n_getc(void)
{
	volatile unsigned *line_status_reg = is_classic ? (unsigned*)0x90020014 : (unsigned*)0x90020018;
	volatile unsigned *recv_buffer_reg = (unsigned*)0x90020000;
	while(!(*line_status_reg & 0b1));
	return *recv_buffer_reg;
}

void n_getline(char* dest)
{
	int i = 0;
	while(1)
	{
		char c = n_getc();
		dest[i++] = c;
		if(c == '\n')
		{
			dest[i] = 0;
			break;
		}
	}
}

void n_putc(char c)
{
	volatile unsigned *line_status_reg = is_classic ? (unsigned*)0x90020014 : (unsigned*)0x90020018;
	volatile unsigned *xmit_holding_reg = (unsigned*)0x90020000;
	while(!(*line_status_reg & 0b100000)); // wait for empty xmit holding reg
		*xmit_holding_reg = c;
}

void n_puts(const char *str)
{
	while(*str) {
		n_putc(*str++);
	}
}

void n_printf(char *format, ...)
{
	char buf[256];
	memset(buf,'\0',256);
	__builtin_va_list arglist;
	__builtin_va_start(arglist,format);
	vsprintf(buf,format,*(char **)&arglist);
	n_puts(buf);
	__builtin_va_end(arglist);
}