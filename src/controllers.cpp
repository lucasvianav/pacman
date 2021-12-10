#include "controllers.h"
#include <curses.h>
#include <stdlib.h>

using namespace std;

// GameController

GameController::GameController() {
  // initializes ncurses
  this->gamescr = initscr();
  keypad(this->gamescr, true);
  nodelay(this->gamescr, true);
  noecho();
  curs_set(false);
  cbreak();

  this->map = Map();
  this->draw_map();
  this->ghost_above_dot = false;
}

bool GameController::position_within_bounds(Position pos) {
  unsigned int n_rows = this->map.get_n_rows();
  unsigned int n_cols = this->map.get_n_cols();

  return (pos.x >= 0 && pos.x < n_cols) && (pos.y >= 0 && pos.y < n_rows);
}

void GameController::draw_map() {
  vector<vector<wchar_t>> map_chars = this->map.get_map();
  unsigned int n_rows = this->map.get_n_rows();
  unsigned int n_cols = this->map.get_n_cols();

  for (unsigned int i = 0; i < n_rows; i++) {
    for (unsigned int j = 0; j < n_cols; j++) {
      waddch(this->gamescr, map_chars[i][j]);
    }

    waddch(this->gamescr, '\n');
  }
}

Position GameController::move(Position old_pos, Position new_pos) {
  if (this->position_within_bounds(new_pos)) {
    wchar_t old_pos_cur_char = this->map.get_char(old_pos);
    wchar_t new_pos_cur_char = this->map.get_char(new_pos);

    bool is_pacman = old_pos_cur_char == PACMAN_ICON;
    bool ghost_leaving_dot = this->ghost_above_dot && !is_pacman;

    wchar_t old_pos_new_char = ghost_leaving_dot ? DOT : SPACE;
    wchar_t new_pos_new_char = old_pos_cur_char;

    switch (new_pos_cur_char) {
    case PACMAN_ICON:
      quit();
      break;

    case DOT:
      if (!is_pacman) {
        this->ghost_above_dot = true;
      }
      break;

    case SPACE:
      if (ghost_leaving_dot) {
        this->ghost_above_dot = false;
      }
      break;

    default:
      return old_pos;
    }

    this->map.update_map(old_pos, old_pos_new_char);
    this->map.update_map(new_pos, new_pos_new_char);

    return new_pos;
  }

  return old_pos;
}

void GameController::refresh() {
  erase();
  wrefresh(this->gamescr);
  this->draw_map();
}

WINDOW *GameController::get_screen() { return this->gamescr; }

// Character

Character::Character(GameController *gc, unsigned int x, unsigned int y) {
  this->gc = gc;
  this->pos = (Position *)malloc(sizeof(Position));
  this->pos->x = x;
  this->pos->y = y;
}

void Character::move(Move direction) {
  Position intended_pos = *this->pos;

  switch (direction) {
  case UP:
    intended_pos.y--;
    break;
  case DOWN:
    intended_pos.y++;
    break;
  case LEFT:
    intended_pos.x--;
    break;
  case RIGHT:
    intended_pos.x++;
    break;
  default:
    return;
  }

  Position new_pos = gc->move(*this->pos, intended_pos);

  if (new_pos != *this->pos) {
    this->pos->x = new_pos.x;
    this->pos->y = new_pos.y;
  }
}

// Pacman

Pacman::Pacman(GameController *gc, unsigned int x, unsigned int y)
    : Character(gc, x, y) {}

void Pacman::move(Move direction) { Character::move(direction); }

// Ghost

Ghost::Ghost(GameController *gc, unsigned int x, unsigned int y)
    : Character(gc, x, y) {}

void Ghost::move() {
  Move direction = static_cast<Move>(rand() % 4);
  Character::move(direction);
}
