#include <iostream>
#include <cmath>

#include "World.h"

#define UP    1
#define DOWN  2
#define LEFT  3
#define RIGHT 4

#define PI 3.14159265


const float map_size = 30.0f;
GLUquadricObj* fillObject = nullptr;
GLfloat light0_position[] = {1.0,1.0,1.0,0.0};
GLfloat mat1_diffuse[] = {1.0,0.0,0.0,1.0};

GLfloat light1_position[] = {1.0,1.0,1.0,0.0};
GLfloat mat2_diffuse[] = {0.0,1.0,0.0,1.0};

GLsizei w, h;

bool rotating=false;
float r, AngIn, AngFin, deltaAng, xCamFin, yCamFin;

int dir = DOWN;
int type = 1;
bool mov = false;
const int speed = 200;

float xCam, yCam, zCam = 30.0f;
std::deque< std::deque<float> > snake_coords;

bool there_is_food = false;
int food_coords[2];

int score = 0;

int stage = 0;
const int increase = 2;

World mundo;
Food food;

// ----------------------------------------------------------------------
void move( int new_dir )
{
  dir = new_dir;

  int last_part = snake_coords.size() - 1;
  std::deque<float> new_head = snake_coords[last_part];

  float delta_x = 0.0f;
  float delta_y = 0.0f;

  float map_edge = 0.0f;

  int snake_part_axis = 0;

  switch (dir){
      case UP:{
          delta_y = 1.0f;
          map_edge = map_size;
          snake_part_axis = 1;

          break;
      }

      case DOWN:{
          delta_y = -1.0f;
          map_edge = -map_size;
          snake_part_axis = 1;

          break;
      }

      case RIGHT:{
          delta_x = 1.0f;
          map_edge = map_size;
          snake_part_axis = 0;

          break;
      }

      case LEFT:{
          delta_x = -1.0f;
          map_edge = -map_size;
          snake_part_axis = 0;

          break;
      }
  }


  for(unsigned int a = 0; a < snake_coords.size(); a++){
      if(snake_coords[0][0] + delta_x == snake_coords[a][0] &&
         snake_coords[0][1] + delta_y == snake_coords[a][1]){
          exit(0);
      }
  }

  if(snake_coords[0][snake_part_axis] == map_edge){
      exit(0);
  }

  if(snake_coords[0][0] + delta_x == food_coords[0] &&
     snake_coords[0][1] + delta_y == food_coords[1]){
       if( type == 1 )
        score += 50;
       else if( type == 2 )
        score += 100;
       else if( type == 3 )
        score += 150;
      type = 1 + rand() % 3;
      stage++;
      food.setEaten(false);
    }

  new_head[0] = snake_coords[0][0] + delta_x;
  new_head[1] = snake_coords[0][1] + delta_y;

  snake_coords.push_front(new_head);

  if(!stage){
      snake_coords.pop_back();
  } else if(stage == increase){
      stage = 0;
  } else {
      stage++;
  }

  glutPostRedisplay();
}

void validateRotation()
{
  if(rotating){
    if(AngIn != AngFin){
      xCam = r*cos(AngIn*PI/180.0f)+snake_coords[0][0];
      yCam = r*sin(AngIn*PI/180.0f)+snake_coords[0][1];
      AngIn = AngIn + deltaAng;
    }else{
      rotating = false;
      xCam = xCamFin;
      yCam = yCamFin;
    }
  }
}
void displayText(){
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  glViewport( 0, h*0.8, w, h);
  gluPerspective(76.0f, 1.0f, 0.0f, 80.0f);
  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity( );

  gluLookAt( 0, map_size+20, 0,0, map_size+20, -40, 0, 1, 0);

  glPushMatrix();
  mundo.drawScore( score, snake_coords, map_size );
  glPopMatrix();

  glPushMatrix();
  mundo.drawControls(map_size);
  glPopMatrix();

}
void displayGame(){
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  glViewport( 0, 0, w, h*0.8 );
  gluPerspective(76.0f, 1.0f, 0.0f, 80.0f);
  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity( );

  validateRotation();
  

  gluLookAt( snake_coords[0][0], snake_coords[0][1], -38.0f,xCam, yCam, -38.0f, 0, 0, 1 );

  mundo.drawWalls();

  mundo.paintGrid(map_size);

  glPushMatrix();
  light0_position[0] = snake_coords[0][0];
  light0_position[1] = snake_coords[0][1];
  light0_position[2] = -40.0f;
  glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, mat2_diffuse);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHTING);
  mundo.displaySnake( snake_coords );
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT1);
  glPopMatrix();

  glPushMatrix();
  food.spawnFood(map_size,snake_coords,food_coords);
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
}
// ----------------------------------------------------------------------
void display( )
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  displayText();

  displayGame();

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

    switch(key){

        case 27:
        case 'q':{
            exit(0);
        }
    }
}

// ----------------------------------------------------------------------
void special( int key, int x, int y){

    switch(key){
        case GLUT_KEY_LEFT:{
          rotating = true;
            if(dir == UP){
                r = map_size - snake_coords[0][1];
                AngIn = 90.0f;
                AngFin = 180.0f;
                deltaAng = 45.0f;


                mov = true;
                xCamFin = -map_size;
                yCamFin = snake_coords[0][1];
                move(LEFT);

                break;
            }
            if(dir == DOWN){
                r = map_size + snake_coords[0][1];
                AngIn = 270.0f;
                AngFin = 360.0f;
                deltaAng = 45.0f;

                mov = true;
                xCamFin = map_size;
                yCamFin = snake_coords[0][1];
                move(RIGHT);
                break;
            }
            if(dir == LEFT){

                r = map_size - snake_coords[0][1];
                AngIn = 180.0f;
                AngFin = 270.0f;
                deltaAng = 45.0f;

                mov = true;
                yCamFin = -map_size;
                xCamFin = snake_coords[0][0];
                move(DOWN);

                break;
            }
            if(dir == RIGHT){
                r = map_size + snake_coords[0][1];
                AngIn = 0.0f;
                AngFin = 90.0f;
                deltaAng = 45.0f;

                mov = true;
                yCamFin = map_size;
                xCamFin = snake_coords[0][0];
                move(UP);

                break;
            }
        }

        case GLUT_KEY_RIGHT:{
          rotating = true;
            if(dir == UP){

                r = map_size - snake_coords[0][1];
                AngIn = 90.0f;
                AngFin = 0.0f;
                deltaAng = -45.0f;

                mov = true;
                xCamFin = map_size;
                yCamFin = snake_coords[0][1];
                move(RIGHT);


                break;
            }
            if(dir == DOWN){
                r = map_size + snake_coords[0][1];
                AngIn = 270.0f;
                AngFin = 180.0f;
                deltaAng = -45.0f;

                mov = true;
                xCamFin = -map_size;
                yCamFin = snake_coords[0][1];
                move(LEFT);

                break;
            }
            if(dir == LEFT){
                r = map_size - snake_coords[0][1];
                AngIn = 180.0f;
                AngFin = 90.0f;
                deltaAng = -45.0f;

                mov = true;
                yCamFin = map_size;
                xCamFin = snake_coords[0][0];
                move(UP);

                break;
            }
            if(dir == RIGHT){
                r = map_size + snake_coords[0][1];
                AngIn = 0.0f;
                AngFin = -90.0f;
                deltaAng = -45.0f;

                mov = true;
                yCamFin = -map_size;
                xCamFin = snake_coords[0][0];
                move(DOWN);

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
void moveAuto( int value )
{
  if(!mov){
      move(dir);
  } else {
      mov = false;
  }
  glutTimerFunc(speed, moveAuto, 0);
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
   glutTimerFunc(speed, moveAuto, 0);

   const int initSize = 3;

   for(int a = 1; a <= initSize; a++){
       std::deque<float> row;

       row.push_back(0.0f);//xCoords
       row.push_back((map_size + 2.0f + (initSize * 2)) - (a * 2));//yCoords
       snake_coords.push_front(row);
   }
   xCam = snake_coords[0][0];
   yCam = -map_size;

   srand(time(NULL));

   initGL();
   glutMainLoop();

   return 0;
}
