#ifndef RENDERER_GAME_HEADER_H
#define RENDERER_GAME_HEADER_H

void renderer_game_background(SDL_Renderer *renderer, SDL_Color *color, game_state *game, int grid_width, int grid_height, int slice);
void renderer_next_layer(SDL_Renderer *renderer, int **grid_matrix, int grid_width, int grid_height, int slice);
void renderer_game(int **grid_matrix, SDL_Renderer *renderer, SDL_Color *color, game_state *game, int grid_width, int grid_height, int slice);
void renderer_clicked(int **grid_matrix, SDL_Renderer *renderer, game_state *game, int grid_width, int grid_height, int slice, int x, int y);
#endif