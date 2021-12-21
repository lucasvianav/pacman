#include "controllers.h"
#include "utils.h"
#include <algorithm>
#include <clocale>
#include <curses.h>
#include <ncurses.h>
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

/*
 *  ____                       ____            _             _ _
 * / ___| __ _ _ __ ___   ___ / ___|___  _ __ | |_ _ __ ___ | | | ___ _ __
 *| |  _ / _` | '_ ` _ \ / _ \ |   / _ \| '_ \| __| '__/ _ \| | |/ _ \ '__|
 *| |_| | (_| | | | | | |  __/ |__| (_) | | | | |_| | | (_) | | |  __/ |
 * \____|\__,_|_| |_| |_|\___|\____\___/|_| |_|\__|_|  \___/|_|_|\___|_|
 */

GameController::GameController() : screen("start") {
  // initializes ncurses
  setlocale(LC_ALL, "");
  this->window = initscr();
  keypad(this->window, true);
  nodelay(this->window, true);
  noecho();
  curs_set(false);
  cbreak();

  this->paused = true;
  this->redrawn_paused = false;
  this->score = 0;
  this->draw_screen();
}

GameController::~GameController() {
  endwin();
  cout << "\nGAME OVER! \nScore: " << this->score << "\n\n";
}

void GameController::draw_screen() {
  this->screen.draw(this->window, this->score, this->paused);
}

Position GameController::move(Position old_pos, Position new_pos, wchar_t *overwritten_char) {
  if (this->screen.position_valid(new_pos) && old_pos != new_pos) {
    wchar_t old_pos_cur_char = this->screen.get_char(old_pos);
    wchar_t new_pos_cur_char = this->screen.get_char(new_pos);

    bool is_pacman = old_pos_cur_char == PACMAN_ICON;

    wchar_t old_pos_new_char = *overwritten_char;
    wchar_t new_pos_new_char = old_pos_cur_char;

    switch (new_pos_cur_char) {
    case GHOST_ICON:
      if (!is_pacman) {
        return old_pos;
      }

    case PACMAN_ICON:
      quit();
      break;

    case DOT:
      if (is_pacman) {
        this->score++;
      }
      break;

    case SPACE:
      break;

    default:
      return old_pos;
    }

    this->screen.set_char(old_pos, old_pos_new_char);
    this->screen.set_char(new_pos, new_pos_new_char);

    *overwritten_char = new_pos_cur_char;
    return new_pos;
  }

  return old_pos;
}

void GameController::redraw_screen() {
  if (this->paused) {
    if (this->redrawn_paused) {
      return;
    } else {
      this->redrawn_paused =  true;
    }
  }

  erase();
  wrefresh(this->window);
  this->draw_screen();
}

void GameController::redraw_screen_changed() {
  if (this->paused) {
    if (this->redrawn_paused) {
      return;
    } else {
      this->redrawn_paused =  true;
    }
  }

  this->screen.redraw(window, this->score);
}

void GameController::refresh() { wrefresh(this->window); }

void GameController::reset() {
  erase();
  wrefresh(this->window);
}

void GameController::toggle_pause() {
  if (!this->won() || should_quit()) {
    this->paused = !this->paused;
    this->redrawn_paused = false;
  } else {
    this->paused = false;
  }
}

void GameController::start() {
  this->screen = Screen("map-01");
  this->paused = false;
  this->redrawn_paused = false;
  this->redraw_screen();
}

WINDOW *GameController::get_window() { return this->window; }

int GameController::get_score() { return this->score; }

bool GameController::won() { return this->score == this->screen.get_n_dots(); }

bool GameController::is_paused() { return this->paused; }

bool GameController::direction_blocked(Position pos, Direction dir) {
  wchar_t character = this->screen.get_char(pos.move(dir));
  return character != DOT && character != SPACE;
}

vector<Position> GameController::get_adjacency_list(Position pos) {
  return this->screen.get_adjacency_list(pos);
}

vector<Position> GameController::get_ghosts_positions() {
  return this->screen.ghosts_positions;
}

Position GameController::get_pacman_position() {
  return this->screen.pacman_posision;
}

/*
 *  ____ _   _    _    ____      _    ____ _____ _____ ____
 * / ___| | | |  / \  |  _ \    / \  / ___|_   _| ____|  _ \
 *| |   | |_| | / _ \ | |_) |  / _ \| |     | | |  _| | |_) |
 *| |___|  _  |/ ___ \|  _ <  / ___ \ |___  | | | |___|  _ <
 * \____|_| |_/_/   \_\_| \_\/_/   \_\____| |_| |_____|_| \_\
 */

Character::Character(GameController *gc, Position pos) {
  this->gc = gc;
  this->pos = (Position *)malloc(sizeof(Position));
  this->pos->x = pos.x;
  this->pos->y = pos.y;
}

void Character::move(Direction direction, wchar_t *overwritten_char) {
  Position intended_pos = (*this->pos);
  intended_pos.move(direction);

  Position new_pos = gc->move(*this->pos, intended_pos, overwritten_char);

  if (new_pos != *this->pos) {
    this->pos->x = new_pos.x;
    this->pos->y = new_pos.y;
  }
}

void Character::move(Position intended_pos, wchar_t *overwritten_char) {
  Position new_pos = gc->move(*this->pos, intended_pos, overwritten_char);

  if (new_pos != *this->pos) {
    this->pos->x = new_pos.x;
    this->pos->y = new_pos.y;
  }
}

Character::~Character() { std::free(this->pos); }

/*
 * ____   _    ____ __  __    _    _   _
 *|  _ \ / \  / ___|  \/  |  / \  | \ | |
 *| |_) / _ \| |   | |\/| | / _ \ |  \| |
 *|  __/ ___ \ |___| |  | |/ ___ \| |\  |
 *|_| /_/   \_\____|_|  |_/_/   \_\_| \_|
 */

Pacman::Pacman(GameController *gc)
    : Character(gc, gc->get_pacman_position()) {
  this->direction = RIGHT;
}

void Pacman::move() {
  if (this->gc->is_paused()) {
    return;
  }

  this->m.lock();
  wchar_t space = SPACE;
  Character::move(this->direction, &space);
  this->m.unlock();
}

void Pacman::turn(Direction dir) {
  if (this->gc->is_paused()) {
    return;
  }

  bool is_blocked = this->gc->direction_blocked(*this->pos, dir);
  if (!is_blocked) {
    this->direction = dir;
  }
}

Position Pacman::get_positon() {
  this->m.lock();
  Position pos = *this->pos;
  this->m.unlock();

  return pos;
}

/*
 *  ____ _   _  ___  ____ _____
 * / ___| | | |/ _ \/ ___|_   _|
 *| |  _| |_| | | | \___ \ | |
 *| |_| |  _  | |_| |___) || |
 * \____|_| |_|\___/|____/ |_|
 */

Ghost::Ghost(GameController *gc, AI type, Position pos)
    : Character(gc, pos) {
  this->last_position.x = pos.x;
  this->last_position.y = pos.y;
  this->type = type;
  this->overwritten_char = ' ';
}

void Ghost::move(Position target) {
  if (this->gc->is_paused()) {
    return;
  }

  Position pos = this->find_next_move(target);
  this->last_position = *this->pos;
  Character::move(pos, &this->overwritten_char);
}

Position Ghost::find_next_move(Position target) {
  if (type != RANDOM) {
    // list of all paths to be analyzed (the next node to
    // be visited is the last one on each path)
    vector<vector<Position>> backlog;

    // all analyzed nodes
    vector<Position> history;

    vector<Position> path;
    path.push_back(*(this->pos));
    backlog.push_back(path);

    // list of the euclidian distances between all nodes in the
    // backlog and the target (only used for Best First Searches)
    vector<double> distances;
    if (this->type == BEST) {
      distances.push_back(target - *this->pos);
    }

    while (!backlog.empty()) {
      // if it's performing a Best First Search, select the node that's closest to the
      // target (aka the node at the same index as the lowest value in distances)
      if (this->type == BEST) {
        auto lowest_distance = min_element(distances.begin(), distances.end());
        int selected_index = distance(distances.begin(), lowest_distance);

        path = backlog.at(selected_index);

        backlog.erase(backlog.begin() + selected_index);
        distances.erase(distances.begin() + selected_index);
      } else if (this->type == DEPTH) { // DFS: LIFO
        path = backlog.back();
        backlog.pop_back();
      } else { // BFS: FIFO
        path = backlog.front();
        backlog.erase(backlog.begin());
      }

      // currently being analyzed node
      Position current = path[path.size() - 1];

      // if either the current node was already analyzed
      // or the current path goes back to the position the
      // ghost just left, then skip to the next one
      int was_analyzed = count(history.begin(), history.end(), current);
      if (was_analyzed || path[1] == this->last_position) {
        continue;
      }

      // if the target is found, returns the next position in path
      // (path[0] is the ghost's current posision)
      if (current == target) {
        return path[1];
      }

      auto adjacencies = this->gc->get_adjacency_list(current);

      history.push_back(current);

      // loops through each adjacent node, marking
      // a new path that ends in it to be analyzed
      for (Position node : adjacencies) {
        vector<Position> new_path(path);
        new_path.push_back(node);
        double distance = target - node;

        backlog.push_back(new_path);
        distances.push_back(distance);
      }
    }
  }

  Position random;
  do {
    random = *this->pos;
    Direction direction = static_cast<Direction>(rand() % 4);
    random.move(direction);
  } while (random == this->last_position);

  return random;
}

