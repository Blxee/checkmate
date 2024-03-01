#include "chess.h"

static int MAX_COLS, MAX_ROWS;
static const int BOARD_SIZE = 8;

void show_board() {
  init_pair(1, COLOR_BLACK, COLOR_BLUE);
  init_pair(2, COLOR_WHITE, COLOR_CYAN);
  init_pair(3, COLOR_WHITE, COLOR_BLACK);

  move(MAX_COLS / 2 - 9, MAX_ROWS / 2 - 17);
  attron(COLOR_PAIR(3) | A_BOLD);
  for (int i = 0; i < 17; i++)
    addstr("▄▄");

  for (int i = 0; i < 8; i++) {
    move(MAX_COLS / 2 - 8 + i * 2, MAX_ROWS / 2 - 17);
    attron(COLOR_PAIR(3));
    addstr("█");

    for (int j = 0; j < 8; j++) {
      attron(COLOR_PAIR(((i + j & 1) & 1) ? 1 : 2) | A_BOLD);
      addstr(" bK ");
    }

    attron(COLOR_PAIR(3));
    addstr("█");
    move(MAX_COLS / 2 - 8 + i * 2 + 1, MAX_ROWS / 2 - 17);
    addstr("█");

    for (int j = 0; j < 8; j++) {
      attron(COLOR_PAIR(((i + j & 1) & 1) ? 1 : 2) | A_BOLD);
      addstr(" ▀▀ ");//▄▀█
    }

    attron(COLOR_PAIR(3));
    addstr("█");
  }

  move(MAX_COLS / 2 + 8, MAX_ROWS / 2 - 17);
  attron(COLOR_PAIR(3));
  for (int i = 0; i < 17; i++)
    addstr("▀▀");
}


int main(void)
{
  WINDOW *stdscr = initscr();
  int inp;

  cbreak();
  noecho();
  raw();
  keypad(stdscr, 1);
  start_color();
  curs_set(0);

  getmaxyx(stdscr, MAX_COLS, MAX_ROWS);
  move(MAX_COLS / 2, MAX_ROWS / 2 - 3);
  init_pair(1, COLOR_BLUE, COLOR_WHITE);
  attron(COLOR_PAIR(1));
  addstr("hello");
  show_board();
  refresh();

  // while ((inp = getch())) addch(inp);
  getch();
  endwin();

  return (0);
}
