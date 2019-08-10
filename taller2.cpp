/* -------------------------------------------------------------------------
 * @brief Example on how to capture mouse clicks in OpenGL
 * @author Leonardo Fl�rez-Valencia (florez-l@javeriana.edu.co)
 * -------------------------------------------------------------------------
 * Compilation on linux:
 *
 * g++ -std=c++17 mouse_click.cxx -lm -lGL -lGLU -lglut -o myMouseClickTest
 *
 * -------------------------------------------------------------------------
 */

#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <bits/stdc++.h>
#include <vector>

std::vector<std::pair<double,double>> puntosDDl;
std::vector<std::pair<double,double>> puntosB;
int contador = 0;
double x0, yo, x1, yi;
double w, h;

//--------------------------------------------------------------------------
void DDA (double x0,double y0,double x1,double y1)
{
  double dx = x1 - x0;
  double dy = y1 - y0;
  double step = 0;

  if( abs(dy) < abs(dx) )
    step = abs(dx);
  else
    step = abs(dy);

  dx = dx / step;
  dy = dy / step;

  double x = x0, y = y0;

  for(int i = 1; i <= step; i++)
  {
    std::pair<double,double> aux;
    aux.first = x;
    aux.second = y;
    puntosDDl.push_back(aux);
    x = x+dx;
    y = y+dy;
  }
}
//--------------------------------------------------------------------------
void Bresenhamx(double x0, double y0,double x1,double y1)
{
  double dx = x1 - x0;
  double dy = y1 - y0;
  double yii = 1;

  if (dy < 0)
  {
    yii = -1;
    dy = -dy;
  }
  double d = (2*dy)-dx;
  double y = y0;

  for(int x = x0; x <= x1; x++)
  {
    std::pair<double,double> aux;
    aux.first = x;
    aux.second = (double)y;
    puntosB.push_back(aux);
    if(d > 0)
    {
    	y = y + yii;
      	d = d - (2*dx);
    }
    d = d + (2*dy);
   }
}
//--------------------------------------------------------------------------
void Bresenhamy(double x0,double y0,double x1,double y1)
{
  double dx = x1 - x0;
  double dy = y1 - y0;
  double xi = 1;

  if (dx < 0)
  {
    xi = -1;
    dx = -dx;
  }
  double d = (2*dx)-dy;
  double x = x0;

  for(int y = y0; y <= y1; y++)
  {
    std::pair<double,double> aux;
    aux.first = x;
    aux.second = y;
    puntosB.push_back(aux);
    if(d > 0)
    {
    	x = x + xi;
      	d = d - (2*dy);//no cambia
    }
    d = d + (2*dx);//no cambia
   }
}
//--------------------------------------------------------------------------
void choose (double x0,double y0,double x1,double y1)
{
  double dx = x1 - x0;
  double dy = y1 - y0;

  if(abs(dx) < abs(dy))
  {
    if(dy < 0){
    	Bresenhamy(x1, y1, x0, y0);
    }else{
    	Bresenhamy(x0, y0, x1, y1);
    }

  }else{
  	if(dx < 0){
    	Bresenhamx(x1, y1, x0, y0);
  	}else{
    	Bresenhamx(x0, y0, x1, y1);
  	}
  }
 }

// -------------------------------------------------------------------------
void Init( )
{
  glClearColor( 1.0, 1.0, 1.0, 0.0 );
  glColor3f( 0.0f, 0.0f, 0.0f );
  glPointSize( 1.0f );
  gluOrtho2D( 0.0f, w, 0.0f, h );
}

// -------------------------------------------------------------------------
void MouseCbk( int button, int state, int x, int y )
{

  if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
  {
    if(contador == 0)
    {
      x0 = x;
      yo = h - y;
      contador++;
    }
    else if (contador == 1)
    {
      x1 = x;
      yi = h-y;
      choose(x0,yo,x1,yi);
      DDA(x0,yo,x1,yi);
      contador = 0;
    }
  }
  else if( button == GLUT_LEFT_BUTTON && state == GLUT_UP )
  {
    std::cout
      << "Left button up on (" << x << ", " << h-y << ")"
      << std::endl;
  } // end if

  glutPostRedisplay();

}

// -------------------------------------------------------------------------
void DisplayCbk( )
{
  unsigned char pixel[4];
  unsigned char pixel1[4];
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_POINTS);

  for(int i = 0; i < puntosDDl.size(); ++i)
  {
    glReadPixels(puntosB[i].first, puntosB[i].second, w, h, GL_RGB, GL_UNSIGNED_BYTE, pixel1);
    glVertex2f(puntosDDl[i].first, puntosDDl[i].second);
  }


  std::vector<std::pair<double,double>> comun;
  glColor3f(0.0, 1.0, 0.0);
  for(int i = 0; i < puntosB.size(); ++i)
  {
    glReadPixels(puntosB[i].first, puntosB[i].second, w, h, GL_RGB, GL_UNSIGNED_BYTE, pixel);
    if((int)pixel1[0] != (int)pixel[0] && (int)pixel1[1] != (int)pixel[1] && (int)pixel1[2] != (int)pixel[2])
    glVertex2i(puntosB[i].first, puntosB[i].second);
    else
    comun.push_back(puntosB[i]);
  }

  glColor3f(0.0, 0.0, 1.0);
  for(int i = 0; i < comun.size(); ++i)
    glVertex2i(comun[i].first, comun[i].second);
/*  sort(puntosDDl.begin(), puntosDDl.end());
  sort(puntosB.begin(), puntosB.end());
  for ( int i = 0; i < puntosB.size(); ++i)
  {
    for(int j = 0; j < puntosDDl.size(); ++j)
    {
      if(puntosB[i].first > puntosDDl[j].first)
        break;
      else if (puntosB[i] == puntosDDl[j])
        glVertex2i(puntosB[i].first, puntosB[i].second);*/
    }
  }



  glEnd();
  glutSwapBuffers();
  glFlush();
}

// -------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
  w = atof(argv[1]);
  h = atof(argv[2]);
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
  glutInitWindowPosition( 50, 50 );
  if(argc < 4)
  {

    glutInitWindowSize( w, h);
    glutCreateWindow( "mouse_click test!!!" );
    glutDisplayFunc( DisplayCbk );
    glutMouseFunc( MouseCbk );
    Init( );
  }

  glutMainLoop( );

  return( 0 );
}

// eof - mouse_click.cxx
