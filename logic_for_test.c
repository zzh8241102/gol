#include <stdio.h>

// Given by parser(file)/click event to listen to the grid -> calculate the current_ ->renderer the current

// calculate the current upper layer

// void calculate_the_next_layer(int **grid_matrix,int grid_width,int grid_height){

//
int main()
{
    int grid_matrix[35][50];
    for (int i = 0; i < 35; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            grid_matrix[i][j] = 0;
            printf("%d",grid_matrix[i][j]);
        }
    }

    grid_matrix[1][0] =1;
    grid_matrix[1][1] =1;
    grid_matrix[2][0] =1;
    grid_matrix[3][0] =1;


    printf("\n\n");

    int grid_height = 35;
    int grid_width = 50;
    int nx[35][50];
    for(int i =0;i<35;i++){
        for(int j=0;j<50;j++){
            nx[i][j]=0;
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
                if (dx < 0 || dy < 0 || dx > grid_height || dx > grid_width || dy > grid_width || dy > grid_height)
                {
                    continue;
                }
                if (grid_matrix[x][y] == 1 && grid_matrix[x][y] == grid_matrix[dx][dy])
                {
                    life_counter++;
                }
                if (grid_matrix[x][y] == 0 && grid_matrix[dx][dy] == 1)
                {
                    reproduct_counter++;
                }
            }
            if (life_counter == 2 || life_counter == 3)
            {
                nx[x][y] = 1;
                
            }
            if (reproduct_counter == 3)
            {
                nx[x][y] = 1;
                
            }
            life_counter = 0;
            reproduct_counter = 0;
        }
    }
    for (int k = 0; k < grid_height; k++)
    {
        for (int l = 0; l < grid_width; l++)
        {
            if (nx[k][l] != 1)
            {
                nx[k][l] = 0;
            }
        }
    }

    for (int i = 0; i < 35; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            printf("%d", nx[i][j]);
            if(j+1==50){
                printf("\n");
            }
        }
    }
}
// calculate_the_next_layer(test_arr,50,35);
