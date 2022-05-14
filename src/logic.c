#include <stdio.h>
#include <stdlib.h>
#include "state.h"

// Given by parser(file)/click event to listen to the grid -> calculate the current_ ->renderer the current

// calculate the current upper layer

// void calculate_the_next_layer(int **grid_matrix,int grid_width,int grid_height){

// To do: with side effects, modify the array parsed by the parser
int **calculate_the_next_layer(int **grid_matrix, int grid_width, int grid_height)
{
    
    // int nx[grid_height][grid_height];
    int **nx;
    nx = (int **)malloc(grid_height * sizeof(int *));
    for (int m = 0; m < grid_height; m++)
    {
        nx[m] = (int *)malloc(grid_width * sizeof(int));
    }
    for (int i = 0; i < grid_height; i++)
    {
        for (int j = 0; j < grid_width; j++)
        {
            *(*(nx + i) + j) = 0;
            
        }
    }
    int dr[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
    int life_counter = 0;
    int reproduct_counter = 0;
    int dx = 0;
    int dy = 0;
    for (int x = 0; x < grid_height; x++)
    {
        for (int y = 0; y < grid_width; y++)
        {
            for (int i = 0; i < 8; i++)
            {

                dx = x + dr[i][0];
                dy = y + dr[i][1];
                if (dx < 0 || dy < 0)
                {
                    continue;
                }
                if (dy >= grid_width || dx >= grid_height)
                {

                    continue;
                }
                if (*(*(grid_matrix + x) + y) == 1 && *(*(grid_matrix + x)+ y) == *(*(grid_matrix + dx )+ dy))
                {
                    life_counter++;
                }
                if (*(*(grid_matrix + x) + y) == 0 && *(*(grid_matrix + dx) + dy) == 1)
                {
                    reproduct_counter++;
                }
            }

            if (life_counter == 2 || life_counter == 3)
            {
                *(*(nx + x) + y) = 1;
            }
            if (reproduct_counter == 3)
            {
                *(*(nx + x) + y) = 1;
            }
            life_counter = 0;
            reproduct_counter = 0;
        }
    }
    return nx;
}

int modify_the_layer(int **grid_matrix, int grid_width, int grid_height)
{
    return -1;
}

int judge_final_state(int **grid_matrix,game_state game)
{
    return -1;
}

int format_result(int **grid_matrix,game_state game){

}