/************************************************\
|               Configuration data               |
|                                                |
| Copyright (c) 2024, https://github.com/IOKG04  |
| Licensed under MIT-Festival-Light (at LICENSE) |
\************************************************/

#ifndef MDE_CONFIG_H__
#define MDE_CONFIG_H__

// whether to check that indexes are within buffer bounds
#define MDE_BUFFER_INDEX_CHECK 1

// whether to show the licensing message, for how long and whether changes were made
#define MDE_LICENSING_MESSAGE 1
#if MDE_LICENSING_MESSAGE
    #define MDE_LICENSING_MESSAGE_DELAY  1
    #define MDE_LICENSING_MESSAGE_CHANGE 0
#endif
// if you intend to disable this, make sure you include a licensing message somewhere else

// whether to draw SE_NULL as SE_SPACE
#define MDE_DRAW_NULL_AS_SPACE 0

#endif
