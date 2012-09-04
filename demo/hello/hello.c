#include <os.h>
#include <nspireio2.h>

int main(void)
{
    // Create a console named csl
    nio_console csl;
    // Initialize the console. It has 53 columns, 30 rows, x coordinate 0 and y coordinate 0. This will create a full-screen console with background color white and text color black.
    nio_init(&csl,NIO_MAX_COLS,NIO_MAX_ROWS,0,0,WHITE,BLACK,TRUE);
    // Write "Hello World!" into csl
    nio_fputs("Hello World!",&csl);
    // Uninitialize csl. You should always use this function on all your consoles before exiting your program.
    nio_free(&csl);

    wait_key_pressed();
    return 0;
}