#ifndef LIBNDLS_X86_H
#define LIBNDLS_X86_H

void clrscr(void);
void idle(void);
void wait_key_pressed(void); // blocks until a key is pressed
void wait_no_key_pressed(void); // blocks until all keys are released
BOOL any_key_pressed(void); // non-blocking, TRUE if any key pressed
BOOL isKeyPressed(const t_key* key);
#define isKeyPressed(x) isKeyPressed(&x)

#endif
