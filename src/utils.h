#ifndef POSITION_H
#define POSITION_H

#include <vector>

#define DOT '.'
#define GHOST_ICON '%'
#define PACMAN_ICON '@'
#define SPACE ' '

#define GHOST_DELAY 90000000
#define INPUT_DELAY 10000
#define PACMAN_DELAY 90000000
#define MAP_REFRESH_DELAY 90000000

/* UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 */
enum Direction { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };

struct Position {
public:
  /* Position in the x-axis. */
  unsigned int x;

  /* Position in the y-axis. */
  unsigned int y;

  /* Moves the point one position to a given direction. */
  Position move(Direction dir);

  bool operator==(const Position p);
  bool operator!=(const Position p);
  bool operator<(const Position p) const;
  Position &operator=(const Position &p);
};

/* Is the game over? */
bool should_quit();

/* Closes the game. */
void quit();

#endif
