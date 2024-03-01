#include "chess.h"

board_t *board_create(void) {
  board_t *board = (board_t *)malloc(sizeof(*board));
  int i;

  if (board == NULL)
    return NULL;

  for (i = 0; i < BOARD_CELLS; i++)
    board->grid.vector[i] = NULL;

  return board;
}
