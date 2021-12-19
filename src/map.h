#ifndef MAP_H
#define MAP_H

#include "utils.h"
#include <vector>

using namespace std;

class Map {
private:
  /* Map matrix. */
  vector<vector<wchar_t>> map;

  /* Number of map rows. */
  unsigned int n_rows;

  /* Number of map column. */
  unsigned int n_cols;

  /* Number of points in the map. */
  unsigned int n_dots;

  /* Check if given position can be "walked" by a character. */
  bool is_walkable(Position pos);

public:
  Map();

  /* Returns the map's matrix. */
  vector<vector<wchar_t>> get_map();

  /* Returns the charater at a given position. */
  wchar_t get_char(Position pos);

  /* Getter for number of map rows. */
  unsigned int get_n_rows();

  /* Getter for number of map columns. */
  unsigned int get_n_cols();

  /* Getter for number of points in the map. */
  unsigned int get_n_dots();

  /* Sets the character at a given position to a given value. */
  void update_map(Position pos, char value);

  /* Check if position is within the map's bounds. */
  bool position_valid(Position pos);

  /* Getter for the adjacency list of a given position. */
  vector<Position> get_adjacency_list(Position pos);
};

#endif
