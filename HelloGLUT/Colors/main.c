#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>

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
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.f, windowRatio, 2., 200);	// switch
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void reshape(GLsizei W, GLsizei H) {
	if(windowRatio>W/H) glViewport(0,0,W,W/windowRatio);
	else glViewport(0,0,H*windowRatio,H);
}

void figure() {
	// back edge
	glColor3f(0.8f, 0.8f, 0.8f);
	glBegin(GL_POLYGON);
	glNormal3f(0.f, 0.f, -1.f);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(1.f, 1.f, 0.f);
	glVertex3f(2.f, 1.f, 0.f);
	glVertex3f(2.f, 0.f, 0.f);
	glEnd();
	// right edge
	glColor3f(0.1f, 0.7f, 1.f);
	glBegin(GL_POLYGON);
	glNormal3f(1.f, 0.f, 0.f);
	glVertex3f(2.f, 0.f, 0.f);
	glVertex3f(2.f, 1.f, 0.f);
	glVertex3f(2.f, 1.f, 1.f);
	glVertex3f(2.f, 0.f, 1.f);
	glEnd();
	// top edge
	glColor3f(0.7f, 0.1f, 0.4f);
	glBegin(GL_POLYGON);
	glNormal3f(0.f, 1.f, 0.f);
	glVertex3f(2.f, 1.f, 0.f);
	glVertex3f(1.f, 1.f, 0.f);
	glVertex3f(1.f, 1.f, 1.f);
	glVertex3f(2.f, 1.f, 1.f);
	glEnd();
	// left edge
	glColor3f(0.1f, 0.9f, 0.7f);
	glBegin(GL_POLYGON);
	glNormal3f(-1.f, 1.f, 0.f);
	glVertex3f(1.f, 1.f, 0.f);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 0.f, 1.f);
	glVertex3f(1.f, 1.f, 1.f);
	glEnd();
	// front edge
	glColor3f(0.8f, 0.4f, 0.9f);
	glBegin(GL_POLYGON);
	glNormal3f(0.f, 0.f, 1.f);
	glVertex3f(1.f, 1.f, 1.f);
	glVertex3f(0.f, 0.f, 1.f);
	glVertex3f(2.f, 0.f, 1.f);
	glVertex3f(2.f, 1.f, 1.f);
	glEnd();
	// bottom edge
	glColor3f(0.8f, 0.4f, 0.9f);
	glBegin(GL_POLYGON);
	glNormal3f(0.f, -1.f, 0.f);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(2.f, 0.f, 0.f);
	glVertex3f(2.f, 0.f, 1.f);
	glVertex3f(0.f, 0.f, 1.f);
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(1.0, 4., 4., 0., 0., 0., 0., 1., 0.);
	figure();

	glFlush();
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("MY SUPER PROGRAM!");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	init();
	glutMainLoop();
}