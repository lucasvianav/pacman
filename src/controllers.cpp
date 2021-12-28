#include "controllers.h"
#include "utils.h"
#include <algorithm>
#include <clocale>
#include <cstdio>
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

  this->game_over = false;
  this->score = 0;
  this->paused = true;
  this->redrawn_paused = false;
  this->draw_screen();
}

GameController::~GameController() {
  delwin(this->window);
  endwin();
}

Position GameController::move(Position old_pos, Position new_pos, char *overwritten_char) {
  if (this->screen.position_valid(new_pos) && old_pos != new_pos) {
    char old_pos_cur_char = this->screen.get_char(old_pos);
    bool is_pacman = old_pos_cur_char == PACMAN_ICON;

    // if the character just entered a
    // portal, teleport it to the other one
    if (new_pos == this->screen.portal_position_1) {
      new_pos = this->screen.portal_position_2;
    } else if (new_pos == this->screen.portal_position_2) {
      new_pos = this->screen.portal_position_1;
    }

    char new_pos_cur_char = this->screen.get_char(new_pos);

    char old_pos_new_char = overwritten_char ? *overwritten_char : SPACE_ICON;
    char new_pos_new_char = old_pos_cur_char;

    switch (new_pos_cur_char) {
    case GHOST_ICON:
      if (!is_pacman) {
        return old_pos;
      } else {
        this->quit();
        break;
      }

    case PACMAN_ICON:
      this->quit();
      break;

    case DOT_ICON:
      if (is_pacman) {
        this->score_mutex.lock();
        this->score++;
        this->score_mutex.unlock();

        if (this->won()) {
          quit();
        }
      }
      break;

    case SPACE_ICON:
      // don't let Pacman go through a barrier if it's heading there
      for(auto barrier_pos : this->screen.barrier_positions) {
        if (new_pos == barrier_pos && is_pacman) {
          return old_pos;
        }
      }
      break;

    default:
      return old_pos;
    }

    this->screen.set_chars({old_pos, new_pos},
        {old_pos_new_char, new_pos_new_char});

    if (overwritten_char) {
      *overwritten_char = new_pos_cur_char;
    }

    return new_pos;
  }

  return old_pos;
}

void GameController::draw_screen() {
  this->paused_mutex.lock();
  if (this->paused) {
    if (this->redrawn_paused) {
      this->paused_mutex.unlock();
      return;
    } else {
      this->redrawn_paused = true;
    }
  }
  this->paused_mutex.unlock();

  this->screen.draw(this->score, this->paused);
}

void GameController::reset_screen() {
  werase(this->window);
  wrefresh(this->window);
}

void GameController::toggle_pause() {
  this->paused_mutex.lock();
  if (!this->is_over()) {
    this->paused = !this->paused;
   this->redrawn_paused = false;
  } else {
    this->paused = false;
  }
  this->paused_mutex.unlock();

  this->reset_screen();
  this->draw_screen();
}

void GameController::start() {
  this->screen = Screen("map-01");
  this->paused = false;
  this->redrawn_paused = false;

  this->reset_screen();
  this->draw_screen();
}

WINDOW *GameController::get_window() { return this->window; }

int GameController::get_score() {
  this->score_mutex.lock();
  auto score = this->score;
  this->score_mutex.unlock();

  return score;
}

bool GameController::won() {
  this->score_mutex.lock();
  bool won = this->score > 0 && this->score == this->screen.get_n_dots();
  this->score_mutex.unlock();

  return won;
}

bool GameController::is_over() {
  this->game_over_mutex.lock();
  bool over = this->game_over;
  this->game_over_mutex.unlock();

  return over || this->won();
}

void GameController::quit() {
  this->game_over_mutex.lock();
  this->game_over = true;
  this->game_over_mutex.unlock();

  if (this->won()) {
    this->screen = Screen("you-win");
  } else {
    this->screen = Screen("game-over");
  }

  this->reset_screen();
  this->draw_screen();
}

bool GameController::is_paused() {
  this->paused_mutex.lock();
  auto paused = this->paused;
  this->paused_mutex.unlock();

  return paused;
}

bool GameController::direction_blocked(Position pos, Direction dir) {
  pos = pos.move(dir);

  // don't let Pacman turn to the direction of a barrier
  for(auto barrier_pos : this->screen.barrier_positions) {
    if (pos == barrier_pos) {
      return true;
    }
  }

  return !this->screen.is_walkable(pos);
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

void Character::move(Direction direction, char *overwritten_char) {
  Position intended_pos = (*this->pos);
  intended_pos.move(direction);

  Position new_pos = gc->move(*this->pos, intended_pos, overwritten_char);

  if (new_pos != *this->pos) {
    this->pos->x = new_pos.x;
    this->pos->y = new_pos.y;
  }
}

void Character::move(Position intended_pos, char *overwritten_char) {
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
  this->direction_mutex.lock();
  this->direction = RIGHT;
  this->direction_mutex.unlock();
}

void Pacman::move() {
  if (this->gc->is_paused()) {
    return;
  }

  this->direction_mutex.lock();
  Direction dir = this->direction;
  this->direction_mutex.unlock();

  this->position_mutex.lock();
  Character::move(dir, NULL);
  this->position_mutex.unlock();
}

void Pacman::turn(Direction dir) {
  if (this->gc->is_paused()) {
    return;
  }

  this->position_mutex.lock();
  bool is_blocked = this->gc->direction_blocked(*this->pos, dir);
  this->position_mutex.unlock();

  if (!is_blocked) {
    this->direction_mutex.lock();
    this->direction = dir;
    this->direction_mutex.unlock();
  }
}

Position Pacman::get_position() {
  this->position_mutex.lock();
  Position pos = *this->pos;
  this->position_mutex.unlock();

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

  this->overwritten_char_mutex.lock();
  Character::move(pos, &this->overwritten_char);
  this->overwritten_char_mutex.unlock();
}

Position Ghost::find_next_move(Position target) {
  if (type != AI::RANDOM) {
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
    if (this->type == AI::BEST) {
      distances.push_back(target - *this->pos);
    }

    while (!backlog.empty()) {
      // if it's performing a Best First Search, select the node that's closest to the
      // target (aka the node at the same index as the lowest value in distances)
      if (this->type == AI::BEST) {
        auto lowest_distance = min_element(distances.begin(), distances.end());
        int selected_index = distance(distances.begin(), lowest_distance);

        path = backlog.at(selected_index);

        backlog.erase(backlog.begin() + selected_index);
        distances.erase(distances.begin() + selected_index);
      } else if (this->type == AI::DEPTH) { // DFS: LIFO
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

