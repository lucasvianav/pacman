#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include "map.h"
#include "utils.h"
#include <ncurses.h>

class GameController {
private:
  Map map;
  WINDOW *window;
  bool ghost_above_dot;
  unsigned int score;
  bool position_within_bounds(Position pos);
  void draw_map();

public:
  GameController();

  /* Move the charater from one position to another.
   * @param old_pos the target's original position.
   * @param new_pos the target's intended position.
   * @return the target's current position (after the move)
   */
  Position move(Position old_pos, Position new_pos);

  /* Refresh/redraw the game's map. */
  void refresh();

  /* Getter for the game window. */
  WINDOW *get_window();

  /* Getter for the game score. */
  int get_score();

  /* Did the player win? */
  bool won();

  /* Check if a position is blocked from a certain direction. */
  bool direction_blocked(Position pos, Move dir);
};

class Character {
protected:
  GameController *gc;
  Position *pos;

public:
  Character(GameController *gc, unsigned int x, unsigned int y);
  void move(Move direction);
};

class Pacman : public Character {
private:
  Move direction;

public:
  Pacman(GameController *gc, unsigned int x, unsigned int y);
  void turn(Move direction);
  void move();
};

class Ghost : public Character {
public:
  Ghost(GameController *gc, unsigned int x, unsigned int y);
  void move();
};

#endif
