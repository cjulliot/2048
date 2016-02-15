#include "Game.h"
#include <curses.h>
#include <string>
#include <cstdlib>


void input_size_x_y(int& size_x, int& size_y);

int main(int argc, char* argv[]) {
   initscr();
   keypad(stdscr, TRUE);
   timeout(-1);

   int size_x, size_y;

   int nb_row, nb_col;
   std::string message;

   input_size_x_y(size_x, size_y);

   /* Disable echo so key inputs are not shown during the game */
   noecho();
   curs_set(0);

   Game my_game(size_x, size_y);
   my_game.print();

   do{
      int key_pressed = my_game.get_arrow_input();
      if(key_pressed == 'q')
         goto end;
      else
         my_game.move(key_pressed);
      my_game.spawn_new_number();
      my_game.print();
   } while(!(my_game.is_over() || my_game.is_won()));

   getmaxyx(stdscr, nb_row, nb_col);
   //mvprintw(0, 0, "");

   if(my_game.is_won())
      message = "YOU WIN!!";
   else
      message = "Game Over :(";

   mvprintw(nb_row/10, nb_col/2-message.length()/2, message.c_str());
   refresh();
   getch();

end:
   endwin();
   return 0;
}


void input_size_x_y(int& size_x, int& size_y){
   int nb_row, nb_col;
   std::string message;
   getmaxyx(stdscr, nb_row, nb_col);

   message = "Welcome to 2048!";
   mvprintw(nb_row/3, nb_col/2-message.length()/2, message.c_str());

   message = "Choose number of rows [2-9] (default=4): ";
   mvprintw(nb_row/3+2, nb_col/2-message.length()/2, message.c_str());

   scanw("%d", &size_y);

   if(size_y < 2 || size_y > 9)
      size_y = 4;

   message = "Choose number of columns [2-9] (default=4): ";
   mvprintw(nb_row/3+4, nb_col/2-message.length()/2, message.c_str());
   scanw("%d", &size_x);

   if(size_x < 2 || size_x > 9)
      size_x = 4;

}
