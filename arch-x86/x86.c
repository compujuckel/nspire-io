/**
 * @file nspire.c
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
 * Functions for Nspire platform
 */

#include "../include/nspireio/platform.h"
#include "../common/util.h"

#include <SDL2/SDL.h>
#include <time.h>

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Texture* screen = NULL;
static SDL_mutex* screen_px_lock = NULL;
static unsigned short* screen_px = NULL;
static char* keystates = NULL;
static int kcount = 0;
static BOOL initialized = FALSE;

unsigned int nio_sdl_callback(unsigned int interval, void* param);
void nio_sdl_update(void);

static int nio_sdl_main(void* data) {
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("Nspire I/O", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if(window == NULL)
		exit_with_error(__FUNCTION__,"window is null");
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL)
		exit_with_error(__FUNCTION__,"renderer is null");
	
	screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB565, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
	if(screen == NULL)
		exit_with_error(__FUNCTION__,"screen is null");
	
	screen_px_lock = SDL_CreateMutex();
	
	SDL_LockMutex(screen_px_lock);
	screen_px = malloc(SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(short));
	if(screen_px == NULL)
		exit_with_error(__FUNCTION__,"screen_px is null");
	
	SDL_UnlockMutex(screen_px_lock);

	clrscr();

	SDL_AddTimer(20, &nio_sdl_callback, NULL);

	keystates = SDL_GetKeyboardState(&kcount);

	initialized = TRUE;

	// Event loop
	while(1) {
		SDL_Event ev;
		while(SDL_WaitEvent(&ev)) {
			if(ev.type == SDL_QUIT) {
				exit(0);
			} else if(ev.type == SDL_USEREVENT) {
				nio_sdl_update();
			} else if(ev.type == SDL_KEYDOWN || ev.type == SDL_KEYUP) {
				printf("Physical %s -> %s\n",SDL_GetScancodeName(ev.key.keysym.scancode),SDL_GetKeyName(ev.key.keysym.sym));
				break;
			}
		}
	}

	return 0;
}

void nio_platform_init(void) {
	SDL_Thread* t;
	t = SDL_CreateThread(nio_sdl_main, "SDLMain", NULL);
	if(t == NULL)
		exit_with_error(__FUNCTION__,"Could not create thread");

	while(!initialized)
		SDL_Delay(10);
}

void idle(void) {
	SDL_Delay(10);
}

void clrscr(void) {
	SDL_LockMutex(screen_px_lock);
	memset(screen_px,0,SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(short));
	SDL_UnlockMutex(screen_px_lock);
}

void wait_key_pressed(void) {
	wait_no_key_pressed();
	while(!any_key_pressed())
		idle();
}

void wait_no_key_pressed(void) {
	while(any_key_pressed())
		idle();
}

BOOL any_key_pressed(void) {
	int i;
	for(i = 0; i < kcount; i++) {
		if(keystates[i])
			return TRUE;
	}
	return FALSE;
}

BOOL isKeyPressed(int key) {
	return keystates[key];
}

unsigned short getPaletteColor(unsigned int color)
{
	unsigned short palette[16] = {0x0000, 0xa800, 0x0540, 0xaaa0, 0x0015, 0xa815, 0x0555, 0xad55,
					0x5aab, 0xfaab, 0x5feb, 0xffeb, 0x5abf, 0xfabf, 0x5fff, 0xffff};
	int rbtable[6] = {0,6,12,18,24,31};
	int gtable[6] = {0,12,25,37,50,63};
        unsigned int c = color;
        unsigned int d;
        if(c < 16)
        {
                return palette[c];
        }
        else if(c < 232)
        {
                d = c-16;
                return (rbtable[d/36]<<11)+(gtable[(d/6)%6]<<5)+rbtable[d%6];
        }
        else if(c < 256)
        {
                d = c-232;
                return ((d+1)<<11)+((d*2+2)<<5)+(d+1);
        }
	return 0;
}

unsigned int nio_sdl_callback(unsigned int interval, void* param) {
	SDL_Event ev;
	SDL_UserEvent uev;

	uev.type = SDL_USEREVENT;
	uev.code = 0;
	uev.data1 = NULL;
	uev.data2 = NULL;

	ev.type = SDL_USEREVENT;
	ev.user = uev;

	SDL_PushEvent(&ev);
	return interval;
}

void nio_sdl_update(void) {
	SDL_UpdateTexture(screen, NULL, screen_px, SCREEN_WIDTH * sizeof(short));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, screen, NULL, NULL);
	SDL_RenderPresent(renderer);
}

// by totorigolo
void nio_pixel_set(int x, int y, unsigned int color)
{
	unsigned short c = getPaletteColor(color);

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return;

	SDL_LockMutex(screen_px_lock);
	screen_px[SCREEN_WIDTH * y + x] = c;
	SDL_UnlockMutex(screen_px_lock);
}

void nio_vram_pixel_set(const int x, const int y, const unsigned int color)
{
	nio_pixel_set(x,y,color);
}

void nio_vram_draw(void)
{

}

unsigned int nio_cursor_clock(void) {
    return time(NULL);
}

BOOL shift = FALSE;
BOOL caps = FALSE;
BOOL ctrl = FALSE;
static char shiftKey(const char normalc, const char shiftc)
{
	if(shift || caps)
	{
		shift = FALSE;
		return shiftc;
	}
	else return normalc;
}
static char shiftOrCtrlKey(const char normalc, const char shiftc, const char ctrlc)
{
	if(shift || caps)
	{
		shift = FALSE;
		return shiftc;
	}
	else if(ctrl)
	{
		ctrl = FALSE;
		return ctrlc;
	}
	else return normalc;
}

char nio_ascii_get(int* adaptive_cursor_state)
{
	// Ctrl, Shift, Caps first
	if(isKeyPressed(KEY_NSPIRE_CTRL))
	{
		if(ctrl)
		{
			ctrl = FALSE;
			*adaptive_cursor_state = 0;
		}
		else
		{
			ctrl = TRUE;
			*adaptive_cursor_state = 4;
		}
		return 1; // Indicates that no key has been pressed - the cursor will continue flashing.
	}
	if(isKeyPressed(KEY_NSPIRE_SHIFT))
	{
		if(ctrl)
		{
			ctrl = FALSE;
			shift = FALSE;
			caps = TRUE;
			*adaptive_cursor_state = 2;
		}
		else if(caps)
		{
			caps = FALSE;
			*adaptive_cursor_state = 0;
		}
		else if(shift)
		{
			shift = FALSE;
			*adaptive_cursor_state = 0;
		}
		else
		{
			shift = TRUE;
			*adaptive_cursor_state = 1;
		}
		return 1;
	}

	if(caps)
		*adaptive_cursor_state = 2;

//	if(isKeyPressed(KEY_NSPIRE_ESC)) return 0;

	// Characters
	if(isKeyPressed(KEY_NSPIRE_A)) return shiftKey('a','A');
	if(isKeyPressed(KEY_NSPIRE_B)) return shiftKey('b','B');
	if(isKeyPressed(KEY_NSPIRE_C)) return shiftKey('c','C');
	if(isKeyPressed(KEY_NSPIRE_D)) return shiftKey('d','D');
	if(isKeyPressed(KEY_NSPIRE_E)) return shiftKey('e','E');
	if(isKeyPressed(KEY_NSPIRE_F)) return shiftKey('f','F');
	if(isKeyPressed(KEY_NSPIRE_G)) return shiftKey('g','G');
	if(isKeyPressed(KEY_NSPIRE_H)) return shiftKey('h','H');
	if(isKeyPressed(KEY_NSPIRE_I)) return shiftKey('i','I');
	if(isKeyPressed(KEY_NSPIRE_J)) return shiftKey('j','J');
	if(isKeyPressed(KEY_NSPIRE_K)) return shiftKey('k','K');
	if(isKeyPressed(KEY_NSPIRE_L)) return shiftKey('l','L');
	if(isKeyPressed(KEY_NSPIRE_M)) return shiftKey('m','M');
	if(isKeyPressed(KEY_NSPIRE_N)) return shiftKey('n','N');
	if(isKeyPressed(KEY_NSPIRE_O)) return shiftKey('o','O');
	if(isKeyPressed(KEY_NSPIRE_P)) return shiftKey('p','P');
	if(isKeyPressed(KEY_NSPIRE_Q)) return shiftKey('q','Q');
	if(isKeyPressed(KEY_NSPIRE_R)) return shiftKey('r','R');
	if(isKeyPressed(KEY_NSPIRE_S)) return shiftKey('s','S');
	if(isKeyPressed(KEY_NSPIRE_T)) return shiftKey('t','T');
	if(isKeyPressed(KEY_NSPIRE_U)) return shiftKey('u','U');
	if(isKeyPressed(KEY_NSPIRE_V)) return shiftKey('v','V');
	if(isKeyPressed(KEY_NSPIRE_W)) return shiftKey('w','W');
	if(isKeyPressed(KEY_NSPIRE_X)) return shiftKey('x','X');
	if(isKeyPressed(KEY_NSPIRE_Y)) return shiftKey('y','Y');
	if(isKeyPressed(KEY_NSPIRE_Z)) return shiftKey('z','Z');

	// Numbers
	if(isKeyPressed(KEY_NSPIRE_0)) return '0';
	if(isKeyPressed(KEY_NSPIRE_1)) return '1';
	if(isKeyPressed(KEY_NSPIRE_2)) return '2';
	if(isKeyPressed(KEY_NSPIRE_3)) return '3';
	if(isKeyPressed(KEY_NSPIRE_4)) return '4';
	if(isKeyPressed(KEY_NSPIRE_5)) return '5';
	if(isKeyPressed(KEY_NSPIRE_6)) return '6';
	if(isKeyPressed(KEY_NSPIRE_7)) return '7';
	if(isKeyPressed(KEY_NSPIRE_8)) return '8';
	if(isKeyPressed(KEY_NSPIRE_9)) return '9';
/*
	// Symbols
	if(isKeyPressed(KEY_NSPIRE_COMMA))		return shiftKey(',',';');
	if(isKeyPressed(KEY_NSPIRE_PERIOD)) 	return shiftKey('.',':');
	if(isKeyPressed(KEY_NSPIRE_COLON))		return ':';
	if(isKeyPressed(KEY_NSPIRE_LP))			return shiftOrCtrlKey('(','[',']');
	if(isKeyPressed(KEY_NSPIRE_RP))			return shiftOrCtrlKey(')','{','}');
	if(isKeyPressed(KEY_NSPIRE_SPACE))		return shiftKey(' ','_');
	if(isKeyPressed(KEY_NSPIRE_DIVIDE))		return shiftKey('/','\\');
	if(isKeyPressed(KEY_NSPIRE_MULTIPLY))	return shiftKey('*','\"');
	if(isKeyPressed(KEY_NSPIRE_MINUS))		return shiftOrCtrlKey('-','<', '_');
	if(isKeyPressed(KEY_NSPIRE_NEGATIVE))	return shiftKey('-','_');
	if(isKeyPressed(KEY_NSPIRE_PLUS))		return shiftKey('+', '>');
	if(isKeyPressed(KEY_NSPIRE_EQU))		return shiftKey('=', '|');
	if(isKeyPressed(KEY_NSPIRE_LTHAN))		return '<';
	if(isKeyPressed(KEY_NSPIRE_GTHAN))		return '>';
	if(isKeyPressed(KEY_NSPIRE_QUOTE))		return '\"';
	if(isKeyPressed(KEY_NSPIRE_APOSTROPHE))	return '\'';
	if(isKeyPressed(KEY_NSPIRE_QUES))		return shiftKey('?','!');
	if(isKeyPressed(KEY_NSPIRE_QUESEXCL))	return shiftKey('?','!');
	if(isKeyPressed(KEY_NSPIRE_BAR))		return '|';
	if(isKeyPressed(KEY_NSPIRE_EXP))		return '^';
	if(isKeyPressed(KEY_NSPIRE_EE))		return shiftKey('&','%');*/
	if(isKeyPressed(KEY_NSPIRE_ENTER))		return shiftKey('\n','~');

	// Special chars
	if(isKeyPressed(KEY_NSPIRE_DEL))		return '\b';
	if(isKeyPressed(KEY_NSPIRE_RET))		return '\n';
//	if(isKeyPressed(KEY_NSPIRE_TAB))		return '\t';

	return 0;
}
