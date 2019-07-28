//  introOpenGL.cpp
//  Creado por Andrea Rueda, 01/2018
//
#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <type_traits>
#define maxCant 500
using namespace std;
int ancho=650;
int alto=500;
bool validar(int i, int j, int ii, int jj, int filas, int columnas, int** mat){
	bool validacion = false;
	while(i > 0 && i < filas-1 && j > 0 && j-1 < columnas-1){
		i = i + ii;
		j = j + jj;
		if(mat[i][j] == 1){
			validacion = true;
			break;
		}
	}
	return validacion;
}
void rellenar(int** mat, int filas, int columnas){
	bool arriba, abajo, izquierda, derecha;
	for (int i = 0; i < filas; ++i)
	{
		for (int j = 0; j < columnas; ++j)
		{
			if(mat[i][j] != 1){
				arriba = validar(i,j,-1,0,filas, columnas, mat);//arriba
				abajo = validar(i,j,1,0,filas, columnas, mat);//abajo
				izquierda = validar(i,j,0,-1,filas, columnas, mat);//izquierda
				derecha = validar(i,j,0,1,filas, columnas, mat);//derecha
				if(arriba && abajo && izquierda && derecha){
				mat[i][j] = 2;
				}
			}
		}
	}
}

void pintar(int** mat,int yMax,int xMin,int filas, int columnas, int escala, float* rgbInterior, float* rgbExterior){
	for (int i = 0; i < filas; ++i)
	{
		for (int j = 0; j < columnas; ++j)
		{
       		if(mat[i][j] == 2){
       			glColor3f(rgbInterior[0],rgbInterior[1],rgbInterior[2]);
       			glVertex2i(((j + xMin)*escala), ((yMax - i)*escala));
       		}
       		if(mat[i][j] == 1){
       			glColor3f(rgbExterior[0],rgbExterior[1],rgbExterior[2]);
       			glVertex2i(((j + xMin)*escala), ((yMax - i)*escala));
       		}
		}
	}
}

void dibujar(int cantPuntos,int escala,int puntosPrimeraCapa[maxCant][2],int yMax,int yMin,int xMax,int xMin, float* rgbInterior, float* rgbExterior){
  int filas=yMax - yMin + 1, columnas=xMax - xMin + 1;//Crear e inizializar variables
	int** mat = new int*[filas];
	for (int i = 0; i < filas; ++i){
    	mat[i] = new int[columnas];
	}

	for (int i = 0; i < filas; ++i)
	{
		for (int j = 0; j < columnas; ++j)
		{
			mat[i][j]=0;
		}
	}
	int x, y;
	//--------------------------------------------------------------
	for (int i = 0; i < cantPuntos; ++i)//conversión de ejes y coordenadas
	{
		x = puntosPrimeraCapa[i][0];
		y = puntosPrimeraCapa[i][1];
		mat[yMax - y][x - xMin] = 1;
	}
	//-------------------------------------------------------
	rellenar(mat,filas,columnas);
	pintar(mat, yMax, xMin, filas, columnas, escala, rgbInterior, rgbExterior);
}

void fondo(float r,float g, float b, int dispersion, int trasX, int trasY){
    glColor3f(r, g, b);
	for (int i = 0; i < ancho; ++i)
	{
		for (int j = 0; j < alto; ++j)
		{
			if(i%dispersion == 0 && j%dispersion == 0){
       			glVertex2i(i+trasY, j+trasX);
			}
		}
	}
}

void myInit (void) {

    glClearColor(1.0,1.0,1.0,1.0);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(0, 640, 0, 480);
    //glOrtho(0, 640, 0, 480, 1.0, -1.0);

}

void myDisplay (void) {
    
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(4.0);
    glBegin(GL_POINTS);
    	fondo(0.0, 1.0, 0.5, 20, 0, 0);
    glEnd();
    glPointSize(3.0);
    glBegin(GL_POINTS);
    	fondo(0.0, 1.0, 0.6, 20, 10, 10);
    glEnd();
    glPointSize(3.0);
    glBegin(GL_POINTS);
    	fondo(0.0, 1.0, 0.8, 20, 10, -10);
    glEnd();
    glPointSize(6.0);
    glBegin(GL_POINTS);
    	float* rgbInterior = new float[3];
    	rgbInterior[0]=0.78;
    	rgbInterior[1]=0.43;
    	rgbInterior[2]=0.02;
    	float* rgbExterior = new float[3];
    	rgbExterior[0]=0.9;
    	rgbExterior[1]=0.43;
    	rgbExterior[2]=0.02;
    	int cantPuntos = 108;
    	int escala=10;// esto depende de la escala de los puntos ingresados a continución
    	int puntosPrimeraCapa[cantPuntos][2]={//puntos del borde de la primera capa, ya deben estar escalados
				{16,40},{17,41},{18,42},{18,43},{19,44},{20,44},{21,44},{22,43},{23,42},{24,41},{25,40},{26,39},{27,38},{28,37},{29,38},{30,39},
    		{31,39},{32,39},{33,39},{34,39},{35,39},{36,39},{37,39},{38,38},{39,37},{40,38},{40,39},{41,40},{42,41},{43,42},{44,42},{45,43},{46,44},{47,44},{48,44},{49,44},{50,44},{50,43},{50,42},{50,41},
    		{50,40},{50,39},{50,38},{50,37},{50,36},{50,35},{50,34},{50,33},{50,32},{49,31},{48,30},{47,29},{47,28},{48,27},{48,26},
    		{48,25},{48,24},{48,23},{48,22},{47,22},{47,21},{46,20},{45,19},{45,18},{44,17},{43,16},{42,15},{41,15},{40,14},{39,13},{38,13},{37,13},
    		{36,12},{35,12},{34,12},{33,12},{32,12},{31,12},{30,13},{29,13},{28,13},{27,14},{26,15},{25,16},{24,16},{23,17},{22,18},{21,19},{20,20},
    		{19,21},{19,22},{18,23},{18,24},{18,25},{18,26},{18,27},{19,28},{19,29},{18,30},{17,31},{16,32},{16,33},{16,34},{16,35},{16,36},
    		{16,37},{16,38},{16,39}
    	};
		int yMax=44, yMin=12, xMax=50, xMin=16;
		dibujar(cantPuntos,escala,puntosPrimeraCapa,yMax,yMin,xMax,xMin, rgbInterior, rgbExterior);
	    rgbInterior[0]=1.0;
	    rgbInterior[1]=0.97;
	    rgbInterior[2]=0.86;
	    rgbExterior[0]=1.0;
	   	rgbExterior[1]=0.97;
	    rgbExterior[2]=0.86;
		cantPuntos = 8;
		int puntosBarbilla[cantPuntos][2]={
			{36,12},{35,12},{34,12},{33,12},{32,12},{33,13},{34,14},{35,13}
		};
		yMax=14; yMin=12; xMax=36; xMin=32;
		dibujar(cantPuntos,escala,puntosBarbilla,yMax,yMin,xMax,xMin, rgbInterior, rgbExterior);
	    rgbInterior[0]=1.0;
	    rgbInterior[1]=0.97;
	    rgbInterior[2]=0.86;
	    rgbExterior[0]=1.0;
	    rgbExterior[1]=0.97;
	    rgbExterior[2]=0.86;
		cantPuntos = 14;
		int puntosOrejaI[cantPuntos][2]={
			{18,38},{19,38},{22,33},{21,33},{22,34},{20,33},{19,34},{18,35},{18,36},{18,37},
			{20,37},{21,37},{22,36},{23,35}
		};
		yMax=38; yMin=33; xMax=23; xMin=18;
		dibujar(cantPuntos,escala,puntosOrejaI,yMax,yMin,xMax,xMin, rgbInterior, rgbExterior);
	    rgbInterior[0]=0.54;
	    rgbInterior[1]=0.21;
	    rgbInterior[2]=0.06;
	    rgbExterior[0]=0.54;
	    rgbExterior[1]=0.21;
	    rgbExterior[2]=0.06;
		cantPuntos = 10;
		int puntossSombraI[cantPuntos][2]={
			{20,38},{21,38},{22,37},{23,36},{24,35},{23,34},
			{20,37},{21,37},{22,36},{23,35}
		};
		yMax=38; yMin=34; xMax=24; xMin=20;
		dibujar(cantPuntos,escala,puntossSombraI,yMax,yMin,xMax,xMin, rgbInterior, rgbExterior);
		rgbInterior[0]=1.0;
	    rgbInterior[1]=0.97;
	    rgbInterior[2]=0.86;
	    rgbExterior[0]=1.0;
	    rgbExterior[1]=0.97;
	    rgbExterior[2]=0.86;
		cantPuntos = 13;
		int puntosOrejaD[cantPuntos][2]={
			{47,38},{48,38},{48,37},{48,36},{48,35},{48,34},{47,33},{46,33},{45,33},
			{44,34},{45,35},{46,36},{47,37}
		};
		yMax=38; yMin=33; xMax=48; xMin=44;//
		dibujar(cantPuntos,escala,puntosOrejaD,yMax,yMin,xMax,xMin, rgbInterior, rgbExterior);
	    rgbInterior[0]=0.54;
	    rgbInterior[1]=0.21;
	    rgbInterior[2]=0.06;
	    rgbExterior[0]=0.54;
	    rgbExterior[1]=0.21;
	    rgbExterior[2]=0.06;
		cantPuntos = 9;
		int puntossSombraD[cantPuntos][2]={
			{43,35},{44,36},{45,37},{46,38},{47,38},
			{44,34},{45,35},{46,36},{47,37}
		};
		yMax=38; yMin=34; xMax=47; xMin=43;
		dibujar(cantPuntos,escala,puntossSombraD,yMax,yMin,xMax,xMin, rgbInterior, rgbExterior);
	    rgbInterior[0]=1.0;
	    rgbInterior[1]=0.97;
	    rgbInterior[2]=0.86;
	    rgbExterior[0]=0.0;
	    rgbExterior[1]=0.0;
	    rgbExterior[2]=0.0;
		cantPuntos = 16;
		int puntosOjoI[cantPuntos][2]={
			{25,28},{26,29},{27,29},{28,29},{29,28},{30,27},{30,26},{30,25},
			{29,24},{28,23},{27,23},{26,23},{25,24},{24,25},{24,26},{24,27}
		};
		yMax=29; yMin=23; xMax=30; xMin=24;//
		dibujar(cantPuntos,escala,puntosOjoI,yMax,yMin,xMax,xMin, rgbInterior, rgbExterior);
		cantPuntos = 16;
		int puntosOjoD[cantPuntos][2]={
			{40,28},{41,29},{42,29},{43,29},{44,28},{45,27},{45,26},{45,25},
			{44,24},{43,23},{42,23},{41,23},{40,24},{39,25},{39,26},{39,27}
		};
		yMax=29; yMin=23; xMax=45; xMin=39;//
		dibujar(cantPuntos,escala,puntosOjoD,yMax,yMin,xMax,xMin, rgbInterior, rgbExterior);
	    rgbInterior[0]=1.0;
	    rgbInterior[1]=0.97;
	    rgbInterior[2]=0.86;
	    rgbExterior[0]=1.0;
	    rgbExterior[1]=0.97;
	    rgbExterior[2]=0.86;
		cantPuntos = 26;
		int puntosSombraNariz[cantPuntos][2]={
			{34,34},{35,34},{36,33},{37,32},{38,31},{38,30},{38,29},{38,28},{38,27},{37,26},{37,25},{36,24},{36,23},
			{35,22},{34,23},{33,24},{32,25},{31,25},{31,26},{31,27},{31,28},{31,29},{31,30},{31,31},{32,32},{33,33}
		};
		yMax=34; yMin=22; xMax=38; xMin=31;//
		dibujar(cantPuntos,escala,puntosSombraNariz,yMax,yMin,xMax,xMin, rgbInterior, rgbExterior);
	    rgbInterior[0]=0.54;
	    rgbInterior[1]=0.21;
	    rgbInterior[2]=0.06;
	    rgbExterior[0]=0.0;
	    rgbExterior[1]=0.0;
	    rgbExterior[2]=0.0;
		cantPuntos = 31;
		int puntosBoca[cantPuntos][2]={
			{29,20},{30,21},{31,22},{32,22},{33,22},{34,22},{35,22},{36,22},{37,22},{38,21},{39,20},{40,19},{40,18},{40,17},{40,16},
			{39,15},{38,14},{37,13},{36,13},{35,14},{34,15},{33,14},{32,13},{31,12},{30,13},{29,14},{28,15},{28,16},{28,17},{28,18},
			{28,19}
		};
		yMax=22; yMin=12; xMax=40; xMin=28;//
		dibujar(cantPuntos,escala,puntosBoca,yMax,yMin,xMax,xMin, rgbInterior, rgbExterior);
	    rgbInterior[0]=0.37;
	    rgbInterior[1]=0.15;
	    rgbInterior[2]=0.07;
	    rgbExterior[0]=0.0;
	    rgbExterior[1]=0.0;
	    rgbExterior[2]=0.0;
		cantPuntos =8;
		int puntosNariz[cantPuntos][2]={
			{35,20},{36,20},{37,19},{36,18},{35,18},{34,18},{33,19},{34,20}
		};
		yMax=20; yMin=18; xMax=37; xMin=33;
		dibujar(cantPuntos,escala,puntosNariz,yMax,yMin,xMax,xMin, rgbInterior, rgbExterior);
    glEnd();
    glFlush();
}


void myResize (int w, int h) {

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(0, w, 0, h);

}


int main (int argc, char** argv) {

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(ancho, alto);

    glutInitWindowPosition(100, 100);

    glutCreateWindow("Graphics Window");

    glutDisplayFunc(myDisplay);

    glutReshapeFunc(myResize);

    myInit();

    glutMainLoop();

    return 0;

}
