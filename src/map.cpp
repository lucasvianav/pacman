#include "map.h"

using namespace std;

Map::Map() {
  wchar_t ghs = GHOST_ICON;
  wchar_t pac = PACMAN_ICON;
  wchar_t spc = SPACE;

  this->map = {
    {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
    {'*', DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, '*', '*', DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, '*'},
    {'*', DOT, '*', '*', '*', '*', DOT, '*', '*', '*', '*', '*', DOT, '*', '*', DOT, '*', '*', '*', '*', '*', DOT, '*', '*', '*', '*', DOT, '*'},
    {'*', DOT, '*', '*', '*', '*', DOT, '*', '*', '*', '*', '*', DOT, DOT, DOT, DOT, '*', '*', '*', '*', '*', DOT, '*', '*', '*', '*', DOT, '*'},
    {'*', DOT, '*', '*', '*', '*', DOT, '*', '*', '*', '*', '*', DOT, '*', '*', DOT, '*', '*', '*', '*', '*', DOT, '*', '*', '*', '*', DOT, '*'},
    {'*', DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, '*', '*', DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, '*'},
    {'*', DOT, '*', '*', '*', '*', DOT, '*', '*', DOT, '*', '*', '*', '*', '*', '*', '*', '*', DOT, '*', '*', DOT, '*', '*', '*', '*', DOT, '*'},
    {'*', DOT, '*', '*', '*', '*', DOT, '*', '*', DOT, '*', '*', '*', '*', '*', '*', '*', '*', DOT, '*', '*', DOT, '*', '*', '*', '*', DOT, '*'},
    {'*', DOT, DOT, DOT, DOT, DOT, DOT, '*', '*', DOT, DOT, DOT, DOT, '*', '*', DOT, DOT, DOT, DOT, '*', '*', DOT, DOT, DOT, DOT, DOT, DOT, '*'},
    {'*', '*', '*', DOT, '*', '*', DOT, '*', '*', '*', '*', '*', DOT, '*', '*', DOT, '*', '*', '*', '*', '*', DOT, '*', '*', DOT, '*', '*', '*'},
    {'*', '*', '*', DOT, '*', '*', DOT, '*', '*', '*', '*', '*', DOT, '*', '*', DOT, '*', '*', '*', '*', '*', DOT, '*', '*', DOT, '*', '*', '*'},
    {'*', DOT, DOT, DOT, '*', '*', DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, '*', '*', DOT, DOT, DOT, '*'},
    {'*', DOT, '*', '*', '*', '*', DOT, '*', '*', DOT, '#', '#', '#', spc, spc, '#', '#', '#', DOT, '*', '*', DOT, '*', '*', '*', '*', DOT, '*'},
    {'*', DOT, '*', '*', '*', '*', DOT, '*', '*', DOT, '#', spc, spc, spc, spc, spc, spc, '#', DOT, '*', '*', DOT, '*', '*', '*', '*', DOT, '*'},
    {'*', DOT, DOT, DOT, DOT, DOT, DOT, '*', '*', DOT, '#', spc, ghs, ghs, ghs, ghs, spc, '#', DOT, '*', '*', DOT, DOT, DOT, DOT, DOT, DOT, '*'},
    {'*', DOT, '*', '*', '*', '*', DOT, '*', '*', DOT, '#', spc, spc, spc, spc, spc, spc, '#', DOT, '*', '*', DOT, '*', '*', '*', '*', DOT, '*'},
    {'*', DOT, '*', '*', '*', '*', DOT, '*', '*', DOT, '#', '#', '#', '#', '#', '#', '#', '#', DOT, '*', '*', DOT, '*', '*', '*', '*', DOT, '*'},
    {'*', DOT, DOT, DOT, '*', '*', DOT, '*', '*', DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, '*', '*', DOT, '*', '*', DOT, DOT, DOT, '*'},
    {'*', '*', '*', DOT, '*', '*', DOT, '*', '*', DOT, '*', '*', '*', '*', '*', '*', '*', '*', DOT, '*', '*', DOT, '*', '*', DOT, '*', '*', '*'},
    {'*', '*', '*', DOT, '*', '*', DOT, '*', '*', DOT, '*', '*', '*', '*', '*', '*', '*', '*', DOT, '*', '*', DOT, '*', '*', DOT, '*', '*', '*'},
    {'*', DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, pac, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, '*'},
    {'*', DOT, '*', '*', '*', '*', DOT, '*', '*', '*', '*', '*', DOT, '*', '*', DOT, '*', '*', '*', '*', '*', DOT, '*', '*', '*', '*', DOT, '*'},
    {'*', DOT, '*', '*', '*', '*', DOT, '*', '*', '*', '*', '*', DOT, '*', '*', DOT, '*', '*', '*', '*', '*', DOT, '*', '*', '*', '*', DOT, '*'},
    {'*', DOT, DOT, DOT, '*', '*', DOT, DOT, DOT, DOT, DOT, DOT, DOT, '*', '*', DOT, DOT, DOT, DOT, DOT, DOT, DOT, '*', '*', DOT, DOT, DOT, '*'},
    {'*', '*', '*', DOT, '*', '*', DOT, '*', '*', DOT, '*', '*', '*', '*', '*', '*', '*', '*', DOT, '*', '*', DOT, '*', '*', DOT, '*', '*', '*'},
    {'*', '*', '*', DOT, '*', '*', DOT, '*', '*', DOT, '*', '*', '*', '*', '*', '*', '*', '*', DOT, '*', '*', DOT, '*', '*', DOT, '*', '*', '*'},
    {'*', DOT, DOT, DOT, DOT, DOT, DOT, '*', '*', DOT, DOT, DOT, DOT, '*', '*', DOT, DOT, DOT, DOT, '*', '*', DOT, DOT, DOT, DOT, DOT, DOT, '*'},
    {'*', DOT, '*', '*', '*', '*', DOT, '*', '*', '*', '*', '*', DOT, '*', '*', DOT, '*', '*', '*', '*', '*', DOT, '*', '*', '*', '*', DOT, '*'},
    {'*', DOT, '*', '*', '*', '*', DOT, '*', '*', '*', '*', '*', DOT, '*', '*', DOT, '*', '*', '*', '*', '*', DOT, '*', '*', '*', '*', DOT, '*'},
    {'*', DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, '*'},
    {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
  };
  this->n_rows = 31;
  this->n_cols = 28;
  this->n_dots = 329;
}

vector<vector<wchar_t>> Map::get_map() { return this->map; };

wchar_t Map::get_char(Position pos) { return this->map[pos.y][pos.x]; };

unsigned int Map::get_n_rows() { return this->n_rows; };

unsigned int Map::get_n_cols() { return this->n_cols; };

unsigned int Map::get_n_dots() { return this->n_dots; };

void Map::update_map(Position pos, char value) {
  this->map[pos.y][pos.x] = value;
}
