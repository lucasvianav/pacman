#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include "map.h"
#include "utils.h"
#include <iostream>
#include <map>
#include <mutex>
#include <ncurses.h>
#include <queue>

class GameController {
private:
  /* Game map. */
  Map map;

  /* Game screen. */
  WINDOW *window;

  /* Is the game paused? */
  bool paused;

  /* The player's score points. */
  unsigned int score;

  /* Was the game was redrawn while paused? */
  bool redrawn_paused;

  /* Draws the game map to the screen. */
  void draw_map();

public:
  GameController();
  ~GameController();

  /* Move a charater from one position to another.
   * @param `old_pos` the target's original position.
   * @param `new_pos` the target's intended position.
   * @param `overwrtten_char` pointer to a variable containing the character
   * that was previously in `old_pos`. It will be updated to the character in
   * `new_pos`.
   * @return the target's current position (after the move).
   */
  Position move(Position old_pos, Position new_pos, wchar_t *overwritten_char);

  /* Redraw the game's map. */
  void redraw();

  /* Refresh the screen. */
  void refresh();

  /* Reset the screen. */
  void reset();

  /* Play/pause the game. */
  void toggle_pause();

  /* Getter for the game window. */
  WINDOW *get_window();

  /* Getter for the game score. */
  int get_score();

  /* Did the player win? */
  bool won();

  /* Is the game paused? */
  bool is_paused();

  /* Check if a position is blocked from a certain direction. */
  bool direction_blocked(Position pos, Direction dir);

  /* Getter for the adjacency list of a given position. */
  vector<Position> get_adjacency_list(Position pos);

  /* Getter for the ghosts' initial positions. */
  vector<Position> get_ghosts_positions();

  /* Getter for Pacman's initial position. */
  Position get_pacman_position();
};

class Character {
protected:
  GameController *gc;

  /* Character's current position. */
  Position *pos;

public:
  Character(GameController *gc, Position pos);
  ~Character();

  /* Move the charater one position in the given direction. */
  void move(Direction direction, wchar_t *overwritten_char);

  /* Move the charater to the given position. */
  void move(Position intended_pos, wchar_t *overwritten_char);
};

class Pacman : public Character {
private:
  Direction direction;
  mutex m;

public:
  Pacman(GameController *gc);

  /* Alter the direction Pacman is heading to a new one. */
  void turn(Direction direction);

  /* Move Pacman one position to the direction it is heading. */
  void move();

  /* Getter for Pacman's position. */
  Position get_positon();
};

class Ghost : public Character {
private:
  /* The position the ghost was last in. */
  Position last_position;

  wchar_t overwritten_char;

  /* Find out where the ghost should go next. */
  Position find_next_move(Position pacman_pos);

  /* Type of artificial intelligence. */
  AI type;

public:
  Ghost(GameController *gc, AI type, Position pos);

  /* Move Ghost one position to a random direction. */
  void move(Position target);
};

#endif
