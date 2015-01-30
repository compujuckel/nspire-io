#include "../../include/nspireio/platform-x86.h"

void wait_no_key_pressed(void) {
	while(any_key_pressed())
		idle();
}

