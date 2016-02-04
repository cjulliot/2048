#include "Grid.h"
#include <curses.h>
#include <cstdlib>
#include <time.h>

Grid::Grid (int x, int y): grid(x, vector<int>(y)), _is_won(false){
   srand(time(NULL));
   spawn_new_number();
}


void Grid::spawn_new_number() {
   int x, y;
   do {
      x = rand() % x_size();
      y = rand() % y_size();
   } while (grid[x][y] != 0);

   grid[x][y] = 2;
}


void Grid::print() const{
   for (int y = 0; y < y_size(); y++){
      for (int x = 0; x < x_size(); x++){
         printw("%d ", grid[x][y]);
      }
      printw("\n");
   }
}


bool Grid::is_over() const{
   bool res = true;

   for (int x = 0; x < x_size(); x++){
      for (int y = 0; y < y_size(); y++){
         if (grid[x][y] == 0){
            res = false;
            break;
         } else if (x < x_size() - 2){ // not a border cell
            if (grid[x][y] == grid[x+1][y]){
               res = false;
               break;
            }
         } else if (y < y_size() - 2){ // not a border cell
            if (grid[x][y] == grid[x][y+1]){
               res = false;
               break;
            }
         }
      }
      if (res == false)
         break;
   }

   return res;
}



int Grid::get_arrow_input() const{
   int input = 0;

   while (!input){
      switch(input = getch()) {
         case KEY_UP:
            printw("Up\n");
            break;
         case KEY_DOWN:
            printw("Down\n");
            break;
         case KEY_LEFT:
            printw("Left\n");
            break;
         case KEY_RIGHT:
            printw("Right\n");
            break;
         default:
            printw("Not an arrow\n");
            input = 0;
            break;
      }
   }

   return input;
}



void Grid::move(const int direction){

   if(direction == KEY_LEFT){
      for(int y = 0; y < y_size(); y++){
         for(int x = 1; x < x_size(); x++){
            /* If cell value is 0 then do nothing */
            if(grid[x][y]){
               int x_stop;

               for(x_stop = x; x_stop >= 0; x_stop--){
                  if(x_stop == 0)
                     break;
                  if((grid[x][y] != grid[x_stop-1][y]) && (grid[x_stop-1][y] != 0))
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
            if(grid[x][y]){
               int x_stop;

               for(x_stop = x; x_stop < x_size(); x_stop++){
                  if(x_stop == x_size()-1)
                     break;
                  if((grid[x][y] != grid[x_stop+1][y]) && (grid[x_stop+1][y] != 0))
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
            if(grid[x][y]){
               int y_stop;

               for(y_stop = y; y_stop >= 0; y_stop--){
                  if(y_stop == 0)
                     break;
                  if((grid[x][y] != grid[x][y_stop-1]) && (grid[x][y_stop-1] != 0))
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
            if(grid[x][y]){
               int y_stop;

               for(y_stop = y; y_stop < y_size(); y_stop++){
                  if(y_stop == y_size()-1)
                     break;
                  if((grid[x][y] != grid[x][y_stop+1]) && (grid[x][y_stop+1] != 0))
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

void Grid::move_cell(const int x_start, const int y_start, \
      const int x_stop, const int y_stop){

   if(grid[x_stop][y_stop] == 0){
      grid[x_stop][y_stop] = grid[x_start][y_start];
      grid[x_start][y_start] = 0;
   } else { // cell "fusion"
      grid[x_stop][y_stop] *= 2;
      grid[x_start][y_start] = 0;
      if(grid[x_stop][y_stop] == 2048)
         _is_won = true;
   }
}
