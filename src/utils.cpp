#include "utils.h"
#include <cmath>

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

bool should_quit_ = false;

bool should_quit() { return should_quit_; }

void quit() { should_quit_ = true; }
