/**
 * @file field_gui.c
 * @author kossadda (https://github.com/kossadda)
 * @brief The module contains functions for initializing and redrawing the main
 * playing field
 * @version 1.0
 * @date 2024-04-30
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./../include/common_gui.h"

static void init_main_field(int rows, int cols);

/// @brief Initializing the main window
void init_screen() {
  initscr();
  raw();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  start_color();
  init_color(COLOR_ORANGE, 1000, 500, 0);
  init_color(COLOR_PINK, 1000, 500, 1000);
  init_pair(WHITE, COLOR_BLACK, COLOR_WHITE);
  init_pair(BLACK, COLOR_WHITE, COLOR_BLACK);
  change_theme(BLACK);
}

/**
 * @brief Initializing full rendering of the playing field
 *
 * @param[in] g main structure
 * @param[in] act game state
 */
void init_all_game_fields(const game_t *g, UserAction_t act) {
  refresh_field(g);
  clear();
  char high_score[25];
  sprintf(high_score, "High score: %d", g->info.high_score);

  attron(A_BOLD);

  if (act == Start) {
    print_info(LEVEL_ROW + (SCORE_ROW - LEVEL_ROW) / 2 - 1, BEGIN_INFO_COL,
               END_INFO_COL, "Level: 1");
    print_info(SCORE_ROW + (HSCORE_ROW - SCORE_ROW) / 2 - 1, BEGIN_INFO_COL,
               END_INFO_COL, "Score: 0");
  }
  print_info(HSCORE_ROW + (BLOCK_ROW - HSCORE_ROW) / 2 - 1, BEGIN_INFO_COL,
             END_INFO_COL, high_score);
  print_info(BLOCK_ROW, BEGIN_INFO_COL, END_INFO_COL, "Next figure: ");

  if (g->theme == BLACK) {
    attron(COLOR_PAIR(BLUE));
  }

  init_main_field(PRINT_ROW, PRINT_COL);
  init_info_field(LEVEL_ROW, SCORE_ROW - 1, BEGIN_INFO_COL, END_INFO_COL);
  init_info_field(SCORE_ROW, HSCORE_ROW - 1, BEGIN_INFO_COL, END_INFO_COL);
  init_info_field(HSCORE_ROW, BLOCK_ROW - 1, BEGIN_INFO_COL, END_INFO_COL);
  init_info_field(BLOCK_ROW, PRINT_ROW, BEGIN_INFO_COL, END_INFO_COL);

  attroff(A_BOLD | COLOR_PAIR(BLUE));
  refresh_next_block(g);
}

/**
 * @brief Drawing the main field
 *
 * @param[in] rows number of rows
 * @param[in] cols number of cols
 */
static void init_main_field(int rows, int cols) {
  mvaddch(RCENTER, CCENTER + 0, ACS_ULCORNER);
  mvaddch(RCENTER, CCENTER + cols, ACS_URCORNER);
  mvaddch(RCENTER + rows, CCENTER, ACS_LLCORNER);
  mvaddch(RCENTER + rows, CCENTER + cols, ACS_LRCORNER);

  for (int i = 1; i < cols; i++) {
    mvaddch(RCENTER, CCENTER + i, ACS_HLINE);
    mvaddch(RCENTER + rows, CCENTER + i, ACS_HLINE);
  }

  for (int i = 1; i < rows; i++) {
    mvaddch(RCENTER + i, CCENTER, ACS_VLINE);
    mvaddch(RCENTER + i, CCENTER + cols, ACS_VLINE);
  }
}

/**
 * @brief Update field relative to installed cells
 *
 * @param[in] g main structure
 */
void refresh_field(const game_t *g) {
  char ch;

  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < COL; j++) {
      if (FIELD(i, j)) {
        if (j % SIZE == 0) {
          ch = '[';
        } else if (j % SIZE == SIZE - 1) {
          ch = ']';
        } else {
          ch = '#';
        }
        color_attribut(FIELD(i, j), 1);
        mvaddch(RCENTER + i + 1, CCENTER + j + 1, ch);
        color_attribut(FIELD(i, j), 0);
      } else {
        mvaddch(RCENTER + i + 1, CCENTER + j + 1, ' ');
      }
    }
  }
}