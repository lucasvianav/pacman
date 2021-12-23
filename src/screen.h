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
  // semaphores
  mutex *matrix_mutex;
  mutex *score_mutex;

  /* Screen matrix. */
  vector<vector<char>> matrix;

  /* Number of screen rows. */
  unsigned int n_rows;

  /* Number of screen column. */
  unsigned int n_cols;

  /* Number of points in the screen. */
  unsigned int n_dots;

  /* If the running terminal emulator supports colors. */
  bool colors;

  /* The player's score points. */
  unsigned int score;

  /* Margin between the screen and warning on the right. */
  unsigned int right_margin;

  /* Prints `right_margin` blankspaces. */
  void print_right_margin();

public:
  Screen(string name);

  /* Returns the charater at a given position. */
  char get_char(Position pos);

  /* Getter for number of screen rows. */
  unsigned int get_n_rows();

  /* Getter for number of screen columns. */
  unsigned int get_n_cols();

  /* Getter for number of points in the screen. */
  unsigned int get_n_dots();

  /* Sets the character at a given position to a given value. */
  void set_char(Position pos, char value);

  /* Sets the characters at multiple positions to the given values. */
  void set_chars(vector<Position> positions, vector<char> values);

  /* Draws the screen to the terminal. */
  void draw(int score, bool paused);

  /* Check if position is within the screen's bounds. */
  bool position_valid(Position pos);

  /* Check if given position can be "walked" by a character. */
  bool is_walkable(Position pos);

  /* Getter for the adjacency list of a given position. */
  vector<Position> get_adjacency_list(Position pos);

  /* The positions of all ghosts in the screen. */
  vector<Position> ghosts_positions;

  /* The positions of the first portal. */
  Position portal_position_1;

  /* The positions of the second portal. */
  Position portal_position_2;

  /* The positions of Pacman in the screen. */
  Position pacman_posision;
};

#endif
