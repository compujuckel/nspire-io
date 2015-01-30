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
#include "../../../Ndless/ndless-sdk/include/keys.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define NIO_MAX_COLS 53
#define NIO_MAX_ROWS 30

//typedef enum { FALSE, TRUE } BOOL;
typedef int BOOL;
#define TRUE 1
#define FALSE 0

/*
#define KEY_NSPIRE_ENTER	SDL_SCANCODE_RETURN
#define KEY_NSPIRE_RET		SDL_SCANCODE_RETURN
#define KEY_NSPIRE_SHIFT	SDL_SCANCODE_LSHIFT
#define KEY_NSPIRE_CTRL		SDL_SCANCODE_LCTRL
#define KEY_NSPIRE_DEL		SDL_SCANCODE_BACKSPACE

#define KEY_NSPIRE_A SDL_SCANCODE_A
#define KEY_NSPIRE_B SDL_SCANCODE_B
#define KEY_NSPIRE_C SDL_SCANCODE_C
#define KEY_NSPIRE_D SDL_SCANCODE_D
#define KEY_NSPIRE_E SDL_SCANCODE_E
#define KEY_NSPIRE_F SDL_SCANCODE_F
#define KEY_NSPIRE_G SDL_SCANCODE_G
#define KEY_NSPIRE_H SDL_SCANCODE_H
#define KEY_NSPIRE_I SDL_SCANCODE_I
#define KEY_NSPIRE_J SDL_SCANCODE_J
#define KEY_NSPIRE_K SDL_SCANCODE_K
#define KEY_NSPIRE_L SDL_SCANCODE_L
#define KEY_NSPIRE_M SDL_SCANCODE_M
#define KEY_NSPIRE_N SDL_SCANCODE_N
#define KEY_NSPIRE_O SDL_SCANCODE_O
#define KEY_NSPIRE_P SDL_SCANCODE_P
#define KEY_NSPIRE_Q SDL_SCANCODE_Q
#define KEY_NSPIRE_R SDL_SCANCODE_R
#define KEY_NSPIRE_S SDL_SCANCODE_S
#define KEY_NSPIRE_T SDL_SCANCODE_T
#define KEY_NSPIRE_U SDL_SCANCODE_U
#define KEY_NSPIRE_V SDL_SCANCODE_V
#define KEY_NSPIRE_W SDL_SCANCODE_W
#define KEY_NSPIRE_X SDL_SCANCODE_X
#define KEY_NSPIRE_Y SDL_SCANCODE_Y
#define KEY_NSPIRE_Z SDL_SCANCODE_Z

#define KEY_NSPIRE_0 SDL_SCANCODE_0
#define KEY_NSPIRE_1 SDL_SCANCODE_1
#define KEY_NSPIRE_2 SDL_SCANCODE_2
#define KEY_NSPIRE_3 SDL_SCANCODE_3
#define KEY_NSPIRE_4 SDL_SCANCODE_4
#define KEY_NSPIRE_5 SDL_SCANCODE_5
#define KEY_NSPIRE_6 SDL_SCANCODE_6
#define KEY_NSPIRE_7 SDL_SCANCODE_7
#define KEY_NSPIRE_8 SDL_SCANCODE_8
#define KEY_NSPIRE_9 SDL_SCANCODE_9
*/
void clrscr(void);
void idle(void);
void wait_key_pressed(void); // blocks until a key is pressed
void wait_no_key_pressed(void); // blocks until all keys are released
BOOL any_key_pressed(void); // non-blocking, TRUE if any key pressed
BOOL isKeyPressed(const t_key* key);
#define isKeyPressed(x) isKeyPressed(&x)

#endif
