/* -------------------------------------------------------------------------
 * @brief Example on how to draw simple 2D shapes
 * @author Leonardo Fl�rez-Valencia (florez-l@javeriana.edu.co)
 * -------------------------------------------------------------------------
 * Compilation on linux:
 *
 * g++ -std=c++17 simple_2d_scene.cxx -lm -lGL -lGLU -lglut -o mySimple2DScene
 *
 * -------------------------------------------------------------------------
 */

#include <GL/glut.h>
#include <cmath>
#include <iostream>

// -------------------------------------------------------------------------
#define _PI      3.14159265359
#define _2PI     6.28318530718
#define _SQRT3   1.73205080757
#define _SQRT3_2 0.86602540378
#define _SQRT3_3 0.57735026919
#define _SQRT3_4 0.43301270189

#define WORLD_MIN_X -2
#define WORLD_MIN_Y -2
#define WORLD_MAX_X  2
#define WORLD_MAX_Y  2

// -------------------------------------------------------------------------
void DrawCircle( GLenum mode, unsigned int samples ) //modo line loop (linea), poligon (coloreado) - puntos
{
  glBegin( mode );
  for( unsigned int i = 0; i < samples; ++i )
  {
    float t = _2PI * float( i ) / float( samples );
    glVertex2f( std::cos( t ), std::sin( t ) );
  } // end if
  glEnd( );
}

// -------------------------------------------------------------------------
void DrawSquare( GLenum mode )
{
  glBegin( mode );
  {
    glVertex2f( -0.5, -0.5 );
    glVertex2f( -0.5,  0.5 );
    glVertex2f(  0.5,  0.5 );
    glVertex2f(  0.5, -0.5 );
  }
  glEnd( );
}

// -------------------------------------------------------------------------
void DrawTriangle( GLenum mode )
{
  glBegin( mode );
  {
    glVertex2f( -0.5, -_SQRT3_4 );
    glVertex2f(  0.5, -_SQRT3_4 );
    glVertex2f(    0,  _SQRT3_4 );
  }
  glEnd( );
}

// -------------------------------------------------------------------------
void DrawBase( ) //base ortonormal, ejes x (rojo) y (verde)
{
  glBegin( GL_LINES );
  {
    glColor3f( 1, 0, 0 );
    glVertex2f( WORLD_MIN_X * 0.75, 0 );
    glVertex2f( WORLD_MAX_X * 0.75, 0 );

    glColor3f( 0, 1, 0 );
    glVertex2f( 0, WORLD_MIN_Y * 0.75 );
    glVertex2f( 0, WORLD_MAX_Y * 0.75 );
  }
  glEnd( );
}

// -------------------------------------------------------------------------
void Init( )
{
  glClearColor( 0.0, 0.0, 0.0, 0.0 );
}

// -------------------------------------------------------------------------
void ResizeCbk( int width, int height )
{
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( ); //1 en la diagonal
  glViewport( 0, 0, width, height );
  gluOrtho2D( WORLD_MIN_X, WORLD_MAX_X, WORLD_MIN_Y, WORLD_MAX_Y );
}

// -------------------------------------------------------------------------
void DisplayCbk( )
{
  // Reset viewport and model matrix
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glMatrixMode( GL_MODELVIEW ); //carga matriz modelo - se aplica a todos los puntos
  glLoadIdentity( );

  // Orthogonal base
  DrawBase( );
//---------- Cuadrados -------------------------------------
  //casa
  glTranslated(0,-0.8,0);
  glScaled(-0.7, 1.6, 1);
  glColor3f( 0, 0, 1 );
  DrawSquare( GL_POLYGON );

  //piso
  glLoadIdentity();
  glTranslated(-1,-1.55,0);
  glScaled(1.25,-0.1,1);
  glColor3f(0,0,1);
  DrawSquare( GL_POLYGON );

  // Frente carro
  glLoadIdentity();
  glTranslated(-0.7,-1.2,0);
  glScaled(0.3,0.3,1);
  glColor3f(0,0,1);
  DrawSquare( GL_POLYGON );

  // Atras carro
  glLoadIdentity();
  glTranslated(-1.1,-1.1,0);
  glScaled(0.5,0.5,1);
  glColor3f(0,1,1);
  DrawSquare( GL_POLYGON );

  // Tronco Arbol
  glLoadIdentity();
  glTranslated(1.3,-1.1,0);
  glScaled(0.45,1,1);
  glColor3f(0,0,1);
  DrawSquare( GL_POLYGON );

//------------ Circulos -----------------------------------
  // Llanta delantera
  glLoadIdentity();
  glTranslated(-0.95,-1.42,0);
  glScaled(0.07,0.07,1);
  glColor3f(1,1,1);
  DrawCircle( GL_POLYGON, 100 );

  // Llanta Trasera
  glLoadIdentity();
  glTranslated(-1.25,-1.42,0);
  glScaled(0.07,0.07,1);
  glColor3f(1,1,1);
  DrawCircle( GL_POLYGON, 100 );

//------------ Triangulos ---------------------------------
  // Techo
  glLoadIdentity();
  glTranslated(0,0.43,0);
  glScaled(1.8,1,1);
  glColor3f(1,1,1);
  DrawTriangle( GL_POLYGON );

  // Primera rama
  glLoadIdentity();
  glTranslated(1.3,-0.4,0);
  glScaled(0.8,0.8,1);
  glColor3f(1,1,1);
  DrawTriangle( GL_POLYGON );

  // Segunda rama
  glLoadIdentity();
  glTranslated(1.3,-0.2,0);
  glScaled(0.8,0.8,1);
  glColor3f(1,1,1);
  DrawTriangle( GL_POLYGON );

  //Tercera rama
  glLoadIdentity();
  glTranslated(1.3,-0.02,1);
  glScaled(0.8,0.8,0);
  glColor3f(1,1,1);
  DrawTriangle( GL_POLYGON );

  // Finish
  glutSwapBuffers( );
}

// -------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
  glutInitWindowPosition( 50, 50 );
  glutInitWindowSize( 1000, 1000 );
  glutCreateWindow( "2D test!!!" );
  glutDisplayFunc( DisplayCbk );
  glutReshapeFunc( ResizeCbk );
  Init( );
  glutMainLoop( );

  return( 0 );
}

// eof - mouse_click.cxx
