#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "state.h"
#include "renderer_game.h"
#include "logic.h"

// Advanced ->interactive
// Advanced ->playback

SDL_Color GRID_COLOR_SLOW = {.r = 255,
                             .g = 255,
                             .b = 255};

SDL_Color GRID_COLOR_QUICK = {.r = 255,
                              .g = 187,
                              .b = 255};

int main(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Initialize error,could not initialize sdl2:%s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    // Create window

    SDL_Window *window = SDL_CreateWindow("Conway's Game of Life",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH,
                                          WINDOW_HEIGHT,
                                          SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        fprintf(stderr, "Cannot create window due to %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // create a renderer

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
                                                SDL_RENDERER_ACCELERATED |
                                                    SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        SDL_DestroyWindow(window);
        fprintf(stderr, "Cannot create renderer due to %s\n", SDL_GetError());
    }

    // Initialize the game state && structures

    // To_be_M

    game_state game;

    game.g_state = STATE_RUN;
        int **nx;
        nx = (int **)malloc(35 * sizeof(int *));
        for (int m = 0; m < 35; m++)
        {
            nx[m] = (int *)malloc(50 * sizeof(int));
        }
        for (int i = 0; i < 35; i++)
        {
        for (int j = 0; j < 50; j++)
        {
            *(*(nx+i)+j) = 0;
        }
        *(*(nx+1)+49) = 1;
        *(*(nx+2)+49) = 1;
        *(*(nx+3)+49) = 1;
        *(*(nx+1)+48) = 1;
        }

    int **cl = NULL;
    int cnt_cl = 0;
    // Event loop
    SDL_Event event;
    while (game.g_state != STATE_QUIT)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                game.g_state = STATE_QUIT;
                break;
            }
        }
        /*renderer --> An init render by parser, then listen for the click on the start button && end button also can acclrt(NOTICE THE PROIR OF PARSER OR LISTEN) -> STOP is used to end the game quickly
         */

        SDL_SetRenderDrawColor(renderer, 190, 190, 190, 255);
        SDL_RenderClear(renderer);
        renderer_game_background(renderer, &GRID_COLOR_SLOW, game, WINDOW_WIDTH / SMALL_SLICE, GRID_HEIGHT / SMALL_SLICE, SMALL_SLICE); // 加到结构体
        SDL_RenderPresent(renderer);
        nx = calculate_the_next_layer(nx,50,35);
        cnt_cl++;
        if(cnt_cl%2!=0){
        cl = nx;
        }
        // for(int i=0;i<35;i++){
        //     for(int j=0;j<50;j++){
        //         printf("%d",*(*(nx+i)+j));
        //         if(j+1==50){
        //             printf("\n");
        //         }
                
        //     }
        // }
        //    break;
        // renderer 
        
        if(cnt_cl%2==0){
        for(int i=0;i<35;i++)
            free(cl[i]);
        free(cl);
        cl =NULL;
        }
        
        SDL_Delay(1000/60);      
    }
    if(!cl){
        for(int i=0;i<35;i++)
            free(cl[i]);
        free(cl);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
