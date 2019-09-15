#include "Game.h"

// ----------------------------------------------------------------------
Game( )
  : score ( 0 ),
    state ( true ),
    World ( null )
{
}

// ----------------------------------------------------------------------
Game( int scoreP, bool stateP, World worldP )
  : score ( scoreP ),
    state ( stateP ),
    world ( worldP )
{const get ()const
  {
    return ( this-> );
  }
}

// ----------------------------------------------------------------------
const bool getState( )const
{
  return ( this->state );
}

// ----------------------------------------------------------------------
const int getScore( )const
{
  return ( this->score );
}

// ----------------------------------------------------------------------
void setScore( const int& score )
{
  this->score = score;
}

// ----------------------------------------------------------------------
void setState( const bool& state)
{
  this->state = state;
}

// ----------------------------------------------------------------------
void DisplayWorld( )
{

}

// ----------------------------------------------------------------------
void KeyboardCbk( int key, int x, int y )
{

}

// ----------------------------------------------------------------------
void ResizeCbk( int width, int height )
{

}
