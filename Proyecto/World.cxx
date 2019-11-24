#include "World.h"


// ----------------------------------------------------------------------
World::World( )
{
}

// ----------------------------------------------------------------------
World::World( Food food, Snake snake, int direction )
  : food ( food ),
    snake ( snake ),
    direction ( direction )
{
}

// ----------------------------------------------------------------------
Food World::getFood( )
{
 return ( this->food );
}

// ----------------------------------------------------------------------
Snake World::getSnake( )
{
 return ( this->snake );
}

// ----------------------------------------------------------------------
void World::setSnake( std::deque< std::deque<float> > part_coords )
{
  this->snake.setPart_Coords( part_coords );
}


// ----------------------------------------------------------------------
void World::displayFood( Food food )
{
  this->food = food;
  this->food.drawFood();
}

// ----------------------------------------------------------------------
void World::displaySnake( std::deque< std::deque<float> > part_Coords )
{
  this->snake.drawSnake( part_Coords );
}

// ----------------------------------------------------------------------
void World::drawBitmapText( char* text, float x, float y, float z )
{
  char* c;

  glPushMatrix();
  glColor3f(0.0f, 1.0f, 0.0f);
  glRasterPos3f(x, y, z);

  for(c = text; *c != '\0'; c++){
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
  }
  glPopMatrix();
}

// ----------------------------------------------------------------------
void World::drawControls( const float map_half_length )
{
  char* move_message = (char*) "Use las flechas izquierda y derecha";
  char* exit_message = (char*) "Presiones ESC para salir";

  drawBitmapText(move_message, map_half_length - 32.0f, map_half_length - 2.0f, -39.5f);
  drawBitmapText(exit_message, map_half_length - 21.0f, map_half_length - 4.0f, -39.5f);
}

// ----------------------------------------------------------------------
void World::drawScore( int score, std::deque< std::deque<float> > part_coords, float map_half_length )
{
  const char* score_message = (char*) "Puntos: ";
  const char* length_message = (char*) "Longitud: ";
  std::stringstream score_string;
  std::stringstream length_string;

  score_string << score_message << score;
  length_string << length_message << part_coords.size();

  drawBitmapText((char*) score_string.str().c_str(), -map_half_length + 1.0f, map_half_length - 2.0f, -39.5f);
  drawBitmapText((char*) length_string.str().c_str(), -map_half_length + 1.0f, map_half_length - 4.0f, -39.5f);
}
