#include "Snake.h"

// ----------------------------------------------------------------------
Snake::Snake( )
{
}

// ----------------------------------------------------------------------
Snake::Snake( std::deque< std::deque<float> > part_coordsP )
  : part_coords ( part_coordsP )
{
}

// ----------------------------------------------------------------------
std::deque< std::deque<float> > Snake::getPart_Coords( )
{
  return ( this->part_coords );
}

// ----------------------------------------------------------------------
void Snake::setPart_Coords( std::deque< std::deque<float> > part_Coords )
{
  this->part_coords = part_Coords;
}

// ----------------------------------------------------------------------
void Snake::drawSnake( std::deque< std::deque<float> > part_Coords )
{
  glPushMatrix();
     glTranslatef(part_Coords[0][0],part_Coords[0][1], -40.0f);
     glColor3f(0.0f,0.0f, 1.0f);
     glutSolidCube(2.0f);
     glPopMatrix();

    for(unsigned int a = 0; a < part_Coords.size(); a++){
        glPushMatrix();
        glTranslatef(part_Coords[a][0], part_Coords[a][1], -40.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glutSolidCube(2.0f);
        glPopMatrix();
    }
}
