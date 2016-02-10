#include "Game.h"
#include <curses.h>
#include <cstdlib>


void input_size_x_y(int& size_x, int& size_y);

int main(int argc, char* argv[]) {
   initscr();
   cbreak();
   clear();
   echo();
   keypad(stdscr, TRUE);
   timeout(-1);

   int size_x, size_y;

   input_size_x_y(size_x, size_y);
   clear();

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


void input_size_x_y(int& size_x, int& size_y){
   printw("Welcome to 2048!\n\n");
   printw("Choose number of rows (2-9, default:4): ");

   scanw("%d[2-9]", &size_y);

   if(size_y < 2 || size_y > 9)
      size_y = 4;

   printw("\nChoose number of columns (2-9, default:4): ");
   scanw("%d[2-9]", &size_x);

   if(size_x < 2 || size_x > 9)
      size_x = 4;

}

