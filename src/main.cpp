#include "controllers.h"
#include "map.h"
#include "utils.h"
#include <chrono>
#include <clocale>
#include <ncurses.h>
#include <string>
#include <thread>
#include <unistd.h>

using namespace std;

int main() {
  setlocale(LC_ALL, "");

  GameController gc;
  Pacman pac{&gc, 14, 20};
  Ghost inky{&gc, 12, 14};

  auto keypress = [&pac, &gc]() {
    int c;
    Move direction;
    int delay = INPUT_DELAY;
    WINDOW *gamescr = gc.get_screen();

    while (true) {
      c = wgetch(gamescr);

      switch (c) {
      case KEY_UP:
      case 'w':
      case 'k':
        direction = UP;
        break;

      case KEY_RIGHT:
      case 'd':
      case 'l':
        direction = RIGHT;
        break;

      case KEY_DOWN:
      case 's':
      case 'j':
        direction = DOWN;
        break;

      case KEY_LEFT:
      case 'a':
      case 'h':
        direction = LEFT;
        break;

      default:
        continue;
      }

      pac.move(static_cast<Move>(direction));

      this_thread::sleep_for(chrono::nanoseconds(delay));
    }
  };

  auto game_controller = [&]() {
    while (true) {
      this_thread::sleep_for(chrono::nanoseconds(MAP_REFRESH_DELAY));
      gc.refresh();
    }
  };

  auto automove_ghosts = [&inky, &gc]() {
    while (true) {
      this_thread::sleep_for(chrono::nanoseconds(GHOST_DELAY));
      inky.move();
    }
  };

  thread t_kp = thread(keypress);
  thread t_gc = thread(game_controller);
  thread t_ag = thread(automove_ghosts);

  t_kp.join();
  t_gc.join();
  t_ag.join();

  return 0;
}
