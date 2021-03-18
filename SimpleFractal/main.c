#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <stdlib.h>
#include "utils.h"

static const GLint windowWidth =  640;
static const GLint windowHeight = 640;
static const GLfloat windowRatio = (float)windowWidth / windowHeight;
static const GLint leftCorner = 	-windowWidth / 2;
static const GLint rightCorner =	 windowWidth / 2;
static const GLint topCorner = 		 windowHeight / 2;
static const GLint bottomCorner = 	-windowHeight / 2;

void init(void) {
	glClearColor(0.33f,0.33f,0.33f,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(leftCorner, rightCorner, bottomCorner, topCorner);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void reshape(GLsizei W, GLsizei H) {
	if(windowRatio>W/H) glViewport(0,0,W,W/windowRatio);
	else glViewport(0,0,H*windowRatio,H);
}

void triangle(GLfloat r, GLfloat g, GLfloat b) {
	glColor3f(r, g, b);
	glBegin(GL_TRIANGLES);
	glVertex2f(0.f, 0.f);
	glVertex2f(1.f, 0.f);
	glVertex2f(0.5f, 0.86602540378f);
	glEnd();
}

void drawTriangles(GLint count, GLfloat scale) {
	if (count == 0)
		return;

	glScalef(scale, scale, 0.f);
	triangle(randFloat(), randFloat(), randFloat());
	glRotatef(30.f, 0.f, 0.f, 1.f);
	glTranslatef(1.f, 0.f, 0.f);
	glRotatef(120.f, 0.f, 0.f, 1.f);
	drawTriangles(count - 1, scale / 2);
}

void display() {
	static GLint trianglesToDisplay;
	static GLint maxTrianglesToDisplay = 20;

	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	drawTriangles(1, windowHeight * 0.9f);
	glPopMatrix();

	if (trianglesToDisplay == maxTrianglesToDisplay) {
		trianglesToDisplay = 1;
	}

	glFlush();
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("MY SUPER PROGRAM!");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	init();
	glutMainLoop();
}
