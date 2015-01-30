#include "../../include/nspireio/platform-x86.h"

extern SDL_mutex* screen_px_lock;
extern unsigned short* screen_px;

void clrscr(void) {
	SDL_LockMutex(screen_px_lock);
	memset(screen_px,0xFFFF,SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(short));
	SDL_UnlockMutex(screen_px_lock);
}

