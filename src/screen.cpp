#include "screen.h"
#include "utils.h"
#include <cstdio>
#include <curses.h>
#include <fstream>
#include <iostream>

// ncurses color profiles
#define STANDARD_COLORS 0
#define PACMAN_COLORS 1
#define GHOST_COLORS 2

using namespace std;

Screen::Screen(string name) {
  this->current_mutex = new mutex();
  this->next_mutex = new mutex();
  this->score_mutex = new mutex();

  this->n_dots = 0;
  this->right_margin = 7;
  this->score = -1;
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

void Screen::print_right_margin() {
  for (unsigned int i = 0; i < this->right_margin; i++) {
    addch(' ');
  }
}

void Screen::draw(int score, bool paused) {
  this->next_mutex->lock();
  this->score_mutex->lock();
  this->current_mutex->lock();

  this->score = score;

  for (unsigned int i = 0; i < this->n_rows; i++) {
    for (unsigned int j = 0; j < this->n_cols; j++) {
      this->current[i][j] = this->next[i][j];

      if (this->colors) {
        switch (next[i][j]) {
        case GHOST_ICON:
          mvaddch(i, j,
                  this->next[i][j] | A_BOLD | A_STANDOUT |
                      COLOR_PAIR(GHOST_COLORS));
          break;
        case PACMAN_ICON:
          mvaddch(i, j, this->next[i][j] | A_BOLD | COLOR_PAIR(PACMAN_COLORS));
          break;
        case DOT:
          mvaddch(i, j, this->next[i][j] | A_DIM | COLOR_PAIR(STANDARD_COLORS));
          break;
        default:
          mvaddch(i, j, this->next[i][j] | COLOR_PAIR(STANDARD_COLORS));
        }
      } else {
        switch (next[i][j]) {
        case GHOST_ICON:
          mvaddch(i, j, this->next[i][j] | A_BOLD | A_STANDOUT);
          break;
        case PACMAN_ICON:
          mvaddch(i, j, this->next[i][j] | A_BOLD);
          break;
        case DOT:
          mvaddch(i, j, this->next[i][j] | A_DIM);
          break;
        default:
          mvaddch(i, j, this->next[i][j] | A_NORMAL);
        }
      }
    }

    if (i == 0 && score != -1 && this->n_dots) {
      this->print_right_margin();
      char score_str[20];
      sprintf(score_str, "SCORE: %d/%d", score, this->n_dots);

      attron(A_UNDERLINE);
      addstr(score_str);
      attroff(A_UNDERLINE);
    } else if (i == 2 && paused && this->n_dots) {
      this->print_right_margin();

      attron(A_BOLD | A_STANDOUT);
      addstr(">> PAUSED <<");
      attroff(A_BOLD | A_STANDOUT);
    }
  }

  this->current_mutex->unlock();
  this->score_mutex->unlock();
  this->next_mutex->unlock();
}

void Screen::redraw(int score) {
  this->next_mutex->lock();
  this->current_mutex->lock();
  for (unsigned int i = 0; i < this->n_rows; i++) {
    for (unsigned int j = 0; j < this->n_cols; j++) {
      // only update chars that changed
      if (this->current[i][j] != this->next[i][j]) {
        mvaddch(i, j, this->next[i][j]);
        this->current[i][j] = this->next[i][j];
      }
    }
  }
  this->current_mutex->unlock();
  this->next_mutex->unlock();

  // only update score if it also changed
  this->score_mutex->lock();
  if (score != (int)this->score) {
    this->score = score;

    if (score >= 0 && this->n_dots) {
      char score_str[20];
      sprintf(score_str, "SCORE: %d/%d", score, this->n_dots);

      attron(A_UNDERLINE);
      mvaddstr(0, this->n_cols + this->right_margin, score_str);
      attroff(A_UNDERLINE);
    }
  }
  this->score_mutex->unlock();
}

char Screen::get_char(Position pos) {
  this->next_mutex->lock();
  char c = this->next[pos.y][pos.x];
  this->next_mutex->unlock();

  return c;
};

unsigned int Screen::get_n_rows() { return this->n_rows; };

unsigned int Screen::get_n_cols() { return this->n_cols; };

unsigned int Screen::get_n_dots() { return this->n_dots; };

void Screen::set_char(Position pos, char value) {
  this->next_mutex->lock();
  this->next[pos.y][pos.x] = value;
  this->next_mutex->unlock();
}

void Screen::set_chars(vector<Position> positions, vector<char> values) {
  int size = positions.size();
  if (size != (int)values.size()) {
    return;
  }

  this->next_mutex->lock();
  for (int i = 0; i < size; i++) {
    this->next[positions[i].y][positions[i].x] = values[i];
  }
  this->next_mutex->unlock();
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
