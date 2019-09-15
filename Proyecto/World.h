#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED
#include <vector>
#include "Food.h"
#include "Obstacle.h"
#include "Snake.h"

class World
{

private:
  std::vector < Food > foods;
  std::vector < Obstacle > obstacles;
  Snake snake;
  int space;

public:
  World( );
  World( std::vector < Food > foods, std::vector < Obstacle > obstacles,
        std::vector < Snake > snake, int space);
  const std::vector < Food > getFoods( )const;
  const std::vector < Obstacle > getObstacles( )const;
  const Snake getSnake( )const;
  const int getSpace( )const;
  void setFoods( const bool& eaten, int& pos_x, int& pos_y );
  void setSnake( const int& length );
  void setSpace( const int& space );
  void displayBoard();
  void displayFoods();
  void displayObstacles();
  void displaySnake();
};

#endif //WORLD_H_INCLUDED
