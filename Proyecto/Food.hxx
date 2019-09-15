#include "Food.h"

// ----------------------------------------------------------------------
Food( )
  : eaten ( false ),
    pos_x ( 0 ),
    pos_y ( 0 ),
    type ( "" )
{
}

// ----------------------------------------------------------------------
Food( bool eatenP, int pos_xP, int pos_yP, char typeP )
  : eaten ( eatenP ),
    pos_x ( pos_xP ),
    pos_y ( pos_yP ),
    type ( typeP )
{
}

// ----------------------------------------------------------------------
const bool& getEaten( ) const
{
  return ( this->eaten );
}

// ----------------------------------------------------------------------
const int& getPos_x( ) const
{
  return ( this->pos_x );
}

// ----------------------------------------------------------------------
const int& getPos_y( ) const
{
  return ( this->pos_y );
}

// ----------------------------------------------------------------------
const char& getType( ) const
{
  return ( this->type );
}

// ----------------------------------------------------------------------
void setEaten( const bool& eaten )
{
  this->eaten = eaten;
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

// ----------------------------------------------------------------------
void setType( const int& type )
{
  this->type = type;
}
