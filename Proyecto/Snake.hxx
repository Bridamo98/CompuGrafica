#include "Snake.h"

// ----------------------------------------------------------------------
Snake( )
  : length ( 0 ),
    pos_x ( 0 ),
    pos_y ( 0 )
{
}

// ----------------------------------------------------------------------
Snake( int lengthP, int pos_xP, int pos_yP )
  : length ( lengthP ),
    pos_x ( pos_xP ),
    pos_y ( pos_yP )
{
}

// ----------------------------------------------------------------------
const int getLength( )const
{
  return ( this->length );
}

// ----------------------------------------------------------------------
const int getPos_x( )const
{
  return ( this->pos_x );
}

// ----------------------------------------------------------------------
const int getPos_y( )const
{
  return ( this->pos_y );
}

// ----------------------------------------------------------------------
void setLength( const int& length )
{
  this->length = length;
}

// ----------------------------------------------------------------------
void setPos_x( const int& pos_x )
{
  this->pos_x = pos_x;
}

// ----------------------------------------------------------------------
void setPos_y( const int& pos_y )
{
  this->pos_y = pos_y;
}
