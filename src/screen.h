#ifndef SCREEN_H
#define SCREEN_H

#include "utils.h"
#include <curses.h>
#include <string>
#include <vector>

using namespace std;

class Screen {
private:
  /* Screen matrix. */
  vector<vector<wchar_t>> screen;

  /* Number of screen rows. */
  unsigned int n_rows;

  /* Number of screen column. */
  unsigned int n_cols;

  /* Number of points in the screen. */
  unsigned int n_dots;

  /* Check if given position can be "walked" by a character. */
  bool is_walkable(Position pos);

public:
  Screen(string name);

  /* Returns the screen's matrix. */
  vector<vector<wchar_t>> get_screen();

  /* Returns the charater at a given position. */
  wchar_t get_char(Position pos);

  /* Getter for number of screen rows. */
  unsigned int get_n_rows();

  /* Getter for number of screen columns. */
  unsigned int get_n_cols();

  /* Getter for number of points in the screen. */
  unsigned int get_n_dots();

  /* Sets the character at a given position to a given value. */
  void set_char(Position pos, char value);

  /* Draws the screen to the screen. */
  void draw(WINDOW *window, int score, bool paused);

  /* Check if position is within the screen's bounds. */
  bool position_valid(Position pos);

  /* Getter for the adjacency list of a given position. */
  vector<Position> get_adjacency_list(Position pos);

  /* The positions of all ghosts in the screen. */
  vector<Position> ghosts_positions;

  /* The positions of Pacman in the screen. */
  Position pacman_posision;
};

#endif
