#ifndef MDE_DISPLAY_H__
#define MDE_DISPLAY_H__

#include <stddef.h>

// initializes buffer and terminal
void setup_screen();
// undos setup_screen()
void revert_screen();

#endif
