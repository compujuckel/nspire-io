#include "../../include/nspireio/platform-x86.h"

extern unsigned short keymap[8];

BOOL any_key_pressed(void) {
	int i;
	for(i = 0; i < 8; i++) {
		if(keymap[i] != 0xFFFF)
			return TRUE;
	}
	return FALSE;
}
