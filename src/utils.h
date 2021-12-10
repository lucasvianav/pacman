#include <vector>

#ifndef POSITION_H
#define POSITION_H

using namespace std;

struct Position {
public:
  unsigned int x;
  unsigned int y;
  bool operator==(const Position p);
  Position &operator=(const Position &p);
};

enum Move { UP = 119, DOWN = 115, LEFT = 97, RIGHT = 100 };

#endif
