/**
 * @file hello.c
 * @author  Julian Mackeben aka compu <compujuckel@googlemail.com>
 * @version 3.1
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301  USA
 *
 * @section DESCRIPTION
 *
 * Hello World
 */
#include <nspireio/nspireio.h>

int main(void)
{
	// Create a console named csl
    nio_console csl;
    // Initialize the console. It has 53 columns, 30 rows, x coordinate 0 and y coordinate 0. This will create a full-screen console with background color white and text color black.
    nio_init(&csl,NIO_MAX_COLS,NIO_MAX_ROWS,0,0,NIO_COLOR_WHITE,NIO_COLOR_BLACK,TRUE);
    // Write "Hello World!" into csl
    nio_fputs("Hello World!",&csl);
    // Uninitialize csl. You should always use this function on all your consoles before exiting your program.
    nio_free(&csl);

    wait_key_pressed();
    return 0;
}
