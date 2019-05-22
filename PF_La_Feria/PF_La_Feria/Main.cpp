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
#include "texture.h"
#include "figuras.h"
#include "Camera.h"
#include "cmodel\CModel.h"
#include "GL\glut.h"
//#include "Main.h"

//Atributos
GLfloat Ambient[] = { 1,1,1,1 };
GLfloat Diffuse[] = { 1,1,1,1 };								// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW)
CCamera objCamera;
float Velocidad = 0.0;
float angulotazas = 50.0;

//Figuras
CFiguras fig1;//caja del mundo cielo
CFiguras fig2;//Taza

//Texturas
CTexture text1;//vista del cielo con llanuras
CTexture text2;//PAsto
//Modelos
//CModel model1;
//Metodos
void InitGL(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //Fondo negro
	glEnable(GL_TEXTURE_2D); //Hbilitamos las texturas en 2D
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);//Habilitamos las luces
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, Ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Specular);

	glClearDepth(1.0f);	// Activamos el valor de inicio del buffer de profundidad
	glEnable(GL_DEPTH_TEST);// Hacemos la prueba de profundidad
	glDepthFunc(GL_LEQUAL);	// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	text1.LoadBMP("Texturas/sky.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();
	text2.LoadTGA("Texturas/pasto.tga");
	text2.BuildGLTexture();
	text2.ReleaseImage();

	//model1._3dsLoad("kitt.3ds");

	objCamera.Position_Camera(0, -2.0f, 5, 0, -2.0f, 0, 0, 1, 0);
}
void taza(void) {
			glTranslatef(0, -6, 0);//nivel de pasto
			fig2.cono(-5,2,10,0); //taza
			glTranslatef(2,-0.1,0);//comienzo de la oreja
			fig2.prisma(0.2, 1, 0.2, 0);//oreja recta horizontal
			glTranslatef(0.5,-0.5,0);//mover oreja
			fig2.prisma(2,0.15,0.2,0);//oreja recha vetical
			glTranslatef(-0.8,-1.1,0);//mover oreja
			glRotatef(40, 0, 0, 1);//rotar oreja
			fig2.prisma(0.2, 2, 0.2, 0);//oreja en diagoal
}
void tetera(void) {
		glTranslatef(0, -2,0);//nivel de pasto
		glScalef(0.5, 2.5, 0.5);
		glutSolidTeapot(4);
}
void pasto(void) {
		glBindTexture(GL_TEXTURE_2D, text2.GLindex);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex3f(-90, -10, -78);
			glTexCoord2f(1, 0); glVertex3f(-90, -10, 78);
			glTexCoord2f(1, 1); glVertex3f(90, -10, 78);
			glTexCoord2f(0, 1); glVertex3f(90, -10, -78);
		glEnd();
}
void display(void) { //se crea la funcion donde se dibuja todo
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//Limpiamos pantalla y Depth Buffer
	glLoadIdentity();
	glPushMatrix();
		glRotatef(g_lookupdown, 1.0f, 0, 0);
		//camara sintetica
		gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
					objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
					objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);
		glPushMatrix();
			//Creamos Cielo
			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(0, 60, 0);
				fig1.skybox(180.0, 150.0, 150.0, text1.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();
			glPushMatrix();
				glPushMatrix();//Creamos pasto
					pasto();
				glPopMatrix();

				glPushMatrix();//Creacion del juego mecanico
					glPushMatrix();//creamos tetera
						tetera();
					glPopMatrix();
					glTranslatef(10, 0, 0);
					glPushMatrix();//creamos taza1
					glRotatef(angulotazas+10,0,1,0);
						taza();
					glPopMatrix();
					glTranslatef(-20, 0, 0);
					glPushMatrix();//creamos taza2
					glRotatef(angulotazas + 20, 0, 1, 0);
						taza();
					glPopMatrix();
					glTranslatef(10, 0, 10);
					glPushMatrix();//creamos taza3
					glRotatef(angulotazas + 15, 0, 1, 0);
						taza();
					glPopMatrix();
					glTranslatef(0, 0, -20);
					glPushMatrix();//creamos taza4
					glRotatef(angulotazas + 12, 0, 1, 0);
						taza();
					glPopMatrix();
					glTranslatef(10, 0, 0);
					glPushMatrix();//creamos taza5
					glRotatef(angulotazas + 18, 0, 1, 0);
						taza();
					glPopMatrix();
					glTranslatef(0, 0, 20);
					glPushMatrix();//creamos taza6
					glRotatef(angulotazas + 16, 0, 1, 0);
						taza();
					glPopMatrix();
					glTranslatef(-20, 0, 0);
					glPushMatrix();//creamos taza7
					glRotatef(angulotazas + 14, 0, 1, 0);
						taza();
					glPopMatrix();
					glTranslatef(0, 0, -20);
					glPushMatrix();//creamos taza8
					glRotatef(angulotazas + 17, 0, 1, 0);
					taza();
					glPopMatrix();
				glPopMatrix();

			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}
void animacion() {
	//Animacion de tazas
	glutPostRedisplay();
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
	//TIPO DE VISTA
	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 170.0);
	
	glMatrixMode(GL_MODELVIEW);	// Seleccionamos Modelview Matrix
	glLoadIdentity();
	
}
void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'w':   //Movimientos de camara
	case 'W':
		objCamera.Move_Camera(CAMERASPEED + 0.2);
		break;

	case 's':
	case 'S':
		objCamera.Move_Camera(-(CAMERASPEED + 0.2));
		break;

	case 'a':
	case 'A':
		objCamera.Strafe_Camera(-(CAMERASPEED + 0.3));
		break;
	case 'd':
	case 'D':
		objCamera.Strafe_Camera(CAMERASPEED + 0.3);
		break;
	case 27: exit(0);
		break;
	}
	glutPostRedisplay();
}
void arrow_keys(int a_keys, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)
{
	switch (a_keys){
	case GLUT_KEY_PAGE_UP: //presionamos la tecla de avpag
		objCamera.UpDown_Camera(CAMERASPEED);
		break;
	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);//pesionamos tecla de repag
		break;
	case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;
	case GLUT_KEY_DOWN:     // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;
	case GLUT_KEY_LEFT:	//Presionamos tecla izq
		objCamera.Rotate_View(-CAMERASPEED);
		break;
	case GLUT_KEY_RIGHT: //Presionamos tecla de la derecha
		objCamera.Rotate_View(CAMERASPEED);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
int main(int argc, char** argv) //Funcion principal
{
	glutInit(&argc, argv);//inicializamos OpenGL
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); //Modo Display (Colores RGB y Alpha | Buffer Sencillo)
	glutInitWindowSize(1500, 1000); //Tamaño de la Ventana
	glutInitWindowPosition(0, 0);//Posicion de la Ventana
	glutCreateWindow("La feria");//Nombre de la Ventana
	//glutFullScreen();//Ventana completa
	InitGL();//parametros iniciales de la aplicacion
	glutDisplayFunc(display);//Indicamos a Glut funcion de dibujo
	glutReshapeFunc(reshape);//Indicamos a Glut funcion en caso de cambio de tamaño
	glutKeyboardFunc(keyboard);//Indicamos a Glut funcion de manejo de teclado
	glutSpecialFunc(arrow_keys);//Indicamos a Glut funcion de manejo de flechas
	glutIdleFunc(animacion);//Indicamos el amnejo de animacion
	//PlaySound(TEXT("Crash Bandicoot 1 Theme.wav"), NULL, SND_LOOP || SND_SYNC);//configuracion de musica
	glutMainLoop();//Hace un ciclo del Main
	return 0;
}