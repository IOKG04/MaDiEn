#include "madien/display.h"

int main(){
    setup_screen(10, 10);

    for(int x = 0; x < 10; x += 2){
	for(int y = 0; y < x; ++y){
	    set_element(x, y, (screen_element_t){'#'});
	}
    }
    draw_screen();

    revert_screen();
}
