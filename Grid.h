#ifndef GRID_H
#define GRID_H

#include <vector>


using namespace std;

class Grid {
   
private:
   vector< vector<int> > grid;

public:
   Grid(int x, int y); // Default constructor

   int x_size() const;
   int y_size() const;

   bool is_over() const; 
   int get_arrow_input() const;
   void move(const int direction);
   void move_cell(const int x_start, const int y_start, \
                     const int x_stop, const int y_stop);
 
   void spawn_new_number();
   void print() const;

};


inline int Grid::x_size() const{
   return grid.size();
}

inline int Grid::y_size() const{
   return grid[0].size();
}


#endif //GRID_H
