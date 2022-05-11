#include <stdio.h>
#include <SDL2/SDL.h>
#include "state.h"
#include <SDL2/SDL2_gfxPrimitives.h>
#include <unistd.h>

// To do: the most upper function of this game, entry in main

void renderer_game(SDL_Renderer *renderer, int grid_width, int grid_height, int *grid_matrix)
{
}

// To do: renderer background of gof due to the file input
void renderer_game_background(SDL_Renderer *renderer, SDL_Color *color, game_state game, int grid_width, int grid_height, int slice)
{
    // slice stands for the size of the grid

    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, SDL_ALPHA_OPAQUE);
    // Draw vertical lines
    for (int i = 1; i < grid_width; i++)
    {
        SDL_RenderDrawLine(renderer, i * slice, 0, i * slice, GRID_HEIGHT);
    }
    // Draw hor lines

    for (int i = 1; i <= grid_height; i++)
    {
        SDL_RenderDrawLine(renderer, 0, i * slice, WINDOW_WIDTH, i * slice);
    }
}

/*To do: render the current upper layer due  g_m is a adjacent matrix comprises 0 and 1, handled by the parser
renderer or not is controled by game state
*/

void renderer_next_layer(SDL_Renderer *renderer, int **grid_matrix, int grid_width, int grid_height, int slice)
{
    for (int i = 0; i < grid_height; i++)
    {
        for (int j = 0; j < grid_width; j++)
        {
            if (*(*(grid_matrix + i) + j) == 1)
            {   
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_Rect fillRect = {.h = slice,
                                     .w = slice,
                                     .y = i * slice,
                                     .x = j * slice};
                printf("(%d,%d)\n\n",i * slice,j * slice);

                SDL_RenderFillRect(renderer, &fillRect);
                // rectangleRGBA(renderer,(i) * slice,(j-1)*slice,(i+1) * slice,j*slice,0,238,238,0);
                
            }
        }
        
        
    }
}
