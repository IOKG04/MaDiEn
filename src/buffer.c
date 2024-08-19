/************************************************\
|          Implementations for buffer.h          |
|                                                |
| Copyright (c) 2024, https://github.com/IOKG04  |
| Licensed under MIT-Festival-Light (at LICENSE) |
\************************************************/

#include "buffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "config.h"

// returns 1D index for {x, y} in buf
#define eb_get_index(x, y, buf) b_get_index(x, y, buf.width)
// returns size of buf
#define b_size(buf) (buf.height * buf.width)

// returns 1D index for {x, y} in buffer with width width
static inline size_t b_get_index(size_t x, size_t y, size_t width);


/******************\
| PUBLIC FUNCTIONS |
\******************/

// initializes buf to size {width, height}
int eb_init(ebuffer_t *buf, size_t width, size_t height){
    buf->data = malloc(sizeof(screen_element_t) * b_size((*buf)));
    if(buf->data == NULL) return 1;
    buf->width = width;
    buf->height = height;
    return 0;
}
// deinitialized members of buf
void eb_free(ebuffer_t *buf){
    free(buf->data);
    buf->data = NULL;
    buf->width = 0;
    buf->height = 0;
}

// sets element in buf at {x, y} to e
int eb_set(ebuffer_t *buf, size_t x, size_t y, screen_element_t e){
    size_t i = eb_get_index(x, y, (*buf));
    #if MDE_BUFFER_INDEX_CHECK
        if(i >= buf->width * buf->height) return 1;
    #endif
    buf->data[i] = e;
    return 0;
}
// sets all elements in buf to e
void eb_clear(ebuffer_t *buf, screen_element_t e){
    for(size_t i = 0; i < b_size((*buf)); ++i){
        buf->data[i] = e;
    }
}

// prints buf to terminal, such that {0, 0} in buf space is at {offs_x, offs_y} in terminal space (zero based)
void eb_draw(ebuffer_t buf, int offs_x, int offs_y){
    for(int y = 0; y < buf.height; ++y){
        if(offs_y + y < 0) continue;
        printf("\x1b[%i;%iH", offs_y + y + 1, (offs_x <= 0 ? 1 : offs_x + 1));
        for(int x = 0; x < buf.width; ++x){
            if(offs_x + x < 0) continue;
            #if MDE_DRAW_NULL_AS_SPACE
                if(SE_IS_NULL(buf.data[x + buf.width * y])) putchar(SE_SPACE.c);
                else                                        putchar(buf.data[x + buf.width * y].c);
            #else
                putchar(buf.data[x + buf.width * y].c);
            #endif
        }
    }
}


/*******************\
| PRIVATE FUNCTIONS |
\*******************/

// returns 1D index for {x, y} in buffer with width width
static inline size_t b_get_index(size_t x, size_t y, size_t width){
    return y * width + x;
}
