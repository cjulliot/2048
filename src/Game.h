#ifndef GAME_H
#define GAME_H

#include <vector>


class Game {
   
private:
   std::vector< std::vector<int> > _grid;
   bool _is_won;
   unsigned int _score;

public:
   Game(int x, int y); // Default constructor

   bool is_won() const;
   int x_size() const;
   int y_size() const;

   bool is_over() const; 
   int get_arrow_input() const;
   void move(const int direction);
   void move_cell(const int x_start, const int y_start,
                     const int x_stop, const int y_stop);
 
   void spawn_new_number();
   void print() const;

};

inline bool Game::is_won() const{
   return _is_won;
}

inline int Game::x_size() const{
   return _grid.size();
}

inline int Game::y_size() const{
   return _grid[0].size();
}

#endif //GAME_H
