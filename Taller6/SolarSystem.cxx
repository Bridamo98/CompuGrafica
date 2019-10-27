/* -------------------------------------------------------------------------
 * @brief Simulation of a simple solar system
 * @author Leonardo Fl�rez-Valencia (florez-l@javeriana.edu.co)
 * -------------------------------------------------------------------------
 */

#include <GL/glut.h>
#include <iostream>
#include <chrono>
#include <cmath>

#include "Camera.h"
#include "SpatialObject.h"

float r = 15.0 , theta=0.50 , phi= 0.00;
float posX = r*sin(theta*_PI)*sin(phi*_PI);
float posY = r*cos(theta*_PI);
float posZ = r*sin(theta*_PI)*cos(phi*_PI);

void rotacion();

// -------------------------------------------------------------------------
GLfloat light0_position[] = {20.0,50.0,50.0,0.0};
GLfloat light1_position[] = {-20.0,-50.0,-50.0,0.0};
GLfloat light2_position[] = {1.0,5.0,1.0,0.0};
GLfloat light3_position[] = {-1.0,-5.0,1.0,0.0};
GLfloat light4_position[] = {30.0,1.0,10.0,0.0};
GLfloat light5_position[] = {10.0,-1.0,-10.0,0.0};
GLfloat light6_position[] = {-50.0,1.0,1.0,0.0};
GLfloat light7_position[] = {-30.0,-5.0,-40.0,0.0};
GLfloat mat1_diffuse[] = {1.0,0.0,0.0,1.0};
GLfloat mat2_diffuse[] = {0.0,1.0,0.0,1.0};
GLfloat mat3_diffuse[] = {0.0,0.0,1.0,1.0};
GLfloat mat4_diffuse[] = {0.5,0.5,0.5,1.0};
GLfloat mat5_diffuse[] = {0.3,0.5,1.4,1.0};
GLfloat mat6_diffuse[] = {0.0,0.1,0.0,1.0};
GLfloat mat7_diffuse[] = {0.0,0.0,0.0,1.0};
GLfloat mat8_diffuse[] = {0.2,0.4,0.5,1.0};
static GLfloat mat_specular[] = {1.0,1.0,1.0,1.0};
static GLfloat mat_shininess[] = {50.0};

// -------------------------------------------------------------------------
Camera myCamera;
SpatialObject* myStar = nullptr;
std::chrono::time_point< std::chrono::high_resolution_clock > frameTime;
double t;

// -------------------------------------------------------------------------
SpatialObject* initWorld( int argc, char* argv[] );
void destroyWorld( SpatialObject* star );

// -------------------------------------------------------------------------
void displayCbk( );
void idleCbk( );
void resizeCbk( int w, int h );
void keyboardCbk( unsigned char key, int x, int y );
void mouseClickCbk( int button, int state, int x, int y );
void mouseMoveCbk( int x, int y );
void initgl( );

// -------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
  // Init OpenGL context
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
  glutInitWindowPosition( 50, 50 );
  glutInitWindowSize( 1024, 768 );
  glutCreateWindow( "Armadillo" );

  // Init world
  try
  {
    myStar = initWorld( argc, argv );

    glutDisplayFunc( displayCbk );
    glutIdleFunc( idleCbk );
    glutReshapeFunc( resizeCbk );
    glutKeyboardFunc( keyboardCbk );
    glutMouseFunc( mouseClickCbk );
    glutMotionFunc( mouseMoveCbk );
    initgl();
    frameTime = std::chrono::high_resolution_clock::now();
    glutMainLoop( );

    destroyWorld( myStar );
    return( 0 );
  }
  catch( std::exception& err )
  {
    std::cerr << err.what( ) << std::endl;
    return( 1 );
  } // end if
}

// -------------------------------------------------------------------------
void initgl()
{
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);

  glClearColor( 0.0, 0.0, 0.0, 0.0);
  glColor3f(0.5,0.5,0.5);

  glShadeModel(GL_SMOOTH);

  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, mat1_diffuse);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHTING);
  glRotatef(10, posX, posY, posZ);

  glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, mat2_diffuse);
  glEnable(GL_LIGHT1);
  glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHTING);
  glRotatef(20, posX, posY, posZ);

  glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, mat3_diffuse);
  glEnable(GL_LIGHT2);
  glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHTING);
  glRotatef(-20, posX, posY, posZ);

  glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
  glLightfv(GL_LIGHT3, GL_DIFFUSE, mat4_diffuse);
  glEnable(GL_LIGHT3);
  glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHTING);
  glRotatef(-10, posX, posY, posZ);

  glLightfv(GL_LIGHT4, GL_POSITION, light4_position);
  glLightfv(GL_LIGHT4, GL_DIFFUSE, mat5_diffuse);
  glEnable(GL_LIGHT4);
  glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHTING);
  glRotatef(-50, posX, posY, posZ);

  glLightfv(GL_LIGHT5, GL_POSITION, light5_position);
  glLightfv(GL_LIGHT5, GL_DIFFUSE, mat6_diffuse);
  glEnable(GL_LIGHT5);
  glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHTING);
  glRotatef(50, posX, posY, posZ);

  glLightfv(GL_LIGHT6, GL_POSITION, light6_position);
  glLightfv(GL_LIGHT6, GL_DIFFUSE, mat7_diffuse);
  glEnable(GL_LIGHT6);
  glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHTING);
  glRotatef(5, posX, posY, posZ);

  glLightfv(GL_LIGHT7, GL_POSITION, light7_position);
  glLightfv(GL_LIGHT7, GL_DIFFUSE, mat8_diffuse);
  glEnable(GL_LIGHT7);
  glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHTING);
  glRotatef(-5, posX, posY, posZ);
}

// -------------------------------------------------------------------------
SpatialObject* initWorld( int argc, char* argv[] )
{
  // Initialize camera
  myCamera.setFOV( 45 );
  myCamera.setPlanes( 1e-2, 100000 );
  myCamera.move( Vector( 0, 0, 600 ) );

  glClearColor( 0, 0, 0, 0 );

  // Check input arguments
  if( argc < 2 )
    throw std::runtime_error(
      std::string( "Usage: " ) + argv[ 0 ] + " world_description"
      );

  // Read world and keep the star of this solar system
  return( new SpatialObject( argv[ 1 ] ) );
}

// -------------------------------------------------------------------------
void destroyWorld( SpatialObject* star )
{
  if( star != nullptr )
    delete star;
}

// -------------------------------------------------------------------------
void displayCbk( )
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity( );

  myCamera.loadCameraMatrix( );

  glColorMaterial(GL_FRONT, GL_DIFFUSE);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  //FPS
  ///t = std::chrono::duration_cast< std::chrono::milliseconds >(
    //std::chrono::high_resolution_clock::now()-frameTime
    //).count()/1000.0;
  //frameTime = std::chrono::high_resolution_clock::now();
  //std::cout<< 1.0/t<<" FPS"<<std::endl;

  // Prepare model matrix
  myStar->drawInOpenGLContext( GL_POLYGON );
  // Finish
  glutSwapBuffers( );
}

// -------------------------------------------------------------------------
void idleCbk( )
{
  glutPostRedisplay( );
}

// -------------------------------------------------------------------------
void resizeCbk( int w, int h )
{
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  myCamera.setWindow( w, h );
  myCamera.loadProjectionMatrix( );
}

// -------------------------------------------------------------------------
void keyboardCbk( unsigned char key, int x, int y )
{
  switch( key )
  {
  case 'w': case 'W':
  {
    myCamera.forward( 10 ) ;
    glutPostRedisplay( );
  }
    break;
  case 's': case 'S':
  {
    myCamera.forward( -10 ) ;
    glutPostRedisplay( );
  }
    break;
  case 'a': case 'A':
  {
    myCamera.strafe( -10 ) ;
    glutPostRedisplay( );
  }
    break;
  case 'd': case 'D':
  {
    myCamera.strafe( 10 ) ;
    glutPostRedisplay( );
  }
    break;
  case 'p': case 'P':
  {
    rotacion();
    initgl();
  }
    break;
  case 'o': case 'O':
  {
    myStar->stopAnimation( );
    glutPostRedisplay( );
  }
    break;
  case 27: // ESC
    std::exit( 0 );
    break;
  default:
    break;
  } // end switch

}
// -------------------------------------------------------------------------
void rotacion()
{
  if(phi <= 0.00){
    phi = 1.99;
  }else{
    phi -= 0.01;
  }
  posX = r*sin(theta*_PI)*sin(phi*_PI);
  posY = r*cos(theta*_PI);
  posZ = r*sin(theta*_PI)*cos(phi*_PI);
}

// -------------------------------------------------------------------------
void mouseClickCbk( int button, int state, int x, int y )
{
  if( state == GLUT_DOWN )
    myCamera.setReference( x, y );
  else
    myCamera.setReference( 0, 0 );
}

// -------------------------------------------------------------------------
void mouseMoveCbk( int x, int y )
{
  int dx, dy;
  myCamera.getReference( dx, dy, x, y );
  myCamera.setReference( x, y );

  // Apply rotations
  if( dx > 0 )      myCamera.rotY( -0.5 );
  else if( dx < 0 ) myCamera.rotY( 0.5 );
  if( dy > 0 )      myCamera.rotX( 0.5 );
  else if( dy < 0 ) myCamera.rotX( -0.5 );

  // Redraw
  glutPostRedisplay( );
}

// eof - SolarSystem.cxx
