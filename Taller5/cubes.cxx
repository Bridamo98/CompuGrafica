#include <GL/glut.h>
#include <cmath>
#include <iostream>

// -------------------------------------------------------------------------
void DrawUnitaryCube( )
{
  float colors[ 8 ][ 3 ] =
  {
    { 1, 0, 0 },
    { 0, 1, 0 },
    { 0, 0, 1 },
    { 0, 1, 1 },
    { 1, 0, 1 },
    { 1, 1, 0 },
    { 0.5, 0.5, 0.5 },
    { 1, 1, 1 }
  };

  float points[ 8 ][ 3 ] =
  {
    { 0, 0, 0 },
    { 1, 0, 0 },
    { 0, 0, 1 },
    { 1, 0, 1 },
    { 0, 1, 0 },
    { 0, 1, 1 },
    { 1, 1, 0 },
    { 1, 1, 1 }
  };

  unsigned int faces[ 6 ][ 4 ] =
  {
    { 0, 1, 3, 2 },
    { 0, 2, 5, 4 },
    { 2, 3, 7, 5 },
    { 5, 7, 6, 4 },
    { 1, 6, 7, 3 },
    { 1, 0, 4, 6 }
  };

  for( unsigned int i = 0; i < 6; ++i )
  {
    glBegin( GL_LINE_LOOP );
    {
      for( unsigned int j = 0; j < 4; ++j )
      {
        glColor3fv( colors[ faces[ i ][ j ] ] );
        glVertex3fv( points[ faces[ i ][ j ] ] );
      } // end for
    }
    glEnd( );
  } // end for
}

// -------------------------------------------------------------------------
void Init( )
{
  glClearColor( 0.7, 0.7, 0.7, 0.0 );
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
  gluLookAt( 1.5, 1.5, 10, 0, 0, 0, 0, 1, 0 );

  // Cubo 1
  glPushMatrix( );
  glScalef( 3, 3, 3 );
  DrawUnitaryCube( );

  // Cubo 2
  glPopMatrix( );
  glPushMatrix( );
  glScalef( 2, 1.5, 1 );
  DrawUnitaryCube( );

  // Finish
  glutSwapBuffers( );
}

// -------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
  glutInitWindowPosition( 50, 50 );
  glutInitWindowSize( 500, 500 );
  glutCreateWindow( "3D test!!!" );
  glutDisplayFunc( DisplayCbk );
  glutReshapeFunc( ResizeCbk );
  Init( );
  glutMainLoop( );

  return( 0 );
}

// eof
