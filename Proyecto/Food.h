#ifndef FOOD_H_INCLUDED
#define FOOD_H_INCLUDED

class Food
{

private:
  bool eaten;
  int pos_x;
  int pos_y;
  char type;

public:
  Food( );
  Food( bool eatenP, int pos_xP, int pos_yP, char typeP );
  const bool getEaten()const;
  const int getPos_x()const;
  const int getPos_y()const;
  const char getType()const;
  void setEaten( const bool& eaten );
  void setPos_x( const int& pos_x );
  void setPos_y( const int& pos_y );
  void setType( const char& type );
};

#endif //FOOD_H_INCLUDED
