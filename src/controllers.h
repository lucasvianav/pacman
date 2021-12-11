#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include "map.h"
#include "utils.h"
#include <ncurses.h>

class GameController {
private:
  /* Game map. */
  Map map;

  /* Game screen. */
  WINDOW *window;

  // TODO: expand this to work for all ghosts
  /* Is the ghost above a dot (point)? */
  bool ghost_above_dot;

  /* The player's score points. */
  unsigned int score;

  /* Draws the game map to the screen. */
  void draw_map();

public:
  GameController();

  /* Move a charater from one position to another.
   * @param `old_pos` the target's original position.
   * @param `new_pos` the target's intended position.
   * @return the target's current position (after the move).
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
  bool direction_blocked(Position pos, Direction dir);
};

class Character {
protected:
  GameController *gc;

  /* Character's current position. */
  Position *pos;

public:
  Character(GameController *gc, unsigned int x, unsigned int y);

  /* Move the charater one position in the given direction. */
  void move(Direction direction);
};

class Pacman : public Character {
private:
  Direction direction;

public:
  Pacman(GameController *gc, unsigned int x, unsigned int y);

  /* Alter the direction Pacman is heading to a new one. */
  void turn(Direction direction);

  /* Move Pacman one position to the direction it is heading. */
  void move();
};

class Ghost : public Character {
public:
  Ghost(GameController *gc, unsigned int x, unsigned int y);

  /* Move Ghost one position to a random direction. */
  void move();
};

#endif
