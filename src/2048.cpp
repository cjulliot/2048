#include "Game.h"
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

   Game my_game(size_x, size_y);
   my_game.print();

   do{
      my_game.move(my_game.get_arrow_input());
      my_game.spawn_new_number();
      clear();
      my_game.print();
   } while(!(my_game.is_over() || my_game.is_won()));

   if(my_game.is_won())
      printw("\n\nYOU WIN!\n");
   else
      printw("\n\nGame Over :(\n");

   getch();

   endwin();
   return 0;
}
