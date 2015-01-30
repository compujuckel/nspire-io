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
#include "../../Ndless/ndless-sdk/include/keys.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Texture* screen = NULL;
static SDL_mutex* screen_px_lock = NULL;
static TTF_Font* font = NULL;
static unsigned short* screen_px = NULL;
static unsigned short keymap[8];
static BOOL initialized = FALSE;

static const char keynames[8][11][6] = {
	{ "ret",   "enter", "space",  "(-)",   "Z",     ".",     "Y",     "0",     "X",     "on",     "theta" },
	{ ",",     "+",     "W",      "3",     "V",     "2",     "U",     "1",     "T",     "e^x",    "pi"    },
	{ "?",     "-",     "S",      "6",     "R",     "5",     "Q",     "4",     "P",     "10^x",   "EE"    },
	{ ":",     "*",     "O",      "9",     "N",     "8",     "M",     "7",     "L",     "x^2",    "i"     },
	{ "\"",    "/",     "K",      "tan",   "J",     "cos",   "I",     "sin",   "H",     "^",      ">"     },
	{ "'",     "cat",   "G",      ")",     "F",     "(",     "E",     "var",   "D",     "shift",  "<"     },
	{ "flag",  "click", "C",      "home",  "B",     "menu",  "A",     "esc",   "|",     "tab",    ""      },
	{ "up",    "u+r",   "right",  "r+d",   "down",  "d+l",   "left",  "l+u",   "del",   "ctrl",   "="     }
};

struct sdltondls_key {
	const int sdl;
	const t_key* ndls;
};

static const struct sdltondls_key key_translation[] = {
	{ SDLK_0, &KEY_NSPIRE_0},
	{ SDLK_1, &KEY_NSPIRE_1},
	{ SDLK_2, &KEY_NSPIRE_2},
	{ SDLK_3, &KEY_NSPIRE_3},
	{ SDLK_4, &KEY_NSPIRE_4},
	{ SDLK_5, &KEY_NSPIRE_5},
	{ SDLK_6, &KEY_NSPIRE_6},
	{ SDLK_7, &KEY_NSPIRE_7},
	{ SDLK_8, &KEY_NSPIRE_8},
	{ SDLK_9, &KEY_NSPIRE_9},

	{ SDLK_a, &KEY_NSPIRE_A},
	{ SDLK_b, &KEY_NSPIRE_B},
	{ SDLK_c, &KEY_NSPIRE_C},
	{ SDLK_d, &KEY_NSPIRE_D},
	{ SDLK_e, &KEY_NSPIRE_E},
	{ SDLK_f, &KEY_NSPIRE_F},
	{ SDLK_g, &KEY_NSPIRE_G},
	{ SDLK_h, &KEY_NSPIRE_H},
	{ SDLK_i, &KEY_NSPIRE_I},
	{ SDLK_j, &KEY_NSPIRE_J},
	{ SDLK_k, &KEY_NSPIRE_K},
	{ SDLK_l, &KEY_NSPIRE_L},
	{ SDLK_m, &KEY_NSPIRE_M},
	{ SDLK_n, &KEY_NSPIRE_N},
	{ SDLK_o, &KEY_NSPIRE_O},
	{ SDLK_p, &KEY_NSPIRE_P},
	{ SDLK_q, &KEY_NSPIRE_Q},
	{ SDLK_r, &KEY_NSPIRE_R},
	{ SDLK_s, &KEY_NSPIRE_S},
	{ SDLK_t, &KEY_NSPIRE_T},
	{ SDLK_u, &KEY_NSPIRE_U},
	{ SDLK_v, &KEY_NSPIRE_V},
	{ SDLK_w, &KEY_NSPIRE_W},
	{ SDLK_x, &KEY_NSPIRE_X},
	{ SDLK_y, &KEY_NSPIRE_Y},
	{ SDLK_z, &KEY_NSPIRE_Z},

	{ SDLK_BACKSPACE, &KEY_NSPIRE_DEL },
	{ SDLK_RETURN, &KEY_NSPIRE_ENTER },
	{ SDLK_LSHIFT, &KEY_NSPIRE_SHIFT },
	{ SDLK_LCTRL, &KEY_NSPIRE_CTRL },
	{ SDLK_ESCAPE, &KEY_NSPIRE_ESC },

	{ SDLK_DOWN, &KEY_NSPIRE_DOWN },
	{ SDLK_UP, &KEY_NSPIRE_UP },
	{ SDLK_LEFT, &KEY_NSPIRE_LEFT },
	{ SDLK_RIGHT, &KEY_NSPIRE_RIGHT },
	{ 0, NULL }
};

static unsigned int nio_sdl_callback(unsigned int interval, void* param);
static void nio_sdl_update(void);
static void nio_sdl_renderTexture(SDL_Texture* tex, int x, int y);
static void nio_sdl_print(int x, int y, char* text);
static void nio_sdl_printf(int x, int y, const char* format, ...);

static int nio_sdl_main(void* data) {
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("Nspire I/O", 100, 100, 550, SCREEN_HEIGHT + 160, 0);
	if(window == NULL)
		exit_with_error(__FUNCTION__,"window is null");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL)
		exit_with_error(__FUNCTION__,"renderer is null");

	TTF_Init();
	font = TTF_OpenFont("OpenSans-Regular.ttf",12);
	if(font == NULL)
		exit_with_error(__FUNCTION__,"could not open font");

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

	memset(keymap, 0xFFFF, sizeof(short) * 8);
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
				//printf("Physical %s -> %s\n",SDL_GetScancodeName(ev.key.keysym.scancode),SDL_GetKeyName(ev.key.keysym.sym));
				int i;
				for(i = 0; key_translation[i].ndls != NULL; i++) {
					if(ev.key.keysym.sym == key_translation[i].sdl) {
						if(ev.key.state == SDL_RELEASED)
							keymap[(key_translation[i].ndls->row / 2) - 0x8] |= key_translation[i].ndls->col;
						else
							keymap[(key_translation[i].ndls->row / 2) - 0x8] &= ~(key_translation[i].ndls->col);
					}
				}
			}
			else if(ev.type == SDL_MOUSEBUTTONDOWN || ev.type == SDL_MOUSEBUTTONUP) {
				if(ev.button.button == SDL_BUTTON_LEFT && ev.button.y - SCREEN_HEIGHT >= 0) {
					int row, col;
					row = (ev.button.y - SCREEN_HEIGHT) / 20;
					col = ev.button.x / 50;
					if(ev.button.state == SDL_RELEASED)
						keymap[row] |= 1 << col;
					else
						keymap[row] &= ~(1 << col);
				}
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
	memset(screen_px,0xFFFF,SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(short));
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
	for(i = 0; i < 8; i++) {
		if(keymap[i] != 0xFFFF)
			return TRUE;
	}
	return FALSE;
}

#undef isKeyPressed
BOOL isKeyPressed(const t_key* key) {
	return ~(*(keymap + (key->row / 2) - 0x8)) & key->col;
}
#define isKeyPressed(x) isKeyPressed(&x)

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

static void nio_sdl_renderTexture(SDL_Texture* tex, int x, int y) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(renderer, tex, NULL, &dst);
}

static void nio_sdl_print(int x, int y, char* text)  {
	SDL_Color c = {0, 0, 0};
	SDL_Surface* f = TTF_RenderText_Blended(font, text, c);
	SDL_Texture* t = SDL_CreateTextureFromSurface(renderer, f);

	SDL_FreeSurface(f);
	nio_sdl_renderTexture(t, x, y);
	SDL_DestroyTexture(t);
}

static void nio_sdl_printf(int x, int y, const char* format, ...) {
	char buffer[200];
	va_list args;
	va_start(args, format);
	vsnprintf(buffer, 200, format, args);
	nio_sdl_print(x, y, buffer);
	va_end(args);
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

static void nio_sdl_drawKeymap(void) {
	int i, j;
	for(j = 0; j < 8; j++) {
		for(i = 0; i <= 10; i++) {
			SDL_Rect r;
			r.x = i * 50;
			r.y = SCREEN_HEIGHT + j * 20;
			r.w = 50;
			r.h = 20;
			t_key k;
			k.row = 0x10 + 2*j;
			k.col = 1 << i;
			if(isKeyPressed(k))
				SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			else
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderFillRect(renderer, &r);
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			nio_sdl_printf(i*50, SCREEN_HEIGHT + j * 20, "%s", keynames[j][i]);
		}
	}
}

void nio_sdl_update(void) {
	SDL_UpdateTexture(screen, NULL, screen_px, SCREEN_WIDTH * sizeof(short));
	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect r;
	r.x = 0;
	r.y = 0;
	r.w = SCREEN_WIDTH;
	r.h = SCREEN_HEIGHT;
	SDL_RenderCopy(renderer, screen, NULL, &r);
	nio_sdl_drawKeymap();
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

	if(isKeyPressed(KEY_NSPIRE_ESC)) return 0;

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
	if(isKeyPressed(KEY_NSPIRE_EE))		return shiftKey('&','%');
	if(isKeyPressed(KEY_NSPIRE_ENTER))		return shiftKey('\n','~');

	// Special chars
	if(isKeyPressed(KEY_NSPIRE_DEL))		return '\b';
	if(isKeyPressed(KEY_NSPIRE_RET))		return '\n';
	if(isKeyPressed(KEY_NSPIRE_TAB))		return '\t';

	return 0;
}
