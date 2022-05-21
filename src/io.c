#include <stdio.h>
#include "state.h"
#include <string.h>
#include <stdlib.h>
// parse the .ini file and return a 2-d array comprise 0-1s
// Optional with same pre-writed model : grid
int file_parser_init(char *df, game_state *game)
{
    game->init_x = 0;
    game->init_y = 0;
    char tmp[100];
    if (sscanf(df, " %s", tmp) == EOF)
        return 0;
    if (sscanf(df, " %[#]", tmp) == 1)
        return 0;
    if (sscanf(df, "game_pace = %d", &game->game_pace) != 1)
    {
        // printf("game pace %d\n", game->game_pace);
        game->game_pace = 20;
        return 0;
    }

    if (sscanf(df, "grid_size = %s", game->grid_notion) == 1)
    {

        if (strcmp("big", game->grid_notion) == 0 && game->is_inited != 1)
        {
            game->slice_size = BIGGER_SLICE;
            game->grid_height = GRID_HEIGHT / BIGGER_SLICE;
            game->grid_width = WINDOW_WIDTH / BIGGER_SLICE;
            game->is_inited = 1;
            game->grid = (int **)malloc(game->grid_height * sizeof(int *));
            game->grid = (int **)malloc(game->grid_height * sizeof(int *));
            for (int m = 0; m < game->grid_height; m++)
            {
                game->grid[m] = (int *)malloc(game->grid_width * sizeof(int));
            }
            for (int i = 0; i < game->grid_height; i++)
            {
                for (int j = 0; j < game->grid_width; j++)
                {
                    *(*(game->grid + i) + j) = 0;
                }
            }
        
            return 0;
        }
        if (strcmp("small", game->grid_notion) == 0 && game->is_inited != 1)
        {
            game->slice_size = SMALL_SLICE;
            game->grid_height = GRID_HEIGHT / SMALL_SLICE;
            game->grid_width = WINDOW_WIDTH / SMALL_SLICE;
            game->is_inited = 1;
            game->grid = (int **)malloc(game->grid_height * sizeof(int *));
            game->grid = (int **)malloc(game->grid_height * sizeof(int *));
            for (int m = 0; m < game->grid_height; m++)
            {
                game->grid[m] = (int *)malloc(game->grid_width * sizeof(int));
            }
            for (int i = 0; i < game->grid_height; i++)
            {
                for (int j = 0; j < game->grid_width; j++)
                {
                    *(*(game->grid + i) + j) = 0;
                }
            }
            return 0;
        }
        else
        {
            game->slice_size = SMALL_SLICE;
            game->grid_height = GRID_HEIGHT / SMALL_SLICE;
            game->grid_width = WINDOW_WIDTH / SMALL_SLICE;
            game->is_inited = 1;
            game->grid = (int **)malloc(game->grid_height * sizeof(int *));
            game->grid = (int **)malloc(game->grid_height * sizeof(int *));
            for (int m = 0; m < game->grid_height; m++)
            {
                game->grid[m] = (int *)malloc(game->grid_width * sizeof(int));
            }
            for (int i = 0; i < game->grid_height; i++)
            {
                for (int j = 0; j < game->grid_width; j++)
                {
                    *(*(game->grid + i) + j) = 0;
                }
            }

            printf("config error on grid size, will use default small size \n");
        }
        return 0;
    }
    if (game->is_inited == 1)
    {
        if (sscanf(df, "x,y = %d,%d", &game->init_x, &game->init_y) == 2)
        {
            // printf("%d,%d\n",game->init_x,game->init_y);
            if (game->init_x >= game->grid_width || game->init_y >= game->grid_height || game->init_x < 0 || game->init_y < 0)
            {
                printf("invaild input in some lines, which will have no effects on the grid.\n");
                return 0;
            }
            else
            {
                *(*(game->grid + game->init_y) + game->init_x) = 1;
            }
        }
        return 0;
    }
    if (game->is_inited == 0)
    {
        game->is_inited = 1;
        game->slice_size = SMALL_SLICE;
        game->grid_height = GRID_HEIGHT / SMALL_SLICE;
        game->grid_width = WINDOW_WIDTH / SMALL_SLICE;
        game->game_pace = 20;
        game->grid = (int **)malloc(game->grid_height * sizeof(int *));
        for (int m = 0; m < game->grid_height; m++)
        {
            game->grid[m] = (int *)malloc(game->grid_width * sizeof(int));
        }
        for (int i = 0; i < game->grid_height; i++)
        {
            for (int j = 0; j < game->grid_width; j++)
            {
                *(*(game->grid + i) + j) = 0;
            }
        }
    }
    game->game_epoch = 0;
    return 0;
}

void init_without_file(game_state *game)
{  
        game->slice_size = SMALL_SLICE;
        game->grid_height = GRID_HEIGHT/SMALL_SLICE;
        game->grid_width = WINDOW_WIDTH/SMALL_SLICE;

        game->grid = (int **)malloc(game->grid_height * sizeof(int *));
        for (int m = 0; m < game->grid_height; m++)
        {
            game->grid[m] = (int *)malloc(game->grid_width * sizeof(int));
        }
         for (int i = 0; i < game->grid_height; i++)
        {
        for (int j = 0; j < game->grid_width; j++)
        {
            *(*(game->grid + i) + j) = 0;
        }
    }
    game->game_epoch = 0;
    game->game_pace = 20;

}

// write the final result to file
int write_result(game_state *game)
{
    FILE *fp;
    fp = fopen("io_files/res.txt", "w");
    if (fp == NULL)
    {
        return -1;
    }
    for (int i = 0; i < game->grid_height; i++)
    {
        for (int j = 0; j < game->grid_width; j++)
        {
            if (*(*(game->grid + i) + j) == 1)
            {
                fprintf(fp, "x,y = %d,%d\n", j, i);
            }
        }
    }
    return 0;
}