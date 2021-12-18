#include "controllers.h"
#include "map.h"
#include "utils.h"
#include <clocale>
#include <thread>

using namespace std;

int main() {
  setlocale(LC_ALL, "");

  GameController gc;
  Pacman pacman{&gc, 14, 20};
  Ghost inky{&gc, 12, 14};
  WINDOW *window = gc.get_window();

  auto user_input = [&pacman, &gc, &window]() {
    int delay = INPUT_DELAY;
    Direction dir;
    int pressed_key;

    /* allowed key sets:
     * w a s d
     * k h j l (vim movement)
     * ↑ ← ↓ →
     */

    while (true) {
      pressed_key = wgetch(window);

      // parse pressed key
      switch (pressed_key) {
      case KEY_UP:
      case 'w':
      case 'k':
        dir = UP;
        break;

      case KEY_RIGHT:
      case 'd':
      case 'l':
        dir = RIGHT;
        break;

      case KEY_DOWN:
      case 's':
      case 'j':
        dir = DOWN;
        break;

      case KEY_LEFT:
      case 'a':
      case 'h':
        dir = LEFT;
        break;

      // if it's not a valid
      // key, just ignore it
      default:
        continue;
      }

      pacman.turn(dir);

      if (should_quit() || gc.won()) {
        break;
      }

      this_thread::sleep_for(chrono::nanoseconds(delay));
    }
  };

  auto pacman_movement = [&pacman, &gc, &window]() {
    while (true) {
      pacman.move();

      if (should_quit() || gc.won()) {
        break;
      }

      this_thread::sleep_for(chrono::nanoseconds(PACMAN_DELAY));
    }
  };

  auto map_refreshing = [&]() {
    while (true) {
      gc.redraw();

      if (should_quit() || gc.won()) {
        break;
      }

      this_thread::sleep_for(chrono::nanoseconds(MAP_REFRESH_DELAY));
    }
  };

  auto inky_movement = [&inky, &gc]() {
    while (true) {
      inky.move();

      if (should_quit() || gc.won()) {
        break;
      }

      this_thread::sleep_for(chrono::nanoseconds(GHOST_DELAY));
    }
  };

  thread threads[4] = {
      thread(user_input),
      thread(pacman_movement),
      thread(map_refreshing),
      thread(inky_movement),
  };

  for (int i = 0; i < 4; i++) {
    threads[i].join();
  }

  return 0;
}
