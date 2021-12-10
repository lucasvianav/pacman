#include "controllers.h"
#include "map.h"
#include "utils.h"
#include <ncurses.h>
#include <string>
#include <thread>
#include <unistd.h>

using namespace std;

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
