#include "../../include/nspireio/platform-x86.h"

void wait_key_pressed(void) {
	wait_no_key_pressed();
	while(!any_key_pressed())
		idle();
}

