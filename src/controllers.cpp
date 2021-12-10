#include "controllers.h"
#include <ncurses.h>
#include <stdlib.h>

using namespace std;

// GameController

GameController::GameController() { this->map = Map(); }

bool GameController::position_within_bounds(Position pos) {
  int n_rows = this->map.get_n_rows();
  int n_cols = this->map.get_n_cols();

  return (pos.x >= 0 && pos.x < n_cols) && (pos.y >= 0 && pos.y < n_rows);
}

void GameController::load_map() {
  vector<vector<char>> map_chars = this->map.get_map();
  int n_rows = this->map.get_n_rows();
  int n_cols = this->map.get_n_cols();

  for (int i = 0; i < n_rows; i++) {
    for (int j = 0; j < n_cols; j++) {
      addch(map_chars[i][j]);
    }

    addch('\n');
  }
}

void GameController::update_map(char character, Position previous,
                                Position current) {
  // TODO: remove
  // Position previous = pac.get_previous_position();
  // Position current = pac.get_current_position();

  // printw(to_string(previous.x).c_str());
  // printw(to_string(previous.y).c_str());
  // addch('\n');

  // printw(to_string(current.x).c_str());
  // printw(to_string(current.y).c_str());
  // addch('\n');

  this->map.update_map(previous.x, previous.y, ' ');
  this->map.update_map(current.x, current.y, character);

  erase();
  refresh();
  load_map();
}

bool GameController::is_position_valid(Position pos, bool is_pacman) {
  vector<vector<char>> map_chars = this->map.get_map();
  char c = map_chars[pos.y][pos.x];

  return (this->position_within_bounds(pos) &&
          (c == 'o' || c == ' ' || (!is_pacman && (c == '@' || c == '%'))));
}

// Character

Character::Character(GameController *gc, unsigned int x, unsigned int y) {
  this->gc = gc;
  this->current_pos.x = x;
  this->current_pos.y = y;
  this->previous_pos = current_pos;
}

Position Character::get_previous_position() { return this->previous_pos; }

Position Character::get_current_position() { return this->current_pos; }

void Character::update_position(Move direction, bool is_pacman) {
  Position new_pos = current_pos;

  switch (direction) {
  case UP:
    new_pos.y--;

    if (gc->is_position_valid(new_pos, is_pacman)) {
      previous_pos = current_pos;
      current_pos.y--;
    }

    break;
  case DOWN:
    new_pos.y++;

    if (gc->is_position_valid(new_pos, is_pacman)) {
      previous_pos = current_pos;
      current_pos.y++;
    }

    break;
  case LEFT:
    new_pos.x--;

    if (gc->is_position_valid(new_pos, is_pacman)) {
      previous_pos = current_pos;
      current_pos.x--;
    }

    break;
  case RIGHT:
    new_pos.x++;

    if (gc->is_position_valid(new_pos, is_pacman)) {
      previous_pos = current_pos;
      current_pos.x++;
    }

    break;
  }
}

// Pacman

Pacman::Pacman(GameController *gc, unsigned int x, unsigned int y)
    : Character(gc, x, y) {}

void Pacman::update_position(Move direction) {
  Character::update_position(direction, true);
}

// Ghost

Ghost::Ghost(GameController *gc, unsigned int x, unsigned int y)
    : Character(gc, x, y) {}

void Ghost::update_position() {
  int index = rand() % 4;
  Move directions[] = {UP, DOWN, LEFT, RIGHT};
  Move direction = directions[index];
  Character::update_position(direction, false);
}
