#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include "map.h"
#include "utils.h"

class GameController {
private:
  Map map;
  bool position_within_bounds(Position pos);

public:
  GameController();
  void load_map();
  void update_map(char character, Position previous, Position current);
  bool is_position_valid(Position pos, bool is_pacman);
};

#endif
