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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(leftCorner, rightCorner, bottomCorner, topCorner);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | );
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("MY SUPER PROGRAM!");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	init();
	glutMainLoop();
}