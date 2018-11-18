/**
*  prac5.cpp
*
*  Entregable SGI practica 5
*
*  @author:   Akshay Punjabi
*  @require:  freeglut, utilidades
*
**/

#define PROYECTO "Reloj 3D"

#include <iostream>
#include "Utilidades.h"
#include <ctime>

using namespace std;

float eyex = 0;
float eyey = 0;
float eyez = 5;
static GLuint d12x12, estrella, estrellas, aguja;
static GLfloat anglesec, anglemin, anglehours;
// Variables dependientes del tiempo
float alfa = 0;
int h, m, s;
struct tm *newtime;
time_t ltime;


void init()
{
	d12x12 = glGenLists(1);
	glNewList(d12x12, GL_COMPILE);
	glColor3f(0.76, 0.76, 0.76);
	glBegin(GL_LINE_STRIP);
	for (auto i = 0; i <= 12; i++) {
		glVertex3f(cos(i * 2 * PI / 12), sin(i * 2 * PI / 12), 0.0);
	}
	glEnd();
	glColor3f(0.3, 0.3, 0.3);
	glBegin(GL_LINE_STRIP);
	for (auto i = 0; i <= 12; i++) {
		glVertex3f(cos(i * 2 * PI / 12) / 2, sin(i * 2 * PI / 12) / 2, 0.0);
	}
	glEnd();
	glColor3f(0.69, 0.69, 0.69);
	for (auto i = 0; i <= 12; i++) {
		glLineWidth(2.5);
		glBegin(GL_LINES);
		glVertex3f(cos(i * 2 * PI / 12), sin(i * 2 * PI / 12), 0.0);
		glVertex3f(cos(i * 2 * PI / 12) / 2, sin(i * 2 * PI / 12) / 2, 0.0);
		glVertex3f(cos(i * 2 * PI / 12), sin(i * 2 * PI / 12), 0.0);
		glVertex3f(cos((i + 1) * 2 * PI / 12) / 2, sin((i + 1) * 2 * PI / 12) / 2, 0.0);
		glVertex3f(cos(i * 2 * PI / 12), sin(i * 2 * PI / 12), 0.0);
		glVertex3f(cos((i - 1) * 2 * PI / 12) / 2, sin((i - 1) * 2 * PI / 12) / 2, 0.0);
		glVertex3f(cos(i * 2 * PI / 12), sin(i * 2 * PI / 12), 0.0);
		glVertex3f(cos((i + 2) * 2 * PI / 12), sin((i + 2) * 2 * PI / 12), 0.0);
		glEnd();
	}
	glEndList();

	// agujas de reloj
	aguja = glGenLists(1);
	glNewList(aguja, GL_COMPILE);
	glColor3f(1, 1, 1);
	glTranslatef(0, 0.5, 0);
	glutSolidCube(1);
	glEndList();

	estrella = glGenLists(1);
	glNewList(estrella, GL_COMPILE);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= 3; i++) {
		glVertex3f(1.0 * cos(i * (2 * PI / 3) + (PI / 2)), 1.0 * sin(i * (2 * PI / 3) + (PI / 2)), 0.0);
		glVertex3f(0.7 * cos(i * (2 * PI / 3) + (PI / 2)), 0.7 * sin(i * (2 * PI / 3) + (PI / 2)), 0.0);
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= 3; i++) {
		glVertex3f(1.0 * cos(i * (2 * PI / 3) + (3 * PI / 2)), 1.0 * sin(i * (2 * PI / 3) + (3 * PI / 2)), 0.0);
		glVertex3f(0.7 * cos(i * (2 * PI / 3) + (3 * PI / 2)), 0.7 * sin(i * (2 * PI / 3) + (3 * PI / 2)), 0.0);
	}
	glEnd();
	glEndList();

	estrellas = glGenLists(1);
	glNewList(estrellas, GL_COMPILE);
	for (int i = 1; i <= 6; i++) {
		float m = (float)i / 10;
		glColor3f(1 - m, 1 - m, 1 - m);
		glRotatef(30, 0, 1, 0);
		glCallList(estrella);
	}
	glEnd();
	glEndList();

	glEnable(GL_DEPTH_TEST);
}

void display()
{
	time(&ltime); // Get time
	newtime = localtime(&ltime); // Convert to local time

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, 0, 0, 0, 0, 1, 0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	glPushMatrix();
	glCallList(d12x12);
	glPopMatrix();


	// hours
	glPushMatrix();
	glRotatef((30 * newtime->tm_hour) + 0.5 * ( newtime->tm_min + 1), 0, 0, -1);
	glScalef(0.03, 0.48, 0.03);
	glCallList(aguja);
	glPopMatrix();

	// min
	glPushMatrix();
	glRotatef(6 * newtime->tm_min, 0, 0, -1);
	glScalef(0.02,0.7, 0.02);
	glCallList(aguja);
	glPopMatrix();

	// sec
	glPushMatrix();
	glRotatef(6 * newtime->tm_sec, 0, 0, -1);
	glScalef(0.01, 0.9, 0.01);
	glCallList(aguja);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.8, 0.8, 0);
	glScalef(0.08, 0.08, 0);
	glRotatef(alfa, 1, 1, 0);
	glCallList(estrellas);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.8, 0.8, 0);
	glScalef(0.08, 0.08, 0);
	glRotatef(alfa, 1, 1, 0);
	glCallList(estrellas);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.8, -0.8, 0);
	glScalef(0.08, 0.08, 0);
	glRotatef(alfa, 1, 1, 0);
	glCallList(estrellas);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.8, -0.8, 0);
	glScalef(0.08, 0.08, 0);
	glRotatef(alfa, 1, 1, 0);
	glCallList(estrellas);
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(GLint w, GLint h) 
{

	glViewport(0, 0, w, h); //utiliza toda el area de dibujo

	float ra = float(w) / float(h);
	float dist;
	float apert;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	dist = sqrt(pow(eyex, 2) + pow(eyey, 2) + pow(eyez, 2));
	float aux = asin(1 / dist) * 2;
	apert = (180 / PI) * aux;
	gluPerspective(apert, ra, 1, 20); 
}

void update()
{
	// Fase de actualizacion

	// Sin control del tiempo
	//alfa += 0.1;

	// Control del tiempo
	static const float omega = 1;	// Vueltas/sg

	// Hora anterior inicial
	static int antes = glutGet(GLUT_ELAPSED_TIME);

	// Hora actual
	int ahora = glutGet(GLUT_ELAPSED_TIME);

	// Tiempo transcurrido
	float tiempo_transcurrido = (float)(ahora - antes) / 1000.0;

	// incremento = velocidad * tiempo;
	alfa += 360 * omega * tiempo_transcurrido;

	// Actualizar la hora para la proxima vez
	antes = ahora;

	// Mandar evento de redibujo
	glutPostRedisplay();

}

void main(int argc, char** argv)
{
	// Initializations
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutCreateWindow(PROYECTO);
	init();

	// Callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(update);

	cout << PROYECTO << " en marcha" << endl;

	// Event loop
	glutMainLoop();
}
