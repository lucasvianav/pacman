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
  this->ghosts_positions = {
    { 12, 14 },
    { 13, 14 },
    { 14, 14 },
    { 15, 14 },
  };
  this->pacman_posision = { 14, 20 };
}

vector<vector<wchar_t>> Map::get_map() { return this->map; };

wchar_t Map::get_char(Position pos) { return this->map[pos.y][pos.x]; };

unsigned int Map::get_n_rows() { return this->n_rows; };

unsigned int Map::get_n_cols() { return this->n_cols; };

unsigned int Map::get_n_dots() { return this->n_dots; };

void Map::update_map(Position pos, char value) {
  this->map[pos.y][pos.x] = value;
}

bool Map::position_valid(Position pos) {
  return (pos.x >= 0 && pos.x < this->n_cols) &&
         (pos.y >= 0 && pos.y < this->n_rows);
}

bool Map::is_walkable(Position pos) {
  auto c = this->get_char(pos);
  return c == DOT || c == SPACE || c == PACMAN_ICON;
}

vector<Position> Map::get_adjacency_list(Position pos) {
  vector<Position> adjacencies;
  Position neighbor;

  // to the left
  if(pos.x != 0) {
    neighbor.x = pos.x-1;
    neighbor.y = pos.y;

    if(this->is_walkable(neighbor)) {
      adjacencies.push_back(neighbor);
    }
  }

  // to the right
  if(pos.x != this->get_n_cols() - 1) {
    neighbor.x = pos.x+1;
    neighbor.y = pos.y;

    if(this->is_walkable(neighbor)) {
      adjacencies.push_back(neighbor);
    }
  }

  // to the bottom
  if(pos.y != this->get_n_rows() - 1) {
    neighbor.x = pos.x;
    neighbor.y = pos.y+1;

    if(this->is_walkable(neighbor)) {
      adjacencies.push_back(neighbor);
    }
  }

  // to the top
  if(pos.y != 0) {
    neighbor.x = pos.x;
    neighbor.y = pos.y-1;

    if(this->is_walkable(neighbor)) {
      adjacencies.push_back(neighbor);
    }
  }
  return adjacencies;
}
