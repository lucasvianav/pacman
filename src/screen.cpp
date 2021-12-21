#include "screen.h"
#include "utils.h"
#include <cstdio>
#include <curses.h>
#include <fstream>
#include <iostream>

using namespace std;

Screen::Screen(string name) {
  this->n_dots = 0;
  this->right_margin = 7;
  this->score = -1;

  ifstream f;
  f.open("./screens/" + name + ".txt");

  char tmp_char;
  Position tmp_pos;

  unsigned int x = -1, y = 0;

  this->current.push_back({});
  this->next.push_back({});
  while (f) {
    tmp_char = f.get();

    if (tmp_char != '\n') {
      this->current.back().push_back(tmp_char);
      this->next.back().push_back(tmp_char);
      x++;
    } else {
      this->current.push_back({});
      this->next.push_back({});
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
  this->current.pop_back();
  this->next.pop_back();

  this->n_rows = this->current.size();
  this->n_cols = this->current.front().size();
}

void Screen::print_right_margin(WINDOW *window) {
  for (unsigned int i = 0; i < this->right_margin; i++) {
    waddch(window, ' ');
  }
}

void Screen::draw(WINDOW *window, int score, bool paused) {
  this->score = score;

  for (unsigned int i = 0; i < this->n_rows; i++) {
    for (unsigned int j = 0; j < this->n_cols; j++) {
      waddch(window, this->next[i][j]);
    }

    if (i == 0 && score != -1 && this->n_dots) {
      this->print_right_margin(window);
      char score_str[20];
      sprintf(score_str, "SCORE: %d/%d", score, this->n_dots);

      attron(A_UNDERLINE);
      waddstr(window, score_str);
      attroff(A_UNDERLINE);
    } else if (i == 2 && paused && this->n_dots) {
      this->print_right_margin(window);

      attron(A_BOLD | A_STANDOUT);
      waddstr(window, ">> PAUSED <<");
      attroff(A_BOLD | A_STANDOUT);
    }

    waddch(window, '\n');
  }
}

void Screen::redraw(WINDOW *window, int score) {
  for (unsigned int i = 0; i < this->n_rows; i++) {
    for (unsigned int j = 0; j < this->n_cols; j++) {
      if (this->current[i][j] == this->next[i][j]) {
        continue;
      } else { // only update chars that changed
        this->current[i][j] = this->next[i][j];
        mvwaddch(window, i, j, next[i][j]);
      }
    }
  }

  // only update scroe if it also changed
  if (score != (int)this->score) {
    this->score = score;

    if (score != -1 && this->n_dots) {
      char score_str[20];
      sprintf(score_str, "SCORE: %d/%d", score, this->n_dots);

      attron(A_UNDERLINE);
      mvwaddstr(window, 0, this->n_cols + this->right_margin, score_str);
      attroff(A_UNDERLINE);
    }
  }
}

vector<vector<wchar_t>> Screen::get_screen() { return this->current; };

wchar_t Screen::get_char(Position pos) { return this->next[pos.y][pos.x]; };

unsigned int Screen::get_n_rows() { return this->n_rows; };

unsigned int Screen::get_n_cols() { return this->n_cols; };

unsigned int Screen::get_n_dots() { return this->n_dots; };

void Screen::set_char(Position pos, char value) {
  this->next[pos.y][pos.x] = value;
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
