#include "World.h"


// ----------------------------------------------------------------------
World::World( )
{
}

// ----------------------------------------------------------------------
World::World( Food food, Snake snake, int dir )
  : food ( food ),
    snake ( snake ),
    dir ( dir )
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
void World::setSnake( std::deque< std::deque<float> > snake_coords )
{
  this->snake.setPart_Coords( snake_coords );
}


// ----------------------------------------------------------------------
void World::displayFood( Food food, int type )
{
  this->food = food;
  this->food.drawFood(type);
}

// ----------------------------------------------------------------------
void World::displaySnake( std::deque< std::deque<float> > snake_coords )
{
  this->snake.drawSnake( snake_coords );
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
void World::drawControls( const float map_size )
{
  char* move_message = (char*) "Use las flechas izquierda y derecha";
  char* exit_message = (char*) "Presiones ESC para salir";

  drawBitmapText(move_message, map_size - 32.0f, map_size - 2.0f, -39.5f);
  drawBitmapText(exit_message, map_size - 21.0f, map_size - 4.0f, -39.5f);
}

// ----------------------------------------------------------------------
void World::drawScore( int score, std::deque< std::deque<float> > snake_coords, float map_size )
{
  const char* score_message = (char*) "Puntos: ";
  const char* length_message = (char*) "Longitud: ";
  std::stringstream score_string;
  std::stringstream length_string;

  score_string << score_message << score;
  length_string << length_message << snake_coords.size();

  drawBitmapText((char*) score_string.str().c_str(), -map_size + 1.0f, map_size - 2.0f, -39.5f);
  drawBitmapText((char*) length_string.str().c_str(), -map_size + 1.0f, map_size - 4.0f, -39.5f);
}
void World::drawWalls()
{
  glPushMatrix();
    glColor3f(0.5f,0.5f,0.5f);
    glBegin(GL_POLYGON);
      glVertex3f(31.0f,31.0f,-40.0f);
      glVertex3f(-31.0f,31.0f,-40.0f);
      glVertex3f(-31.0f,31.0f,-30.0f);
      glVertex3f(31.0f,31.0f,-30.0f);
    glEnd();
    glBegin(GL_POLYGON);
      glVertex3f(-31.0f,31.0f,-40.0f);
      glVertex3f(-31.0f,-31.0f,-40.0f);
      glVertex3f(-31.0f,-31.0f,-30.0f);
      glVertex3f(-31.0f,31.0f,-30.0f);
    glEnd();
    glBegin(GL_POLYGON);
      glVertex3f(-31.0f,-31.0f,-40.0f);
      glVertex3f(31.0f,-31.0f,-40.0f);
      glVertex3f(31.0f,-31.0f,-30.0f);
      glVertex3f(-31.0f,-31.0f,-30.0f);
    glEnd();
    glBegin(GL_POLYGON);
      glVertex3f(31.0f,31.0f,-40.0f);
      glVertex3f(31.0f,31.0f,-30.0f);
      glVertex3f(31.0f,-31.0f,-30.0f);
      glVertex3f(31.0f,-31.0f,-40.0f);
    glEnd();
    glBegin(GL_POLYGON);
      glVertex3f(31.0f,31.0f,-40.0f);
      glVertex3f(-31.0f,31.0f,-40.0f);
      glVertex3f(-31.0f,-31.0f,-40.0f);
      glVertex3f(31.0f,-31.0f,-40.0f);
    glEnd();

    glColor3f(0.0f,0.0f,1.0f);
    glBegin(GL_LINE_LOOP);
      glVertex3f(31.0f,31.0f,-40.0f);
      glVertex3f(-31.0f,31.0f,-40.0f);
      glVertex3f(-31.0f,31.0f,-30.0f);
      glVertex3f(31.0f,31.0f,-30.0f);
    glEnd();
    glBegin(GL_LINE_LOOP);
      glVertex3f(-31.0f,31.0f,-40.0f);
      glVertex3f(-31.0f,-31.0f,-40.0f);
      glVertex3f(-31.0f,-31.0f,-30.0f);
      glVertex3f(-31.0f,31.0f,-30.0f);
    glEnd();
    glBegin(GL_LINE_LOOP);
      glVertex3f(-31.0f,-31.0f,-40.0f);
      glVertex3f(31.0f,-31.0f,-40.0f);
      glVertex3f(31.0f,-31.0f,-30.0f);
      glVertex3f(-31.0f,-31.0f,-30.0f);
    glEnd();
    glBegin(GL_LINE_LOOP);
      glVertex3f(31.0f,31.0f,-40.0f);
      glVertex3f(31.0f,31.0f,-30.0f);
      glVertex3f(31.0f,-31.0f,-30.0f);
      glVertex3f(31.0f,-31.0f,-40.0f);
    glEnd();
    glBegin(GL_LINE_LOOP);
      glVertex3f(31.0f,31.0f,-40.0f);
      glVertex3f(-31.0f,31.0f,-40.0f);
      glVertex3f(-31.0f,-31.0f,-40.0f);
      glVertex3f(31.0f,-31.0f,-40.0f);
    glEnd();
  glPopMatrix();
}
void World::paintGrid(float map_size){
  glPushMatrix();
      glColor3f(0.0f,0.0f,1.0f);
      glLineWidth(2.0);
      for (float i = -map_size-1.0f; i <= map_size+1.0f; i = i + 2.0f)
      {
          glBegin(GL_LINE_LOOP);
              glVertex3f(i, map_size+1.0f, -40.0f);
              glVertex3f(i, -map_size-1.0f, -40.0f);
          glEnd();
      }
      for (float j = -map_size-1.0f; j <= map_size+1.0f; j = j + 2.0f)
      {
          glBegin(GL_LINE_LOOP);
              glVertex3f(map_size+1.0f, j, -40.0f);
              glVertex3f(-map_size-1.0f, j, -40.0f);
          glEnd();
      }
  glPopMatrix();
}
