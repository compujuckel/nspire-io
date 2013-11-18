#include "uart.hpp"

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
