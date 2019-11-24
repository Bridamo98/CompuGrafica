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

// ----------------------------------------------------------------------
void Food::spawnFood(const float map_half_length, std::deque< std::deque<float> > part_coords, int food_coords[2] )
{
  if(this->eaten){
        return;
    }

    int temp_food_coords[2];
    bool collides;

    do {
        collides = false;

        // Produce a temporary random coordinate
        temp_food_coords[0] = 2 * (rand() % ((int) map_half_length + 1)) - (int) map_half_length;
        temp_food_coords[1] = 2 * (rand() % ((int) map_half_length + 1)) - (int) map_half_length;

        // Does it collide with the snake?
        for(unsigned int a = 0; a < part_coords.size(); a++){
            if(temp_food_coords[0] == part_coords[a][0] &&
               temp_food_coords[1] == part_coords[a][1]){
                collides = true;
            }
        }
    } while(collides);

    food_coords[0] = temp_food_coords[0];
    food_coords[1] = temp_food_coords[1];

    this->eaten = true;
}
