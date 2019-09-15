#ifndef OBSTACLE_H_INCLUDED
#define OBSTACLE_H_INCLUDED

class Obstacle
{

private:
  int pos_x;
  int pos_y;

public:
  Obstacle( );
  Obstacle( int pos_xP, int pos_yP );
  const int getPos_x()const;
  const int getPos_y()const;
  void setPos_x( const int& pos_x );
  void setPos_y( const int& pos_y );
};

#endif //OBSTACLE_H_INCLUDED
