#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

GLfloat R=640.0/480; //Форматное соотношение
GLfloat w=640;       //Ширина мирового окна
GLfloat h=480;       //Высота мирового окна
GLfloat l, r, b, t;  //Параметры мирового окна

GLdouble radius = 10.;
GLdouble eyex = 10.;
GLdouble eyez = 0.;
GLdouble eyey = 1.5;
GLfloat scalex = 1.f;
GLfloat scaley = 1.f;
GLfloat scalez = 1.f;

GLfloat angle = 0.f;
GLfloat dAngleStep = 0.02f;
GLfloat dScaleStep = 0.1f;

void init(void) {
	h=w/R; l=-w/80; r=w/80; b=-h/80; t=h/80;
	glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	glOrtho(l, r, b, t, -1000.0, 1000.0);				// switch
	gluPerspective(45.f, R, 2., 200);	// switch
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void increaseAngle(GLfloat step) {
	if (angle + step < -M_PI)
		angle = M_PI;
	else if (angle + step > M_PI)
		angle = -M_PI;
	else
		angle += step;
}

void keyFunction(unsigned char key, int x, int y) {
	switch (key) {
		case 'X':
			increaseAngle(dAngleStep);
			break;
		case 'Y':
			increaseAngle(-dAngleStep);
			break;
		default: break;
	}
	glutPostRedisplay();
}

void increaseScale(GLfloat mult) {
	scalex *= mult;
	scaley *= mult;
}

void mouseFunction(int button, int state, int x, int y) {
	if (state != GLUT_UP)
		return;
	switch (button) {
		case GLUT_LEFT_BUTTON:
			increaseScale(1. + dScaleStep);
			break;
		case GLUT_RIGHT_BUTTON:
			increaseScale(1. - dScaleStep);
			break;
		default: break;
	}
	glutPostRedisplay();
}


void reshape(GLsizei W, GLsizei H) {
	if(R>W/H) glViewport(0,0,W,W/R);
	else glViewport(0,0,H*R,H);
}

void countEyes() {
	eyex = sin(angle) * radius;
	eyez = cos(angle) * radius;
}

void fig(GLfloat x, GLfloat y, GLfloat z) {
	glPushMatrix();
	glTranslatef(x, y, x);
	glScalef(scalex, scaley, scalez);
	glutWireOctahedron();
	glPopMatrix();
}

void autoIncreaseScale() {
	static GLint phase = 1;
	static GLint period = 100;
	static GLfloat scaleMin = 0.5f;
	static GLfloat scaleMax = 2.5f;
	GLfloat sc;

	if (phase < period >> 1) {
		sc = scaleMin + (scaleMax - scaleMin) / (period << 1) * (phase++ << 1);
		scalex = sc;
		scaley = sc;
		scalez = sc;
	}
	else {
		sc = scaleMax - (scaleMax - scaleMin) / (period << 1) * (phase++ << 1);
		scalex = sc;
		scaley = sc;
		scalez = sc;
	}
	if (phase == period)
		phase = 1;
}

void idle() {
	increaseAngle(dAngleStep);	// switch
	autoIncreaseScale();		// switch
	glutPostRedisplay();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.f, 0.f, 0.f);

	countEyes();
	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);
	fig(0.f, 0.f, 0.f);
	fig(3.f, 0.f, 0.f);	// switch

	glFlush();
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("Myprog");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyFunction);
	glutMouseFunc(mouseFunction);
	init();

	glutMainLoop();
}