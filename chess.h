#ifndef CHESS_H
#define CHESS_H

#include <ncurses.h>
#include <stdlib.h>

static const int BOARD_SIZE = 8;
static const int BOARD_CELLS = BOARD_SIZE * BOARD_SIZE;

typedef enum piece_type_e {
  KING   = 'K',
  QUEEN  = 'Q',
  BISHOP = 'B',
  KNIGHT = 'H',
  ROOK   = 'R',
  PAWN   = 'p',
} piece_type_t;

typedef enum color_e {
  BLACK = 'b',
  WHITE = 'w',
} color_t;

typedef struct piece_s {

} piece_t;

typedef struct cell_s {
  piece_t *piece;
  int threatened: 1;
} cell_t;

typedef struct board_s {
  union {
    cell_t vector[BOARD_CELLS];
    cell_t matrix[BOARD_SIZE][BOARD_SIZE];
  } grid;
  color_t turn;
} board_t;

board_t *board_create(void);
void board_free(board_t *board);

#endif // !CHESS_H
