#include <iostream>
#include "World.h"

#define UNUSED(param) (void)(param)

#define UP    1
#define DOWN  2
#define LEFT  3
#define RIGHT 4


const float map_half_length = 30.0f;
GLUquadricObj* fillObject = nullptr;

GLsizei w, h;

int direction = DOWN;
bool moved = false;
const int move_speed = 500;

float xCam, yCam, zCam = 30.0f;
std::deque< std::deque<float> > part_coords;

bool food_available = false;
int food_coords[2];

int score = 0;

int growth_stage = 0;
const int growth = 2;

World mundo;
Food food;

// ----------------------------------------------------------------------
void moveSnake( int new_direction )
{
  direction = new_direction;

  int last_part = part_coords.size() - 1;
  std::deque<float> new_head = part_coords[last_part];

  float delta_x = 0.0f;
  float delta_y = 0.0f;

  float map_edge = 0.0f;

  int snake_part_axis = 0;

  switch (direction){
      case UP:{
          delta_y = 2.0f;
          map_edge = map_half_length;
          snake_part_axis = 1;

          break;
      }

      case DOWN:{
          delta_y = -2.0f;
          map_edge = -map_half_length;
          snake_part_axis = 1;

          break;
      }

      case RIGHT:{
          delta_x = 2.0f;
          map_edge = map_half_length;
          snake_part_axis = 0;

          break;
      }

      case LEFT:{
          delta_x = -2.0f;
          map_edge = -map_half_length;
          snake_part_axis = 0;

          break;
      }
  }


  for(unsigned int a = 0; a < part_coords.size(); a++){
      if(part_coords[0][0] + delta_x == part_coords[a][0] &&
         part_coords[0][1] + delta_y == part_coords[a][1]){
          exit(0);
      }
  }

  if(part_coords[0][snake_part_axis] == map_edge){
      exit(0);
  }

  if(part_coords[0][0] + delta_x == food_coords[0] &&
     part_coords[0][1] + delta_y == food_coords[1]){
      score += 50;
      growth_stage++;
      food_available = false;
    }

  new_head[0] = part_coords[0][0] + delta_x;
  new_head[1] = part_coords[0][1] + delta_y;

  part_coords.push_front(new_head);

  if(!growth_stage){
      part_coords.pop_back();
  } else if(growth_stage == growth){
      growth_stage = 0;
  } else {
      growth_stage++;
  }

  glutPostRedisplay();
}

// ----------------------------------------------------------------------
void display( )
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  glViewport( 0, h*0.8, w, h);
  gluPerspective(76.0f, 1.0f, 0.0f, 80.0f);
  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity( );

  gluLookAt( 0, map_half_length+20, 0,0, map_half_length+20, -40, 0, 1, 0);

  glPushMatrix();
  mundo.drawScore( score, part_coords, map_half_length );
  glPopMatrix();

  glPushMatrix();
  mundo.drawControls(map_half_length);
  glPopMatrix();

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  glViewport( 0, 0, w, h*0.8 );
  gluPerspective(76.0f, 1.0f, 0.0f, 80.0f);
  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity( );

  gluLookAt( part_coords[0][0], part_coords[0][1], -20,xCam, yCam, -40, 0, 0, 1 );

  glPushMatrix();
      glColor3f(0.0f,0.0f,1.0f);
      glLineWidth(2.0);
      for (float i = -31.0f; i <= 31.0f; i = i + 2.0f)
      {
          glBegin(GL_LINE_LOOP);
              glVertex3f(i, 31.0f, -40.0f);
              glVertex3f(i, -31.0f, -40.0f);
          glEnd();
      }
      for (float j = -31.0f; j <= 31.0f; j = j + 2.0f)
      {
          glBegin(GL_LINE_LOOP);
              glVertex3f(31.0f, j, -40.0f);
              glVertex3f(-31.0f, j, -40.0f);
          glEnd();
      }
  glPopMatrix();

  glPushMatrix();
  mundo.displaySnake( part_coords );
  glPopMatrix();

  glPushMatrix();
  food.spawnFood(map_half_length,part_coords,food_coords);
  glPopMatrix();

  glPushMatrix();
  food.setPos_x(food_coords[0]);
  food.setPos_y(food_coords[1]);
  food.setPos_z(-40.0f);
  mundo.displayFood( food );
  glPopMatrix();

  glutSwapBuffers();
}

// ----------------------------------------------------------------------
void initGL()
{
    fillObject = gluNewQuadric( );
    gluQuadricDrawStyle( fillObject, GLU_FILL);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// ----------------------------------------------------------------------
void keyboard( unsigned char key, int x, int y)
{
    UNUSED(x);
    UNUSED(y);

    switch(key){

        // Escape key
        case 27:
        case 'q':{
            exit(0);
        }
    }
}

// ----------------------------------------------------------------------
void special( int key, int x, int y){
    UNUSED(x);
    UNUSED(y);

    switch(key){
        case GLUT_KEY_LEFT:{
            if(direction == UP){
                moved = true;

                moveSnake(LEFT);
                xCam = -map_half_length;
                yCam = part_coords[0][1];
                break;
            }
            if(direction == DOWN){
                moved = true;

                moveSnake(RIGHT);

                xCam = map_half_length;
                yCam = part_coords[0][1];
                break;
            }
            if(direction == LEFT){
                moved = true;

                moveSnake(DOWN);
                yCam = -map_half_length;
                xCam = part_coords[0][0];
                break;
            }
            if(direction == RIGHT){
                moved = true;

                moveSnake(UP);

                yCam = map_half_length;
                xCam = part_coords[0][0];
                break;
            }
        }

        case GLUT_KEY_RIGHT:{
            if(direction == UP){
                moved = true;

                moveSnake(RIGHT);
                xCam = map_half_length;
                yCam = part_coords[0][1];

                break;
            }
            if(direction == DOWN){
                moved = true;

                moveSnake(LEFT);
                xCam = -map_half_length;
                yCam = part_coords[0][1];
                break;
            }
            if(direction == LEFT){
                moved = true;

                moveSnake(UP);
                yCam = map_half_length;
                xCam = part_coords[0][0];
                break;
            }
            if(direction == RIGHT){
                moved = true;

                moveSnake(DOWN);
                yCam = -map_half_length;
                xCam = part_coords[0][0];
                break;
            }
        }
    }
}

// ----------------------------------------------------------------------
void reshape(GLsizei width, GLsizei height)
{

    w = width;
    h = height;

}

// ----------------------------------------------------------------------
void moveSnakeAuto( int value )
{
  if(!moved){
      UNUSED(value);

      moveSnake(direction);
  } else {
      moved = false;
  }

  glutTimerFunc(move_speed, moveSnakeAuto, 0);
}

// ----------------------------------------------------------------------
int main(int argc, char** argv)
{
  glutInit(&argc, argv);

   glutInitWindowSize(800, 800);
   glutCreateWindow("Snake 3D");

   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutTimerFunc(move_speed, moveSnakeAuto, 0);

   const int initSize = 3;

   // Specify the coordinates to each part of the snake
   for(int a = 1; a <= initSize; a++){
       std::deque<float> row;

       row.push_back(0.0f);
       row.push_back((map_half_length + 2.0f + (initSize * 2)) - (a * 2));
   //    cout<<(map_half_length + 2.0f + (initSize * 2)) - (a * 2)<<endl;

       part_coords.push_front(row);
   }
   xCam = part_coords[0][0];
   yCam = -map_half_length;

   srand(time(NULL));

   initGL();
   glutMainLoop();

   return 0;
}
