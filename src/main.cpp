#include "controllers.h"
#include "map.h"
#include "utils.h"
#include <chrono>
#include <clocale>
#include <cstdio>
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
  WINDOW *window = gc.get_window();

  auto keypress = [&pac, &gc, &window]() {
    int delay = INPUT_DELAY;

    while (true) {
      int c = wgetch(window);
      Move dir;

      switch (c) {
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

      default:
        continue;
      }

      pac.turn(dir);

      if (should_quit() || gc.won()) {
        break;
      }

      this_thread::sleep_for(chrono::nanoseconds(delay));
    }
  };

  auto pacman = [&pac, &gc, &window]() {
    while (true) {
      pac.move();

      if (should_quit() || gc.won()) {
        break;
      }

      this_thread::sleep_for(chrono::nanoseconds(PACMAN_DELAY));
    }
  };

  auto game_controller = [&]() {
    while (true) {
      gc.refresh();

      if (should_quit() || gc.won()) {
        char score[15];
        sprintf(score, "GAME OVER! %d", gc.get_score());

        waddstr(window, score);
        break;
      }

      this_thread::sleep_for(chrono::nanoseconds(MAP_REFRESH_DELAY));
    }
  };

  auto automove_ghosts = [&inky, &gc]() {
    while (true) {
      inky.move();

      if (should_quit() || gc.won()) {
        break;
      }

      this_thread::sleep_for(chrono::nanoseconds(GHOST_DELAY));
    }
  };

  thread t_kp = thread(keypress);
  thread t_pc = thread(pacman);
  thread t_gc = thread(game_controller);
  thread t_ag = thread(automove_ghosts);

  t_kp.join();
  t_pc.join();
  t_gc.join();
  t_ag.join();

  return 0;
}
