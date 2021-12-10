#include "utils.h"

bool Position::operator==(const Position p) {
  return this->x == p.x && this->y == p.y;
}

Position &Position::operator=(const Position &p) {
  x = p.x;
  y = p.y;
  return (*this);
}
