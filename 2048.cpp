#include "Grid.h"
#include <curses.h>
#include <cstdlib>

#define MAX_X_SIZE 15
#define MAX_Y_SIZE 15

int main(int argc, char* argv[]) {
   initscr();
   clear();
   noecho();
   keypad(stdscr, TRUE);
   timeout(-1);

   int size_x = 4;
   int size_y = 4;

   if(argc == 3){
      size_x = atoi(argv[1]);
      size_y = atoi(argv[2]);

      if (size_x <= 0 || size_y <= 0){
         size_x = 4;
         size_y = 4;
      }

      if (size_x > MAX_X_SIZE)
         size_x = MAX_X_SIZE;
      if (size_y > MAX_Y_SIZE)
         size_y = MAX_Y_SIZE;
   }

   Grid my_grid(size_x, size_y);
   my_grid.print();

   do{
      my_grid.move(my_grid.get_arrow_input());
      my_grid.spawn_new_number();
      clear();
      my_grid.print();
   } while(!my_grid.is_over());

   endwin();
   return 0;
}
