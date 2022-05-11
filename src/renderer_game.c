#include <stdio.h>
#include <SDL2/SDL.h>
#include "state.h"
#include <SDL2/SDL2_gfxPrimitives.h>



// To do: the most upper function of this game, entry in main

void renderer_game(SDL_Renderer *renderer,int grid_width,int grid_height,int *grid_matrix){

}

// To do: renderer background of gof due to the file input
int renderer_game_background(SDL_Renderer *renderer,SDL_Color *color,game_state game,int grid_width,int grid_height,int slice)
{
    
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, SDL_ALPHA_OPAQUE);
    // Draw vertical lines 
    for(int i=0;i<slice;i++){
        printf("%d\n",i*grid_width);
        SDL_RenderDrawLine(renderer,i*grid_width,0,i*grid_width,GRID_HEIGHT);
    }

}

/*To do: render the current upper layer due  g_m is a adjacent matrix comprises 0 and 1, handled by the parser
renderer or not is controled by game state
*/
 
int renderer_next_layer(SDL_Renderer *renderer,int *grid_matrix){

}
