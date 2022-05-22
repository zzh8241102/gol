#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_thread.h>
#include "state.h"
#include "renderer_game.h"
#include "logic.h"
#include "io.h"
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>

int main(int argc, char **argv)
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
    //
    SDL_Surface *surface = IMG_Load("resources/icon.png");
    SDL_SetWindowIcon(window, surface);

    // create a renderer

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
                                                SDL_RENDERER_ACCELERATED |
                                                    SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        SDL_DestroyWindow(window);
        fprintf(stderr, "Cannot create renderer due to %s\n", SDL_GetError());
    }
    if (TTF_Init() == -1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        return EXIT_FAILURE;
    }
    TTF_Font *font = TTF_OpenFont("./font/Blox2.ttf", FONT_SIZE);
    TTF_Font *font_instrc = TTF_OpenFont("./font/Koulen-Regular.ttf", 23);

    // Initialize the game state && structures

    // To_be_M

    game_state game;
    game.g_state = STATE_RUN;
    game.game_epoch = 0;
    SDL_Color GRID_COLOR_SLOW = {.r = 255,
                                 .g = 255,
                                 .b = 255};

    SDL_Color GRID_COLOR_QUICK = {.r = 255,
                                  .g = 187,
                                  .b = 255};

    char buffer[200];
    game.is_inited = 0;
    if (argc == 2)
    {
        char tp[50];
        strcpy(tp, argv[1]);
        FILE *f = fopen(tp, "r");
        if (f == NULL)
        {
            // perror("fopen return NULL");
            printf("invalid file, you will start the game with click mode.\n");
            // fclose(f);
            init_without_file(&game);
            game.game_mode = CLICK_MODE;
        }
        else
        {
            char ch = fgetc(f);
            if (strcmp(tp, "io_files/game.config") == 0 && ch != EOF)
            {
                while (fgets(buffer, sizeof(buffer), f))
                {
                    file_parser_init(buffer, &game);
                }
            }
            else
            {
                printf("invalid file, you will start the game with click mode.\n");
                // fclose(f);
                init_without_file(&game);
                game.game_mode = CLICK_MODE;
            }
        }
    }
    if (argc == 1)
    {
        init_without_file(&game);
        game.game_mode = CLICK_MODE;
    }
    if (argc != 1 && argc != 2)
    {
        printf("invalid file, you will start the game with click mode.\n");
        init_without_file(&game);
        game.game_mode = CLICK_MODE;
    }
    int **cl = NULL;
    int cnt_cl = 0;
    // Event loop
    SDL_DisplayMode displayMode;
    SDL_GetWindowDisplayMode(window, &displayMode);
    uint16_t SCREEN_REFRESH_INTERVAL = (uint16_t)(1000.0 / displayMode.refresh_rate - 1);
    while (game.g_state != STATE_QUIT)
    {
        /*renderer --> An init render by parser, then listen for the click on the start button && end button also can acclrt(NOTICE THE PROIR OF PARSER OR LISTEN) -> STOP is used to end the game quickly
         */
        SDL_SetRenderDrawColor(renderer, 140, 146, 197, 123);
        SDL_RenderClear(renderer);
        if (game.g_state == STATE_START_TO_RENDERER)
        {
            renderer_text(renderer, &game, font, font_instrc);
            game.game_epoch += 1;
            game.grid = calculate_the_next_layer(game.grid, game.grid_width, game.grid_height);
            renderer_game(game.grid, renderer, &GRID_COLOR_QUICK, &game);
            cnt_cl++;
            if (cnt_cl % MEMORY_DIV != 0)
            {
                cl = game.grid;
            }
            else if (cnt_cl % MEMORY_DIV == 0)
            {
                for (int i = 0; i < game.grid_height; i++)
                    free(cl[i]);
                free(cl);
                cl = NULL;
            }
        }
        if (game.g_state == STATE_ITERATE)
        {
            renderer_game(game.grid, renderer, &GRID_COLOR_SLOW, &game);
            renderer_text(renderer, &game, font, font_instrc);
        }
        if (game.g_state != STATE_START_TO_RENDERER && game.g_state != STATE_ITERATE)
        {
            renderer_game(game.grid, renderer, &GRID_COLOR_SLOW, &game);
            renderer_text(renderer, &game, font, font_instrc);
        }
        if (game.g_state == STATE_ONE_STEP && game.g_state != STATE_START_TO_RENDERER)
        {
            game.game_epoch += 1;
            renderer_text(renderer, &game, font, font_instrc);
            game.grid = calculate_the_next_layer(game.grid, game.grid_width, game.grid_height);
            renderer_game(game.grid, renderer, &GRID_COLOR_SLOW, &game);
            game.g_state = STATE_ITERATE;
        }
        SDL_RenderPresent(renderer);

        for (int i = 0; i < game.game_pace; i++)
        {
            SDL_Delay(SCREEN_REFRESH_INTERVAL / 5);
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    write_result(&game);
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
                    case SDL_SCANCODE_B:
                        if (game.g_state == STATE_ITERATE && game.game_pace <= 80)
                        {
                            game.game_pace += 10;
                        }
                        break;
                    case SDL_SCANCODE_X:
                        if (game.g_state == STATE_ITERATE && game.game_pace >= 20)
                        {
                            game.game_pace -= 10;
                        }
                        break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (game.g_state != STATE_START_TO_RENDERER)
                    {
                        if (event.button.x >= 0 && event.button.y <= GRID_HEIGHT && event.button.y >= 0 && event.button.x <= WINDOW_WIDTH)
                        {
                            game.game_clicked_x = (int)event.button.x;
                            game.game_clicked_y = (int)event.button.y;
                            int grid_x = (int)game.game_clicked_x / game.slice_size;
                            int grid_y = (int)game.game_clicked_y / game.slice_size;
                            if (grid_y < GRID_HEIGHT / game.slice_size && grid_x < WINDOW_WIDTH / game.slice_size)
                            {
                                if (*(*(game.grid + grid_y) + grid_x) != 1)
                                {
                                    *(*(game.grid + grid_y) + grid_x) = 1;
                                }
                                else if (*(*(game.grid + grid_y) + grid_x) == 1)
                                {
                                    *(*(game.grid + grid_y) + grid_x) = 0;
                                }
                            }
                        }
                    }
                    if (event.button.x >= 808 && event.button.x <= 928 && event.button.y >= 708 && event.button.y <= 763 && game.g_state != STATE_START_TO_RENDERER)
                    {
                        game.g_state = STATE_ONE_STEP;
                    }
                }
            }
        }
    }
    TTF_CloseFont(font);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
