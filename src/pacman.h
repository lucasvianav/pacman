#ifndef PACMAN_H
#define PACMAN_H

#include "controllers.h"
#include "utils.h"

class Pacman {
private:
  GameController *gc;
  Position previous_pos;
  Position current_pos;

public:
  Pacman(GameController *gc, unsigned int x, unsigned int y);
  Position get_previous_position();
  Position get_current_position();
  void update_position(Move direction);
};

#endif
