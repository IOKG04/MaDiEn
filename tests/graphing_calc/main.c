/************************************************\
|       Just a very bad graphing calculator      |
|                                                |
| Licensed under WTFPL, available at             |
| LICENSES/WTFPL                                 |
\************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "madien/display.h"
#include "madien/buffer.h"
#include "madien/buffer_strutils.h"

#define EQUATIONS (10)

#define SE_W_DASH  ((screen_element_t){'-', 0xff, 0xff, 0xff})
#define SE_W_PIPE  ((screen_element_t){'|', 0xff, 0xff, 0xff})
#define SE_W_PLUS  ((screen_element_t){'+', 0xff, 0xff, 0xff})
#define SE_W_CARET ((screen_element_t){'^', 0xff, 0xff, 0xff})
#define SE_W_GREAT ((screen_element_t){'>', 0xff, 0xff, 0xff})

#define SE_G_DASH  ((screen_element_t){'-', 0xa0, 0xa0, 0xa0})
#define SE_G_PIPE  ((screen_element_t){'|', 0xa0, 0xa0, 0xa0})
#define SE_G_PLUS  ((screen_element_t){'+', 0xa0, 0xa0, 0xa0})

#define SE_DG_DOT  ((screen_element_t){'.', 0x40, 0x40, 0x40})

#define SE_NR_TEMP ((screen_element_t){' ', 0xff, 0xff, 0xff})
#define SE_SE_TEMP ((screen_element_t){' ', 0xff, 0xff, 0xff})
#define SE_EQ_TEMP ((screen_element_t){' ', 0xc0, 0xc0, 0xc0})
#define SE_OF_TEMP ((screen_element_t){' ', 0xa0, 0xa0, 0xa0})
#define SE_TT_TEMP ((screen_element_t){' ', 0xa0, 0xa0, 0xa0})

#define SE_GRAPH_UR ((screen_element_t[2]){(screen_element_t){'/', 0xc0, 0xc0, 0xc0}, (screen_element_t){'/', 0xff, 0xff, 0xff}})
#define SE_GRAPH_DR ((screen_element_t[2]){(screen_element_t){'\\', 0xc0, 0xc0, 0xc0}, (screen_element_t){'\\', 0xff, 0xff, 0xff}})
#define SE_GRAPH_ST ((screen_element_t[2]){(screen_element_t){'-', 0xc0, 0xc0, 0xc0}, (screen_element_t){'-', 0xff, 0xff, 0xff}})

typedef struct{
    double a,
           b;
    int active;
} equation_t;

int cfloor(double d){
    int outp = d;
    return outp - (d < 0 ? 1 : 0);
}

int main(){
    setup_screen(MDE_DTUI | MDE_DTRUECOLOR);

    // initializing buffers
    ebuffer_t final      = {},
              eq_panel   = {},
              graphs     = {};

    if(eb_init(&final, 80, 25) ||
       eb_init(&eq_panel, 19, 23) ||
       eb_init(&graphs, 60, 23)){
        revert_screen();
        exit(1);
    }

    int inp,
        zooml = 4, // chars per integer position; smaller -> more zoomed
        selected_eq = 0;

    equation_t equations[EQUATIONS] = {};
    equations[0] = (equation_t){1, 0, 1};

    while(1){
        eb_clear(&final, SE_SPACE);
        eb_clear(&eq_panel, SE_SPACE);
        eb_clear(&graphs, SE_DG_DOT);

        // draw coordinate system
        for(int uy = 0; uy < 23; ++uy){
            int y = 23 - uy - 1;
            if(y % zooml == 0){
                // ind line
                char ycoord[12] = {};
                sprintf(ycoord, "%i", y / zooml);
                for(int x = 1; x < 60; ++x){
                    eb_set(&graphs, x, uy, SE_G_DASH);
                }
                eb_str_put(&graphs, ycoord, 0, uy, strlen(ycoord), MDE_SDEFAULT, SE_NR_TEMP);
            }
            else{
                if(uy != 0) eb_set(&graphs, 0, uy, SE_W_PIPE);
                else        eb_set(&graphs, 0, uy, SE_W_CARET);
            }
        }
        for(int x = 1; x < 60; ++x){
            if(x % zooml == 0){
                // ind line
                char xcoord[12] = {};
                sprintf(xcoord, "%i", x / zooml);
                for(int y = 0; y < 22; ++y){
                    switch(eb_get(graphs, x, y).c){
                        case '-':
                            eb_set(&graphs, x, y, SE_G_PLUS);
                            break;
                        case '.':
                            eb_set(&graphs, x, y, SE_G_PIPE);
                            break;
                        default:
                            break;
                    }
                }
                eb_str_put(&graphs, xcoord, x, 22, strlen(xcoord), MDE_SDEFAULT, SE_NR_TEMP);
                x += strlen(xcoord) - 1;
            }
            else{
                if(x != 59) eb_set(&graphs, x, 22, SE_W_DASH);
                else        eb_set(&graphs, x, 22, SE_W_GREAT);
            }
        }
        // draw equations (text)
        for(int i = 0; i < EQUATIONS; ++i){
            char eq_text[20] = {};
            sprintf(eq_text, "y%i = %.2fx + %.2f", (i + 1) % 10, equations[i].a, equations[i].b);
            eb_str_put(&eq_panel, eq_text, 0, 2 + i * 2, strlen(eq_text), MDE_SDEFAULT, equations[i].active ? (i == selected_eq ? SE_SE_TEMP : SE_EQ_TEMP) : SE_OF_TEMP);
            if(!equations[i].active) continue;
            for(int x = 1; x < 60; ++x){
                int miny = 22 - cfloor(((x - 0.5) / (double)zooml * equations[i].a + equations[i].b) * zooml);
                int maxy = 22 - cfloor(((x + 0.5) / (double)zooml * equations[i].a + equations[i].b) * zooml);
                if(equations[i].a > 0){
                    int t = miny;
                    miny = maxy;
                    maxy = t;
                }
                for(int y = miny; y < maxy || y == miny; ++y){
                    if(y == 22) continue;
                    if(equations[i].a >= 1)       eb_set(&graphs, x, y, SE_GRAPH_UR[i == selected_eq]);
                    else if(equations[i].a <= -1) eb_set(&graphs, x, y, SE_GRAPH_DR[i == selected_eq]);
                    else                          eb_set(&graphs, x, y, SE_GRAPH_ST[i == selected_eq]);
                }
            }
        }

        eb_str_put(&eq_panel,
            "GRAPHING CALCULATOR",
            0, 0, 0, MDE_SDEFAULT, SE_NR_TEMP);

        eb_draw(&final, eq_panel, 0, 0, MDE_BDEFAULT);
        eb_draw(&final, graphs, 20, 0, MDE_BDEFAULT);

        eb_str_put(&final,
            "1-0: select equation; v: toggle visibility; a, b: set a or b; +/-: zoom; q: quit",
            0, 24, 0, MDE_SDEFAULT, SE_TT_TEMP);

        eb_print(final, 0, 0);

        inp = getchar();
        char inpbuf[9] = {};
        switch(inp){
            case 'q':
                goto CLOSE;
                break;
            case '1':
                selected_eq = 0;
                equations[selected_eq].active = 1;
                break;
            case '2':
                selected_eq = 1;
                equations[selected_eq].active = 1;
                break;
            case '3':
                selected_eq = 2;
                equations[selected_eq].active = 1;
                break;
            case '4':
                selected_eq = 3;
                equations[selected_eq].active = 1;
                break;
            case '5':
                selected_eq = 4;
                equations[selected_eq].active = 1;
                break;
            case '6':
                selected_eq = 5;
                equations[selected_eq].active = 1;
                break;
            case '7':
                selected_eq = 6;
                equations[selected_eq].active = 1;
                break;
            case '8':
                selected_eq = 7;
                equations[selected_eq].active = 1;
                break;
            case '9':
                selected_eq = 8;
                equations[selected_eq].active = 1;
                break;
            case '0':
                selected_eq = 9;
                equations[selected_eq].active = 1;
                break;
            case 'v':
                equations[selected_eq].active = !equations[selected_eq].active;
                selected_eq = 0;
                for(int i = 0; i < EQUATIONS; ++i){
                    if(!equations[i].active) continue;;
                    selected_eq = i;
                    break;
                }
                break;
            case '-':
                ++zooml;
                break;
            case '+':
                --zooml;
                if(zooml < 1) zooml = 1;
                break;
            case 'a':
                for(int i = 0; i < 8 && (inp = getchar()) != '\n'; ++i){
                    inpbuf[i] = inp;
                }
                equations[selected_eq].a = strtod(inpbuf, NULL);
                break;
            case 'b':
                for(int i = 0; i < 8 && (inp = getchar()) != '\n'; ++i){
                    inpbuf[i] = inp;
                }
                equations[selected_eq].b = strtod(inpbuf, NULL);
                break;
        }
    }

CLOSE:
    eb_free(&final);
    eb_free(&eq_panel);
    eb_free(&graphs);
    revert_screen();
    return 0;
}
