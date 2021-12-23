#include "utils.h"
#include <cmath>

Position::Position() {
  this->x = -1;
  this->y = -1;
}

Position::Position(int x, int y) {
  this->x = x;
  this->y = y;
}

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

bool Position::operator<(const Position p) const {
  return sqrt(pow(this->x, 2) + pow(this->y, 2)) <
         sqrt(pow(p.x, 2) + pow(p.y, 2));
}

bool Position::operator>(const Position p) const {
  return sqrt(pow(this->x, 2) + pow(this->y, 2)) >
         sqrt(pow(p.x, 2) + pow(p.y, 2));
}

// for this use case, negative positions are not allowed
Position::operator bool() { return this->x >= 0 && this->y >= 0; }

bool Position::operator!() { return this->x < 0 || this->y < 0; }

double Position::operator-(const Position p) {
  return sqrt(pow(p.x - this->x, 2) + pow(p.y - this->y, 2));
}

Position::operator std::string() {
  return std::to_string(this->x) + ", " + std::to_string(this->y);
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
