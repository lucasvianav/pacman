#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include "map.h"
#include "utils.h"
#include <ncurses.h>

class GameController {
private:
  Map map;
  bool position_within_bounds(Position pos);
  void draw_map();
  WINDOW *gamescr;

public:
  GameController();

  /* Move the charater from one position to another.
   * @param old_pos the target's original position.
   * @param new_pos the target's intended position.
   * @return the target's current position (after the move)
   */
  Position move(Position old_pos, Position new_pos, bool is_pacman);

  /* Refresh/redraw the game's map. */
  void refresh();

  /* Check if a position is valid for either Pacman or a ghost. */
  bool is_position_valid(Position pos);

  /* Getter for the game window. */
  WINDOW *get_screen();
};

class Character {
protected:
  GameController *gc;
  Position *pos;

public:
  Character(GameController *gc, unsigned int x, unsigned int y);
  void move(Move direction, bool is_pacman);
};

class Pacman : public Character {
public:
  Pacman(GameController *gc, unsigned int x, unsigned int y);
  void move(Move direction);
};

class Ghost : public Character {
public:
  Ghost(GameController *gc, unsigned int x, unsigned int y);
  void move();
};

#endif
