#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED
#include <deque>
#include <deque>
#include <GL/glut.h>
#include <sstream>
#include <iostream>
#include "Food.h"
#include "Snake.h"

#define UP    1
#define DOWN  2
#define LEFT  3
#define RIGHT 4

class World
{

private:
  int direction;
  Food food;
  Snake snake;

public:
  World( );
  World( Food food, Snake snake, int direction );
  Food getFood( );
  Snake getSnake( );
  void setSnake( std::deque< std::deque<float> > part_coords );
  void displayFood( Food food );
  void displaySnake( std::deque< std::deque<float> > part_Coords );
  void drawBitmapText( char* text, float x, float y, float z);
  void drawControls( const float map_half_length );
  void drawScore( int score, std::deque< std::deque<float> > part_coords, float map_half_length );
  void drawWalls();
};

#endif //WORLD_H_INCLUDED
