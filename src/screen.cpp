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
  this->matrix_mutex = new mutex();
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

  int x = -1, y = 0;

  this->matrix.push_back({});
  while (f) {
    tmp_char = f.get();

    if (tmp_char == PORTAL_ICON || tmp_char == BARRIER_ICON) {
      this->matrix.back().push_back(SPACE_ICON);
      x++;
    } else if (tmp_char != '\n') {
      this->matrix.back().push_back(tmp_char);
      x++;
    } else {
      this->matrix.push_back({});
      y++;
      x = -1;
      continue;
    }

    tmp_pos = {x, y};

    if (tmp_char == PACMAN_ICON) {
      this->pacman_posision = tmp_pos;
    } else if (tmp_char == GHOST_ICON) {
      this->ghosts_positions.push_back(tmp_pos);
    } else if (tmp_char == DOT_ICON) {
      this->n_dots++;
    } else if (tmp_char == PORTAL_ICON) {
      if (this->portal_position_1) {
        this->portal_position_2 = tmp_pos;
      } else {
        this->portal_position_1 = tmp_pos;
      }
    } else if (tmp_char == BARRIER_ICON) {
      this->barrier_positions.push_back({x, y});
    }
  }

  f.close();

  // if the portal positions are invalid, exit with error code
  // invalid cases are:
  // - one position is assigned, but the other isn't
  // - the positions are the same
  // - the positions aren't aligned in neither axis
  if (!this->portal_position_1 != !this->portal_position_2 ||
      (this->portal_position_1.x != this->portal_position_2.x &&
       this->portal_position_1.y != this->portal_position_2.y) ||
      (this->portal_position_1 == this->portal_position_2 &&
       this->portal_position_1 && this->portal_position_2)) {
    exit(1);
  }

  // last element will be an empty row
  this->matrix.pop_back();

  this->n_rows = this->matrix.size();
  this->n_cols = this->matrix.front().size();
}

void Screen::print_right_margin() {
  for (unsigned int i = 0; i < this->right_margin; i++) {
    addch(' ');
  }
}

void Screen::draw(int score, bool paused) {
  this->matrix_mutex->lock();
  this->score_mutex->lock();

  this->score = score;

  if (this->colors) {
    bkgd(STANDARD_COLORS);
    bkgdset(STANDARD_COLORS);
  }

  for (unsigned int i = 0; i < this->n_rows; i++) {
    for (unsigned int j = 0; j < this->n_cols; j++) {
      if (score >= 0 && j + 2 < this->n_cols && matrix[i][j] == 's' &&
          matrix[i][j + 1] == 'c' && matrix[i][j + 2] == 'o') {

        char score_str[4];
        sprintf(score_str, "%03d", score);

        attron(A_BOLD | A_UNDERLINE);
        mvaddstr(i, j, score_str);
        attroff(A_BOLD | A_UNDERLINE);

        j += 2;
        continue;
      }

      if (this->colors) {
        switch (matrix[i][j]) {
        case GHOST_ICON:
          mvaddch(i, j,
                  this->matrix[i][j] | A_BOLD | A_STANDOUT |
                      COLOR_PAIR(GHOST_COLORS));
          break;
        case PACMAN_ICON:
          mvaddch(i, j,
                  this->matrix[i][j] | A_BOLD | COLOR_PAIR(PACMAN_COLORS));
          break;
        case DOT_ICON:
          mvaddch(i, j,
                  this->matrix[i][j] | A_DIM | COLOR_PAIR(STANDARD_COLORS));
          break;
        default:
          mvaddch(i, j, this->matrix[i][j] | COLOR_PAIR(STANDARD_COLORS));
        }
      } else {
        switch (matrix[i][j]) {
        case GHOST_ICON:
          mvaddch(i, j, this->matrix[i][j] | A_BOLD | A_STANDOUT);
          break;
        case PACMAN_ICON:
          mvaddch(i, j, this->matrix[i][j] | A_BOLD);
          break;
        case DOT_ICON:
          mvaddch(i, j, this->matrix[i][j] | A_DIM);
          break;
        default:
          mvaddch(i, j, this->matrix[i][j] | A_NORMAL);
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

  this->score_mutex->unlock();
  this->matrix_mutex->unlock();
}

char Screen::get_char(Position pos) {
  this->matrix_mutex->lock();
  char c = this->matrix[pos.y][pos.x];
  this->matrix_mutex->unlock();

  return c;
};

unsigned int Screen::get_n_rows() { return this->n_rows; };

unsigned int Screen::get_n_cols() { return this->n_cols; };

unsigned int Screen::get_n_dots() { return this->n_dots; };

void Screen::set_char(Position pos, char value) {
  this->matrix_mutex->lock();
  this->matrix[pos.y][pos.x] = value;
  this->matrix_mutex->unlock();
}

void Screen::set_chars(vector<Position> positions, vector<char> values) {
  int size = positions.size();
  if (size != (int)values.size()) {
    return;
  }

  this->matrix_mutex->lock();
  for (int i = 0; i < size; i++) {
    this->matrix[positions[i].y][positions[i].x] = values[i];
  }
  this->matrix_mutex->unlock();
}

bool Screen::position_valid(Position pos) {
  return (pos.x >= 0 && pos.x < (int)this->n_cols) &&
         (pos.y >= 0 && pos.y < (int)this->n_rows);
}

bool Screen::is_walkable(Position pos) {
  auto c = this->get_char(pos);
  return c == DOT_ICON || c == SPACE_ICON || c == PACMAN_ICON;
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
  if (pos.x != (int)this->get_n_cols() - 1) {
    neighbor.x = pos.x + 1;
    neighbor.y = pos.y;

    if (this->is_walkable(neighbor)) {
      adjacencies.push_back(neighbor);
    }
  }

  // to the bottom
  if (pos.y != (int)this->get_n_rows() - 1) {
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
