#include "chess.h"

extern int g_MAX_COLS;
extern int g_MAX_ROWS;

static const char *const g_BOARD_INIT[] = {
  "wRwHwBwKwQwBwHwR",
  "wpwpwpwpwpwpwpwp",
  "                ",
  "                ",
  "                ",
  "                ",
  "bpbpbpbpbpbpbpbp",
  "bRbHbBbKbQbBbHbR",
};


board_t *board_create(void) {
  board_t *board = (board_t *)malloc(sizeof(*board));
  int flip = rand() & 1;
  int i, j;

  if (board == NULL)
    return NULL;

  // init the cells of the board
  board->turn = (rand() & 1) ? BLACK : WHITE;
  board->moves_num = 0;
  for (i = 0; i < g_BOARD_CELLS; i++)
    board->grid.vector[i] = (cell_t){
      .piece = NULL,
      .threatened = 0,
    };

  // put the board pieces in starting position
  for (i = 0; i < g_BOARD_SIZE; i++) {
    for (j = 0;j < g_BOARD_SIZE;j++) {
      const char *tile = g_BOARD_INIT[flip ? g_BOARD_SIZE - 1 - i : i] + (j * 2);

      if (tile[1] != ' ') {
        board->grid.matrix[i][j].piece = malloc(sizeof(piece_t));
        // if not null
        *board->grid.matrix[i][j].piece = (piece_t){
          .color = tile[0],
          .type = tile[1],
          .moves_num = 0,
        };
      }
    }
  }

  return board;
}


void board_print(board_t *board) {
  int i, j, k;
  char buf[g_BOARD_CELLS * 2];

  k = 0;
  for (i = 0; i < g_BOARD_SIZE; i++) {
    for (j = 0; j < g_BOARD_SIZE; j++) {
      if (board->grid.matrix[i][j].piece)
        buf[k++] = board->grid.matrix[i][j].piece->type;
      else
        buf[k++] = '.';

      if (j != g_BOARD_SIZE - 1)
        buf[k++] = ' ';
    }
    buf[k++] = '\n';
  }

  write(STDOUT_FILENO, buf, sizeof(buf));
}


void board_show(board_t *board) {
  cell_t *cell;
  short black_bg = 0b00000001;
  short black_fg = 0b00000010;
  short white_bg = 0b00000100;
  short white_fg = 0b00001000;
  short border_color = 0b00010000;
  short fg, bg;

  init_pair(black_fg | black_bg, COLOR_BLACK, COLOR_BLUE);
  init_pair(white_fg | white_bg, COLOR_WHITE, COLOR_CYAN);
  init_pair(black_fg | white_bg, COLOR_BLACK, COLOR_CYAN);
  init_pair(white_fg | black_bg, COLOR_WHITE, COLOR_BLUE);
  init_pair(border_color, COLOR_WHITE, COLOR_BLACK);

  move(g_MAX_COLS / 2 - g_BOARD_SIZE - 1, g_MAX_ROWS / 2 - 2 * g_BOARD_SIZE - 1);
  attron(COLOR_PAIR(border_color) | A_BOLD);
  for (int i = 0; i < 2 * g_BOARD_SIZE + 1; i++)
    addstr("\u2584\u2584");

  for (int i = 0; i < g_BOARD_SIZE; i++) {
    move(g_MAX_COLS / 2 - g_BOARD_SIZE + i * 2, g_MAX_ROWS / 2 - 2 * g_BOARD_SIZE - 1);
    attron(COLOR_PAIR(border_color));
    addstr("\u2588");

    for (int j = 0; j < g_BOARD_SIZE; j++) {
      cell = &board->grid.matrix[i][j];
      fg = cell->piece && cell->piece->color == BLACK ? black_fg : white_fg;
      bg = (i + (j & 1)) & 1 ? black_bg : white_bg;
      attron(COLOR_PAIR(fg | bg) | A_BOLD);
      if (cell->piece)
        printw(" %c%c ",
               cell->piece->type,
               cell->piece->type);
      else
        addstr("    ");
    }

    attron(COLOR_PAIR(border_color));
    addstr("\u2588");
    move(g_MAX_COLS / 2 - g_BOARD_SIZE + i * 2 + 1, g_MAX_ROWS / 2 - 2 * g_BOARD_SIZE - 1);
    addstr("\u2588");

    for (int j = 0; j < g_BOARD_SIZE; j++) {
      cell = &board->grid.matrix[i][j];
      fg = cell->piece && cell->piece->color == BLACK ? black_fg : white_fg;
      bg = (i + (j & 1)) & 1 ? black_bg : white_bg;
      attron(COLOR_PAIR(fg | bg) | A_BOLD);
      if (cell->piece)
        addstr(" \u2580\u2580 ");
      else
        addstr("    ");
    }

    attron(COLOR_PAIR(border_color));
    addstr("█");
  }

  move(g_MAX_COLS / 2 + g_BOARD_SIZE, g_MAX_ROWS / 2 - 2 * g_BOARD_SIZE - 1);
  attron(COLOR_PAIR(border_color));
  for (int i = 0; i < 2 * g_BOARD_SIZE + 1; i++)
    addstr("\u2580\u2580");
}


int board_mvpiece(board_t *board) {

  return NULL;
}
