#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

class Snake
{

private:
  int length;
  int pos_x;
  int pos_y;

public:
  Snake( );
  Snake( int lengthP, int pos_xP, int pos_yP );
  const int getLength()const;
  const int getPos_x()const;
  const int getPos_y()const;
  void setLength( const int& length );
  void setPos_x( const int& pos_x );
  void setPos_y( const int& pos_y );
};

#endif //SNAKE_H_INCLUDED
