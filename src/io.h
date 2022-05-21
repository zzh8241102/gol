#ifndef IO__GUARD__H
#define IO__GUARD__H
int file_parser_init(char *df, game_state *game);
int write_result(game_state *game);
void init_without_file(game_state *game);

#endif