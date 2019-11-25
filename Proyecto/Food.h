#ifndef FOOD_H_INCLUDED
#define FOOD_H_INCLUDED


#include <GL/glut.h>
#include <deque>
#include <sstream>

class Food
{

private:
  bool eaten;
  int pos_x;
  int pos_y;
  int pos_z;

public:
  Food( );
  Food( bool eatenP, int pos_xP, int pos_yP, int pos_zP );
  bool getEaten();
  int getPos_x();
  int getPos_y();
  int getPos_z();
  void setEaten( bool eaten );
  void setPos_x( int pos_x );
  void setPos_y( int pos_y );
  void setPos_z( int pos_z );

  void drawFood(int type);
  void spawnFood(const float map_half_length, std::deque< std::deque<float> > part_coords, int food_coords[2] );
};

#endif //FOOD_H_INCLUDED
