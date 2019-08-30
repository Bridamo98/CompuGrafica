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
void DrawTree(float trasX, float trasY, float tam)
{
  // Tronco Arbol
  glLoadIdentity();
  glTranslated((1.3+trasX)*tam,(-1.1+trasY)*tam,0);
  glScaled(0.45*tam,1*tam,1*tam);
  glColor3f(0.36,0.20,0.09);
  DrawSquare( GL_POLYGON );

  // Primera rama
  glLoadIdentity();
  glTranslated((1.3+trasX)*tam,(-0.4+trasY)*tam,0);
  glScaled(0.8*tam,0.8*tam,1*tam);
  glColor3f(0.22,0.49,0.01);
  DrawTriangle( GL_POLYGON );

  // Segunda rama
  glLoadIdentity();
  glTranslated((1.3+trasX)*tam,(-0.2+trasY)*tam,0);
  glScaled(0.8*tam,0.8*tam,1*tam);
  glColor3f(0.23,0.40,0.16);
  DrawTriangle( GL_POLYGON );

  //Tercera rama
  glLoadIdentity();
  glTranslated((1.3+trasX)*tam,(-0.02+trasY)*tam,1);
  glScaled(0.8*tam,0.8*tam,0*tam);
  glColor3f(0.27,0.55,0.0);
  DrawTriangle( GL_POLYGON );
}

// -------------------------------------------------------------------------
void DrawHouse(float trasX, float trasY ,float tam)
{
  //casa
  glLoadIdentity();
  glTranslated((0.0+trasX)*tam,(-0.8+trasY)*tam,0);
  glScaled(-0.7*tam, 1.6*tam, 1*tam);
  glColor3f( 0.87, 0.49, 0.20 );
  DrawSquare( GL_POLYGON );

  // Techo
  glLoadIdentity();
  glTranslated((0.0+trasX)*tam,(0.43+trasY)*tam,0);
  glScaled(1.8*tam,1*tam,1*tam);
  glColor3f(0.8,0.0,0.0);
  DrawTriangle( GL_POLYGON );
}

// -------------------------------------------------------------------------
void DrawCar(float trasX, float trasY, float tam )
{
  // Frente carro
  glLoadIdentity();
  glTranslated((-0.7+trasX)*tam,(-1.2+trasY)*tam,0);
  glScaled(0.3*tam,0.3*tam,1*tam);
  glColor3f(0,0,1);
  DrawSquare( GL_POLYGON );

  // Atras carro
  glLoadIdentity();
  glTranslated((-1.1+trasX)*tam,(-1.1+trasY)*tam,0);
  glScaled(0.5*tam,0.5*tam,1*tam);
  glColor3f(0.80,0.79,0.71);
  DrawSquare( GL_POLYGON );

  // Llanta delantera
  glLoadIdentity();
  glTranslated((-0.95+trasX)*tam,(-1.42+trasY)*tam,0);
  glScaled(0.07*tam,0.07*tam,1*tam);
  glColor3f(0.21,0.21,0.21);
  DrawCircle( GL_POLYGON, 100 );

  // Llanta Trasera
  glLoadIdentity();
  glTranslated((-1.25+trasX)*tam,(-1.42+trasY)*tam,0);
  glScaled(0.07*tam,0.07*tam,1*tam);
  glColor3f(0.21,0.21,0.21);
  DrawCircle( GL_POLYGON, 100 );
}

// -------------------------------------------------------------------------
void DrawFloor( float trasX, float trasY, float tam)
{
  //piso
  glLoadIdentity();
  glTranslated((-1+trasX)*tam,(-1.55+trasY)*tam,0);
  glScaled(1.25*tam,-0.1*tam,1*tam);
  glColor3f(0.20,0.0,0.0);
  DrawSquare( GL_POLYGON );
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
  DrawBase();
  
  for (float i = 0.0; i < 16.0; i = i + 0.75)//fila de arboles
  {
  	DrawTree(-9.0+i,7.0,0.25);
  }
  for (float i = 0.0; i < 16.0; i = i + 0.75)//fila de arboles
  {
  	DrawTree(-9.0+i,4.0,0.35);
  }
  for (float i = 0.0; i < 16.0; i = i + 0.75)//fila de arboles
  {
  	DrawTree(-9.0+i,2.0,0.45);
  }
  
  float sepX=0.0;
  float sepY=0.0;
  float factEsc=1.0;
  for (int i = 0; i < 5; ++i)
  {
  	DrawHouse( 2.0+sepX,1.0+sepY,0.35*factEsc);//lado derecho
  	DrawHouse( -2.0-sepX,1.0+sepY,0.35*factEsc);//lado izquierdo

  	factEsc+=0.25;
  	sepY-=0.30;
  	sepX+=0.15;
  }
  for (float i = 0.0; i < 3.0; ++i)
  {
  	DrawCar(0.0+i,0.5,1.5);
  	DrawFloor( 0.0+i,0.5,1.5);
  }
  

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
