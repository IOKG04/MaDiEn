/************************************************\
|      Prints bold and normal '#' character      |
|                                                |
| Licensed under WTFPL, available at             |
| LICENSES/WTFPL                                 |
\************************************************/

#include <stdlib.h>
#include "madien/display.h"
#include "madien/buffer.h"
#include "madien/buffer_strutils.h"

int main(){
    setup_screen(MDE_DTUI);

    ebuffer_t buf,
              sbuf;
    if(eb_init(&buf, 16, 8) ||
       eb_init(&sbuf, 16, 1)){
        revert_screen();
        exit(1);
    }

    eb_clear(&buf, (screen_element_t){'.'});

    char *str = "Hello world!";

    eb_clear(&sbuf, SE_NULL);
    eb_str_put(&sbuf, str, 0, 0, 0, MDE_SDEFAULT, SE_SPACE);
    eb_draw(&buf, sbuf, 0, 0, MDE_BDEFAULT);

    eb_clear(&sbuf, SE_NULL);
    eb_str_put(&sbuf, str, 0, 0, 0, MDE_SDEFAULT | MDE_SREPLACE, SE_SPACE);
    eb_draw(&buf, sbuf, 0, 1, MDE_BDEFAULT);

    eb_clear(&sbuf, SE_NULL);
    eb_str_put(&sbuf, str, 0, 0, 14, MDE_SDEFAULT | MDE_SREPLACE, SE_SPACE);
    eb_draw(&buf, sbuf, 0, 2, MDE_BDEFAULT);

    eb_clear(&sbuf, SE_NULL);
    eb_str_put(&sbuf, str, 0, 0, 8, MDE_SDEFAULT, SE_SPACE);
    eb_draw(&buf, sbuf, 0, 3, MDE_BDEFAULT);

    eb_clear(&sbuf, SE_NULL);
    eb_str_put(&sbuf, str, 8, 0, 0, MDE_SDEFAULT, SE_SPACE);
    eb_draw(&buf, sbuf, 0, 4, MDE_BDEFAULT);

    eb_clear(&sbuf, SE_NULL);
    eb_str_put(&sbuf, str, -4, 0, 0, MDE_SDEFAULT, SE_SPACE);
    eb_draw(&buf, sbuf, 0, 5, MDE_BDEFAULT);

    eb_clear(&sbuf, SE_NULL);
    eb_str_put(&sbuf, str, -4, 0, 8, MDE_SDEFAULT, SE_SPACE);
    eb_draw(&buf, sbuf, 0, 6, MDE_BDEFAULT);

    eb_str_put(&buf, str, 0, 7, 0, MDE_SDEFAULT, SE_SPACE);
    eb_print(buf, 0, 0);

    revert_screen();
}
