#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "World.h"

class Game
{

private:
  int score;
  bool state;
  World world;

public:
  Game( );
  Game( int scoreP, bool stateP, World worldP );
  const bool getState( )const;
  const int getScore( )const;
  void setScore( const int& score );
  void setState( const bool& state );
  void DisplayWorld( );
  void KeyboardCbk(int key, int x, int y);
  void ResizeCbk( int width, int height );
};

#endif //GAME_H_INCLUDED
