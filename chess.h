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

/**
 * enum color_e - the colors of the board pieces.
 *
 */
typedef enum color_e {
  BLACK = 'b',
  WHITE = 'w',
} color_t;

/**
 * struct point_s - represents a single point.
 *
 * @x: x position of the point.
 * @y: y position of the point.
 */
typedef struct point_s {
  int x;
  int y;
} point_t;

/**
 * struct piece_s - represents a chess piece.
 *
 */
typedef struct piece_s {
  piece_type_t type;
  color_t color;
  point_t pos;
  unsigned int moves_num;
  struct piece_s *king;
} piece_t;

/**
 * struct cell_s: represents a single cell on the board.
 *
 * @piece: an optional contained piece.
 * @threatened: whether the cell is threatened by a piece or not.
 */
typedef struct cell_s {
  piece_t *piece;
  int threatened: 1;
} cell_t;


/**
 * struct board_s - represents the whole chess board.
 *
 * @grid: represents either a vector a matrix of cells of the board.
 * @turn: the current turn.
 * @moves_num: total moved so far.
 * @king_north: the at the north of the board.
 * @king_south: the at the south of the board.
 * @check_piece: the foe piece checking the king of the current player.
 */
typedef struct board_s {
  union {
    cell_t vector[g_BOARD_CELLS];
    cell_t matrix[g_BOARD_SIZE][g_BOARD_SIZE];
  } grid;
  color_t turn;
  unsigned int moves_num;
  piece_t *king_north;
  piece_t *king_south;
  piece_t *check_piece;
} board_t;


board_t *board_create(void);
void board_print(board_t *board);
void board_show(board_t *board);
void board_free(board_t *board);

#endif // !CHESS_H
