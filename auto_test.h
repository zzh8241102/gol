#ifndef STATE_HEADER_H
#define STATE_HEADER_H
#include <SDL2/SDL.h>
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 768
#define MENU_HEIGHT 68
#define GRID_HEIGHT 700
#define SMALL_SLICE 20
#define BIGGER_SLICE 10
#define MEMORY_DIV 2
#define FONT_SIZE 30
// Small size /20
// Bigger size /10

#define STATE_QUIT 0
#define STATE_RUN 1
#define STATE_START_TO_RENDERER 2
#define STATE_TO_RENDERER_BG 3
#define STATE_ITERATE 4
#define STATE_ONE_STEP 5
#define STATE_RENDER_WELCOME 6
#define FILE_MODE 0
#define CLICK_MODE 2

//////////////////////////////////////

#define TEST_HEIGHT_1 35
#define TEST_WIDTH_1 50
#define TEST_HEIGHT_2 70
#define TEST_WIDTH_2 100
#define NONE_ERROR_INDICATOR 0
#define ERROR_INDICATOR -1

// The number of grid --> backgroud

typedef struct _state
{
    int g_state;
    int grid_width;
    int grid_height;
    int slice_size; // size of grid
    int generation;
    int **grid;
    int terminator;
    int game_pace;
    int game_mode;
    int game_clicked_x;
    int game_clicked_y;
    int game_epoch;
    char grid_notion[30];
    int init_x;
    int init_y;
    int is_inited;
} game_state;


typedef struct _color
{
SDL_Color *grid_color;

}color_grid;

int **calculate_the_next_layer(int **grid_matrix, int grid_width, int grid_height);
int file_parser_init(char *df, game_state *game);
int write_result(game_state *game);
void init_without_file(game_state *game);
#endif