#include <os.h>
#include <nspireio2.h>

int main(void)
{
	clrscr();
	
	nio_console csl;
	nio_init(&csl,NIO_MAX_COLS,NIO_MAX_ROWS,0,0,WHITE,BLACK,TRUE);
	nio_set_default(&csl);
	nio_color(&csl,BLACK,WHITE);
	nio_puts("Nspire I/O testing tool\n");
	nio_color(&csl,WHITE,BLACK);
	nio_printf("Compiled %s %s\n",__DATE__,__TIME__);
	nio_puts("Press any key to flush console...\n");
	nio_drawing_enabled(&csl,FALSE);
	nio_putchar('A');
	nio_fputc('a',&csl);
	nio_putchar('\n');
	nio_puts("This line is too long for the Nspire's screen so we have te continue it on the next line...\n");
	wait_key_pressed();
	nio_fflush(&csl);
	nio_drawing_enabled(&csl,TRUE);
	nio_puts("Enter text:\n");
	char input[100];
	nio_gets(input);
	nio_printf("Your text was:\n%s\n",input);
	errno = 1;
	nio_perror("Error test: ");
	nio_putchar('\n');
	nio_puts("Saving console. Press any key...\n");
	nio_save("/documents/nio_tests.tns",&csl);
	wait_key_pressed();
	clrscr();
	nio_free(&csl);
	nio_load("/documents/nio_tests.tns",&csl);
	nio_puts("If the text above is the same, everything is OK\n");
	
	int reg_test = 12345;
	nio_fprintf(&csl,"Storing %d in file\n",reg_test);
	reg_store(&reg_test,sizeof(int),"/documents/nio_tests.tns");
	int* reg_test2 = reg_get("/documents/nio_tests.tns");
	nio_printf("%d is %d\n",reg_test,*reg_test2);
	
	nio_puts("Testing UART...\n");
	uart_puts("Nspire I/O testing tool\n");
	uart_printf("Compiled %s %s",__DATE__,__TIME__);
	
	nio_puts("Tests finished.");
	nio_free(&csl);
	wait_key_pressed();
	
	return 0;
}