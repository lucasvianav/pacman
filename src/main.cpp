#include "map.h"
#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include <string>
#include <thread>
#include <unistd.h>
#include <vector>

using namespace std;

enum Move { UP = 119, DOWN = 115, LEFT = 97, RIGHT = 100 };

struct Position {
  unsigned int pos_X;
  unsigned int pos_Y;

  bool operator==(const Position p) {
    if ((pos_X == p.pos_X) && (pos_Y == p.pos_Y)) {
      return true;
    } else {
      return false;
    }
  }

  Position &operator=(const Position &p) {
    pos_X = p.pos_X;
    pos_Y = p.pos_Y;

    return (*this);
  }
};

class GameController {
private:
  Map map = Map();

  bool position_within_bounds(Position pos) {
    int n_rows = this->map.get_n_rows();
    int n_cols = this->map.get_n_cols();

    return (pos.pos_X >= 0 && pos.pos_X < n_cols) &&
           (pos.pos_Y >= 0 && pos.pos_Y < n_rows);
  }

public:
  void load_map() {
    vector<vector<char>> map_chars = this->map.get_map();
    int n_rows = this->map.get_n_rows();
    int n_cols = this->map.get_n_cols();

    for (int i = 0; i < n_rows; i++) {
      for (int j = 0; j < n_cols; j++) {
        addch(map_chars[i][j]);
      }

      addch('\n');
    }
  }

  void update_map(char character, Position previous, Position current) {
    // TODO: remove
    // Position previous = pac.get_previous_position();
    // Position current = pac.get_current_position();

    // printw(to_string(previous.pos_X).c_str());
    // printw(to_string(previous.pos_Y).c_str());
    // addch('\n');

    // printw(to_string(current.pos_X).c_str());
    // printw(to_string(current.pos_Y).c_str());
    // addch('\n');

    this->map.update_map(previous.pos_X, previous.pos_Y, ' ');
    this->map.update_map(current.pos_X, current.pos_Y, character);

    erase();
    refresh();
    load_map();
  }

  bool is_position_valid(Position pos, bool is_pacman) {
    vector<vector<char>> map_chars = this->map.get_map();
    char c = map_chars[pos.pos_Y][pos.pos_X];

    return (this->position_within_bounds(pos) &&
            (c == 'o' || c == ' ' || (!is_pacman && (c == '@' || c == '%'))));
  }
};

class Pacman {
  GameController *gc;
  Position previous_pos;
  Position current_pos;

public:
  Pacman(GameController *game_ctrl, unsigned int pos_X, unsigned int pos_Y) {
    gc = game_ctrl;
    current_pos.pos_X = pos_X;
    current_pos.pos_Y = pos_Y;
    previous_pos = current_pos;
  }

  Position get_previous_position() { return previous_pos; }

  Position get_current_position() { return current_pos; }

  void update_position(Move direction) {
    Position new_pos = current_pos;

    if (direction == UP) {
      new_pos.pos_Y--;

      if (gc->is_position_valid(new_pos, true)) {
        previous_pos = current_pos;
        current_pos.pos_Y--;
      }
    } else if (direction == DOWN) {
      new_pos.pos_Y++;

      if (gc->is_position_valid(new_pos, true)) {
        previous_pos = current_pos;
        current_pos.pos_Y++;
      }
    } else if (direction == LEFT) {
      new_pos.pos_X--;

      if (gc->is_position_valid(new_pos, true)) {
        previous_pos = current_pos;
        current_pos.pos_X--;
      }
    } else if (direction == RIGHT) {
      new_pos.pos_X++;

      if (gc->is_position_valid(new_pos, true)) {
        previous_pos = current_pos;
        current_pos.pos_X++;
      }
    }
  }
};

class Ghost {
  GameController *gc;
  Position previous_pos;
  Position current_pos;

public:
  Ghost(GameController *game_ctrl, unsigned int pos_X, unsigned int pos_Y) {
    gc = game_ctrl;
    current_pos.pos_X = pos_X;
    current_pos.pos_Y = pos_Y;
    previous_pos = current_pos;
  }

  Position get_previous_position() { return previous_pos; }

  Position get_current_position() { return current_pos; }

  void update_position() {
    int direction = rand() % 4;
    Position new_pos = current_pos;

    switch (direction) {
    // UP
    case 0: {
      new_pos.pos_Y--;

      if (gc->is_position_valid(new_pos, false)) {
        previous_pos = current_pos;
        current_pos.pos_Y--;
      }

      break;
    }

    // RIGHT
    case 1: {
      new_pos.pos_X++;

      if (gc->is_position_valid(new_pos, false)) {
        previous_pos = current_pos;
        current_pos.pos_X++;
      }

      break;
    }

    // DOWN
    case 2: {
      new_pos.pos_Y++;

      if (gc->is_position_valid(new_pos, false)) {
        previous_pos = current_pos;
        current_pos.pos_Y++;
      }

      break;
    }

    // LEFT
    case 3: {
      new_pos.pos_X--;

      if (gc->is_position_valid(new_pos, false)) {
        previous_pos = current_pos;
        current_pos.pos_X--;
      }

      break;
    }

    default:
      break;
    }
  }
};

int main() {
  GameController game_ctrl;
  Pacman pac{&game_ctrl, 14, 20};
  Ghost inky{&game_ctrl, 12, 14};

  initscr();

  auto keypress = [&pac, &game_ctrl]() {
    char c = 0;

    while (true) {
      c = getch();

      pac.update_position(static_cast<Move>(c));
      game_ctrl.update_map('@', pac.get_previous_position(),
                           pac.get_current_position());
    }
  };

  auto game_controller = [&]() { game_ctrl.load_map(); };

  auto automove_ghosts = [&inky, &game_ctrl]() {
    while (true) {
      sleep(1);
      inky.update_position();
      game_ctrl.update_map('%', inky.get_previous_position(),
                           inky.get_current_position());
    }
  };

  thread kp = thread(keypress);
  thread gc = thread(game_controller);
  // thread ag = thread(automove_ghosts);

  kp.join();
  gc.join();
  // ag.join();

  return 0;
}
