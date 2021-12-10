#include "map.h"

using namespace std;

Map::Map() {
  this->map = {
    {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
    {'*', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', '*', '*', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', '*'},
    {'*', 'o', '*', '*', '*', '*', 'o', '*', '*', '*', '*', '*', 'o', '*', '*', 'o', '*', '*', '*', '*', '*', 'o', '*', '*', '*', '*', 'o', '*'},
    {'*', 'o', '*', '*', '*', '*', 'o', '*', '*', '*', '*', '*', 'o', 'o', 'o', 'o', '*', '*', '*', '*', '*', 'o', '*', '*', '*', '*', 'o', '*'},
    {'*', 'o', '*', '*', '*', '*', 'o', '*', '*', '*', '*', '*', 'o', '*', '*', 'o', '*', '*', '*', '*', '*', 'o', '*', '*', '*', '*', 'o', '*'},
    {'*', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', '*', '*', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', '*'},
    {'*', 'o', '*', '*', '*', '*', 'o', '*', '*', 'o', '*', '*', '*', '*', '*', '*', '*', '*', 'o', '*', '*', 'o', '*', '*', '*', '*', 'o', '*'},
    {'*', 'o', '*', '*', '*', '*', 'o', '*', '*', 'o', '*', '*', '*', '*', '*', '*', '*', '*', 'o', '*', '*', 'o', '*', '*', '*', '*', 'o', '*'},
    {'*', 'o', 'o', 'o', 'o', 'o', 'o', '*', '*', 'o', 'o', 'o', 'o', '*', '*', 'o', 'o', 'o', 'o', '*', '*', 'o', 'o', 'o', 'o', 'o', 'o', '*'},
    {'*', '*', '*', 'o', '*', '*', 'o', '*', '*', '*', '*', '*', 'o', '*', '*', 'o', '*', '*', '*', '*', '*', 'o', '*', '*', 'o', '*', '*', '*'},
    {'*', '*', '*', 'o', '*', '*', 'o', '*', '*', '*', '*', '*', 'o', '*', '*', 'o', '*', '*', '*', '*', '*', 'o', '*', '*', 'o', '*', '*', '*'},
    {'*', 'o', 'o', 'o', '*', '*', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', '*', '*', 'o', 'o', 'o', '*'},
    {'*', 'o', '*', '*', '*', '*', 'o', '*', '*', 'o', '#', '#', '#', ' ', ' ', '#', '#', '#', 'o', '*', '*', 'o', '*', '*', '*', '*', 'o', '*'},
    {'*', 'o', '*', '*', '*', '*', 'o', '*', '*', 'o', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', 'o', '*', '*', 'o', '*', '*', '*', '*', 'o', '*'},
    {'*', 'o', 'o', 'o', 'o', 'o', 'o', '*', '*', 'o', '#', ' ', '%', '%', '%', '%', ' ', '#', 'o', '*', '*', 'o', 'o', 'o', 'o', 'o', 'o', '*'},
    {'*', 'o', '*', '*', '*', '*', 'o', '*', '*', 'o', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', 'o', '*', '*', 'o', '*', '*', '*', '*', 'o', '*'},
    {'*', 'o', '*', '*', '*', '*', 'o', '*', '*', 'o', '#', '#', '#', '#', '#', '#', '#', '#', 'o', '*', '*', 'o', '*', '*', '*', '*', 'o', '*'},
    {'*', 'o', 'o', 'o', '*', '*', 'o', '*', '*', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', '*', '*', 'o', '*', '*', 'o', 'o', 'o', '*'},
    {'*', '*', '*', 'o', '*', '*', 'o', '*', '*', 'o', '*', '*', '*', '*', '*', '*', '*', '*', 'o', '*', '*', 'o', '*', '*', 'o', '*', '*', '*'},
    {'*', '*', '*', 'o', '*', '*', 'o', '*', '*', 'o', '*', '*', '*', '*', '*', '*', '*', '*', 'o', '*', '*', 'o', '*', '*', 'o', '*', '*', '*'},
    {'*', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', '@', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', '*'},
    {'*', 'o', '*', '*', '*', '*', 'o', '*', '*', '*', '*', '*', 'o', '*', '*', 'o', '*', '*', '*', '*', '*', 'o', '*', '*', '*', '*', 'o', '*'},
    {'*', 'o', '*', '*', '*', '*', 'o', '*', '*', '*', '*', '*', 'o', '*', '*', 'o', '*', '*', '*', '*', '*', 'o', '*', '*', '*', '*', 'o', '*'},
    {'*', 'o', 'o', 'o', '*', '*', 'o', 'o', 'o', 'o', 'o', 'o', 'o', '*', '*', 'o', 'o', 'o', 'o', 'o', 'o', 'o', '*', '*', 'o', 'o', 'o', '*'},
    {'*', '*', '*', 'o', '*', '*', 'o', '*', '*', 'o', '*', '*', '*', '*', '*', '*', '*', '*', 'o', '*', '*', 'o', '*', '*', 'o', '*', '*', '*'},
    {'*', '*', '*', 'o', '*', '*', 'o', '*', '*', 'o', '*', '*', '*', '*', '*', '*', '*', '*', 'o', '*', '*', 'o', '*', '*', 'o', '*', '*', '*'},
    {'*', 'o', 'o', 'o', 'o', 'o', 'o', '*', '*', 'o', 'o', 'o', 'o', '*', '*', 'o', 'o', 'o', 'o', '*', '*', 'o', 'o', 'o', 'o', 'o', 'o', '*'},
    {'*', 'o', '*', '*', '*', '*', 'o', '*', '*', '*', '*', '*', 'o', '*', '*', 'o', '*', '*', '*', '*', '*', 'o', '*', '*', '*', '*', 'o', '*'},
    {'*', 'o', '*', '*', '*', '*', 'o', '*', '*', '*', '*', '*', 'o', '*', '*', 'o', '*', '*', '*', '*', '*', 'o', '*', '*', '*', '*', 'o', '*'},
    {'*', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', '*'},
    {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
  };
  this->n_rows = 31;
  this->n_cols = 28;
}

vector<vector<char>> Map::get_map() {
  return this->map;
};

int Map::get_n_rows() { return this->n_rows; };

int Map::get_n_cols() { return this->n_cols; };

void Map::update_map(int x, int y, char value) { this->map[y][x] = value; }
