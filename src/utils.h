#ifndef POSITION_H
#define POSITION_H

#include <vector>

#define DOT '.'
#define GHOST_ICON '%'
#define PACMAN_ICON '@'
#define SPACE ' '

#define GHOST_DELAY 90000000
#define INPUT_DELAY 1000
#define MAP_REFRESH_DELAY 90000000

struct Position {
public:
  unsigned int x;
  unsigned int y;
  bool operator==(const Position p);
  bool operator!=(const Position p);
  Position &operator=(const Position &p);
};

enum Move { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };

bool should_quit();
void quit();

#endif
