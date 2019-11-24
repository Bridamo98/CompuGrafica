#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED
#include <deque>
#include <GL/glut.h>
#include <iostream>

class Snake
{

private:
  std::deque< std::deque<float> > part_coords;

public:
  Snake( );
  Snake( std::deque< std::deque<float> > part_coordsP );
  std::deque< std::deque<float> > getPart_Coords();
  void setPart_Coords( std::deque< std::deque<float> > part_Coords );

  void drawSnake( std::deque< std::deque<float> > part_Coords );
};

#endif //SNAKE_H_INCLUDED
