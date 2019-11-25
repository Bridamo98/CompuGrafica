#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED
#include <deque>
#include <deque>
#include <GL/glut.h>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Food.h"
#include "Snake.h"

#define UP    1
#define DOWN  2
#define LEFT  3
#define RIGHT 4

class World
{

private:
  int dir;
  Food food;
  Snake snake;

public:
  World( );
  World( Food food, Snake snake, int dir );
  Food getFood( );
  Snake getSnake( );
  void setSnake( std::deque< std::deque<float> > snake_coords );
  void displayFood( Food food, int type );
  void displaySnake( std::deque< std::deque<float> > snake_coords );
  void drawBitmapText( char* text, float x, float y, float z);
  void drawControls( const float map_size );
  void drawScore( int score, std::deque< std::deque<float> > snake_coords, float map_size );
  void drawWalls();
  void paintGrid(float map_size);
};

#endif //WORLD_H_INCLUDED
