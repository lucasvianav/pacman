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

bool Map::position_valid(Position pos) {
  return (pos.x >= 0 && pos.x < this->n_cols) &&
         (pos.y >= 0 && pos.y < this->n_rows);
}

bool Map::is_walkable_cell(Position pos) {
  return this->get_char(pos) != '*' && this->get_char(pos) != '#';
}

vector<Position> Map::get_adj_list(Position pos) {
    Position neighborsPosition;
    vector<Position> neighborsList;
    // vizinho casa a esquerda
    if(pos.x != 0) {
        neighborsPosition.x = pos.x-1;
        neighborsPosition.y = pos.y;
        if(this->is_walkable_cell(neighborsPosition)) {
            neighborsList.push_back(neighborsPosition);
        }
    }
    // vizinho casa a direita
    if(pos.x != this->get_n_cols() - 1) {
        neighborsPosition.x = pos.x+1;
        neighborsPosition.y = pos.y;
        if(this->is_walkable_cell(neighborsPosition)) {
            neighborsList.push_back(neighborsPosition);
        }
    }
    //vizinho abaixo
    if(pos.y != this->get_n_rows() - 1) {
        neighborsPosition.x = pos.x;
        neighborsPosition.y = pos.y+1;
        if(this->is_walkable_cell(neighborsPosition)) {
            neighborsList.push_back(neighborsPosition);
        }
    }

    // vizinho acima
    if(pos.y != 0) {
        neighborsPosition.x = pos.x;
        neighborsPosition.y = pos.y-1;
        if(this->is_walkable_cell(neighborsPosition)) {
            neighborsList.push_back(neighborsPosition);
        }
    }
    return neighborsList;
}
