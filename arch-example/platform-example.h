/**
 * @file platform-example.h
 * @author Julian Mackeben aka compu <compujuckel@googlemail.com>
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
 * Example platform header.
 */
 
#ifndef EXAMPLE_H
#define EXAMPLE_H

// Put all your platform-specific includes here

#include <important-header.h>

// If your platform does not have this:
// typedef enum { FALSE, TRUE } BOOL;

// Put these macros/functions here
// wait_key_pressed() - blocks until a key is pressed
// wait_no_key_pressed() - blocks until all keys are released (internally calls wait_key_pressed first)
// any_key_pressed() - non-blocking, TRUE if any key pressed

// Fullscreen console size goes here

#define NIO_MAX_ROWS 50
#define NIO_MAX_COLS 50

// Don't forget to add your platform header to platform.h!

#endif
