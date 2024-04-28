/**
 * @file init.c
 * @author kossadda (https://github.com/kossadda)
 * @brief 
 * @version 1.0
 * @date 2024-04-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "./../include/common.h"
#include <time.h>

void init_game(Game *game) {
  srand(time(NULL));

  game->info.field = (int **)calloc(ROW, sizeof(int *));
  for(int i = 0; i < ROW; i++) {
    game->info.field[i] = (int *)calloc(COL, sizeof(int));
  }

  game->info.next = (int **)calloc(2, sizeof(int *));
  for(int i = 0; i < 2; i++) {
    game->info.next[i] = (int *)calloc(4 * BLOCK_SIZE, sizeof(int));
  }

  set_high_score(&game->info);
  game->info.score = 0;
  game->info.level = 0;
  game->info.speed = 0;
  game->info.speed = 0;
  game->cursor.x = 0;
  game->cursor.y = 0;
  game->current = random(BLOCK_CNT);
  
  fill_next_block(game);
}

int random(int max) {
  return rand() % max;
}

void set_high_score(GameInfo_t *info) {
  char *filename = "score.txt";
  char path[strlen(__FILE__) + 1];
  strcpy(path, __FILE__);
  char *last_slash_ptr = strrchr(path, '/');
  *(++last_slash_ptr) = '\0';
  char path_score[strlen(path) + strlen(filename) + 1];
  sprintf(path_score, "%s%s", path, filename);

  FILE *f_score = fopen(path_score, "rw");
  char str_score[15];

  if(fgets(str_score, 15, f_score)) {
    info->high_score = atoi(str_score);
  } else {
    info->high_score = 0;
  }

  if(f_score) {
    fclose(f_score);
  }
}