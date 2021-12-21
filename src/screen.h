#ifndef SCREEN_H
#define SCREEN_H

#include "utils.h"
#include <curses.h>
#include <mutex>
#include <string>
#include <vector>

using namespace std;

class Screen {
private:
  mutex *current_mutex;
  mutex *next_mutex;
  mutex *score_mutex;

  /* Screen matrix being currently displayed. */
  vector<vector<wchar_t>> current;

  /* Screen matrix to be displayed in next refresh. */
  vector<vector<wchar_t>> next;

  /* Number of screen rows. */
  unsigned int n_rows;

  /* Number of screen column. */
  unsigned int n_cols;

  /* Number of points in the screen. */
  unsigned int n_dots;

  /* The player's score points. */
  unsigned int score;

  /* Margin between the screen and warning on the right. */
  unsigned int right_margin;

  /* Check if given position can be "walked" by a character. */
  bool is_walkable(Position pos);

  /* Prints `right_margin` blankspaces. */
  void print_right_margin(WINDOW *window);

public:
  Screen(string name);

  /* Returns the charater at a given position. */
  wchar_t get_char(Position pos);

  /* Getter for number of screen rows. */
  unsigned int get_n_rows();

  /* Getter for number of screen columns. */
  unsigned int get_n_cols();

  /* Getter for number of points in the screen. */
  unsigned int get_n_dots();

  /* Sets the character at a given position to a given value. */
  void set_char(Position pos, wchar_t value);

  /* Sets the characters at multiple positions to the given values. */
  void set_chars(vector<Position> positions, vector<wchar_t> values);

  /* Draws the screen to the terminal. */
  void draw(WINDOW *window, int score, bool paused);

  /*
   * Redraw the only the changed parts in the screen.
   * @see https://stackoverflow.com/a/34843392
   */
  void redraw(WINDOW *window, int score);

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
