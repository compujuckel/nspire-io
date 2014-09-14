#include "util.h"

void exit_with_error(const char* f, const char* e)
{
	uart_printf("Nspire I/O: in %s: %s\n",f,e);
	abort();
}