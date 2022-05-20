#include <stdio.h>
#include <SDL2/SDL.h>
#include "state.h"
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <unistd.h>

// To do: the most upper function of this game, entry in main

// To do: renderer background of gof due to the file input
void renderer_game_background(SDL_Renderer *renderer, SDL_Color *color, game_state *game)
{
    // slice stands for the size of the grid
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, SDL_ALPHA_OPAQUE);
    // Draw vertical lines
    for (int i = 1; i < game->grid_width; i++)
    {
        SDL_RenderDrawLine(renderer, i * game->slice_size, 0, i * game->slice_size, GRID_HEIGHT);
    }
    // Draw hor lines

    for (int i = 1; i <= game->grid_height; i++)
    {
        SDL_RenderDrawLine(renderer, 0, i * game->slice_size, WINDOW_WIDTH, i * game->slice_size);
    }
}

/*To do: render the current upper layer due  g_m is a adjacent matrix comprises 0 and 1, handled by the parser
renderer or not is controled by game state
*/

void renderer_next_layer(SDL_Renderer *renderer, int **grid_matrix, game_state *game)
{
    for (int i = 0; i < game->grid_height; i++)
    {
        for (int j = 0; j < game->grid_width; j++)
        {
            if (*(*(grid_matrix + i) + j) == 1)
            {
                SDL_SetRenderDrawColor(renderer, 255, 216, 158, SDL_ALPHA_OPAQUE);
                SDL_Rect fillRect = {.h = game->slice_size,
                                     .w = game->slice_size,
                                     .y = i * game->slice_size,
                                     .x = j * game->slice_size};

                SDL_RenderFillRect(renderer, &fillRect);
            }
        }
    }
}



void renderer_text(SDL_Renderer *renderer, game_state *game, TTF_Font *font, TTF_Font *font_instrc)
{
    SDL_Color fg = {212, 227, 240};
    int _to_be_con = game->game_epoch;
    char tmp[30] = "";
    sprintf(tmp, "%d", _to_be_con);
    char gen[100] = "Generation ";
    strcat(gen, tmp);
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, gen, fg);
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_Rect text_pos = {.x = 50, .y = 720, .w = text_surface->w, .h = text_surface->h};
    SDL_FreeSurface(text_surface);
    SDL_Surface *text_surface_instrc = TTF_RenderText_Solid(font_instrc, "HIT W TO START  S TO PAUSE ", fg);
    SDL_Texture *text_texture_x = SDL_CreateTextureFromSurface(renderer, text_surface_instrc);
    SDL_Rect text_pos_x = {.x = 400, .y = 710, .w = text_surface_instrc->w, .h = text_surface_instrc->h};
    SDL_FreeSurface(text_surface_instrc);
    SDL_RenderCopy(renderer, text_texture, NULL, &text_pos);
    SDL_RenderCopy(renderer, text_texture_x, NULL, &text_pos_x);
}

// void renderer_text_information(game_state game,SDL_Renderer *renderer,)

void renderer_game(int **grid_matrix, SDL_Renderer *renderer, SDL_Color *color, game_state *game, int grid_width, int grid_height, int slice)
{
    renderer_game_background(renderer, color, game);
    renderer_next_layer(renderer, grid_matrix, game);
}
