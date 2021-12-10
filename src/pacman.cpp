#include "pacman.h"

Pacman::Pacman(GameController *gc, unsigned int x, unsigned int y) {
  this->gc = gc;
  this->current_pos.x = x;
  this->current_pos.y = y;
  this->previous_pos = current_pos;
}

Position Pacman::get_previous_position() { return this->previous_pos; }

Position Pacman::get_current_position() { return this->current_pos; }

void Pacman::update_position(Move direction) {
  Position new_pos = current_pos;

  switch (direction) {
  case UP:
    new_pos.y--;

    if (gc->is_position_valid(new_pos, true)) {
      previous_pos = current_pos;
      current_pos.y--;
    }

    break;
  case DOWN:
    new_pos.y++;

    if (gc->is_position_valid(new_pos, true)) {
      previous_pos = current_pos;
      current_pos.y++;
    }

    break;
  case LEFT:
    new_pos.x--;

    if (gc->is_position_valid(new_pos, true)) {
      previous_pos = current_pos;
      current_pos.x--;
    }

    break;
  case RIGHT:
    new_pos.x++;

    if (gc->is_position_valid(new_pos, true)) {
      previous_pos = current_pos;
      current_pos.x++;
    }

    break;
  }
}
