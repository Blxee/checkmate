#ifndef CHESS_H
#define CHESS_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


#define g_BOARD_SIZE 8
#define g_BOARD_CELLS (g_BOARD_SIZE * g_BOARD_SIZE)


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

/**
 * struct piece - represents a chess piece.
 *
 * @type: 
 *
 */
typedef struct piece_s {
  piece_type_t type;
  color_t color;
  unsigned int moves_num;
} piece_t;

typedef struct cell_s {
  piece_t *piece;
  int threatened: 1;
} cell_t;

typedef struct board_s {
  union {
    cell_t vector[g_BOARD_CELLS];
    cell_t matrix[g_BOARD_SIZE][g_BOARD_SIZE];
  } grid;
  color_t turn;
  unsigned int moves_num;
} board_t;


board_t *board_create(void);
void board_print(board_t *board);
void board_show(board_t *board);
void board_free(board_t *board);

#endif // !CHESS_H
