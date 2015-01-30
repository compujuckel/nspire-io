/**
 * @file nspire.h
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
 * Header for Nspire platform
 */

#ifndef X86_H
#define X86_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <SDL2/SDL.h>
#include "ndless-sdk/include/keys.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define NIO_MAX_COLS 53
#define NIO_MAX_ROWS 30

typedef int BOOL;
#define TRUE 1
#define FALSE 0

#include "libndls-x86.h"

#endif
