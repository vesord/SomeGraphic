#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

GLfloat R=640.0/480; //Форматное соотношение
GLfloat w=640;       //Ширина мирового окна
GLfloat h=480;       //Высота мирового окна
GLfloat l, r, b, t;  //Параметры мирового окна

GLdouble eyex = 20.;
GLdouble eyey = 0.;
GLdouble eyez = 20.;

//const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
//const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
//const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
//
//const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
//const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
//const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
//const GLfloat high_shininess[] = { 100.0f };

void init(void) {
	h=w/R; l=-w/2; r=w/2; b=-h/2; t=h/2;
	glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-w/h, w/h, -1.0, 1.0, 2.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity() ;

//	glEnable(GL_CULL_FACE);
//	glCullFace(GL_BACK);

//	glDepthFunc(GL_LESS);

//	glEnable(GL_LIGHT0);
//	glEnable(GL_NORMALIZE);
//	glEnable(GL_COLOR_MATERIAL);
//	glEnable(GL_LIGHTING);
//
//	glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
//	glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
//	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
//	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//
//	glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
//	glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
//	glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
//	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

void reshape(GLsizei W, GLsizei H) {
	if(R>W/H) glViewport(0,0,W,W/R);
	else glViewport(0,0,H*R,H);
}


void disp() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.f, 0.f, 0.f);
	static GLfloat dAngle = 0.f;

	glPushMatrix();
	gluLookAt(eyex, eyey, eyez, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);
	glRotatef(dAngle, 0.f, 1.f, 0.f);
	glutWireOctahedron();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.f, 0.f, -10.f);
	glutWireOctahedron();
	glPopMatrix();

	dAngle += 1.f;
	if (dAngle >= 360.f) dAngle = 0.f;

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
	glutDisplayFunc(disp);
	glutIdleFunc(disp);
	init();

	glutMainLoop();
}