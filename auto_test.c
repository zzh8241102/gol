// Tutorial on https://blog.csdn.net/benkaoya/article/details/95870801 and https://blog.csdn.net/benkaoya/article/details/95887879 which introduced the cunit API
#include <stdio.h>
#include <string.h>
#include "./include/CUnit/Basic.h"
#include "auto_test.h"

static int suite_init(void)
{
    return 0;
}

static int suite_clean(void)
{
    return 0;
}

static void test_calculate(void)
{
    int **nx;
    nx = (int **)malloc(TEST_HEIGHT_1 * sizeof(int *));
    for (int m = 0; m < TEST_HEIGHT_1; m++)
    {
        nx[m] = (int *)malloc(TEST_WIDTH_1 * sizeof(int));
    }
    for (int i = 0; i < TEST_HEIGHT_1; i++)
    {
        for (int j = 0; j < TEST_WIDTH_1; j++)
        {
            *(*(nx + i) + j) = 0;
        }
    }
    int **nx_2;
    nx_2 = (int **)malloc(TEST_HEIGHT_2 * sizeof(int *));
    for (int m = 0; m < TEST_HEIGHT_2; m++)
    {
        nx_2[m] = (int *)malloc(TEST_WIDTH_2 * sizeof(int));
    }
    for (int i = 0; i < TEST_HEIGHT_2; i++)
    {
        for (int j = 0; j < TEST_WIDTH_2; j++)
        {
            *(*(nx_2 + i) + j) = 0;
        }
    }
    CU_ASSERT_PTR_NOT_NULL(calculate_the_next_layer(nx, TEST_WIDTH_1, TEST_HEIGHT_1));
    CU_ASSERT_PTR_NOT_NULL(calculate_the_next_layer(nx_2, TEST_WIDTH_2, TEST_HEIGHT_2));
    CU_ASSERT_PTR_NOT_EQUAL(calculate_the_next_layer(nx, TEST_WIDTH_1, TEST_HEIGHT_1), calculate_the_next_layer(nx_2, TEST_WIDTH_2, TEST_HEIGHT_2))
    CU_ASSERT_PTR_EQUAL(calculate_the_next_layer(nx, TEST_WIDTH_1, TEST_HEIGHT_1), calculate_the_next_layer(nx, TEST_WIDTH_1, TEST_HEIGHT_1))
    CU_ASSERT_PTR_EQUAL(calculate_the_next_layer(nx_2, TEST_WIDTH_2, TEST_HEIGHT_2), calculate_the_next_layer(nx_2, TEST_WIDTH_2, TEST_HEIGHT_2))
}
static void test_IO_INPUT(void)
{
    game_state game;
    char buf[100] = "";
    char buf_2[] = "# The speed/delay of the game process recommanded value 10/20/40/60";
    char buf_3[] = "grid_size = small";
    char buf_4[] = "grid_size = big";
    char buf_5[] = "game_pace = 20";
    char buf_6[] = "x,y = 11,12";
    // Test their side effects as well
    CU_ASSERT_EQUAL(file_parser_init(buf, &game), 0);
    CU_ASSERT_EQUAL(file_parser_init(buf_2, &game), 0);
    CU_ASSERT_EQUAL(file_parser_init(buf_3, &game), 0);
    CU_ASSERT_EQUAL(game.grid_height, GRID_HEIGHT / SMALL_SLICE);
    CU_ASSERT_EQUAL(file_parser_init(buf_4, &game), 0);
    CU_ASSERT_EQUAL(game.grid_height, GRID_HEIGHT / BIGGER_SLICE);
    CU_ASSERT_NOT_EQUAL(game.game_pace, 20);
    CU_ASSERT_EQUAL(file_parser_init(buf_5, &game), 0);
    CU_ASSERT_EQUAL(game.game_pace, 20);
    CU_ASSERT_EQUAL(file_parser_init(buf_6, &game), 0);
    CU_ASSERT_PTR_NOT_NULL(game.grid);
    init_without_file(&game);
    CU_ASSERT_EQUAL(game.game_pace,20);
    CU_ASSERT_EQUAL(game.grid_height,35);
    CU_ASSERT_EQUAL(game.grid_width,50);

    // Test their side effects
}
static void test_IO_OUTPUT(void)
{
    game_state game;
    CU_ASSERT_EQUAL(write_result(&game), -1);
    char buf_4[] = "grid_size = big";
    file_parser_init(buf_4, &game);
    // use side effects
    CU_ASSERT_NOT_EQUAL(write_result(&game), 0);
}
static void test_bg(void){
    // GUI is not visiable,so just use the logic
    int cnt_x = 0;
    int cnt_y = 0;
    game_state game;
    init_without_file(&game);
     for (int i = 1; i < game.grid_width; i++)
    {
       cnt_x+=1;
    }
    for (int i = 1; i <= game.grid_height; i++)
    {
        cnt_y+=1;
    }
    CU_ASSERT_NOT_EQUAL(cnt_x,game.grid_width);
    CU_ASSERT_EQUAL(cnt_y,game.grid_height);
}
static void test_layer(void){
    // GUI is not visiable,so just use the logic
    game_state game;
    init_without_file(&game);
    CU_ASSERT_PTR_NOT_NULL(game.grid);
    CU_ASSERT_EQUAL(game.game_pace,20);

}
int main()
{
    /// VAULE SPCACE FOR TEST_1
    int **nx;
    nx = (int **)malloc(TEST_HEIGHT_1 * sizeof(int *));
    for (int m = 0; m < TEST_HEIGHT_1; m++)
    {
        nx[m] = (int *)malloc(TEST_WIDTH_1 * sizeof(int));
    }
    for (int i = 0; i < TEST_HEIGHT_1; i++)
    {
        for (int j = 0; j < TEST_WIDTH_1; j++)
        {
            *(*(nx + i) + j) = 0;
        }
    }

    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
    {
        return CU_get_error();
    }

    /* add a suite to the registry */
    pSuite = CU_add_suite("suite_FOR_calculation", suite_init, suite_clean);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "test_for_next_generation", test_calculate)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_pSuite pSuite2 = NULL;
    pSuite2 = CU_add_suite("suite_FOR_IO", suite_init, suite_clean);
    if (NULL == pSuite2)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ((NULL == CU_add_test(pSuite2, "test_for_IO_INPUT", test_IO_INPUT)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ((NULL == CU_add_test(pSuite2, "test_for_IO_OUTPUT", test_IO_OUTPUT)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_pSuite pSuite3 = NULL;
    pSuite3 = CU_add_suite("suite_FOR_RENDER", suite_init, suite_clean);
    if (NULL == pSuite3)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ((NULL == CU_add_test(pSuite3, "test_for_RENDERER_BACKGROUND", test_bg)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ((NULL == CU_add_test(pSuite3, "test_for_RENDERER_NEXT_LAYER", test_layer)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();


    /* Clean up registry and return */
    CU_cleanup_registry();
    return CU_get_error();
}
int **calculate_the_next_layer(int **grid_matrix, int grid_width, int grid_height)
{
    // reversed x,y
    // int nx[grid_height][grid_height];

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
                if (*(*(grid_matrix + x) + y) == 1 && *(*(grid_matrix + x) + y) == *(*(grid_matrix + dx) + dy))
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
                *(*(grid_matrix + x) + y) = 1;
            }
            if (reproduct_counter == 3)
            {
                *(*(grid_matrix + x) + y) = 1;
            }
            life_counter = 0;
            reproduct_counter = 0;
        }
    }
    return grid_matrix;
}
int file_parser_init(char *df, game_state *game)
{
    game->init_x = 0;
    game->init_y = 0;
    char tmp[100];
    if (sscanf(df, " %s", tmp) == EOF)
        return 0;
    if (sscanf(df, " %[#]", tmp) == 1)
        return 0;
    if (sscanf(df, "game_pace = %d", &game->game_pace) == 1)
    {
        // printf("game pace %d\n", game->game_pace);
        return 0;
    }

    if (sscanf(df, "grid_size = %s", game->grid_notion) == 1)
    {

        if (strcmp("big", game->grid_notion) == 0)
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
        return -1;
    }
    game->game_epoch = 0;
    return 0;
}

void init_without_file(game_state *game)
{
    game->slice_size = SMALL_SLICE;
    game->grid_height = GRID_HEIGHT / SMALL_SLICE;
    game->grid_width = WINDOW_WIDTH / SMALL_SLICE;

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

int write_result(game_state *game)
{
    FILE *fp;
    fp = fopen("./io_files/res.txt", "w");
    if (fp == NULL)
    {   
        return -1;
    }
    if(game->grid_height==0||game->grid_width==0){
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

