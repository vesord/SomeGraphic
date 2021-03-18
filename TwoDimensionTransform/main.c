#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define PI 3.1459
GLfloat R=640.0/640; //Форматное соотношение
GLfloat w=640;       //Ширина мирового окна
GLfloat h=640;       //Высота мирового окна
GLfloat l, r, b, t;  //Параметры мирового окна
GLfloat f=0.0f;
GLfloat dStep = 60;
GLfloat dAngle = 16.0f;
GLfloat dScale = 1.0f;

void init(void) { //Расчет параметров мирового окна
	h=w/R; l=-w/2; r=w/2; b=-h/2; t=h/2;
	glClearColor(1.0,1.0,0.3,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(l, r, b, t);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void reshape(GLsizei W, GLsizei H) {
	if(R>W/H) glViewport(0,0,W,W/R);
	else glViewport(0,0,H*R,H);
}

void showAxis(void) {
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0, t);
	glVertex2f(0, 0);
	glVertex2f(r, 0);
	glEnd();
}

void showAxisSmall(void) {
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(0.f, 0.f);
	glVertex2f(0.f, 30.f);
	glVertex2f(0.f, 0.f);
	glVertex2f(30.f, 0.f);
	glEnd();
}

void fig0(void) {
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(100.0f, 100.0f);
	glVertex2f(-100.0f, 100.0f);
	glVertex2f(-100.0f, -100.0f);
	glVertex2f(100.0f, -100.0f);
	glEnd();
}

void fig1Modify(GLfloat step) {
	glTranslatef(-step, step, 0.f);
	glRotatef(90.f, 0.f, 0.f, 1.f);
}

void fig1(GLfloat step) {
	fig1Modify(step);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.f, 50.f);
	glVertex2f(0.f, -50.f);
	glVertex2f(50.f, 0.f);
	glEnd();
}

//void fig2Modify(GLfloat step) {
//	glRotatef(45.f, 0.f, 0.f, 1.f);
//	glTranslatef(sqrtf(2.f * step * step - 1.41f), 0.f, 0.f);
//}

void fig2() {
	glBegin(GL_LINE_LOOP);
	glColor3f(0.9f, 0.1f, 0.9f);
	glVertex2d(0.f, 25.f);
	glVertex2d(-5.f, 5.f);
	glVertex2d(-25.f, 0.f);
	glVertex2d(-5.f, -5.f);
	glVertex2d(0.f, -25.f);
	glVertex2d(5.f, -5.f);
	glVertex2d(25.f, 0.f);
	glVertex2d(5.f, 5.f);
	glEnd();
}

void updateParams() {
	static GLfloat stepScaler = 3.f;
	static GLfloat scaleScaler = 0.05f;
	dAngle += 1.f; if (dAngle >= 360.f) dAngle = 0.f;
	dStep += stepScaler; if (dStep >= 140.f || dStep <= 60) stepScaler *= -1.f;
	dScale += scaleScaler; if (dScale <= 0.5f || dScale >= 2.0f) scaleScaler *= -1.f;
}

void drawFig0() {
	glPushMatrix();
	glColor3f(0.f, 1.f, 0.f);
	glRotatef(-dAngle, 0.f, 0.f, 1.f);
	fig0();
	glPopMatrix();
}

void bigModify(GLfloat angle, GLfloat step, GLfloat scale) {
//	glScalef(scale, scale, 0.f);
	glRotatef(angle, 0.f, 0.f, 1.f);
	glTranslatef(step, 0.f, 0.f);
}

void drawFig1() {
	glPushMatrix();
	bigModify(dAngle, dStep, dScale);
	for (int i = 0; i < 4; ++i)
		fig1(dStep);
	glPopMatrix();
}

void drawFig2() {
	static GLint count = 8;
	static GLfloat angle = 360.f / 8.f;
	for (int i = 0; i < 8; ++i) {
		glPushMatrix();
		glRotatef(angle * i - dAngle / 2.f, 0.f, 0.f, 1.f);
		glTranslatef(250.f, 0.f, 0.f);
		glRotatef(dAngle, 0.f, 0.f, 1.f);
		fig2();
		glPopMatrix();
	}
}

void squaresAndTriangles() {
	glClear(GL_COLOR_BUFFER_BIT);

//	showAxis();
	drawFig0();
	drawFig1();
	drawFig2();

	glFlush();
	glutSwapBuffers();

	updateParams();
}

int main(int argc, char **argv) {
	void (*task) ();
	task = squaresAndTriangles;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("Myprog");
	glutReshapeFunc(reshape);
	glutDisplayFunc(task);
	glutIdleFunc(task);
	init();
	glutMainLoop();
}