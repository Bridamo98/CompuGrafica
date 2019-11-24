#include "Food.h"

// ----------------------------------------------------------------------
Food::Food( )
  : eaten ( false ),
    pos_x ( 0 ),
    pos_y ( 0 ),
    pos_z ( 0 )
{
}

// ----------------------------------------------------------------------
Food::Food( bool eatenP, int pos_xP, int pos_yP, int pos_zP )
  : eaten ( eatenP ),
    pos_x ( pos_xP ),
    pos_y ( pos_yP ),
    pos_z ( pos_zP )
{
}

// ----------------------------------------------------------------------
bool Food::getEaten( )
{
  return ( this->eaten );
}

// ----------------------------------------------------------------------
int Food::getPos_x( )
{
  return ( this->pos_x );
}

// ----------------------------------------------------------------------
int Food::getPos_y( )
{
  return ( this->pos_y );
}

// ----------------------------------------------------------------------
int Food::getPos_z( )
{
  return ( this->pos_z );
}

// ----------------------------------------------------------------------
void Food::setEaten( bool eaten )
{
  this->eaten = eaten;
}

// ----------------------------------------------------------------------
void Food::setPos_x( int pos_x )
{
  this->pos_x = pos_x;
}

// ----------------------------------------------------------------------
void Food::setPos_y( int pos_y )
{
  this->pos_y = pos_y;
}

// ----------------------------------------------------------------------
void Food::setPos_z( int pos_z )
{
  this->pos_z = pos_z;
}

// ----------------------------------------------------------------------
void Food::drawFood()
{
  glPushMatrix();
  glTranslatef(this->pos_x, this->pos_y, this->pos_z);
  glColor3f(1.0f, 0.0f, 0.0f);
  glutSolidCube(2.0f);
  glPopMatrix();
}
