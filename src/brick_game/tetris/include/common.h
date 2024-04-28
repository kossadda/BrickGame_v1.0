/**
 * @file common.h
 * @author kossadda (https://github.com/kossadda)
 * @brief 
 * @version 1.0
 * @date 2024-04-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef COMMON_H
#define COMMON_H

#include "./fsm.h"
#include "./objects.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 3
#define COL 10 * BLOCK_SIZE
#define ROW 20

void init_game(Game *game);
void set_high_score(GameInfo_t *info);
int random(int max);

void fill_next_block(Game *game);

#endif // COMMON_H