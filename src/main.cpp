#include "controllers.h"
#include "screen.h"
#include "utils.h"
#include <chrono>
#include <cstdio>
#include <thread>
#include <unistd.h>

using namespace std;

#define N_THREADS 4

int main() {
  GameController gc;
  WINDOW *window = gc.get_window();

  int pressed_key;
  while (true) {
    pressed_key = wgetch(window);

    // <Enter> key
    if (pressed_key == '\n') {
      gc.start();
      break;
    }

    usleep(INPUT_DELAY);
  }

  // characters
  Pacman pacman{&gc};
  auto ghosts_positions = gc.get_ghosts_positions();
  Ghost inky{&gc, BREADTH, ghosts_positions[0]};
  Ghost blinky{&gc, DEPTH, ghosts_positions[1]};
  Ghost clyde{&gc, RANDOM, ghosts_positions[2]};
  Ghost pinky{&gc, BEST, ghosts_positions[3]};

  auto user_input = [&pacman, &gc, &window]() {
    Direction dir;
    int pressed_key;

    /* allowed key sets:
     * w a s d
     * k h j l (vim movement)
     * ↑ ← ↓ →
     */

    while (true) {
      pressed_key = wgetch(window);

      // <Enter> key
      if (pressed_key == '\n') {
        gc.toggle_pause();
      } else if (gc.is_paused()) {
        continue;
      }

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

      this_thread::sleep_for(chrono::microseconds(INPUT_DELAY));
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

  auto screen_refreshing = [&]() {
    auto delay = min(GHOST_DELAY, PACMAN_DELAY);

    while (true) {
      /* gc.redraw_screen(); */
      gc.redraw_screen_changed();

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
      thread(screen_refreshing),
      thread(ghosts_movement),
  };

  for (int i = 0; i < N_THREADS; i++) {
    threads[i].join();
  }

  return 0;
}
