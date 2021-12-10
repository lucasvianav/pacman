#include "utils.h"

bool Position::operator==(const Position p) {
  return this->x == p.x && this->y == p.y;
}

bool Position::operator!=(const Position p) {
  return this->x != p.x || this->y != p.y;
}

Position &Position::operator=(const Position &p) {
  x = p.x;
  y = p.y;
  return (*this);
}

bool should_quit_ = false;

bool should_quit() { return should_quit_; }

void quit() { should_quit_ = true; }
