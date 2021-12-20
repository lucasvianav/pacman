#include "screen.h"
#include "utils.h"
#include <cstdio>
#include <curses.h>
#include <fstream>
#include <iostream>

using namespace std;

Screen::Screen(string name) {
  this->n_dots = 0;

  ifstream f;
  f.open("./screens/" + name + ".txt");

  char tmp_char;
  Position tmp_pos;

  unsigned int x = -1, y = 0;

  this->screen.push_back({});
  while (f) {
    tmp_char = f.get();

    if (tmp_char != '\n') {
      this->screen.back().push_back(tmp_char);
      x++;
    } else {
      this->screen.push_back({});
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
  this->screen.pop_back();

  this->n_rows = this->screen.size();
  this->n_cols = this->screen.front().size();
}

void Screen::draw(WINDOW *window, int score, bool paused) {
  for (unsigned int i = 0; i < this->n_rows; i++) {
    for (unsigned int j = 0; j < this->n_cols; j++) {
      waddch(window, this->screen[i][j]);
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

vector<vector<wchar_t>> Screen::get_screen() { return this->screen; };

wchar_t Screen::get_char(Position pos) { return this->screen[pos.y][pos.x]; };

unsigned int Screen::get_n_rows() { return this->n_rows; };

unsigned int Screen::get_n_cols() { return this->n_cols; };

unsigned int Screen::get_n_dots() { return this->n_dots; };

void Screen::set_char(Position pos, char value) {
  this->screen[pos.y][pos.x] = value;
}

bool Screen::position_valid(Position pos) {
  return (pos.x >= 0 && pos.x < this->n_cols) &&
         (pos.y >= 0 && pos.y < this->n_rows);
}

bool Screen::is_walkable(Position pos) {
  auto c = this->get_char(pos);
  return c == DOT || c == SPACE || c == PACMAN_ICON;
}

vector<Position> Screen::get_adjacency_list(Position pos) {
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
