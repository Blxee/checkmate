#include "chess.h"

int g_MAX_COLS, g_MAX_ROWS;

int main(void)
{
  WINDOW *stdscr = initscr();
  int inp;
  board_t *board;

  srand(time(NULL));
  board = board_create();

  cbreak();
  noecho();
  raw();
  keypad(stdscr, 1);
  start_color();
  curs_set(0);

  getmaxyx(stdscr, g_MAX_COLS, g_MAX_ROWS);

  board_show(board);
  refresh();

  // while ((inp = getch())) addch(inp);
  getch();
  endwin();

  board_print(board);
  return (0);
}
