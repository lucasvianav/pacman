#include "controllers.h"
#include "map.h"
#include "utils.h"
#include <chrono>
#include <clocale>
#include <thread>

using namespace std;

#define N_THREADS 4

int main() {
  setlocale(LC_ALL, "");

  GameController gc;
  Pacman pacman{&gc};
  WINDOW *window = gc.get_window();

  auto ghosts_positions = gc.get_ghosts_positions();
  Ghost inky{&gc, BREADTH, ghosts_positions[0]};
  Ghost blinky{&gc, DEPTH, ghosts_positions[1]};
  Ghost clyde{&gc, RANDOM, ghosts_positions[2]};
  Ghost pinky{&gc, BEST, ghosts_positions[3]};

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

      this_thread::sleep_for(chrono::microseconds(delay));
    }
  };

  auto pacman_movement = [&pacman, &gc, &window]() {
    while (true) {
      pacman.move();

      if (should_quit() || gc.won()) {
        break;
      }

      this_thread::sleep_for(chrono::microseconds(PACMAN_DELAY));
    }
  };

  auto map_refreshing = [&]() {
    auto delay = min(GHOST_DELAY, PACMAN_DELAY);

    while (true) {
      gc.redraw();

      if (should_quit() || gc.won()) {
        break;
      }

      this_thread::sleep_for(chrono::microseconds(delay));
    }
  };

  auto ghosts_movement = [&inky, &blinky, &clyde, &pinky, &gc, &pacman]() {
    this_thread::sleep_for(chrono::seconds(1));

    while (true) {
      inky.move(pacman.get_positon());
      blinky.move(pacman.get_positon());
      clyde.move(pacman.get_positon());
      pinky.move(pacman.get_positon());

      if (should_quit() || gc.won()) {
        break;
      }

      this_thread::sleep_for(chrono::microseconds(GHOST_DELAY));
    }
  };

  thread threads[N_THREADS] = {
      thread(user_input),
      thread(pacman_movement),
      thread(map_refreshing),
      thread(ghosts_movement),
  };

  for (int i = 0; i < N_THREADS; i++) {
    threads[i].join();
  }

  return 0;
}
