#include "controllers.h"
#include <curses.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

/*
 *  ____                       ____            _             _ _
 * / ___| __ _ _ __ ___   ___ / ___|___  _ __ | |_ _ __ ___ | | | ___ _ __
 *| |  _ / _` | '_ ` _ \ / _ \ |   / _ \| '_ \| __| '__/ _ \| | |/ _ \ '__|
 *| |_| | (_| | | | | | |  __/ |__| (_) | | | | |_| | | (_) | | |  __/ |
 * \____|\__,_|_| |_| |_|\___|\____\___/|_| |_|\__|_|  \___/|_|_|\___|_|
 */

GameController::GameController() {
  // initializes ncurses
  this->window = initscr();
  keypad(this->window, true);
  nodelay(this->window, true);
  noecho();
  curs_set(false);
  cbreak();

  this->map = Map();
  this->draw_map();
  this->ghost_above_dot = false;
  this->score = 0;
}

GameController::~GameController() {
  endwin();
  cout << "\nGAME OVER! \nScore: " << this->score << "\n\n";
}

void GameController::draw_map() {
  vector<vector<wchar_t>> map_chars = this->map.get_map();
  unsigned int n_rows = this->map.get_n_rows();
  unsigned int n_cols = this->map.get_n_cols();

  for (unsigned int i = 0; i < n_rows; i++) {
    for (unsigned int j = 0; j < n_cols; j++) {
      waddch(this->window, map_chars[i][j]);
    }

    if (i == 0) {
      char score[21];
      sprintf(score, "      SCORE: %d/%d", this->score, this->map.get_n_dots());
      waddstr(this->window, score);
    }

    waddch(this->window, '\n');
  }
}

Position GameController::move(Position old_pos, Position new_pos) {
  if (this->map.position_valid(new_pos) && old_pos != new_pos) {
    wchar_t old_pos_cur_char = this->map.get_char(old_pos);
    wchar_t new_pos_cur_char = this->map.get_char(new_pos);

    bool is_pacman = old_pos_cur_char == PACMAN_ICON;
    bool ghost_leaving_dot = this->ghost_above_dot && !is_pacman;

    wchar_t old_pos_new_char = ghost_leaving_dot ? DOT : SPACE;
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
      } else {
        this->ghost_above_dot = true;
      }
      break;

    case SPACE:
      if (ghost_leaving_dot) {
        this->ghost_above_dot = false;
      }
      break;

    default:
      return old_pos;
    }

    this->map.update_map(old_pos, old_pos_new_char);
    this->map.update_map(new_pos, new_pos_new_char);

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

/*
 *  ____ _   _    _    ____      _    ____ _____ _____ ____
 * / ___| | | |  / \  |  _ \    / \  / ___|_   _| ____|  _ \
 *| |   | |_| | / _ \ | |_) |  / _ \| |     | | |  _| | |_) |
 *| |___|  _  |/ ___ \|  _ <  / ___ \ |___  | | | |___|  _ <
 * \____|_| |_/_/   \_\_| \_\/_/   \_\____| |_| |_____|_| \_\
 */

Character::Character(GameController *gc, unsigned int x, unsigned int y) {
  this->gc = gc;
  this->pos = (Position *)malloc(sizeof(Position));
  this->pos->x = x;
  this->pos->y = y;
}

void Character::move(Direction direction) {
  Position intended_pos = (*this->pos);
  intended_pos.move(direction);

  Position new_pos = gc->move(*this->pos, intended_pos);

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

Pacman::Pacman(GameController *gc, unsigned int x, unsigned int y)
    : Character(gc, x, y) {
  this->direction = RIGHT;
}

void Pacman::move() { Character::move(this->direction); }

void Pacman::turn(Direction dir) {
  bool is_blocked = this->gc->direction_blocked(*this->pos, dir);
  if (!is_blocked) {
    this->direction = dir;
  }
}

/*
 *  ____ _   _  ___  ____ _____
 * / ___| | | |/ _ \/ ___|_   _|
 *| |  _| |_| | | | \___ \ | |
 *| |_| |  _  | |_| |___) || |
 * \____|_| |_|\___/|____/ |_|
 */

Ghost::Ghost(GameController *gc, unsigned int x, unsigned int y)
    : Character(gc, x, y) {}

void Ghost::move() {
  Direction direction = static_cast<Direction>(rand() % 4);
  Character::move(direction);
}

Position get_next_move(vector<Position>& path)
{
  return path[1];
}
 
// utility function to check if current
// vertex is already present in path
int isNotVisited(Position x, vector<Position>& path)
{
    int size = path.size();
    for (int i = 0; i < size; i++)
        if (path[i] == x)
            return 0;
    return 1;
}
 
// utility function for finding paths in graph
// from source to destination
Position Ghost::find_next_move(Position pacman_pos, Map maze)
{
  // create a queue which stores
  // the paths
  queue<vector<Position>> q;

  // path vector to store the current path
  vector<Position> path;
  path.push_back(*(this->pos));
  q.push(path);
  while (!q.empty()) {
      path = q.front();
      q.pop();
      Position last = path[path.size() - 1];

      // if last vertex is the desired destination
      // then print the path
      if (last == pacman_pos)
          return get_next_move(path);       

      // traverse to all the nodes connected to
      // current vertex and push new path to queue
      for(Position p : maze.get_adj_list(last)) {
        if(isNotVisited(p, path)) {
          vector<Position> newpath(path);
          newpath.push_back(p);
          q.push(newpath);
        }
      }
  }
}