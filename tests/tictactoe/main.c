/************************************************\
|     A game of tictactoe between two humans     |
|                                                |
| Licensed under WTFPL, available at             |
| LICENSES/WTFPL                                 |
\************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "madien/display.h"
#include "madien/buffer.h"

#define DRAW_ROUTINE eb_clear(&b_display, (screen_element_t){'.'}); \
    eb_draw(&b_display, b_vertline, 3, 0, MDE_BDEFAULT); \
    eb_draw(&b_display, b_vertline, 7, 0, MDE_BDEFAULT); \
    eb_draw(&b_display, b_horiline, 0, 3, MDE_BDEFAULT); \
    eb_draw(&b_display, b_horiline, 0, 7, MDE_BDEFAULT); \
    for(int x = 0; x < 3; ++x){ \
        for(int y = 0; y < 3; ++y){ \
            if(board[y][x] == bs_x){ \
                eb_draw(&b_display, b_x, x * 4, y * 4, MDE_BDRAW_OVER); \
            } \
            else if(board[y][x] == bs_o){ \
                eb_draw(&b_display, b_o, x * 4, y * 4, MDE_BDRAW_OVER); \
            } \
        } \
    } \
    eb_print(b_display, 1, 1)

typedef enum{
    bs_none = 0,
    bs_draw,
    bs_o,
    bs_x,
} boardstate;
boardstate board[3][3] = {};

boardstate who_won(){
    // hori
    for(int y = 0; y < 3; ++y){
        if(board[y][0] != bs_none && board[y][0] == board[y][1] && board[y][0] == board[y][2]) return board[y][0];
    }
    // vert
    for(int x = 0; x < 3; ++x){
        if(board[0][x] != bs_none && board[0][x] == board[1][x] && board[0][x] == board[2][x]) return board[0][x];
    }
    // diags
    if(board[0][0] != bs_none && board[0][0] == board[1][1] && board[0][0] == board[2][2]) return board[0][0];
    if(board[0][2] != bs_none && board[0][2] == board[1][1] && board[0][2] == board[2][0]) return board[0][0];
    // draw
    if(board[0][0] != bs_none && board[0][1] != bs_none && board[0][2] != bs_none &&
       board[1][0] != bs_none && board[1][1] != bs_none && board[1][2] != bs_none &&
       board[2][0] != bs_none && board[2][1] != bs_none && board[2][2] != bs_none) return bs_draw;
    // no win yet
    return bs_none;
}

int main(){
    setup_screen(MDE_DTUI | MDE_DCURSOR);

    // initialize buffers
    ebuffer_t b_display,
              b_x,
              b_o,
              b_vertline,
              b_horiline;
    if(eb_init(&b_display, 11, 11) ||
       eb_init(&b_x, 3, 3) ||
       eb_init(&b_o, 3, 3) ||
       eb_init(&b_vertline, 1, 16) ||
       eb_init(&b_horiline, 16, 1)){
        revert_screen();
        exit(1);
    }

    // draw "sprites" to buffers
    eb_set(&b_x, 0, 0, (screen_element_t){'X'});
    eb_set(&b_x, 2, 0, (screen_element_t){'X'});
    eb_set(&b_x, 1, 1, (screen_element_t){'X'});
    eb_set(&b_x, 0, 2, (screen_element_t){'X'});
    eb_set(&b_x, 2, 2, (screen_element_t){'X'});
    eb_set(&b_o, 0, 0, (screen_element_t){'O'});
    eb_set(&b_o, 1, 0, (screen_element_t){'O'});
    eb_set(&b_o, 2, 0, (screen_element_t){'O'});
    eb_set(&b_o, 0, 1, (screen_element_t){'O'});
    eb_set(&b_o, 2, 1, (screen_element_t){'O'});
    eb_set(&b_o, 0, 2, (screen_element_t){'O'});
    eb_set(&b_o, 1, 2, (screen_element_t){'O'});
    eb_set(&b_o, 2, 2, (screen_element_t){'O'});
    eb_clear(&b_vertline, (screen_element_t){'|'});
    eb_clear(&b_horiline, (screen_element_t){'-'});

    int tt = 0;
    boardstate winner = bs_none;
    do{
        DRAW_ROUTINE;

        // get user input
        printf("\n\n%c's turn. Where do you place (numpad)? ", (tt % 2) == 0 ? 'X' : 'O');
        int c = getchar();
        switch(c){
            case '1': board[2][0] = (tt % 2) == 0 ? bs_x : bs_o; break;
            case '2': board[2][1] = (tt % 2) == 0 ? bs_x : bs_o; break;
            case '3': board[2][2] = (tt % 2) == 0 ? bs_x : bs_o; break;
            case '4': board[1][0] = (tt % 2) == 0 ? bs_x : bs_o; break;
            case '5': board[1][1] = (tt % 2) == 0 ? bs_x : bs_o; break;
            case '6': board[1][2] = (tt % 2) == 0 ? bs_x : bs_o; break;
            case '7': board[0][0] = (tt % 2) == 0 ? bs_x : bs_o; break;
            case '8': board[0][1] = (tt % 2) == 0 ? bs_x : bs_o; break;
            case '9': board[0][2] = (tt % 2) == 0 ? bs_x : bs_o; break;
        }

        ++tt;
    } while((winner = who_won()) == bs_none);

    reset_screen();

    DRAW_ROUTINE;

    if(winner == bs_draw) printf("\n\nA draw... guess you too are too good\nor bad\n");
    else printf("\n\n%c won!\n", (--tt % 2) == 0 ? 'X' : 'O');

    eb_free(&b_display);
    eb_free(&b_x);
    eb_free(&b_o);
    eb_free(&b_vertline);
    eb_free(&b_horiline);
    revert_screen();
}
