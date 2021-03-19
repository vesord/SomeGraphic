#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include "materials.h"

// More materials: http://www.it.hiof.no/~borres/j3d/explain/light/p-materials.html

typedef struct	s_material {
	t_material_type type;
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shine;
}				t_material;

static const t_material materials[] = {
	{MATERIAL_NONE,
		{0.0f, 0.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, 0.0f},
		0.f
	},
	{MATERIAL_GOLD,
		{0.24725f, 0.1995f, 0.0745f, 1.0f},
		{0.75164f, 0.60648f, 0.22648f, 1.0f},
		{0.628281f, 0.555802f, 0.366065f, 1.0f},
		51.2f
	},
	{MATERIAL_SILVER,
		{0.19225f, 0.19225f, 0.19225f, 1.0f},
		{0.50754f, 0.50754f, 0.50754f, 1.0f},
		{0.508273f, 0.508273f, 0.508273f, 1.0f},
		51.2f
	},
	{MATERIAL_POLISHED_BRONZE,
		{0.25f, 0.148f, 0.06475f, 1.0f},
		{0.4f, 0.2368f, 0.1036f, 1.0f},
		{0.774597f, 0.458561f, 0.200621f, 1.0f},
		76.8f
	},
	{MATERIAL_TURQUOISE,
		{0.1f, 0.18725f, 0.1745f, 0.8f},
		{0.396f, 0.74151f, 0.69102f, 0.8f},
		{0.297254f, 0.30829f, 0.306678f, 0.8f},
		12.8f
	},
	{MATERIAL_PERL,
		{0.25f, 0.20725f, 0.20725f, 0.922f},
		{1.0f, 0.829f, 0.829f, 0.922f},
		{0.296648f, 0.296648f, 0.296648f, 0.922f},
		11.264f
	}
};

void applyMaterial(GLenum cullMode, t_material_type materialType) {
	glMaterialf(cullMode, GL_SHININESS, materials[materialType].shine);
	glMaterialfv(cullMode, GL_AMBIENT, materials[materialType].ambient);
	glMaterialfv(cullMode, GL_DIFFUSE, materials[materialType].diffuse);
	glMaterialfv(cullMode, GL_SPECULAR, materials[materialType].specular);
}