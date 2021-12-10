#ifndef MAP_H
#define MAP_H

#include "utils.h"
#include <vector>

using namespace std;

class Map {
private:
  vector<vector<wchar_t>> map;
  unsigned int n_rows;
  unsigned int n_cols;

public:
  Map();
  vector<vector<wchar_t>> get_map();
  wchar_t get_char(Position pos);
  unsigned int get_n_rows();
  unsigned int get_n_cols();
  void update_map(Position pos, char value);
};

#endif
