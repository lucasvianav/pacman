#ifndef POSITION_H
#define POSITION_H

#include <string>
#include <vector>

#define DOT '.'
#define GHOST_ICON '%'
#define PACMAN_ICON '@'
#define SPACE ' '

#define GHOST_DELAY 300000
#define INPUT_DELAY 10
#define PACMAN_DELAY 120000
#define SCREEN_REFRESHING_DELAY 300000

/* UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 */
enum Direction { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };

/* Artificial Intelligence type for a ghost.j */
enum AI { DEPTH, BREADTH, BEST, RANDOM };

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
  bool operator>(const Position p) const;
  double operator-(const Position p);
  Position &operator=(const Position &p);
  operator std::string();
};

#endif
