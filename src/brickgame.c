/**
 * @file brickgame.c
 * @author kossadda (https://github.com/kossadda)
 * @brief 
 * @version 1.0
 * @date 2024-04-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "./gui/cli/include/common_gui.h"

static void game_loop(game_t *g);

int main() {
  game_t game; 

  init_screen();
  init_game(&game);
  print_field();
  refresh_field(&game.gi);

  game_loop(&game);
  
  endwin();

  return 0;
}

static void game_loop(game_t *g) {
  UserAction_t action = ' ';
  double last_update_time = current_time();

  while (1) {
    action = getch();
    if(g->gi.pause == Pause) {
      
      continue;
    } else if(g->gi.pause == Terminate) {
      break;
    } else {
      user_input(action, g, &last_update_time, 0);
      refresh_field(&g->gi);
      refresh();
    }
    napms(1);
  }
}