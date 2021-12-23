#ifndef POSITION_H
#define POSITION_H

#include <string>
#include <vector>

// icons
#define DOT_ICON '.'
#define GHOST_ICON '%'
#define PACMAN_ICON '@'
#define SPACE_ICON ' '
#define PORTAL_ICON '='

// delays
#define GHOST_DELAY 300000
#define INPUT_DELAY 10
#define PACMAN_DELAY 120000

/* UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 */
enum Direction { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };

/* Artificial Intelligence type for a ghost. */
enum class AI { DEPTH, BREADTH, BEST, RANDOM };

struct Position {
public:
  Position();
  Position(int x, int y);

  /* Position in the x-axis. */
  int x;

  /* Position in the y-axis. */
  int y;

  /* Moves the point one position to a given direction. */
  Position move(Direction dir);

  bool operator==(const Position p);
  bool operator!=(const Position p);
  bool operator<(const Position p) const;
  bool operator>(const Position p) const;
  bool operator!();
  double operator-(const Position p);
  Position &operator=(const Position &p);
  operator std::string();
  operator bool();
};

#endif
