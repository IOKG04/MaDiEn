/************************************************\
|      Prints bold and normal '#' character      |
|                                                |
| Licensed under WTFPL, available at             |
| LICENSES/WTFPL                                 |
\************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "madien/display.h"
#include "madien/buffer.h"

int main(){
    setup_screen(MDE_DTUI | MDE_DNCLEAR);
    ebuffer_t buf = {};
    if(eb_init(&buf, 1, 1)){
        revert_screen();
        exit(1);
    }
    eb_clear(&buf, (screen_element_t){'#'});

    do{
        eb_print(buf, 0, 0);

        set_flags_screen(get_flags_screen() ^ MDE_DBOLD);
        reset_screen();
    } while(getchar() != 'q');

    eb_free(&buf);
    revert_screen();
}
