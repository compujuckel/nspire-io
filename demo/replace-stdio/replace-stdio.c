#include <os.h>
#define NIO_REPLACE_STDIO
#include <nspireio2.h>

int main(void)
{
    // Use this function at the beginning of your code
    nio_use_stdio();
    puts("Hello World!");
    // ...and this one at the end
    nio_free_stdio();
    
    wait_key_pressed();
    return 0;
}