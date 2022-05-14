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
// single step

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
    game.game_pace = 20;
    game.slice_size =20;
    SDL_Color GRID_COLOR_SLOW = {.r = 255,
                                 .g = 255,
                                 .b = 255};

    SDL_Color GRID_COLOR_QUICK = {.r = 255,
                                  .g = 187,
                                  .b = 255};

    int **nx;
    nx = (int **)malloc(game.grid_height * sizeof(int *));
    for (int m = 0; m < game.grid_height; m++)
    {
        nx[m] = (int *)malloc(game.grid_width * sizeof(int));
    }
    for (int i = 0; i < game.grid_height; i++)
    {
        for (int j = 0; j < game.grid_width; j++)
        {
            *(*(nx + i) + j) = 0;
        }
        *(*(nx + 1) + 25) = 1;
        *(*(nx + 2) + 25) = 1;
        *(*(nx + 3) + 25) = 1;
        *(*(nx + 1) + 24) = 1;
        *(*(nx + 10) + 32) = 1;
        *(*(nx + 10) + 33) = 1;
        *(*(nx + 11) + 32) = 1;
        *(*(nx + 21) + 32) = 1;
        *(*(nx + 21) + 33) = 1;
        *(*(nx + 21) + 34) = 1;
        *(*(nx + 24) + 32) = 1;
        *(*(nx + 25) + 33) = 1;
        *(*(nx + 21) + 34) = 1;
        *(*(nx + 24) + 32) = 1;
        *(*(nx + 31) + 32) = 1;
        *(*(nx + 29) + 33) = 1;
        *(*(nx + 31) + 34) = 1;
        *(*(nx + 12) + 33) = 1;
        *(*(nx + 13) + 32) = 1;
        *(*(nx + 14) + 32) = 1;
        *(*(nx + 12) + 33) = 1;
        *(*(nx + 12) + 32) = 1;
        *(*(nx + 13) + 34) = 1;
        *(*(nx + 12) + 34) = 1;
        *(*(nx + 17) + 32) = 1;
        *(*(nx + 19) + 32) = 1;
        *(*(nx + 16) + 33) = 1;
        *(*(nx + 18) + 32) = 1;
        *(*(nx + 21) + 11) = 1;
        *(*(nx + 21) + 12) = 1;
        *(*(nx + 21) + 6) = 1;
        *(*(nx + 21) + 7) = 1;
        *(*(nx + 21) + 8) = 1;
        *(*(nx + 20) + 8) = 1;
        *(*(nx + 12) + 34) = 1;
        *(*(nx + 17) + 32) = 1;
        *(*(nx + 19) + 32) = 1;
        *(*(nx + 8) + 7) = 1;
        *(*(nx + 3) + 7) = 1;
        *(*(nx + 3) + 6) = 1;
        *(*(nx + 3) + 8) = 1;
        *(*(nx + 5) + 7) = 1;
        *(*(nx + 4) + 6) = 1;
        *(*(nx + 21) + 21) = 1;
        *(*(nx + 22) + 22) = 1;
        *(*(nx + 22) + 23) = 1;
        *(*(nx + 21) + 23) = 1;
        *(*(nx + 20) + 23) = 1;
    }

    int **cl = NULL;
    int cnt_cl = 0;
    // Event loop
    SDL_DisplayMode displayMode;
    SDL_GetWindowDisplayMode(window, &displayMode);
    uint16_t SCREEN_REFRESH_INTERVAL = (uint16_t)(1000.0 / displayMode.refresh_rate - 1);
    // int data = 10;

    while (game.g_state != STATE_QUIT)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                game.g_state = STATE_QUIT;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                     game.g_state = STATE_START_TO_RENDERER;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                     game.g_state = STATE_ITERATE;
                    break;
                }
                break;
        
            }
        }
        /*renderer --> An init render by parser, then listen for the click on the start button && end button also can acclrt(NOTICE THE PROIR OF PARSER OR LISTEN) -> STOP is used to end the game quickly
         */
        SDL_SetRenderDrawColor(renderer, 119, 136, 153, 255);
        SDL_RenderClear(renderer);
        if (game.g_state == STATE_START_TO_RENDERER)
        {
            nx = calculate_the_next_layer(nx, game.grid_width, game.grid_height);
            renderer_game(nx, renderer, &GRID_COLOR_SLOW, &game, game.grid_width, game.grid_height, game.slice_size);
            cnt_cl++;
            if (cnt_cl % 2 != 0)
            {
                cl = nx;
            }
            else if (cnt_cl % 2 == 0)
            {
                for (int i = 0; i < game.grid_height; i++)
                    free(cl[i]);
                free(cl);
                cl = NULL;
            }
        }
        if(game.g_state == STATE_ITERATE){
            renderer_game(nx, renderer, &GRID_COLOR_SLOW, &game, game.grid_width, game.grid_height, game.slice_size);
        }
        if(game.g_state!= STATE_START_TO_RENDERER && game.g_state!=STATE_ITERATE){
            renderer_game_background(renderer,&GRID_COLOR_SLOW,&game,game.grid_width,game.grid_height,game.slice_size);
        }
        SDL_RenderPresent(renderer);

        for (int i = 0; i < game.game_pace; i++)
        { 
            SDL_Delay(SCREEN_REFRESH_INTERVAL);
            SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                game.g_state = STATE_QUIT;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                     game.g_state = STATE_START_TO_RENDERER;
                    break;
                
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                     game.g_state = STATE_ITERATE;
                break;
                }
                break;
            }
        }
        }
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
