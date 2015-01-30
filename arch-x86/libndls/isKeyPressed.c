#include "../../include/nspireio/platform-x86.h"
#include "ndless-sdk/include/keys.h"

extern unsigned short keymap[8];

#undef isKeyPressed
BOOL isKeyPressed(const t_key* key) {
	return ~(*(keymap + (key->row / 2) - 0x8)) & key->col;
}
