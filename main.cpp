#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <thread>
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

  Position& operator=(const Position& p) {
    pos_X = p.pos_X;
    pos_Y = p.pos_Y;

    return (*this);
  }
};

class Game_Controller {
  vector<vector<char>> map {
    {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
    {'*','o','o','o','o','o','o','o','o','o','o','o','o','*','*','o','o','o','o','o','o','o','o','o','o','o','o','*'},
    {'*','o','*','*','*','*','o','*','*','*','*','*','o','*','*','o','*','*','*','*','*','o','*','*','*','*','o','*'},
    {'*','o','*','*','*','*','o','*','*','*','*','*','o','o','o','o','*','*','*','*','*','o','*','*','*','*','o','*'},
    {'*','o','*','*','*','*','o','*','*','*','*','*','o','*','*','o','*','*','*','*','*','o','*','*','*','*','o','*'},
    {'*','o','o','o','o','o','o','o','o','o','o','o','o','*','*','o','o','o','o','o','o','o','o','o','o','o','o','*'},
    {'*','o','*','*','*','*','o','*','*','o','*','*','*','*','*','*','*','*','o','*','*','o','*','*','*','*','o','*'},
    {'*','o','*','*','*','*','o','*','*','o','*','*','*','*','*','*','*','*','o','*','*','o','*','*','*','*','o','*'},
    {'*','o','o','o','o','o','o','*','*','o','o','o','o','*','*','o','o','o','o','*','*','o','o','o','o','o','o','*'},
    {'*','*','*','o','*','*','o','*','*','*','*','*','o','*','*','o','*','*','*','*','*','o','*','*','o','*','*','*'},
    {'*','*','*','o','*','*','o','*','*','*','*','*','o','*','*','o','*','*','*','*','*','o','*','*','o','*','*','*'},
    {'*','o','o','o','*','*','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','*','*','o','o','o','*'},
    {'*','o','*','*','*','*','o','*','*','o','#','#','#',' ',' ','#','#','#','o','*','*','o','*','*','*','*','o','*'},
    {'*','o','*','*','*','*','o','*','*','o','#',' ',' ',' ',' ',' ',' ','#','o','*','*','o','*','*','*','*','o','*'},
    {'*','o','o','o','o','o','o','*','*','o','#',' ','%','%','%','%',' ','#','o','*','*','o','o','o','o','o','o','*'},
    {'*','o','*','*','*','*','o','*','*','o','#',' ',' ',' ',' ',' ',' ','#','o','*','*','o','*','*','*','*','o','*'},
    {'*','o','*','*','*','*','o','*','*','o','#','#','#','#','#','#','#','#','o','*','*','o','*','*','*','*','o','*'},
    {'*','o','o','o','*','*','o','*','*','o','o','o','o','o','o','o','o','o','o','*','*','o','*','*','o','o','o','*'},
    {'*','*','*','o','*','*','o','*','*','o','*','*','*','*','*','*','*','*','o','*','*','o','*','*','o','*','*','*'},
    {'*','*','*','o','*','*','o','*','*','o','*','*','*','*','*','*','*','*','o','*','*','o','*','*','o','*','*','*'},
    {'*','o','o','o','o','o','o','o','o','o','o','o','o','o','@','o','o','o','o','o','o','o','o','o','o','o','o','*'},
    {'*','o','*','*','*','*','o','*','*','*','*','*','o','*','*','o','*','*','*','*','*','o','*','*','*','*','o','*'},
    {'*','o','*','*','*','*','o','*','*','*','*','*','o','*','*','o','*','*','*','*','*','o','*','*','*','*','o','*'},
    {'*','o','o','o','*','*','o','o','o','o','o','o','o','*','*','o','o','o','o','o','o','o','*','*','o','o','o','*'},
    {'*','*','*','o','*','*','o','*','*','o','*','*','*','*','*','*','*','*','o','*','*','o','*','*','o','*','*','*'},
    {'*','*','*','o','*','*','o','*','*','o','*','*','*','*','*','*','*','*','o','*','*','o','*','*','o','*','*','*'},
    {'*','o','o','o','o','o','o','*','*','o','o','o','o','*','*','o','o','o','o','*','*','o','o','o','o','o','o','*'},
    {'*','o','*','*','*','*','o','*','*','*','*','*','o','*','*','o','*','*','*','*','*','o','*','*','*','*','o','*'},
    {'*','o','*','*','*','*','o','*','*','*','*','*','o','*','*','o','*','*','*','*','*','o','*','*','*','*','o','*'},
    {'*','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','*'},
    {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'}
  };

  public:
    void load_map() {
      int j;

      for (int i = 0; i < 31; i++) {
        for (j = 0; j < 28; j++)
          addch(map[i][j]);

        addch('\n');
      }
    }

    void update_map(char c, Position previous, Position current) {
      //Position previous = pac.get_previous_position();
      //Position current = pac.get_current_position();

      //printw(to_string(previous.pos_X).c_str());
      //printw(to_string(previous.pos_Y).c_str());
      //addch('\n');

      //printw(to_string(current.pos_X).c_str());
      //printw(to_string(current.pos_Y).c_str());
      //addch('\n');

      map[previous.pos_Y][previous.pos_X] = ' ';
      map[current.pos_Y][current.pos_X] = c;

      erase();
      refresh();
      load_map();
    }

    bool is_position_valid(Position pos, bool is_pacman) {
      if (is_pacman) {
        return ((pos.pos_X >= 0 && pos.pos_X < 28) && 
                (pos.pos_Y >= 0 && pos.pos_Y < 31) && 
                (map[pos.pos_Y][pos.pos_X] == 'o' || 
                 map[pos.pos_Y][pos.pos_X] == ' '));
      } else {
        return ((pos.pos_X >= 0 && pos.pos_X < 28) && 
                (pos.pos_Y >= 0 && pos.pos_Y < 31) && 
                (map[pos.pos_Y][pos.pos_X] == 'o' || 
                 map[pos.pos_Y][pos.pos_X] == ' ' || 
                 map[pos.pos_Y][pos.pos_X] == '@' ||
                 map[pos.pos_Y][pos.pos_X] == '%'));
      }
    }
};

class Pacman {
  Game_Controller *gc;
  Position previous_pos;
  Position current_pos;

  public:
    Pacman(Game_Controller *game_ctrl, unsigned int pos_X, unsigned int pos_Y) {
      gc = game_ctrl;
      current_pos.pos_X = pos_X;
      current_pos.pos_Y = pos_Y;
      previous_pos = current_pos;
    }

    Position get_previous_position() {
      return previous_pos;
    }

    Position get_current_position() {
      return current_pos;
    }

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
  Game_Controller *gc;
  Position previous_pos;
  Position current_pos;

  public:
    Ghost(Game_Controller *game_ctrl, unsigned int pos_X, unsigned int pos_Y) {
      gc = game_ctrl;
      current_pos.pos_X = pos_X;
      current_pos.pos_Y = pos_Y;
      previous_pos = current_pos;
    }

    Position get_previous_position() {
      return previous_pos;
    }

    Position get_current_position() {
      return current_pos;
    }

    void update_position() {
      int direction = rand() % 4;
      Position new_pos = current_pos;

      switch(direction) {
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

        default: break;
      }
    }
};

int main() {
  Game_Controller game_ctrl;
  Pacman pac { &game_ctrl, 14, 20 };
  Ghost inky { &game_ctrl, 12, 14 };

  initscr();

  auto keypress = [&pac, &game_ctrl]() {
    char c = 0;

    while (true) {
      c = getch();

      switch(c) {
        case static_cast<char>(UP): {
          pac.update_position(static_cast<Move>(c));
          game_ctrl.update_map('@', pac.get_previous_position(), pac.get_current_position());
          break;
        }

	      case static_cast<char>(DOWN): {
          pac.update_position(static_cast<Move>(c));
          game_ctrl.update_map('@', pac.get_previous_position(), pac.get_current_position());
          break;
	      }

	      case static_cast<char>(LEFT): {
          pac.update_position(static_cast<Move>(c));
          game_ctrl.update_map('@', pac.get_previous_position(), pac.get_current_position());
          break;
	      }

	      case static_cast<char>(RIGHT): {
          pac.update_position(static_cast<Move>(c));
          game_ctrl.update_map('@', pac.get_previous_position(), pac.get_current_position());
          break;
	      }

        default: break;
      }
    }
  };

  auto game_controller = [&]() {
    game_ctrl.load_map();
  };

  auto automove_ghosts = [&inky, &game_ctrl]() {
    while (true) {
      sleep(1);
      inky.update_position();
      game_ctrl.update_map('%', inky.get_previous_position(), inky.get_current_position());      
    }
  };

  thread kp = thread(keypress);
  thread gc = thread(game_controller);
  //thread ag = thread(automove_ghosts);

  kp.join();
  gc.join();
  //ag.join();

  return 0;
}