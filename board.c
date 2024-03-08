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
  board->check_piece = NULL;
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
          .pos = (point_t){.x = i, .y = j},
          .moves_num = 0,
          // .king
        };
      }

      /// set kings of north and south
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

static cell_t **s_cells_array;
cell_t **board_cells_between(board_t *board, point_t pos1, point_t pos2) {

}

static piece_t **s_pieces_array;
piece_t **board_pieces_between(board_t *board, point_t pos1, point_t pos2) {

}

int piece_set_pos(board_t *board, piece_t *piece, point_t tar) {
  cell_t *target_cell;

  if (piece == NULL)
    return 0;

  if (tar.x < 0 || tar.x >= g_BOARD_SIZE
    || tar.y < 0 || tar.y >= g_BOARD_SIZE)
    return 0;

  // empty piece position
  board->grid.matrix[piece->pos.x][piece->pos.y].piece = NULL;
  // free previous piece if any
  target_cell = &board->grid.matrix[tar.x][tar.y];
  if (target_cell->piece != NULL)
    free(target_cell->piece);
  // move piece to new position
  target_cell->piece = piece;
  piece->pos = tar;

  return 1;
}

int try_castling(board_t *board, piece_t *king, point_t tar) {
  point_t src;
  point_t rook_tar;
  int rook_x;
  piece_t *rook;

  if (board == NULL || king == NULL)
    return -1;

  src = king->pos;

  // if king has moved already
  if (king->moves_num > 0)
    return 0;

  // if target position isn't within bounds
  if (tar.y != src.y || abs(tar.x - src.x) != 2)
    return 0;

  // if rook isn't of correct type and color or has moved already
  rook_x = tar.x < src.x ? 0 : (g_BOARD_SIZE - 1);
  rook = board->grid.matrix[rook_x][src.y].piece;
  if (rook == NULL || rook->type != ROOK || rook->color != king->color || rook->moves_num > 0)
    return 0;

  // if space between is not empty
  if (board_pieces_between(board, king->pos, rook->pos))
    return 0;

  piece_set_pos(board, king, tar);
  rook_tar = (point_t){
    .x = tar.x < src.x ? tar.x + 1 : tar.x - 1,
    .y = src.y,
  };
  piece_set_pos(board, rook, rook_tar);
  return 1;
}

int try_en_passant(board_t *board, piece_t *pawn, point_t tar) {
  point_t src;
  int y_direction;
  piece_t **foe;

  if (board == NULL || pawn == NULL)
    return -1;

  src = pawn->pos;

  if (pawn->king == board->king_north)
    y_direction = 1;
  else if (pawn->king == board->king_south)
    y_direction = -1;
  else
    return -1;

  // if target pos isn't 1 to the side
  if (abs(tar.x - src.x) != 1 || tar.y - src.y != y_direction)
    return 0;

  // if foe not exists or is an ally
  foe = &board->grid.matrix[src.x][tar.y].piece;
  if (*foe == NULL || (*foe)->color == pawn->color)
    return 0;

  // if foe isn't a pawd which stepped 2 cells
  if ((*foe)->type != PAWN || /*not moved 2*/)
    return 0;

  // move to the side and take the foe
  piece_set_pos(board, pawn, tar);
  free(*foe);
  *foe = NULL;
  return 1;
}

int piece_pattern(board_t *board, piece_t *piece, point_t tar) {
  point_t src;
  piece_t *foe;
  int pawn_step, pawn_direction;

  if (piece == NULL || board == NULL)
    return -1;

  // if target position has an ally instead of a foe
  foe = board->grid.matrix[tar.x][tar.y].piece;
  if (foe != NULL && foe->color == piece->color)
    return 0;

  src = piece->pos;

  // if piece trying to move to the same place
  if (tar.x == src.x && tar.y == src.y)
    return 0;

  switch (piece->type) {
    case KING: // if threatened..
      if (try_castling(board, piece, tar) == 1)
        return 1;
      return tar.x - src.x <= 1 && tar.y - src.y <= 1;
    case QUEEN:
      return (abs(tar.x - src.x) == abs(tar.y - src.y))
          || (tar.x == src.x || tar.y == src.y);
    case BISHOP:
      return abs(tar.x - src.x) == abs(tar.y - src.y);
    case KNIGHT:
      return (abs(tar.x - src.x) == 1 && abs(tar.y - src.y) == 2)
          || (abs(tar.x - src.x) == 2 && abs(tar.y - src.y) == 1);
    case ROOK:
      return tar.x == src.x || tar.y == src.y;
    case PAWN:
      if (try_en_passant(board, piece, tar) == 1)
        return 1;
      pawn_step = piece->moves_num == 0 ? 2 : 1;
      pawn_direction = (piece->king == board->king_north) ? 1 : -1;
      return tar.x == src.x
          && (tar.y - src.y) * pawn_direction > 0
          && (tar.y - src.y) * pawn_direction <= pawn_step;
  }
  // this should not be reached normally
  return -1;
}


int piece_protecting(board_t *board, int x, int y) {
  if (board == NULL)
    return -1;

  // if piece is not threatened then it's not protecting
  if (!board->grid.matrix[x][y].threatened)
    return 0;
}


int piece_can_protect(board_t *board, int x, int y) {
  if (board == NULL)
    return -1;

}


int board_mvpiece(board_t *board) {

  return NULL;
}
