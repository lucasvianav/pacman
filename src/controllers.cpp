#include "controllers.h"
#include "utils.h"
#include <algorithm>
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

GameController::GameController() : map("01") {
  // initializes ncurses
  this->window = initscr();
  this->has_color = has_colors();
  keypad(this->window, true);
  nodelay(this->window, true);
  noecho();
  curs_set(false);
  cbreak();

  if (this->has_color) {
    start_color();

    // color profiles
    init_pair(STANDARD_COLORS, COLOR_WHITE,  COLOR_BLACK);
    init_pair(GHOST_COLORS,    COLOR_RED,    COLOR_WHITE);
    init_pair(PACMAN_COLORS,   COLOR_YELLOW, COLOR_BLACK);

    // set BG color to black
    wbkgd(this->window, A_NORMAL | COLOR_PAIR(0));
  }

  this->draw_map();
  this->ghost_above_dot = false;
  this->score = 0;
}

GameController::~GameController() {
  delwin(this->window);
  endwin();
  cout
    << "\n"
    << (this->score == this->map.get_n_dots() ? "YOU WIN!" : "GAME OVER!")
    << " \nScore: " << this->score << "\n\n";
}

void GameController::draw_map() {
  vector<vector<wchar_t>> map_chars = this->map.get_map();
  unsigned int n_rows = this->map.get_n_rows();
  unsigned int n_cols = this->map.get_n_cols();

  for (unsigned int i = 0; i < n_rows; i++) {
    for (unsigned int j = 0; j < n_cols; j++) {
      if (this->has_color) {
        if (map_chars[i][j] == GHOST_ICON) {
          waddch(this->window, map_chars[i][j] | A_BOLD | A_STANDOUT | COLOR_PAIR(GHOST_COLORS));
        } else if (map_chars[i][j] == PACMAN_ICON) {
          waddch(this->window, map_chars[i][j] | A_BOLD | COLOR_PAIR(PACMAN_COLORS));
        } else {
          waddch(this->window, map_chars[i][j] | A_NORMAL | COLOR_PAIR(STANDARD_COLORS));
        }
      } else {
        if (map_chars[i][j] == GHOST_ICON) {
          waddch(this->window, map_chars[i][j] | A_BOLD | A_STANDOUT);
        } else if (map_chars[i][j] == PACMAN_ICON) {
          waddch(this->window, map_chars[i][j] | A_BOLD);
        } else {
          waddch(this->window, map_chars[i][j] | A_NORMAL);
        }
      }
    }

    if (i == 0) {
      char score[21];
      sprintf(score, "      SCORE: %d/%d", this->score, this->map.get_n_dots());
      waddstr(this->window, score);
    }

    waddch(this->window, '\n');
  }
}

Position GameController::move(Position old_pos, Position new_pos, wchar_t *overwritten_char) {
  if (this->map.position_valid(new_pos) && old_pos != new_pos) {
    wchar_t old_pos_cur_char = this->map.get_char(old_pos);
    wchar_t new_pos_cur_char = this->map.get_char(new_pos);

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

    this->map.update_map(old_pos, old_pos_new_char);
    this->map.update_map(new_pos, new_pos_new_char);

    *overwritten_char = new_pos_cur_char;
    return new_pos;
  }

  return old_pos;
}

void GameController::redraw() {
  erase();
  wrefresh(this->window);
  this->draw_map();
}

void GameController::refresh() { wrefresh(this->window); }

void GameController::reset() {
  erase();
  wrefresh(this->window);
}

WINDOW *GameController::get_window() { return this->window; }

int GameController::get_score() { return this->score; }

bool GameController::won() { return this->score == this->map.get_n_dots(); }

bool GameController::direction_blocked(Position pos, Direction dir) {
  wchar_t character = this->map.get_char(pos.move(dir));
  return character != DOT && character != SPACE;
}

vector<Position> GameController::get_adjacency_list(Position pos) {
  return this->map.get_adjacency_list(pos);
}

vector<Position> GameController::get_ghosts_positions() {
  return this->map.ghosts_positions;
}

Position GameController::get_pacman_position() {
  return this->map.pacman_posision;
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
  this->m.lock();
  wchar_t space = SPACE;
  Character::move(this->direction, &space);
  this->m.unlock();
}

void Pacman::turn(Direction dir) {
  bool is_blocked = this->gc->direction_blocked(*this->pos, dir);
  if (!is_blocked) {
    this->direction = dir;
  }
}

Position Pacman::get_position() {
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
  Position pos = this->find_next_move(target);
  this->last_position = *this->pos;
  Character::move(pos, &this->overwritten_char);
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

