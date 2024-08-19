#include <stdlib.h>
#include "madien/display.h"
#include "madien/buffer.h"

int main(){
    setup_screen();

    ebuffer_t buf = {};
    if(eb_init(&buf, 20, 10)){
        exit(1);
    }

    eb_clear(&buf, SE_SPACE);
    for(int x = 0; x < 20; x += 2){
        for(int y = 0; y < x / 2 + 1; ++y){
            if(eb_set(&buf, x, y, (screen_element_t){'#'})){
                revert_screen();
                exit(1);
            }
        }
    }
    eb_draw(buf, 0, 0);

    revert_screen();
}
