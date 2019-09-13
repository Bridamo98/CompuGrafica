#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include "objetos3d.h"
#define PI 3.14159265
// -------------------------------------------------------------------------
float r = 15.0 , theta=0.50 , phi= 0.00, posX = r * sin(theta*PI)*sin(phi*PI), posY = r*cos(theta*PI), posZ = r*sin(theta*PI)*cos(phi*PI);

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
    0.01, 400
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

// Luna derecha ----------------------
  glPushMatrix( );
  glTranslatef(4.75,4,0);
  glRotatef(14.0362,0,0,1);
  glScalef( 1.11803, 1.25, 1.11803);
  tetraedro( ); 

  glPopMatrix();

// Planeta derecha superior ----------------------

  glPushMatrix( );
  glTranslatef(6,1.5,0);
  glRotatef(14.0362,0,0,1);
  glScalef( 1.11803, 1.11803, 1.11803);
  cubo( );

  glPopMatrix();

  //prueba
  glPushMatrix( );
  glTranslatef(6,1.5,0);
  prismaTriangular( );  

  glPopMatrix();

// Planeta derecha inferior ----------------------

  glPushMatrix( );
  glTranslatef(5.5,-0.5,0);
  glRotatef(45.0,0,1,0);
  glScalef( 0.70812 , 0.70812, 0.70812);
  octaedro( );

  glPopMatrix();

// Sol ----------------------

  glPushMatrix( );
  glRotatef(45.0,0,1,0);
  glScalef( 1.58112 ,1.58112, 1.58112);
  octaedro( );

  glPopMatrix();

// Planeta izquierda superior ----------------------

  glPushMatrix( );
  glTranslatef(-6 ,3 ,0);
  glRotatef(-14.0362,0,0,1);
  glScalef( 1.11821 , 1.25, 1.11821);
  tetraedro( );

  glPopMatrix();

// Luna izquierda superior ----------------------

  glPushMatrix( );
  glTranslatef(-5, 4.5,0);
  glRotatef(45,0,0,1);
  glScalef( 0.70812 , 0.70812, 0.70812);
  cubo( );

  glPopMatrix();

// Luna izquierda inferior ----------------------

  glPushMatrix( );
  glTranslatef(-5.25,0.75,0);
  glRotatef(18.43491,0,0,1);
  glScalef( 0.55012, 0.79061,  0.55012);
  prismaTriangular( );

  glPopMatrix();

// Planeta izquierda inferior ----------------------

  glPushMatrix( );
  glTranslatef(-5,-3,0);
  glRotatef(30.96,0,0,1);
  glScalef( 1.45772, 1.67731, 1.45772 );
  prismaTriangular( );

  glPopMatrix();
// Planeta izquierda inferior ----------------------

  glPushMatrix( );
  glTranslatef(-3,-3,0);
  glRotatef(30.96,0,0,1);
  glScalef( 0.35392, 0.55931, 0.35392 );
  octaedro( );

  glPopMatrix();//MUY IMPORTANTE ESTE POP FINAL

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
  glutInitWindowSize( 700, 700 );
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
