/************************************************\
|       Buffers types and related functions      |
|                                                |
| Copyright (c) 2024, https://github.com/IOKG04  |
| Licensed under MIT-Festival-Light (at LICENSE) |
\************************************************/

#ifndef MDE_BUFFER_H__
#define MDE_BUFFER_H__

#include <stddef.h>

// screen_element_t with empty space
#define SE_SPACE ((screen_element_t){' '})
// screen_element_t containing no data
#define SE_NULL  ((screen_element_t){'\0'})

// returns 1 if e is null equivalent
#define SE_IS_NULL(e) (e.c == '\0')

// element in a screen buffer
typedef struct{
    char  c;
} screen_element_t;

// buffer containing screen_element_t
typedef struct{
    screen_element_t *data;
    size_t            width,
                      height;
} ebuffer_t;

// initializes buf to size {width, height}
int eb_init(ebuffer_t *buf, size_t width, size_t height);
// deinitialized members of buf
void eb_free(ebuffer_t *buf);

// sets element in buf at {x, y} to e
int eb_set(ebuffer_t *buf, size_t x, size_t y, screen_element_t e);
// sets all elements in buf to e
void eb_clear(ebuffer_t *buf, screen_element_t e);

// prints buf to terminal, such that {0, 0} in buf space is at {offs_x, offs_y} in terminal space (zero based)
void eb_draw(ebuffer_t buf, int offs_x, int offs_y);

#endif
