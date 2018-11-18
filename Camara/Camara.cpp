/**
*  Camara.cpp
*
*  Manejo de la camara en OpenGL
*
*  @author:   rvivo@upv.es
*  @version:  v1.0 Oct,2018
*  @require:  freeglut, utilidades
*
**/

#define PROYECTO "ISGI::S4E01::Camara"

#include <iostream>
#include <Utilidades.h>

using namespace std;

void init()
{
	// Configurar el motor de render
	glClearColor(0, 0, 0.3, 1);
	glEnable(GL_DEPTH_TEST);

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Seleccionar la MODELVIEW
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Situar y orientar la camara: punto de vista, punto de interes, vertical
	gluLookAt(3, 3, 4, 0, 0, 0, 0, 1, 0);

	ejes();

	// Tetera roja
	glPushMatrix();
	glTranslatef(0, 0, 0.5);
	glColor3f(1, 0, 0);
	glutSolidTeapot(0.5);
	glColor3f(1, 1, 1);
	glutWireTeapot(0.51);
	glPopMatrix();

	// Tetera verde
	glPushMatrix();
	glTranslatef(0, 0, -0.4);
	glColor3f(0, 1, 0);
	glutSolidTeapot(0.5);
	glColor3f(1, 1, 1);
	glutWireTeapot(0.51);
	glPopMatrix();

	glFlush();
}

void reshape(GLint w, GLint h)
{
	// Toda el area como marco
	glViewport(0, 0, w, h);

	// Razon de aspecto
	float ra = float(w) / float(h);

	// Matriz de la proyeccion

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Camara ortografica con isometria
	//if(ra>1) glOrtho(-2*ra, 2*ra, -2, 2, -2, 2);
	//else glOrtho(-2, 2, -2 / ra, 2 / ra, -2, 2);

	// Camara perspectiva
	gluPerspective(20, ra, 0.2, 10);
}

void main(int argc, char** argv)
{
	// Initializations
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow(PROYECTO);
	init();

	// Callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	cout << PROYECTO << " en marcha" << endl;

	// Event loop
	glutMainLoop();
}
