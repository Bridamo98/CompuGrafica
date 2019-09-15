#include "World.h"

// ----------------------------------------------------------------------
World( )
  : foods ( null ),
    obstacles ( null ),
    snake ( null ),
    space ( 0 )
{
}

// ----------------------------------------------------------------------
World( std::vector < Food > foods, std::vector < Obstacle > obstacles,
      std::vector < Snake > snake, int space )
  : foods ( foods ),
    obstacles ( obstacles ),
    snake ( snake ),
    space ( space )
{
}

// ----------------------------------------------------------------------
const std::vector< Food > getFoods( )const
{
 return ( this->foods );
}

// ----------------------------------------------------------------------
const Snake getSnake( )const
{
 return ( this->snake );
}

// ----------------------------------------------------------------------
const std::vector< Obstacle > getObstacles( )const
{
 return ( this->obstacles );
}

// ----------------------------------------------------------------------
const int getSpace( )const
{
 return ( this->space );
}

// ----------------------------------------------------------------------
void setFoods( const bool& eaten, int& pos_x, int& pos_y )
{
  for( int i = 0; i < this->foods.size(); ++i)
  {
    if(this->foods[i].pos_x == pos_x && this->foods[i].pos_y == pos_y )
        this->foods[i].setEaten(eaten);
  }
}

// ----------------------------------------------------------------------
void setSnake( const int& length )
{
  this->snake.setLength( length );
}

// ----------------------------------------------------------------------
void setSpace( const int& space )
{
  this->space = space;
}

// ----------------------------------------------------------------------
void displayBoard( )
{

}

// ----------------------------------------------------------------------
void displayFoods( )
{

}

// ----------------------------------------------------------------------
void displayObstacles( )
{

}

// ----------------------------------------------------------------------
void displaySnake( )
{

}
