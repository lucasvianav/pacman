#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include "screen.h"
#include "utils.h"
#include <iostream>
#include <mutex>
#include <ncurses.h>
#include <queue>

class GameController {
private:
  mutex paused_mutex;
  mutex score_mutex;
  mutex game_over_mutex;

  /* Game screen being currently displayed. */
  Screen screen;

  /* Game screen. */
  WINDOW *window;

  /* Is the game paused? */
  bool paused;

  /* The player's score points. */
  unsigned int score;

  /* Did the player lose? */
  bool game_over;

  /* Was the game was redrawn while paused? */
  bool redrawn_paused;

public:
  GameController();
  ~GameController();

  /*
   * Move a charater from one position to another.
   * @param `old_pos` the target's original position.
   * @param `new_pos` the target's intended position.
   * @param `overwrtten_char` pointer to a variable containing the character
   * that was previously in `old_pos`. It will be updated to the character in
   * `new_pos`.
   * @return the target's current position (after the move).
   */
  Position move(Position old_pos, Position new_pos, char *overwritten_char);

  /* Draws the game screen to the terminal. */
  void draw_screen();

  /* Reset the screen. */
  void reset_screen();

  /* Play/pause the game. */
  void toggle_pause();

  /* Start the game. */
  void start();

  /* Getter for the game window. */
  WINDOW *get_window();

  /* Getter for the game score. */
  int get_score();

  /* Did the player win? */
  bool won();

  /* Is the game over? */
  bool is_over();

  /* Closes the game. */
  void quit();

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
  void move(Direction direction, char *overwritten_char);

  /* Move the charater to the given position. */
  void move(Position intended_pos, char *overwritten_char);
};

class Pacman : public Character {
private:
  Direction direction;
  mutex position_mutex;
  mutex direction_mutex;

public:
  Pacman(GameController *gc);

  /* Alter the direction Pacman is heading to a new one. */
  void turn(Direction direction);

  /* Move Pacman one position to the direction it is heading. */
  void move();

  /* Getter for Pacman's position. */
  Position get_position();
};

class Ghost : public Character {
private:
  mutex overwritten_char_mutex;

  /* The position the ghost was last in. */
  Position last_position;

  /* The previous char from the position the ghost is currently in. */
  char overwritten_char;

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
