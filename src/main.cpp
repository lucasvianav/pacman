#include "controllers.h"
#include "map.h"
#include "pacman.h"
#include "utils.h"
#include <ncurses.h>
#include <string>
#include <thread>
#include <unistd.h>

using namespace std;

class Ghost {
  GameController *gc;
  Position previous_pos;
  Position current_pos;

public:
  Ghost(GameController *game_ctrl, unsigned int x, unsigned int y) {
    gc = game_ctrl;
    current_pos.x = x;
    current_pos.y = y;
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
      new_pos.y--;

      if (gc->is_position_valid(new_pos, false)) {
        previous_pos = current_pos;
        current_pos.y--;
      }

      break;
    }

    // RIGHT
    case 1: {
      new_pos.x++;

      if (gc->is_position_valid(new_pos, false)) {
        previous_pos = current_pos;
        current_pos.x++;
      }

      break;
    }

    // DOWN
    case 2: {
      new_pos.y++;

      if (gc->is_position_valid(new_pos, false)) {
        previous_pos = current_pos;
        current_pos.y++;
      }

      break;
    }

    // LEFT
    case 3: {
      new_pos.x--;

      if (gc->is_position_valid(new_pos, false)) {
        previous_pos = current_pos;
        current_pos.x--;
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
