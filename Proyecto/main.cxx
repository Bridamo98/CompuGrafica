#include <iostream>
#include <cmath>

#include "World.h"

#define UNUSED(param) (void)(param)

#define UP    1
#define DOWN  2
#define LEFT  3
#define RIGHT 4

#define PI 3.14159265


const float map_half_length = 30.0f;
GLUquadricObj* fillObject = nullptr;
GLfloat light0_position[] = {1.0,1.0,1.0,0.0};
GLfloat mat1_diffuse[] = {1.0,0.0,0.0,1.0};

GLfloat light1_position[] = {1.0,1.0,1.0,0.0};
GLfloat mat2_diffuse[] = {0.0,1.0,0.0,1.0};

GLsizei w, h;

bool rotating=false;
float r, AngIn, AngFin, deltaAng, xCamFin, yCamFin;

int direction = DOWN;
int type = 1;
bool moved = false;
const int move_speed = 200;

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
          delta_y = 1.0f;
          map_edge = map_half_length;
          snake_part_axis = 1;

          break;
      }

      case DOWN:{
          delta_y = -1.0f;
          map_edge = -map_half_length;
          snake_part_axis = 1;

          break;
      }

      case RIGHT:{
          delta_x = 1.0f;
          map_edge = map_half_length;
          snake_part_axis = 0;

          break;
      }

      case LEFT:{
          delta_x = -1.0f;
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
       if( type == 1 )
        score += 50;
       else if( type == 2 )
        score += 100;
       else if( type == 3 )
        score += 150;
      type = 1 + rand() % 3;
      growth_stage++;
      food.setEaten(false);
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

  if(rotating){
    if(AngIn != AngFin){
      xCam = r*cos(AngIn*PI/180.0f)+part_coords[0][0];
      yCam = r*sin(AngIn*PI/180.0f)+part_coords[0][1];
      AngIn = AngIn + deltaAng;
    }else{
      rotating = false;
      xCam = xCamFin;
      yCam = yCamFin;
    }
  }

  gluLookAt( part_coords[0][0], part_coords[0][1], -38.0f,xCam, yCam, -38.0f, 0, 0, 1 );

  mundo.drawWalls();

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
  light0_position[0] = part_coords[0][0];
  light0_position[1] = part_coords[0][1];
  light0_position[2] = -40.0f;
  glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, mat2_diffuse);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHTING);
  mundo.displaySnake( part_coords );
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT1);
  glPopMatrix();

  glPushMatrix();
  food.spawnFood(map_half_length,part_coords,food_coords);
  glPopMatrix();

  glPushMatrix();
  food.setPos_x(food_coords[0]);
  food.setPos_y(food_coords[1]);
  food.setPos_z(-40.0f);
  light0_position[0] = food_coords[0];
  light0_position[1] = food_coords[1];
  light0_position[2] = -40.0f;
  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, mat1_diffuse);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  mundo.displayFood( food, type );
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);
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
          rotating = true;
            if(direction == UP){
                r = map_half_length - part_coords[0][1];
                AngIn = 90.0f;
                AngFin = 180.0f;
                deltaAng = 45.0f;


                moved = true;
                xCamFin = -map_half_length;
                yCamFin = part_coords[0][1];
                moveSnake(LEFT);

                break;
            }
            if(direction == DOWN){
                r = map_half_length + part_coords[0][1];
                AngIn = 270.0f;
                AngFin = 360.0f;
                deltaAng = 45.0f;

                moved = true;
                xCamFin = map_half_length;
                yCamFin = part_coords[0][1];
                moveSnake(RIGHT);
                break;
            }
            if(direction == LEFT){

                r = map_half_length - part_coords[0][1];
                AngIn = 180.0f;
                AngFin = 270.0f;
                deltaAng = 45.0f;

                moved = true;
                yCamFin = -map_half_length;
                xCamFin = part_coords[0][0];
                moveSnake(DOWN);

                break;
            }
            if(direction == RIGHT){
                r = map_half_length + part_coords[0][1];
                AngIn = 0.0f;
                AngFin = 90.0f;
                deltaAng = 45.0f;

                moved = true;
                yCamFin = map_half_length;
                xCamFin = part_coords[0][0];
                moveSnake(UP);

                break;
            }
        }

        case GLUT_KEY_RIGHT:{
          rotating = true;
            if(direction == UP){

                r = map_half_length - part_coords[0][1];
                AngIn = 90.0f;
                AngFin = 0.0f;
                deltaAng = -45.0f;

                moved = true;
                xCamFin = map_half_length;
                yCamFin = part_coords[0][1];
                moveSnake(RIGHT);


                break;
            }
            if(direction == DOWN){
                r = map_half_length + part_coords[0][1];
                AngIn = 270.0f;
                AngFin = 180.0f;
                deltaAng = -45.0f;

                moved = true;
                xCamFin = -map_half_length;
                yCamFin = part_coords[0][1];
                moveSnake(LEFT);

                break;
            }
            if(direction == LEFT){
                r = map_half_length - part_coords[0][1];
                AngIn = 180.0f;
                AngFin = 90.0f;
                deltaAng = -45.0f;

                moved = true;
                yCamFin = map_half_length;
                xCamFin = part_coords[0][0];
                moveSnake(UP);

                break;
            }
            if(direction == RIGHT){
                r = map_half_length + part_coords[0][1];
                AngIn = 0.0f;
                AngFin = -90.0f;
                deltaAng = -45.0f;

                moved = true;
                yCamFin = -map_half_length;
                xCamFin = part_coords[0][0];
                moveSnake(DOWN);

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
       part_coords.push_front(row);
   }
   xCam = part_coords[0][0];
   yCam = -map_half_length;

   srand(time(NULL));

   initGL();
   glutMainLoop();

   return 0;
}
