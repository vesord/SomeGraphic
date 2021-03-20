#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "materials.h"
#include "FreeImage.h"

static const GLint windowWidth =  640;
static const GLint windowHeight = 640;
static const GLfloat windowRatio = (float)windowWidth / windowHeight;

static GLfloat lightAngle = 0.f;
static GLfloat figurAngle = 0.f;
static const GLfloat lightDAngle = 1.f;
static const GLfloat figurDAngle = 1.f;

typedef enum e_rotate_what {
	ROTATE_OBJECT,
	ROTATE_LIGHT
}			 t_rotate_what;

static GLuint texture;

static t_rotate_what rotateWhat = ROTATE_OBJECT;
static t_material_type materialType = MATERIAL_SILVER;

void init(void) {
	glClearColor(0.6f, 0.6f, 0.9f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	glViewport(0, 0, windowWidth, windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.f, windowRatio, 2., 200);	// switch
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void initLight() {
	GLfloat myAmbient[] = {0.2, 0.2, 0.2, 1.};
	GLfloat myDiffuse[] = {1., 1., 1., 1.};
	GLfloat mySpecular[] = {1., 1., 1., 1.};
	glLightfv(GL_LIGHT0, GL_AMBIENT, myAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, myDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, mySpecular);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void initTexture() {
	glEnable(GL_TEXTURE_2D);

	glGenTextures (1, &texture);
	glBindTexture (GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
				 width, height, 0, GL_RGB,
				 GL_UNSIGNED_BYTE, data);
}

void reshape(GLsizei W, GLsizei H) {
	if(windowRatio>W/H) glViewport(0,0,W,W/windowRatio);
	else glViewport(0,0,H*windowRatio,H);
}

void rotateObject() {
	rotateWhat = ROTATE_OBJECT;
}

void rotateLight() {
	rotateWhat = ROTATE_LIGHT;
}

void changeMaterial() {
	++materialType;
	if (materialType == MATERIAL_END)
		materialType = MATERIAL_NONE;
	applyMaterial(GL_FRONT, materialType);
}

void key(unsigned char key, int x, int y) {
	switch (key) {
		case 'f': glCullFace(GL_FRONT); break;
		case 'b': glCullFace(GL_BACK); break;
		case 'o': rotateObject(); break;
		case '1': rotateLight(); break;
		case 'm': changeMaterial(); break;
		default: break;
	}
	glutPostRedisplay();
}

void figure() {
	// back edge
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_POLYGON);
	glColor4f(0.f, 1.f, 0.f, 0.f);
	glNormal3f(0.f, 0.f, -1.f);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.f, 0.f, 0.f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.f, 1.f, 0.f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(2.f, 1.f, 0.f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(2.f, 0.f, 0.f);
	glEnd();
	// right edge
	glColor3f(0.1f, 0.7f, 1.f);
	glBegin(GL_POLYGON);
	glNormal3f(1.f, 0.f, 0.f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(2.f, 0.f, 0.f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(2.f, 1.f, 0.f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(2.f, 1.f, 1.f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(2.f, 0.f, 1.f);
	glEnd();
	// top edge
	glColor3f(0.7f, 0.1f, 0.4f);
	glBegin(GL_POLYGON);
	glNormal3f(0.f, 1.f, 0.f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(2.f, 1.f, 0.f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.f, 1.f, 0.f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.f, 1.f, 1.f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(2.f, 1.f, 1.f);
	glEnd();
	// left edge
	glColor3f(0.1f, 0.9f, 0.7f);
	glBegin(GL_POLYGON);
	glNormal3f(-1.f, 1.f, 0.f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.f, 1.f, 0.f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.f, 0.f, 0.f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.f, 0.f, 1.f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.f, 1.f, 1.f);
	glEnd();
	// front edge
	glColor3f(0.8f, 0.4f, 0.9f);
	glBegin(GL_POLYGON);
	glNormal3f(0.f, 0.f, 1.f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.f, 1.f, 1.f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.f, 0.f, 1.f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(2.f, 0.f, 1.f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(2.f, 1.f, 1.f);
	glEnd();
	// bottom edge
	glColor3f(0.8f, 0.4f, 0.9f);
	glBegin(GL_POLYGON);
	glNormal3f(0.f, -1.f, 0.f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.f, 0.f, 0.f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(2.f, 0.f, 0.f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(2.f, 0.f, 1.f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.f, 0.f, 1.f);
	glEnd();
}

void locateLight() {
	glPushMatrix();
	glRotatef(lightAngle, 0.f, 1.f, 0.f);
	GLfloat myLightPosition[] = {0.0, 3.0, 3.0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, myLightPosition);
	glPopMatrix();
}

void drawFigure() {
	glPushMatrix();
	glRotatef(figurAngle, 0.f, 1.f, 0.f);
	figure();
	glPopMatrix();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 4., 4., 0., 0., 0., 0., 1., 0.);

	locateLight();
	drawFigure();

	glFlush();
	glutSwapBuffers();
}

void normalizeAngle(GLfloat *angle) {
	if (*angle >= 360.f)
		*angle = 0.f;
}

void updateAngles() {
	switch (rotateWhat) {
		case ROTATE_OBJECT: figurAngle += figurDAngle; normalizeAngle(&figurAngle); break;
		case ROTATE_LIGHT: lightAngle += lightDAngle; normalizeAngle(&lightAngle); break;
		default: break;
	}
}

void idle() {
	updateAngles();
	glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("MY SUPER PROGRAM!");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(key);
	init();
//	initLight();
	initTexture();
//	applyMaterial(GL_BACK, MATERIAL_PERL);
//	applyMaterial(GL_FRONT, materialType);
	glutMainLoop();
}
