/**************************Clase principal***************************************AGRADECIMIENTOS A:*******************************
**************************Facultad de Ingeneria*********************************Ing. Luis Sergio Valencia Castro*****************
*************************Autores: Sandoval Juarez Tania**************************Héctor Alejandro Martínez Garduño***************
*************************         Gomez de la Cruz Luis Octavio******************************************************************
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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;

//Solo para Visual Studio 2015 o mayor
#if (_MSC_VER >= 1900)
#   pragma comment( lib, "legacy_stdio_definitions.lib" )
#endif

//KEYFRAMES
float posx = -50;
float posy = 40;
float posz = 0;
float giroaguila = 0;
bool inicioanimacion = true;
#define MAX_FRAMES 9
int i_max_steps = 90;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ
	float giroaguila;
	float giroaguilainc;

}FRAME;
FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 9;//cuantos datos introduciremos
bool play = false;
int playIndex = 0;
bool time = true;

//Atributos
GLfloat Ambient[] = { 1,1,1,1 };
GLfloat Diffuse[] = { 1,1,1,1 };// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW)
CCamera objCamera;
float Velocidad = 0.0;
int angulotazas1 = 25.0;
int angulotazas2 = 25.0;
int angulotazas3 = 25.0;
int angulotazas4 = 25.0;
int angulotazas5 = 25.0;
int angulotazas6 = 25.0;
int angulotazas7 = 25.0;
int angulotazas8 = 25.0;
int angulotetera = 25.0;

//Figuras
CFiguras fig0;//DIA
CFiguras fig1;//NOCHE caja del mundo cielo
CFiguras fig2;//Taza
CFiguras fig3;//tetera
CFiguras fig4;//platos
CFiguras fig5;//camino
CFiguras fig6;//techo cielo dia
CFiguras fig7;//nubes noche
CFiguras fig8;//tienda
CFiguras fig9;//medusa
CFiguras fig10;//arbolreal

//Texturas
CTexture text0;//DIA
CTexture text1;//NOCHE del cielo con llanuras
CTexture text2;//PAsto
CTexture text3;//plato
CTexture text4;//camino
CTexture text5;//marmol
CTexture text6;//techo nubes dia
CTexture text7;//nubesnoche
CTexture text8;//tienda
CTexture text9;//tienda
CTexture text10;//pared
CTexture text11;//baño
CTexture text12;//medusa madera
CTexture text13;//carrito
CTexture text14;//carrito2
CTexture text15;//arbol real
CTexture text16;//arbusto

//Modelos
CModel model1;//arbol
CModel model2;//asiento
CModel model3;//aguila
CModel model4;//trash

//Metodos
void saveFrame(void)
{

	printf("frameindex %d\n", FrameIndex);

	KeyFrame[FrameIndex].posX = posx;
	KeyFrame[FrameIndex].posY = posy;
	KeyFrame[FrameIndex].posZ = posz;

	KeyFrame[FrameIndex].giroaguila = giroaguila;

	FrameIndex++;
}

void resetElements(void)
{
	posx = KeyFrame[0].posX;
	posy = KeyFrame[0].posY;
	posz = KeyFrame[0].posZ;

	giroaguila = KeyFrame[0].giroaguila;


}
void interpolation(void)
{
	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;
	KeyFrame[playIndex].giroaguilainc = (KeyFrame[playIndex + 1].giroaguila - KeyFrame[playIndex].giroaguila) / i_max_steps;

}

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

	text0.LoadBMP("Texturas/cielo.bmp");
	text0.BuildGLTexture();
	text0.ReleaseImage();
	text1.LoadBMP("Texturas/sky.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();
	text2.LoadTGA("Texturas/pasto.tga");
	text2.BuildGLTexture();
	text2.ReleaseImage();
	text3.LoadBMP("Texturas/plato.bmp");
	text3.BuildGLTexture();
	text3.ReleaseImage();
	text4.LoadBMP("Texturas/camino.bmp");
	text4.BuildGLTexture();
	text4.ReleaseImage();
	text5.LoadBMP("Texturas/marmol.bmp");
	text5.BuildGLTexture();
	text5.ReleaseImage();
	text6.LoadTGA("Texturas/nube.tga");
	text6.BuildGLTexture();
	text6.ReleaseImage();
	text7.LoadBMP("Texturas/nubenoche.bmp");
	text7.BuildGLTexture();
	text7.ReleaseImage();
	text8.LoadBMP("Texturas/tienda7.bmp");
	text8.BuildGLTexture();
	text8.ReleaseImage();
	text9.LoadBMP("Texturas/tienda8.bmp");
	text9.BuildGLTexture();
	text9.ReleaseImage();
	text10.LoadBMP("Texturas/pared.bmp");
	text10.BuildGLTexture();
	text10.ReleaseImage();
	text11.LoadTGA("Texturas/baño.tga");
	text11.BuildGLTexture();
	text11.ReleaseImage();
	text12.LoadTGA("Texturas/madera.tga");
	text12.BuildGLTexture();
	text12.ReleaseImage();
	text13.LoadTGA("Texturas/carro.tga");
	text13.BuildGLTexture();
	text13.ReleaseImage();
	text14.LoadTGA("Texturas/metal.tga");
	text14.BuildGLTexture();
	text14.ReleaseImage();
	text15.LoadTGA("Texturas/tree01.tga");
	text15.BuildGLTexture();
	text15.ReleaseImage();
	text16.LoadTGA("Texturas/shrub.tga");
	text16.BuildGLTexture();
	text16.ReleaseImage();

	model1._3dsLoad("Modelos/firtree3.3ds");
	model2._3dsLoad("Modelos/garden.3ds");
	model3._3dsLoad("Modelos/eagle.3ds");
	//model4._3dsLoad("Modelos/trash.3ds");

	KeyFrame[0].posX = -50;
	KeyFrame[0].posY = 40;
	KeyFrame[0].posZ = 0;
	KeyFrame[0].giroaguila = 0;//bien
	KeyFrame[1].posX = -50;
	KeyFrame[1].posY = 35;
	KeyFrame[1].posZ = 50;
	KeyFrame[1].giroaguila = 0;//mal
	KeyFrame[2].posX = 0;
	KeyFrame[2].posY = 30;
	KeyFrame[2].posZ = 50;
	KeyFrame[2].giroaguila = 0;//mal
	KeyFrame[3].posX = 50;
	KeyFrame[3].posY = 35;
	KeyFrame[3].posZ = 50;
	KeyFrame[3].giroaguila = 0;
	KeyFrame[4].posX = 50;
	KeyFrame[4].posY = 40;
	KeyFrame[4].posZ = 0;
	KeyFrame[4].giroaguila = 0;
	KeyFrame[5].posX = 50;
	KeyFrame[5].posY = 45;
	KeyFrame[5].posZ = -50;
	KeyFrame[5].giroaguila = 0;
	KeyFrame[6].posX = 0;
	KeyFrame[6].posY = 40;
	KeyFrame[6].posZ = -50;
	KeyFrame[6].giroaguila =0 ;
	KeyFrame[7].posX = -50;
	KeyFrame[7].posY = 35;
	KeyFrame[7].posZ = -50;
	KeyFrame[7].giroaguila = 0;
	KeyFrame[8].posX = -50;
	KeyFrame[8].posY = 40;
	KeyFrame[8].posZ = 0;
	KeyFrame[8].giroaguila = 0;


	objCamera.Position_Camera(0, -2.0f, 5, 0, -2.0f, 0, 0, 1, 0);
}
void soporteMedusa(void) {
	glPushMatrix();

	//----------------1

	glPushMatrix();
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, 1.75, 0);
	glRotatef(45, 0, 0, 1);
	fig9.prisma(4.5, 0.5, 0.5, text12.GLindex);
	glRotatef(90, 0, 0, 1);
	fig9.prisma(4.5, 0.5, 0.5, text12.GLindex);
	glPopMatrix();

	fig9.prisma(4, 0.5, 0.5, text12.GLindex);
	glTranslatef(0, 3.5, 0);
	fig9.prisma(4, 0.5, 0.5, text12.GLindex);

	glTranslatef(1.75, -1.75, 0);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	fig9.prisma(4, 0.5, 0.5, text12.GLindex);
	glPopMatrix();

	glTranslatef(-3.5, 0, 0);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	fig9.prisma(4, 0.5, 0.5, text12.GLindex);
	glPopMatrix();

	glPopMatrix();

	//----------------2

	glPushMatrix();
	glTranslatef(0, 0, -3.5);
	glPushMatrix();
	glTranslatef(0, 1.75, 0);
	glRotatef(45, 0, 0, 1);
	fig9.prisma(4.5, 0.5, 0.5, text12.GLindex);
	glRotatef(90, 0, 0, 1);
	fig9.prisma(4.5, 0.5, 0.5, text12.GLindex);
	glPopMatrix();

	fig9.prisma(4, 0.5, 0.5, text12.GLindex);
	glTranslatef(0, 3.5, 0);
	fig9.prisma(4, 0.5, 0.5, text12.GLindex);

	glTranslatef(1.75, -1.75, 0);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	fig9.prisma(4, 0.5, 0.5, text12.GLindex);
	glPopMatrix();

	glTranslatef(-3.5, 0, 0);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	fig9.prisma(4, 0.5, 0.5, text12.GLindex);
	glPopMatrix();

	glPopMatrix();

	//-----------------3


	glPushMatrix();
	glTranslatef(-1.75, 0, -1.75);
	glRotatef(90, 0, 1, 0);

	glPushMatrix();
	glTranslatef(0, 1.75, 0);
	glRotatef(45, 0, 0, 1);
	fig9.prisma(4.5, 0.5, 0.5, text12.GLindex);
	glRotatef(90, 0, 0, 1);
	fig9.prisma(4.5, 0.5, 0.5, text12.GLindex);
	glPopMatrix();

	fig9.prisma(4, 0.5, 0.5, text12.GLindex);
	glTranslatef(0, 3.5, 0);
	fig9.prisma(4, 0.5, 0.5, text12.GLindex);

	glTranslatef(1.75, -1.75, 0);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	fig9.prisma(4, 0.5, 0.5, text12.GLindex);
	glPopMatrix();

	glTranslatef(-3.5, 0, 0);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	fig9.prisma(4, 0.5, 0.5, text12.GLindex);
	glPopMatrix();

	glPopMatrix();

	//-------------4

	glPushMatrix();

	glTranslatef(1.75, 0, -1.75);
	glRotatef(90, 0, 1, 0);

	glPushMatrix();
	glTranslatef(0, 1.75, 0);
	glRotatef(45, 0, 0, 1);
	fig9.prisma(4.5, 0.5, 0.5, text12.GLindex);
	glRotatef(90, 0, 0, 1);
	fig9.prisma(4.5, 0.5, 0.5, text12.GLindex);
	glPopMatrix();

	fig9.prisma(4, 0.5, 0.5, text12.GLindex);
	glTranslatef(0, 3.5, 0);
	fig9.prisma(4, 0.5, 0.5, text12.GLindex);

	glTranslatef(1.75, -1.75, 0);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	fig9.prisma(4, 0.5, 0.5, text12.GLindex);
	glPopMatrix();

	glTranslatef(-3.5, 0, 0);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	fig9.prisma(4, 0.5, 0.5, text12.GLindex);
	glPopMatrix();

	glPopMatrix();



	glPopMatrix();
}

void translateMedusa(float x, float y, float z) {
	glTranslatef(x * 4, y * 4, z * 4);
}

void columnasMedusa(int length) {

	glPushMatrix();
	soporteMedusa();
	for (size_t i = 0; i < length; i++)
	{
		glPushMatrix();
		glTranslated(0, i * 4, 0);
		soporteMedusa();
		glPopMatrix();

	}

	glPopMatrix();
}

void estructuraMedusaTotal(void) {

	//Push General de la función
	glPushMatrix();

	columnasMedusa(5);
	translateMedusa(1, 0, 0);
	columnasMedusa(5);
	translateMedusa(2, 0, 0);
	columnasMedusa(5);
	translateMedusa(2, 0, 0);
	columnasMedusa(6);

	//Primera curva

	translateMedusa(1, 0, -1);
	columnasMedusa(7);
	translateMedusa(1, 0, -1);
	columnasMedusa(8);

	translateMedusa(0, 0, -2);
	columnasMedusa(9);
	translateMedusa(0, 0, -2);
	columnasMedusa(10);
	translateMedusa(0, 0, -2);
	columnasMedusa(11);
	translateMedusa(0, 0, -2);
	columnasMedusa(12);
	translateMedusa(0, 0, -2);
	columnasMedusa(13);
	translateMedusa(0, 0, -2);
	columnasMedusa(14);
	translateMedusa(0, 0, -2);
	columnasMedusa(15);
	translateMedusa(0, 0, -2);
	columnasMedusa(16);

	//Segunda Curva

	translateMedusa(-1, 0, -1);
	columnasMedusa(17);
	translateMedusa(-1, 0, -1);
	columnasMedusa(17);
	translateMedusa(-1, 0, 0);
	columnasMedusa(17);
	translateMedusa(-1, 0, 0);
	columnasMedusa(17);
	translateMedusa(-1, 0, 1);
	columnasMedusa(17);

	translateMedusa(0, 0, 2);
	columnasMedusa(16);
	translateMedusa(0, 0, 2);
	columnasMedusa(14);
	translateMedusa(0, 0, 2);
	columnasMedusa(13);
	translateMedusa(0, 0, 2);
	columnasMedusa(12);
	translateMedusa(0, 0, 2);
	columnasMedusa(10);
	translateMedusa(0, 0, 2);
	columnasMedusa(9);

	//Tercera Curva
	translateMedusa(-1, 0, 1);
	columnasMedusa(7);
	translateMedusa(-1, 0, 1);
	columnasMedusa(7);
	translateMedusa(-1, 0, 0);
	columnasMedusa(7);
	translateMedusa(-1, 0, 0);
	columnasMedusa(7);//
	translateMedusa(-1, 0, -1);
	columnasMedusa(7);
	translateMedusa(-1, 0, -1);
	columnasMedusa(7);

	translateMedusa(0, 0, -2);
	columnasMedusa(6);
	translateMedusa(0, 0, -2);
	columnasMedusa(5);
	translateMedusa(0, 0, -2);
	columnasMedusa(4);
	translateMedusa(0, 0, -2);
	columnasMedusa(3);
	translateMedusa(0, 0, -2);
	columnasMedusa(3);
	translateMedusa(0, 0, -2);
	columnasMedusa(3);
	translateMedusa(0, 0, -2);
	columnasMedusa(3);

	//Cuarta Curva
	translateMedusa(-1, 0, -1);
	columnasMedusa(4);
	translateMedusa(-1, 0, -1);
	columnasMedusa(5);
	translateMedusa(-1, 0, 0);
	columnasMedusa(7);
	translateMedusa(-1, 0, 0);
	columnasMedusa(9);
	translateMedusa(-1, 0, 1);
	columnasMedusa(11);
	translateMedusa(-1, 0, 1);
	columnasMedusa(13);

	translateMedusa(0, 0, 2);
	columnasMedusa(15);
	translateMedusa(0, 0, 2);
	columnasMedusa(17);
	translateMedusa(0, 0, 2);
	columnasMedusa(19);
	translateMedusa(0, 0, 2);
	columnasMedusa(19);
	translateMedusa(0, 0, 2);
	columnasMedusa(17);
	translateMedusa(0, 0, 2);
	columnasMedusa(15);
	translateMedusa(0, 0, 2);
	columnasMedusa(13);
	translateMedusa(0, 0, 2);
	columnasMedusa(11);
	translateMedusa(0, 0, 2);
	columnasMedusa(9);

	//Quinta curva
	translateMedusa(-1, 0, 1);
	columnasMedusa(7);
	translateMedusa(-1, 0, 1);
	columnasMedusa(7);
	translateMedusa(-1, 0, 0);
	columnasMedusa(6);
	translateMedusa(-1, 0, -1);
	columnasMedusa(5);
	translateMedusa(-1, 0, -1);
	columnasMedusa(4);

	translateMedusa(0, 0, -2);
	columnasMedusa(4);
	translateMedusa(0, 0, -2);
	columnasMedusa(5);
	translateMedusa(0, 0, -2);
	columnasMedusa(6);
	translateMedusa(0, 0, -2);
	columnasMedusa(7);
	translateMedusa(0, 0, -2);
	columnasMedusa(8);
	translateMedusa(0, 0, -2);
	columnasMedusa(9);
	translateMedusa(0, 0, -2);
	columnasMedusa(10);
	translateMedusa(0, 0, -2);
	columnasMedusa(11);
	translateMedusa(0, 0, -2);
	columnasMedusa(12);

	//SextaCurva
	translateMedusa(-1, 0, -2);
	columnasMedusa(13);
	translateMedusa(-2, 0, -2);
	columnasMedusa(13);
	translateMedusa(-2, 0, 0);
	columnasMedusa(13);
	translateMedusa(-2, 0, 0);
	columnasMedusa(13);
	translateMedusa(-2, 0, 2);
	columnasMedusa(13);
	translateMedusa(-1, 0, 2);
	columnasMedusa(13);

	translateMedusa(0, 0, 2);
	columnasMedusa(12);
	translateMedusa(0, 0, 2);
	columnasMedusa(10);
	translateMedusa(0, 0, 2);
	columnasMedusa(9);
	translateMedusa(0, 0, 2);
	columnasMedusa(8);
	translateMedusa(0, 0, 2);
	columnasMedusa(7);
	translateMedusa(0, 0, 2);
	columnasMedusa(6);
	translateMedusa(0, 0, 2);
	columnasMedusa(5);
	translateMedusa(0, 0, 2);
	columnasMedusa(5);
	translateMedusa(0, 0, 2);
	columnasMedusa(5);
	translateMedusa(0, 0, 2);
	columnasMedusa(5);

	//Septima Curva
	translateMedusa(1, 0, 2);
	columnasMedusa(5);
	translateMedusa(2, 0, 1);
	columnasMedusa(5);
	translateMedusa(2, 0, 1);
	columnasMedusa(5);
	translateMedusa(2, 0, 1);
	columnasMedusa(5);
	translateMedusa(2, 0, 1);
	columnasMedusa(5);
	translateMedusa(2, 0, 0);
	columnasMedusa(5);
	translateMedusa(2, 0, -1);
	columnasMedusa(5);
	translateMedusa(1, 0, -1);
	columnasMedusa(5);
	translateMedusa(1, 0, -1);
	columnasMedusa(5);
	translateMedusa(1, 0, -1);
	columnasMedusa(5);
	translateMedusa(1, 0, -1);
	columnasMedusa(5);

	translateMedusa(2, 0, 0);
	columnasMedusa(5);
	translateMedusa(2, 0, 0);
	columnasMedusa(5);
	translateMedusa(2, 0, 0);
	columnasMedusa(5);

	//Fin del circuito Medusa

	//Pop General de la función
	glPopMatrix();
}


void carroMedusa(void) {
	glPushMatrix();
	//Carro Medusa
	glColor3f(1, 1, 1);
	fig9.prisma(4, 0.5, 3, text14.GLindex);
	glTranslatef(1.25, 1.25, 0);
	fig9.prisma(1.5, 2, 3, text14.GLindex);
	glTranslatef(-1, -0.25, 0);
	glColor3f(1, 0, 0);
	fig9.prisma(0.5, 1.5, 2, NULL);
	glTranslatef(-0.625, -0.5, 0);
	fig9.prisma(0.75, 0.5, 2, NULL);
	glColor3f(1, 1, 1);
	glTranslatef(-1.375, 0, 0);
	fig9.prisma(0.5, 1.5, 3, text13.GLindex);

	glPopMatrix();

}

void arregloCarrosMedusa(void) {
	for (size_t i = 0; i < 8; i++)
	{
		carroMedusa();
		glPushMatrix();
		glTranslatef(i * 4, 0, 0);
		carroMedusa();
		glPopMatrix();

	}
}
void arbol()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glBindTexture(GL_TEXTURE_2D, text15.GLindex);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.5, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(2.5, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(2.5, 10.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.5, 10.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.5, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(2.5, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(2.5, 10.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.5, 10.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.5, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(2.5, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(2.5, 10.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.5, 10.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.5, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(2.5, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(2.5, 10.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.5, 10.0, 0.0);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	//glDisable(GL_BLEND);        // Turn Blending Off
	//glEnable(GL_DEPTH_TEST);    // Turn Depth Testing On
	glEnable(GL_LIGHTING);

	glPopMatrix();
}
void arbusto()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_ALPHA_TEST);
	//glDisable(GL_DEPTH_TEST);   // Turn Depth Testing Off
	glAlphaFunc(GL_GREATER, 0.1);
	//glEnable(GL_BLEND);     // Turn Blending On
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, text16.GLindex);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.5, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.5, 3.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.5, 3.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.5, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.5, 3.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.5, 3.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.5, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.5, 3.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.5, 3.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.5, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.5, 3.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.5, 3.0, 0.0);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	//glDisable(GL_BLEND);        // Turn Blending Off
	//glEnable(GL_DEPTH_TEST);    // Turn Depth Testing On
	glEnable(GL_LIGHTING);

	glPopMatrix();
}
void camino(void) {
	glPushMatrix();
		glScalef(10, 0.1, 10);
		glDisable(GL_LIGHTING);
		fig5.prisma2(text4.GLindex, 0);
		glEnable(GL_LIGHTING);
	glPopMatrix();
}
void iniciocamino(void) {
	glPushMatrix();
	glTranslatef(0, -9.9, 70);
	glScalef(10, 0.1, 10);
	glDisable(GL_LIGHTING);
	fig5.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}
void tienda(void) {
	//seven
	glPushMatrix();
		glTranslatef(35, 2, 30);
		glRotatef(90,1,0,0);
		glScalef(20, 10, 25);
		glDisable(GL_LIGHTING);
		fig8.prisma2(text8.GLindex, text10.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();
	//oxxo
	glPushMatrix();
		glTranslatef(-15, 2, 50);
		glRotatef(90, 1, 0, 0);
		glRotatef(180,0,0,1);
		glScalef(20, 10, 25);
		glDisable(GL_LIGHTING);
		fig8.prisma2(text9.GLindex, text10.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();
	//BAÑO
	glPushMatrix();
		glTranslatef(10, -3, 10);
		glRotatef(90, 1, 0, 0);
		glRotatef(90, 0, 0, 1);
		glScalef(15, 10, 15);
		glDisable(GL_LIGHTING);
		fig8.prisma2(text11.GLindex, text10.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

}
void asiento(void) {
	glPushMatrix();
		glTranslatef(5, -10, -25);
		glRotatef(270, 0, 1, 0);
		glScalef(0.02, 0.02, 0.02);
		model2.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-5, -10, 20);
		glRotatef(90, 0, 1, 0);
		glScalef(0.02, 0.02, 0.02);
		model2.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(20, -10, 35);
		glRotatef(0, 0, 1, 0);
		glScalef(0.02, 0.02, 0.02);
		model2.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(-30, -10, 45);
		glRotatef(180, 0, 1, 0);
		glScalef(0.02, 0.02, 0.02);
		model2.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glEnable(GL_COLOR_MATERIAL);
}
void arboles(void) {//tematicos
	glColor3f(0, 1, 1);
	glPushMatrix();
		glDisable(GL_COLOR_MATERIAL);
		glTranslatef(-25, -10, -45);
		glScalef(5, 5, 5);
		model1.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(25, -10, -35);
		glScalef(5, 5, 5);
		model1.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(30, -10, -60);
		glScalef(5, 5, 5);
		model1.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();

		glPushMatrix();//aguka
			glTranslatef(posx, posy, posz);
			glScalef(5, 5, 5);
			model3.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();
	glColor3f(1, 1, 1);
}
void taza(void) {
			glPushMatrix();
				glTranslatef(0, -9.7, 0);
				fig2.cono(0,3,50,text3.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0, -6, 0);//nivel de pasto
				fig2.cono(-5,2,50,text5.GLindex); //taza
				glTranslatef(2,-0.1,0);//comienzo de la oreja
				fig2.prisma(0.2, 1, 0.2, text5.GLindex);//oreja recta horizontal
				glTranslatef(0.5,-0.5,0);//mover orejaa
				fig2.prisma(2,0.15,0.2, text5.GLindex);//oreja recha vetical
				glTranslatef(-0.8,-1.1,0);//mover oreja
				glRotatef(40, 0, 0, 1);//rotar oreja
				fig2.prisma(0.2, 2, 0.2, text5.GLindex);//oreja en diagoal
			glPopMatrix();
}
void tetera(void) {
	
	glPushMatrix();
			glTranslatef(0, -10., 0);
			fig2.cono(0.1, 18, 100, text5.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, -4,0);//nivel de pasto
			glScalef(0.5, 2.5, 0.5);
			fig3.prisma2(text5.GLindex, text5.GLindex);
			glutSolidTeapot(3);
		glPopMatrix();
}
void pasto(void) {
	glPushMatrix();
	glDisable(GL_LIGHTING);
		glBindTexture(GL_TEXTURE_2D, text2.GLindex);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex3f(-90, -10.5, -78);
			glTexCoord2f(1, 0); glVertex3f(-90, -10.5, 78);
			glTexCoord2f(1, 1); glVertex3f(90, -10.5, 78);
			glTexCoord2f(0, 1); glVertex3f(90, -10.5, -78);
		glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();
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
		if (time == true) {
			//DIA
			glPushMatrix();//Creamos caja Cielo
			glDisable(GL_LIGHTING);
			glTranslatef(0, 60, 0);
			fig0.skybox(180.0, 150.0, 150.0, text0.GLindex);
			glEnable(GL_LIGHTING);
			glPopMatrix();//Fin de caja cielo

			glPushMatrix();// inicio techo cielo
			glTranslatef(0, 130, 0.0);
			glScalef(200, .1, 200);
			fig6.prisma2(text6.GLindex, text6.GLindex);
			glPopMatrix();//fin techo cielo
		}
		else {
			//NOCHE
			glPushMatrix();//Creamos caja Cielo
			//glDisable(GL_LIGHTING);
			glTranslatef(0, 60, 0);
			glColor3f(1, 1, 1);
			fig1.skybox(180.0, 150.0, 150.0, text1.GLindex);
			//glEnable(GL_LIGHTING);
			glColor3f(1, 1, 1);
			glPopMatrix();//Fin de caja cielo

			glPushMatrix();// inicio techo cielo
				glTranslatef(0, 130, 0.0);
				glScalef(200, .1, 200);
				fig7.prisma2(text7.GLindex, text7.GLindex);
			glPopMatrix();//fin techo cielo
		}
			
				glPushMatrix();//Creamos pasto
					pasto();
				glPopMatrix();//Fin de pasto

				glPushMatrix();//Creacion del juego mecanico
				glTranslatef(0,0,-55);
				glRotatef(angulotetera = ((angulotetera + 2) % 360), 0, 1, 0);
					glPushMatrix();//creamos tetera
						tetera();
					glPopMatrix();
				
					glTranslatef(10, 0, 0);
					glPushMatrix();//creamos taza1
					glRotatef(angulotazas1 = ((angulotazas1 +5) % 360) ,0,1,0);
						taza();
					glutPostRedisplay();
					glPopMatrix();
					
					glTranslatef(-20, 0, 0);
					glPushMatrix();//creamos taza2
					glRotatef(angulotazas2 = ((angulotazas2 - 5) % 360), 0, 1, 0);
					taza();
					glPopMatrix();
					
					glTranslatef(10, 0, 10);
					glPushMatrix();//creamos taza3
					glRotatef(angulotazas3 = ((angulotazas3 - 10) % 360), 0, 1, 0);
					taza();
					glPopMatrix();
					
					glTranslatef(0, 0, -20);
					glPushMatrix();//creamos taza4
					glRotatef(angulotazas4 = ((angulotazas4 + 5) % 360), 0, 1, 0);
					taza();
					glPopMatrix();
					
					glTranslatef(10, 0, 0);
					glPushMatrix();//creamos taza5
					glRotatef(angulotazas4 = ((angulotazas4 + 10) % 360), 0, 1, 0);
						taza();
					glPopMatrix();
					
					glTranslatef(0, 0, 20);
					glPushMatrix();//creamos taza6
					glRotatef(angulotazas4 = ((angulotazas4 - 5) % 360), 0, 1, 0);
						taza();
					glPopMatrix();
					
					glTranslatef(-20, 0, 0);
					glPushMatrix();//creamos taza7
					glRotatef(angulotazas4 = ((angulotazas4 - 10) % 360), 0, 1, 0);
						taza();
					glPopMatrix();
					
					glTranslatef(0, 0, -20);
					glPushMatrix();//creamos taza8
					glRotatef(angulotazas4 = ((angulotazas4 + 5) % 360), 0, 1, 0);
					taza();
					glPopMatrix();
				glPopMatrix();//fin de creacion de juego mecanico

				glPushMatrix();//ARBOLES
				arboles();
				glPopMatrix();

				glPushMatrix();//camino
					iniciocamino();//1
					glTranslatef(0, -9.9, 60);
					camino();//2
					glTranslatef(0, 0, -10);
					camino();//3
					glTranslatef(0, 0, -10);
					camino();//4
						//DESVIACION izq
						glPushMatrix();
							glTranslatef(-10,0,0);
							camino();//1.4
							glTranslatef(-10, 0, 0);
							camino();//1.1.4
							glTranslatef(-10, 0, 0);
							camino();//1.1.4
								 //DESVIACION IZQ RECTA
									glPushMatrix();
										glTranslatef(0, 0, -10);
										camino();//
										glTranslatef(0, 0, 10);
										camino();//
										glTranslatef(0, 0, 3);
										camino();//
									glPopMatrix();
							glTranslatef(-10, 0, 0);
							camino();//1.1.1.4
							glTranslatef(-10, 0, 0);
							camino();//1.1.1.1.4
							glTranslatef(-10, 0, 0);
							camino();//1.1.1.1.1.4
						glPopMatrix();
						//DESVIACION DER
						glPushMatrix();
							glTranslatef(10, 0, 0);
							camino();//4.1
							glTranslatef(10, 0, 0);
							camino();//4.1.1
							glTranslatef(10, 0, 0);
							camino();//4.1.1
							glTranslatef(10, 0, 0);
							camino();//4.1.1.1
							glTranslatef(10, 0, 0);
							camino();//4.1.1.1.1
							glTranslatef(10, 0, 0);
							camino();//4.1.1.1.1.1
								//DESVIACION DERE RECTA
									glTranslatef(0, 0, -20);
									camino();//
									glTranslatef(0, 0, 10);
									camino();//
									glTranslatef(0, 0, 10);
									camino();//
									glTranslatef(0, 0, 10);
									camino();//
									glTranslatef(0, 0, 10);
									camino();//
									glTranslatef(0, 0, 10);
									camino();//
						glPopMatrix();

					glTranslatef(0, 0, -10);
					camino();//5
					glTranslatef(0, 0, -10);
					camino();//6
					glTranslatef(0, 0, -10);
					camino();//7
					glTranslatef(0, 0, -10);
					camino();//8
					glTranslatef(0, 0, -10);
					camino();//9
					glTranslatef(0, 0, -10);
					camino();//10
					glTranslatef(0, 0, -10);
					camino();//11
					glTranslatef(0, 0, -2);
					camino();//12
				glPopMatrix();

				glPushMatrix();
				asiento();
				glPopMatrix();

				glPushMatrix();
				tienda();
				glPopMatrix();

				glEnable(GL_LIGHTING);
				//medusa
				glPushMatrix();
					glTranslatef(-25, -10, 20);
					//glRotatef(90, 0, 1, 0);
					glScalef(.5, .5, .5);
					glPushMatrix();
						glTranslatef(4, 20, -1.75);
						glRotatef(180, 0, 1, 0);
						arregloCarrosMedusa();
					glPopMatrix();
					estructuraMedusaTotal();
				glPopMatrix();

				//arboles
				glPushMatrix();
					glTranslatef(-7, -10,15);
					arbol();
					glTranslatef(0, 0, -4);
					arbol();
					glTranslatef(0, 0, -4);
					arbol();
					glTranslatef(0, 0, -4);
					arbol();
					glTranslatef(0, 0, -4);
					arbol();
					glTranslatef(0, 0, -4);
					arbol();
					glTranslatef(0, 0, -4);
					arbol();
					glTranslatef(0, 0, -4);
					arbol();
					glTranslatef(0, 0, -4);
					arbol();
					glTranslatef(0, 0, -4);
					arbol();
					glTranslatef(0, 0, -4);
					arbol();
					glTranslatef(0, 0, -4);
					arbol();
					glTranslatef(0, 0, -4);
					arbol();
				glPopMatrix();

				//arbustos
				glPushMatrix();
					glTranslatef(7, -10, 35);
					arbusto();
					glTranslatef(0, 0, -4);
					arbusto();
					glTranslatef(0, 0, -4);
					arbusto();
					glTranslatef(0, 0, -4);
					arbusto();
					glTranslatef(0, 0, -4);
					arbusto();
					glTranslatef(0, 0, -20);
					arbusto();
					glTranslatef(0, 0, -4);
					arbusto();
					glTranslatef(0, 0, -4);
					arbusto();
					glTranslatef(0, 0, -4);
					arbusto();
					glTranslatef(0, 0, -4);
					arbusto();
					glTranslatef(0, 0, -4);
					arbusto();
					glTranslatef(0, 0, -4);
					arbusto();
					glTranslatef(0, 0, -4);
					arbusto();
					glTranslatef(0, 0, -4);
					arbusto();
				glPopMatrix();
			
		glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}
void animacion() {
	if (play) {
		if (i_curr_steps >= i_max_steps)
		{
			playIndex++;
			if (playIndex > FrameIndex - 2) {
				printf("termina animacion\m");
				playIndex = 0;
				play = false;
			}
			else {
				i_curr_steps = 0;
				interpolation();
			}
		}
		else {
			posx += KeyFrame[playIndex].incX;
			posy += KeyFrame[playIndex].incY;
			posz += KeyFrame[playIndex].incZ;

			giroaguila += KeyFrame[playIndex].giroaguilainc;
			i_curr_steps++;
		}
	}
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
	case 'h':
	case 'H':
		if (play == false && (FrameIndex>1))
		{

			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
		break;
	case 't':
	case 'T':
		if (time == true) {
			time = false;
		}
		else
			time = true;
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
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); //Modo Display (Colores RGB y Alpha | Buffer Sencillo)
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
	PlaySound(TEXT("circo.wav"), NULL, SND_LOOP || SND_SYNC);//configuracion de musica
	glutMainLoop();//Hace un ciclo del Main
	return 0;
}