
// Thanks to https://blog.csdn.net/benkaoya/article/details/95870801 and https://blog.csdn.net/benkaoya/article/details/95887879 which introduced the cunit API 
#include <stdio.h>
#include <string.h>
#include "./include/CUnit/"
#include "./src/state.h"



int file_parser_init(char *df, game_state *game){
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

static int suite_init(void)
{
    return 0;
}

static int suite_clean(void)
{
    return 0;
}

static void test_sum(void)
{
    CU_ASSERT_EQUAL(sum(1, 2), 3);
    CU_ASSERT_EQUAL(sum(5, 2), 7);
}

int main()
{
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    /* add a suite to the registry */
    pSuite = CU_add_suite("suite_input", suite_init, suite_clean);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "test_input", test_sum))) {
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
