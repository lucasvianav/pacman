#include "utils.h"

bool Position::operator==(const Position p) {
  return this->x == p.x && this->y == p.y;
}

bool Position::operator!=(const Position p) {
  return this->x != p.x || this->y != p.y;
}

Position &Position::operator=(const Position &p) {
  this->x = p.x;
  this->y = p.y;
  return *this;
}

Position Position::move(Direction dir) {
  switch (dir) {
  case UP:
    this->y--;
    break;
  case DOWN:
    this->y++;
    break;
  case LEFT:
    this->x--;
    break;
  case RIGHT:
    this->x++;
    break;
  }

  return *this;
}

bool should_quit_ = false;

bool should_quit() { return should_quit_; }

void quit() { should_quit_ = true; }
