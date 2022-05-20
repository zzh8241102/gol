#ifndef RENDERER_GAME_HEADER_H
#define RENDERER_GAME_HEADER_H
#include <SDL2/SDL_ttf.h>

void renderer_game_background(SDL_Renderer *renderer, SDL_Color *color, game_state *game);
void renderer_next_layer(SDL_Renderer *renderer, int **grid_matrix, game_state *game);
void renderer_text(SDL_Renderer *renderer,game_state *game,TTF_Font* font,TTF_Font *font_instrc);
void renderer_game(int **grid_matrix, SDL_Renderer *renderer, SDL_Color *color, game_state *game);

#endif