// Hello World with old syntax
#include <os.h>
#define NIO_KEEP_COMPATIBILITY
#include <nspireio2.h>

int main(void)
{
    nio_console csl;
    nio_InitConsole(&csl,53,30,0,0,WHITE,BLACK);
    nio_PrintStr(&csl,"Hello World!");
    nio_CleanUp(&csl);
    
    wait_key_pressed();
    return 0;
}