#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include "objetos3d.h"
#define PI 3.14159265
// -------------------------------------------------------------------------
float r = 10.0 , theta=0.50 , phi= 0.00, posX = r * sin(theta*PI)*sin(phi*PI), posY = r*cos(theta*PI), posZ = r*sin(theta*PI)*cos(phi*PI);

void Init( )
{
  glClearColor( 1.0, 1.0, 1.0, 0.0 );
}

// -------------------------------------------------------------------------
void ResizeCbk( int width, int height )
{
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  glViewport( 0, 0, width, height );
 
  // Ortho
  // glOrtho( -2, 6, 0, 8, -2, 200 );

  // Prespective
  gluPerspective(
    45,
    float( width ) / float( height ),
    0.01, 200
    );
}

// -------------------------------------------------------------------------
void DisplayCbk( )
{

  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glMatrixMode( GL_MODELVIEW );
  
  // Camara
  glLoadIdentity( );
  gluLookAt( posX, posY, posZ, 0, 0, 0, 0, 1, 0 );


  glPushMatrix( );
  glScalef( 3, 3, 3 );
  prismaTriangular( );

  glPopMatrix();

  glPushMatrix( );
  glScalef( 1.5, 1.5, 1.5 );
  glTranslatef(1.5,1.5,1.5);
  tetraedro( );

  glPopMatrix();

  glPushMatrix( );
  glTranslatef(2.5,2.5,0);
  glScalef( 0.5, 0.5, 0.5 );
  cubo( );



  glPopMatrix();//MUY IMPORTANTE ESTE POP FINAL

  // Cubo 1 CÓDIGO DEL PROFESOR
  /*glPushMatrix( );
  glScalef( 3, 3, 3 );
  DrawUnitaryCube( );

  // Cubo 2
  glPopMatrix( );
  glPushMatrix( );
  glScalef( 2, 1.5, 1 );
  DrawUnitaryCube( );*/

  // Finish
  glutSwapBuffers( );
}
// -------------------------------------------------------------------------
void SpecialKeyboardCbk( int key, int x, int y ) // id tecla especial, GLUT_F1 GLUT_UP, etc -
{

  if(key == GLUT_KEY_LEFT){
    //  std::cout << "izquierda" << std::endl;
    if(phi <= 0.00){
      phi = 1.99;
    }else{
      phi -= 0.01; 
    }
  }
  else if(key == GLUT_KEY_RIGHT){
  //  std::cout << "derecha" << std::endl;
    if (phi >= 2.00)
    {
      phi = 0.01;
    }else{
      phi += 0.01;
    }
  }
  else if(key == GLUT_KEY_DOWN){
  //  std::cout << "abajo" << std::endl;
    if (theta < 0.99)
    {
      theta += 0.01;
    }
  }
  else if(key == GLUT_KEY_UP){
  //  std::cout << "arriba" << std::endl;
    if (theta > 0.01)
    {
      theta -= 0.01;
    }
  }
  posX = r * sin(theta*PI)*sin(phi*PI);
  posY = r*cos(theta*PI);
  posZ = r*sin(theta*PI)*cos(phi*PI);
  //glutPostRedisplay();// NO SE CUAL SEA LA DIFERENCIA ENTRE USAR ESTO Y EL DE ABAJO
  DisplayCbk( );
}

// -------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//parámetro para permitir efecto de superposición (GLUT_DEPTH)
  glutInitWindowPosition( 50, 50 );
  glutInitWindowSize( 500, 500 );
  glutCreateWindow( "3D test!!!" );

  glEnable(GL_DEPTH_TEST);//Para permitir efecto de superposición

  glutSpecialFunc( SpecialKeyboardCbk );
  glutDisplayFunc( DisplayCbk );
  glutReshapeFunc( ResizeCbk );
  Init( );
  glutMainLoop( );

  return( 0 );
}

// eof
