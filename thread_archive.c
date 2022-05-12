#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_thread.h>
#include "state.h"
#include "renderer_game.h"
#include "logic.h"

// Advanced ->interactive
// Advanced ->playback
typedef struct {
  int par1;
  int par2;

} ThreadData;

int done = 0;
int threadFunction( void* data)

{
    ThreadData *tdata = data;
    int param1 = tdata->par1;
    int param2 = tdata->par2;
    SDL_Color GRID_COLOR_QUICK = {.r = 255,
                              .g = 187,
                              .b = 255};

    printf("%d %d",param1,param2);
    //Print incoming data
    // renderer_game_background(renderer,&GRID_COLOR_QUICK,game,50,35,20);
    // printf( "Running thread with value = %d\n", (int)data );
  
    return 0;
}

SDL_Color GRID_COLOR_SLOW = {.r = 255,
                             .g = 255,
                             .b = 255};

SDL_Color GRID_COLOR_QUICK = {.r = 255,
                              .g = 187,
                              .b = 255};

SDL_Color RECT_BLUE = {
    .r = 0,
    .g = 238,
    .b = 238,
};

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
    game.grid_height = 35;
    game.grid_width = 50;
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
            *(*(nx + i) + j) = 0;
        }
        *(*(nx + 1) + 25) = 1;
        *(*(nx + 2) + 25) = 1;
        *(*(nx + 3) + 25) = 1;
        *(*(nx + 1) + 24) = 1;
        *(*(nx + 10) + 32) = 1 ; 
        *(*(nx + 10)+ 33) = 1 ;
        *(*(nx + 11)+ 32) = 1 ; 
        *(*(nx + 21) + 32) = 1 ; 
        *(*(nx + 21)+ 33) = 1 ;
        *(*(nx + 21)+ 34) = 1 ; 
         *(*(nx + 24) + 32) = 1 ; 
        *(*(nx + 25)+ 33) = 1 ;
        *(*(nx + 21)+ 34) = 1 ; 
        *(*(nx + 24) + 32) = 1 ; 
         *(*(nx + 31) + 32) = 1 ; 
        *(*(nx + 29)+ 33) = 1 ;
        *(*(nx + 31)+ 34) = 1 ; 
        *(*(nx + 12)+ 33) = 1 ;
        *(*(nx + 13)+ 32) = 1 ; 
        *(*(nx + 14) + 32) = 1 ; 
        *(*(nx + 12)+ 33) = 1 ;
        *(*(nx + 12)+ 32) = 1 ; 
        *(*(nx + 13) + 34) = 1 ; 
        *(*(nx + 12)+ 34) = 1 ;
        *(*(nx + 17)+ 32) = 1 ; 
        *(*(nx + 19) + 32) = 1 ; 
        *(*(nx + 16)+ 33) = 1 ;
        *(*(nx + 18)+ 32) = 1 ; 
         *(*(nx + 21) + 11) = 1 ; 
        *(*(nx + 21)+ 12) = 1 ;
        *(*(nx + 21)+ 6) = 1 ; 
         *(*(nx + 21) + 7) = 1 ; 
        *(*(nx + 21)+ 8) = 1 ;
        *(*(nx + 20)+ 8) = 1 ; 


    }

    int **cl = NULL;
    int cnt_cl = 0;
    // Event loop

    SDL_DisplayMode displayMode;
    SDL_GetWindowDisplayMode(window, &displayMode);
    uint16_t SCREEN_REFRESH_INTERVAL = (uint16_t)(1000.0 / displayMode.refresh_rate - 1);
    // int data = 10;
    ThreadData *data = malloc(sizeof(ThreadData));
    
    while (done!=1)
    {     SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                // game.g_state = STATE_QUIT;
                done = 1;
                break;
            }
        }

        /*renderer --> An init render by parser, then listen for the click on the start button && end button also can acclrt(NOTICE THE PROIR OF PARSER OR LISTEN) -> STOP is used to end the game quickly
         */
        data->par1 =1;
        data->par2 =100;
        SDL_Thread *ts = SDL_CreateThread(threadFunction,"Test",(void*)data);
        SDL_SetRenderDrawColor(renderer, 190, 190, 190, 255);
        SDL_RenderClear(renderer);
        // renderer_game_background(renderer, &GRID_COLOR_SLOW, game, WINDOW_WIDTH / SMALL_SLICE, GRID_HEIGHT / SMALL_SLICE, SMALL_SLICE); // 加到结构体 // renderer once
        nx = calculate_the_next_layer(nx, 50, 35);
        // renderer_next_layer(renderer,nx,50,35,SMALL_SLICE);
        renderer_game(nx,renderer,&GRID_COLOR_SLOW,game,50,35,20);
        SDL_RenderPresent(renderer);
        cnt_cl++;
         if (cnt_cl % 2 != 0)
        {
            cl = nx;
        }
        else if (cnt_cl % 2 == 0)
        {
            for (int i = 0; i < 15; i++)
                free(cl[i]);
            free(cl);
            cl = NULL;
        }
        
        // SDL_Delay(SCREEN_REFRESH_INTERVAL);

    }
    // if (!cl)
    // {
    //     for (int i = 0; i < 35; i++)
    //         free(cl[i]);

    //     free(cl);
    // }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
