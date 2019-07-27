//  introOpenGL.cpp
//  Creado por Andrea Rueda, 01/2018
//
#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <type_traits>
#define maxCant 500
using namespace std;

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
			}

			if(arriba && abajo && izquierda && derecha){
				mat[i][j] = 1;
			}

		}
	}
}

void pintar(int** mat,int yMax,int xMin,int filas, int columnas, int escala){
	for (int i = 0; i < filas; ++i)
	{
		for (int j = 0; j < columnas; ++j)
		{
       		if(mat[i][j] == 1){
       			glVertex2i(((j + xMin)*escala), ((yMax - i)*escala));
       		}
		}
	}
}

void dibujar(int cantPuntos,int escala,int puntosPrimeraCapa[maxCant][2],int yMax,int yMin,int xMax,int xMin){

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
		//cout << yMax-y << " " << x-xMin << endl;//prueba
	}
	//-------------------------------------------------------

	//rellenar(mat,filas,columnas);

	for (int i = 0; i < filas; ++i)
	{
		for (int j = 0; j < columnas; ++j)
		{
			cout << mat[i][j];
		}
		cout << endl;
	}

	pintar(mat, yMax, xMin, filas, columnas, escala);
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
    

    glPointSize(1.0);//grosor del punto ------ ENTRADA
    glColor3f(0.0, 0.0, 0.0);//definir el color de la primera capa ------ ENTRADA
    glBegin(GL_POINTS);
    	//ENTRADAS PRIMERA CAPA----------------------------------
    	int cantPuntos = 129;
    	int escala=1;// esto depende de la escala de los puntos ingresados a continución
    	int puntosPrimeraCapa[cantPuntos][2]={//puntos del borde de la primera capa, ya deben estar escalados
    		{34,75},{36,75},{38,74},{40,74},{43,73},{45,72},{46,72},{48,71},{50,70},{51,69},{52,68},{54,67},{55,66},{57,65},{57,64},{58,63},
    		{59,64},{62,64},{64,65},{65,65},{68,65},{70,64},{74,63},{75,63},{77,64},{78,65},{79,66},{80,67},{81,68},{82,69},{84,70},{85,71},
    		{87,72},{89,73},{91,74},{93,75},{94,75},{96,76},{97,76},{99,77},{100,78},{100,75},{100,74},{100,72},{100,69},{101,66},{101,65},
    		{101,63},{101,61},{102,58},{102,56},{100,55},{99,52},{98,51},{97,50},{96,49},{95,48},{96,46},{97,45},{98,44},{98,43},{98,40},{98,38},{97,36},
    		{97,35},{96,34},{95,32},{94,30},{93,28},{93,26},{91,25},{89,24},{87,23},{86,22},{85,21},{84,20},{82,19},{79,19},{78,18},{76,17},{75,17},
    		{73,16},{72,15},{69,14},{67,15},{65,15},{73,16},{62,17},{60,18},{59,17},{56,18},{55,18},{54,19},{53,20},{50,20},{49,21},{48,22},
    		{47,23},{45,24},{44,26},{43,27},{42,28},{41,29},{40,30},{40,32},{39,34},{39,36},{37,37},{36,40},{36,43},{37,45},{38,47},{39,49},
    		{37,50},{36,52},{35,53},{34,54},{33,55},{34,56},{36,57},{35,58},{34,59},{33,60},{33,62},{33,64},{33,66},{33,67},{33,70},{34,73}
    	};
    	int yMax=78, yMin=14, xMax=102, xMin=33;//
    	dibujar(cantPuntos,escala,puntosPrimeraCapa,yMax,yMin,xMax,xMin);
    	//------------------------------------------
    glEnd();

    //aquí se hará lo mismo con las demás capas ...
    // ...
    // ...
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
    
    glutInitWindowSize(130, 90); 
    
    glutInitWindowPosition(100, 100); 

    glutCreateWindow("Graphics Window"); 
    
    glutDisplayFunc(myDisplay);
    
    glutReshapeFunc(myResize); 
    
    myInit(); 
    
    glutMainLoop(); 
    
    return 0;

}