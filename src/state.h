#ifndef STATE_HEADER_H
#define STATE_HEADER_H

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 768
#define MENU_HEIGHT 68
#define GRID_HEIGHT 700
#define SMALL_SLICE 20
#define BIGGER_SLICE 10

// Small size /20
// Bigger size /10

#define STATE_QUIT 0
#define STATE_RUN 1



                                    
// fake data to test before implement io operation

// The number of grid --> backgroud


typedef struct _state
{
    int g_state;
    int grid_width;
    int grid_height;

} game_state;



#endif