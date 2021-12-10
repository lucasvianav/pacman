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

class Character {
protected:
  GameController *gc;
  Position previous_pos;
  Position current_pos;

public:
  Character(GameController *gc, unsigned int x, unsigned int y);
  Position get_previous_position();
  Position get_current_position();
  void update_position(Move direction, bool is_pacman);
};

class Pacman : public Character {
public:
  Pacman(GameController *gc, unsigned int x, unsigned int y);
  void update_position(Move direction);
};

class Ghost : public Character {
public:
  Ghost(GameController *gc, unsigned int x, unsigned int y);
  void update_position();
};

#endif
