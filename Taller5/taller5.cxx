#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include "objetos3d.h"

// -------------------------------------------------------------------------
float dx =1.5 , dy=1.5 , dz= 10.0;

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
  gluLookAt( dx, dy, dz, 0, 0, 0, 0, 1, 0 );//ESTO ES SOLO UNA APROXIMACIÓN, SOLO LO UTILIZO PARA VERFICAR QUE LOS OBJETOS ESTÉN BIEN CONSTRUIDOS


  glPushMatrix( );
  glScalef( 3, 3, 3 );
  prismaTriangular( );


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
    dx -=0.1;
  }

    else if(key == GLUT_KEY_RIGHT){
    //  std::cout << "derecha" << std::endl;
        dx +=0.1;
    }
    else if(key == GLUT_KEY_DOWN){
    //  std::cout << "abajo" << std::endl;
        dy-=0.1;
    }
    else if(key == GLUT_KEY_UP){
    //  std::cout << "arriba" << std::endl;
        dy+=0.1;
    }
    //glutPostRedisplay(); NO SE CUAL SEA LA DIFERENCIA ENTRE USAR ESTO Y EL DE ABAJO
    DisplayCbk( );
}
// -------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
  glutInitWindowPosition( 50, 50 );
  glutInitWindowSize( 500, 500 );
  glutCreateWindow( "3D test!!!" );
  glutSpecialFunc( SpecialKeyboardCbk );
  glutDisplayFunc( DisplayCbk );
  glutReshapeFunc( ResizeCbk );
  Init( );
  glutMainLoop( );

  return( 0 );
}

// eof
