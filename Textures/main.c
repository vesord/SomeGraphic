#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "materials.h"

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

static t_rotate_what rotateWhat = ROTATE_OBJECT;
static t_material_type materialType = MATERIAL_SILVER;

typedef struct	s_image {
	unsigned long sizeX;
	unsigned long sizeY;
	char *data;
}				t_image;

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

t_image *imageLoad(char *filename) {
	FILE *file;
	t_image * image;
	unsigned long size; // size of the image in bytes.
	unsigned long i; // standard counter.
	unsigned short int planes; // number of planes in image (must be 1)
	unsigned short int bpp; // number of bits per pixel (must be 24)
	char temp; // temporary color storage for bgr-rgb conversion.

	image = malloc(sizeof(t_image));
	if (!image) {
		printf("malloc fails\n");
		return 0;
	}

	// make sure the file is there.
	if ((file = fopen(filename, "rb"))==NULL){
		printf("File Not Found : %s\n",filename);
		return 0;
	}

	// seek through the bmp header, up to the width/height:
	fseek(file, 18, SEEK_CUR);

	// read the width
	if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
		printf("Error reading width from %s.\n", filename);
		return 0;
	}
	//printf("Width of %s: %lu\n", filename, image->sizeX);

	// read the height
	if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
		printf("Error reading height from %s.\n", filename);
		return 0;
	}
	//printf("Height of %s: %lu\n", filename, image->sizeY);

	// calculate the size (assuming 24 bits or 3 bytes per pixel).
	size = image->sizeX * image->sizeY * 3;

	// read the planes
	if ((fread(&planes, 2, 1, file)) != 1) {
		printf("Error reading planes from %s.\n", filename);
		return 0;
	}

	if (planes != 1) {
		printf("Planes from %s is not 1: %u\n", filename, planes);
		return 0;
	}

	// read the bitsperpixel
	if ((i = fread(&bpp, 2, 1, file)) != 1) {
		printf("Error reading bpp from %s.\n", filename);
		return 0;
	}

	if (bpp != 24) {
		printf("Bpp from %s is not 24: %u\n", filename, bpp);
		return 0;
	}

	// seek past the rest of the bitmap header.
	fseek(file, 24, SEEK_CUR);

	// read the data.
	image->data = (char *) malloc(size);
	if (image->data == NULL) {
		printf("Error allocating memory for color-corrected image data");
		return 0;
	}
	if ((i = fread(image->data, size, 1, file)) != 1) {
		printf("Error reading image data from %s.\n", filename);
		return 0;
	}

	for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
		temp = image->data[i];
		image->data[i] = image->data[i+2];
		image->data[i+2] = temp;
	}
	return image;
}

void initTexture() {
	glEnable(GL_TEXTURE_2D);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	t_image *image = imageLoad("Star.bmp");
	if (!image)
		exit(1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image->sizeX, image->sizeY, GL_RGB, GL_UNSIGNED_BYTE, image->data);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->sizeX, image->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data);
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
	initLight();
	initTexture();
//	applyMaterial(GL_BACK, MATERIAL_PERL);
//	applyMaterial(GL_FRONT, materialType);
	glutMainLoop();
}

//#define checkImageWidth 64
//#define checkImageHeight 64
//
//GLubyte checkImage[checkImageWidth][checkImageHeight][3];
//
//void makeCheckImage(void){
//	int i, j, c;
//	for (i = 0; i < checkImageWidth; i++) {
//		for (j = 0; j < checkImageHeight; j++) {
//			c = ((((i&0x8)==0)^((j&0x8)==0)))*255;
//			checkImage[i][j][0] = (GLubyte) c;
//			checkImage[i][j][1] = (GLubyte) c;
//			checkImage[i][j][2] = (GLubyte) c;
//		}
//	}
//}


//
//void myinit(void)
//{
//	glClearColor (0.5, 0.5, 0.5, 0.0);
//
//	glEnable(GL_DEPTH_TEST);
//
//	glDepthFunc(GL_LESS);
//
//	Image *image1 = loadTexture();
//
//	if(image1 == NULL){
//
//		printf("Image was not returned from loadTexture\n");
//
//		exit(0);
//
//	}
//
//	makeCheckImage();
//
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//
//	// Create Texture
//
//	glGenTextures(2, texture);
//
//	glBindTexture(GL_TEXTURE_2D, texture[0]);
//
//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //scale linearly when image bigger than texture
//
//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //scale linearly when image smalled than texture
//
//	glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0,
//
//				 GL_RGB, GL_UNSIGNED_BYTE, image1->data);
//
//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
//
//	glBindTexture(GL_TEXTURE_2D, texture[1]);
//
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//
//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
//
//	glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
//
//				 checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
//
//	glEnable(GL_TEXTURE_2D);
//	glShadeModel(GL_FLAT);
//}