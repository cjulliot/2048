#include "Game.h"
#include <curses.h>
#include <cstdlib>
#include <time.h>

Game::Game (int x, int y): _grid(x, std::vector<int>(y)), _is_won(false), _score(0){
   srand(time(NULL));
   spawn_new_number();
}


void Game::spawn_new_number() {
   int x, y;
   do {
      x = rand() % x_size();
      y = rand() % y_size();
   } while (_grid[x][y] != 0);

   _grid[x][y] = 2;
}


void Game::print() const{
   int nb_row, nb_col;
   /* Get window's size */
   getmaxyx(stdscr, nb_row, nb_col);

   for (int y = 0; y < y_size(); y++){
      /* Reset printw cursor to top left corner, then move to center of screen */
      mvprintw(0, 0, "");
      mvprintw(nb_row/2-y_size()+2*y, nb_col/2-x_size()*2, "");
      for (int x = 0; x < x_size(); x++){
         printw("%4d ", _grid[x][y]);
      }
   }
   mvprintw(0, 0, "");
   mvprintw(nb_row/2+y_size()+3, 3*nb_col/5, "");
   printw("Score: %d\n", _score);
}


bool Game::is_over() const{
   for (int x = 0; x < x_size(); x++){
      for (int y = 0; y < y_size(); y++){
         if (_grid[x][y] == 0){
            return false;
         } else if (x < x_size() - 1){ // not a border cell
            if (_grid[x][y] == _grid[x+1][y]){
               return false;
            }
         } else if (y < y_size() - 1){ // not a border cell
            if (_grid[x][y] == _grid[x][y+1]){
               return false;
            }
         }
      }
   }

   return true;
}



int Game::get_arrow_input() const{
   int input = 0;

   while (!input){
      switch(input = getch()) {
         case KEY_UP:
         case KEY_DOWN:
         case KEY_LEFT:
         case KEY_RIGHT:
            break;
         default:
            input = 0;
            break;
      }
   }

   return input;
}



void Game::move(const int direction){

   if(direction == KEY_LEFT){
      for(int y = 0; y < y_size(); y++){
         for(int x = 1; x < x_size(); x++){
            /* If cell value is 0 then do nothing */
            if(_grid[x][y]){
               int x_stop;

               for(x_stop = x; x_stop >= 0; x_stop--){
                  if(x_stop == 0)
                     break;
                  if((_grid[x][y] != _grid[x_stop-1][y]) && (_grid[x_stop-1][y] != 0))
                     break;
               }

               /* Test if we need to move */
               if(x != x_stop)
                  move_cell(x, y, x_stop, y);
            }
         }
      }
   }

   if(direction == KEY_RIGHT){
      for(int y = 0; y < y_size(); y++){
         for(int x = x_size()-2; x >= 0; x--){
            if(_grid[x][y]){
               int x_stop;

               for(x_stop = x; x_stop < x_size(); x_stop++){
                  if(x_stop == x_size()-1)
                     break;
                  if((_grid[x][y] != _grid[x_stop+1][y]) && (_grid[x_stop+1][y] != 0))
                     break;
               }

               /* Test if we need to move */
               if(x != x_stop)
                  move_cell(x, y, x_stop, y);
            }
         }
      }
   }

   if(direction == KEY_UP){
      for(int x = 0; x < x_size(); x++){
         for(int y = 1; y < y_size(); y++){
            if(_grid[x][y]){
               int y_stop;

               for(y_stop = y; y_stop >= 0; y_stop--){
                  if(y_stop == 0)
                     break;
                  if((_grid[x][y] != _grid[x][y_stop-1]) && (_grid[x][y_stop-1] != 0))
                     break;
               }

               /* Test if we need to move */
               if(y != y_stop)
                  move_cell(x, y, x, y_stop);
            }
         }
      }
   }

   if(direction == KEY_DOWN){
      for(int x = 0; x < x_size(); x++){
         for(int y = y_size()-2; y >= 0; y--){
            if(_grid[x][y]){
               int y_stop;

               for(y_stop = y; y_stop < y_size(); y_stop++){
                  if(y_stop == y_size()-1)
                     break;
                  if((_grid[x][y] != _grid[x][y_stop+1]) && (_grid[x][y_stop+1] != 0))
                     break;
               }

               /* Test if we need to move */
               if(y != y_stop)
                  move_cell(x, y, x, y_stop);
            }
         }
      }
   }
}

void Game::move_cell(const int x_start, const int y_start, \
      const int x_stop, const int y_stop){

   if(_grid[x_stop][y_stop] == 0){
      _grid[x_stop][y_stop] = _grid[x_start][y_start];
      _grid[x_start][y_start] = 0;
   } else { // cell "fusion"
      _score += _grid[x_stop][y_stop];
      _grid[x_stop][y_stop] *= 2;
      _grid[x_start][y_start] = 0;
      if(_grid[x_stop][y_stop] == 2048)
         _is_won = true;
   }
}
