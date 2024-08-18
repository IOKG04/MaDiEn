#include "display.h"

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "config.h"

// data for old termios
struct termios old_termios;

// gets the index if a pixel in buffer space
static inline size_t s_get_index(size_t x, size_t y);


/******************\
| PUBLIC FUNCTIONS |
\******************/

// initializes buffer and terminal
void setup_screen(){
    // set termios
    tcgetattr(fileno(stdin), &old_termios);
    struct termios new_termios = old_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(fileno(stdin), TCSANOW, &new_termios);

    // clear screen
    printf("\x1b[?25l\x1b[2J");

    #if LICENSING_MESSAGE
    // display MaDiEn licensing information
    #if LICENSING_MESSAGE_CHANGE == 0
    printf("\x1b[HMaDiEn Copyright (c) 2024, https://github.com/IOKG04\nThis software uses code licensed under the MIT-Festival-Light License (https://github.com/IOKG04/Licenses/blob/master/MIT-FL/MIT-Festival-Light).\n");
    #else
    printf("\x1b[HMaDiEn Copyright (c) 2024, https://github.com/IOKG04, modified by creator of this software\nThis software uses code licensed under the MIT-Festival-Light License (https://github.com/IOKG04/Licenses/blob/master/MIT-FL/MIT-Festival-Light).\n");
    #endif
    sleep(LICENSING_MESSAGE_DELAY);
    printf("\x1b[2J");
    #endif
}
// undos setup_screen()
void revert_screen(){
    // reset termios
    tcsetattr(fileno(stdin), TCSANOW, &old_termios);

    // reset screen
    printf("\x1b[?25h\x1b[0m");
}
