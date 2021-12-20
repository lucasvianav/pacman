#include "map.h"
#include "utils.h"
#include <cstdio>
#include <fstream>
#include <iostream>

// color profiles
#define STANDARD_COLORS 0
#define PACMAN_COLORS 1
#define GHOST_COLORS 2

using namespace std;

Map::Map(string name) {
  this->n_dots = 0;
  this->colors = has_colors();

  if (this->colors) {
    start_color();

    // color profiles
    init_pair(STANDARD_COLORS, COLOR_WHITE, COLOR_BLACK);
    init_pair(GHOST_COLORS, COLOR_RED, COLOR_WHITE);
    init_pair(PACMAN_COLORS, COLOR_YELLOW, COLOR_BLACK);
  }

  ifstream f;
  f.open("./screens/" + name + ".txt");

  char tmp_char;
  Position tmp_pos;

  unsigned int x = -1, y = 0;

  this->map.push_back({});
  while (f) {
    tmp_char = f.get();

    if (tmp_char != '\n') {
      this->map.back().push_back(tmp_char);
      x++;
    } else {
      this->map.push_back({});
      y++;
      x = -1;
    }

    tmp_pos = {x, y};

    if (tmp_char == PACMAN_ICON) {
      this->pacman_posision = tmp_pos;
    } else if (tmp_char == GHOST_ICON) {
      this->ghosts_positions.push_back(tmp_pos);
    } else if (tmp_char == DOT) {
      this->n_dots++;
    }
  }

  f.close();

  // last element will be an empty row
  this->map.pop_back();

  this->n_rows = this->map.size();
  this->n_cols = this->map.front().size();
}

void Map::draw(WINDOW *window, int score, bool paused) {
  erase();

  // set BG color to black
  wbkgd(window, A_NORMAL | COLOR_PAIR(0));

  for (unsigned int i = 0; i < this->n_rows; i++) {
    for (unsigned int j = 0; j < this->n_cols; j++) {
      if (this->colors) {
        if (this->map[i][j] == GHOST_ICON) {
          waddch(window, this->map[i][j] | A_BOLD | A_STANDOUT |
                             COLOR_PAIR(GHOST_COLORS));
        } else if (this->map[i][j] == PACMAN_ICON) {
          waddch(window, this->map[i][j] | A_BOLD | COLOR_PAIR(PACMAN_COLORS));
        } else if (this->map[i][j] == DOT) {
          waddch(window, this->map[i][j] | A_DIM | COLOR_PAIR(STANDARD_COLORS));
        } else {
          waddch(window,
                 this->map[i][j] | A_NORMAL | COLOR_PAIR(STANDARD_COLORS));
        }
      } else {
        if (this->map[i][j] == GHOST_ICON) {
          waddch(window, this->map[i][j] | A_BOLD | A_STANDOUT);
        } else if (this->map[i][j] == PACMAN_ICON) {
          waddch(window, this->map[i][j] | A_BOLD);
        } else if (this->map[i][j] == DOT) {
          waddch(window, this->map[i][j] | A_DIM);
        } else {
          waddch(window, this->map[i][j] | A_NORMAL);
        }
      }
    }

    if (i == 0 && score != -1 && this->n_dots) {
      waddstr(window, "      ");
      char score_str[20];
      sprintf(score_str, "SCORE: %d/%d", score, this->n_dots);

      attron(A_UNDERLINE);
      waddstr(window, score_str);
      attroff(A_UNDERLINE);
    } else if (i == 2 && paused && this->n_dots) {
      waddstr(window, "      ");

      attron(A_BOLD | A_STANDOUT);
      waddstr(window, ">> PAUSED <<");
      attroff(A_BOLD | A_STANDOUT);
    }

    waddch(window, '\n');
  }
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
  if (pos.x != 0) {
    neighbor.x = pos.x - 1;
    neighbor.y = pos.y;

    if (this->is_walkable(neighbor)) {
      adjacencies.push_back(neighbor);
    }
  }

  // to the right
  if (pos.x != this->get_n_cols() - 1) {
    neighbor.x = pos.x + 1;
    neighbor.y = pos.y;

    if (this->is_walkable(neighbor)) {
      adjacencies.push_back(neighbor);
    }
  }

  // to the bottom
  if (pos.y != this->get_n_rows() - 1) {
    neighbor.x = pos.x;
    neighbor.y = pos.y + 1;

    if (this->is_walkable(neighbor)) {
      adjacencies.push_back(neighbor);
    }
  }

  // to the top
  if (pos.y != 0) {
    neighbor.x = pos.x;
    neighbor.y = pos.y - 1;

    if (this->is_walkable(neighbor)) {
      adjacencies.push_back(neighbor);
    }
  }
  return adjacencies;
}
