#include <vector>

#ifndef MAP_H
#define MAP_H

using namespace std;

class Map {
private:
  vector<vector<char>> map;
  int n_rows;
  int n_cols;

public:
  Map();
  vector<vector<char>> get_map();
  int get_n_rows();
  int get_n_cols();
  void update_map(int x, int y, char value);
};

#endif
