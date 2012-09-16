/**
 * @file replace-stdio.c
 * @author  Julian Mackeben aka compu <compujuckel@googlemail.com>
 * @version 3.0
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
 * stdio demo
 */
#include <os.h>
#define NIO_REPLACE_STDIO
#include <nspireio.h>

int main(void)
{
    lcd_ingray();
	// Use this function at the beginning of your code
    nio_use_stdio();
    puts("Hello World!");
    // ...and this one at the end
    nio_free_stdio();
    
    wait_key_pressed();
    return 0;
}