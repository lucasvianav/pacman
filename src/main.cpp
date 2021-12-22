#include "controllers.h"
#include "screen.h"
#include "utils.h"
#include <chrono>
#include <cstdio>
#include <curses.h>
#include <thread>
#include <unistd.h>

using namespace std;

#define N_THREADS 4

int main() {
  GameController gc;
  int pressed_key;

  // until <Enter> key is pressed
  while (pressed_key != '\n') {
    pressed_key = getch();
    usleep(INPUT_DELAY);
  }

  gc.start();

  // characters
  Pacman pacman{&gc};
  auto ghosts_positions = gc.get_ghosts_positions();
  Ghost inky{&gc, AI::BREADTH, ghosts_positions[0]};
  Ghost blinky{&gc, AI::DEPTH, ghosts_positions[1]};
  Ghost clyde{&gc, AI::RANDOM, ghosts_positions[2]};
  Ghost pinky{&gc, AI::BEST, ghosts_positions[3]};

  // receive user input
  auto user_input = [&pacman, &gc, &pressed_key]() {
    Direction dir;

    /* allowed key sets:
     * w a s d
     * k h j l (vim movement)
     * ↑ ← ↓ →
     */

    while (!gc.is_over()) {
      pressed_key = getch();

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

      this_thread::sleep_for(chrono::microseconds(INPUT_DELAY));
    }
  };

  // move pacman
  auto pacman_movement = [&pacman, &gc]() {
    while (!gc.is_over()) {
      pacman.move();
      this_thread::sleep_for(chrono::microseconds(PACMAN_DELAY));
    }
  };

  // redraw the screen everytime a character moves
  auto screen_refreshing = [&gc]() {
    auto delay = min(GHOST_DELAY, PACMAN_DELAY);

    while (!gc.is_over()) {
      gc.draw_screen();
      this_thread::sleep_for(chrono::microseconds(delay));
    }
  };

  // move ghosts
  auto ghosts_movement = [&inky, &blinky, &clyde, &pinky, &gc, &pacman]() {
    this_thread::sleep_for(chrono::seconds(1));
    Position pacman_pos;

    while (!gc.is_over()) {
      pacman_pos = pacman.get_position();

      inky.move(pacman_pos);
      blinky.move(pacman_pos);
      clyde.move(pacman_pos);
      pinky.move(pacman_pos);

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

  // until <Enter> key is pressed
  pressed_key = -1;
  while (pressed_key != '\n') {
    pressed_key = getch();
    usleep(INPUT_DELAY);
  }

  return 0;
}
