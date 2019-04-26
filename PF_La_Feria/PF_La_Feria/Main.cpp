/**************************Clase principal***************************************
**************************Facultad de Ingeneria*********************************
*************************Autores: Sandoval Juarez Tania**************************
*************************         Gomez de la Cruz Luis Octavio*****************
*************************Materia: Computacion Grafica****************************
*************************Semestre:2019-2****************************************
**Descripcion:******************************************************************
Se realizara una feria tomando en cuanta anteriormente imagenes 
para su comparacion
********************************************************************************/
//Incluimos las librerias
//#include <GL/glut.h>
//#include <stdlib.h>
#include "Main.h"
void InitGL(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//Limpiamos pantalla y Depth Buffer
	glMatrixMode(GL_MODELVIEW);//Reinicializamos la actual matriz Modelview
	glLoadIdentity();

	glFlush();
}
void reshape(int width, int height)   // Creamos funcion Reshape
{
	if(height == 0)	// Prevenir division entre cero
	{
		height = 1;
	}
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);// Seleccionamos Projection Matrix
	glLoadIdentity();
	// Ortogonal
	glOrtho(-10, 10, -10, 10, 0.1, 2);

	glMatrixMode(GL_MODELVIEW);	// Seleccionamos Modelview Matrix
	glLoadIdentity();
}
void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 27: exit(0);
		break;
	}
	glutPostRedisplay();
}
int main(int argc, char** argv) //Funcion principal
{
	glutInit(&argc, argv);//inicializamos OpenGL
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE); //Modo Display (Colores RGB y Alpha | Buffer Sencillo)
	glutInitWindowSize(500, 500); //Tamaño de la Ventana
	glutInitWindowPosition(0, 0);//Posicion de la Ventana
	glutCreateWindow("La feria");//Nombre de la Ventana
	InitGL();//parametros iniciales de la aplicacion
	glutDisplayFunc(display);//Indicamos a Glut funcion de dibujo
	glutReshapeFunc(reshape);//Indicamos a Glut funcion en caso de cambio de tamaño
	glutKeyboardFunc(keyboard);//Indicamos a Glut funcion de manejo de teclado
	glutMainLoop();//HaceUn ciclo del Main
	return 0;
}