#ifndef OBJETOS3D_H_INCLUDED
#define OBJETOS3D_H_INCLUDED
#define _SQRT3_3 0.57735026919
#define _SQRT3_6 0.28867513459
#define _SQRT6_6 0.40824829046
#define _1_SQRT2 0.70710678118

//TO DO
void cubo( )
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
    { -0.5, -0.5,-0.5},
    { 0.5,-0.5, -0.5 },
    { -0.5, -0.5, 0.5 },
    { 0.5, -0.5, 0.5 },
    { -0.5, 0.5, -0.5 },
    { -0.5, 0.5, 0.5 },
    { 0.5, 0.5, -0.5 },
    { 0.5, 0.5, 0.5 }
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

  for( unsigned int i = 0; i < 6; ++i )//cantidad caras
  {
    glBegin( GL_POLYGON);
    {
      for( unsigned int j = 0; j < 4; ++j )//cantidad puntos por cara
      {
        glColor3fv( colors[ faces[ i ][ j ] ] );
        glVertex3fv( points[ faces[ i ][ j ] ] );
      } // end for
    }
    glEnd( );
  } // end for
}
void tetraedro( )
{
  float colors[ 8 ][ 3 ] =
  {
    { 1, 0, 0 },
    { 0, 1, 0 },
    { 0, 0, 1 },
    { 0, 1, 1 }
  };

  float points[ 4][ 3 ] =
  {
    { 0, _SQRT6_6*(-1.0),_SQRT3_3*(-1.0)},
    { -0.5,_SQRT6_6*(-1.0), _SQRT3_6 },
    { 0.5,_SQRT6_6*(-1.0), _SQRT3_6  },
    { 0,_SQRT6_6, 0 }
  };

  unsigned int faces[ 4 ][ 3 ] =
  {
    { 0, 1, 3 },
    { 2, 3, 1},
    { 0, 3, 2 },
    { 0, 2, 1 }
  };

  for( unsigned int i = 0; i < 4; ++i )//cantidad caras
  {
    glBegin( GL_POLYGON);
    {
      for( unsigned int j = 0; j < 3; ++j )//cantidad puntos por cara
      {
        glColor3fv( colors[ faces[ i ][ j ] ] );
        glVertex3fv( points[ faces[ i ][ j ] ] );
      } // end for
    }
    glEnd( );
  } // end for
}
void octaedro( )
{
  float colors[ 6 ][ 3 ] =
  {
    { 1, 0, 0 },
    { 0, 1, 0 },
    { 0, 0, 1 },
    { 0, 1, 1 },
    { 1, 0, 1 },
    { 1, 1, 0 }
  };

  float points[ 6 ][ 3 ] =
  {
    { 0, _1_SQRT2,0},
    { -0.5, 0, -0.5 },
    { -0.5, 0, 0.5 },
    { 0.5, 0, 0.5 },
    { 0.5, 0, -0.5 },
    { 0,_1_SQRT2*(-1.0),0}
  };

  unsigned int faces[ 8 ][ 3 ] =
  {
    { 4, 1, 0 },
    { 1, 2, 0 },
    { 3, 0, 2 },
    { 4, 0, 3 },
    { 4, 5, 1 },
    { 1, 5, 2 },
    { 5, 3, 2 },
    { 5, 4, 3 }
  };

  for( unsigned int i = 0; i < 8; ++i )//cantidad caras
  {
    glBegin( GL_POLYGON);
    {
      for( unsigned int j = 0; j < 3; ++j )//cantidad puntos por cara
      {
        glColor3fv( colors[ faces[ i ][ j ] ] );
        glVertex3fv( points[ faces[ i ][ j ] ] );
      } // end for
    }
    glEnd( );
  } // end for
}

void prismaTriangular( )
{
  float colors[ 6 ][ 3 ] =
  {
    { 1, 0, 0 },
    { 0, 1, 0 },
    { 0, 0, 1 },
    { 0, 1, 1 },
    { 1, 0, 1 },
    { 1, 1, 0 }
  };

  float points[ 6][ 3 ] =
  {
    { 0, 0.5,_SQRT3_3*(-1.0)},
    { -0.5,0.5, _SQRT3_6 },
    { 0.5, 0.5, _SQRT3_6 },
    { 0, -0.5, _SQRT3_3*(-1.0)},
    { -0.5,-0.5, _SQRT3_6 },
    { 0.5,-0.5, _SQRT3_6 }
  };

  int faces[ 5 ][ 4 ] =
  {
    { 0, 1, 2, -1 },
    { 0, 3, 4, 1 },
    { 2, 1, 4, 5 },
    { 0, 2, 5, 3 },
    { 3, 5, 4, -1 }
  };

  for( unsigned int i = 0; i < 5; ++i )//cantidad caras
  {
    glBegin( GL_POLYGON);
    {
      for( unsigned int j = 0; j < 4; ++j )//cantidad puntos por cara
      {
        if(faces[i][j] != -1){
        	glColor3fv( colors[ faces[ i ][ j ] ] );
        	glVertex3fv( points[ faces[ i ][ j ] ] );
        }
      } // end for
    }
    glEnd( );
  } // end for
}

// -------------------------------------------------------------------------
#endif // OBJETOS3D_H_INCLUDED