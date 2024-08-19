/************************************************\
|           Terminal utility functions           |
|                                                |
| Copyright (c) 2024, https://github.com/IOKG04  |
| Licensed under MIT-Festival-Light (at LICENSE) |
\************************************************/

#ifndef MDE_DISPLAY_H__
#define MDE_DISPLAY_H__

#include <stdint.h>

// sets font as bold
#define MDE_DBOLD   0b00000001
// does NOT clear screen
#define MDE_DNCLEAR 0b00000010
// shows cursor
#define MDE_DCURSOR 0b00000100
// does NOT set cursor position to {0, 0}
#define MDE_DNHOME  0b00001000

// recommended default for TUI applications
#define MDE_DTUI (0)
// recommended default for ascii graphics
#define MDE_DGRAPHICS (MDE_DBOLD)

typedef uint8_t mde_dflags_t;

// initializes terminal with given flags
void setup_screen(mde_dflags_t flags);
// sets display flags
void set_flags_screen(mde_dflags_t flags);
// returns current display flags
mde_dflags_t get_flags_screen();
// resets screen to current display flags
void reset_screen();
// undos setup_screen()
void revert_screen();

#endif
