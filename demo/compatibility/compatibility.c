/**
 * @file compatibility.c
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
 * Compatibility demo
 */

// Including nspireio2.h compiles the program in compatibility mode automatically
// Alternatively, you could use:
// #define NIO_KEEP_COMPATIBILITY
// #include <nspireio/nspireio.h>
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