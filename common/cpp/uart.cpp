/**
 * @file uart.cpp
 * @author  Julian Mackeben aka compu <compujuckel@googlemail.com>
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
 * C++ UART wrapper
 */

#include <nspireio/uart.hpp>

using namespace nio;

uart::uart()
{
	f = (fmtflags)(dec | right | fixed | skipws);
	s = goodbit;
	w = 0;
	p = 5;
	count = 0;
}

void uart::put(char ch)
{
	uart_putchar(ch);
}

void uart::write(const char* s, streamsize n)
{
	int i;
	for(i = 0; i < n; i++)
		put(s[i]);
}

void uart::flush()
{

}

streamsize uart::gcount() const
{
	return count;
}

char uart::get()
{
	char tmp = uart_getchar();
	count = tmp != 0 ? 1 : 0;
	return tmp;
}

void uart::get(char& ch)
{
	ch = uart_getchar();
	count = ch != 0 ? 1 : 0;
}

void uart::get(char* s, streamsize n)
{
	uart_gets(s);
	count = strlen(s);
}

void uart::getline(char* s, streamsize n)
{
	get(s,n);
}
